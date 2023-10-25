//11127129張軒偉 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

class Maze{
private:
	int mazex;             //儲存迷宮x軸長度 
	int mazey;             //儲存迷宮y軸長度 
	char **mazeptr = NULL; //儲存原始迷宮陣列 
	char **vmazeptr = NULL;//儲存走過的迷宮陣列
	char **pmazeptr = NULL;//儲存成功路徑的迷宮陣列
	bool have = true;      //true表示有迷宮 
	int goals;             //儲存目標數量 
	int spath;             //儲存最短路徑長度 
	
public:
    
    //釋放動態陣列空間 
 	void Free(){
 		
    	for (int z = 0; z < mazey; z++) {
        	free(mazeptr[z]);
   		}
   		free(mazeptr);
   		
   		for (int z = 0; z < mazey; z++) {
        	free(vmazeptr[z]);
   		}
   		free(vmazeptr);
   		
   		for (int z = 0; z < mazey; z++) {
        	free(pmazeptr[z]);
   		}
   		free(pmazeptr);
   		
	}
	
	void Freep(){
   		for (int z = 0; z < mazey; z++) {
        	free(pmazeptr[z]);
   		}
   		free(pmazeptr);
	}
	
    void Setv() {
    	
    	//用x和y來設定一個二維字元陣列
    	char **maze = (char **)malloc(mazey * sizeof(char *));
    	for (int z = 0; z < mazey; z++) {
        	maze[z] = (char *)malloc(mazex+2 * sizeof(char));
   		}
   		
   		//將迷宮陣列存入private的變數 
   		vmazeptr=maze;
   		
   		//把原始迷宮的數據複製進V迷宮 
    	for (int i = 0; i < mazey; i++) {
        	for (int j = 0; j < mazex; j++) {
            	vmazeptr[i][j] = mazeptr[i][j];
            	vmazeptr[i][j+1]='\n';
        	}
        	
    	}
	}
	
	void Setp() {
    	
    	//用x和y來設定一個二維字元陣列
    	char **maze = (char **)malloc(mazey * sizeof(char *));
    	for (int z = 0; z < mazey; z++) {
        	maze[z] = (char *)malloc(mazex+2 * sizeof(char));
   		}
   		
   		//將迷宮陣列存入private的變數
   		pmazeptr=maze;
   		
   		//把原始迷宮的數據複製進R迷宮
    	for (int i = 0; i < mazey; i++) {
        	for (int j = 0; j < mazex; j++) {
            	pmazeptr[i][j] = mazeptr[i][j];
            	pmazeptr[i][j+1]='\n';
        	}
        	
    	}
	}
	
    void SetMaze(FILE *file) {
        char buffer[1000];//儲存檔案每行的內容
    	char all[1000];   //儲存檔案全部的內容 
		char temp;        //暫存字元 
		char xc[10]="";   //儲存陣列x軸長度的字串 
		char yc[10]="";   //儲存陣列y軸長度的字串  
		int x;            //儲存陣列x軸長度 
		int y;            //儲存陣列y軸長度 
		int i=3;          //整個檔案的字串從第4個開始為有效字元因此設為3
		
		//讀取每行的內容直到沒有 
		while(fgets(buffer, sizeof(buffer), file) != NULL) {
    		// 在這裡處理讀取的內容
			//將讀到的內容串接到all 
    		strcat(all,buffer);
		}
		
		//從all中讀出x的長度 
		temp=all[i];
		//讀第一個空格前的所有字元 
		int a =0;
		while(temp!=' '){
			
			xc[a]=temp;
			xc[a+1]='\0';	
			
			a++;
			i++;
			temp=all[i];	
		}
		//將字元轉數字 
		x = atoi(xc);
		
		//從all中讀出y的長度
		i++;
		temp=all[i];
		//讀第一個換行前的所有字元
		a=0;
		while(temp!='\n'){			
			yc[a]=temp;
			yc[a+1]='\0';
			a++;
			i++;
			temp=all[i];	
		}
		//將字元轉數字
		y = atoi(yc);
		
		//若是兩軸有一軸為0，have=false
		if(x<=0||y<=0){
			have=false;
		}
			
		//用x和y來設定一個二維字元陣列 
		char **maze = (char **)malloc(y * sizeof(char *));
    	for (int z = 0; z < y; z++) {
        	maze[z] = (char *)malloc(x+2 * sizeof(char));
   		}
   		
   		//將迷宮的資訊依序讀入陣列 
   		int j=0,k=0;
   		while(j<y){
   			i++;
			temp=all[i];
			k=0;
			while(temp!='\n'&&temp!='\0'){ 
				maze[j][k]=temp;
				i++;
				temp=all[i];
				k++;	
			}	
			j++;
	    }
   		
   		//將迷宮陣列和長寬存入private的變數 
   		mazex=x;
   		mazey=y;
   		mazeptr=maze; 
   		maze=NULL;
   		
   		Setv(); //呼叫Setv()設定V陣列 
   		Setp(); //呼叫Setp()設定R陣列 
   		Setspath();
    }

