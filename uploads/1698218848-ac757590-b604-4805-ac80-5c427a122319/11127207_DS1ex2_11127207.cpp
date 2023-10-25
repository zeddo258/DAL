// 11127207 楊竣傑

# include <iostream>
# include <string> 
# include <cstdlib>
# include <new>

# define MAX_LEN 255

using namespace std ;


struct listNode {  // 儲存成把字串類似23+2變成指標23,+,2的 
	string c ;  
	struct listNode *next ;	// structure of each node in list
} ;

class expLIST {  // 處理字串是否為中序式的主要程式 
	bool repeat ;	// 有無重複的運算符 
	listNode*head,*tail ; // only two data members 
	
public :
	expLIST() { //初始化 
		head = NULL ;
		tail = NULL ;
		repeat = true ;
	} // end expList initializer

	listNode* gethead() {
		return head;
	} 
	
    void insert( string ch ) { //建立指標串列 
    	
        listNode * newNode = new listNode ; // 創建指標並塞入東西 
        newNode -> c = ch ;
        newNode -> next = NULL ;
        
        if ( head == NULL ) { // 建立指標的頭 
            head = newNode;
            tail = newNode;
        } // if
		else {
			if ( tail -> c == "+" || tail -> c == "-" || tail -> c == "*" || tail -> c == "/" ) { 
				if ( ch == "+" || ch == "-" || ch == "*" || ch == "/" ) { //檢查有沒有 ++ +-等等錯誤 
					repeat = false ;
					cout << "Error 3: there is one extra operator."	;
				} // if
				
			} // if
		
            tail -> next = newNode ;
            tail = newNode;
        }
    }

	bool allRight() { // 返回檢查出的錯誤 
		if ( repeat == true && Check() == true ) { // 有無重複或多餘的運算符或運算子 
			return true ;
		}
		else {
			return false ;
		}
		
	} // allRight()
	
	bool Check() { // 檢查有無重複或多餘的運算符或運算子  
		
		listNode * check = head ; // 從頭檢查的指標 
		while ( check -> next != NULL ) {
			string save = check -> c ;
			if ( save != "+" && save != "-" && save != "*" && save != "/" && save != "(" && save != ")" ) {
				if ( check -> c == "(" ) {
					cout << "Error 3 : there is one extra operand." << endl ;
					return false ;
				} // if
					
			} // if
			else if ( save == ")" ) {
				if ( check -> c == "+" && check -> c == "*" && check -> c == "/" && check -> c == "-" ) {
					cout << "Error 3 : there is one extra operand." << endl ;
					cout << check -> c << endl ;
					return false ;
				} // if
				
			} // else if
			
			check = check -> next ;
		}	// while
		
		if ( check -> c == "+" || check -> c == "/" && check -> c == "*" && check -> c == "-" ) {
			cout << "Error 3 : there is one extra operator." << endl ;
			return false ;
		}
		else
			return true ;
	} // Check()
	
	bool isEmpty() {  // decide whrith list is empty
		listNode * check = head ; // 從頭檢查的指標 
		int length = 0 ;
		while ( check != NULL ) {
			length++ ;
			check = check -> next ;
		}	// while
		
		if ( length == 0 ) {
			cout << "Error 3: there is one extra operator."<< endl ;
			return false ;
		} // if
		else 
			return true ;
			
	} // end expList:: isEmpty
	
	bool  isBalanced() { // 檢查是否有相等的左右括號 
		int left = 0 ;
		int right = 0 ;
		listNode * check = head ; // 從頭檢查的指標  
		while ( check != NULL ) {
			if ( check -> c == "(" )
				left = left + 1 ;
			else if ( check -> c == ")" )
				right = right + 1 ;
			check = check -> next ;
		} // while
		
		if ( left > right ) { // 左括號多於右括號 
			cout << "Error 2: there is one extra open parenthesis." << endl ;
			return false ;
		} // if
		else if ( right > left ) { // 右括號多於左括號 
			cout << "Error 2: there is one extra close parenthesis." << endl ;
			return false ;
		} // else if
		else 
			return true ;
		
		
	} // end isBalanced()
	
