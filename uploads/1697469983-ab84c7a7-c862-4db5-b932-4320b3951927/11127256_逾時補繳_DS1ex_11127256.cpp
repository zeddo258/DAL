//11127256¿½¤Ñ»y 
#include "555.hpp"

int main(void)
{	int command = 0;
	do
	{	Maze aMaze;
		string	fileName;
		Modes	mode = oneG;
		cout<<endl<<"*** Path Finding ***";
		cout<<endl<<"* 0. Quit          *";
		cout<<endl<<"* 1. One goal      *";
		cout<<endl<<"* 2. More goals    *";
		cout<<endl<<"********************";
		cout<<endl<<"Input a command(0,1,2,):";
		cin>>command;
		if((command == 1)||(command == 2))
		{	if(command == 2 )
				mode = moreG;
			cout<<endl<<"Input a file number(e.g.,201,202,...):";
			cin>>fileName;
			if(aMaze.load(fileName,mode)) //load the original matrix
			{	Maze	vMaze(aMaze);// a copy to keep the visited cells
				bool success = aMaze.findGoals(vMaze);// find a path to goal(s)
				mode = oneG;// reset to default
				vMaze.show();// show on screen the visited cells+
				if(success){// to check the if the goal is reached or not
					cout<<endl;
					aMaze.show();// show on screen the route to reach the goal
				}
				vMaze.cir();//clear up the copy
			}
			aMaze.cir();//clear up the original matrix
		}
		else if(!command)//stop the program
			break;
		else
			cout<<endl<<"Command does not exist!"<<endl;
	}while(true);
	
	system("pause");
	return 0;
}