    //用來取得原始迷宮的函式 
    char ** GetMaze() {
     	return mazeptr;
    }
    
    //用來取得V迷宮的函式
    char ** GetvMaze() {
     	return vmazeptr;
    }
    
    //用來取得R迷宮的函式
    char ** GetpMaze() {
     	return pmazeptr;
    }
    
    //用來取得迷宮x軸的函式
    int Getx(){
    	return mazex;
	}
	
	//用來取得迷宮y軸的函式
	int Gety(){
    	return mazey;
	}
	
	//用來設定have的函式
	void Sethave(bool x){
    	have=x;
	}
	
	void Setspath(){
    	spath=mazex*mazey;
	}
    
    //用來取得have的函式
    bool Gethave(){
    	return have;
	}
	
	//用來設定goals的函式
	void Setgoals(int x){
		goals=x;
	}
	
    int Getpath(){
    	return spath;
	}
	
    bool OneGo(int x, int y,int direction) {
		// 定義方向（右下左上）
		int dx[] = {0, 1, 0, -1};
		int dy[] = {1, 0, -1, 0};
		
    	// 如果目前位置是目標，返回true
    	if (mazeptr[x][y]=='G') {
        	return true;
    	}
		
   		// 設定目前位置為已走過 
    	vmazeptr[x][y] = 'V';
		
		//繼續嘗試目前的方向 
		if(direction >=0 &&direction <=3){
			//將x,y以目前方向往前一格 
			int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// 檢查新位置是否在迷宮範圍內，且是一個未訪問過且能走的的點
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V') {
            	// 遞迴搜索新位置
            	if (OneGo(newx, newy,direction)) {
           	     	// 如果找到一條通往出口的路徑，返回true
           	     	// 並將此路徑在R陣列標上R 
           		   	pmazeptr[x][y] = 'R';
            	   	return true;
         		}
       	 	}
       	 	//若此方向走不到目標則將方向轉向下一個方向 
       	 	direction=direction+1;
			
		}
		
