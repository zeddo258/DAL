//DS1ex1_11120406 �®f��
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
        	numRows = 0;	//	���� 
        	numCols = 0;	//	��C 
    	}

    	bool load(const string& fileNumber){
    		
        	// �غc�ɮצW�� 
        	string filename = "input" + fileNumber + ".txt";
        	ifstream inputFile(filename.c_str());

        	if (!inputFile) {
            	cerr << "�L�k�k���}���" << endl;
            	return false;
        	}

        	// Ū����C�� 
        	inputFile >> numRows >> numCols;
        	
        	// �����楽�������
        	inputFile.ignore(); 

        	//	���t�@�ӥR�����g�c�ƾڪŶ� 
        	mazeData.resize(100, vector<char>(100));
        	
        	// 	Ū����J��󤤪��r�żƾڡA�ñN��غc���@�ӤG���r�ŦV�q�A�H��ܰg�c�������C
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
    	
    	//	��M�ؼ�(G) 
    	bool findGoals(int x, int y, int way, Maze &vMaze){
		
    		if(mazeData[x][y]=='G'){
    			return true;
			} 
			//	����4�Ӥ�V 
			for(int i=0;i<4;i++){	
				//	�P�_�Ӧ�l�k�U���W�i�檺���| 
				//	�Hway����V�ܼ�,�k�U���W�̧Ǭ�0,1,2,3 
				if(way==0){
					//	�ˬd�O�_�W�X�g�c
					//	�U�@�Ӧ�l�O�_��'O'��'V' 
					if( (y+1) >= numRows || mazeData[x][y+1]=='O' || vMaze.Getmaze(x,y+1)=='V'){
						way=1;
					}
					else{
						mazeData[x][y]='R';
						vMaze.Setmaze('V',x,y);
						
						//	���j�~�򩹦P�@��V�e�i 
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
		//	��X�x�} 
    	void show() 
		{
        	for (int i = 0; i < numCols; i++)	//i�t�d���L���� 
			{	
            	for (int j = 0; j < numRows; j++) 	//j�t�d���L��C 
				{	
                	cout << mazeData[i][j];
            	}
            	cout << endl;
        	}
    	}
    	
    	//	�Ω���Ӧ�l�g�c���r�� 
    	void Setmaze(char A,int x, int y) {
    		mazeData[x][y] = A ;
		}
		
		//	�Ω�����Ӧ�l�g�c���r�� 
		char Getmaze(int x,int y) {
			return mazeData[x][y] ;
		}
		
		//�M�Űg�c�ƾ� 
		void clr() {
			vector <vector<char> >().swap(mazeData) ;
		}


	private:
    	int numRows;
    	int numCols;
    	
    	//	�ŧi�G���x�} 
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
    
    
    //	do-while���\�h����J�R�O,�����J��0�~�X�h  
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
        	
        	//	��J�ɮץN�X 
    		cout << "Input a file number: ";
    		cin >> fileNumber;

			//���J�ɮ� 
    		if (aMaze.load(fileNumber)) 
			{
				//�ƻs�@�ӬۦP���g�c 
				Maze vMaze(aMaze);
				
				//�P�_�O�_�����ؼ�(G)�����| 
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
	
	//	�d�ݵ{�����浲�G,�b����������f 
	system("pause");
    return 0;
}

