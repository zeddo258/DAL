//03109309_�f�K�M 
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
		if(command==1||command==2){//��J1��2
			//�@�Ӳ��I 
			if(command==2)
				mode=2; //�h�Ӳ��I 
			cout<<endl<<"Input a file number:";
			cin>>fileName;//��J�ɮצW�� 
			if(aMaze.load(fileName)){
				aMaze.show(mode);
				aMaze.final(mode);
			}
		}
		else if(!command)//��J0���}�{�� 
		break;
		else//��J���s�b���ﶵ 
		cout<<endl<<"Command does not exist!"<<endl;
	}while(true);
    system("pause");
	return 0;
}
