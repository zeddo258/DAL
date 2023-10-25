//��u�G�A 10911110 ���ݭ�

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//�g�c
class MAZE{
	public:
		int row,col,n;  //���A�e�A�ؼмƶq
		char mode;     //��J���O
        string fileName,inputName;      //  �ɮצW�١A��J�ɮ׽s��
        string *aMaze;       //�g�c�a��


    //�q�ɮ�Ū���g�c
    int loadMaze() {
            fileName = "input"+inputName+".txt";
            ifstream in;
            string buffer;
            in.open(fileName);
            if(in.fail()){      //Ū�ɥ���
                cout<<endl<<fileName<<" does not exist!";
                return 0;
            }
            else{               //Ū�ɥ��`
                in>>col>>row;   //Ū�����e

                aMaze=new string[row];      //�ʺA�ŧi
                for(int i=0;i<row;i++){     //Ū���g�c
                    in>>aMaze[i];
                    }
            }
            in.close();
            return 1;
		}
    //���g�c
    int GO(int x,int y,int dir){

            if(aMaze[x][y]=='G'){      //�I��ؼ�
                n--;
                if(n==0) {      //����һݥؼСA�L�X�a��
                        for(int i=0;i<row;i++){
                            cout<<aMaze[i]<<endl;
                        }
                        cout<<endl;
                    return n;
                }
            }
            else if(aMaze[x][y]=='E') aMaze[x][y]='V';      //�J��Ů�e�i

            //�P�_�e��O�_����ê���άO�ؼ�
            for(int i=0;i<3&&n>0;i++){
                if(n>0&&x+dx[dir]<row&&x+dx[dir]>=0&&y+dy[dir]<col&&y+dy[dir]>=0&&
                   (aMaze[x+dx[dir]][y+dy[dir]]=='E'||aMaze[x+dx[dir]][y+dy[dir]]=='G')
                )
                {
                    GO(x+dx[dir],y+dy[dir],dir);
                }
                if(i==1) dir++;     //��V
                dir=(dir+1)%4;
            }
            //����һݥؼСA�аO���u
            if(n==0)	aMaze[x][y]='R';

            return n;

        }
    private:
        //�w�]��V�A�k�U���W
        const int dx[4]={0,1,0,-1};
        const int dy[4]={1,0,-1,0};

};
int main(){

	MAZE Maze;  //�s�W�g�c

	while(1){
		cout<<"\n*** Path Finding ***\n* 0. Quit          *\n* 1. One goal      *\n* 2. More goals    *\n********************\n";
		cout<<("Input a command(0, 1, 2): ");
		cin>>Maze.mode;     //��J���O

		if(Maze.mode=='1'||Maze.mode=='2'){
			cout<<("\nInput a file number: ");
			cin>>Maze.inputName;    //��J�ɮ׽s��
            if(Maze.mode=='2'){       //����O��2�A��J�ؼмƶq
                cout<<"\nNumber of G (goals): ";
                cin>>Maze.n;
            }else Maze.n=1;         //����O��1�A�w�]�ؼмƶq��1
            Maze.aMaze=nullptr;
            if(Maze.loadMaze()){    //�q�ɮ�Ū���g�c
            Maze.n=Maze.GO(0,0,0);  //���g�c�A�_�l��m(0.0)�A��V�V�k

            if(Maze.n==0){          //����ؼСA�ÿ�X�a��
                for(int i=0;i<Maze.row;i++){
					for(int j=0;j<Maze.col;j++){
						if(Maze.aMaze[i][j]=='V') Maze.aMaze[i][j]='E';
					}
					cout<<Maze.aMaze[i]<<endl;
				}
            }
            else if(Maze.n>0){      //�S������ؼСA��X���|
                for(int i=0;i<Maze.row;i++){
                    cout<<Maze.aMaze[i]<<endl;
                }
            }
            delete []Maze.aMaze;    //����O����
            }

        }else if(Maze.mode=='0')    return 0;     //���O��0�A�פ�{��
        else    cout<<"\nCommand does not exist!";  //���O���~

        cout<<endl;
    }

    return 0;
}
