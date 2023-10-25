//11127126 黃柏寧 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Maze {
	public:
    	bool Get_Matrix(const string& filename);//根據讀入檔建造二維陣列 
    	void printPath(int target);//印出走過的路徑及成功找到'G'的路徑 
    	bool findPath(int x, int y, int target);//尋找到'G'的路徑
    	void recordG();//儲存每次找到'G'的路徑
    private:
		bool getLastResult = false;//得到上一步的結果(true or false) 
		int totalgoals = 0;//目前找到幾個'G'
		int rows;//行數 
    	int cols;//列數
		string nextmove = "right";//老鼠下一步該走的方向，預設為向右。right代表向右，down代表向下，left代表向左，up代表向上，no代表退回上一個位置 
    	string lastmove = "null";//紀錄老鼠上一步的方向，在退回上一格時會用到 
		vector<vector<char>> maze;//儲存走過的路徑 
    	vector<vector<char>> successMaze;//儲存成功找到目前'G'的路徑
		vector<vector<char>> haveSuccess;//儲存找到'G'的所有路徑，避免有些點在找其他'G'時被改成'E' 
    	bool isValid(int x, int y);//檢查某個座標 (x, y)是否有效，即該座標是否位於迷宮內部並且是否可以通行。 
    	void nextDirection(int x, int y);//尋找老鼠下一步該走的方向
};

bool Maze::Get_Matrix(const string& filename) {
	string read = "input" + filename + ".txt";
    ifstream inputFile(read);
    
    if (inputFile.is_open()) {
    	inputFile >> cols >> rows; //讀Maze的行數及列數

    	//根據行數及列數改變maze、successMaze、haveSuccess的大小 ，並初始化指定的行數（rows）和列數（cols） 
    	maze.resize(rows, vector<char>(cols));
    	successMaze.resize(rows, vector<char>(cols));
    	haveSuccess.resize(rows, vector<char>(cols));
    	
    	//把檔案的內容儲存在maze
    	for (int i = 0; i < rows; ++i) {
        	for (int j = 0; j < cols; ++j) {
            	inputFile >> maze[i][j];
        	}
    	}
    
    	successMaze.assign(maze.begin(), maze.end());//讓二維陣列successMaze跟maze初始狀態完全相同 
    	haveSuccess.assign(maze.begin(), maze.end());//讓二維陣列haveSuccessMaze跟maze初始狀態完全相同
    	inputFile.close();
    	return true;
    }
    else {
    	cerr << "\nUnable to open file: " << filename;
        return false;
	}
}

bool Maze::isValid(int x, int y) {
	
	//判斷當前座標是否有效，return true為有效，return false為無效 
    if (x >= 0 && x < rows && y >= 0 && y < cols && (maze[x][y] == 'E' || maze[x][y] == 'G')) return true;
    return false;
} 

void Maze::recordG() {
	
	//當成功找到一個'G'時，就先把目前的路徑存到haveSuccess裡 
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(successMaze[i][j] == 'V') haveSuccess[i][j] = 'R';
		}
	}
}

void Maze::nextDirection(int x, int y) {
	
	//判斷老鼠下一步的方向，依照右、下、左、上的順序檢查目前位置的四周有沒有路可以走，沒有的話就退回上一格，並修改nextmove 
	if (nextmove == "right") {
		if(isValid(x, y + 1) == true) nextmove = "right";
		else if (isValid(x + 1, y) == true) nextmove = "down";
		else if(isValid(x, y - 1) == true) nextmove = "left";
		else if(isValid(x - 1, y) == true) nextmove = "up";
		else nextmove = "no";
	}
	else if (nextmove == "down") {
		if(isValid(x + 1, y) == true) nextmove == "down";
		else if (isValid(x, y - 1) == true) nextmove = "left";
		else if(isValid(x - 1, y) == true) nextmove = "up";
		else if(isValid(x, y + 1) == true) nextmove = "right";
		else nextmove = "no";	
	}
	else if (nextmove == "left") {
		if(isValid(x, y - 1) == true) nextmove == "left";
		else if (isValid(x - 1, y) == true) nextmove = "up";
		else if(isValid(x, y + 1) == true) nextmove = "right";
		else if(isValid(x + 1, y) == true) nextmove = "down";
		else nextmove = "no";
	}
	else if (nextmove == "up") {
		if(isValid(x - 1, y) == true) nextmove == "up";
		else if (isValid(x, y + 1) == true) nextmove = "right";
		else if(isValid(x + 1, y) == true) nextmove = "down";
		else if(isValid(x, y - 1) == true) nextmove = "left";
		else nextmove = "no";
	}
	//如果方向是退回上一格，就再檢查一遍其他方向有沒有路可以走 
	else if(nextmove == "no") {
		if(lastmove ==  "right") {
			if (isValid(x + 1, y) == true) nextmove = "down";
			else if(isValid(x, y - 1) == true) nextmove = "left";
			else if(isValid(x - 1, y) == true) nextmove = "up";
		}
		else if(lastmove == "down") {
			if (isValid(x, y - 1) == true) nextmove = "left";
			else if(isValid(x - 1, y) == true) nextmove = "up";
			else if(isValid(x, y + 1) == true) nextmove = "right";
		}
		else if(lastmove == "left"){
			if (isValid(x - 1, y) == true) nextmove = "up";
			else if(isValid(x, y + 1) == true) nextmove = "right";
			else if(isValid(x + 1, y) == true) nextmove = "down";
		}
		else if(lastmove == "up"){
			if (isValid(x, y + 1) == true) nextmove = "right";
			else if(isValid(x + 1, y) == true) nextmove = "down";
			else if(isValid(x, y - 1) == true) nextmove = "left";
		}
	}
}


