// �q��T 11020116 ��q�s 
// ���ϥ�C++11 

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <string>
#include <deque>
#include <string.h>
using namespace std;

void GetCommand( int &command ) { // �L�X�ϥΤ�����Ū�J���O�H�γB�z���O�X�������p 
    printf("\n"); 
	printf("*** Path Finding ***\n");
	printf("* 0. Quit          *\n");	
	printf("* 1. One Goal      *\n");
	printf("* 2. More Goals    *\n");
	printf("* 3. Shortest Path *\n");
	printf("********************\n");
	printf("Input a command(0, 1, 2, 3): ");
	scanf("%d", &command);
	
	if(command!=0 && command!=1 && command!=2 && command !=3){ //���O�X���A���s��J 
		printf("Command does not exist!\n");
		GetCommand(command);
	}
	else
	  return;	
}
void Inputtxt(ifstream &inputFile, int &x, int &y) //�ϥ�ifstream�ɪ�Ū�J�ɮ� for mission2.3
{
    string targetname;
    cout << "input a file number:";
    cin >> targetname;
    targetname = "input" + targetname + ".txt";
    inputFile.open(targetname);
    while (!inputFile) {
        cout<< targetname << "does not exist!\n"; 
        cout << "input a file number:";
        cin >> targetname;
        targetname = "input" + targetname + ".txt";
        inputFile.open(targetname);
    } 
	
    inputFile >> x >> y;
    
}
void FILEInputtxt(FILE *&fp, int&x, int&y){ // �ϥ�FILE�ɪ�Ū�J�ɮ�for mission1 
	char input[10];
	cout<<"input a file number:";
	cin >> input;
	strcat(input, ".txt");
	char targetname[50] = "input" ;
	strcat(targetname, input);			
	fp = fopen( targetname, "r");	
	fscanf(fp, "%d", &x);
			
	while (fp == NULL){
		fclose(fp);
		cout<< targetname << "does not exist!\n";
		cout<<"input a file number\n";
		cin >> input;
		strcat(input, ".txt");
		strcpy(targetname, "input") ;
		strcat(targetname, input);			
		fp = fopen( targetname, "r");	
		fscanf(fp, "%d", &x);
	}
	fscanf(fp, "%d\n", &y);
	
}
class OldMaze { //�ίx�}�覡�إ߰g�c�x�}�A���H���X����2.3�A�u�Φb����1 
    int curx ;
	int cury ;
	int direction ; // 1=�k 2=�U 3=�� 4=�W 
	char fieldtype ;
	bool visted;
	bool goalfound;
	public:
		void Initialmaze (char); //��l��maze 
		void Printmaze();  //�L�Xmaze 
		char Getfieldtype();  // �N�Ӯ檺������X 
		int  Checkdirection(); // return ��e��V(1:�k 2:�U 3:�� 4:�W) 
		void Changedirection();// ���Ӷ��Ǵ���V 
		bool Checkgoaled(); // return �O�_�w�g��F�L���I 
		void Savecurrentmaze(int, int); // �s�U��U����m 
		void Forward(); // �V���w��V���� 
		void Changefieldtype(char); //�ܧ�Ӯ����� 

};


bool OldMaze::Checkgoaled(){
	if(goalfound == true){
		return true;
	} 
	else
	  return false;
} 
void OldMaze::Initialmaze(char c){
    curx = 0;
	cury = 0;
	direction = 1;
	fieldtype = c;
	goalfound = false;
	visted = false;

}


void OldMaze::Printmaze(){
    printf("%c", fieldtype);
}

char OldMaze::Getfieldtype(){
    return fieldtype;
}

void OldMaze::Changefieldtype( char c){
	fieldtype = c; 
}



void OldMaze::Savecurrentmaze(int x, int y){
    curx = x;
    cury = y;
}

int OldMaze::Checkdirection(){
    return direction;
}
void OldMaze::Changedirection(){
	if (direction == 1 ){
		direction = 2;
		return;
	}
	if (direction == 2 ){
		direction = 3;
		return;
	}
	if (direction == 3 ){
		direction = 4;
		return;
	}

	if (direction == 4 ){
		direction = 1;
		return;
	}
	
}

void OldMaze::Forward(){
	if(fieldtype == 'E'){
	  visted = true;
  	  fieldtype = 'V';
	}
	else if(fieldtype == 'G'){
		visted = true;
		goalfound = true;
	}
	else{
		visted = true;
	}
		
}







class Block // �ΨӥN��C�@"��"�g�c����� 
{
    char fieldtype;
    bool visited;
    bool route;
    public:
        Block( char type='E' ){
        	fieldtype = type;
        	visited = false;
        	route = false;
		}
        char getfieldtype()
		{ return fieldtype;}
        bool isvisited() 
		{ return visited; }
        void setvisited() 
		{ visited = true; }

        void setroute() { route = true; }
        bool isroute() { return route; }
};




class Maze //�ϥΫ��Ыإ߾�Ӱg�c 
{
    Block **maze;
    int width, height;
    public:
        Maze(int x, int y){ //�إ�x*y�����Яx�} 
        	width = x;
        	height = y;
            maze = new Block *[y];
            for(int i = 0; i < y; i++) maze[i] = new Block [x];
        }
    void setBlock(int x, int y, char type) { maze[x][y] = Block(type); } //�]�w�Ӯ檺block
    Block& getBlock(int x, int y) { return maze[y][x]; }  //���V�Ӯy�Ю檺���� 
    void printMaze(bool visitedOnly = false); // �L�X�g�c 
    bool findMultiPath(int x, int y, int &remainingGoals, int dir = 0); //���ȤG 
};





