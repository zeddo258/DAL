// 11127220 ³¢¤d»² 
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <iostream>
# include <vector>
#include <cctype>  // calculate
# include <cstdlib>  // system, atoi
# include <fstream>  // read file
#define MAX_LEN 255 // maximum string length

using namespace std ;

struct Node {
	char ch ;
	Node *next ; 
};

class Stackop {
    private: 
        vector<char> op ;
    public:
		bool empty() {
			if ( op.empty() ) 
                return true ;
			else
                return false ;
		}
		
		int size() {
			return op.size() ;
		}
		
		char top() {
			return op.back() ;  // return the last data
		}
		
		void pop() {
			op.pop_back() ;  // delete last data
		}
		
		void push(char ch) {
			op.push_back(ch) ;  // enter a data
		}
};

class Stacknum {
    private:
        vector<int> num ;
    public:
		bool empty() {
			if ( num.empty() ) 
                return true ;
			else
                return false ;
		}
		
		int size() {
			return num.size() ;
		}
		
		char top() {
			return num.back() ;
		}
		
		void pop() {
			num.pop_back() ;
		}
		
		void push(int i) {
			num.push_back(i) ;
		}
};

class Mission1 {
    public:
        bool isDigit( char ch ) {
            if ( isdigit(ch) ) 
                return true ;
            else
                return false ;
        } // isDigit()

        bool isOperator( char ch ) {
            if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' )
                return true ;
            else
                return false ;
        } // isOp()

        bool isPar( char ch ) {  // check whether it is () or not
            if ( ch == '(' || ch == ')' )
                return true ;
            else
                return false ;
        } // isPar()

        bool isSpace( char ch ) {
            if ( ch == ' ' || ch == '\t' )
                return true ;
            else
                return false ;
        } // isSpace()

        bool whitSpace( string str ) {  // check only space
            int count = 0 ;
            for ( int i = 0 ; i < str.size() ; i = i + 1 ) {
                if ( isSpace(str[i]) )
                    count = count + 1 ;
            } // for
    
            if ( count == str.size() )
                return true ;
            else
                return false ;
        } // whitSpace()

        bool isExp( string str ) {  // check the validity of each symbol
            if ( whitSpace(str) || str.size() == 0 )
                return false ;
            for ( int i = 0 ; i < str.size() ; i = i + 1 ) {
                if ( !isDigit(str[i]) && !isOperator(str[i]) && !isPar(str[i]) && !isSpace(str[i]) )
                    return false ;
            } // for
    
            return true ;
        } // isExp()

        bool isBalanced( string str ) {  // check the validity of balanced parentheses
            int right = 0, left = 0 ;
            for ( int i = 0 ; i < str.size() ; i = i + 1 ) {
                if ( str[i] == '(' )
                    left = left + 1 ;
                else if ( str[i] == ')' )
                    right = right + 1 ;
            } // for
    
            if ( right != left )
                return false ;
            else
                return true ;
        } // isBalanced()

        int isBalance( string str ) {  // check the validity of balanced parentheses
            int right = 0, left = 0 ;
            for ( int i = 0 ; i < str.size() ; i = i + 1 ) {
                if ( str[i] == '(' )
                    left = left + 1 ;
                else if ( str[i] == ')' )
                    right = right + 1 ;
            } // for
    
            if ( right < left )
                return 1 ;
            else if ( right > left )
                return 2 ;
            else
                return 0 ;
        } // isBalance()

        bool isLegal( string str ) {  // check whether it is a legal expression
            if ( isOperator(str[0]) || isOperator(str[str.size()-1]) || str[0] == ')' )
                return false ;
            for ( int i = 0 ; i < str.size() ; i = i + 1 ) {
                if ( isOperator(str[i]) || str[i] == '(' ) {
                    if ( isOperator(str[i+1]) || str[i+1] == ')' )
                        return false ;
                } // if
        
                if ( str[i] == ')' ) {
                    if ( isDigit(str[i+1]) || str[i+1] == '(' )
                        return false ;
                } // if
            } // for
    
                return true ;
        } // isLegal

