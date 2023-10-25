// 11127157 黃子耀

# include <iostream>
# include <string> 
# include <cstdio>

using namespace std;

class Maze {

	public: 	
  		int row = 0 ;
    	int column = 0;
    	char** maze;  //指向 指向char指標 的指標  
    	int i = 0;
		int j = 0;
	  
    	Maze() {      //  生成Maze時初始化資料 
      		row = 0;
      		column = 0;
      		maze = NULL;
    	}

    	void Clr() {  //釋放記憶體 
        	if (maze != NULL) {
            	for (int i = 0; i < row; i++) {
                	delete[] maze[i];   //釋放每行  
            	}
            	delete[] maze;  //釋放迷宮maze 
        	}
    	}
	
		bool load(string fileName) {  //讀檔 
      		FILE *fileptr = NULL;
	  		bool success = false;
	    
	  		fileName = "input" + fileName + ".txt";
      		fileptr = fopen(fileName.c_str(), "r");  //開檔 
    
      		if (fileptr == NULL) {    //讀檔失敗 
        		cout << endl << fileName << " does not exist!" << endl;
    			return false;
	  		}
	
	  		else {                              
	  			fscanf(fileptr, "%d %d", &column, &row);
	    		maze = new char*[row];
				for (int i = 0; i < row; i++) {  
            		maze[i] = new char[column]; 
            		for (int j = 0; j < column; j++) {
                		fscanf(fileptr, " %c", &maze[i][j]);   //讀入資料元素 
            		}
        		}	 
        
        
			i = 0;
        	j = 0;
        		 
			fclose(fileptr);  //關檔 
				
      		return true ;	   		
      		} 
    
  		}	  
  
  		bool findGoals(int x, int y,int direction) {  //(座標,方向) 
  			
  			int next_direction = 0;  //轉向用 
    
    		if (x < 0 || x >= row || y < 0 || y >= column || maze[x][y] == 'O' || maze[x][y] == 'V')  //超出迷宮或障礙物 
        		return false;
    		else if (maze[x][y] == 'G') 
        		return true;
		        
    		maze[x][y] = 'V';  //走過打勾 
	
    		// 向右移 
    		if (direction == 0) {
    			if (findGoals(x,y+1,direction)) 
					return true;
			}
	 	
    		// 向下移
    		else if (direction == 1) {
    			if (findGoals(x+1,y,direction))
	  				return true;	 	
			}		 

    		// 向左移
    		else if (direction == 2) {
    			if (findGoals(x,y-1,direction))
					return true;    			
			} 		 			 

    		// 向上移
    		else if (direction == 3){
    			if (findGoals(x-1,y,direction))
    				return true;
    		}  

            maze[x][y] = 'E';  //這個方向已經走到底或已經無法再走了,變成空格以便下次遞迴用 
			next_direction = (direction + 1) % 4;  //轉向方法 
			
			if(findGoals(x,y,next_direction))  //轉向繼續走 
				return true;

    		maze[x][y] = 'V';        		// 如果四個方向都無法前進，將當前位置標記為 'V' 表示已走過  

    		return false;
  		}
	  	
  		void show() {   //印出V 的路徑 
  			while (i < row) {
		  		while(j < column) {
		  			cout << maze[i][j];
		  			j++;
		  		}
		  		j = 0;
		  		i++;
		  		cout << endl;
			}
			cout << "\n";
			i = 0;
			j = 0;
		}
		
		void showroad(){   //印出R 的路徑 
			while (i < row) {
		  		while(j < column) {
		  			if(maze[i][j] == 'V')
		  				maze[i][j] = 'R';
		  			cout << maze[i][j];
		  			j++;
		  		}
		  		j = 0;
		  		i++;
		  		cout << endl;
		  }
		}
};

int main(){
	
	int command = 0 ;

	do {		
    	Maze aMaze ; 
		string fileName ;
	     
		cout << endl << "*** Path Finding ***" ;
    	cout << endl << "*0. Quit           *" ;
		cout << endl << "*1. One goal       *" ;
    	cout << endl << "*2. More goal      *" ;	    	
    	cout << endl << "********************" ;
		cout << endl << "Input a command(0,1,2): " ;
	
		cin >> command ;
	
    	if (command == 1) {  
			cout << endl << "Input a file number :" ;  
	  		cin >> fileName ;
	  		if (aMaze.load(fileName) == true) {
        		if(aMaze.findGoals(0,0,0)){   //從起始點開始走 
					aMaze.show();
					aMaze.showroad();
				}
				
				else 
					aMaze.show();  
	  		}
    	}	
		
		else if(command == 2) {
			cout << endl << "Input a file number :" ;  
			cin >> fileName ;
			if (aMaze.load(fileName) == true) {
        		if(aMaze.findGoals(0,0,0)){   //從起始點開始走 
					aMaze.show();
					aMaze.showroad();
				}
				else 
					aMaze.show();  
	  		}
		} 
    	aMaze.Clr();
	}while(command != 0);

}
