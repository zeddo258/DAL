//11120127 陳宥任 
#include <iostream>
using namespace std;

#include "DS1ex1_11120127Maze.hpp"


int main(void){
    int command =0;
    
    do{
        Maze aMaze;
        string fileName;
        //Modes mode =oneG;
        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1, 2):";
        cin >> command;
        if((command==1) || (command==2)){
            //if (command == 2)
                //mode =moreG;
            cout << endl << "Input a file number:" ;
            cin >> fileName;
            if(aMaze.load(fileName)){ // 存文字檔 
                Maze vMaze(aMaze);			
				bool success = aMaze.findGoals(vMaze); // 找路 
                //mode = oneG;
                vMaze.show();
                if(success) {
                    aMaze.show();
            	}
				vMaze.clr();
            }
            aMaze.clr();
        }
        else if (!command)
            break;
        else
            cout<<endl<<"Command does not exist!"<<endl;
    } while(true);
    //system("pause");
    return 0;
}