	void clear() { // clear up the entire list
	
		listNode * current = head ;
    	while (current != NULL ) {  
        	listNode * temp = current;
        	current = current -> next;
        	delete temp;
    	} // while
    	
    	head = NULL ;	 // 清空資料以免造成memory leak 
	} // clear()
	
	
};

class expStack {  // 處理堆疊和轉後項式 
	struct theList{ // 結果的指標 
		string c ;
		struct theList *next ;	
	};
	
	struct save{ // 暫存運算符的指標 
		string ch ;
		struct save *next ;
	};

theList *first, *second ;
save *top, *end;

public:	
    expStack() { // 初始化 
		first = NULL ;
		second = NULL ;
		top = NULL ;
		end = NULL ;   
    }
    

	void push( string x ) { // 建立要印出的後項式的指標並塞入 
        theList * newNode = new theList ;
        newNode -> c = x ;
        newNode -> next = NULL ;
        
		if ( first == NULL ) {
            first = newNode;
            second = newNode;
        } // if
		else {
            second -> next = newNode ;
            second = newNode;
        } // else
        
	} // push
	
	void push2( string x ) { // 存運算符的 
        save * newNode = new save ;
        newNode -> ch = x ;
        newNode -> next = NULL ;
        
		if ( top == NULL ) {
            top = newNode;
            end = newNode;
        } // if
		else {
            end -> next = newNode ;
            end = newNode;
        } // else
        
	} // push
	
	int getPriority( string op ) { // 檢查優先級 
    	if (op == "*" || op == "/" )
        	return 2;
    	else if (op == "+" || op == "-" )
        	return 1;
    	return 0;
	}
	
	bool isEmpty() { // 檢查指標串列是否為空 
		
		if( top == NULL ) {
			return true ;
		} // if
		else
			return false ;
		
	} // isEmpty()
	
	string getTop() { // 找指標串列最尾端的指標 
		save *temp = top ;
		if ( temp -> next == NULL ) {
			return temp -> ch ;
		} // if
		
		else {
			while ( temp -> next != NULL ) {
				temp = temp -> next ;
			} // while
			
			return temp -> ch ;
		}
		
		
	} // getTop()
	
	void deleteTop() { // 刪除最尾端的指標 
		save *temp = top ;
		if ( temp == NULL ) {
			return ;
		}
		
		if ( temp -> next == NULL ) {
			delete temp ;
			top = NULL ;
			end = NULL ;
		} // if
		
		else {
			save* previous = NULL ;
			while ( temp -> next != NULL ) {
				previous = temp ;
				temp = temp -> next ;
			} // while
			
			delete temp ;
			previous -> next = NULL ;
			end = previous ;
		}
		
	} // deleteTop()
	
	void turnToPostfix( listNode *temp ) {  // 中項式轉後項式 
		cout << "It is a legitimate infix expression." << endl ;
		
		while ( temp != NULL ) { // 檢查 
			if ( temp -> c != "+" && temp -> c != "-" && temp -> c != "*"
				&& temp -> c != "/" && temp -> c != "(" && temp -> c != ")" ) { // 如果是運算子直接丟入結果指標中 
        		push( temp -> c ) ;	
			} // if
			else if (temp -> c == "+" || temp -> c == "-" || temp -> c == "*" || temp -> c == "/" ) { // 為運算符 
				if ( isEmpty() == true ) { // 暫存運算符的指標沒東西 
					push2( temp -> c ) ;
				} // if 
				else if ( isEmpty() != true && getPriority( getTop() ) < getPriority( temp -> c ) ) { // 寫一個取最上方的function
					push2( temp -> c ) ; // 有東西且存運算符指標最尾端優先度小於目前讀入的運算符 
				} // else if
				else if( isEmpty() != true  && getPriority( getTop() ) >= getPriority( temp -> c ) ) { // 檢查為何不會跑進這裡 
					push( getTop() ) ; // 有東西且存運算符指標最尾端優先度大於等於目前讀入的運算符 
					deleteTop() ;      // 且把最尾端指運算符彈出 類似pop()和top() 
					push2( temp -> c ) ;
				} // else
				
			} // else if
			else if ( temp -> c == "(" ) { // 是(就直接丟入存運算符的指標 
				push2( temp -> c ) ;
			} // else if
			else if ( temp -> c == ")" ) { //直到找到相對應的(不斷把運算符指標裡的東西彈出 
				
				while ( getTop() != "(" ) {
					if ( isEmpty() != true ) {
						push( getTop() ) ;
						deleteTop() ;
					} // if
					
				} // while
				
				if ( getTop() == "(" ) { // 找到相對應的( 並刪除 
					deleteTop() ;
				} // if
				
			} // else if
			
			temp = temp -> next ; 
		} // while
		
		if ( isEmpty() != true ) { // 把剩餘的丟入結果指標 
			while ( isEmpty() != true ) {
				push( getTop() ) ;
				deleteTop() ;
			} // while
			
		} // if
		
	} // turnToPostfix()	
	
