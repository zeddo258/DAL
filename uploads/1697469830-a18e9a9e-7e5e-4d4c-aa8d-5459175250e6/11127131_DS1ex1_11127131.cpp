# include <iostream>
# include <string.h>
# include <fstream>
# include <stdlib.h>
# include <string>

using namespace std;

//*********************************************//
// Path finding for one or more goals in a maze
//*********************************************//

class Maze{

public:


int xlen = 0, ylen = 0; // the column and row lenth
char xy[100][100]; // matrix to put the maze
char keep[100][100]; // matrix to keep the goals' position

bool input(char command[1000], char goalnum[100]){
    int i = 0, j = 0;
    for(i = 0; i < 100; i++){ // clean the keep matrix
        for(j = 0; j < 100; j++) keep[j][i] = '\0';
    }
    if(strcmp(command,"0")==0) return true; // quit

    string filenumber; 
    if(strcmp(command,"1")==0||strcmp(command,"2")==0) {
        printf("Input a file number(e.g., 101, 102,...): ");
        cin >> filenumber; // get the filenumber
        printf("\n");
    }
    else {
        printf("Command does not exist!\n\n"); // no such command
        return false;
    }

    string filename = "input" + filenumber + ".txt"; // combine the filename
    ifstream file(filename); // open the file
    i = 0, j = 0;
    if(file.is_open()){ // if there has this file
        if(strcmp(command,"1")==0||strcmp(command,"2")==0){ // if the command is 1 or 2
            if(strcmp(command,"2")==0) { // more goals then input the goal numbers
                while(true){
                    int numofdigit = 0, number;
                    cout << "Number of G (goals): ";
                    memset(goalnum,0,100); // clear the input
                    cin >> goalnum;
                    printf("\n");

                    for(int p = 0;p<100;p++){ // check the input is digit or not
                        if(isdigit(goalnum[p])) numofdigit++;
                    }
                    if(numofdigit==strlen(goalnum)) { // input is a totally digit
                        number = atoi(goalnum); // turn string to digit
                        if(number==0||number>100) cout << "### The number must be in [1,100] ###\n\n"; // there is a wrong digit
                        else break;
                    }
                }
            }

            file >> xlen >> ylen; // get the column and row

            while(i<ylen){ // get the maze
                while(j<xlen){
                    file >> xy[j][i];
                    if(xy[j][i]=='G'){ // record the goals' position
                        keep[j][i] = 'G';
                    }
                    j = j + 1;
                }
                j = 0;
                i = i + 1;
            }

            return true;
        }
    }
    else cout << filename + " does not exist!\n\n"; // no such filename

    return false;
}


char find(int x, int y, char dir, int &goalnum){
    char check = xy[x][y]; 
    // cout << x << " " << y << " " << dir << " = " << check << " ";
    if(check=='G') {
        goalnum = goalnum - 1; // arrived the goal
        xy[x][y] = 'R'; // record the road
        if(goalnum==0) return 'F'; // finish all goals
    }
    else if(check=='V'||xy[x][y]=='R') return 'V'; // no route(second times visited)
    else if(check=='O') return 'O'; // there is a obstacle
    if(check!='G') xy[x][y] = 'V'; // had visited

    char ans;
    int i = 0;
    
    if(dir=='r' && xlen > x+1) ans = find(x+1,y,'r',goalnum); // keep move to right
    else if(dir=='d' && ylen > y+1) ans = find(x,y+1,'d',goalnum); // keep move to down
    else if(dir=='l' && x!=0) ans = find(x-1,y,'l',goalnum); // keep move to left
    else if(dir=='u' && y!=0) ans = find(x,y-1,'u',goalnum); // keep move to up

    if(ans=='G') {
        check = 'G';
        xy[x][y] = 'R';
    }
    if(ans=='F') { // finish all goals
        xy[x][y] = 'R'; // record the route
        return 'F'; // return the finish signal
    }

    while(i<3){
        if(dir=='u') { // last direction is up
            if(xlen > x+1) ans = find(x+1,y,'r',goalnum); // no exceed matrix length then go right
            dir = 'r'; // change direction to right
        }
        else if(dir=='r') { // last direction is right
            if(ylen > y+1) ans = find(x,y+1,'d',goalnum); // no exceed matrix length then go down
            dir = 'd'; // change direction to down
        }
        else if(dir=='d') { // last direction is down
            if(x!=0) ans = find(x-1,y,'l',goalnum); // no exceed matrix length then go left            
            dir = 'l'; // change direction to left
        }
        else if(dir=='l') { // last direction is left
            if(y!=0) ans = find(x,y-1,'u',goalnum); // no exceed matrix length then go up
            dir = 'u'; // change direction to up
        }

        if(ans=='G') {
            check = 'G';
            xy[x][y] = 'R';
        }
        if(ans=='F') { // finish all goals
            xy[x][y] = 'R'; // record the route
            return 'F'; // return the finish signal
        }
        i = i + 1;
    }
    if(check=='G') return 'G';
    return 'V'; // there is no way to move
}

void print(bool finish){
    int i = 0, j = 0;
    char z;
    while(i<ylen){
        while(j<xlen){
            z = xy[j][i];
            if(keep[j][i]=='G') cout << 'G'; // print goal from keep matrix
            else if(z=='V'||z=='R') cout << "V"; // print visited and route blank
            else if(z=='E'||z=='O') cout << z; // print empty and obstacle blank
            j = j + 1;
        }
        printf("\n");
        j = 0;
        i = i + 1;
    }
    if(finish){ // if all goal finished
        printf("\n");
        i = j = 0;
        while(i<ylen){
            while(j<xlen){
                z = xy[j][i];
                if(keep[j][i]=='G') cout << 'G'; // print goal from keep matrix
                else if(z=='R'||z=='O') cout << z; // print route and obstacle blank
                else if(z=='E'||z=='V') cout << "E"; // print empty and visited blank
                j = j + 1;
            }
            printf("\n");
            j = 0;
            i = i + 1;
        }        
    }   
    cout << endl; 
}
};


int main(){
    char command[1000]; 
    while(true){
        cout << "*** Path Finding ***\n";
        printf("* 0. Quit          *\n");
        printf("* 1. One goal      *\n");
        printf("* 2. More goal     *\n");
        printf("********************\n");
        printf("Input a command(0,1,2): ");
        cin >> command; // get the command
        printf("\n");
        Maze amaze; 
        char ans;
        char goalnum[100];
        if(amaze.input(command,goalnum)){ // if there has correct input
            if(strcmp(command,"0")==0) return 0; // quit
            else if(strcmp(command,"1")==0||strcmp(command,"2")==0){ // one goal or more goal
                int num = atoi(goalnum);
                if(strcmp(command,"2")==0) num = atoi(goalnum);
                else num = 1;
                ans = amaze.find(0,0,'r',num); // find the answer
                if(ans=='F') amaze.print(true); // finish all goal then print two mazes
                else amaze.print(false); // just print one maze
            }
        }
    }
    return 0;
}




