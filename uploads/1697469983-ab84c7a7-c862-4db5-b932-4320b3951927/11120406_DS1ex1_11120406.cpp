//DS1ex1_11120406 謝宸恩
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>  

using namespace std;

class Maze 
{
	public:
    	Maze(){
        	numRows = 0;	//	直行 
        	numCols = 0;	//	橫列 
    	}

    	bool load(const string& fileNumber){
    		
        	// 建構檔案名稱 
        	string filename = "input" + fileNumber + ".txt";
        	ifstream inputFile(filename.c_str());

        	if (!inputFile) {
            	cerr << "無法法打開文件" << endl;
            	return false;
        	}

        	// 讀取行列數 
        	inputFile >> numRows >> numCols;
        	
        	// 忽略行末的換行符
        	inputFile.ignore(); 

        	//	分配一個充足的迷宮數據空間 
        	mazeData.resize(100, vector<char>(100));
        	
        	// 	讀取輸入文件中的字符數據，並將其建構成一個二維字符向量，以表示迷宮的布局。
        	for (int i = 0; i < numCols; i++) {
            	string line;
            	getline(inputFile, line);
            	for (int j = 0; j < numRows; j++) {
                	mazeData[i][j] = line[j];
            	}
        	}
        	inputFile.close();
        	return true;
    	}	
    	
    	//	找尋目標(G) 
    	bool findGoals(int x, int y, int way, Maze &vMaze){
		
    		if(mazeData[x][y]=='G'){
    			return true;
			} 
			//	嘗試4個方向 
			for(int i=0;i<4;i++){	
				//	判斷該位子右下左上可行的路徑 
				//	以way為方向變數,右下左上依序為0,1,2,3 
				if(way==0){
					//	檢查是否超出迷宮
					//	下一個位子是否為'O'或'V' 
					if( (y+1) >= numRows || mazeData[x][y+1]=='O' || vMaze.Getmaze(x,y+1)=='V'){
						way=1;
					}
					else{
						mazeData[x][y]='R';
						vMaze.Setmaze('V',x,y);
						
						//	遞迴繼續往同一方向前進 
						return findGoals(x,y+1,0,vMaze);
					} 
				}
				else if(way==1){
					if( (x+1) >= numCols || mazeData[x+1][y]=='O' ||  vMaze.Getmaze(x+1,y)=='V'){
						way=2;
					}
					else{
						mazeData[x][y]='R';
						vMaze.Setmaze('V',x,y);
						return findGoals(x+1,y,1,vMaze);
					} 
				}
				else if(way==2){
					if( (y-1) < 0 || mazeData[x][y-1]=='O' ||  vMaze.Getmaze(x,y-1)=='V'){
						way=3;
					}
					else{
						mazeData[x][y]='R';
						vMaze.Setmaze('V',x,y);
						return findGoals(x,y-1,2,vMaze);
					} 
				}
				else if(way==3){
					if( (x-1) < 0  || mazeData[x-1][y]=='O' ||  vMaze.Getmaze(x-1,y)=='V'){
						way=0;
					}
					else{
						mazeData[x][y]='R';
						vMaze.Setmaze('V',x,y);
						return findGoals(x-1,y,3,vMaze);
					} 	
				}
			}
		}
		//	輸出矩陣 
    	void show() 
		{
        	for (int i = 0; i < numCols; i++)	//i負責打印直行 
			{	
            	for (int j = 0; j < numRows; j++) 	//j負責打印橫列 
				{	
                	cout << mazeData[i][j];
            	}
            	cout << endl;
        	}
    	}
    	
    	//	用於更改該位子迷宮的字符 
    	void Setmaze(char A,int x, int y) {
    		mazeData[x][y] = A ;
		}
		
		//	用於獲取該位子迷宮的字符 
		char Getmaze(int x,int y) {
			return mazeData[x][y] ;
		}
		
		//清空迷宮數據 
		void clr() {
			vector <vector<char> >().swap(mazeData) ;
		}


	private:
    	int numRows;
    	int numCols;
    	
    	//	宣告二維矩陣 
    	vector<vector<char> > mazeData;
};

enum Modes
{
    oneG,moreG
};

int main(void) 
{
    Maze aMaze;
    Modes mode = oneG;
    string fileNumber;
    int command = 0;
    
    
    //	do-while允許多次輸入命令,直到輸入為0才出去  
    do
	{
    	cout<<endl<<"***Path Finding***";
    	cout<<endl<<"***0. Quit        *";
    	cout<<endl<<"***1. One goal    *";
    	cout<<endl<<"***2. More goal   *";
    	cout<<endl<<"*****************";
    	cout<<endl<<"Input a command(0, 1, 2):";
    	cin>>command;
    	if((command==1)||(command==2))
    	{
        	if(command==2)
        	{ 
        		mode = moreG;
        	} 
        	
        	//	輸入檔案代碼 
    		cout << "Input a file number: ";
    		cin >> fileNumber;

			//載入檔案 
    		if (aMaze.load(fileNumber)) 
			{
				//複製一個相同的迷宮 
				Maze vMaze(aMaze);
				
				//判斷是否有找到目標(G)的路徑 
				bool whetherSuccess = (aMaze.findGoals(0,0,0,vMaze));
					
				mode = oneG;
				vMaze.show();
				if(whetherSuccess)
				{
					cout << endl;
        			aMaze.show();
        		}
        		vMaze.clr();
    		}
    		aMaze.clr();
    	}
		else if(!command) 
			break;
		else
			cout<<endl<<"Command does not exist"<<endl;
	}while(true);
	
	//	查看程式執行結果,在手動關閉窗口 
	system("pause");
    return 0;
}

