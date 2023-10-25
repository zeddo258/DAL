#include <stdlib.h>
#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Map {
public:
    int a = 0;
	int b = 0;
    int x = 0;
	int y = 0;
    int dis = 0;
    bool isG = true;
    // constructor
    Map(string path);
    // find the path of the map
    void task1(int x, int y, int dis, bool &isG ); 
    // find the path of the map
    void task2(int x, int y, int dis, bool &isG );
    // print the map
    void printMap();
    // get the point of the map info
    char getMapInfo(int x, int y);

private:
    vector<vector<char> > map;
    void setMapInfo(int x, int y, char c);

};

int main() {
    int x = 0 ;
    int y = 0;
    int dis = 0;
    int command = 0;
    bool isG = false;
    string file;
    cout << endl << "*** Path Finding ***";
    cout << endl << "* 0. Quit          *"; 
    cout << endl << "* 1. One goal      *"; 
    cout << endl << "* 2. More goals    *";
    cout << endl <<"*********************";
    cout << endl << "Input a command(0, 1, 2): ";
    cin >> command;
    cout << endl << "Input the file number: ";
    cin >> file;
    Map map(file);
    if( (command == 1) || (command == 2)){
    	if ( command == 1 ) {
	    	map.task1(x, y, dis, isG);
	    	map.printMap();
		}
	    if( command == 2 ){
			map.task2(x, y, dis, isG);
    		map.printMap();
    	}
    	return 0;
    }
}

// constructor
Map::Map(string path) { 
    ifstream file;
    path = "input" + path + ".txt";
    file.open( path.c_str() );  
    assert(file.is_open());
    string line;
    file  >> a >> b;
    a = a;
    b = b;
    getline(file, line);
    while (getline(file, line)) {
        vector<char> row;
        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
        }
        map.push_back(row);
    }
    file.close();
}

void Map::printMap(){
    for (int i = 0; i < map.size(); i++ ){
        for (int j = 0; j < map[i].size(); j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
    
    if ( isG  ){
    	cout << endl;

    	for (int i = 0; i < map.size(); i++ ){
        	for (int j = 0; j < map[i].size(); j++) {
        		if ( map[i][j] == 'V' )
        			map[i][j] = 'R';
  	        	cout << map[i][j];
    	    }
        	cout << endl;
    	}
	}
}

void Map::task1( int x, int y, int dis, bool &isG ){
    
    if ( x >= 0 && x < b && y >= 0 && y < a){
        if ( map[x][y] == 'E' ){
        	
            if ( dis == 0 ) {
                setMapInfo(x, y, 'V' );
                y++;
                task1(x, y, dis, isG);
            }
            if ( dis == 1 ) {
                setMapInfo(x, y, 'V' );
                x++;
                task1(x, y, dis, isG);
            }
            if ( dis == 2 ) {
                setMapInfo(x, y, 'V' );
                y--;
                task1(x, y, dis, isG);
            }
            if ( dis == 3 ) {
                setMapInfo(x, y, 'V' );
                x--;
                task1(x, y, dis, isG);
            }  
        }  
        else if ( ( map[x][y] == 'O' || map[x][y] == 'V' ) ) {
            dis ++;
            dis = dis % 4;   
            
            if ( dis == 1 ) { // down
                y--;
                x++;
                task1(x, y, dis, isG);
            }
            if ( dis == 2 ) { // left
                x--;
                y--;
                task1(x, y, dis, isG);
            }
            if ( dis == 3 ) { // up
                y++;
                x--;
                task1(x, y, dis, isG);
            }
            if ( dis == 0 ) { // right
                x++;
                y++;
                dis = 0;
                task1(x, y, dis, isG);
            }  
        }
        else if ( map [x][y] == 'G' ){
    		isG = true;
   		}
    
    }
	else if ( y == a || x == b || y < 0 || x < 0 ) {                                                     
		dis++;
		dis = dis % 4;

		if( y == a ) {
			y--;
			x++;
			task1(x, y, dis, isG);
		}
		if( x == b ){
			x--;
			y--;
			task1(x, y, dis, isG);
		}
		if( y < 0 ) {
			y++;
			x--;
			task1(x, y, dis, isG);
		}
		if( x < 0){
			x++;
			y++;
			task1(x, y, dis, isG);
		}
	}
	
}

void Map::task2( int x, int y, int dis, bool &isG ){
    if ( x >= 0 && x < b && y >= 0 && y < a){
        if ( map[x][y] == 'E' ){
        	
            if ( dis == 0 ) {
                setMapInfo(x, y, 'V' );
                y++;
                task2(x, y, dis, isG);
            }
            if ( dis == 1 ) {
                setMapInfo(x, y, 'V' );
                x++;
                task2(x, y, dis, isG);
            }
            if ( dis == 2 ) {
                setMapInfo(x, y, 'V' );
                y--;
                task2(x, y, dis, isG);
            }
            if ( dis == 3 ) {
                setMapInfo(x, y, 'V' );
                x--;
                task2(x, y, dis, isG);
            }  
        }  
        else if ( ( map[x][y] == 'O' || map[x][y] == 'V' ) ) {
            dis ++;
            dis = dis % 4;   
            
            if ( dis == 1 ) { // down
                y--;
                x++;
                task2(x, y, dis, isG);
            }
            if ( dis == 2 ) { // left
                x--;
                y--;
                task2(x, y, dis, isG);
            }
            if ( dis == 3 ) { // up
                y++;
                x--;
                task2(x, y, dis, isG);
            }
            if ( dis == 0 ) { // right
                x++;
                y++;
                dis = 0;
                task2(x, y, dis, isG);
            }  
        }
        else if ( map [x][y] == 'G' ){
    		isG = true;
            if ( map[x][y++] == 'E') { 
            	dis = 0;
                task2(x, y, dis, isG);
            }
            if ( map[x++][y] == 'E' ) {
            	dis = 1;
                task2(x, y, dis, isG);
            }
            if ( map[x][y--] == 'E' ) { 
                dis = 2;
                task2(x, y, dis, isG);
            }
            if ( map[x--][y] == 'E' ) {
            	dis = 3;
                task2(x, y, dis, isG);  
            } 
   		}
    }
	else if ( y == a || x == b || y < 0 || x < 0 ) {                                                     
		dis++;
		dis = dis % 4;

		if( y == a ) {
			y--;
			x++;
			task2(x, y, dis, isG);
		}
		if( x == b ){
			x--;
			y--;
			task2(x, y, dis, isG);
		}
		if( y < 0 ) {
			y++;
			x--;
			task2(x, y, dis, isG);
		}
		if( x < 0){
			x++;
			y++;
			task2(x, y, dis, isG);
		}
	}
	
    
}

char Map::getMapInfo(int x, int y){
    return map[x][y];
}

void Map::setMapInfo(int x, int y, char c){
    map[x][y] = c;
}
