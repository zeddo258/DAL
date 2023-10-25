//11127126 ���f�� 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Maze {
	public:
    	bool Get_Matrix(const string& filename);//�ھ�Ū�J�ɫسy�G���}�C 
    	void printPath(int target);//�L�X���L�����|�Φ��\���'G'�����| 
    	bool findPath(int x, int y, int target);//�M���'G'�����|
    	void recordG();//�x�s�C�����'G'�����|
    private:
		bool getLastResult = false;//�o��W�@�B�����G(true or false) 
		int totalgoals = 0;//�ثe���X��'G'
		int rows;//��� 
    	int cols;//�C��
		string nextmove = "right";//�ѹ��U�@�B�Ө�����V�A�w�]���V�k�Cright�N���V�k�Adown�N���V�U�Aleft�N���V���Aup�N���V�W�Ano�N���h�^�W�@�Ӧ�m 
    	string lastmove = "null";//�����ѹ��W�@�B����V�A�b�h�^�W�@��ɷ|�Ψ� 
		vector<vector<char>> maze;//�x�s���L�����| 
    	vector<vector<char>> successMaze;//�x�s���\���ثe'G'�����|
		vector<vector<char>> haveSuccess;//�x�s���'G'���Ҧ����|�A�קK�����I�b���L'G'�ɳQ�令'E' 
    	bool isValid(int x, int y);//�ˬd�Y�Ӯy�� (x, y)�O�_���ġA�Y�Ӯy�ЬO�_���g�c�����åB�O�_�i�H�q��C 
    	void nextDirection(int x, int y);//�M��ѹ��U�@�B�Ө�����V
};

bool Maze::Get_Matrix(const string& filename) {
	string read = "input" + filename + ".txt";
    ifstream inputFile(read);
    
    if (inputFile.is_open()) {
    	inputFile >> cols >> rows; //ŪMaze����ƤΦC��

    	//�ھڦ�ƤΦC�Ƨ���maze�BsuccessMaze�BhaveSuccess���j�p �A�ê�l�ƫ��w����ơ]rows�^�M�C�ơ]cols�^ 
    	maze.resize(rows, vector<char>(cols));
    	successMaze.resize(rows, vector<char>(cols));
    	haveSuccess.resize(rows, vector<char>(cols));
    	
    	//���ɮת����e�x�s�bmaze
    	for (int i = 0; i < rows; ++i) {
        	for (int j = 0; j < cols; ++j) {
            	inputFile >> maze[i][j];
        	}
    	}
    
    	successMaze.assign(maze.begin(), maze.end());//���G���}�CsuccessMaze��maze��l���A�����ۦP 
    	haveSuccess.assign(maze.begin(), maze.end());//���G���}�ChaveSuccessMaze��maze��l���A�����ۦP
    	inputFile.close();
    	return true;
    }
    else {
    	cerr << "\nUnable to open file: " << filename;
        return false;
	}
}

bool Maze::isValid(int x, int y) {
	
	//�P�_���e�y�ЬO�_���ġAreturn true�����ġAreturn false���L�� 
    if (x >= 0 && x < rows && y >= 0 && y < cols && (maze[x][y] == 'E' || maze[x][y] == 'G')) return true;
    return false;
} 

void Maze::recordG() {
	
	//�����\���@��'G'�ɡA�N����ثe�����|�s��haveSuccess�� 
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(successMaze[i][j] == 'V') haveSuccess[i][j] = 'R';
		}
	}
}