void Maze::printMaze(bool tragetunfound)
{
    cout << "\n";
    for(int i=0; i<height; i++) { //���LV�� 
        for(int j=0; j<width; j++) {

            
            if(maze[i][j].getfieldtype() == 'G') {cout << 'G'; }
            else if(maze[i][j].isvisited()) {cout << 'V'; }
            else if (maze[i][j].getfieldtype() == 'O') cout << 'O' ;
			else	 cout << 'E';
        }
        cout << "\n";
    }

    if(tragetunfound) return; //�p�G�S�����I �N�u�L�o�� 

    cout <<  "\n";

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            if(maze[i][j].getfieldtype() == 'G') {cout << 'G'; continue;}
            else if(maze[i][j].isroute()) {cout << 'R'; continue;}
            else if (maze[i][j].getfieldtype() == 'O') cout << 'O' ;
			else	 cout << 'E';
        }
        cout << "\n";
    }
}

int main()
{
	int order = -1; // �]�w��l�� 
	int x = 0;
	int y = 0;
	char temp ;
	int check = 0;
	int targetcount = 0;
    int command;
    GetCommand(command);
    while(command!=0){	 
        //ifstream inputFile;
        //Maze* maze; //�إ߰g�cpointer 
		if(command==1 ){
			FILE *fp = NULL;  
			FILEInputtxt(fp,x,y); //Ū�Jtxt������� 
			targetcount = 1;
			cout << x << " * " << y << "\n"; // �L�X�x�}�W��
			int i = 0, j = 0;
			OldMaze maze[x+1][y]; // x+1�]�t���� 
			for(char c=getc(fp) ; c!= EOF && i < x+1 && j < y; c=getc(fp)){
				maze[i][j].Initialmaze(c);  
				//maze[i][j].Printmaze();   		
				if(i == x){
					j ++;
					i = 0;
				}
				else
					i++ ;	      			 
			} // �إ߰g�c�x�}
			fclose(fp); // �Χ��ɮ� ���� 
			
			i = 0;
			j = 0;
			int count = 0;

			while(targetcount>0 ){  //�b�����I�e������ 
              if(maze[0][0].Checkdirection()==1){ // �V�k 
                temp = maze[i+1][j].Getfieldtype();
                
                if(temp == 'O' || temp =='V' || i+1 >= x ){ //�J���ê�ζW�L�d��N����V 

                	maze[0][0].Changedirection();             	
				}
				else if(temp == 'E'|| temp =='G'){
					i++; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			
				
			  }
              else if(maze[0][0].Checkdirection()==2){ //�V�U 
                temp = maze[i][j+1].Getfieldtype();


                
                if(temp == 'O' || temp =='V' || j+1 >= y ){ //�J���ê�ζW�L�d��N����V  
                	maze[0][0].Changedirection();            	
				}
				else if(temp == 'E'|| temp =='G'){
					j++; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			  }
              else if(maze[0][0].Checkdirection()==3){ //�V��
                temp = maze[i-1][j].Getfieldtype();

                
                if(temp == 'O' ||  i-1 <0 ){ //�J���ê�ζW�L�d��N����V 
                	maze[0][0].Changedirection();
                	
				}
				else if(temp == 'E'|| temp =='G' || temp =='V'){  
					i--; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			  }
              else if(maze[0][0].Checkdirection()==4){ //�V�W
                temp = maze[i][j-1].Getfieldtype();
                
                if(temp == 'O' || temp =='V'|| j-1<0){//�J���ê�ζW�L�d��N����V 
                	maze[0][0].Changedirection();                 	
				}
				else if(temp == 'E'|| temp =='G' || temp =='V'){  
					j--; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			  }

				if(maze[i][j].Checkgoaled() == true){ //�p�G�w�g���ؼСA�h�ǳƲ����j�� 
				  targetcount--;

				}
			}
			
			if(targetcount>0){ //�p�G�S�����I�N�u�LV�� 
				maze[0][0].Changefieldtype('V');
				for (int temp1 = 0, temp2 = 0; temp1 <x+1, temp2<y ; ){ 				
					maze[temp1][temp2].Printmaze(); 	
					if(temp1 == x){
						temp1 = 0;
						temp2++;
					}
					else
						temp1++;
				}
				cout << "\n"; 
				
			}		  
			else{ // �p�G���N�LR�MV�� 
				maze[0][0].Changefieldtype('V');
				for (int temp1 = 0, temp2 = 0; temp1 <x+1, temp2<y ; ){ 				
					maze[temp1][temp2].Printmaze(); 	
					if(temp1 == x){
						temp1 = 0;
						temp2++;
					}
					else
						temp1++;
				}			
				cout << "\n";				
				maze[0][0].Changefieldtype('R');
				for (int temp1 = 0, temp2 = 0; temp1 <x+1, temp2<y ; ){ 
					if(maze[temp1][temp2].Getfieldtype()=='V'){
						maze[temp1][temp2].Changefieldtype('R');
					}
					maze[temp1][temp2].Printmaze(); 	
					if(temp1 == x){
						temp1 = 0;
						temp2++;
					}
					else
						temp1++;
				}
				cout << "\n";
			}

			 
			
		
		}


        else if( command == 2){ // �����X�� 
                cout << "�S���X��\n";
		} 
        else if( command == 3){ // �����X�� 
                cout << "�S���X��\n";
    	}
		command = -1;
		GetCommand(command); 

            
        
	}

    return 0;
}
