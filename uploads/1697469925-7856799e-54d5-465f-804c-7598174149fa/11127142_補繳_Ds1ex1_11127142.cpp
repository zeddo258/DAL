// 11127142 范庭郡
#include <iostream>
#include "Maze.h"
using namespace std;
int main(){
    int command = 0;
    do {
        string filename;
        cout << endl << "***Path Finding***";
        cout << endl << "0. Quit           ";
        cout << endl << "1. One goal       ";
        cout << endl << "2. More goals     ";
        cout << endl << "3.ShortestPath    ";
        cout << endl << "******************";
        cout << endl << "Input a command( 0, 1, 2, 3 )";
        cin >> command;
        if ( command == 1 || command == 2 || command ==3 ) {
            Maze amaze;
            if ( command==2 ){
                int n = 0;
                cout << endl<<"Enter the number of N = ";
                cin >> n;
                amaze.G = n;
            }
            else {
                amaze.G = 1;
            }
            cout<<endl<<"Please input a file number : ";
            cin >> filename;
            if (amaze.load(filename)) {
                if ( !amaze.FindG(amaze.aMaze) ) {
                    amaze.G = 0;
                    cout << "The path doesn't exist.... " << endl;
                } // if
                if ( command == 1 || command == 2 )
                    amaze.show();
                else
                    amaze.FindShortestPath();
            } // if

            else {
                cout << "The file dosen't exist" << endl;
            }
        } // if

        else if (!command) {
            cout << "bye~"<<endl;
            break;
        } // else if

        else
            cout<<endl<<"Command does not exist!!"<<endl;
    } while(1);

    system("pause");
    return 0;
} // main()