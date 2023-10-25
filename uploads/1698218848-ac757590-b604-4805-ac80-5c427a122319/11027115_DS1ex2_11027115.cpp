//11027115_王敬豪 

#include <iostream> //in out
#include <cstdlib>
#include <vector> // vector
#include <iomanip> // setw
#include <math.h> //sqrt
#include <fstream>
#include <string> 
#include <utility> // pair

#define MAX_LEN   235
#define no 0
#define oor 1
#define oand 2 

using namespace std ;

struct Token{	// 存後序的Node 
	char token = '\0' ;
	Token * next = NULL ;	// 下一個 
};

struct Token_or{	// 存運算子的Node 
	char token = '\0' ;
	int num = 0 ;	// 每個運算子的優先順序 
	Token_or * next = NULL ;	// 下一個 
	Token_or * pre = NULL ;		// 前一個 
};

// 後序的 
Token * head = NULL ;
Token * now = NULL ;
// 運算子的 
Token_or * Oor = NULL ;
Token_or * oorcur = NULL ;

void write() {
	
	now = head ;
	cout << "Postfix expression: " ;

	while ( now -> next != NULL ) {
		if ( now->token >= '0' && now->token <= '9' )	cout << now -> token ;	// 數字直接印出 
		else if ( now->token == ' ' )	cout << ", "  ;		// 用空格代表要逗號 
		else if (  now->token != '+' ||  now->token != '-' ||  now->token != '*' ||  now->token != '/'){	// 運算子的部分 
		
			cout << now->token ;	// 先印出 
			if ( now->next->token != '\0' )	{	 	// 確認下一格有東西 
			
				if ( now -> next->token == ' ' ){ 	// 如果是運算子接括號 
													// 要將括號省略掉 所以直接跳下一個 
					now = now ->next ;							
					if ( now -> next-> token != '\0') 	cout << ", " ;	// 如果是\0 代表是最後一個 不需要逗號了 
				}		
			}					
		}
		now = now -> next ;		// 下一個 
	}
	cout << endl ;	// 換行 
}

bool legal( string input ) { // 限用的文數字符號 
	for ( int i = 0 ; i < input.length() ; i++ ) {
		if ( input[i] == ' ') continue ; // 空白直接跳下一個
		if( input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '(' && input[i] != ')' && !( input[i] >= '0' && input[i] <= '9' ) ){
			cout << endl << "Error 1: " << input[i] << " is not a legitimate character." << endl ;
			return false ;
		} 
	}
	
	return true ;
}

bool parentheses( string input ) { // 成對括號，沒有檢查括號正不正確只有成不成對 
	int left = 0, right = 0 ;
	for ( int i = 0 ; i < input.length() ; i++ ) {	// 計算左右括號的數量 
		if ( input[i] == '(' ) left++ ;
		if ( input[i] == ')' ) right++ ;
	}
	
	if ( left != right ) {	// 數量一樣代表成對 
		cout << endl << "Error 2: there is one extra open parenthesis." << endl;
		return false;
	}
	
	return true ;
}

bool is_infix( string input ) {	// 是不是中序的形式 
	int sth = no ; 			// 看前一位是數字還是加減符號 
	char tempor = '\0' ;	// 暫存前一個運算子是什麼 
	
	for ( int i = 0 ; i < input.length() ; i++ ) {
		if ( input[i] == ' ' ) continue ;	// 空白跳過 
		if ( sth == no ) { 					// no 代表還沒拿到資訊 
			if ( input[i] <= '9' && input[i] >= '0' ) sth = oand ;	// 為運算元 
			else sth = oor ; 										// 為運算子 		
			continue ; 												// 拿到第一個的資訊後直接跳下一個 
		}
				
		if ( input[i] == '(' ) { //左括號
			
			tempor = input[i] ;
			if ( sth == oand && input[i-1] !='(' ) { //  數字 (   的樣子 而且不是兩個括號疊在一起 
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;
			} 			
			
			i++ ; // 直接往括號右邊看
			 
			if ( input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) { // ( 符號  的樣子  
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;				
			}
			else if ( input[i] == ' ' ) continue ; // 如果下一個是空格直接下一次迴圈 
			
			sth = oor ; // 本格為括號為符號設為oor
			 
		}
		else if ( input[i] == ')' ) { // 右括號 
			tempor = input[i] ;
			
			if ( sth == oor && input[i-1] !=')' ) { //	符號 )  的樣子 而且不是兩個括號疊在一起 
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;
			} 			
			
			i++ ; // 直接往括號右邊看
			 
			if ( i > input.length() ) return true ; 			// 右括號為最後一個 
			else if ( input[i] <= '9' && input[i] >= '0' ) { 	//	)數字  的樣子  
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;				
			}
			else if ( input[i] == ' ' ) continue ; 	// 如果下一個是空格直接下一次迴圈 
				
			sth = oor ; 							// 本格為括號為符號設為oor 			
			
		}
		else if ( input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) { // 是運算元 
			
			if ( sth == no ) { 		// 開頭第一個是符號不對 
				cout << endl << "Error 3: there is one extra operand." << endl ;
				return false ;				
			}
			else if ( sth == oor ) { 			// 上一個也是運算園連續兩個是不對的 
				if ( tempor == ')' || tempor == '(' ) continue ;	// 除非是括號 ) * ( 的樣子 
				else{
					cout << endl << "Error 3: there is one extra operand." << endl ;
					return false ;	
				}		
			}
			else {
				sth = oor ; //  本格為括號為符號設為oor 	
			}
		}
		else sth = oand ; //  上面把運算符號可能都讀過都不是,所以是數字 
	}
	return true ;
}

