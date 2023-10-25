#include <iostream> 
#include <vector>
#include <string.h> 
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <tgmath.h>

using namespace std;
struct dt{
	char sign ;
	char lastdir ;
};

class mission1 {
	private :
		vector<vector<dt>> dataitem; //�G���ʺA�}�C 
	public :
		void Readfile( string filenum ) { 
			ifstream text ;
			string useless ;
			char letter ;
			int row, column ;
			string filename = "input" + filenum +".txt" ;
			dataitem.clear(); // �M�� 

			
			text.open( filename.c_str() ) ; // open text  
			while( text.fail() ) {
				cout << endl<< "### " << filename << ".txt does not exist! ###" ;
				cout << endl<< "Input a file number (e.g., 100, 101, 102, ...): " ;
				cin >> filenum ;
				filename = "input" + filenum +".txt" ;
				text.open( filename.c_str() ) ;
			} // while
			
			text >> row >> column ;
			dataitem.resize( column ) ;
			for ( int i = 0 ; i < column ; i++) {
				for ( int j = 0 ; j < row ; j++ ){
					text >> letter ;
					dt temp ;
					temp.sign = letter ;
					temp.lastdir = 'l' ;
					dataitem[i].push_back( temp ) ;
				} // for
				
			} // for
			
			
			text.clear() ;
			text.close() ;
			
			/*for( int j = 0 ; j < row ; j++ ) {
				for( int i = 0 ; i < column ; i++ )
					cout << dataitem[j][i];
				cout << endl;
				�ˬdŪ�� 
			*/ 	
		} // Readfile
		
	
		
		void IfHaveOther( int column, int row ) {
		 		
			if( row+1 < dataitem[column].size() && ( dataitem[column][row+1].sign == 'V' || dataitem[column][row+1].sign == 'G' ) ){ //�k�� 
				
				dataitem[column][row].sign = 'R' ;
				
				if( dataitem[column][row+1].sign == 'G' )
				
					printTruePath();
					
				else {
				
					dataitem[column][row+1].lastdir = 'l' ;	
					GoShortestPath( column, row+1, 'r' );
				} // else
				
			} // if
			
			else if( column+1 < dataitem.size() && ( dataitem[column+1][row].sign == 'V' || dataitem[column+1][row].sign == 'G') ){ //�U�� 
				dataitem[column][row].sign = 'R' ;
				if(dataitem[column+1][row].sign == 'G' )
					printTruePath();
				else{
				
					dataitem[column+1][row].lastdir = 'u' ;
					GoShortestPath( column+1, row, 'd' );
				} // else
				
			} // else if
			
			else if( row-1 >= 0 && ( dataitem[column][row-1].sign == 'V' || dataitem[column][row-1].sign == 'G' ) ){ //���� 
				dataitem[column][row].sign = 'R' ;
				if( dataitem[column][row-1].sign == 'G' )
					printTruePath();
				else{
					dataitem[column][row-1].lastdir = 'r' ;			   
					GoShortestPath( column, row-1, 'l' );	
				} // else
					
			} // else if
			
			else if( column-1 >= 0 && ( dataitem[column-1][row].sign == 'V' || dataitem[column-1][row].sign == 'G' ) ){	 //�W��
				dataitem[column][row].sign = 'R' ;
				if( dataitem[column-1][row].sign == 'G' )
					printTruePath();
					
				else{
					dataitem[column-1][row].lastdir = 'd' ;	
					GoShortestPath( column-1, row, 'u' );	
				} // else
					
			} // else if
			
			else{																   // �S����^�W�@�� 
				if(dataitem[column][row].lastdir == 'l' ) 
					IfHaveOther( column, row-1 ) ;
				else if (dataitem[column][row].lastdir == 'u' ) 
					IfHaveOther( column-1, row ) ; 
				else if (dataitem[column][row].lastdir == 'r' ) 
					IfHaveOther( column, row+1 ) ; 
				else if (dataitem[column][row].lastdir == 'd' ) 
					IfHaveOther( column+1, row ) ; 
			}
		}
		
