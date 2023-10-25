#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<string>
#include<fstream>
using namespace std ;
//G 6 O 14
struct set
{
    int x;
    int y;

};

class Maze{
    public:
    int row ;//  to record the row of the maze
    int column ; //  to record the column of the maze
    int aim ;// to fine where all the goals's location
    Maze(){
        row = 0 ;
        column = 0 ;
    }
    vector<set> goal_vec, goal_vvec ; // goal_vvec 是已拜訪的'G'
    vector<vector<int>> maze ; // for visited 
    vector<vector<int>> maze2 ; // for track
    vector<set>  track , track2;
    // track2 will be used in the q2 to record all the track to 'G' 
    // although track can do this but if the user want to find more than one goal
    // it will pop the first trail to the 'G'
    bool if_done( void ) ; // to check the if the goal exist in the track_vec
    void Create_maze( string filename ) ;//I will turn the char maze into the int maze via ASCII code
    bool isvisited( int x, int y) ; // if the spot is visited
    bool is_o( int x, int y) ;// if the spot is obstacle 
    bool noway( set temp) ; // if there is any way that the spot can move
    void Start(set cur, int dir, int targer_num) ; //  Start moving
    void print_v(void); // print the visited trail
    void print_r(void);// print the trail to the 'G' via track
    void print_r2( void);// print the trail to the 'G' via track2
};  
void Maze :: print_r(void){
    if ( goal_vvec.size() != 0 ){
    cout << endl << endl ;
        for ( int i = 0 ; i < track.size(); i++ ){
            maze2[track[i].y][track[i].x] = 17;
        }
            for ( int i = 0 ; i < goal_vvec.size(); i++){
            maze2[goal_vvec[i].y][goal_vvec[i].x] = 6 ;
        }
        for ( int i = 0 ;i < goal_vec.size(); i++ ){
            maze2[goal_vec[i].y][goal_vec[i].x] = 6 ;
        }  
        for( int i = 0 ; i < row ; i++ ){
            for( int j = 0 ; j < column ; j++ ){
                printf( "%c", (char)maze2[i][j] + 65);
            }
            cout << endl ;
        }    
    }    
}
void Maze :: print_r2(void){
    if( goal_vvec.size() == aim){
        cout << endl << endl ;    
        for ( int i = 0 ; i < track2.size(); i++ ){
            maze2[track2[i].y][track2[i].x] = 17;
        }
        for ( int i = 0 ; i < goal_vvec.size(); i++ ){
            maze2[goal_vvec[i].y][goal_vvec[i].x] = 6 ;
        }
        for ( int i = 0 ;i < goal_vec.size(); i++ ){
            maze2[goal_vec[i].y][goal_vec[i].x] = 6 ;
        }
        for( int i = 0 ; i < row ; i++ ){
            for( int j = 0 ; j < column ; j++ ){
                printf( "%c",  (char)maze2[i][j] + 65);
            }
            cout << endl ;
        }
    }
}
void Maze :: print_v( void){
    for ( int i = 0 ; i < goal_vvec.size(); i++){
        maze[goal_vvec[i].y][goal_vvec[i].x] = 6 ;
    }
    for ( int i = 0 ;i < goal_vec.size(); i++ ){
        maze[goal_vec[i].y][goal_vec[i].x] = 6 ;
    }    

    
    for( int i = 0 ; i < row ; i++ ){
        for( int j = 0 ; j < column ; j++ ){
            printf( "%c", (char)maze[i][j] + 65);
        }
        cout << endl ;
    }

}
bool Maze :: noway( set temp){
    if ( ( temp.y + 1 <= row - 1 && maze[temp.y + 1][temp.x] == 4) ||
    ( temp.y - 1 >= 0 && maze[temp.y -1][temp.x] == 4) 
    ||(temp.x + 1 <= column - 1 && maze[temp.y ][temp.x + 1] == 4 )
    ||( temp.x - 1 >= 0 && maze[temp.y ][temp.x -1] == 4))
        return false ;
    return true ;
}
bool Maze :: if_done(void){ // ok
    if ( track.size() == 0 ) return false ;
    for ( int j = 0 ; j < goal_vvec.size() ; j++ ){
        if ( goal_vvec[j].x == track[track.size()-1].x && goal_vvec[j].y == track[track.size() - 1 ].y )
            return true ;
    }
    for( int i = 0 ; i < goal_vec.size() ; i++ ){
        
        if ( track[track.size()-1].x == goal_vec[i].x && track[track.size() - 1 ].y == goal_vec[i].y ){
            goal_vvec.push_back(goal_vec[i]) ;
            for( int k = 0 ; k < track.size(); k++)
                track2.push_back(track[k]);
            goal_vec.erase( goal_vec.begin() + i ) ;
            return true ; 
        }
    }
    return false ;
}
void Maze :: Start(set cur, int dir, int target){
    if ( track.empty() ) return ;
    if( if_done() && target == goal_vvec.size()) return ;
    if( dir == 0 && cur.x + 1 <= column - 1  && !isvisited( cur.x + 1 , cur.y ) && !is_o( cur.x + 1 , cur.y) ){ // right
        cur.x = cur.x+1 ;
        maze[cur.y][cur.x] = 21 ;
        track.push_back(cur) ;
        Start(cur, dir, target);
    }
    else{
        // if the direction was right before and then it countered the obstacle
        // it will turn it's direction into left
        if ( dir == 0 ) dir = 1 ;
    }
    if(if_done()&& target == goal_vvec.size()) return ;
    if( dir == 1 && cur.y + 1 <= row - 1 && !isvisited( cur.x , cur.y + 1 )&& !is_o( cur.x  , cur.y + 1 ) ){ // down
        cur.y = cur.y + 1 ;
       
        maze[cur.y][cur.x] = 21 ;      
        track.push_back(cur) ;
        Start( cur,dir, target );
    }
    else{
        if ( dir == 1 ) dir = 2 ;
    }
    if(if_done()&& target == goal_vvec.size()) return ;
    if( dir == 2 && cur.x - 1 >= 0 && !isvisited( cur.x - 1 , cur.y ) && !is_o( cur.x - 1 , cur.y ) ){ // left 
        cur.x = cur.x - 1 ;
        maze[cur.y][cur.x] = 21 ;        
        track.push_back(cur) ; 
        Start(cur,dir, target);
    }
    else {
        if ( dir == 2 ) dir = 3 ;
    }
    if(if_done()&& target == goal_vvec.size()) return ;
    if( dir == 3  && cur.y - 1 >= 0 && !isvisited( cur.x  , cur.y - 1 )  && !is_o( cur.x , cur.y - 1 ) ){ // up
        cur.y = cur.y - 1 ;
        maze[cur.y][cur.x] = 21 ;
        track.push_back(cur);
        Start(cur,dir, target);
    }
    else{
        if ( dir == 3 ) dir = 0 ;
    }
    if( if_done() && target == goal_vvec.size()) return ;
    else{
        if ( !track.empty()){
            while ( noway(cur) && track.size() > 0 ){
                cur = track[track.size() - 1 ] ; 
                track.pop_back();
            } 
        }
        Start(cur, dir, target);
        
    }   
}
bool Maze :: is_o( int x, int y){ // ok
    if ( maze[y][x] == 14 ) return true ;
    return false ;
}
bool Maze :: isvisited( int x, int y ){
    if ( maze[y][x] == 21 ) return true ;
    return false;
}
void Maze :: Create_maze( string filename ){
    ifstream ifs ;
    ifs.open(filename);
    if( !ifs.is_open() ) {
        cout << " there is not such file"<< endl  ;
        return ;
    }
    string line ;
    int first = 0 ;
    getline(ifs, line);
    for ( int i = 0 ; i < line.size(); i++ ){
        if (line[i] == ' '){
            for ( int j = 0 ; j < i ;j++){
                column = column + (line[j] -'0') * pow(10, i -j -1);
            }
            for ( int j = i ; j < line.size() -1; j++ ){
                row = row +(line[j+1] - '0') * pow(10, line.size() -2 - j);
            }
        }

    }
    vector<int> columnv ;
    columnv.assign(column,0);
    vector<vector<int>> vec_2d;
    vec_2d.assign(row,columnv);
    int index = 0 ; 
    set goal ;
    
    while( !ifs.eof() ){
        getline(ifs, line);
        for ( int i = 0 ; i < line.size() ; i++){
            vec_2d[index][i] = line[i] - 'A';
            if ( line[i] == 'G') {
                goal.y = index ;
                goal.x = i ;
                goal_vec.push_back(goal);
                // to record the coordinate of the goal
                
            }
        }
        index++;
    }
    maze = vec_2d ;
    maze2 = vec_2d ;
    maze[0][0] = 21 ; // the start point is visited point 
    set temp ;
    temp.x = 0 ;
    temp.y = 0 ;
    track.push_back(temp);
    ifs.close();
}


int main(){
    int command ;
    do{
    cout << "*** Path Finding ***" << endl 
         << "* 0. Quit          *" << endl 
         << "* 1. One goal      *" << endl
         << "* 2. More goals    *" << endl 
         << "********************"<< endl 
         << "Input a command(0, 1, 2):";
        cin >> command ;
        Maze test ;
        string filename ;
        set temp ;
        temp.x = 0 ;
        temp.y = 0 ; 
        if ( command == 1 ){
            cout << "enter a filenum : ";
            cin >> filename ;
            test.Create_maze("input"+filename+".txt");
            test.Start(temp, 0,1);
            test.print_v();
            test.print_r();
        }
        else if ( command == 2 ){
            cout << "enter a filenum : ";
            cin >> filename ;
            test.Create_maze("input"+filename+".txt");
            cout << "enter a number : ";   
            cin >> test.aim ;
            test.Start(temp, 0, test.aim);
            test.print_v();
            test.print_r2();
        }
        else if ( command <0 || command > 2){
            cout << " the entered number is worng " ;
        }
        

    }while( command != 0);

    return 0;
}
