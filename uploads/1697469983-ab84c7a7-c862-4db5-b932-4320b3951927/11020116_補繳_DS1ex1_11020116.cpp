// 電資三 11020116 潘皓群 
// 有使用C++11 

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <string>
#include <deque>
#include <string.h>
using namespace std;

void GetCommand( int &command ) { // 印出使用介面並讀入指令以及處理指令出錯的情況 
    printf("\n"); 
	printf("*** Path Finding ***\n");
	printf("* 0. Quit          *\n");	
	printf("* 1. One Goal      *\n");
	printf("* 2. More Goals    *\n");
	printf("* 3. Shortest Path *\n");
	printf("********************\n");
	printf("Input a command(0, 1, 2, 3): ");
	scanf("%d", &command);
	
	if(command!=0 && command!=1 && command!=2 && command !=3){ //指令出錯，重新輸入 
		printf("Command does not exist!\n");
		GetCommand(command);
	}
	else
	  return;	
}
void Inputtxt(ifstream &inputFile, int &x, int &y) //使用ifstream時的讀入檔案 for mission2.3
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
void FILEInputtxt(FILE *&fp, int&x, int&y){ // 使用FILE時的讀入檔案for mission1 
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
class OldMaze { //用矩陣方式建立迷宮矩陣，難以做出任務2.3，只用在任務1 
    int curx ;
	int cury ;
	int direction ; // 1=右 2=下 3=左 4=上 
	char fieldtype ;
	bool visted;
	bool goalfound;
	public:
		void Initialmaze (char); //初始化maze 
		void Printmaze();  //印出maze 
		char Getfieldtype();  // 將該格的類型輸出 
		int  Checkdirection(); // return 當前方向(1:右 2:下 3:左 4:上) 
		void Changedirection();// 按照順序換方向 
		bool Checkgoaled(); // return 是否已經到達過終點 
		void Savecurrentmaze(int, int); // 存下當下的位置 
		void Forward(); // 向指定方向移動 
		void Changefieldtype(char); //變更該格類型 

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







class Block // 用來代表每一"格"迷宮的資料 
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




class Maze //使用指標建立整個迷宮 
{
    Block **maze;
    int width, height;
    public:
        Maze(int x, int y){ //建立x*y的指標矩陣 
        	width = x;
        	height = y;
            maze = new Block *[y];
            for(int i = 0; i < y; i++) maze[i] = new Block [x];
        }
    void setBlock(int x, int y, char type) { maze[x][y] = Block(type); } //設定該格的block
    Block& getBlock(int x, int y) { return maze[y][x]; }  //指向該座標格的類型 
    void printMaze(bool visitedOnly = false); // 印出迷宮 
    bool findMultiPath(int x, int y, int &remainingGoals, int dir = 0); //任務二 
};





void Maze::printMaze(bool tragetunfound)
{
    cout << "\n";
    for(int i=0; i<height; i++) { //先印V圖 
        for(int j=0; j<width; j++) {

            
            if(maze[i][j].getfieldtype() == 'G') {cout << 'G'; }
            else if(maze[i][j].isvisited()) {cout << 'V'; }
            else if (maze[i][j].getfieldtype() == 'O') cout << 'O' ;
			else	 cout << 'E';
        }
        cout << "\n";
    }

    if(tragetunfound) return; //如果沒找到終點 就只印這樣 

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
	int order = -1; // 設定初始值 
	int x = 0;
	int y = 0;
	char temp ;
	int check = 0;
	int targetcount = 0;
    int command;
    GetCommand(command);
    while(command!=0){	 
        //ifstream inputFile;
        //Maze* maze; //建立迷宮pointer 
		if(command==1 ){
			FILE *fp = NULL;  
			FILEInputtxt(fp,x,y); //讀入txt內的資料 
			targetcount = 1;
			cout << x << " * " << y << "\n"; // 印出矩陣規模
			int i = 0, j = 0;
			OldMaze maze[x+1][y]; // x+1包含換行 
			for(char c=getc(fp) ; c!= EOF && i < x+1 && j < y; c=getc(fp)){
				maze[i][j].Initialmaze(c);  
				//maze[i][j].Printmaze();   		
				if(i == x){
					j ++;
					i = 0;
				}
				else
					i++ ;	      			 
			} // 建立迷宮矩陣
			fclose(fp); // 用完檔案 關閉 
			
			i = 0;
			j = 0;
			int count = 0;

			while(targetcount>0 ){  //在找到終點前不停止 
              if(maze[0][0].Checkdirection()==1){ // 向右 
                temp = maze[i+1][j].Getfieldtype();
                
                if(temp == 'O' || temp =='V' || i+1 >= x ){ //遇到阻礙或超過範圍就換方向 

                	maze[0][0].Changedirection();             	
				}
				else if(temp == 'E'|| temp =='G'){
					i++; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			
				
			  }
              else if(maze[0][0].Checkdirection()==2){ //向下 
                temp = maze[i][j+1].Getfieldtype();


                
                if(temp == 'O' || temp =='V' || j+1 >= y ){ //遇到阻礙或超過範圍就換方向  
                	maze[0][0].Changedirection();            	
				}
				else if(temp == 'E'|| temp =='G'){
					j++; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			  }
              else if(maze[0][0].Checkdirection()==3){ //向左
                temp = maze[i-1][j].Getfieldtype();

                
                if(temp == 'O' ||  i-1 <0 ){ //遇到阻礙或超過範圍就換方向 
                	maze[0][0].Changedirection();
                	
				}
				else if(temp == 'E'|| temp =='G' || temp =='V'){  
					i--; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			  }
              else if(maze[0][0].Checkdirection()==4){ //向上
                temp = maze[i][j-1].Getfieldtype();
                
                if(temp == 'O' || temp =='V'|| j-1<0){//遇到阻礙或超過範圍就換方向 
                	maze[0][0].Changedirection();                 	
				}
				else if(temp == 'E'|| temp =='G' || temp =='V'){  
					j--; 
					maze[i][j].Forward();
					maze[0][0].Savecurrentmaze(i,j);					
			
				}
			  }

				if(maze[i][j].Checkgoaled() == true){ //如果已經找到目標，則準備脫離迴圈 
				  targetcount--;

				}
			}
			
			if(targetcount>0){ //如果沒找到終點就只印V圖 
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
			else{ // 如果找到就印R和V圖 
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


        else if( command == 2){ // 做不出來 
                cout << "沒做出來\n";
		} 
        else if( command == 3){ // 做不出來 
                cout << "沒做出來\n";
    	}
		command = -1;
		GetCommand(command); 

            
        
	}

    return 0;
}
