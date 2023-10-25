//11127162 陳祈恩
#include <iostream> 
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <utility>

using namespace std;
struct rem{ 
	int i = 0;
	int j = 0;
	rem * next;
};

class Maze {
	
	
	int list = 0;
	int row = 0;
	vector<string>  route; 
	vector< pair< int , int > > goal;
	public:
		
		bool OpenMap( vector<string> &path, int &row, int &list ) { // 打開外部txt文字檔，並檢查是否為空 
			string line;
			ifstream in;
			string name;
			cout << "Input a file number:";
			cin >> name ;	
				
			if ( name ==  "01" )			
				in.open( "input101.txt" );
			else if ( name == "02" ) {
				in.open( "input102.txt" );
			} // else if
			else if ( name == "03" ) {
				in.open( "input103.txt" );
			} // else if
			else if ( name == "04" ) {
				in.open( "input104.txt" );
			} // else if
			else if ( name == "05" ) {
				in.open( "input105.txt" );
			} // else if
			else if ( name == "06" ) {
				in.open( "input106.txt" );
			} // else if
			else if ( name == "07" ) {
				in.open( "input107.txt" );
			} // else if
			else if ( name == "08" ) {
				in.open( "input108.txt" );
			} // else if
			else {
				cout << "input"<< name <<".txt does not exist!" << endl;
				
			} // else
				
			
			
		   
			if ( in.is_open() ) { // 判斷是否為空 
			
				
				while ( getline( in,line ) ) { // 將地圖存入
					// cout << line << endl;
					
					path.push_back( line );
					list = max(list, static_cast<int>(line.size()));
					// cout << list << endl;
					row++; 
					// cout << row << endl;
				} // while
				
				in.close();
				
				return true;
			} // if
		
			return false;
		} // OpenMap
		
		void PrintMap( vector<string> path ) { // 輸出地圖
	 
			for ( int i = 1 ; i < path.size(); i++ ) {
				cout << path[i] << endl;
			} // for
			
		} // PrintMap
		
		
		bool MoveInMaze( vector<string> &path, int &i, int &j ) {
				   
		    i = 1;
		    j = 0;
		   		    
		    bool stuck = false;
		    bool exmap = false;
		    int temp = 0;
			
			while ( 1 )  {
				
				stuck = true;
				vector< pair< int , int  > > remp; // 紀錄已走訪過的點
				
				if ( MoveRight(path, i, j , remp ) ) {
				
					
					stuck = false;
					if ( path[i][j] == 'G' ) {
						exmap = true;
						break;
					} // if
                   		
                    	
				} // if
				
				if ( MoveDown(path, i, j, remp) ) {
					
					stuck = false;
					if ( path[i][j] == 'G' ) {
						exmap = true;
						break;
						
					} // if
					
					
				} // if
				
				if ( MoveLeft(path, i, j, remp ) ) {
					
					stuck = false;
					if ( path[i][j] == 'G' ) {
						exmap = true;
						break;
					}
				
				} // if
				
				if ( MoveUp(path, i, j ,remp ) ) {
					
					stuck = false;
					if ( path[i][j] == 'G' ) {
						exmap = true;
						break;
					} // if
					
                  
				} // if
		        
				
						
				if ( stuck ) {
					break;	// if stuck, than break
				   
				} // if
				    	
				
					
			} // while
			
		 	
			return exmap; // 回傳完整還是不完整地圖
			
		} // MoveInMaze
		
		
			
	
		bool MoveRight( vector<string> &path, int &i, int &j , vector< pair< int, int > > & remp ) { // 此函數為實現向右走的動作
			
			
			
			int length = path[i].size();
			//int k = 0;
			
			if ( path[i][j+1] == 'V' ) { // 排查有沒有已經走訪過，如果有就返回MoveInMaze函數，讓往下走的程式繼續執行
					
				return false;
			} // if
			else if (path[i][j+1] == 'O'  ) { // 排查是否為障礙O，如果有就返回MoveInMaze函數，讓往下走的程式繼續執行
				return false;
			} // else if
			else if ( j + 1 == length ) // 排查有沒有超過地圖邊界，如果有就返回MoveInMaze函數，讓往下走的程式繼續執行
				return false;
			
			
			for (  ; j < length ; j++ ) { //往右
			
				
				
			    if ( path[i][j] == 'E'){ // 如果是空的(E)，就往右走，並且留下走訪紀錄(V)
			    	remp.push_back( make_pair( i, j ) );
					path[i][j] = 'V';
				} // if	
				else if ( path[i][j] == 'O' ) { // 如果是障礙(O)，就停住，並返回MoveInMaze函數，讓往下走的程式繼續執行
									
					j=j-1;
					
					return true;
				} // else if
				
			    if ( j + 1 == length  ) { // 排查是否走過頭，如果走到邊緣，就停住，並返回MoveInMaze函數，讓往下走的程式繼續執行
			    	
					return true;
				} // if
				
				if ( path[i][j] == 'G' ) //  排查是否為目標(G)，如果是，就紀錄下位置，並返回MoveInMaze函數
					return true;
				
				
			} // for
			
			
			return false; 
		} // MoveRight
		