        bool error(string str) {  // print error message
            for ( int i = 0 ; i < str.size() ; i = i + 1 ) {
		        if ( !isDigit(str[i]) && !isOperator(str[i]) && !isPar(str[i]) && !isSpace(str[i]) ) {  // error1
			        cout << "Error 1: " << str[i] << " is not a legitimate character." << endl ;
			        return false ;
		        } // if	
	        } // for
	
	        if ( isBalance(str) == 1 ) {  // error2( right < left )
	            cout << "Error 2: there is one extra open parenthesis." << endl;
	            return false;
	        } // if
	        else if ( isBalance(str) == 2 ) {  // error2( right > left )
	            cout << "Error 2: there is one extra close parenthesis." << endl;
	            return false;
	        } // else if
	
            if ( whitSpace(str) || str.size() == 0 ) {  // error3( only one whitespace || no input )
        	    cout << "Error 3: there is one extra operator." << endl;
		        return false;
            } // if
    
            for ( int i = 0 ; i < str.size() ; i = i + 1 ) {  // error3
		        if ( isOperator(str[i]) ) {  // extra operator
		            if ( isOperator(str[i+1]) || ( i + 1 ) == str.size() || 
                            isOperator(str[str.size() - 1]) ) {
                        cout << "Error 3: there is one extra operator." << endl;
			            return false ;
                    } // if
		        } // if	
	        } // for
	
	        for ( int i = 0 ; i < str.size() ; i = i + 1 ) {  // error3
		        if ( str[i] == ')' ) {  // extra operand( extra op after ')' )
		            if ( isDigit(str[i+1]) || str[i+1] == '(' ) {
                        cout << "Error 3: there is one extra operand." << endl;
			            return false ;
                    } // if
		        } // if	 
		        else if ( isDigit(str[i]) ) {  // extra operand( extra op before '(' )
		            if ( str[i+1] == '(' ) {
		                cout << "Error 3: there is one extra operand." << endl;
			            return false ;
                    } // if
                } // else if 
                else if ( str[i] == '(' ) {  // (), ( ), (op) 
                    if ( str[i+1] == ')' || isSpace(str[i+1]) || isOperator(str[i+1]) ) {
                        cout << "Error 3: it is not infix in the parentheses." << endl;
		                return false;
                    } // if
                } // else if
	        } // for
        
	        return true ;
        } // error()
};

class Mission2 {
    private:
        Node *head ;
        Node *run ;
    public:
        bool isDigit( char ch ) {
            if ( isdigit(ch) ) 
                return true ;
            else
                return false ;
        } // isDigit()

        bool isOperator( char ch ) {
            if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' )
                return true ;
            else
                return false ;
        } // isOp()
        
        bool isSpace( char ch ) {
            if ( ch == ' ' || ch == '\t' )
                return true ;
            else
                return false ;
        } // isSpace()
        
        void str2list( string str ) {  // parse a string into a linked list  
            head = nullptr ;       
            Node *store = head ;

	        for ( int i = 0 ; i < str.size() ; i = i + 1 ) {
		        if ( !isSpace(str[i]) ) {
			        if (head == nullptr) { // first
                        head = new Node ;
                        head -> ch = str[i] ;
                        head -> next = nullptr ;
                        store = head ;
                    } // if
                    else {
                        store -> next = new Node ;
                        store = store -> next ;
                        store -> ch = str[i] ;
                        store -> next = nullptr ;
                    } // else
		        } // if
	        } // for
      
	        store = nullptr ;
	        delete store ;
        } // str2list()

