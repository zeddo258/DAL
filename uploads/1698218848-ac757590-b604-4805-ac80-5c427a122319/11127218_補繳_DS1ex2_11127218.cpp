//11127218 林岑翰 
#include <string>                    // string class
#include <cstdlib>                   // system, atoi
#include <cctype>
#include <iostream>
# include <new>
# include <string.h>  // string class 
using namespace std;

template<class T>   // type template for data value in list node
class expLIST
{   typedef struct qN   // structure of each node in list
    {   T       value;
        struct qN       *next;  // next element
    }   listNode;
    listNode*head,*tail;    // only two data members
public:
    expLIST():head(NULL),tail(NULL)     // constructor with initialization
    {}  // end expLIST initializer

	void append(const T& value)      // append new value 
    {
        listNode* newNode = new listNode;
        newNode->value = value;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    bool isEmpty() const
    {
        return head == NULL;
    }   // end expLIST::isEmpty

    void getHead(T& outValue)   // get the head of list without removal
    {
        outValue = head -> value;
    }   // end expLIST::getHead

    void del()  // remove the head of list
    {
        listNode *temp = head;
        head = head -> next;
        delete temp;
    }   // end expLIST::del outout parameter

    void del(T& outValue)   // get the head of stack and remove it
    {
        outValue = head -> value;
        del();
    }   // end expLIST::del outout parameter

	void display()
	{
    	listNode* current = head;
    	while (current)
    	{
        	cout << current->value;
        	if (current->next )           // not the last value
        	{
            	cout << ", ";
        	}
        	current = current->next;
    	}
    	cout << endl;
	}


	


    void clearUp()  // clear up the entire list
    {
        while ( !isEmpty() ){
        	del();
		}
    }   // end expLIST::clearUp

    ~expLIST()  // destructor
    {
        clearUp();
    }   // end expLIST class
    



};  // end expLIST class
//***********************************************************/
//The above is self-defined expLIST class, used for keeping a series of values
//***********************************************************/

using namespace std;

template <class T>                          // type template for data value in stack node
class expSTACK
{   typedef struct sN                       // structure of each element in stack
    {   T       value;
        struct sN   *next;                  // next element
    }   stackNode;

    stackNode *topPtr;                      // only one data member

public:
    expSTACK():topPtr(NULL)                 // constructor with initialization
    {} // end expSTACK initializer

    bool isEmpty()  const                   // decide whether stack is empty
    {   return topPtr == NULL ;
    }   //end expSTACK::isEmpty

    void push( const T inValue)             // push element into stack
    {   
        stackNode *newNode = new stackNode;
        newNode->value = inValue;
        newNode->next = topPtr;
        topPtr = newNode;
            
    }  //  end push
        
      

    void getTop(T& outValue)            //  get the top of stack without removal
    {
        outValue = topPtr -> value; 
        
    }  //  end expSTACK::getTop

    void pop()              //  remove the top of stack
    {
        stackNode *temp = topPtr;
        topPtr = topPtr -> next;
        delete temp;
        
    }  //  end expSTACK::pop without output parameter

