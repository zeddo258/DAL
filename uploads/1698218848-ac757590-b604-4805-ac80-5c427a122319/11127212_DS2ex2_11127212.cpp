// 11127212 曾博仁 
# include <iostream>	// string class
# include <string>		// system, atoi
# include <sstream>
# include <cstdlib>
# include <new>
# define MAX_LEN 255 	// maximum string length


using namespace std ;
const char legal[17] = {'1','2','3','4','5','6','7','8','9','0','+','-','*','/','(',')',' ' } ;		// 把正確的字都列出來 
enum Opt { Number, Operator, Balance };  															// 將符號分類 
template<class T>  // type template for data value in list node


class expLIST {
		typedef struct qN  			// structure of each node in list
		{ 	T value ;
			struct qN *next ;		// next element
		}	listNode ;
		listNode *head, *tail ;		// only two data members
	public : 
		expLIST() : head(NULL), tail(NULL)	// constructor with initialization
		{} // end expLIST initializer
	bool isEmpty() const {					// decide whether list is empty
		return head == NULL ;
	} // end expLIST::isEmpty
	void ins(const T inValue) {				// append one value into list
		try {
			listNode *current = new listNode ;	// 設定新的指標 current 
			current->value = inValue ;			// 把資料放到 value 裡 
			current->next = NULL ;				// 將下一指標指向 NULL  
			if ( head == NULL ) {
				head = current ;				// 如果 LIST 裡面是空，將 Head 和 tail 指向 current 
				tail = head ;
			} // if
			
			else {
												// 把新的街道資料的後面 
				tail->next = current ;		 
				tail = current ;
			}
		} // end try
		catch ( bad_alloc& ba)		// unable to allocate space
		{ cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl ;
		} // end catch
	} // end expLIST::ins
	
	void getHead(T& outValue) {		// get the head of list without removal
		// ???
	} // end expLIST::getHead
	
	void del()						// remove the head of list
	{
		// ???
	} // end expLIST :: del with output parameter
	
	void getdelHead(T & outValue)			// get the head of stack and remove it
	{
		listNode *delet = head ;			// 設一個 delete 指標指向 head (要刪除的資料) 
		outValue = head->value ;			// 回傳 head -> value 的植 
		head = head->next ;					// head 指向 head -> next 
		delete delet ;						// 刪除無用指標 
		
	} // end expLIST::del with output parameter
	
	void clearUp() 					// clear up the entire list
	{
		// ???
	} // end expLIST::clearUp 
	~expLIST()						// destructor
	{	clearUp() ; 
	} // end destructor
};	// end expLIST class

template<class T>
class expSTACK {
		typedef struct sN				// structure of each element in stack
		{	T value ;
			struct sN *next ;			// next element
		}	stackNode ;
	
		stackNode *topPtr ;				// only one data member
	public :
		expSTACK() : topPtr(NULL)		// constructor with initialization
		{}	// end expSTACK initializer
		
		bool isEmpty() const {			// decide whether stack is empty
			return topPtr == NULL ;
		}	// end expSTACK::isEmpty
		
		void push(const T inValue)		// add one element into stack
		{	try {
				stackNode *current = new stackNode ;	// 設定新的指標 current  
				current->value = inValue ;				// 把資料放到 value 裡 
				current->next = NULL ;					// 將下一指標指向 NULL 
				if ( topPtr == NULL ) {					// 只要 Stack 是 NULL 
					topPtr = current ;					// 
				} // if
				else {
					current->next = topPtr ;
					topPtr = current ;
				}
			} // end try
			catch ( bad_alloc& ba)		// unable to allocate space
			{	cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl ;
			}	// end catch
		} // end expSTACK::push
		
		void getTop(T & outValue)		// get the top of stack without removal
		{
			outValue = topPtr->value ;
			
		} // end expSTACK::getTop
		
		void pop()						// remove the top of stack
		{
			stackNode *del = topPtr ;
			topPtr = topPtr->next ;
			delete del ;
		} // end expSTACK::pop without output parameter
		
		void pop(T& outValue)			// get the top op stack and remove
		{	getTop(outValue) ;
			pop() ;
			
		} // end expSTACK::pop with output parameter
		
		~expSTACK()						// destructor
		{	while(!isEmpty())
				pop() ;
		}	// end destructor
};	// end expSTACK class		


bool isExp(string & exp) ;			// check the validity of each symbol
bool isBalanced(const string exp) ;		// check the validity of balanced parentheses
bool isLegal(const string exp) ; 		// check whether it is a legal expression
bool infix2postfix(expLIST<string> explist) ;				// transform infix into postfix
void str2list(const string exp, expLIST<string> & explist ) ;					// parse a string into a linked list
Opt whatOpt( const char operation ) ;