        void infix2postfix() {  // transform infix into postfix
            run = nullptr ;
            Stackop op ;
            Node *data = run ;
            
            while ( head != nullptr ) {  // last data = NULL
                if ( run == nullptr ) {  // first
                    run = new Node ;
                    run -> next = nullptr ;
                    data = run ;
                } // if
                
		        if ( isDigit(head -> ch) ) {  // is digit >>>>> store
			        data -> ch = head -> ch ;
			        data -> next = new Node ;
			        data = data -> next ;
			        data -> next = nullptr ;
	           	} // if
		        else if ( head -> ch == '(' ) // ch = '(' >>>>> stake
                    op.push( head -> ch ) ;    
		        else if ( head -> ch == ')' ) {  // ch = ')'
                    if ( op.top() != '(' ) {
			       	    data -> ch = ',' ;
				        data -> next = new Node ;
				        data = data -> next ;
				        data -> next = nullptr ;
			        } // if
                    		
			        while ( !op.empty() && op.top() != '(' ) {  // store op into Node
				        data -> ch = op.top() ;
				        data -> next = new Node ;
				        data = data -> next ;
				        data -> next = nullptr ;
				        op.pop() ;
			        } // while
			         
                    op.pop() ;  // delete '('
		        } // else if
        		else {  // not num, '(' or ')'
        		    if( isOperator(head -> ch) ) {
        		        data -> ch = ',' ;
			            data -> next = new Node ;
			            data = data -> next ;
			            data -> next = nullptr ;
                    } // if
                    
		            if ( head -> ch == '*' || head -> ch == '/' ) {  // '*' && '/'
				        if ( op.empty() )  // nothing in op, push back
					       op.push( head -> ch ) ;
				        else if ( op.top() == '*' || op.top() == '/' ) {  // extra op there
					       data -> ch = op.top() ;  // store data
					       op.pop() ;  // delete
					       data -> next = new Node;
					       data = data -> next;
					       data -> next = nullptr ;
					       op.push( head -> ch ) ;  // push back 
				        } // else if
				        else
					       op.push( head -> ch) ;
			        } // if
			        else if ( head -> ch == '+' || head -> ch == '-' ) {  // '+' && '-'
				        if ( op.empty() || op.top() == '(' )  // num +/- num
					       op.push( head -> ch ) ;
				        else {
					        while ( !op.empty() && op.top() != '(' ) {  // one/more op inside
						        data -> ch = op.top() ;
						        data -> next = new Node ;
						        data = data -> next ;
						        data -> next = nullptr ;
						        op.pop() ;
					        } // while
					        
					        op.push( head -> ch ) ;
				        } // else
			        } // else if	
		        } // else
		        
		        head = head -> next ;
	        } // while
	        while ( !op.empty() ) {  // clear stack op 
		        if ( op.top() != '(' ) {
		            data -> ch = ',' ;
			        data -> next = new Node ;
			        data = data -> next ;
			        data -> next = nullptr ;
			        data -> ch = op.top() ;
			        data -> next = new Node ;
			        data = data -> next ;
			        data -> next = nullptr ;
		        } // if
		        
		        op.pop();
	        } // while
	        
	        head = nullptr ;
	        delete head ;
	        data = nullptr ;
	        delete data ;
	        
            cout << "Postfix expression: " ;
            while ( run -> next != nullptr ) {  // print
                cout << run -> ch ;
                if ( run -> ch == ',' ) 
                    cout << " " ;
                else if ( run -> next -> next != nullptr && isOperator(run -> ch) && run -> next -> ch != ',' )
                    cout << ", " ;
                run = run -> next ;
            } // while
            
            cout << endl ;
            
        } // infix2postfix() 
};

int main(void)
{   int command = 0 ;  // user command
    Mission1 mission1 ;
    Mission2 mission2 ;
    do
    {   string infixS ; 
        cout << endl << "* Arithmetic Expression Evaluator *" ;
        cout << endl << "* 0. Quit                         *" ;
        cout << endl << "* 1. infix2postfix Transformation *" ;
        cout << endl << "***********************************" ;
        cout << endl << "Input a choice(0, 1): " ;
        cin >> command ;  // get the command
        cin.ignore(MAX_LEN, '\n') ;  // clear the input buffer
        switch(command) 
        {   case 0: break ;
            case 1: cout << endl << "Input an infix expression: " ;
                    getline(cin, infixS) ;
                    if(mission1.isExp(infixS) &&  // cheack each symbol & remove useless one
                        mission1.isBalanced(infixS) &&  // check the validity of balanced parentheses
                        mission1.isLegal(infixS) )  // check whether it is a legal expression
                    {
                        cout << "It is a legitimate infix expression." << endl ;  // mission1
                        mission2.str2list(infixS) ;  // parse a string into a linked list
                        mission2.infix2postfix() ; // transform infixS into postfixS
                        // Mission One: check whether it is an infix expression
                        // Mission Two: transform infix to postfix, stored as a linked list
                    } // end of if 
                    else
                        mission1.error(infixS) ;                   
                    break ;
            default: cout << endl << "Command dose not exist!" << endl ;
        } // end switch
    } while(command != 0) ;  // '0': stop the program
    system("pause") ;  // pause the display
    return 0 ;
} // end of main
