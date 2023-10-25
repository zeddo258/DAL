// 11127203 郭力嫚 
#include <iostream>
#include <cstdlib> // system, atoi
#include <string> // string class

#define MAX_LEN 255 // maximum string length

using namespace std ;

class ListNode {
public:
    string value ;  // 用來儲存節點的值
    ListNode* next ; // 指向下一個節點的指標
    ListNode( const string& val ) : value( val ), next( nullptr ) {} // 初始化節點，將next指標初始化為nullptr，表示它是堆疊中的最上面一個節點 
};

class expLIST {
private:
    ListNode* head ;
    ListNode* tail ;
    // 指向鏈表的頭節點和尾節點

public:
    expLIST() : head( nullptr ), tail( nullptr ) {} // 建構子，初始化類別的物件，並執行一些初始設定操作 

    bool isEmpty() { // 檢查列表是否為空，頭節點是否為 nullptr 
        return head == nullptr ;
    } // bool isEmpty()
 
    void ins( const string val ) { // 在列表末尾插入具有特定值的新節點
        ListNode* newNode = new ListNode( val ) ;
        if ( tail == nullptr ) {
            head = tail = newNode ; // 新節點設為head和tail
        } // if ( tail == nullptr )
        else {
            tail->next = newNode ; // 新節點連接到目前的tail節點的後面
            tail = newNode ; // 將tail指針更新為新節點
        }
    }
    
    void deleteHead() { // 刪除列表頭節點。釋放記憶體 
        if ( !isEmpty() ) {
            ListNode* temp = head ; // 創建一個指向頭節點的指標
            head = head->next ; // 更新head指標以指向列表的下一個節點
            delete temp ; // 釋放之前的頭節點的記憶體，以防止內存洩漏
        } // if ( !isEmpty() )
        
    } // void deleteHead()

    void clear() { // 清除整個列表 
        while ( !isEmpty() ) {
            deleteHead() ;
        } // while ( !isEmpty() )
    } // void clear()
    
	void getpostfix() { // 印出後序運算式
    	ListNode* current = head ;
    	string separator = "" ;
    	while ( current != nullptr ) {
        	cout << separator << current->value ;
        	separator = ", " ;
        	current = current->next ;
    	} // while ( current != nullptr )
    	
	} // void getpostfix()


    ~expLIST() { // 解構子，在物件生命週期結束時進行清理和釋放資源的操作
        clear() ;
    }
};

class expSTACK {
private:
    ListNode* topPtr ; //指向堆疊的頂部節點。用於維護堆疊的結構，執行壓入（push）和彈出（pop）操作 

public:
    expSTACK() : topPtr( nullptr ) {} // 建構子，初始化類別的物件，並執行一些初始設定操作 

    bool isEmpty() { // 檢查堆疊是否為空 
        return topPtr == nullptr ;
    } // bool isEmpty()

    void push( char val ) { // 將特定值(val)壓入堆疊 
        ListNode* newNode = new ListNode( string( 1, val ) ) ; // 創建一個新的stackNode節點 newNode，並將值 val 初始化為這個節點的值
        newNode->next = topPtr ; // 指向當前堆疊的頂部節點，為堆疊的最上面一個節點
        topPtr = newNode ; // 將 topPtr 指向新壓入的節點 newNode，使其成為新的堆疊頂部
    } // void push( char val )  

    char getTop() { // 取得堆疊頂部的值
        if ( !isEmpty() ) {
            return topPtr->value[0] ;
        } // if ( !isEmpty() )
        return '\0';
    } // char getTop()

    void pop() {
        if ( !isEmpty() ) {
            ListNode* temp = topPtr ; // 創建一個指向頂部節點的臨時指標 temp
            topPtr = topPtr->next ; // 更新 topPtr，使其指向當前頂部節點的下一個節點
            delete temp ; // 釋放 temp，即刪除原來的頂部節點，以防止內存洩漏
        } // if ( !isEmpty() )
    } // void pop()

    ~expSTACK() { // 解構子，在物件生命週期結束時進行清理和釋放資源的操作 
        while ( !isEmpty() ) {
            pop() ; // while ( !isEmpty() )
        } // while ( !isEmpty() ) {
    } // ~ExpStack()
};

bool isOperator( char c ) { // 函式以檢查字符是否為運算符 
    return ( c  == '+' || c == '-' || c == '*' || c == '/' ) ;
} // bool isOperator( char c )  

int getPrecedence( char c ) { // 函式以獲取運算符的優先順序 
    if ( c == '+' || c == '-' ) {
        return 1 ;
    } // if ( c == '+' || c == '-' )
	
	else if ( c == '*' || c == '/' ) {
        return 2 ;
    } // else if ( c == '*' || c == '/' )
    
    return 0;
} // int getPrecedence( char c )