		void GoShortestPath(int column, int row, char direction) {
			
			 
			if( direction == 'r') {  // �e�@����V�k
			 	
				if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
		 			printTruePath();
		 			return ;
				} //if	
				else if( column+1 < dataitem.size() &&  dataitem[column+1][row].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
			 		printTruePath();
		 			return ;
				
				 } // else if
				 			 
			 	if( dataitem[column][row+1].sign != 'V' || row+1 >= dataitem[column].size() ) {// ���O'V'�ΨS��k���k 
			 		if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'R' )
			 			IfHaveOther( column, row );
			 		else
						GoShortestPath( column, row, 'd' ) ; // recursion���U	
				} // if
				 
		 		else {
					dataitem[column][row].sign = 'R' ;
		 			GoShortestPath( column, row+1, 'r' ) ; // recursion���k
		 			
		 		} // else
				
			 } // if
			 
			 else if( direction == 'd') { // �e�@����V�U
			 		
				if( column+1 < dataitem.size() &&  dataitem[column+1][row].sign == 'G' ){
					
			 		dataitem[column][row].sign = 'R' ;
			 		printTruePath();
		 			return ;
				} //if
				
				else if( row-1 >= 0 && dataitem[column][row-1].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
		 			printTruePath();
		 			return ;
				 } // else if
				 			
			 	if( column +1 >= dataitem.size() || dataitem[column+1][row].sign != 'V' ){// ���O'V'�ΨS��k���U 
			 		if( column +1 < dataitem.size() && dataitem[column+1][row].sign == 'R' )
			 			IfHaveOther(column, row);
			 		else	
						GoShortestPath( column, row, 'l' ) ; // recursion����			 
				} // if
				
		 		else {
		 			dataitem[column][row].sign = 'R' ;
					GoShortestPath( column+1, row, 'd' ) ; // recursion���U
				} // if
		 				
				
			 } // else if
				 
			else if( direction == 'l') {// �e�@����V�� 
				
				if( row-1 >= 0 && dataitem[column][row-1].sign == 'G' ){
		 			dataitem[column][row].sign = 'R' ;
		 			printTruePath();
		 			return ;
				} // if
				
				else if( column-1 >= 0 &&  dataitem[column-1][row].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
					
		 			printTruePath();
		 			return ;
				} // else if 				 
		 		if( row-1 < 0 || dataitem[column][row-1].sign != 'V' ){  //���O'V' �Ϊ̨S��k���� 
					if( row-1 >= 0 && dataitem[column][row-1].sign == 'R' )
						IfHaveOther( column, row) ;
					else
		 				GoShortestPath( column, row, 'u' ) ; // recursion���W 
				}
				else {
		 			dataitem[column][row].sign = 'R' ;
					GoShortestPath( column, row-1, 'l' ) ; // recursion���� 
				} // else
		 				
				
				 	
			 } // else if
				 
			else if( direction == 'u') {  // �e�@����V�W
				 	
				if( column-1 >= 0 &&  dataitem[column-1][row].sign == 'G'  ){
					
					dataitem[column][row].sign = 'R' ;
		 			printTruePath();
		 			return ;
			 	} // else if
			 	
			 	else if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
		 		
		 			printTruePath();
		 			return ;
			 	} // else if
			 	
		 		if(column - 1 < 0 || dataitem[column-1][row].sign != 'V'  ) {// ���O'V' �Ϊ̨S��k���W 
		 			if( column - 1 >= 0 && dataitem[column-1][row].sign == 'R' )
				 		IfHaveOther( column, row );
				 	else
				 		GoShortestPath( column, row, 'r' ) ; // recursion���k 
				} // if
				
				else  {
					dataitem[column][row].sign = 'R' ;
					GoShortestPath( column-1, row, 'u' ) ; // recursion���W 
				} // else if
		 		
			 } // else if
			
		
		}
		
		void IfHaveRoad( int column, int row ) {
			
			if( column+ row < 0 ){ // �פ� 
				print() ;
				return ;
			} // if
		 		
			if( row+1 < dataitem[column].size() && ( dataitem[column][row+1].sign == 'E' || dataitem[column][row+1].sign == 'G' ) ){ //�k�� 
				dataitem[column][row+1].lastdir = 'l' ;	
				FindRoad( column, row+1, 'r' );
			} // if
			
			else if( column+1 < dataitem.size() && ( dataitem[column+1][row].sign == 'E' || dataitem[column+1][row].sign == 'G') ){ //�U�� 
				dataitem[column+1][row].lastdir = 'u' ;
				FindRoad( column+1, row, 'd' );
			} // else if
			
			else if( row-1 >= 0 && ( dataitem[column][row-1].sign == 'E' || dataitem[column][row-1].sign == 'G' ) ){ //���� 
				dataitem[column][row-1].lastdir = 'r' ;			   
				FindRoad( column, row-1, 'l' );
			} // else if
			
			else if( column-1 >= 0 && ( dataitem[column-1][row].sign == 'E' || dataitem[column-1][row].sign == 'G' ) ){	 //�W��
				dataitem[column-1][row].lastdir = 'd' ;		   
				FindRoad( column-1, row, 'u' );	
			} // else if
			
			else{																   // �S����^�W�@�� 
				if(dataitem[column][row].lastdir == 'l' ) 
					IfHaveRoad( column, row-1 ) ;
				else if (dataitem[column][row].lastdir == 'u' ) 
					IfHaveRoad( column-1, row ) ; 
				else if (dataitem[column][row].lastdir == 'r' ) 
					IfHaveRoad( column, row+1 ) ; 
				else if (dataitem[column][row].lastdir == 'd' ) 
					IfHaveRoad( column+1, row ) ; 
			}
		}
		 
	 
		void FindRoad( int column, int row, char direction ) { // direction�ΥH�����W�@������V r=�k d=�U l=�� u=�W  lastdir �����W�@���I 
		 	if( dataitem[column][row].sign == 'G' ){
		 		print();
		 		GoShortestPath( 0, 0, 'r' );
		 		return ;
			 }
		 		
		 	
		 	if( direction == 'r') {  // �e�@����V�k
			 	dataitem[column][row].sign = 'V' ;				 
			 	if( dataitem[column][row+1].sign == 'O' || (row+1 >= dataitem[column].size() || dataitem[column][row+1].sign == 'V' )) {// �J��'O'��'V'�ΨS��k���k 
					if( row + 1 < dataitem[column].size() && dataitem[column][row+1].sign == 'V')
						IfHaveRoad( column, row ) ; // ��|�P�O�_���� 
					else
						FindRoad( column, row, 'd' ) ; // recursion���U	
				}
		 		else {
				 	
				 	dataitem[column][row+1].lastdir = 'l' ;
		 			FindRoad( column, row+1, 'r' ) ; // recursion���k
		 		} // else
				
			 } // if
			 
			 else if( direction == 'd') { 
			 	dataitem[column][row].sign = 'V' ;				 // �e�@����V�U
			 	if( column +1 >= dataitem.size() || (dataitem[column+1][row].sign == 'O' || dataitem[column+1][row].sign == 'V' ) ){// �J��'O'��'V'�ΨS��k���U 
				 
				 	if( column+1< dataitem.size() && dataitem[column+1][row].sign == 'V')
				 		
						IfHaveRoad( column, row) ;
					else
						FindRoad( column, row, 'l' ) ; // recursion����
					
						 
				} // if
				
		 		else {
		 			dataitem[column+1][row].lastdir = 'u' ;
					FindRoad( column+1, row, 'd' ) ; // recursion���U
				} // if
		 				
				
			 } // else if
				 
			else if( direction == 'l') {
				dataitem[column][row].sign = 'V' ; 				 // �e�@����V�� 
		 		if( row-1 < 0 || (dataitem[column][row-1].sign == 'O'|| dataitem[column][row-1].sign == 'V') ){  //�J��'O'��'V' �Ϊ̨S��k���� 
		 			if( row -1 >= 0 && dataitem[column][row-1].sign == 'V')
 						IfHaveRoad( column, row ) ;
						
					else
		 				FindRoad( column, row, 'u' ) ; // recursion���W 
				}
				else {
		 			
		 			dataitem[column][row-1].lastdir = 'r' ;
					FindRoad( column, row-1, 'l' ) ; // recursion���� 
				} // else
		 				
				
				 	
			 } // else if
				 
			else if( direction == 'u') { 
				dataitem[column][row].sign = 'V' ;				 // �e�@����V�W 
		 		if(column - 1 < 0 || (dataitem[column-1][row].sign == 'V' || dataitem[column-1][row].sign == 'O') ) {// �J��'O'��'V' �Ϊ̨S��k���W 
		 			if( column -1 >= 0 && dataitem[column-1][row].sign == 'V')
						 
						IfHaveRoad( column, row ) ;
					else
				 		FindRoad( column, row, 'r' ) ; // recursion���k 
				} // if
				
				else  {
		 			
		 			dataitem[column-1][row].lastdir = 'd' ;
					FindRoad( column-1, row, 'u' ) ; // recursion���W 
				} // else if
		 		
			 } // else if
			 
		}
			 	

	void printTruePath(){
		for( int j = 0 ; j < dataitem.size() ; j++ ) {  
				for( int i = 0 ; i < dataitem[0].size()  ; i++ ){
					if( dataitem[j][i].sign == 'V' )
						cout << 'E' ;
					else
						cout << dataitem[j][i].sign;
					} //for
					
				cout << endl;
		} 
		
		cout << endl;
	}	
		
	void print(){
		for( int j = 0 ; j < dataitem.size() ; j++ ) {  
				for( int i = 0 ; i < dataitem[0].size()  ; i++ )
					cout << dataitem[j][i].sign;
				cout << endl;
		} 
		
		cout << endl;
	} // Print 
	
	
};