int main(void) {
	
	int command = 0 ; // user command
	do { 
		string infixS ;
		expLIST<string> explist ;
		cout << endl << "*Arithmetic Expression Evaluator*" ;
		cout << endl << "* 0. QUIT			*" ;
		cout << endl << "* 1. Infix2posfix Transformation*" ;
		cout << endl << "*********************************"	;
		cout << endl << "Input a choice(0,1) :" ;
		cin >> command ;	// get a command
		cin.ignore(MAX_LEN, '\n') ;	// clear the input buffer
		switch(command){
			case 0 : break ;
			case 1 : cout << endl << "Input an infix expression: " ;
					 getline(cin, infixS) ;
					 if ( isExp(infixS) &&      // check each symbol & remove useless ones 
					 	  isBalanced(infixS) && // check the validity of balanced parentheses
						  isLegal(infixS)) {	// check whether it is a legal expression
						  cout << "It is a legitimate infix expression." << endl ;
						str2list(infixS, explist) ;			// parse a string into a linded list
					 	if ( infix2postfix(explist)) 		// transform infixS into postfixS
					 		;
					// Mission One : check whether it is an infix expression
					// Mission Two : transform infix to postfix, stored as a linked list
					
					 } // end if
					 break ;
			default : cout << endl << "Command does not exist!" << endl ;
			} // end switch
	} while(command!=0) ;
	system("pause") ;
	return 0 ;
} // end main

bool isExp(string & exp) {								// 判斷是否有正確字元以外的字元 
	string non_space ;									// 設一個字串是沒有空格的 
	for ( int i = 0 ; i < exp.size() ; i ++ ) {			// 判斷 exp 裡的字元是否和 lebal 一樣，不一樣 return false  
		if ( exp[i] != ' ' ) non_space += exp[i] ;		// 把非空白的字元放進 non_space 
		for ( int j = 0 ; j < 18 ; j ++ ) {
			if ( j == 17 ) {
				cout << "Error 1 : " << exp[i] << " is not a legitimate character." << endl ;
				return false ;
			}
			if ( exp[i] == legal[j] ) break ;
		} // for
	} // for
	
	exp = non_space ;									// 把 exp 改成 non_space 
	return true ;
} // end isExp

bool isBalanced(const string exp) {						// 判斷括號是否成雙成對 
	int balance = 0 ;									// 正數代表 '(' 比較多，負數代表 ')' 比較多 
	for ( int i = 0 ; i < exp.size() ; i ++ ) {			 
		if ( exp[i] == '(' ) balance ++ ;				// 如果遇到 '('， balance + 1 
		else if ( exp[i] == ')' ) balance -- ;			// 如果遇到 ')' ， balance - 1 
		if ( balance < 0 ) {							// 如果 balance < 0 表示 ')' 前面沒有 '(' 
			cout << "Error 2 : there is one extra close parenthesis." << endl ;
			return false ;
		} // if
	} // for
	
	if (balance > 0) {									// 如果 balance > 0 表示 '(' 比較多 
		cout << "Error 2 : there is one extra open parenthesis." << endl ;
		return false ;
	} // if
	
	return true ;
} // isBalanced()

bool isLegal(const string exp) { 											// 判斷是不是中序式 
	Opt forward, backward ;													// 設定前面的字元和後面的字元類別 
	forward = whatOpt(exp[0]) ;												// 取得前面的字元類別 
	if ( exp.size() == 1 ) {												// 如果算式只有一個字元只要判斷它是否為數字 
		if ( forward == Number ) return true ;								
		else {
			cout << "Error 3 : there is one extra operator." << endl ;
			return false ;
		}
	}
	
	for ( int i = 1 ; i < exp.size() ; i ++ ) {								// 判斷是否有不合理的文法 
		backward = whatOpt(exp[i]) ;
		if ( forward == Operator && backward == Operator ) {				// 兩個符號黏在一起 
			cout << "Error 3 : there is one extra operator." << endl ;
			return false ;			
		} // if
		else if ( forward == Number && exp[i] == '(' ) {					// Number 和 '(' 黏在一起 
			cout << "Error 3 : there is one extra operand." << endl ;
			return false ;			
		} // else if
		else if ( exp[i-1] == '(' && backward == Operator ) {				// '(' 和 Operation 黏在一起 
			cout << "Error 3 : It is not infix in the parentheses." << endl ;
			return false ;			
		} // else if
		else if ( forward == Operator && exp[i] == ')' ) {					// Operation 和 ')' 黏在一起 
			cout << "Error 3 : It is not infix in the parentheses." << endl ;
			return false ;			
		} // else if
		else if ( exp[i-1] == ')' && backward == Number ) {					// ')' 和 Number 黏在一起 
			cout << "Error 3 : there is one extra operand." << endl ;
			return false ;				
		} // else if
		else if ( exp[i-1] == ')' && exp[i] == '(' ) {					// ')' 和 '(' 黏在一起 
			cout << "Error 3 : there is one extra operand." << endl ;
			return false ;		
		}
		else if ( exp[i-1] == '(' && exp[i] == ')' ) {
			cout << "Error 3 : It is not infix in the parentheses." << endl ;	// '(' 和 ')' 黏在一起 
			return false ; 
		} // else if
		
		forward = backward ;												
	} // for
	
	return true ;
	
} // isLegal

