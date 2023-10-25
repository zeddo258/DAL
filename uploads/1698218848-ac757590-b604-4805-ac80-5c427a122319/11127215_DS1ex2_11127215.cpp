//  11127215 李宗翰 
#include <string> // string class
#include <iostream>
#include <cstdlib> // system, atoi
#include <new> // new 


#define MAX_LEN 255 // maximum string length

using namespace std;
template< class T > // type template for data value in stack node
class expSTACK 
{
  
  typedef struct sN // structure of each element in stack
  {	T value;
  	struct sN * next; // next element
  }	stackNode;
  
  stackNode * topPtr; // only one data member
public: 
  expSTACK(): topPtr( NULL ) // constructor with initialization
  {} // end expSTACK initializer
  
  bool isEmpty() const // decide whether stack is empty
  {  return topPtr == NULL;
  } // end expSTACK:: isEmpty
  
  
  void push( const T inValue ) // add one element into stack
  { try 
    { 
      if ( topPtr == NULL ) {
      	
      	topPtr = new stackNode;
      	topPtr -> next = NULL;
      	topPtr -> value = inValue;
	  }
	  
	  else {
	  	  stackNode * newPtr = new stackNode;
		  newPtr -> value = inValue;
		  newPtr -> next = topPtr;
		  topPtr = newPtr; 
	  	
	  }
	} // end try
	
	catch (std::bad_alloc & ba ) // unable to allocate space
	{ std::cerr << endl << "bad_alloc on stack caught:" << ba.what() << endl;
	} // end catch
  } // end expSTACK::push
  
  void getTop( T & outvalue ) // get the top of stack without removal
  {
  	if ( ! isEmpty() )
  	   outvalue = topPtr -> value; 
  } // end expSTACK::getTop
  
  void pop() // remove the top of stack
  {
  	if ( ! isEmpty() ) 
  	{ stackNode * temp = topPtr;
  	  topPtr = topPtr -> next;
  	  temp -> next = NULL;
  	  delete temp;
	} // end if
    
  } // end expSTACK::pop without output parameter
  
  void pop( T & outValue ) // get the top of stack and remove it
  { 
    if ( ! isEmpty() ) 
	{    outValue = topPtr -> value;
	     stackNode * temp = topPtr;
  	     topPtr = topPtr -> next;
  	     temp -> next = NULL;
  	     delete temp; 
	} // end if
  } // end expSTACK::pop with output parameter
  
  ~expSTACK() // destructor
  {  while ( ! isEmpty())
       pop();
  } // end destructor
  
}; // end expSTACK class

bool isExp( string &str ) { // check the validity of each symbol
    
	 
	
    for ( int i = 0 ; i < str.length() ; i++ ) {
       // 去除空白
       
	  while ( str.at( i ) == ' ' ) {
	    str.replace( i , 1 , "" );
	  } //  while
   
	  if ( str.at( i ) != '+' && str.at( i ) != '-' && str.at( i ) != '*' && str.at( i ) != '/'
	         && str.at( i ) != '(' && str.at( i ) != ')' ) {
      	if ( str.at( i ) < 48 || str.at( i ) > 57 ) { // this symbol is one number from 0 to 9
      	  cout << "Error 1: " << str.at( i ) << " is not a legitimate character.\n";
          return false;
	    } // end if
	  } // end if
	} // end for
    
    return true;
} // end isExp()

bool isBalanced( string str ) { // check the validity of balanced parentheses(括號)
  int left = 0 , right = 0; // left 左括數 right 右括數 
  for ( int i = 0 ; i < str.length() ; i++ ) {
  	if ( str.at( i ) == '(' ) {
  	  left++;	
	} // end if
	  
	else if ( str.at( i ) == ')' ) {
	  right++;
	} // end else if
  } // end for
  
  if ( left == right ) {
  	return true;
  } // end if
  
  else if ( left > right ) {
  	cout << "Error 2: there is one extra open parentheses.\n";
  	return false;
  } // end else if
  
  else {
  	cout << "Error 2: there is one extra close parentheses.\n";
  	return false;
  } // end else 
} // end isBalanced()
            
bool isLegal( string str ) { // check whether it is a legal expression

   
  for ( int i = 0 ; i < str.length() ; i++ ) {
  	
  	// 運算符號不能在頭尾，也不能連續出現 
  	
    if ( str.at( i ) == '+' || str.at( i ) == '-' || str.at( i ) == '*' || str.at( i ) == '/' ) {
      if ( i == 0 || i == str.length() - 1 || ( str.at( i + 1 ) == '+' || str.at( i + 1 ) == '-' || str.at( i + 1 ) == '*' || str.at( i + 1 ) == '/' ) 
	     ) {
	    cout << "Error 3: there is one extra operator.\n";
	    return false;
	  } // end if
	} // end if

    // 括號內不得為空 
    
	if ( str.at( i ) == '(' && str.at( i + 1 ) == ')' ) {
	  cout << "Error 3: it is not infix in the parentheses.\n";
	  return false;
	} // end if
	
	// 左括號前 、 右括號後不能為數字 
	
	if ( str.at( i ) == '(' && i != 0 ) { 
      if ( str.at( i - 1 ) >= 48 && str.at( i - 1 ) <= 57 ) {
	    cout << "Error 3: there is one extra operand.\n";
	    return false;
      } // end if    
	} // end if
	
	else if ( str.at( i ) == ')' && i != str.length() - 1 ) {
	  if ( str.at( i + 1 ) >= 48 && str.at( i + 1 ) <= 57 ) {
	    cout << "Error 3: there is one extra operand.\n";
	    return false;
      } // end if    
	} // end else if
  } // end for
  
  return true;
} // end isLegal()

