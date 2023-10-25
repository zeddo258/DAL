//03109309_呂沛霖 
#include<iostream>
#include<string> 
#include<cstdio>
#include<fstream>
#include<cstring>
#include "DS1Maze.h"//header file
using namespace std;

int main(){
	int command=0;
	do{ Maze aMaze;
		int mode=1;
		string fileName;
		cout<<"***Path Finding***"<<endl;
		cout<<"*0. Quit         *"<<endl;
		cout<<"*1. One goal     *"<<endl;
		cout<<"*2. More goals   *"<<endl;
		cout<<"******************"<<endl;
		cout<<endl<<"Input a command(0,1,2):";

		cin>>command;
		if(command==1||command==2){//輸入1或2
			//一個終點 
			if(command==2)
				mode=2; //多個終點 
			cout<<endl<<"Input a file number:";
			cin>>fileName;//輸入檔案名稱 
			if(aMaze.load(fileName)){
				aMaze.show(mode);
				aMaze.final(mode);
			}
		}
		else if(!command)//輸入0離開程式 
		break;
		else//輸入不存在的選項 
		cout<<endl<<"Command does not exist!"<<endl;
	}while(true);
    system("pause");
	return 0;
}