void re_ans(){ // 將最後答案多餘的空格消掉 不會有連續兩個空格存在的問題 
	now = head ;
	while( now -> next != NULL ) {
		
		if ( now ->token == ' ' ) {
			if ( now ->next ->token == ' ' ) {
				now ->next = now ->next->next ;
			}
		}
		
		now = now->next ;
	}
}

void pushoor() { // 將運算子丟入後序的答案中 
	
	if ( oorcur -> token == '(' ) { 	// 遇到右括號  不用丟進去 
		if ( oorcur ->pre != NULL ) {	
			oorcur = oorcur -> pre ;	// 堆疊中還有運算子 將指標往前一格 
			delete oorcur -> next ;		// 釋放掉 	
		}
		else {
			delete oorcur ;				// 如果沒有前一格則將Oor初始化變成NULL 
			Oor = NULL ;
			oorcur = Oor ;
		}
		
		return ; // 結束 
	}
	
	// 將運算子丟入答案中 
	now->token = oorcur->token ; 
	now ->next = new Token ;
	now = now ->next ;
	// 並給它空格 當作逗號 
	now->token = ' ' ;
	now->next = new Token ;
	now = now->next ;
	
	if ( oorcur ->pre != NULL ) {
		oorcur = oorcur -> pre ;	// 堆疊中還有運算子 將指標往前一格 
		delete oorcur -> next ;		// 釋放掉
	}
	else {
		delete oorcur ;				// 如果沒有前一格則將Oor初始化變成NULL 
		Oor = NULL ;
		oorcur = Oor ;
	}

	
}

void check( char input ){	// 檢查運算子堆疊裡面還有沒有東西 

	if ( oorcur == NULL ) return ;	// 沒東西結束 
	
	if ( input == '+' || input == '-' ){	// 讀進+或- 
		if( 1 > oorcur-> num )	return ;	//　原先堆疊的運算子優先順序小於+跟-的 就結束 
		else {						
			pushoor();				// 大於等於的 將堆疊中的丟進結果中 
			check( input ) ;		// 然後再繼續檢查 
		}		
	}
	else if ( input == '*' || input == '/' ){	// 讀進*或/ 
		if( 2 > oorcur-> num )	return ;		//　原先堆疊的運算子優先順序小於*跟/的 就結束
		else {
			pushoor();				// 大於等於的 將堆疊中的丟進結果中 
			check( input ) ;		// 然後再繼續檢查 
		}			
	}
	
	return ;	// 結束 
}

