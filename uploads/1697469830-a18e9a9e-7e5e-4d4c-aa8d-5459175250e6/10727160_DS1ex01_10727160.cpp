// 10727160 ªô¥@øÊ
#include <fstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

int gMapX, gMapY ;

bool GetMap( string fileID, vector<vector<char>> &mMap ) {
	string fileName = "input" + fileID + ".txt" ;
    ifstream inFile( fileName ) ;

    if (!inFile) {
        cout << "### " << fileName << " does not exist! ###" << endl;
        return false;
    } // if()

	char ch = '\0';
	int mapX = 0, mapY = 0; // X,Y of map
	inFile >> gMapX >> gMapY ;
	mMap.resize( gMapX, vector<char>( gMapY ) ) ;  // set size

    for ( int y = 0 ; y < gMapY ; y++ ) {
        for ( int x = 0 ; x < gMapX ; x++ ) 
			inFile >> mMap[x][y] ;
    } // for()
	
	inFile.close();
    return true ;
} // GetMap()

void PrintMap( vector<vector<char>> &map ) {
    for (int y = 0 ; y < gMapY ; y++ ) {
        for (int x = 0 ; x < gMapX ; x++) {
        	if ( map[x][y] == '-' ) map[x][y] = 'G' ;
			cout << map[x][y] << " " ;
		} // for() 
        cout << endl ;
    } // for()
    cout << endl ;
}

class Mouse {
	public:
		void Initialize( vector<vector<char>> &mMap ) ;
		void DirectWay( stack<pair<int,int>> mRoute, vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) ;
		void Clear( stack<pair<int,int>> &mRoute, vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) ;
		void NGoals( int num, stack<pair<int,int>> &mRoute, 
				   vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) ;
		bool Move( int x, int y, int &num, stack<pair<int,int>> &mRoute, 
				   vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) ;
		bool CanMove( int x, int y, vector<vector<char>> mMap ) {
			if ( mMap[x][y] != 'O' && mMap[x][y] != 'V' ) return true ;
			else return false ;
		} // CanMove()
};

bool Mouse::Move( int x, int y, int &num, stack<pair<int,int>> &mRoute, 
				  vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) {
	bool haveRoad;
	if ( mMap[x][y] == 'E' ) mMap[x][y] = 'V' ;
	pair<int,int> coordinates(x,y) ;
	mRoute.push( coordinates ) ;

	if ( ( x + 1 ) < gMapX && CanMove( x+1, y, mMap ) ) {  // Right
		if ( mMap[x+1][y] == 'G' ) {
			stack<pair<int,int>> goalRoute = mRoute ;
			vRoutes.push_back( goalRoute ) ;
			mMap[x+1][y] = '-' ;
			num-- ;
			if ( num == 0 ) return true ;
		} // if() 
		haveRoad = Move( x+1, y, num, mRoute, mMap, vRoutes ) ;
		if ( !haveRoad ) mRoute.pop() ;
		else return true ;
	} // if()
	
	if ( ( y + 1 ) < gMapY && CanMove( x, y+1, mMap ) ) {  // Down
		if ( mMap[x][y+1] == 'G' ) {
			stack<pair<int,int>> goalRoute = mRoute ;
			vRoutes.push_back( goalRoute ) ;
			mMap[x][y+1] = '-' ;
			num-- ;
			if ( num == 0 ) return true ;
		} // if()
		haveRoad = Move( x, y+1, num, mRoute, mMap, vRoutes ) ;
		if ( !haveRoad ) mRoute.pop() ;
		else return true ;
	} // if()
	
	if ( ( x - 1 ) > -1 && CanMove( x-1, y, mMap ) ) {	   // Left
		if ( mMap[x-1][y] == 'G' ) {
			stack<pair<int,int>> goalRoute = mRoute ;
			vRoutes.push_back( goalRoute ) ;
			mMap[x-1][y] = '-' ;
			num-- ;
			if ( num == 0 ) return true ;
		} // if()
		haveRoad = Move( x-1, y, num, mRoute, mMap, vRoutes ) ;
		if ( !haveRoad ) mRoute.pop() ;
		else return true ;
	} // if()
	
	if ( ( y - 1 ) > -1 && CanMove( x, y-1, mMap ) ) {     // Up
		if ( mMap[x][y-1] == 'G' ) {
			stack<pair<int,int>> goalRoute = mRoute ;
			vRoutes.push_back( goalRoute ) ;
			mMap[x][y-1] = '-' ;
			num-- ;
			if ( num == 0 ) return true ;
		} // if()
		haveRoad = Move( x, y-1, num, mRoute, mMap, vRoutes ) ;
		if ( !haveRoad ) mRoute.pop() ;
		else return true ;
	} // if()
	
	return false ;
} // Move()

