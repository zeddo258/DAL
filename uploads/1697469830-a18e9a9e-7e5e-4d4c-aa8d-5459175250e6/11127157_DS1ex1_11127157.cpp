// 11127157 ���lģ

# include <iostream>
# include <string> 
# include <cstdio>

using namespace std;

class Maze {

	public: 	
  		int row = 0 ;
    	int column = 0;
    	char** maze;  //���V ���Vchar���� ������  
    	int i = 0;
		int j = 0;
	  
    	Maze() {      //  �ͦ�Maze�ɪ�l�Ƹ�� 
      		row = 0;
      		column = 0;
      		maze = NULL;
    	}

    	void Clr() {  //����O���� 
        	if (maze != NULL) {
            	for (int i = 0; i < row; i++) {
                	delete[] maze[i];   //����C��  
            	}
            	delete[] maze;  //����g�cmaze 
        	}
    	}
	
		bool load(string fileName) {  //Ū�� 
      		FILE *fileptr = NULL;
	  		bool success = false;
	    
	  		fileName = "input" + fileName + ".txt";
      		fileptr = fopen(fileName.c_str(), "r");  //�}�� 
    
      		if (fileptr == NULL) {    //Ū�ɥ��� 
        		cout << endl << fileName << " does not exist!" << endl;
    			return false;
	  		}
	
	  		else {                              
	  			fscanf(fileptr, "%d %d", &column, &row);
	    		maze = new char*[row];
				for (int i = 0; i < row; i++) {  
            		maze[i] = new char[column]; 
            		for (int j = 0; j < column; j++) {
                		fscanf(fileptr, " %c", &maze[i][j]);   //Ū�J��Ƥ��� 
            		}
        		}	 
        
        
			i = 0;
        	j = 0;
        		 
			fclose(fileptr);  //���� 
				
      		return true ;	   		
      		} 
    
  		}	  
  
  		bool findGoals(int x, int y,int direction) {  //(�y��,��V) 
  			
  			int next_direction = 0;  //��V�� 
    
    		if (x < 0 || x >= row || y < 0 || y >= column || maze[x][y] == 'O' || maze[x][y] == 'V')  //�W�X�g�c�λ�ê�� 
        		return false;
    		else if (maze[x][y] == 'G') 
        		return true;
		        
    		maze[x][y] = 'V';  //���L���� 
	
    		// �V�k�� 
    		if (direction == 0) {
    			if (findGoals(x,y+1,direction)) 
					return true;
			}
	 	
    		// �V�U��
    		else if (direction == 1) {
    			if (findGoals(x+1,y,direction))
	  				return true;	 	
			}		 

    		// �V����
    		else if (direction == 2) {
    			if (findGoals(x,y-1,direction))
					return true;    			
			} 		 			 

    		// �V�W��
    		else if (direction == 3){
    			if (findGoals(x-1,y,direction))
    				return true;
    		}  

            maze[x][y] = 'E';  //�o�Ӥ�V�w�g���쩳�Τw�g�L�k�A���F,�ܦ��Ů�H�K�U�����j�� 
			next_direction = (direction + 1) % 4;  //��V��k 
			
			if(findGoals(x,y,next_direction))  //��V�~�� 
				return true;

    		maze[x][y] = 'V';        		// �p�G�|�Ӥ�V���L�k�e�i�A�N��e��m�аO�� 'V' ��ܤw���L  

    		return false;
  		}
	  	
  		void show() {   //�L�XV �����| 
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
		
		void showroad(){   //�L�XR �����| 
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
        		if(aMaze.findGoals(0,0,0)){   //�q�_�l�I�}�l�� 
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
        		if(aMaze.findGoals(0,0,0)){   //�q�_�l�I�}�l�� 
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