void str2list(const string exp, expLIST<string> & explist) {			// 將字串的東西裝到鏈結串列裡 

	for ( int i = 0 ; i < exp.size() ; i ++ ) {							// 將字串拆成字元放到鏈結串列 
		if ( whatOpt(exp[i]) == Number ) {
			string number ;												
			for (  ; i < exp.size() && whatOpt(exp[i]) == Number ; i ++ ) {	// 如過遇到數字，要把後面的數字接在一起 
				number += exp[i] ;
			} // for
			
			explist.ins(number) ; 									
		} // if
		
		if ( whatOpt(exp[i]) != Number ) {									// 如果遇到非數字就直接放入鏈結串列 

			explist.ins(string(1,exp[i]));
		} // if
	} // for
} // void

bool infix2postfix(expLIST<string> explist) {			// 將中序式轉成後序式 
	string current ;									// 存取目前的字串 
	string move ;										// 存取要從 bottom 移到 postfixExp 的資料 
	string check ;										// 確認 bottom 的值 
	expSTACK<string> bottom ;							// 暫時存取符號 
	expLIST<string> postfixExp ;						// 存取正確後序式 
	bool have_pre = false ;								// 是否要優先做 
	while(!explist.isEmpty()) {							// 將鏈結串列的資料取出，直到為空 
		explist.getdelHead(current) ;					// 將Head的資料取出來並刪除 
		if (whatOpt(current[0]) == Number) { 			// 如果遇到的是數字就優先放入 postfixExp 
			postfixExp.ins(current) ;					
			if ( have_pre ) {							// 如果有遇到優先處理的'*''/'，就可以放完數字就先拿出來 
				bottom.pop(move) ;
				postfixExp.ins(move) ;
				have_pre = false ;
			} // if
		}
		else if ( current[0] == '*' || current[0] == '/' ) // 遇到'*''/'先放入bottom，且標註是優先符號 
		{bottom.push(current) ; have_pre = true ; }	
		else if ( current[0] == '+' || current[0] == '-' ) {	// 遇到'+''-'的處理 
			if ( !bottom.isEmpty()) {
		
				bottom.getTop(check) ;							
				if ( check[0] == '+' || check[0] == '-' ) {		// 如果上一個是加號或減號，則不能在堆疊上去 
					bottom.pop(move) ;							
					postfixExp.ins(move) ;
				} // if
			} // if
			
			bottom.push(current) ;
		} // else if 
		else if ( current[0] == '(' ) {bottom.push(current) ; have_pre = false ;
		} 	// 遇到'('直接放入bottom，並將優先符號歸零 
		else if ( current[0] == ')' ) {			// 遇到')'就要把'('前的符號全部印出來 
			
			bottom.pop(move) ;					
			while(move[0] != '(' ) {
				postfixExp.ins(move) ;
				bottom.pop(move) ;
			} // while
		} // else if
		
	} // while
	
	while ( !bottom.isEmpty() ) {		// 如果到最後 bottom 還有東西全部取出來 
		bottom.pop(move) ;
		postfixExp.ins(move) ;		
	} // while
	
	cout << "Postfix expression: " ;						
	while ( true ) {									// 把後序式列出來 
		string answer ;
		postfixExp.getdelHead(answer) ;
		cout << answer ;
		if (!postfixExp.isEmpty()) cout << ", " ;
		else { cout << endl ; break ;
		}
	} // while
	
	return true ;
} // infix2postfix

Opt whatOpt( const char operation ) {										// 把 operation 分類 
	if ( operation >= 48 && operation <= 57 ) return Number ;				// 0~9 分成 Number 
	else if ( operation == '(' || operation == ')' ) return Balance ;		// ( ) 分成 Balance 
	else if ( operation == '+' || operation == '-' || operation == '*' || operation == '/' ) return Operator ; // +-*/ 分成 operation, 
} // whatOpt