	void Print() { // 印出結果 
		theList * current = first ;
		while ( current != NULL ) {
			cout << current -> c ;
			if ( current -> next != NULL )
				cout << "," ;
			current = current -> next ;	
		} // while
		
	} // Print()
	
	void Clear() { // 刪除結果指標的內容 
		theList * current = first ;
    	while ( current != NULL ) {  
        	theList * temp = current;
        	current = current -> next;
        	delete temp;
    	} // while
    	
    	first = NULL ;	 // 清空資料以免造成memory leak 	
	} // Clear()
	
}; // expStack
	



int main( void ) {
	int command = 0 ; // use command
	bool character = true ; // 找錯誤用 
	expLIST List ;  
	
	do {
		character = true ;
		string infixS = "" ; 
		string token = "" ;
		int x = 0 ;
		cout << endl << "* Arithmetic Expression Evaluator*" ;  //使用者看到的面板 
		cout << endl << "* 0.QUIT                         *" ;
		cout << endl << "* 1.Infix2postfix Transformation *" ;
		cout << endl << "**********************************" ;
		cout << endl << "Input a choice(0 , 1): " ;
		cin >> command ;
		cin.ignore( MAX_LEN, '\n' ) ;
		
		switch (command) {	
			case 0 : break ;
			case 1 :
				cout << endl << "Input an infix exression: " ;  
				getline(cin, infixS) ; // 讀取運算式 
				
				for ( size_t i = 0; i < infixS.length(); i++ ) {  // 把字串拆成字元 
					char ch = infixS[i];
					if ( ch >= '0' && ch <= '9' ) {  // 丟入時定義 
						token = token + ch ;  // 是數字就先儲存在字串 
					} // if
					else if ( ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '(' || ch == ')' ) { // 檢查是否有不符合的東西 
						if ( token != "" ) // 有數字字串先丟入 
							List.insert( token );
						token = ch ;
						List.insert( token ); // 丟入運算符 
						token = "" ;
					} // else if
					else if ( ch == ' ' ) // do nothing 
						x = x + 1 ; 
					else {
						cout << "Error 1 " << ch << " is not a legitmate character." << endl ; // 檢查是否有不合法的字符在字串中 
						character = false ; 
					} // else
					
				} // for
				
				
				if ( token != "" ) // 字串尾數是 ) 等 
					List.insert( token );  
       			
				if ( List.isEmpty() && List.isBalanced() 
					  && List.allRight() && character == true ) { // 確認運算式完全沒問題 
					  	listNode *temp = List.gethead() ; // 取得檢查時做好的指標的頭 
					 	expStack list2 ;
						list2.turnToPostfix( temp ) ; // 轉成後項式 
						list2.Print() ; // 印出結果 
						cout << endl ;  
						list2.Clear() ; // 清空指標 
						List.clear() ; // 清空指標 
					}  // end if
					
				else { // 遇到錯誤情況清除鏈結串列 
					List.clear() ;
				}
				
				break ;
				
				default : cout << endl << "Command does not exist!" << endl ;
					
		} // end switch
		
	} while ( command != 0 ) ;
	
	system( "pause" ) ;
	return 0 ;
	
} // main