    void pop(T& outValue)           //  get the top of stack and remove it
    {   
		getTop(outValue) ;
        pop();
        
    }   // end expSTACK::pop with output parameter


	
    ~expSTACK()             // destructor
    {   
		while (!isEmpty())
        pop() ;
    }   // end destructor

};      // end expSTACK class
 
#define MAX_LEN 255                   // maximum string length

bool isExp(string & inifix)                 // check the validity of each symbol
{	
	
	for ( int i = 0; i < inifix.length(); i++ ){
		if ( !isdigit( inifix[i] ) && inifix[i] != ' ' && inifix[i] != '(' && inifix[i] != ')' 
			 && inifix[i] != '+' && inifix[i] != '-' && inifix[i] != '*' && inifix[i] != '/' )
		{
			cout << "Error 1 : " << inifix[i] << " is not a legitimate character.";
			return false;
		}
		
	}
	return true;
}
bool isBalanced(const string inifix)       // check the validity of balanced parentheses
{
	int countOpen = 0;
    int countClose = 0;

    for ( int i = 0; i < inifix.length(); i++ ){         // count open and close parentheses
        if ( inifix[i] == '(') {
            countOpen++;
        } else if ( inifix[i] == ')') {
            countClose++;
        }
	}
        if (countClose > countOpen) {                                  //  check whether ( == )
        	cout << "Error 2 : there is one extra close parenthesis.";
            return false;
        }
        if (countClose < countOpen) {
        	cout << "Error 2 : there is one extra open parenthesis.";
            return false;
        }
    

    return true;
	
}
bool isLegal(const string inifix)
{
	for ( int i = 0; i < inifix.length(); i++ ){
		if ( inifix[i] == '*' ){                                      
			if ( i == 0 || i == inifix.size() ){                        // * can't be the first one or the last 
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
			else if ( !isdigit( inifix[ i + 1 ] ) && inifix[ i + 1 ] != '(' && inifix[ i + 1 ] != ' ' ){           // * can't add non-digit or non-( or other operator behimd 
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
			else if ( !isdigit( inifix[ i - 1 ] ) && inifix[ i - 1 ] != ')' && inifix[ i - 1 ] != ' ' ){            // * can't add non-digit or non-( or other operator before
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
		}
		else if ( inifix[i] == '+' ){
			if ( i == 0 || i == inifix.size() ){
				cout << "Error 3 : there is one extra operator.";                    // + can't be the first one or the last 
				return false;
			}
			else if ( !isdigit( inifix[ i + 1 ] ) && inifix[ i + 1 ] != '(' && inifix[ i + 1 ] != ' ' ){                   // + can't add non-digit or non-( or other operator behimd 
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
			else if ( !isdigit( inifix[ i - 1 ] ) && inifix[ i - 1 ] != ')' && inifix[ i - 1 ] != ' ' ){                  // + can't add non-digit or non-( or other operator before
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
		}
		else if ( inifix[i] == '-' ){                                                                               
			if ( i == 0 || i == inifix.size() ){                                  // - can't be the first one or the last
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
			else if ( !isdigit( inifix[ i + 1 ] ) && inifix[ i + 1 ] != '(' && inifix[ i + 1 ] != ' ' ){                // - can't add non-digit or non-( or other operator behimd 
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
			else if ( !isdigit( inifix[ i - 1 ] ) && inifix[ i - 1 ] != ')' && inifix[ i - 1 ] != ' ' ){                // - can't add non-digit or non-( or other operator before
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
		}
		else if ( inifix[i] == '/' ){
			if ( i == 0 || i == inifix.size() ){                                                               // / can't be the first one or the last
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
			else if ( !isdigit( inifix[ i + 1 ] ) && inifix[ i + 1 ] != '(' && inifix[ i + 1 ] != ' ' ){                     // / can't add non-digit or non-( or other operator behimd 
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
			else if ( !isdigit( inifix[ i - 1 ] ) && inifix[ i - 1 ] != ')' && inifix[ i - 1 ] != ' ' ){                     // / can't add non-digit or non-( or other operator before
				cout << "Error 3 : there is one extra operator.";
				return false;
			}
		}
		else if ( inifix[i] == '(' ){                                   // 23( is not allow
			if ( isdigit( inifix[ i - 1 ] ) ){
				cout << "Error 3 : there is one extra operand.";
				return false;
			}
		}
		else if ( inifix[i] == ')' ){                                   // )23 is not allow
			if ( isdigit( inifix[ i + 1 ] ) ){
				cout << "Error 3 : there is one extra operand.";
				return false;
			}
		}
	}
	
	return true;
	
}         // check whether is a legal expression
void str2list( const string& str, expLIST< string >& list)               // parse string into list
{
	string numberBuffer;                       // a string for num
	string oper;                               // a string for other
	for ( int i = 0; i < str.length(); i++ ){
		if ( isdigit( str[i] ) ){
			numberBuffer += str[i];
		}
		else {
			if ( !numberBuffer.empty() ){         // append num to list
				list.append( numberBuffer );
				numberBuffer.clear();
			}
			string oper(1, str[i] );            // append operator or parentheses to list
			list.append( oper );
			oper.clear();
		}
		
	}
	if (!numberBuffer.empty()) {               // append the last number
        list.append(numberBuffer);
    }
	
	
}                // parse a string into a linked list

    // Define a function to get the precedence of operators
int getPrecedence ( const string& op) {         // sort the operator *,/ first +,- second
    if ( op == "*" || op == "/" )
        return 2;
    else if ( op == "+" || op == "-" )
        return 1;
    else
        return 0;
}

bool infix2postfix(expLIST<string>& infixList, expLIST<string>& postfixList)              // transform inifix into postfix
{
    expSTACK<string> operatorStack;
    string token;

    
    while (!infixList.isEmpty())                                      // Loop the infix list
    {
        infixList.getHead(token);

        
        if (isdigit(token[0]))                                        // // If token is num, append  to postfix list
        {
            postfixList.append(token);
        }
        // If token is an operator
        else if (token == "+" || token == "-" || token == "*" || token == "/")       // Pop operators from the stack and append to postfix list
        {
            
            
            string topOperator;

            while (!operatorStack.isEmpty() && (operatorStack.getTop(topOperator), getPrecedence(topOperator) >= getPrecedence(token)))         // if operatorstack is not empty && topoperator'order is bigger the current operator
            {
                operatorStack.pop();
                postfixList.append(topOperator);
            }

            
            operatorStack.push(token);                                   // Push the current operator onto the stack
        }               // until the top of the stack has lower precedence or is a '('
        
        else if (token == "(")                                    // If token is '(',  ( is the first order
        {
            operatorStack.push(token);
        }
        
        else if (token == ")")                                        // If token is ')', pop operators from the stack and append to postfixlist until '(' 
        {
            string topOperator;
            while (!operatorStack.isEmpty() && (operatorStack.getTop(topOperator), topOperator) != "(")   // while operatorstack is not empty && operator != )
            {
                operatorStack.pop();
                postfixList.append(topOperator);
            }

            // Pop the '(' from the stack
            operatorStack.pop();
        }

        
        infixList.del();              // delete token in infix list
    }

    // Pop operators from the stack and append to postfix list
    string topOperator;
    while (!operatorStack.isEmpty())                                   // while there is left in operratorstack
    {
        operatorStack.pop(topOperator);
        postfixList.append(topOperator);
    }

    return true;
}                                                           // transform inifix into postfix

                
#define MAX_LEN255                   // maximum string length

int main(void)
{
	int command = 0;                 // user command
	expLIST<string> myList; 
	expLIST<string> pList;
	do
	{
		myList.clearUp();  // 清空之前的數據 
        pList.clearUp();   // 清空之前的數據 
		string infixS;
		
		cout << endl <<"* Arithmetic Expression Evaluator *";
		cout << endl <<"* 0. QUIT                         *";
		cout << endl <<"* 1. Infix2postfix Transformation *";
		cout << endl <<"* 2. Infix2postfix Transformation *";
		cout << endl <<"***********************************";
		cout << endl <<"Input a choice(0, 1):";
		cin >> command;               // get a command
		cin.ignore(MAX_LEN, '\n');    // clear the input buffer
		switch (command)
		{ 
			case 0:break;
			case 1:cout << endl << "Input an infixexpression: ";
			       
		           getline(cin,infixS);
		           if(isExp(infixS) &&               // check each symbol & remove useless ones
				        isBalanced(infixS)           // check the validity of balanced parentheses
						&& isLegal(infixS))          // check whether it is a legal expression
					{
						str2list( infixS, myList );                 // parse a string into a linked list
						
						if( infix2postfix( myList, pList ) ){          // transform infixS into postfixS
						 	cout << "Postfix expression: ";
							pList.display();                            // display the postfixlist 
						 	
						 	
					    }
//Mission One: check whether it is an infix expression
//Mission Two: transform infix to postfix, stored as a linked list						      
					}	// end if
					break;
			default:cout << endl << "Command does not exist" << endl;		
		}  // end switch
	}while (command != 0);                           // '0':stop the program
	system("pause");                                 // pause the display
	return 0;
	
}    // end main