class mission2 {
	private :
		char a = 'F' ;
		int num2 = 0 ;
		int num = 0 ;
		vector<vector<dt>> dataitem; //�G���ʺA�}�C 
		vector<vector<dt>> copy ;
	public :
		void Readfile( string filenum ) { 
			ifstream text ;
			string useless ;
			char letter ;
			int row, column ;
			string filename = "input" + filenum +".txt" ;
			dataitem.clear(); // �M�� 
			copy.clear() ;
			
			text.open( filename.c_str() ) ; // open text  
			while( text.fail() ) {
				cout << endl<< "### " << filename << ".txt does not exist! ###" ;
				cout << endl<< "Input a file number (e.g., 100, 101, 102, ...): " ;
				cin >> filenum ;
				filename = "input" + filenum +".txt" ;
				text.open( filename.c_str() ) ;
			} // while
			
			text >> row >> column ;
			dataitem.resize( column ) ;
			copy.resize( column ) ;
			for ( int i = 0 ; i < column ; i++) {
				for ( int j = 0 ; j < row ; j++ ){
					text >> letter ;
					dt temp, temp2 ;
					temp.sign = letter ;
					temp.lastdir = 'l' ;
					temp2.sign = letter ;
					temp2.lastdir = 'l' ;
					dataitem[i].push_back( temp ) ;
					copy[i].push_back( temp2 ) ;
				} // for
				
			} // for
			
			
			text.clear() ;
			text.close() ;
				
		} // Readfile
		
