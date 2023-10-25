//11127247 張嘉紜 
#include <iostream>
#include <fstream> 
#include <vector>
#include <string>

using namespace std;

class Maze {
  
  public: 
    vector< vector<char> > row; // 用來存矩陣迷宮的二維陣列 
    vector< vector<int> > passedby; // 用來存走過路線'V'每組位置的二維陣列 
    vector<int> ele; // 用來存走過路線'V'之每組位置的座標 
    int i= 0,j = 0 ;
    int c=0;
    int k=0;
	int way = 1;//判斷現在是右下左上哪一個 
	int g=0;
	int straight =0; //下一步是不是直走 

    
    
  	void load(string &input){
  	  fstream file;
  	  file.open(input.c_str());
  	  if(!file.is_open())
  	    return;
  	  vector<char> column; //用來存每一列中的每個字母'E''O''G''V''R' 
  	  char ch;
  	  int countofRow;  //矩陣迷宮的列數 
  	  int countofColumn; //矩陣迷宮的行數 
  	  file >> countofColumn >> countofRow; //讀txt檔案中的行數及列數 
  	  
  	  for(int i=0; i<countofRow; i++){ //當執行時不超過 
  	    for(int j=0; j<countofColumn; j++){
  	      file >> ch ; //一個一個字讀入 
  	  	  column.push_back(ch); 
  	    }
  	    
  	    row.push_back(column);
  	    column.clear();
      } 

      return ;
	}
	


	bool isG(){  //判斷下一個是不是G 
      

	  if(way==1){
	    if((row[i][j+1]=='G')) // there is a G on the right 
          return true; 
      }
	  else if(way==2){
	    if((row[i+1][j]=='G'))// there is a G underneath
          return true;
      }
	  else if(way==3){
	    if((row[i][j-1]=='G'))// there is a G on the left
          return true;
      }
  	  else if(way==4){
        if((row[i-1][j]=='G') )//there is a G below
          return true;  
      }

      return false;
      
		
	}
	
	void findGoals(int countG) {
		




      if(isG()){
      	row[i][j]='V'; 
      	ele.push_back(i);//存走過路線的座標位置 
        ele.push_back(j);

        passedby.push_back(ele);

        ele.clear();
      	g++;
      	if(g==countG)
      	  
      	  return;	
      }
      else{
      	
      	

        if(way==1){ //檢查右邊 
        	
	      if((row[i][j+1]=='O'||row[i][j+1]=='V')&&row[i].size()>j+1){ // there is a obstacle on the right 
	        
	        way=2; //換成檢查下面 
	        straight=0;
	      }
          else
            straight=1; //往右邊直走 
            
        }
	    else if(way==2){ //檢查下面 
	      
	      if((row[i+1][j]=='O'||row[i+1][j]=='V')&&row.size()>i+1) {// there is a obstacle underneath

	        way=3; //換成檢查左邊  
	        straight=0;
          }
          else
            straight=1; //往下面直走 
        }
	    else if(way==3){//檢查左邊 
	    	
	      if((row[i][j-1]=='O'||row[i][j-1]=='V')&& j>0){// there is a obstacle on the left

	        way=4; //換成檢查上面  
	        straight=0;
          }
          else
            straight=1; //往左邊直走 
        }
	    else if(way==4){ //檢查上面 
	      if((row[i-1][j]=='O'||row[i-1][j]=='V')&&i>0) {//there is a obstacle below
	        way=1; //換成檢查右邊 
	        straight=0;
          }
          else
            straight=1; //往上面直走 
     
		}
		

	  }
	    
      
      
      if(straight==1){
      	if(way==1){
		  
      	  if(row[i].size()>j+1 ) {
            ele.push_back(i);
            ele.push_back(j);
            passedby.push_back(ele);
            ele.clear();
            row[i][j]='V'; 
      	    j++;
      	     
      	  } 
      	  else
		    way=2; //向右走的時候超過範圍，方向改成下面 
	    }
      	else if(way==2){
		  
      	  if(row.size()>i+1){
			ele.push_back(i);
            ele.push_back(j);
            passedby.push_back(ele);
            ele.clear();
            row[i][j]='V'; 
      	    i++;
      	  
          }
      	  else
      	    way=3; //向下走的時候超過範圍，方向改成左邊 
        }
      	else if(way==3){
		  
      	  if(j>0){
			ele.push_back(i);
            ele.push_back(j);
            passedby.push_back(ele);
            ele.clear();
            row[i][j]='V';  
      	    j--;
      	    
          }
      	  else
      	    way=4; //向左走的時候超過範圍，方向改成上面  
        }
      	else if(way==4){
		  
      	  if(i>0){
			ele.push_back(i);
            ele.push_back(j);
            passedby.push_back(ele);
            ele.clear();
            row[i][j]='V'; 
      	    i--;
          }    
      	  else
      	    way=1; //向上走的時候超過範圍，方向改成右邊 
        }
      	
	  }

      
      findGoals(countG);

	}


	void show() {
	  int i = 0, j=0;
	  for(i=0; row.size()>i; i++){
	  	for(j=0; j<row[i].size(); j++)
	  	  cout << row[i][j] ;
	  	cout<<endl;
	  }
	}
	
	void findR(){
		int ti,tj;

	  for(int i=0; passedby.size()>i; i++){
	  	ti=passedby[i][0];
	  	tj=passedby[i][1];
	  	row[ti][tj]='R';
	  	
	  }
		
	}

    


	
};

int main() {

	Maze aMaze, vMaze,rMaze;
	int command=0; //指令 
	countofG=1; //G的數量 
	string filename; 
	cout<<endl<<"***Path Finding***";
	cout<<endl<<"*0.Quit          *";
	cout<<endl<<"*1.One Goal      *"; 
	cout<<endl<<"*2.More Goals    *";
	cout<<endl<<"******************";
	cout<<endl<<"Input a command(0,1,2):";
	cin>>command;
	if(command==1 || command==2){
	  if(command==2)
	  	cin >> countofG;
	  
	  cout<<"Input a file number(eg:101,102,....):"; 
	  cin>>filename;
	  string s="input"+filename+".txt";
	  aMaze.load(s); //將矩陣讀入
	  
	  vMaze=aMaze;

	  for(int k=0;k<countofG;k++){

	      vMaze.findGoals(countofG);  //找'G'，並且將走過路線改成'V' 
		

      }
	  vMaze.show();
	  cout<<endl;
	  rMaze=vMaze;
	  rMaze.findR(); //標示一條可行路線'R' 
	  rMaze.show();
	  
	  

    }
	return 0;
}