		bool MoveLeft( vector<string> &path, int &i, int &j , vector< pair< int, int > > & remp ) {// 此函數為實現向左走的動作
			
			
			int length = path[i].size();
		
			if ( path[i][j-1] == 'V' ) { // 排查有沒有已經走訪過，如果有就返回MoveInMaze函數，讓往上走的程式繼續執行
					
					return false;
			} // if
			else if (path[i][j-1] == 'O'  ) { // 排查是否為障礙O，如果有就返回MoveInMaze函數，讓往上走的程式繼續執行
				return false;
			} // else if
			else if ( j == 0 ){  // 排查有沒有超過地圖邊界，如果有就返回MoveInMaze函數，讓往上走的程式繼續執行
				return false;
			} // else if 
		
			
			
			for (  ; j >= 0; j-- ) { //往左
				
				if ( path[i][j] == 'E' ) { // 如果是空的(E)，就往左走，並且留下走訪紀錄(V)
					remp.push_back( make_pair( i, j ) );
					path[i][j] = 'V';
					
				} // if
					
				else if ( path[i][j] == 'O' ) { // 如果是障礙(O)，就停住，並返回MoveInMaze函數，讓往上走的程式繼續執行
					
					j=j+1;
					return true;
				} // else if
				
				if ( j == 0  ) { // 排查是否走過頭，如果走到邊緣，就停住，並返回MoveInMaze函數，讓往上走的程式繼續執行
					return true;
				} // if
				
				if ( path[i][j] == 'G' ) //  排查是否為目標(G)，如果是，就紀錄下位置，並返回MoveInMaze函數
					return true;
				
			} // for
			
			
			return false; 
		} // MoveLeft
		
		bool MoveDown( vector<string> &path, int &i , int &j , vector< pair< int, int > > & remp) { // 此函數為實現向下走的動作
			
     		//int k = 0;
     		//cout << "------" << endl;
     		if ( path[i+1][j] == 'V' ) { // 排查有沒有已經走訪過，如果有就返回MoveInMaze函數，讓往左走的程式繼續執行
					
				return false;
			} // if
			else if (path[i+1][j] == 'O'  ) { // 排查是否為障礙O，如果有就返回MoveInMaze函數，讓往左走的程式繼續執行
				return false;
			} // else if
			else if ( i == path.size() ) // 排查有沒有超過地圖邊界，如果有就返回MoveInMaze函數，讓往左走的程式繼續執行
				return false;
				
			for ( ; 0 < i ; i++ ) {  // 往下
			
				if ( path[i][j] == 'E' ) { // 如果是空的(E)，就往左走，並且留下走訪紀錄(V)
					remp.push_back( make_pair( i, j ) );
					path[i][j] = 'V';
					
				} // if
				else if ( path[i][j] == 'O' ) { // 如果是障礙(O)，就停住，並返回MoveInMaze函數，讓往左走的程式繼續執行
				    
				   	i = i - 1;
				   	return true;
				} // else if
				
				if ( i == path.size() ) { // 排查是否走過頭，如果走到邊緣，就停住，並返回MoveInMaze函數，讓往左走的程式繼續執行
					return true;
				} // if
				
			 	if ( path[i][j] == 'G' ) //  排查是否為目標(G)，如果是，就紀錄下位置，並返回MoveInMaze函數
					return true;
		
				 		
			} // for
			
			return false; 
		} // MoveDown
		
		
		bool MoveUp( vector<string> &path, int &i, int &j , vector< pair< int, int > > & remp ){ // 此函數為實現向上走的動作
			
			//int k = 0;
     		//cout << "------" << endl;
     		if ( path[i-1][j] == 'V' ) { // 排查有沒有已經走訪過，如果有就返回MoveInMaze函數，讓往右走的程式繼續執行
					
				return false;
			} // else if
			else if (path[i-1][j] == 'O'  ) { // 排查是否為障礙O，如果有就返回MoveInMaze函數，讓往右走的程式繼續執行
				return false;
			} // else if
			else if ( i == 1 ) { // 排查有沒有超過地圖邊界，如果有就返回MoveInMaze函數，讓往右走的程式繼續執行
				return false;
			} // else if
			
			for ( ; 0 < i ; i-- ) { // 往上
				
				if ( path[i][j] == 'E' ) { // 如果是空的(E)，就往上走，並且留上走訪紀錄(V)
					remp.push_back( make_pair( i, j ) );
					
					path[i][j] = 'V';
				
				} // if
					
				else if ( path[i][j] == 'O') { // 如果是障礙(O)，就停住，並返回MoveInMaze函數，讓往右走的程式繼續執行
				    
				   	i = i + 1;
				   	return true;
				} // else if
				
				if ( i == 0  ) { // 排查是否走過頭，如果走到邊緣，就停住，並返回MoveInMaze函數，讓往右走的程式繼續執行
					return true;
				} // if
				
				else if ( path[i][j] == 'G' ) //  排查是否為目標(G)，如果是，就紀錄下位置，並返回MoveInMaze函數
					return true;
				
				 		
			} // for
			
			return false; 
		} // MoveDown
		
	
	    void IfMoreG(vector<string> &map , int goalsLeft ) { 
	        CheckG(map);
	        int i =  1, j = 0, dir = -1;
	        MoreG(map, i, j, goalsLeft, dir );
               
	        
	    }
	