bool Maze::findPath(int x, int y, int target) {
	
	if (isValid(x, y) == false) return false;//如果當前座標為無效座標，就return false 
	
    if (maze[x][y] == 'G') {
    	totalgoals++;
    	
    	if(target > 1) recordG();//如果要找的'G'不只一個，就先存目前找到'G'的路徑 
    	
    	if(target == totalgoals) return true;//要找數量等於當前數量，就return true 
    	else if(target > 1 || totalgoals < target) {
    		
    		maze[x][y] = 'g';//避免'G'的上一格在找方向時又再找到'G' 
    		nextDirection(x, y);// 找'G'的下一步方向 
    		 
    		if(nextmove == "right") {
    			
    			getLastResult = findPath(x, y + 1, target);//紀錄下一步的結果 
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次 
    				
    				//把多走的在successMaze裡改成'E' 
    				if(successMaze[x][y + 1] != 'G' && successMaze[x][y + 1] != 'O') successMaze[x][y + 1] = 'E';
    				
    				if(nextmove == "no") return false;//如果檢查第二遍還是沒路可走，就return false
    				else {
    					//根據nextmove去尋找下一步 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "down") {
    			
    			getLastResult = findPath(x - 1, y, target);//紀錄下一步的結果
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次 
    				
    				//把多走的在successMaze裡改成'E'
    				if(successMaze[x - 1][y] != 'G' && successMaze[x - 1][y] != 'O') successMaze[x - 1][y] = 'E';
    				
    				if(nextmove == "no") return false;//如果檢查第二遍還是沒路可走，就return false
    				else {
    					//根據nextmove去尋找下一步 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "left") {
    			
    			getLastResult = findPath(x, y - 1, target);//紀錄下一步的結果
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次
    				
    				//把多走的在successMaze裡改成'E'
    				if(successMaze[x][y - 1] != 'G' && successMaze[x][y - 1] != 'O') successMaze[x][y - 1] = 'E';
    				
    				if(nextmove == "no") return false;//如果檢查第二遍還是沒路可走，就return false
    				else {
    					//根據nextmove去尋找下一步 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "up") {
    			
    			getLastResult = findPath(x - 1, y, target);//紀錄下一步的結果
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次 
    				
    				//把多走的在successMaze裡改成'E'
    				if(successMaze[x - 1][y] != 'G' && successMaze[x - 1][y] != 'O') successMaze[x - 1][y] = 'E';
    				
    				if(nextmove == "no") return false;//如果檢查第二遍還是沒路可走，就return false
    				else {
    					//根據nextmove去尋找下一步 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "no") return false;//如果沒路可走，就return false
		}
    	return true;
	}
    else if ((maze[x][y] == 'E') && totalgoals < target) {
    	
    	lastmove = nextmove;//紀錄上一步的方向，退回上一格時會用到 
        nextDirection(x, y);//檢查下一步方向 
        
        //把目前所在的點標記為走過
		maze[x][y] = 'V';
        successMaze[x][y] = 'V';
        
        //如果目前的座標沒路可走，就退回上一格 
		if(nextmove == "no") {
			successMaze[x][y] = 'E';
			return false;
		}
        
        if(nextmove == "right") {
        	
        	getLastResult = findPath(x, y + 1, target);//紀錄下一步的結果
        	
        	if(getLastResult == false) {
        		
        		lastmove = "right";//紀錄上一步的方向
        		
        		//把多走的在successMaze裡改成'E'
        		if(successMaze[x][y + 1] != 'G' && successMaze[x][y + 1] != 'O') successMaze[x][y + 1] = 'E';
        		
        		nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次 
        		
        		//如果檢查第二遍還是沒路可走，就return false 
        		if(nextmove == "no") {
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//根據nextmove去尋找下一步 
					if(nextmove == "right") return findPath(x, y + 1, target);
					else if(nextmove == "down") return findPath(x + 1, y, target);
					else if(nextmove == "left") return findPath(x, y - 1, target);
					else if(nextmove == "up") return findPath(x - 1, y, target);
				}
			}
			else return true;
		}
		else if(nextmove == "down") {
			
			getLastResult = findPath(x + 1, y, target);//紀錄下一步的結果
			
			if(getLastResult == false) {
				
				lastmove = "down";//紀錄上一步的方向 
				
				//把多走的在successMaze裡改成'E'
				if(successMaze[x + 1][y] != 'G' && successMaze[x + 1][y] != 'O') successMaze[x + 1][y] = 'E';
				
				nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次 
				
				//如果檢查第二遍還是沒路可走，就return false
        		if(nextmove == "no"){
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//根據nextmove去尋找下一步
					if(nextmove == "right") return findPath(x, y + 1, target);
					else if(nextmove == "down") return findPath(x + 1, y, target);
					else if(nextmove == "left") return findPath(x, y - 1, target);
					else if(nextmove == "up") return findPath(x - 1, y, target);
				}
			}
			else return true;
		}
		else if(nextmove == "left") {
			
			getLastResult = findPath(x, y - 1, target);//紀錄下一步的結果
			
			if(getLastResult == false) {
				
				lastmove = "left";//紀錄上一步的方向
				
				//把多走的在successMaze裡改成'E'
				if(successMaze[x][y - 1] != 'G' && successMaze[x][y - 1] != 'O') successMaze[x][y - 1] = 'E';
				
				nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次
				
				//如果檢查第二遍還是沒路可走，就return false
        		if(nextmove == "no") {
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//根據nextmove去尋找下一步
					if(nextmove == "right") return findPath(x, y + 1, target);
					else if(nextmove == "down") return findPath(x + 1, y, target);
					else if(nextmove == "left") return findPath(x, y - 1, target);
					else if(nextmove == "up") return findPath(x - 1, y, target);
				}
			}
			else return true;
		}
		else if(nextmove == "up") {
			
			getLastResult = findPath(x - 1, y, target);//紀錄下一步的結果
			
			if(getLastResult == false) {
				
				lastmove = "up";//紀錄上一步的方向
				
				//把多走的在successMaze裡改成'E'
				if(successMaze[x - 1][y] != 'G' && successMaze[x - 1][y] != 'O' && isValid(x, y + 1) == false) successMaze[x - 1][y] = 'E';
				
				nextDirection(x, y);//可能不只一個方向可以走，所以要再找一次
				
				//如果檢查第二遍還是沒路可走，就return false
        		if(nextmove == "no") {
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//根據nextmove去尋找下一步
					if(nextmove == "right") return findPath(x, y + 1, target);
					else if(nextmove == "down") return findPath(x + 1, y, target);
					else if(nextmove == "left") return findPath(x, y - 1, target);
					else if(nextmove == "up") return findPath(x - 1, y, target);
				}
			}
			else return true;
		}
        return true;
    }
}

void Maze::printPath(int target) {
	
	//印出走過的路徑
	for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
        	if(maze[i][j] == 'g') maze[i][j] = 'G';//把所有的'g'改成'G' 
            cout << maze[i][j];
        }
        cout << endl;
    } 
    
    cout<<endl;
    
    //成功找到'G'的路徑 
    if (target == totalgoals) {
        for (int i = 0; i < rows; ++i) {
        	for (int j = 0; j < cols; ++j) {
        		if(successMaze[i][j] == 'V') successMaze[i][j] = 'R';//把所有的'V'改成'R'
        		if(haveSuccess[i][j] == 'R') successMaze[i][j] = 'R';//把過程中因為找其他'G'而被改成'E'的路徑補上
        		cout<<successMaze[i][j];
        	}
        	cout << endl;
    	}
    }
    
    cout<<"\n";
}

int main(void) {
	int command = 0;
	
	do {
		Maze aMaze; // a matrix
		string fileName; // 檔案名稱 
		int target = 1; // 預設為找1個'G' 
		
		cout << endl << "*** Path Finding ***"; 
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *"; 
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		cin>>command;
		
		if(command == 1 || command == 2) {
			cout<<"\nInput a file number: ";
			cin>>fileName;
			
			if(command == 2) {
				
				cout<<"\nNumber of G (goals): ";
				cin>>target;//總共要找幾個'G'
				
				while(target < 0) {
					cout<<"Please enter a positive number";
					cout<<"\nNumber of G (goals): ";
					cin>>target;
				}
			}
			
			if(aMaze.Get_Matrix(fileName) == true) {
				aMaze.findPath(0, 0, target);
				aMaze.printPath(target);
			}
		}
		else if(!command) break;
		else cout<<"\nCommand doesn't exit!\n";
	} while(true);
	
	system("pause");
    return 0;
}