    	// 嘗試剩餘三個可能的方向
    	for (int i = 0; i < 3; i++) {
    		//方向>3就將方向歸零 
    		if(direction>3){
    			direction=0;
			}
			//將x,y以目前方向往前一格 
        	int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// 檢查新位置是否在迷宮範圍內，且是一個未訪問過且能走的點
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V') {
            	// 遞迴搜索新位置
            	if (OneGo(newx, newy,direction)) {
           	   		// 如果找到一條通往出口的路徑，返回true
           	   		// 並將此路徑在R陣列標上R 
           	     	pmazeptr[x][y] = 'R';
                	return true;
         		}
       	 	}
       	 	//若此方向走不到目標則將方向轉向下一個方向
       	 	direction=direction+1;
    	}

		
    	// 如果所有方向都無法找到路徑，返回false
    	return false;
	}
	
	bool MoreGo(int x, int y,int direction) {
		// 定義方向（右下左上）
		int dx[] = {0, 1, 0, -1};
		int dy[] = {1, 0, -1, 0};
		
		//若是目標已經找完，返回true 
		if(goals==0){
    		return true;
		}
    	
		
   		// 設定目前位置(不能是G)為已走過
		if(vmazeptr[x][y]!='G'){
			vmazeptr[x][y] = 'V';
		} 
    	
    	//繼續嘗試目前的方向
    	if(direction >=0 &&direction <=3){
    		//將x,y以目前方向往前一格
			int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// 檢查新位置是否在迷宮範圍內，且是一個未訪問過且能走又不能是已走過的目標的點
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V'&&
				mazeptr[newx][newy] != 'T') {
				
				//若走到目標則將目標設為T(TAKE)，且 goals-1
				if (mazeptr[newx][newy]=='G') {
    				mazeptr[newx][newy]='T';
    				goals=goals-1;
    			}
            	// 遞迴搜索新位置
            	if (MoreGo(newx, newy,direction)) {
                	// 如果找到一條路徑，返回true
                	// 並將此路徑(目標位置不標)在R陣列標上R 
                	if(mazeptr[x][y] != 'T'&&mazeptr[x][y] != 'G'){
                		pmazeptr[x][y] = 'R';
					}
					
					return true;
         		}
         		//將goals!=0但有找到目標路徑(目標位置不標)在R陣列標上R 
         		else if(pmazeptr[newx][newy]=='G'||pmazeptr[newx][newy]=='R'&&
				        pmazeptr[x][y]!='G'){
         			pmazeptr[x][y] = 'R';
				}
       	 	}
       	 	//若此方向走不到目標則將方向轉向下一個方向
       	 	direction=direction+1;	
			
		}
		
    	// 嘗試剩餘三個可能的方向
    	for (int i = 0; i < 3; i++) {
    		//方向>3就將方向歸零
    		if(direction>3){
    			direction=0;
			}
			//將x,y以目前方向往前一格
        	int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// 檢查新位置是否在迷宮範圍內，且是一個未訪問過且能走又不能是已走過的目標的點
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' && vmazeptr[newx][newy]!='V'&&
				mazeptr[newx][newy] != 'T') {
            		
            	//若走到目標則將目標設為T(TAKE)，且 goals-1
            	if (mazeptr[newx][newy]=='G') {
    				mazeptr[newx][newy]='T';
    				goals=goals-1;
    			}
    			
            	// 遞迴搜索新位置
            	if (MoreGo(newx, newy,direction)) {
                	// 如果找到一條路徑，返回true
                	// 並將此路徑(目標位置不標)在R陣列標上R 
                	if(mazeptr[x][y] != 'T'&&mazeptr[x][y] != 'G'){
                		pmazeptr[x][y] = 'R';
					}
					
					return true;
         		}
         		//將goals!=0但有找到目標路徑(目標位置不標)在R陣列標上R
         		else if(pmazeptr[newx][newy]=='G'||pmazeptr[newx][newy]=='R'&&
				        pmazeptr[x][y]!='G'){
         			pmazeptr[x][y] = 'R';
				}
       	 	}
       	 	//若此方向走不到目標則將方向轉向下一個方向
       	 	direction=direction+1;
    	}
		
    	// 如果所有方向都無法找到路徑，返回false
    	return false;
	}
	
	int ShortGo(int x, int y,int direction,int path) {
		int od=direction;           //存原方向 
		int temp=0;                 //暫時回傳值 
		int result=spath+1;         //最終回傳值  
		
		//路徑+1，若長度已比最短相同則直接返回 
		path = path+1;
		if(path>=spath){
			return -1; 
		}
		// 定義方向（右下左上）
		int dx[] = {0, 1, 0, -1};
		int dy[] = {1, 0, -1, 0};
		//計算上一個的座標 
		int ox = x-dx[od];
		int oy = y-dy[od];
		
    	// 如果目前位置是目標，返回path
    	if (mazeptr[x][y]=='G') {
    		//比最短還短才返回 
    		if(path<spath){
    			// 將R圖reset 
    			Freep();
    			Setp();
    			//將最短設為現在的長度 
    			spath=path;
    			return path;
			}
			//有目標但不是最短返回-1 
        	return -1;
    	}
		
   		// 設定目前位置為已走過 ，除了G 
    	if(vmazeptr[x][y]!='G'){
			vmazeptr[x][y] = 'V';
		} 
		
		//繼續嘗試目前的方向 
		if(direction >=0 &&direction <=3){
			//將x,y以目前方向往前一格 
			int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// 檢查新位置是否在迷宮範圍內，且是一個未訪問過且能走的的點
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' ) {
            	// 遞迴搜索新位置
            	temp=ShortGo(newx, newy,direction,path);
            	//若回傳=目前最短且不為-1，設結果為回傳值 
            	if (temp==spath&&temp!=-1) {
                	result=temp;
         		}
         		
       	 	}
       	 	//若此方向走不到目標則將方向轉向下一個方向 
       	 	direction=direction+1;
			
		}
		
    	// 嘗試剩餘三個可能的方向
    	for (int i = 0; i < 3; i++) {
    		//方向>3就將方向歸零 
    		if(direction>3){
    			direction=0;
			}
			//將x,y以目前方向往前一格 
        	int newx = x + dx[direction];
        	int newy = y + dy[direction];
        	// 檢查新位置是否在迷宮範圍內，且是一個未訪問過且能走的點
        	if (newx >= 0 && newx < mazey && newy >= 0 && newy < mazex &&
            	mazeptr[newx][newy] != 'O' ) {
            	// 遞迴搜索新位置
            	
            	if(newx==ox&&newy==oy){
            		//新一格與上一格相同不走 
				}
				else{
            		temp=ShortGo(newx, newy,direction,path);
            		//若回傳=目前最短且不為-1，設結果為回傳值 
            		if (temp==spath&&temp!=-1) {
           	     		result=temp;
         			}
         		}
       	 	}
       	 	//若此方向走不到目標則將方向轉向下一個方向
       	 	direction=direction+1;
    	}
		if (result==spath&&result!=-1) { //result=spath
           	// 結果=已知最短則最終路徑會經過此格 
           	// 並將此路徑在R陣列標上R 
           	// 再將結果繼續回傳 
           	pmazeptr[x][y] = 'R';
            return result;
        }
    	// 如果所有方向都無法找到路徑，返回-1
    	return -1;
	}
};