void Mouse::Initialize( vector<vector<char>> &mMap ) {
    for ( int y = 0 ; y < gMapY ; y++ ) {
        for ( int x = 0 ; x < gMapX ; x++ ) {
        	if ( mMap[x][y] == 'V' ) mMap[x][y] = 'E' ;
    	} // for()
    } // for()
} // Initialize()

void Mouse::DirectWay( stack<pair<int,int>> mRoute, vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) {
	if ( vRoutes.size() < 1 ) mMap[0][0] = 'V' ; // no goal
	else {
		for ( int i = 0 ; i < vRoutes.size() ; i++ ) {
			for ( stack<pair<int,int>> sDway = vRoutes[i] ; !sDway.empty(); sDway.pop() ) {
				pair<int,int> dway = sDway.top() ;
				int x = dway.first ;
				int y = dway.second ;
				if ( mMap[x][y] != 'G') mMap[x][y] = 'R' ;
			} // for()			
		} // for()
	} // else()
} // DirectWay()

void Mouse::Clear( stack<pair<int,int>> &mRoute, vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) {
	vector<vector<char>>().swap( mMap ) ; // swap with empty vector
	vector<stack<pair<int,int>>>().swap( vRoutes ) ;
	while ( !mRoute.empty() ) mRoute.pop() ;
} // Clear()

void Mouse::NGoals( int num, stack<pair<int,int>> &mRoute, 
				  vector<vector<char>> &mMap, vector<stack<pair<int,int>>> &vRoutes ) {

	bool existGoal ;
	existGoal = Move( 0, 0, num, mRoute, mMap, vRoutes ) ;
	PrintMap( mMap ) ;
	cout << "=========================" << endl << endl ;
	Initialize( mMap ) ;
	DirectWay( mRoute, mMap, vRoutes ) ;
	PrintMap( mMap ) ;

	Clear( mRoute, mMap, vRoutes ) ;

} // NGoals()

int main()
{
    int command, num ;
    bool existFile ;
    string fileID ;
	Mouse mouse ;
	vector<vector<char>> mMap ;	
	stack<pair<int,int>> mRoute ;			// save the direct route(x,y) to goal
	vector<stack<pair<int,int>>> vRoutes ;	// save N direct routes to different goals

	do{
    	cout << "*** Path Finding ***" << endl ;
    	cout << "* 0. QUIT          *" << endl ;
   		cout << "* 1. One goal      *" << endl ;
    	cout << "* 2. More goals    *" << endl ;
    	cout << "********************" << endl ;
    	cout << endl << "Input a command(0, 1, 2): " ;
    	cin >> command ;

		switch (command){
    		case 0:
        		break ;
	    	case 1:
    			cout << endl << "Input a file number ([0] Quit):" ;
    			cin >> fileID ;
    			cout << endl ;	
	    		existFile = GetMap( fileID, mMap ) ;	
	    		if ( !existFile ) break ;

	    		num = 1 ;     // mission1: only zero or a goal
	    		mouse.NGoals( num, mRoute, mMap, vRoutes ) ;

    	    	break ;

	   	 	case 2:
	   	 		cout << endl << "Input number of Goals : " ;
	    		cin >> num ;  // mission2: input number of goals
    			cout << endl << "Input a file number ([0] Quit):" ;
    			cin >> fileID ;
    			cout << endl ;	
	    		existFile = GetMap( fileID, mMap ) ;	
	    		if ( !existFile ) break ;
 
	    		mouse.NGoals( num, mRoute, mMap, vRoutes ) ;
	    		

	        	break ;

    		default: cout << endl << "Command does not exist!" << endl ;
		} // end switch

	}while(command != 0) ;

} // main()
