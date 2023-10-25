// 11127144 ñRÓÚ³¯( MA,YU-CHAO )

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#define SIZE 100
using namespace std;


int CO_X,CO_Y ;                                                      // Set maximum X and Y of the matrix
int position,fake_position;                                          // Set direction of search
bool get_G = false ;                                                // Found the endpoint or not
bool have_G_path = false ;                                          // This path has found the endpoint or not

bool readfile(int CO[SIZE][SIZE], string fileName){                    // Load a file
    ifstream ifs;
    int x=0,y=0;
    fileName = "input"+fileName+".txt";
    ifs.open(fileName,ios::in);

    if(!ifs.is_open())
        cout << endl << fileName << " does not exist!" << endl;
    else{
        char a[100] = {0};
        ifs.getline(a, sizeof(a));
        istringstream iss(a);
        iss >> CO_X >> CO_Y;                                         // Read the matrix size range

        x=0;
        y=0;
        char b;
        while ( (b = ifs.get()) != EOF ){
            if ( x ==  CO_X ){
                x = 0 ;
                y += 1 ;
            }
            switch( b ) {                                           // Convert char to int, make calculations more eazy
                case 'O':
                    CO[y][x]=1;
                    x+=1;
                    break;
                case 'E':
                    CO[y][x]=7;
                    x+=1;
                    break;
                case 'G':
                    CO[y][x]=3;
                    x+=1;
                    break;
                case 'V':
                    CO[y][x]=4;
                    x+=1;
                    break;
                case 'R':
                    CO[y][x]=5;
                    x+=1;
                    break;
                default:  break;
            }
        }
        ifs.close();
        return true ;
    }
    return false ;
}

void copy_CO(int A[SIZE][SIZE],int B[SIZE][SIZE]){                         // Make two matrices the same
    for(int i = 0; i < CO_Y; i++){
        for(int j = 0; j < CO_X; j++){
            B[i][j] = A[i][j];
        }
    }
}

void final_CO(int A[SIZE][SIZE],int B[SIZE][SIZE]){                        // Specify the endpoint's coordinate position
    for(int i = 0; i < CO_Y; i++){
        for(int j = 0; j < CO_X; j++){
            if( B[i][j] == 3 )
            A[i][j] = 3;
        }
    }
}


void show(int CO[SIZE][SIZE]){                                         // Print out the matrix
    for(int i = 0; i < CO_Y; i++){
        for(int j = 0; j < CO_X; j++){
            switch( CO[i][j] ){
                case 1:
                    cout << "O";
                    break;
                case 7:
                    cout << "E";
                    break;
                case 8:
                    cout << "e";
                    break;
                case 3:
                    cout << "G";
                    break;
                case 4:
                    cout << "V";
                    break;
                case 44:
                    cout << "v";
                    break;
                default:  break;
            }
        }
        cout << endl;
    }
}

void show_final(int CO[SIZE][SIZE]){                                   // Print out the final matrix
    for(int i = 0; i < CO_Y; i++){
        for(int j = 0; j < CO_X; j++){
            switch( CO[i][j] ){
                case 1:
                    cout << "O";
                    break;
                case 7:
                    cout << "E";
                    break;
                case 8:
                    cout << "E";
                    break;
                case 3:
                    cout << "G";
                    break;
                case 4:
                    cout << "R";
                    break;
                case 44:
                    cout << "R";
                    break;
                default:  break;
            }
        }
        cout << endl;
    }
}

void path(int CO[SIZE][SIZE],int CO_2[SIZE][SIZE],int goals,int x,int y);                    // Path recursion function
void path_position(int p,int CO[SIZE][SIZE],int CO_2[SIZE][SIZE],int goals,int x,int y);     // Path orientation function
void re_path_position(int p,int CO[SIZE][SIZE],int CO_2[SIZE][SIZE],int goals,int x,int y);  // Path turn back function
bool find_position(int p,int CO[SIZE][SIZE],int x,int y);                                 // Function to find unexplored paths
bool can_position_move(int p,int CO[SIZE][SIZE],int x,int y);                             // Can move or not
bool find_position_V(int p,int CO[SIZE][SIZE],int x,int y);                               // Function for locating the way back direction
void path_position_V(int p,int CO[SIZE][SIZE],int CO_2[SIZE][SIZE],int goals,int x,int y);   // Function to find traversed paths