Maze Set(Maze maze){
	char num[100] ;         //存使用者輸入的檔案號碼 
	char fname[200]="input";//存整個檔案的名字 
	char trash;             //存不需要的換行 
	
	//讀入檔案號碼 
	printf("Input a file number:");
	scanf("%s",&num); 
	
	//串接檔名 
	strcat(fname,num);
	strcat(fname,".txt");
	
	//開啟相應文件 
	FILE *file;
	file = fopen(fname, "rb"); // 以唯讀模式打開文件
	if (file == NULL) {
		//找不到此文件則輸出錯誤訊息 
    	printf("\ninput%s.txt does not exist!\n",num);
    	//並將maze中的have設為false
    	maze.Sethave(false);
	}
	else{
		//找到則呼叫maze.SetMaze()繼續執行迷宮設定 
		maze.SetMaze(file);
		//設定完成關閉文件 
		fclose(file);
	}
	
	
	//讀取前面讀取檔案號碼訊息多餘的換行
	scanf("%c",&trash);
	printf("\n");
	return maze; //將設定好的class回傳 
}

void One(){
	Maze maze;          // 建立一個新的Maze class 
	char **pmaze = NULL;// 存取R的結果陣列 
	char **vmaze = NULL;// 存取V的結果陣列 
	
	//呼叫Set()進行迷宮設定 
	maze=Set(maze);
	
	// 用maze.Gethave()檢查確實有迷宮 
	if (maze.Gethave()){
	
		//若有找到目標則輸出V陣列和R陣列
		//(0,0,0)代表從座標(0,0)開始方向朝右 
		if (maze.OneGo(0,0,0)) {
		
			vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);	
				}
				printf("\n");
    	    }
    	    printf("\n");
			pmaze=maze.GetpMaze();
    	    for (int i = 0; i < maze.Gety(); i++) {
    	    	for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",pmaze[i][j]);
				}
				printf("\n");   
    	    }
    	    printf("\n");
    	} 
    	//若沒找到目標則只輸出V陣列
		else {
    	    vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);
				}
				printf("\n");
    	    }
    	    printf("\n");
    	}
	}
	//釋放記憶體 
	maze.Free();
}

