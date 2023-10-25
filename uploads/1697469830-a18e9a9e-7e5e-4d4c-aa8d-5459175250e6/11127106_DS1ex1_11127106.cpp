// 11127106 陳子昂 
#include<iostream>
#include <fstream>
#include<vector>
#include<string>
using namespace std;

class Maze {
		int row;
		int column;	
		char s[100][100];
		char v_road[100][100];
		char r_road[100][100];
		int Gx[100];
		int Gy[100];
	public:
		int gtimes = 0; // 紀錄我找到幾個G了
		bool load( string fileName );
		int Get_row() const;
		int Get_column() const;
		void set_v( int i, int j);
		void set_row_col( int r, int w);
		bool setManyWay( int i, int j, int direction, int G, int G_detect, int success );
		bool donthaveDirection( int i, int j ); // 如果周圍沒路可以走 就return true。
		void printv( int i, int j);	
		void printr( int i, int j);
};

bool Maze::donthaveDirection( int i, int j){ 
	int time = 0;
	bool test = false;
	bool test1 = false;
	bool test2 = false;
	bool test3 = false; 
	while ( time < gtimes ){ // 找尋周圍是否有已經找過的G  如果有，就代表那個方向也是死路
    		if ( ( Gx[time] == i-1 && Gy[time] == j ) ){
    			test = true; 
			}
			if ( Gx[time] == i && Gy[time] == j-1 ) {
				test1 = true;
			}
			if( Gx[time] == i+1 && Gy[time] == j ) {
				test2 = true;
			}
			if ( Gx[time] == i && Gy[time] == j+1 )  {
				test3 = true;
			}
    			
    		time++;		
	}
	if ( j-1 < 0 ){ //只要return true 代表周圍都是死路
			if ( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test3 == true ) ){
				if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test == true ) ) {
					if ( i+1 == column ){
						return true;
					}
					else {
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true ) ){
							return true;
						}
						return false;
					}
					
				}
				return false;
			}
			
			return false;
	}
	else { //只要return true 代表周圍都是死路
		if ( ( v_road[i][j-1]=='V' || v_road[i][j-1] == 'O' || test1 == true ) ) {
			if  ( j+1 == row) {
				if ( i-1 < 0){
					if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) ){
						return true;
					}
					return false;
				}
				else {
					if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test == true) ) {
						if ( i+1 == column){
							return true;	
						}
						else {
							if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) ){
								return true;
							}
							return false;
						}
						
					
					
					}
					return false;
				}
				
								
			} 
			else{
				if( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test3 == true)){	
					if ( i-1 < 0) {
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) )
							return true;
						return false;
					}
					else {
						if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test == true ) ) {
							if ( i+1 == column ){
								return true;
							}
							else {
								if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test2 == true) ){
									return true	;
								}
								return false;
							}
						
						}
						return false;
						
				 
					}
				}
				return false;
			}
			
		}
		return false;
				
	}	
}
	
void Maze::printv( int i, int j) {
	cout<< v_road[i][j]; // 呼叫並印出當前的v路徑
}

void Maze::printr( int i, int j) {
	cout<< r_road[i][j]; // 呼叫並印出當前的R路徑
}
void Maze::set_row_col( int r, int w) { 
	row = r;
	column = w;
	
}

void Maze::set_v( int i, int j) { // 經過的路徑要改成V 
	v_road[i][j] = 'V';
}
int Maze::Get_row() const{ // 取得迷宮的長
	return row;
}

