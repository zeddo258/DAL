//資工二乙 10911110 江侑倫

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//迷宮
class MAZE{
	public:
		int row,col,n;  //長，寬，目標數量
		char mode;     //輸入指令
        string fileName,inputName;      //  檔案名稱，輸入檔案編號
        string *aMaze;       //迷宮地圖


    //從檔案讀取迷宮
    int loadMaze() {
            fileName = "input"+inputName+".txt";
            ifstream in;
            string buffer;
            in.open(fileName);
            if(in.fail()){      //讀檔失敗
                cout<<endl<<fileName<<" does not exist!";
                return 0;
            }
            else{               //讀檔正常
                in>>col>>row;   //讀取長寬

                aMaze=new string[row];      //動態宣告
                for(int i=0;i<row;i++){     //讀取迷宮
                    in>>aMaze[i];
                    }
            }
            in.close();
            return 1;
		}
    //走迷宮
    int GO(int x,int y,int dir){

            if(aMaze[x][y]=='G'){      //碰到目標
                n--;
                if(n==0) {      //找齊所需目標，印出地圖
                        for(int i=0;i<row;i++){
                            cout<<aMaze[i]<<endl;
                        }
                        cout<<endl;
                    return n;
                }
            }
            else if(aMaze[x][y]=='E') aMaze[x][y]='V';      //遇到空格前進

            //判斷前方是否為障礙物或是目標
            for(int i=0;i<3&&n>0;i++){
                if(n>0&&x+dx[dir]<row&&x+dx[dir]>=0&&y+dy[dir]<col&&y+dy[dir]>=0&&
                   (aMaze[x+dx[dir]][y+dy[dir]]=='E'||aMaze[x+dx[dir]][y+dy[dir]]=='G')
                )
                {
                    GO(x+dx[dir],y+dy[dir],dir);
                }
                if(i==1) dir++;     //轉向
                dir=(dir+1)%4;
            }
            //找齊所需目標，標記路線
            if(n==0)	aMaze[x][y]='R';

            return n;

        }
    private:
        //預設方向，右下左上
        const int dx[4]={0,1,0,-1};
        const int dy[4]={1,0,-1,0};

};
int main(){

	MAZE Maze;  //新增迷宮

	while(1){
		cout<<"\n*** Path Finding ***\n* 0. Quit          *\n* 1. One goal      *\n* 2. More goals    *\n********************\n";
		cout<<("Input a command(0, 1, 2): ");
		cin>>Maze.mode;     //輸入指令

		if(Maze.mode=='1'||Maze.mode=='2'){
			cout<<("\nInput a file number: ");
			cin>>Maze.inputName;    //輸入檔案編號
            if(Maze.mode=='2'){       //當指令為2，輸入目標數量
                cout<<"\nNumber of G (goals): ";
                cin>>Maze.n;
            }else Maze.n=1;         //當指令為1，預設目標數量為1
            Maze.aMaze=nullptr;
            if(Maze.loadMaze()){    //從檔案讀取迷宮
            Maze.n=Maze.GO(0,0,0);  //走迷宮，起始位置(0.0)，方向向右

            if(Maze.n==0){          //找齊目標，並輸出地圖
                for(int i=0;i<Maze.row;i++){
					for(int j=0;j<Maze.col;j++){
						if(Maze.aMaze[i][j]=='V') Maze.aMaze[i][j]='E';
					}
					cout<<Maze.aMaze[i]<<endl;
				}
            }
            else if(Maze.n>0){      //沒有找齊目標，輸出路徑
                for(int i=0;i<Maze.row;i++){
                    cout<<Maze.aMaze[i]<<endl;
                }
            }
            delete []Maze.aMaze;    //釋放記憶體
            }

        }else if(Maze.mode=='0')    return 0;     //指令為0，終止程式
        else    cout<<"\nCommand does not exist!";  //指令錯誤

        cout<<endl;
    }

    return 0;
}