// parse a string into a linked list

/*
void str2list( String str ) { 
    
  
}

*/

// transform infix into postfix

bool infix2postfix ( string str ) { 
  
  expSTACK<char> expstack;
  bool num = false;
  //bool isEmpty = true; // 判斷是否已讀過+-*/
  char value = '\0';
  /*
  if () {
  	return false; 
  } // end if
  */
  
 
  for ( int i = 0; i < str.length() ; i++ ) {
  	// 是運算數就直接印出
	
    if ( str.at( i ) != '+' && str.at( i ) != '-' && str.at( i ) != '*' 
	     && str.at( i ) != '/'  && str.at( i ) != '(' && str.at( i ) != ')' ) 
    {
      cout << str.at( i ); 
    } // end if 
 
    // 遇到右括號 
	   
	else if ( str.at( i ) == ')' ) { 
	  expstack.getTop( value );
	  
	  while ( value != '(' ) {
	  	cout << ", ";
	    cout << value;    
	  	expstack.pop();
	  	expstack.getTop( value );	
	  } // while
	  
	  expstack.pop();
	  
	} // end else if
	
    else { 
      cout << ", ";
	  // 左括號直接堆疊
	   
      if ( expstack.isEmpty() || str.at( i ) == '(' ) {
      	
      	expstack.push( str.at( i ) );
		continue; 
// 不是左括號判斷stack是否為空( 只有左括也可視為空 )
	  }
      
      else {
	  
	  	expstack.getTop( value );
	  	
	  
	  }
	
	  if ( value == '(' ) {
	  	
	  	expstack.push( str.at( i ) );
	  	
	  }
	  
	  
      else { 

		expstack.getTop( value ); 
		if ( value == '*' || value == '/' ) {
		  	expstack.pop( value ); 
		  	cout << value;
		  	cout << ", ";
		   	if ( ! expstack.isEmpty() ) {
		      	if ( str.at( i ) == '+' || str.at( i ) == '-' ) {
		          expstack.pop( value ); 
		  	   	  cout << value;
		  	   	  cout << ", ";
		  	   	  expstack.push( str.at( i ) );
				} // end if
				  	
		        else {
				  expstack.push( str.at( i ) );
				} // end else
		        
		    } // end if
			  
		    else {
			    expstack.push( str.at( i ) );	
			}   // else 
		} // end if
		 
		// 前一個是 + -	 
		 
		else {
			
		  if ( str.at(i) == '+' || str.at(i) == '-' ) {
		  	
		  	expstack.pop( value ); 
		  	cout << value;
		  	cout << ", ";
		  	expstack.push( str.at( i ) );
		  	
		  } // end if 
		  
		  else {
		  	
	        expstack.push( str.at( i ) );
		  } // else
		  			
		} // else	
			
	  }	// end if
		  
	}
		 
  } // end for
  
  while ( ! expstack.isEmpty()  ) {
  	//cout << ", ";
	expstack.pop( value );
	cout << value;
	
	if ( ! expstack.isEmpty() )
	  cout << ", ";
	
  } // while
	
  return true;
} // end infix2postfix() 

int main( void ) {		
  int command = 0; // user command	
  while (1) {
    string infixS = "\0";
    cout << endl << "* Arithmetic Expression Evaluator *"	;
    cout << endl << "* 0. QUIT                         *";	
    cout << endl << "* 1. Infix2postfix Transformation *";	
    cout << endl << "***********************************";
    cout << endl << "Input a choice(0, 1): ";
    cin >> command; // get a command
    cin.ignore( MAX_LEN, '\n' ); // clear the input buffer
	if ( command == 0 ) {
	  system( "pause" );
	  return 0;  	
	} // end if	
	
	else if ( command == 1 ){
	  cout << endl << "Input an infix expression: "; 	
	  getline(cin, infixS);
	  if ( isExp( infixS ) // check each symbol & remove useless ones
	       && isBalanced( infixS )  // check the validity of balanced parentheses(括號)  
	       && isLegal( infixS ) // check whether it is a legal expression
		 ) { 
		cout << "It is a legitimate infix expression.";
		
	   // str2list( infixS ); // parse a string into a linked list
		infix2postfix( infixS ) ;// transform infixS into postfixS 
	     
	  } // end if
	} // end else if
	
	else {
	  cout << endl << "Command does not exist!" << endl;
	} // end else
	
  } // end while	
} // end main