void More(){
	Maze maze;          // 建立一個新的Maze class 
	int goals;          // 存讀入的目標數 
	char trash;         // 存不需要的換行
	char **pmaze = NULL;// 存取R的結果陣列
	char **vmaze = NULL;// 存取V的結果陣列
	
	//呼叫Set()進行迷宮設定 
	maze=Set(maze);
	
	// 用maze.Gethave()檢查確實有迷宮
	if(maze.Gethave()){
	
		//詢問並讀入目標數 
		printf("Number of G (goals):");
		scanf("%d",&goals);
		printf("\n");
		while(goals<1||goals>100){
			printf("### The number must be in [1,100] ###\n\n");
			printf("Number of G (goals):");
			scanf("%d",&goals);
			printf("\n");
		}
		//呼叫Setgoals()設定目標數 
		maze.Setgoals(goals);
	
		//若有找到索求數量的目標則輸出V陣列和R陣列
		//(0,0,0)代表從座標(0,0)開始方向朝右 
		if (maze.MoreGo(0,0,0)) {
		
			vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);
				}
				printf("\n");
    	    }
    	    printf("\n");
			pmaze=maze.GetpMaze();
    	    for (int i = 0; i < maze.Gety(); i++) {
    	    	for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",pmaze[i][j]);
				}
				printf("\n");   
    	    }
    	    printf("\n");
    	} 
		//若沒找到目標則只輸出V陣列
		else {
    	    vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);
				}
				printf("\n");
    	    }
    	    printf("\n");
    	}
	
		//讀掉目標數後面的換行 
		scanf("%c",&trash);
	}
	//釋放記憶體 
	maze.Free();
}

void Short(){
	Maze maze;          // 建立一個新的Maze class 
	char **pmaze = NULL;// 存取R的結果陣列 
	char **vmaze = NULL;// 存取V的結果陣列 
	int path;           // 存路徑長度 
	//呼叫Set()進行迷宮設定 
	maze=Set(maze);
	
	// 用maze.Gethave()檢查確實有迷宮 
	if (maze.Gethave()){
	
	    
		//若有找到目標則輸出V陣列和R陣列還有路徑長 
		//(0,0,0,0)代表從座標(0,0)開始方向朝右 ,且路徑為0 
		if (maze.ShortGo(0,0,0,0)>0) {
		
		    //取得最短的路徑 
			path=maze.Getpath();
			
			vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);	
				}
				printf("\n");
    	    }
    	    printf("\n");
			pmaze=maze.GetpMaze();
    	    for (int i = 0; i < maze.Gety(); i++) {
    	    	for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",pmaze[i][j]);
				}
				printf("\n");   
    	    }
    	    printf("\n");
    	    
    	    printf("Shortest path length = %d\n",path);
    	    printf("\n");
    	} 
    	//若沒找到目標則只輸出V陣列
		else {
    	    vmaze=maze.GetvMaze();
			for (int i = 0; i < maze.Gety(); i++) {
				for (int j = 0; j < maze.Getx(); j++) {
    	        	printf("%c",vmaze[i][j]);
				}
				printf("\n");
    	    }
    	    printf("\n");
    	}
	}
	
	//釋放記憶體 
	maze.Free();
}

int main(int argc, char** argv) {
	char trash;      //存不需要的換行
	char dowhat='\0';//存取指令
	
	//不停地詢問要執行的動作直到輸入0退出 
	while(dowhat!='0'){
		//印出介面並讀取指令 
		printf("*** Path Finding ***\n");
    	printf("* 0. Quit          *\n");
    	printf("* 1. One goal      *\n");
    	printf("* 2. More goals    *\n");
    	printf("********************\n");
    	printf("Input a command(0, 1, 2, 3):");
		scanf("%c",&dowhat);
		printf("\n");
	
	    //若非合法指令則輸出錯誤訊息，合法則執行相應動作 
		if(dowhat!='0'&&dowhat!='1'&&dowhat!='2'&&dowhat!='3'){
			printf("Command does not exist!\n");
			//讀取前面指令訊息多餘的換行 
			if(dowhat!='\n'){
				scanf("%c",&trash);	
			}
			
			printf("\n");
		}
		else if(dowhat=='1'){
			//指令為1則呼叫One()執行後續程序 
			One();
		}
		else if(dowhat=='2'){
			//指令為1則呼叫More()執行後續程序
			More();
		}
		else if(dowhat=='3'){
			//指令為1則呼叫More()執行後續程序
			Short();
		}
	}
	

}