		void HowMuchToFind(){
			cout << "Number of G (goals): " ;
			cin >> num ;
			num2 = num ;
			FindRoad( 0, 0, 'r' ) ;
		} // HowMuchToFind()
		
		void IfHaveOther( int column, int row ) {
		 	
			if( row+1 < dataitem[column].size() && ( dataitem[column][row+1].sign == 'V' || dataitem[column][row+1].sign == 'G' ) ){ //�k�� 
				
				if(dataitem[column][row].sign != 'B' ){
					
					dataitem[column][row].sign = 'R' ;
				
				}
					
			
				
				dataitem[column][row+1].lastdir = 'l' ;	
				GoShortestPath( column, row+1, 'r' );
				
			} // if
			
			else if( column+1 < dataitem.size() && ( dataitem[column+1][row].sign == 'V' || dataitem[column+1][row].sign == 'G') ){ //�U�� 
				
				
				if(dataitem[column][row].sign != 'B' ){
					
					dataitem[column][row].sign = 'R' ;
				}
					
				dataitem[column+1][row].lastdir = 'u' ;
				GoShortestPath( column+1, row, 'd' );
				
				
			} // else if
			
			else if( row-1 >= 0 && ( dataitem[column][row-1].sign == 'V' || dataitem[column][row-1].sign == 'G' ) ){ //���� 
				
				if(dataitem[column][row].sign != 'B' ){
					
					dataitem[column][row].sign = 'R' ;
					
				}
					
				
				dataitem[column][row-1].lastdir = 'r' ;			   
				GoShortestPath( column, row-1, 'l' );	
				
					
			} // else if
			
			else if( column-1 >= 0 && ( dataitem[column-1][row].sign == 'V' || dataitem[column-1][row].sign == 'G' ) ){	 //�W��
			
				if(dataitem[column][row].sign != 'B' ) {
					
					dataitem[column][row].sign = 'R' ;
				}
					
				
			
				dataitem[column-1][row].lastdir = 'd' ;	
				GoShortestPath( column-1, row, 'u' );	
						
			} // else if
			
			else{				
																   // �S����^�W�@�� 
				if( dataitem[column][row].sign == 'B'  ) {
					int i = 0 ;
					if( row+1 >= dataitem[column].size() || dataitem[column][row+1].sign == 'O')
						i++;
					if( column+1 >= dataitem.size() || dataitem[column+1][row].sign == 'O')
						i++;	
					if( row-1 < 0 || dataitem[column][row-1].sign == 'O')
						i++;
					if( column-1 < 0  || dataitem[column-1][row].sign == 'O')
						i++;
						
					if( i < 3)
						a = 'R' ;
				}
				
				else
					dataitem[column][row].sign = a ;
				
				
				
				if(dataitem[column][row].lastdir == 'l' ) 
					IfHaveOther( column, row-1 ) ;
				else if (dataitem[column][row].lastdir == 'u' ) 
					IfHaveOther( column-1, row ) ; 
				else if (dataitem[column][row].lastdir == 'r' ) 
					IfHaveOther( column, row+1 ) ; 
				else if (dataitem[column][row].lastdir == 'd' ) 
					IfHaveOther( column+1, row ) ; 
			}
		}
		