void Maze::nextDirection(int x, int y) {
	
	//�P�_�ѹ��U�@�B����V�A�̷ӥk�B�U�B���B�W�������ˬd�ثe��m���|�P���S�����i�H���A�S�����ܴN�h�^�W�@��A�íק�nextmove 
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
	//�p�G��V�O�h�^�W�@��A�N�A�ˬd�@�M��L��V���S�����i�H�� 
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
	
	if (isValid(x, y) == false) return false;//�p�G���e�y�Ь��L�Įy�СA�Nreturn false 
	
    if (maze[x][y] == 'G') {
    	totalgoals++;
    	
    	if(target > 1) recordG();//�p�G�n�䪺'G'���u�@�ӡA�N���s�ثe���'G'�����| 
    	
    	if(target == totalgoals) return true;//�n��ƶq������e�ƶq�A�Nreturn true 
    	else if(target > 1 || totalgoals < target) {
    		
    		maze[x][y] = 'g';//�קK'G'���W�@��b���V�ɤS�A���'G' 
    		nextDirection(x, y);// ��'G'���U�@�B��V 
    		 
    		if(nextmove == "right") {
    			
    			getLastResult = findPath(x, y + 1, target);//�����U�@�B�����G 
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@�� 
    				
    				//��h�����bsuccessMaze�̧令'E' 
    				if(successMaze[x][y + 1] != 'G' && successMaze[x][y + 1] != 'O') successMaze[x][y + 1] = 'E';
    				
    				if(nextmove == "no") return false;//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false
    				else {
    					//�ھ�nextmove�h�M��U�@�B 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "down") {
    			
    			getLastResult = findPath(x - 1, y, target);//�����U�@�B�����G
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@�� 
    				
    				//��h�����bsuccessMaze�̧令'E'
    				if(successMaze[x - 1][y] != 'G' && successMaze[x - 1][y] != 'O') successMaze[x - 1][y] = 'E';
    				
    				if(nextmove == "no") return false;//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false
    				else {
    					//�ھ�nextmove�h�M��U�@�B 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "left") {
    			
    			getLastResult = findPath(x, y - 1, target);//�����U�@�B�����G
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@��
    				
    				//��h�����bsuccessMaze�̧令'E'
    				if(successMaze[x][y - 1] != 'G' && successMaze[x][y - 1] != 'O') successMaze[x][y - 1] = 'E';
    				
    				if(nextmove == "no") return false;//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false
    				else {
    					//�ھ�nextmove�h�M��U�@�B 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "up") {
    			
    			getLastResult = findPath(x - 1, y, target);//�����U�@�B�����G
    			
    			if(getLastResult == false){
    				
    				nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@�� 
    				
    				//��h�����bsuccessMaze�̧令'E'
    				if(successMaze[x - 1][y] != 'G' && successMaze[x - 1][y] != 'O') successMaze[x - 1][y] = 'E';
    				
    				if(nextmove == "no") return false;//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false
    				else {
    					//�ھ�nextmove�h�M��U�@�B 
    					if(nextmove == "right") return findPath(x, y + 1, target);
						else if(nextmove == "down") return findPath(x + 1, y, target);
						else if(nextmove == "left") return findPath(x, y - 1, target);
						else if(nextmove == "up") return findPath(x - 1, y, target);
					}
				}
				else return true;
			}
    		else if(nextmove == "no") return false;//�p�G�S���i���A�Nreturn false
		}
    	return true;
	}
    else if ((maze[x][y] == 'E') && totalgoals < target) {
    	
    	lastmove = nextmove;//�����W�@�B����V�A�h�^�W�@��ɷ|�Ψ� 
        nextDirection(x, y);//�ˬd�U�@�B��V 
        
        //��ثe�Ҧb���I�аO�����L
		maze[x][y] = 'V';
        successMaze[x][y] = 'V';
        
        //�p�G�ثe���y�ШS���i���A�N�h�^�W�@�� 
		if(nextmove == "no") {
			successMaze[x][y] = 'E';
			return false;
		}
        
        if(nextmove == "right") {
        	
        	getLastResult = findPath(x, y + 1, target);//�����U�@�B�����G
        	
        	if(getLastResult == false) {
        		
        		lastmove = "right";//�����W�@�B����V
        		
        		//��h�����bsuccessMaze�̧令'E'
        		if(successMaze[x][y + 1] != 'G' && successMaze[x][y + 1] != 'O') successMaze[x][y + 1] = 'E';
        		
        		nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@�� 
        		
        		//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false 
        		if(nextmove == "no") {
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//�ھ�nextmove�h�M��U�@�B 
					if(nextmove == "right") return findPath(x, y + 1, target);
					else if(nextmove == "down") return findPath(x + 1, y, target);
					else if(nextmove == "left") return findPath(x, y - 1, target);
					else if(nextmove == "up") return findPath(x - 1, y, target);
				}
			}
			else return true;
		}
		else if(nextmove == "down") {
			
			getLastResult = findPath(x + 1, y, target);//�����U�@�B�����G
			
			if(getLastResult == false) {
				
				lastmove = "down";//�����W�@�B����V 
				
				//��h�����bsuccessMaze�̧令'E'
				if(successMaze[x + 1][y] != 'G' && successMaze[x + 1][y] != 'O') successMaze[x + 1][y] = 'E';
				
				nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@�� 
				
				//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false
        		if(nextmove == "no"){
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//�ھ�nextmove�h�M��U�@�B
					if(nextmove == "right") return findPath(x, y + 1, target);
					else if(nextmove == "down") return findPath(x + 1, y, target);
					else if(nextmove == "left") return findPath(x, y - 1, target);
					else if(nextmove == "up") return findPath(x - 1, y, target);
				}
			}
			else return true;
		}
		else if(nextmove == "left") {
			
			getLastResult = findPath(x, y - 1, target);//�����U�@�B�����G
			
			if(getLastResult == false) {
				
				lastmove = "left";//�����W�@�B����V
				
				//��h�����bsuccessMaze�̧令'E'
				if(successMaze[x][y - 1] != 'G' && successMaze[x][y - 1] != 'O') successMaze[x][y - 1] = 'E';
				
				nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@��
				
				//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false
        		if(nextmove == "no") {
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//�ھ�nextmove�h�M��U�@�B
					if(nextmove == "right") return findPath(x, y + 1, target);
					else if(nextmove == "down") return findPath(x + 1, y, target);
					else if(nextmove == "left") return findPath(x, y - 1, target);
					else if(nextmove == "up") return findPath(x - 1, y, target);
				}
			}
			else return true;
		}
		else if(nextmove == "up") {
			
			getLastResult = findPath(x - 1, y, target);//�����U�@�B�����G
			
			if(getLastResult == false) {
				
				lastmove = "up";//�����W�@�B����V
				
				//��h�����bsuccessMaze�̧令'E'
				if(successMaze[x - 1][y] != 'G' && successMaze[x - 1][y] != 'O' && isValid(x, y + 1) == false) successMaze[x - 1][y] = 'E';
				
				nextDirection(x, y);//�i�ण�u�@�Ӥ�V�i�H���A�ҥH�n�A��@��
				
				//�p�G�ˬd�ĤG�M�٬O�S���i���A�Nreturn false
        		if(nextmove == "no") {
        			successMaze[x][y] = 'E';
        			return false;
				}
				else {
					//�ھ�nextmove�h�M��U�@�B
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
	
	//�L�X���L�����|
	for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
        	if(maze[i][j] == 'g') maze[i][j] = 'G';//��Ҧ���'g'�令'G' 
            cout << maze[i][j];
        }
        cout << endl;
    } 
    
    cout<<endl;
    
    //���\���'G'�����| 
    if (target == totalgoals) {
        for (int i = 0; i < rows; ++i) {
        	for (int j = 0; j < cols; ++j) {
        		if(successMaze[i][j] == 'V') successMaze[i][j] = 'R';//��Ҧ���'V'�令'R'
        		if(haveSuccess[i][j] == 'R') successMaze[i][j] = 'R';//��L�{���]�����L'G'�ӳQ�令'E'�����|�ɤW
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
		string fileName; // �ɮצW�� 
		int target = 1; // �w�]����1��'G' 
		
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
				cin>>target;//�`�@�n��X��'G'
				
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