void postfix( string input ) {	// 中序轉後序 
	head = new Token ;
	now = head ;
	
	int left = 0, right = 0 ;
	
	for ( int i = 0 ; i < input.length() ; i++ ) {
		if ( input[i] == ' ' ) continue ;
		
		if ( input[i] >= '0' && input[i] <= '9' ) { // 數字直接丟進結果 
			now->token = input[i] ;
			now->next = new Token ;
			now = now->next ;	
			if ( i == input.length()-1 ) {
				now->token = ' ' ;
				now->next = new Token ;
				now = now->next ;	
			}
			continue ;		
		}
		else if ( input[i] == '+' || input[i] == '-' ){ // 如果是符號丟stack裡 
			
			now->token = ' ' ;
			now->next = new Token ;
			now = now->next ;	
			
			if ( Oor == NULL ){ // 堆疊為空的時候 

				Oor = new Token_or ;
				oorcur = Oor ;
				
				oorcur->token = input[i] ;
				oorcur->num = 1 ;
				oorcur->next = NULL ;	
				
				continue ;								
								
			}
			else if ( 1 <= oorcur->num )	check( input[i] ) ;
			
			// 從check出來有可能導致Oor是NULL 所以要再new 
			if (Oor == NULL){
				Oor = new Token_or ;
				oorcur = Oor ;
			}
			
			oorcur->next = new Token_or ;
			oorcur->next->pre = oorcur ;
			oorcur = oorcur->next ; 
						
			oorcur->token = input[i] ;
			oorcur->num = 1 ;											

		} 
		else if ( input[i] == '*' || input[i] == '/' ) {

			
			now->token = ' ' ;
			now->next = new Token ;
			now = now->next ;	
			
			if ( Oor == NULL ){ // 堆疊為空的時候 

				Oor = new Token_or ;
				oorcur = Oor ;				
	
				oorcur->token = input[i] ;
				oorcur->num = 2 ;	
				oorcur->next = NULL ;
				
				continue ;								
								
			}		
			if ( 2 <= oorcur->num )		check( input[i] ) ;

			// 從check出來有可能導致Oor是NULL 所以要再new			
			if (Oor == NULL){
				Oor = new Token_or ;
				oorcur = Oor ;
			}
			
			oorcur->next = new Token_or ;
			oorcur->next->pre = oorcur ;
			oorcur = oorcur->next ; 
							
			oorcur->token = input[i] ;
			oorcur->num = 2 ;
			 	
	
		}
		else if ( input[i] == '(' ) {	
	
			if ( Oor == NULL ){ // 堆疊為空的時候 
				Oor = new Token_or ;
				oorcur = Oor ;					
				oorcur->token = input[i] ;
				oorcur->num = 0 ;	
				continue ;								
								
			}
			
			oorcur->next = new Token_or ;
			oorcur->next->pre = oorcur ;
			oorcur = oorcur->next ; 
												
			oorcur->token = input[i] ;
			oorcur->num = 0 ;
						
		}
		else if ( input[i] == ')' ) {
			
			now->token = ' ' ;
			now->next = new Token ;
			now = now->next ;			

			pushoor() ;
			if ( oorcur -> token == '(' ) {

				if ( oorcur ->pre != NULL ) {
					oorcur = oorcur -> pre ;
					delete oorcur -> next ;				
					
				}
				else {
					delete oorcur ;
					Oor = NULL ;
					oorcur = Oor ;
					
				}
			}
		}	
	}
	
	while( oorcur != NULL ) {		// 全都讀完了 將運算子清空 
		if ( oorcur -> token == '\0' ) {
			delete oorcur ;
			Oor = NULL ;
			oorcur = Oor ;
			break ;
		}
		
		pushoor() ;		
	}	
	
	now = NULL ;
}

int main(void) {
	
	int command ;
		
	do{
		cout << endl << "* Arithmetic Expression Evaluator *" << endl ;
		cout << "* 0. QUIT                         *" << endl ;
		cout << "* 1. Infix2postfix Transformation *" << endl ;
		cout << "***********************************" << endl ;
		cout << "Input a command(0, 1): "  ;
		cin >> command ;
		cin.ignore(MAX_LEN,'\n');	
			
		switch( command ){
			case 0 :
				break ;
			case 1 :	
			
				cout << endl << "Input an infix expression: "  ;
				string input ;
				getline ( cin, input ) ;
				
				if ( !legal(input) || !parentheses( input ) || !is_infix( input )) break ;
				cout << "It is a legitimate infix expression." << endl ;	
				
				postfix( input ) ;
				re_ans() ;
				write() ;
					
				break ;
		}
		
	}while( command != 0 ) ;
} 

/*
Test
(29+101)*33/25
24*7770/(55+30*2)
(90+(70*(68-55/10)))
69/33+30*5-24/8

24*7770^(55+30*2)
(90+(70*(68-55/10))
(29+101)*33/25)
69/3++30*5-24/8

1+2*3+(4-7)*(2+1)*(5+2)+6
*/