	    bool MoreG(vector<string> &map, int i, int j, int &goalsLeft, int & dir) {
	    	
	        if (  map[i][j] == 'O' || map[i][j] == 'V') {
	            return false;
	        } // if
	
	        if (map[i][j] == 'G') {
	            goalsLeft--;
	            return true;
	            
	        }
	
	        if (map[i][j] == 'E') {
	            map[i][j] = 'V';
	            
	        } // if
			
			
			
	        if ( j + 1 < map[i].size()  && dir == 0  && MoreG(map, i, j + 1, goalsLeft , dir ) ) {
	        	
	        	
	        	cout << "右" << endl;
	            return true;
	        }
			
	        if ( i + 1 < map.size() && dir == 1 && MoreG(map, i + 1, j, goalsLeft , dir ) ) {
	        	
	        	
	        	
	            return true;
	        } // if
			
	        if ( j - 1 >= 0 && dir == 2 && MoreG(map, i, j - 1 , goalsLeft , dir ) ) {
	        	
	        	cout << "左" << endl;
	            return true;
	        } // if
			
	        if ( i - 1 >= 0 && dir == 3 && MoreG(map, i - 1, j , goalsLeft , dir ) ) {
	        	
	        	cout << "上" << endl;
	            return true;
	        } // if		
			


			if ( goalsLeft >= 0 ) {
				return MoreG(map, i, j , goalsLeft , dir ) || true;
			}
			else
	        	return false;
	    } 
	
	    void CheckG(vector<string> &map) {
	    	
	        for (int i = 0; i < map.size(); ++i) {
	        	
	            for (int j = 0; j < map[i].size(); ++j) {
	            	
	                if (map[i][j] == 'G') {
	                	
	                    goal.push_back(make_pair(i, j));
	                    
	                } // if
	                
	            } // for
	            
	        } // for
	        
	    } // CheckG
			
			
			
		


		


		
		void PrintUI ( int &com ) {
			
			cout << "*** Path Finding ***" << endl;
		    cout << "* 0. Quit          *" << endl;
		    cout << "* 1. One goal      *" << endl;
		    cout << "* 2. More goals    *" << endl;
		    cout << "********************" << endl;
		    cout << "Input a command(0, 1, 2): ";
		    cin >> com ;
		    
		} // PrintUI
		
	
		
		void PrintRoute( vector<string> path ){
			
			for ( int i = 0 ; i < path.size() ; i++ ) {
				route.push_back( path[i] );
			} // for
			for( int i = 0 ; i < route.size() ; i ++ ) {
				
				for ( int j = 0 ; j < route[i].size() ; j ++ ){
					
					if ( route[i][j] == 'V' ){
						route[i][j] = 'R';
						
					} // if
					
						
				} // for
				
				 
				
			} // for
			
			PrintMap( route );
			
			
		} //PrintRoute


				
}; // Maze





int main() {
	
		
	int x = 0,y=0;
	int com = 0, mat = 0;
	
	while (1) {
		Maze m;
	
		m.PrintUI( com );
		vector<string> Map;
		
		if ( com == 0 ) {
				
			return 0;
		} // if
		else if ( com == 1 ) {
			
							
			if ( m.OpenMap( Map, x, y ) ) {  // 檢查是否有地圖
				
				bool iscomplete = m.MoveInMaze( Map , x ,y ); // 是否有完整的地圖
				if( iscomplete ) { // 如果是完整地圖
					cout << "       " << endl;
					m.PrintMap( Map );
						cout << "       " << endl;
					m.PrintRoute( Map );
		 			cout << "       " << endl;
				} // if
				else if ( !iscomplete ){ // 如果是不完整地圖
					
					cout << "走訪完成" << endl;
					m.PrintMap( Map );
					
				} // else if
					
			} // if
					
					
		} // else if
		else if( com == 2 ) {
			cout << "Enter the Number of goals:";
			int k = 0;
			cin >> k;
			m.OpenMap(Map,x,y);
			m.IfMoreG( Map, k);			
			m.PrintMap( Map );
		
		} // else if
		else{
			cout << "Command does not exist!" << endl;
			cout << "                       " << endl;
		} // else
		
		
		
	} // while
	
    
	return 0;
	
} // main