int main(void){
	int command = 0;		                            // user command
	do{
		int A[SIZE][SIZE] = {0};							// a final matrix
		int B[SIZE][SIZE] = {0};                            // a path matrix
		position = 0;                                   // Reset position
		string fileName;						        // a file name
		int goals = 1;						            // Reset goals

		cout << endl <<"*** Path Finding ***";         // UI
		cout << endl <<"* 0. Quit          *";
		cout << endl <<"* 1. One goal	   *";
		cout << endl <<"* 2. More goals    *";
		cout << endl <<"********************";
		cout << endl <<"Input a command(0, 1, 2): ";
		cin >> command;							// get the command
		if ((command == 1) || (command == 2)){
            cout << endl << "Input a file number (e.g., 201, 202, ...): ";
			cin >> fileName;
            if (readfile(A,fileName)){
                if (command == 2){                           // one or more goals
                    cout << endl << "Number of G (goals): ";
                    cin >> goals;
                }

                if ( command == 2 && goals <= 1 )
                    cout << endl << "Goals must be greater than 1." << endl;
                else{
                    copy_CO(A,B);                           // Make A the same as B
                    path(A,B,goals,0,0);                    // Call the path function
                    final_CO(A,B);
                    show(B);                                // Print out the path matrix
                    cout << endl;
                    if ( get_G ){                           // Check if a solution exists
                        show_final(A);                      // Print out the final matrix
                        cout << endl;
                    }
                }
            }
		}
		else if(!command)
            break;
        else
            cout << endl << "Command does not exist!" << endl;

	}while(true);

	system("pause");
	return 0;
}




void path(int CO[SIZE][SIZE], int CO_2[SIZE][SIZE], int goals, int x, int y) {
    if (goals > 0) {
    // Number of endpoints still to be found
        if ( CO[y][x] == 4 ) {
            // If this cell has been visited, determine the next steps
            int add = 0 ;

            while( find_position(position,CO,x,y)!=true && add <= 3 ){
                // Search for untraveled paths
                add++;
                position++;
            }

            if( find_position(position,CO,x,y) == true && add <= 3 ) // Go when it's found
                path_position(position, CO, CO_2, goals, x, y);
            else{
                // If not found, mark this cell as a new obstacle (with endpoint path (44) & without endpoint path (8))
                if ( have_G_path || CO[y][x] == 44 )
                    CO[y][x] = 44;
                else
                    CO[y][x] = 8;

                add = 0 ;

                while( find_position_V(fake_position,CO,x,y)!=true && add <= 3 ){
                    // Search for the way back
                    add++;
                    fake_position--;
                }

                if( find_position_V(fake_position,CO,x,y) == true && add <= 3 ) // Go when it's found
                    path_position_V(fake_position, CO, CO_2, goals, x, y);
            }

        } else if (x >= CO_X || y >= CO_Y || x < 0 || y < 0 || CO[y][x] == 1 || CO[y][x] == 8 || CO[y][x] == 44 ) {
            // If encountering a boundary or obstacle, backtrack to the previous position
            re_path_position(position, CO, CO_2, goals, x, y);
            fake_position = (position % 4) + 100 ;
            // Synchronize direction
        } else if (CO[y][x] == 3) {
            // Found the endpoint, mark it as found, set this path as an endpoint path, and decrement the count of endpoints to be found
            goals--;

            if ( goals == 0 )
                get_G = true;

            CO[y][x] = 4;
            have_G_path = true;
            fake_position = (position % 4) + 100 ;
            if( can_position_move(position,CO,x,y) ){
                // If unable to proceed, mark this cell as a new obstacle (with endpoint path (44) & without endpoint path (8))
                if ( have_G_path || CO[y][x] == 44 )
                    CO[y][x] = 44;
                else
                    CO[y][x] = 8;
                path_position(position+2, CO, CO_2, goals, x, y);
                // Walk back
            }
            else{
                path_position(position, CO, CO_2, goals, x, y);
                // Go forward
            }
        } else {
            // Untraveled path, mark this location as visited, And reset "have_G_path" to paths without finding the endpoint
            CO[y][x] = 4;
            CO_2[y][x] = 4;
            have_G_path = false;
            fake_position = (position % 4) + 100 ;
            // Synchronize direction
            if( can_position_move(position,CO,x,y) ){
                // If unable to proceed, mark this cell as a new obstacle (with endpoint path (44) & without endpoint path (8))
                if ( have_G_path || CO[y][x] == 44 )
                    CO[y][x] = 44;
                else
                    CO[y][x] = 8;
                path_position(position+2, CO, CO_2, goals, x, y);
                // Walk back
            }
            else{
                path_position(position, CO, CO_2, goals, x, y);
                // Go forward
            }
        }
    }
}