void infix2Postfix( const string infix ) {  // 函式以將中序表示法轉換為前序表示法
    expSTACK stack ;
    expLIST postfix ;

    for ( int i = 0 ; i < infix.length() ; i++ ) { // 遍歷中序表達式 infix
        char c = infix[i] ;
        if ( c == ' ' ) { // 跳過空格字符，繼續下一次循環
            continue ;
        } // if ( c == ' ' )
		
		else if ( c >= '0' && c <= '9' ) { // 如果當前字符是數字（'0' 到 '9' 之間的字符），則處理數字
            string number ;               // 循環讀取連續的數字字符，將它們拼接成一個完整的數字
            number += c ;
            while ( i + 1 < infix.size() && infix[i + 1] >= '0' && infix[i + 1] <= '9' ) {
                i++ ;
                number += infix[i] ;
            } // while ( i + 1 < infix.size() && infix[i + 1] >= '0' && infix[i + 1] <= '9' )
            
            postfix.ins( number ) ; // 將該數字添加到 postfix 鏈表中，表示後序表達式的一部分
        } // else if ( c >= '0' && c <= '9' )
		
		else if ( isOperator( c ) ) {
            while ( !stack.isEmpty() ) {
                char top = stack.getTop();
                if ( isOperator( top ) && getPrecedence( top ) >= getPrecedence( c ) ) { // 判斷其優先級， 堆疊頂部的運算符的優先級大於或等於當前運算符，
                    postfix.ins( string( 1, top ) ) ;                                   // 就將堆疊頂部的運算符彈出並添加到 postfix中
                    stack.pop() ;
                } // if ( isOperator( top ) && getPrecedence( top ) >= getPrecedence( c ) ) 
				
				else {
                    break;
                } // else
                
            } // while ( !stack.isEmpty() )
            
            stack.push( c ) ;
        } // else if ( isOperator( c ) )
		
		else if ( c == '(' ) { // 壓入 
            stack.push( c ) ;
        } // else if ( c == '(' )
        
		else if ( c == ')' ) {
            while (!stack.isEmpty() && stack.getTop() != '(' ) { //彈出 
                postfix.ins(string( 1, stack.getTop() ) ) ;
                stack.pop() ;
            } // while (!stack.isEmpty() && stack.getTop() != '(')
            
            if ( !stack.isEmpty() && stack.getTop() == '(' ) { //彈出 
                stack.pop() ;
            } // if (!stack.isEmpty() && stack.getTop() == '(')
            
        } // else if ( c == ')' )
        
    } // for ( int i = 0 ; i < infix.length() ; i++ )

    while ( !stack.isEmpty() ) {
        postfix.ins( string( 1, stack.getTop() ) ) ; // 頂部運算符壓入 
        stack.pop() ;
    } //while ( !stack.isEmpty() )

    postfix.getpostfix() ;  // 印出後序運算式
    postfix.clear() ;
} // void infix2Postfix( const string infix )


bool isExp( string& infixS ) {   
	char invalid = '\0' ;
	for ( char check : infixS ) {
		if ( check != '+' && check != '-' && check != '*' && check != '/' && check != '(' && check != ')' && !isdigit( check ) && check != ' ' ) {
			invalid = check ;
			cout << "Error 1: " << invalid << " is not a legitimate character." << endl ;
			return false ;
		}
	} // for ( char check : infixS )
	
	return true ;
} // isExp( string& infixS )  // 檢查每個符號的有效性

bool isBalanced( const string infixS ) { // 'const'表示不可變的字符串
    int count = 0 ;
    char first =  infixS[0] ;
    if ( first == ')' ) { // 判斷第一個字符是否為'(' 
    	cout << "Error 2: there is one extra open parenthesis." << endl ;
		return false ;
	} // if ( first == ')' )
	
	for ( char check : infixS ) {
		if ( check == '(' ) {
			count++ ;
		} // if ( check == '(' )
		
		else if ( check == ')' ) {
			count++ ;
		} // else if ( check == ')' )
		
	} // for ( char check : infixS )
	
	if ( count % 2 != 0 ) {
		cout << "Error 2: there is one extra open parenthesis." << endl ;
		return false ;
	}
	
	return true ;
	
} // isBalanced( const string infixS ) 檢查括號是否平衡有效