int Maze::Get_column() const{ // 取得迷宮的寬
	return column;
}
bool  Maze::setManyWay(int i, int j ,int direction, int G, int G_detect, int success) { // 這個function是要找出我們要找尋的所有G
	int row = Maze::Get_row() ;
	int column = Maze::Get_column() ;
	int time = 0;  
	bool test = false; 
	bool test1 = false;
	bool test2 = false;
	bool test3 = false;
    if ( v_road[i][j] == 'G' ){ 
    	Gx[gtimes] = i;  // 紀錄這個G的位置 以免找到相同的G 
    	Gy[gtimes] = j; // 紀錄這個G的位置 以免找到相同的G 
    	gtimes = gtimes + 1; // r記錄找過幾個G了 
    	if ( Maze::donthaveDirection( i, j ) ){  // 如果周圍沒有其他路可以走 就return true 
    		return true;							
		}
    		
    	else { // 如果還有路，就依序先往右、往下、往左、往上去找 ， 找到該去的方向並呼叫遞迴 
    		if ( j+1 != row ){
				if ( (v_road[i][j+1] == 'E' && v_road[i][j+1] != 'G' && v_road[i][j+1] != 'V'  ) ) success = Maze::setManyWay(i,j+1, 1, G, G_detect, success);	
			}	
			if ( i+1 != column) {
				if ( (v_road[i+1][j] == 'E' && v_road[i+1][j] != 'G' && v_road[i+1][j] != 'V') ) success = Maze::setManyWay(i+1,j, 2, G, G_detect, success);
			}
		
			if ( j-1 != -1) {
				if ( (v_road[i][j-1] == 'E' && v_road[i][j-1] != 'G' && v_road[i][j-1] != 'V') ) success = Maze::setManyWay(i,j-1, 3, G, G_detect, success);
			}
		
			if ( i-1 != -1 ){
				if ( (v_road[i-1][j] == 'E' && v_road[i-1][j] != 'G' && v_road[i-1][j] != 'V') )success = Maze::setManyWay(i-1,j, 4, G, G_detect, success);	
			}
			
			return true;
    		
		}
	}
	else if ( gtimes == G ){  
		return true;
	}
    else{ // direction 的 1、2、3、4 分別代表 向右 向下 向左 向上 
    	v_road[i][j] = 'V';
    	r_road[i][j] = 'R';
    	while ( time < gtimes ){ // 這個while是去以防會一直找到相同G
    		if ( Gx[time] == i && Gy[time] == j+1 )
    			test = true;
    		time++;		
		}
		if ( (j+1 != row ) &&  direction == 1) {
			if ( (v_road[i][j+1] != 'O' &&  v_road[i][j+1] != 'V' &&  direction == 1  && ( test == false && !Maze::donthaveDirection( i, j) ) ) )  {
    			direction = 1;
    			success = Maze::setManyWay(i, j+1, direction, G , G_detect, success);
    			if ( (success == true &&  Maze::donthaveDirection( i, j )) || gtimes == G ){
    				return true;
				}
    				
			}  		
		}
		if ( j+1 != row){
			if ( (v_road[i][j+1] == 'O' ||  v_road[i][j+1] == 'V' || v_road[i][j+1] == 'G' ) &&  (direction == 1 ) ){// 從原本往右 變成往下去判斷是否有路 (direction=2)
				direction = 2;	
			}
		}
		else {
			if( direction == 1 )	
				direction = 2;
		}
		
		time = 0;
		while ( time < gtimes ){ // 這個while是去以防會一直找到相同G 
    		if ( Gx[time] == i+1 && Gy[time] == j )
    			test1 = true;
    		time++;		
		}
		if ( (i+1 != column) && direction == 2){
			if ( v_road[i+1][j] != 'O' &&  v_road[i+1][j] != 'V' && direction == 2 && ( test1 == false && !Maze::donthaveDirection( i, j) ) ){
				direction = 2;
			
				success = Maze::setManyWay(i+1, j , direction, G, G_detect, success);
				if ( ( success == true && Maze::donthaveDirection( i, j) ) || gtimes == G )
					return true;
			}
		}
		if ( i+1 != column ){
			if ( (v_road[i+1][j] == 'O' || v_road[i+1][j] == 'V' || v_road[i+1][j] == 'G') && (direction == 2) ) // 從原本往下 變成往左去判斷是否有路 (direction=3) 
			direction = 3;		
		}
		else{
			if( direction == 2 )
				direction = 3;
		}
		
		time = 0;
		while ( time < gtimes ){ // 這個while是去以防會一直找到相同G 
    		if ( (Gx[time] == i )&& Gy[time] == (j-1) )
    			test2 = true;
    		time++;		
		}
		if( (j-1 != -1) && direction == 3){
			if ( v_road[i][j-1] != 'O' &&  v_road[i][j-1] != 'V' && direction == 3 && ( test2 == false && !Maze::donthaveDirection( i, j) )) {
				direction = 3;
				success = Maze::setManyWay(i,j-1, direction, G, G_detect, success);
				if ( ( success == true && Maze::donthaveDirection( i, j) ) || gtimes == G ){
					return true;
				}
					
			}
		}
		
		if( j-1 != -1 ) {  
			if ( (v_road[i][j-1]=='V' || v_road[i][j-1] == 'O' || v_road[i][j-1] == 'G' ) && (direction == 3) ) // 從原本往左 變成往上去判斷是否有路 (direction=4) 
				direction = 4;
		}
		else {
			if ( direction == 3 )
				direction = 4;
		}
		
		time = 0;	
		while ( time < gtimes ){  // 這個while是去以防會一直找到相同G 
    		if ( Gx[time] == i-1 && Gy[time] == j )
    			test3 = true;
    		time++;		
		}
		
		if( (i-1 != -1) && direction == 4 ) { 
			if ( v_road[i-1][j] != 'O' && v_road[i-1][j] != 'V'  && direction == 4 && ( test3 == false && !Maze::donthaveDirection( i, j) ) ){
				direction = 4;
				success = Maze::setManyWay(i-1,j, direction, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
		}
		// 以下的四個if 是要判斷還有沒有路可走 
		if ( j+1 != row ){  // 判斷還有沒有路可走
			if ( (v_road[i][j+1] != 'O' && v_road[i][j+1] != 'V' && ( test == false && !Maze::donthaveDirection( i, j)  ) )) {
				success = Maze::setManyWay(i,j+1, 1, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
					
		}	
		if ( i+1 != column) { // 判斷還有沒有路可走
			if ( v_road[i+1][j] != 'O' && v_road[i+1][j] != 'V' && ( test1 == false && !Maze::donthaveDirection( i, j) ) )  {
				success = Maze::setManyWay(i+1,j, 2, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
				
		}
		
		if ( j-1 != -1) {  // 判斷還有沒有路可走
			if ( v_road[i][j-1] != 'O' && v_road[i][j-1] != 'V' && ( test2 == false && !Maze::donthaveDirection( i, j) ) ) {
				success = Maze::setManyWay(i,j-1, 3, G, G_detect, success);
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
				
		}
		
		if ( i-1 != -1 ){ // 判斷還有沒有路可走
			if ( v_road[i-1][j] != 'O' && v_road[i-1][j] != 'V' && ( test3 == false && !Maze::donthaveDirection( i, j) ) ){
				success = Maze::setManyWay(i-1,j, 4, G, G_detect, success);	
				if ( ( success == true  && Maze::donthaveDirection( i, j)) || gtimes == G )
					return true;
			}
				
		}
		if ( gtimes == G ){
			return true;
		}
		
			
		time = 0;	
		while ( time < gtimes ){  // 找尋周圍是否有已經找過的G  如果有，就代表那個方向也是死路
    		if ( ( Gx[time] == i && Gy[time] == j+1 ) ){
    			test = true;
			}
			if ( Gx[time] == i+1 && Gy[time] == j ) {
				test1 = true;
			}
			if( Gx[time] == i && Gy[time] == j-1 ) {
				test2 = true;
			}
			if ( Gx[time] == i-1 && Gy[time] == j )  {
				test3 = true;
			}
    			
    		time++;		
		}
		
		if ( j-1 < 0 ){ //周圍都是死路 所以程式return false 所以也要把 R路徑這個位置的 R 改成 E 
			if ( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test == true ) ){
				if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test3 == true ) ) {
					if ( i+1 == column ){
						r_road[i][j] = 'E'; // 把 R路徑這個位置的 R 改成 E 
						return false;  
					}
					else {
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test3 == true ) ){
							r_road[i][j] = 'E';
							return false; 
						}
						
					}
					
				}
			}
		}
		else {
			if ( ( v_road[i][j-1]=='V' || v_road[i][j-1] == 'O' || test2 == true ) ) {
				if  ( j+1 == row) {
					if ( i-1 < 0 ){
						if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
							r_road[i][j] = 'E';
							return false; 
						}
					}
					else{
						if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test3 == true) ) {
							if ( i+1 == column ){
								r_road[i][j] = 'E';
								return false; 
							} 
							else {
								if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
									r_road[i][j] = 'E';
									return false;  
								}
								
							}
							
						} 	
					}
					
				}
				else{
					if( ( v_road[i][j+1] == 'V' || v_road[i][j+1] == 'O' || test == true)){
					
						if ( i-1 < 0 ){
							if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
								r_road[i][j] = 'E';
								return false; 
							} 		
						}
						else{
							if ( ( v_road[i-1][j]=='V' || v_road[i-1][j] == 'O' || test3 == true ) ) {
								if ( i+1 == column ){
									r_road[i][j] = 'E';
									return false;
								}
								else{
									if ( (v_road[i+1][j]=='V' || v_road[i+1][j] == 'O' || test1 == true) ){
										r_road[i][j] = 'E';
										return false;   
									}
										
								}
							}
						}
					}
				}
			}
				
		}
		
	}
    
}
bool Maze::load( string fileName ) {
	int row = 0,column = 0;
	string file = "input" + fileName + ".txt";  
	ifstream ifs( file.c_str() );//打開檔案
	int i = 0;
	int j = 0;
    if ( ifs ){  
    	 ifs >> row; 
   		 ifs >> column; 
   		 Maze::set_row_col( row, column);  // 把所得到的row column 存起來 
		for ( i = 0; i <  column ; i++) {  //將迷宮存入陣列中
			for ( j = 0 ; j < row ; j++) {
				ifs >> Maze::s[i][j];
				Maze::v_road[i][j] = Maze::s[i][j];
				Maze::r_road[i][j] = Maze::v_road[i][j];
			}
		} 
    	ifs.close(); // 關閉檔案 
        return true; 
    }
    cout <<"\n"; 
    cout << file << " does not exist!" << endl;

	return false;	
}


