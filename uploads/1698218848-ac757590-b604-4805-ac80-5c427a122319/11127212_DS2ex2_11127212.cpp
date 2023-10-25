// 11127212 ���դ� 
# include <iostream>	// string class
# include <string>		// system, atoi
# include <sstream>
# include <cstdlib>
# include <new>
# define MAX_LEN 255 	// maximum string length


using namespace std ;
const char legal[17] = {'1','2','3','4','5','6','7','8','9','0','+','-','*','/','(',')',' ' } ;		// �⥿�T���r���C�X�� 
enum Opt { Number, Operator, Balance };  															// �N�Ÿ����� 
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
			listNode *current = new listNode ;	// �]�w�s������ current 
			current->value = inValue ;			// ���Ʃ�� value �� 
			current->next = NULL ;				// �N�U�@���Ы��V NULL  
			if ( head == NULL ) {
				head = current ;				// �p�G LIST �̭��O�šA�N Head �M tail ���V current 
				tail = head ;
			} // if
			
			else {
												// ��s����D��ƪ��᭱ 
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
		listNode *delet = head ;			// �]�@�� delete ���Ы��V head (�n�R�������) 
		outValue = head->value ;			// �^�� head -> value ���� 
		head = head->next ;					// head ���V head -> next 
		delete delet ;						// �R���L�Ϋ��� 
		
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
				stackNode *current = new stackNode ;	// �]�w�s������ current  
				current->value = inValue ;				// ���Ʃ�� value �� 
				current->next = NULL ;					// �N�U�@���Ы��V NULL 
				if ( topPtr == NULL ) {					// �u�n Stack �O NULL 
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

bool isExp(string & exp) {								// �P�_�O�_�����T�r���H�~���r�� 
	string non_space ;									// �]�@�Ӧr��O�S���Ů檺 
	for ( int i = 0 ; i < exp.size() ; i ++ ) {			// �P�_ exp �̪��r���O�_�M lebal �@�ˡA���@�� return false  
		if ( exp[i] != ' ' ) non_space += exp[i] ;		// ��D�ťժ��r����i non_space 
		for ( int j = 0 ; j < 18 ; j ++ ) {
			if ( j == 17 ) {
				cout << "Error 1 : " << exp[i] << " is not a legitimate character." << endl ;
				return false ;
			}
			if ( exp[i] == legal[j] ) break ;
		} // for
	} // for
	
	exp = non_space ;									// �� exp �令 non_space 
	return true ;
} // end isExp

bool isBalanced(const string exp) {						// �P�_�A���O�_�������� 
	int balance = 0 ;									// ���ƥN�� '(' ����h�A�t�ƥN�� ')' ����h 
	for ( int i = 0 ; i < exp.size() ; i ++ ) {			 
		if ( exp[i] == '(' ) balance ++ ;				// �p�G�J�� '('�A balance + 1 
		else if ( exp[i] == ')' ) balance -- ;			// �p�G�J�� ')' �A balance - 1 
		if ( balance < 0 ) {							// �p�G balance < 0 ��� ')' �e���S�� '(' 
			cout << "Error 2 : there is one extra close parenthesis." << endl ;
			return false ;
		} // if
	} // for
	
	if (balance > 0) {									// �p�G balance > 0 ��� '(' ����h 
		cout << "Error 2 : there is one extra open parenthesis." << endl ;
		return false ;
	} // if
	
	return true ;
} // isBalanced()

bool isLegal(const string exp) { 											// �P�_�O���O���Ǧ� 
	Opt forward, backward ;													// �]�w�e�����r���M�᭱���r�����O 
	forward = whatOpt(exp[0]) ;												// ���o�e�����r�����O 
	if ( exp.size() == 1 ) {												// �p�G�⦡�u���@�Ӧr���u�n�P�_���O�_���Ʀr 
		if ( forward == Number ) return true ;								
		else {
			cout << "Error 3 : there is one extra operator." << endl ;
			return false ;
		}
	}
	
	for ( int i = 1 ; i < exp.size() ; i ++ ) {								// �P�_�O�_�����X�z����k 
		backward = whatOpt(exp[i]) ;
		if ( forward == Operator && backward == Operator ) {				// ��ӲŸ��H�b�@�_ 
			cout << "Error 3 : there is one extra operator." << endl ;
			return false ;			
		} // if
		else if ( forward == Number && exp[i] == '(' ) {					// Number �M '(' �H�b�@�_ 
			cout << "Error 3 : there is one extra operand." << endl ;
			return false ;			
		} // else if
		else if ( exp[i-1] == '(' && backward == Operator ) {				// '(' �M Operation �H�b�@�_ 
			cout << "Error 3 : It is not infix in the parentheses." << endl ;
			return false ;			
		} // else if
		else if ( forward == Operator && exp[i] == ')' ) {					// Operation �M ')' �H�b�@�_ 
			cout << "Error 3 : It is not infix in the parentheses." << endl ;
			return false ;			
		} // else if
		else if ( exp[i-1] == ')' && backward == Number ) {					// ')' �M Number �H�b�@�_ 
			cout << "Error 3 : there is one extra operand." << endl ;
			return false ;				
		} // else if
		else if ( exp[i-1] == ')' && exp[i] == '(' ) {					// ')' �M '(' �H�b�@�_ 
			cout << "Error 3 : there is one extra operand." << endl ;
			return false ;		
		}
		else if ( exp[i-1] == '(' && exp[i] == ')' ) {
			cout << "Error 3 : It is not infix in the parentheses." << endl ;	// '(' �M ')' �H�b�@�_ 
			return false ; 
		} // else if
		
		forward = backward ;												
	} // for
	
	return true ;
	
} // isLegal

void str2list(const string exp, expLIST<string> & explist) {			// �N�r�ꪺ�F��˨��쵲��C�� 

	for ( int i = 0 ; i < exp.size() ; i ++ ) {							// �N�r���r������쵲��C 
		if ( whatOpt(exp[i]) == Number ) {
			string number ;												
			for (  ; i < exp.size() && whatOpt(exp[i]) == Number ; i ++ ) {	// �p�L�J��Ʀr�A�n��᭱���Ʀr���b�@�_ 
				number += exp[i] ;
			} // for
			
			explist.ins(number) ; 									
		} // if
		
		if ( whatOpt(exp[i]) != Number ) {									// �p�G�J��D�Ʀr�N������J�쵲��C 

			explist.ins(string(1,exp[i]));
		} // if
	} // for
} // void

bool infix2postfix(expLIST<string> explist) {			// �N���Ǧ��ন��Ǧ� 
	string current ;									// �s���ثe���r�� 
	string move ;										// �s���n�q bottom ���� postfixExp ����� 
	string check ;										// �T�{ bottom ���� 
	expSTACK<string> bottom ;							// �Ȯɦs���Ÿ� 
	expLIST<string> postfixExp ;						// �s�����T��Ǧ� 
	bool have_pre = false ;								// �O�_�n�u���� 
	while(!explist.isEmpty()) {							// �N�쵲��C����ƨ��X�A���쬰�� 
		explist.getdelHead(current) ;					// �NHead����ƨ��X�ӨçR�� 
		if (whatOpt(current[0]) == Number) { 			// �p�G�J�쪺�O�Ʀr�N�u����J postfixExp 
			postfixExp.ins(current) ;					
			if ( have_pre ) {							// �p�G���J���u���B�z��'*''/'�A�N�i�H�񧹼Ʀr�N�����X�� 
				bottom.pop(move) ;
				postfixExp.ins(move) ;
				have_pre = false ;
			} // if
		}
		else if ( current[0] == '*' || current[0] == '/' ) // �J��'*''/'����Jbottom�A�B�е��O�u���Ÿ� 
		{bottom.push(current) ; have_pre = true ; }	
		else if ( current[0] == '+' || current[0] == '-' ) {	// �J��'+''-'���B�z 
			if ( !bottom.isEmpty()) {
		
				bottom.getTop(check) ;							
				if ( check[0] == '+' || check[0] == '-' ) {		// �p�G�W�@�ӬO�[���δ�A�h����b���|�W�h 
					bottom.pop(move) ;							
					postfixExp.ins(move) ;
				} // if
			} // if
			
			bottom.push(current) ;
		} // else if 
		else if ( current[0] == '(' ) {bottom.push(current) ; have_pre = false ;
		} 	// �J��'('������Jbottom�A�ñN�u���Ÿ��k�s 
		else if ( current[0] == ')' ) {			// �J��')'�N�n��'('�e���Ÿ������L�X�� 
			
			bottom.pop(move) ;					
			while(move[0] != '(' ) {
				postfixExp.ins(move) ;
				bottom.pop(move) ;
			} // while
		} // else if
		
	} // while
	
	while ( !bottom.isEmpty() ) {		// �p�G��̫� bottom �٦��F��������X�� 
		bottom.pop(move) ;
		postfixExp.ins(move) ;		
	} // while
	
	cout << "Postfix expression: " ;						
	while ( true ) {									// ���Ǧ��C�X�� 
		string answer ;
		postfixExp.getdelHead(answer) ;
		cout << answer ;
		if (!postfixExp.isEmpty()) cout << ", " ;
		else { cout << endl ; break ;
		}
	} // while
	
	return true ;
} // infix2postfix

Opt whatOpt( const char operation ) {										// �� operation ���� 
	if ( operation >= 48 && operation <= 57 ) return Number ;				// 0~9 ���� Number 
	else if ( operation == '(' || operation == ')' ) return Balance ;		// ( ) ���� Balance 
	else if ( operation == '+' || operation == '-' || operation == '*' || operation == '/' ) return Operator ; // +-*/ ���� operation, 
} // whatOpt