		void GoShortestPath(int column, int row, char direction) {
			if ( dataitem[column][row].sign == 'G' ){
				dataitem[column][row].sign = 'B' ;
				a = 'F' ;
				num2--;
				if( num2 == 0 ){
					printTruePath() ;
					return ;
				} // if	
				
			} // if
			
				
			
			if( direction == 'r') {  // �e�@����V�k
			 	
				/*if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
					num2--;
					GoShortestPath( column, row+1, 'r' ) ;
		 			//printTruePath();
		 			return ;
				} //if	
				else if( column+1 < dataitem.size() &&  dataitem[column+1][row].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
					num2--;
					GoShortestPath( column+1, row, 'r' ) ;
			 		//printTruePath();
		 			return ;
				
				 } // else if*/ 
				 			 
			 	if( dataitem[column][row+1].sign != 'V' || row+1 >= dataitem[column].size() ) {// ���O'V'�ΨS��k���k 
			 		if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'R' )
			 			IfHaveOther( column, row );
			 		else if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'G' ) {
		 				dataitem[column][row].sign = 'R' ;
		 				GoShortestPath( column, row+1, 'r' ) ;
		 				dataitem[column][row+1].lastdir = 'l' ;
					 } // else if
					
					else if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'B' ){
						
						IfHaveOther( column, row );
					}
			 			
					 
			 		else
						GoShortestPath( column, row, 'd' ) ; // recursion���U	
				} // if
				 
		 		else {
		 			if( dataitem[column][row].sign != 'B' )
						dataitem[column][row].sign = 'R' ;
					dataitem[column][row+1].lastdir = 'l' ;
					
		 			GoShortestPath( column, row+1, 'r' ) ; // recursion���k
		 			
		 			
		 		} // else
				
			 } // if
			 
			 else if( direction == 'd') { // �e�@����V�U
			 		
				/*if( column+1 < dataitem.size() &&  dataitem[column+1][row].sign == 'G' ){
					
			 		dataitem[column][row].sign = 'R' ;
			 		num2--;
			 		GoShortestPath( column+1, row, 'r' ) ;
			 		//printTruePath();
		 			return ;
				} //if
				
				else if( row-1 >= 0 && dataitem[column][row-1].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
					num2--;
					GoShortestPath( column, row-1, 'r' ) ;
		 			//printTruePath();
		 			return ;
				 } // else if*/
				 			
			 	if( column +1 >= dataitem.size() || dataitem[column+1][row].sign != 'V' ){// ���O'V'�ΨS��k���U 
			 		if( column +1 < dataitem.size() && dataitem[column+1][row].sign == 'R' )
			 			IfHaveOther(column, row);
			 		else if( column +1 < dataitem.size() && dataitem[column+1][row].sign == 'G' ) {
		 				dataitem[column][row].sign = 'R' ;
		 				dataitem[column+1][row].lastdir = 'u' ;
		 				GoShortestPath( column+1, row, 'd' ) ;
					 } // else if
					else if( column +1 < dataitem.size() && dataitem[column+1][row].sign == 'B' )
			 			IfHaveOther(column, row);
			 		else	
						GoShortestPath( column, row, 'l' ) ; // recursion����			 
				} // if
				
		 		else {
		 			if( dataitem[column][row].sign != 'B' )
						dataitem[column][row].sign = 'R' ;
					dataitem[column+1][row].lastdir = 'u' ;
					GoShortestPath( column+1, row, 'd' ) ; // recursion���U
				} // if
		 				
				
			 } // else if
				 
			else if( direction == 'l') {// �e�@����V�� 
				
			/*	if( row-1 >= 0 && dataitem[column][row-1].sign == 'G' ){
		 			dataitem[column][row].sign = 'R' ;
		 			num2--;
		 			GoShortestPath( column, row-1, 'r' ) ;
		 			//printTruePath();
		 			return ;
				} // if
				
				else if( column-1 >= 0 &&  dataitem[column-1][row].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
					num2--;
					GoShortestPath( column-1, row, 'r' ) ;
		 			//printTruePath();
		 			return ;
				} // else if 	*/
							 
		 		if( row-1 < 0 || dataitem[column][row-1].sign != 'V' ){  //���O'V' �Ϊ̨S��k���� 
					if( row-1 >= 0 && dataitem[column][row-1].sign == 'R' ){
						
						IfHaveOther( column, row) ;
					}
					else if( row-1 >= 0 && dataitem[column][row-1].sign == 'G' ) {
		 				dataitem[column][row].sign = 'R' ;
		 				dataitem[column][row-1].lastdir = 'r' ;
		 				GoShortestPath( column, row-1, 'l' ) ;
					 } // else if
					 
					else if( row-1 >= 0 && dataitem[column][row-1].sign == 'B' )
						IfHaveOther( column, row) ;
					else
		 				GoShortestPath( column, row, 'u' ) ; // recursion���W 
				}
				else {
		 			if( dataitem[column][row].sign != 'B' )
						dataitem[column][row].sign = 'R' ;
					dataitem[column][row-1].lastdir = 'r' ;
					GoShortestPath( column, row-1, 'l' ) ; // recursion���� 
				} // else
		 				
				
				 	
			 } // else if
				 
			else if( direction == 'u') {  // �e�@����V�W
				 	
				/*if( column-1 >= 0 &&  dataitem[column-1][row].sign == 'G'  ){
					
					dataitem[column][row].sign = 'R' ;
					num2--;
					GoShortestPath( column-1, row, 'r' ) ;
		 			//printTruePath();
		 			return ;
			 	} // else if
			 	
			 	else if( row+1 < dataitem[column].size() && dataitem[column][row+1].sign == 'G' ){
					dataitem[column][row].sign = 'R' ;
					num2--;
		 			GoShortestPath( column, row+1, 'r' ) ;
		 			//printTruePath();
		 			return ;
			 	} // else if*/
			 	
		 		if(column - 1 < 0 || dataitem[column-1][row].sign != 'V'  ) {// ���O'V' �Ϊ̨S��k���W 
		 			if( column - 1 >= 0 && dataitem[column-1][row].sign == 'R' )
				 		IfHaveOther( column, row );
				 	else if(  column - 1 >= 0 && dataitem[column-1][row].sign == 'G' ) {
		 				dataitem[column][row].sign = 'R' ;
		 				dataitem[column-1][row].lastdir = 'd' ;
		 				GoShortestPath( column-1, row, 'u' ) ;
					 } // else if
					
					else if( column - 1 >= 0 && dataitem[column-1][row].sign == 'B' )
				 		IfHaveOther( column, row );
				 	else
				 		GoShortestPath( column, row, 'r' ) ; // recursion���k 
				} // if
				
				else  {
					if( dataitem[column][row].sign != 'B' )
						dataitem[column][row].sign = 'R' ;
					dataitem[column-1][row].lastdir = 'd' ;
					GoShortestPath( column-1, row, 'u' ) ; // recursion���W 
				} // else if
		 		
			 } // else if
			
		
		}
		
		void IfHaveRoad( int column, int row ) {
			
			if( column+ row < 0 ){ // �פ� 
				print() ;
				return ;
			} // if
		 		
			if( row+1 < dataitem[column].size() && ( dataitem[column][row+1].sign == 'E' || dataitem[column][row+1].sign == 'G' ) ){ //�k�� 
				dataitem[column][row+1].lastdir = 'l' ;	
				FindRoad( column, row+1, 'r' );
			} // if
			
			else if( column+1 < dataitem.size() && ( dataitem[column+1][row].sign == 'E' || dataitem[column+1][row].sign == 'G') ){ //�U�� 
				dataitem[column+1][row].lastdir = 'u' ;
				FindRoad( column+1, row, 'd' );
			} // else if
			
			else if( row-1 >= 0 && ( dataitem[column][row-1].sign == 'E' || dataitem[column][row-1].sign == 'G' ) ){ //���� 
				dataitem[column][row-1].lastdir = 'r' ;			   
				FindRoad( column, row-1, 'l' );
			} // else if
			
			else if( column-1 >= 0 && ( dataitem[column-1][row].sign == 'E' || dataitem[column-1][row].sign == 'G' ) ){	 //�W��
				dataitem[column-1][row].lastdir = 'd' ;		   
				FindRoad( column-1, row, 'u' );	
			} // else if
			
			else{																   // �S����^�W�@�� 
				if(dataitem[column][row].lastdir == 'l' ) 
					IfHaveRoad( column, row-1 ) ;
				else if (dataitem[column][row].lastdir == 'u' ) 
					IfHaveRoad( column-1, row ) ; 
				else if (dataitem[column][row].lastdir == 'r' ) 
					IfHaveRoad( column, row+1 ) ; 
				else if (dataitem[column][row].lastdir == 'd' ) 
					IfHaveRoad( column+1, row ) ; 
			}
		}
		 
	 
		void FindRoad( int column, int row, char direction ) { // direction�ΥH�����W�@������V r=�k d=�U l=�� u=�W  lastdir �����W�@���I 
		 	if( dataitem[column][row].sign == 'G' ){
		 		num--;
		 		if( num == 0 ) {
					print();
		 			GoShortestPath( 0, 0, 'r' );
		 			return ;
				 } // if
		 		
			 } // if
		 		
		 	
		 	if( direction == 'r') {  // �e�@����V�k
			 	dataitem[column][row].sign = 'V' ;				 
			 	if( dataitem[column][row+1].sign == 'O' || (row+1 >= dataitem[column].size() || dataitem[column][row+1].sign == 'V' )) {// �J��'O'��'V'�ΨS��k���k 
					if( row + 1 < dataitem[column].size() && dataitem[column][row+1].sign == 'V')
						IfHaveRoad( column, row ) ; // ��|�P�O�_���� 
					else
						FindRoad( column, row, 'd' ) ; // recursion���U	
				}
		 		else {
				 	
				 	dataitem[column][row+1].lastdir = 'l' ;
		 			FindRoad( column, row+1, 'r' ) ; // recursion���k
		 		} // else
				
			 } // if
			 
			 else if( direction == 'd') { 
			 	dataitem[column][row].sign = 'V' ;				 // �e�@����V�U
			 	if( column +1 >= dataitem.size() || (dataitem[column+1][row].sign == 'O' || dataitem[column+1][row].sign == 'V' ) ){// �J��'O'��'V'�ΨS��k���U 
				 
				 	if( column+1< dataitem.size() && dataitem[column+1][row].sign == 'V')
				 		
						IfHaveRoad( column, row) ;
					else
						FindRoad( column, row, 'l' ) ; // recursion����
					
						 
				} // if
				
		 		else {
		 			dataitem[column+1][row].lastdir = 'u' ;
					FindRoad( column+1, row, 'd' ) ; // recursion���U
				} // if
		 				
				
			 } // else if
				 
			else if( direction == 'l') {
				dataitem[column][row].sign = 'V' ; 				 // �e�@����V�� 
		 		if( row-1 < 0 || (dataitem[column][row-1].sign == 'O'|| dataitem[column][row-1].sign == 'V') ){  //�J��'O'��'V' �Ϊ̨S��k���� 
		 			if( row -1 >= 0 && dataitem[column][row-1].sign == 'V')
 						IfHaveRoad( column, row ) ;
						
					else
		 				FindRoad( column, row, 'u' ) ; // recursion���W 
				}
				else {
		 			
		 			dataitem[column][row-1].lastdir = 'r' ;
					FindRoad( column, row-1, 'l' ) ; // recursion���� 
				} // else
		 				
				
				 	
			 } // else if
				 
			else if( direction == 'u') { 
				dataitem[column][row].sign = 'V' ;				 // �e�@����V�W 
		 		if(column - 1 < 0 || (dataitem[column-1][row].sign == 'V' || dataitem[column-1][row].sign == 'O') ) {// �J��'O'��'V' �Ϊ̨S��k���W 
		 			if( column -1 >= 0 && dataitem[column-1][row].sign == 'V')
						 
						IfHaveRoad( column, row ) ;
					else
				 		FindRoad( column, row, 'r' ) ; // recursion���k 
				} // if
				
				else  {
		 			
		 			dataitem[column-1][row].lastdir = 'd' ;
					FindRoad( column-1, row, 'u' ) ; // recursion���W 
				} // else if
		 		
			 } // else if
			 
		}
			 	

	void printTruePath(){
		for( int j = 0 ; j < dataitem.size() ; j++ ) {  
				for( int i = 0 ; i < dataitem[0].size()  ; i++ ){
					if( dataitem[j][i].sign == 'V' || dataitem[j][i].sign == 'F' )
						cout << 'E' ;
					else if ( dataitem[j][i].sign == 'B' )
						cout << 'G' ;
					else
						cout << dataitem[j][i].sign;
					} //for
					
				cout << endl;
		} 
		
		cout << endl;
	}	
		
		void print(){
		for( int j = 0 ; j < dataitem.size() ; j++ ) {  
				for( int i = 0 ; i < dataitem[0].size()  ; i++ ) {
				
					if( copy[j][i].sign == 'G' )
						dataitem[j][i].sign = 'G' ;
					cout << dataitem[j][i].sign;
				} // for
				
				cout << endl;
		} 
		
		cout << endl;
	} // Print 
	
	
};
int main() {
	string command  ;
	int num ;
	int operation ;
	mission1 one ;
	mission2 two ;
	
	bool end = false ;
	string filenum ;
	command = atoi( command.c_str() ) ;
                           		
	while( end == 0 ) { 
		cout << endl << "*** Path Finding ***" ;
		cout << endl << "* 0. QUIT          *" ;
		cout << endl << "* 1. One goal      *" ;
		cout << endl << "* 2. More goals    *" ;
		cout << endl << "********************" ;
		
		cout << endl << "Input a command( 0, 1, 2 ): " ;
		
		cin >> command ;
		operation = atoi(command.c_str());
	                                		
        switch (operation)
        {	case 0:
        		end = true ;
		    	break;
            case 1:	
            	cout << endl<< "Input a file number (e.g., 100, 101, 102, ...): " ;
            	cin >> filenum ;
            	one.Readfile( filenum ) ; // read file function
            	one.FindRoad( 0, 0, 'r' ) ;
            	//one.print();
			
                break;
            case 2:	
            	cout << endl<< "Input a file number (e.g., 100, 101, 102, ...): " ;
            	cin >> filenum ;
            	two.Readfile( filenum ) ;
            	two.HowMuchToFind() ;
            	
                break;
            default: cout << endl << "Command does not exist!" << endl;
        }	// end switch
        
    }                             			
    system("pause");                                    			// pause the execution
    return 0;
}