int main() {
	int command = 0;
	int moreGoals = 0;
	int G_detect = 0;  
	do {
		Maze aMaze;
		string fileName;
    	
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "********************";
		cout << endl << "Input a command(0, 1, 2): ";
		cin >> command;
		if ( ( command == 1 ) || ( command == 2) ) {
			cout << endl << "Input a file number: ";
			cin >> fileName;
			if ( command == 1 ) {
			
				if ( aMaze.load(fileName)) { 
					if (aMaze.setManyWay( 0, 0 , 1, 1,1,0) ) {  //找的到G  就依序印出 V路徑 和 R路徑  
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}
			
							cout << "\n";
						} 
					
						cout << "\n";
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printr( i, j );
							}	
			
							cout << "\n";
						} 	
						cout << "\n";
						
					}
					else { // 找不到G 只印出 V路徑
					
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}	
			
							cout << "\n";
						} 
					}			
				}
			}
			
			else if ( command == 2 ) {
				if ( aMaze.load(fileName)) {
					cout << endl << "Number of G (goals): ";
					cin >> moreGoals ; //輸入我要找的G個數 
					G_detect = moreGoals;
					if ( aMaze.setManyWay( 0, 0 , 1, moreGoals, G_detect, 0) ) {  //如果能找出符合我要找的G個數就依序印出 V路徑 和 R路徑
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}
			
							cout << "\n";
						} 
					
						cout << "\n";
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printr( i, j );
							}	
			
							cout << "\n";
						} 
						cout << "\n";	
						
					}
					else {  //如果不能找出符合我要找的G個數 只印出V路徑 
						for ( int i = 0; i <  aMaze.Get_column() ; i++) { 
							for ( int j = 0 ; j <  aMaze.Get_row() ; j++) {
								aMaze.printv( i, j );
							}	
							cout << "\n";
							
						} 
						cout << "\n";
					}		
				}
			}
		}
		else if ( !command )
			break;
		else
			cout << endl << "Command does not exist!" << endl;
					
		
	} while(true);
	system( "pause" );
	return 0;

}