void path_position(int p,int CO[SIZE][SIZE],int CO_2[SIZE][SIZE],int goals,int x,int y){
    if(p%4 == 0)
        path(CO,CO_2,goals,x+1,y);// Go right
    if(p%4 == 1)
        path(CO,CO_2,goals,x,y+1);// Go down
    if(p%4 == 2)
        path(CO,CO_2,goals,x-1,y);// Go left
    if(p%4 == 3)
        path(CO,CO_2,goals,x,y-1);// Go up
}

void re_path_position(int p,int CO[SIZE][SIZE],int CO_2[SIZE][SIZE],int goals,int x,int y){
    // Function to find unexplored paths
    if(p%4 == 0)
        path(CO,CO_2,goals,x-1,y);// Go left
    if(p%4 == 1)
        path(CO,CO_2,goals,x,y-1);// Go up
    if(p%4 == 2)
        path(CO,CO_2,goals,x+1,y);// Go right
    if(p%4 == 3)
        path(CO,CO_2,goals,x,y+1);// Go down
}

bool find_position(int p,int CO[SIZE][SIZE],int x,int y){
    // Walk towards untraveled paths or endpoints
    if(p%4 == 0){
        if ( CO[y][x+1] == 7 || CO[y][x+1] == 3 )
        return true ;
    }
    if(p%4 == 1){
        if ( CO[y+1][x] == 7 || CO[y+1][x] == 3 )
        return true ;
    }
    if(p%4 == 2){
        if ( CO[y][x-1] == 7 || CO[y][x-1] == 3 )
        return true ;
    }
    if(p%4 == 3){
        if ( CO[y-1][x] == 7 || CO[y-1][x] == 3 )
        return true ;
    }

    return false ;
}

bool can_position_move(int p,int CO[SIZE][SIZE],int x,int y){
    // The path ahead has been walked or not
    if(p%4 == 0){
        if ( CO[y][x+1] == 4 )
        return true ;
    }
    if(p%4 == 1){
        if ( CO[y+1][x] == 4 )
        return true ;
    }
    if(p%4 == 2){
        if ( CO[y][x-1] == 4 )
        return true ;
    }
    if(p%4 == 3){
        if ( CO[y-1][x] == 4 )
        return true ;
    }

    return false ;
}

bool find_position_V(int p,int CO[SIZE][SIZE],int x,int y){
    // The location of the previous step
    if(p%4 == 0){
        if ( CO[y][x-1] == 4 )
        return true ;
    }
    if(p%4 == 3){
        if ( CO[y+1][x] == 4 )
        return true ;
    }
    if(p%4 == 2){
        if ( CO[y][x+1] == 4 )
        return true ;
    }
    if(p%4 == 1){
        if ( CO[y-1][x] == 4 )
        return true ;
    }

    return false ;
}

void path_position_V(int p,int CO[SIZE][SIZE],int CO_2[SIZE][SIZE],int goals,int x,int y){
    if(p%4 == 0)
        path(CO,CO_2,goals,x-1,y);// Go left
    if(p%4 == 3)
        path(CO,CO_2,goals,x,y+1);// Go down
    if(p%4 == 2)
        path(CO,CO_2,goals,x+1,y);// Go right
    if(p%4 == 1)
        path(CO,CO_2,goals,x,y-1);// Go up
}
