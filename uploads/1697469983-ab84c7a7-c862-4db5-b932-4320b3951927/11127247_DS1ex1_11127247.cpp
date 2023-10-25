//11127247 �i�ů� 
#include <iostream>
#include <fstream> 
#include <vector>
#include <string>

using namespace std;

class Maze {
  
  public: 
    vector< vector<char> > row; // �ΨӦs�x�}�g�c���G���}�C 
    vector< vector<int> > passedby; // �ΨӦs���L���u'V'�C�զ�m���G���}�C 
    vector<int> ele; // �ΨӦs���L���u'V'���C�զ�m���y�� 
    int i= 0,j = 0 ;
    int c=0;
    int k=0;
	int way = 1;//�P�_�{�b�O�k�U���W���@�� 
	int g=0;
	int straight =0; //�U�@�B�O���O���� 

    
    
  	void load(string &input){
  	  fstream file;
  	  file.open(input.c_str());
  	  if(!file.is_open())
  	    return;
  	  vector<char> column; //�ΨӦs�C�@�C�����C�Ӧr��'E''O''G''V''R' 
  	  char ch;
  	  int countofRow;  //�x�}�g�c���C�� 
  	  int countofColumn; //�x�}�g�c����� 
  	  file >> countofColumn >> countofRow; //Ūtxt�ɮפ�����ƤΦC�� 
  	  
  	  for(int i=0; i<countofRow; i++){ //�����ɤ��W�L 
  	    for(int j=0; j<countofColumn; j++){
  	      file >> ch ; //�@�Ӥ@�ӦrŪ�J 
  	  	  column.push_back(ch); 
  	    }
  	    
  	    row.push_back(column);
  	    column.clear();
      } 

      return ;
	}
	


	bool isG(){  //�P�_�U�@�ӬO���OG 
      

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
      	ele.push_back(i);//�s���L���u���y�Ц�m 
        ele.push_back(j);

        passedby.push_back(ele);

        ele.clear();
      	g++;
      	if(g==countG)
      	  
      	  return;	
      }
      else{
      	
      	

        if(way==1){ //�ˬd�k�� 
        	
	      if((row[i][j+1]=='O'||row[i][j+1]=='V')&&row[i].size()>j+1){ // there is a obstacle on the right 
	        
	        way=2; //�����ˬd�U�� 
	        straight=0;
	      }
          else
            straight=1; //���k�䪽�� 
            
        }
	    else if(way==2){ //�ˬd�U�� 
	      
	      if((row[i+1][j]=='O'||row[i+1][j]=='V')&&row.size()>i+1) {// there is a obstacle underneath

	        way=3; //�����ˬd����  
	        straight=0;
          }
          else
            straight=1; //���U������ 
        }
	    else if(way==3){//�ˬd���� 
	    	
	      if((row[i][j-1]=='O'||row[i][j-1]=='V')&& j>0){// there is a obstacle on the left

	        way=4; //�����ˬd�W��  
	        straight=0;
          }
          else
            straight=1; //�����䪽�� 
        }
	    else if(way==4){ //�ˬd�W�� 
	      if((row[i-1][j]=='O'||row[i-1][j]=='V')&&i>0) {//there is a obstacle below
	        way=1; //�����ˬd�k�� 
	        straight=0;
          }
          else
            straight=1; //���W������ 
     
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
		    way=2; //�V�k�����ɭԶW�L�d��A��V�令�U�� 
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
      	    way=3; //�V�U�����ɭԶW�L�d��A��V�令���� 
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
      	    way=4; //�V�������ɭԶW�L�d��A��V�令�W��  
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
      	    way=1; //�V�W�����ɭԶW�L�d��A��V�令�k�� 
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
	int command=0; //���O 
	countofG=1; //G���ƶq 
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
	  aMaze.load(s); //�N�x�}Ū�J
	  
	  vMaze=aMaze;

	  for(int k=0;k<countofG;k++){

	      vMaze.findGoals(countofG);  //��'G'�A�åB�N���L���u�令'V' 
		

      }
	  vMaze.show();
	  cout<<endl;
	  rMaze=vMaze;
	  rMaze.findR(); //�Хܤ@���i����u'R' 
	  rMaze.show();
	  
	  

    }
	return 0;
}