bool isLegalInfix( const string infixS ) { // 是否符合中序運算式 
    int parenContentLength = 0 ;  //計算括號內的內容的長度( 運算符號與數字 ) 
    int count = 0 ; // 計算括弧數量 
    bool pcount = true ; // 括弧是否為零 
    bool inParenthesis = false ; // 是否在括號內 
    bool prevIsDigit = false ;  // 前一個字符是否是數字 
    bool prevIsOperator = false ; // 前一個字符是否是運算符
	bool newDigit = false ;  // 是否遇到了新一括弧的數字

    for ( char c : infixS ) {
        if ( c == '(' ) {
            inParenthesis = true ;
            prevIsOperator = false ;
            count++ ;
        } // if ( c == '(' )
        
        else if ( c == ')' ) {
            inParenthesis = false ;
            if ( !prevIsDigit ) {
                return false ; 
                count++ ;
            } // if ( !prevIsDigit ) 

            prevIsDigit = true ;
            prevIsOperator = false ;
            newDigit = false ;
        } // else if ( c == ')' )
        
        else if ( inParenthesis ) {
            if ( isdigit( c ) ) {
            	newDigit = true ;
                prevIsDigit = true ;
                prevIsOperator = false ;
            } // if ( isdigit( c ) )
			
			else if ( c == '+' || c == '-' || c == '*' || c == '/' ) {
                if ( prevIsOperator ) {
                    return false ;  
                } // if ( prevIsOperator )
                
                else if ( !newDigit ) { // 括弧後直接接符號 
                	return false ;
				} // else if ( !newDigit )
                
                prevIsDigit = false ;
                prevIsOperator = true ;
            } // else if ( c == '+' || c == '-' || c == '*' || c == '/' )
            
			else {
                return false ; 
            } // else
            
        } // else if ( inParenthesis )
        
    } // for ( char c : infixS )
    
    if ( count == 0 ) {
    	pcount = false ;
	} // if ( count == 0 )

    if ( ( prevIsOperator || !prevIsDigit ) && pcount ) {
        return false ;  
    } // if ( prevIsOperator || !prevIsDigit && count!= 0 )

    return true ;
} // bool isLegalInfix( const string infixS )




bool isLegal( const string infixS ) { // 'const'表示不可變的字符串
	int OperCount = 0 ; // 計算運算符 
	int NumCount = 0 ; // 計算數字 
	bool isinfix = isLegalInfix( infixS ) ; // 是否為中序運算式 
	bool isoperator = false ; // 運算符錯誤 
	bool isnum = false ; // 數字錯誤 

    char prevC = ' ' ;
	
	for ( int i = 0 ; i < infixS.length() ; ++i ) {
		if ( isdigit( infixS[i] ) ) {
			NumCount++ ;
			while ( i < infixS.length() && isdigit( infixS[i] ) ) {
				i++ ;
			} // while ( i < infixS.length() && isdigit( infixS[i] ) )
			
			i-- ;
		} // if ( isdigit( infixS[i] ) )
		
		else if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/' ) {
			OperCount++ ;
		} // else if ( infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/')
		
	} // for ( int i = 0 ; i < infixS.length() ; ++i )
	
	if ( ( NumCount <= OperCount || NumCount != OperCount + 1  ) ) {
		if ( NumCount <= OperCount ) {
			isoperator = true ;
		} // if ( NumCount <= OperCount )
		
		else if ( NumCount != OperCount + 1 ) {
			isnum = true ;
		} // else if ( NumCount != OperCount + 1 )
		
	} // if ( NumCount <= OperCount || NumCount != OperCount + 1 )
	
	
	if ( !isinfix && !isoperator && !isnum ) {
		cout << "Error 3: it is not infix in the parenthesis." << endl ;
		return false ;
	} // if ( !isinfix && !isoperator && !isnum )
	
	if ( isoperator ) {
		if ( !isinfix ) 
			cout << "Error 3: it is not infix in the parenthesis." << endl ;
		else
			cout << "Error 3: there is one extra operator." << endl ;
			return false ;
	} // if ( NumCount <= OperCount )
		
	else if ( isnum ) {
		cout << "Error 3: there is one extra operand." << endl ;
		return false ;
	} // else if ( isnum )
	

	return true ;
} // isLegal( const string infixS ) 檢查是否是有效表達


int main() {
	int command = 0 ;
	do {
		string infixS ;
		
		cout << "\n" ;
		cout << "* Arithmetic Expression Evaluator *\n" ;
		cout << "* 0. QUIT                         *\n" ;
		cout << "* 1. Infix2postfix Transformation *\n" ;
		cout << "***********************************\n" ;
		cout << "Input a choice(0, 1): " ;
		cin >> command ;
		cin.ignore( MAX_LEN, '\n' ) ; // 清除緩衝區中的換行符（'\n'）或其他可能不需要的字符
		switch (command) {
			case 0:
			 	break;
			case 1:
				cout << endl << "Input an infix expression: " ;
				getline( cin, infixS ) ;
				if ( isExp( infixS ) && isBalanced( infixS )  && isLegal( infixS ) ) {
					cout << "It is a legitimate infix expression." << endl ; 
					cout << "Postfix expression: ";
					infix2Postfix( infixS ) ;
					cout << "\n" ;				
				} // if ( isExp( infixS ) && isBalanced( infixS )  && isLegal( infixS ) )
				  // 檢查每個符號；檢查括號是否平衡有效；檢查是否是有效表達  

				break ;
				
			default: cout << endl << "Command does not exist!" << endl ;

		} // swith( command ) 
	} while ( command != 0 ) ;
	
	system("pause") ; // 暫停程序執行，等待按下Enter鍵
	return 0 ;
} // main()


