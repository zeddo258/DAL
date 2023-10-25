//********************************************************************************/
// 11127219, Kao, Hong-Chun °ªªl¶v
// Based on demo code of Exercise 03: Infix2Postfix by Wu, Yi-Hung@ICE.CYCU 2019/10
//********************************************************************************/

#include <stack> // using stack methods
#include <iostream> // endl
#include <new>  // new
#include <string> // string class
#include <cstdlib> // system, atoi
#define MAX_LEN 255 // maximum string length

using namespace std;

struct listNode // structure of each node in list
{
    string value;
    struct listNode *next; // next element

};

struct stackNode // structure of each element in stack
{
    string value;
    struct stackNode *next; // next element

};

bool isExp(string& nibba); // check the validity of each symbol
bool isBalanced(const string nibba); // check the validity of balanced parentheses
bool isLegal(const string nibba); // check whether it is a legal expression
bool isHigher( char c, char d ); // comparing order of operators
bool isOperator(char c); // check if it is operator
bool isOperand(char c);// check if it is operand
int order ( char c ); // other of operators

int order( char c ) {

    switch (c){

        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;

        default: return 0;

    }

}

bool isHigher( char c, char d ) {

    if( order(c) >= order(d) )
        return true;
    else
        return false;

}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isOperand(char c) {
    return (c >= '0' && c <= '9');
}

bool isExp(string& nibba) {


    for ( int i = 0; i < nibba.length(); i++) {

        char currentChar = nibba[i];

        if ( isOperator(currentChar) ) ;
        else if ( isOperand(currentChar) ) ;
        else if ( currentChar == 40 || currentChar == 41 ) ;
        else if ( currentChar == ' ' ) ;
        else{

            cout << endl << "Error 1: "<< currentChar << " is not a legitimate character." ;
            return false ;

        }

    }

    return true ;

}

bool isBalanced(const string nibba) {

    int open = 0, close = 0 ;

    for (char c : nibba ) {

        switch (c) {

            case '(':

                open++;
                break;

            case ')':

                close++;
                break;

        }
    }

    if ( open > close )
        cout << endl << "Error 2: there is one extra open parenthesis." ;

    else if ( open < close )
        cout << endl << "Error 2: there is one extra close parenthesis.";

    return (open == close);

}

bool isLegal(const string nibba) {

    int openParenCount = 0;
    int closeParenCount = 0;
    bool lastWasOperand = false;
    bool lastWasOpenParen = false;
    bool lastWasCloseParen = false;
    bool lastWasOperator = false;
    bool lastWasDivide = false ;

    for (char c : nibba) {

        if (c == '(') {

            openParenCount++;
            if ( lastWasOperand ) {

                cout << endl << "Error 3: there is one extra operand." ;
                return false;  // no operands can be outside paren

            }

            lastWasOpenParen = true;
            lastWasCloseParen = false;
            lastWasOperand = false;
            lastWasOperator = false;
            lastWasDivide = false ;
        }
        else if (c == ')') {

            closeParenCount++;
            if ( lastWasOpenParen || lastWasOperator ) {

                cout << endl << "Error 3: it is not infix in the parentheses." ;
                return false ; // inside parentheses is invalid

            }

            lastWasOpenParen = false;
            lastWasCloseParen = true;
            lastWasOperand = false;
            lastWasOperator = false;
            lastWasDivide = false ;
        }
        else if (isOperator(c)) {

            if (lastWasOpenParen) {

                cout << endl << "Error 3: it is not infix in the parentheses." ;
                return false ; // inside parentheses is invalid
            }
            else if ( lastWasOperator ) {

                cout << endl << "Error 3: there is one extra operator." ;
                return false; // Operators must be between operands and close paren
            }

            if ( c == '/' )
                lastWasDivide = true ;
            else
                lastWasDivide = false ;

            lastWasOpenParen = false;
            lastWasCloseParen = false;
            lastWasOperand = false;
            lastWasOperator = true;

        }
        else if (isOperand(c)) {

            if ( lastWasDivide && c == '0' ) {

                cout << endl << "Error 3: there is dividing by zero." ;
                return false ;

            }


            if ( lastWasCloseParen ) {

                cout << endl << "Error 3: there is one extra operand." ;
                return false ; // no operands can be outside paren

            }

            lastWasOpenParen = false;
            lastWasCloseParen = false;
            lastWasOperand = true;
            lastWasOperator = false;
            lastWasDivide = false ;
        }
        else if ( c == ' ' ) ;

    }

    // Ensure that the expression does not end with an operator
    if ( lastWasOperator ) {

        cout << endl << "Error 3: there is one extra operator." ;
        return false;
    }

    return true;

}


class expLIST {

private:

    listNode *head, *tail, *printer; // head, tail, and printing data members
    string infix;

public:

    expLIST(const string nibba): head(NULL), tail(NULL), printer(NULL) // constructor with initialization
    { infix = nibba ; // 69
    } //end expLIST initializer

    expLIST(): head(NULL), tail(NULL), printer(NULL) // constructor with initialization
    {
    }

    void printList() { // for printing nodes in postfix list

        while ( ( printer != NULL ) ) {

            cout << printer->value ;
            printer = printer->next;

            if ( printer != NULL )
                cout << " ," ;

        }

    }

    void str2list( ) { // operators, operands, parens are tokenized

        // separate tokens are then inserted into linked list
        // 1+1+1+1
        string token = "" ;
        for (char c : infix) {

            if ( isOperand(c) )
                token = token + c ;

            else {

                if ( !token.empty()) {

                    ins(token);
                    token = "";

                } // (8+988)+7-57*(7-(7+5))

                if ( c != ' ' && c != '\n' )
                    ins(string(1,c)); // a separate string with single char(paren or operator)
            }

        }

        if ( !token.empty() )
            ins(token);

    }

    bool isEmpty() const // decide whether list is empty
    { return head == NULL;
    } //end expLIST::isEmpty

    void ins(const string inValue) // append one token into list
    {
        try{

            listNode *newNode ;
            newNode = new listNode;
            newNode->value = inValue ;
            newNode->next = NULL ;

            if ( isEmpty() ) {

                head = newNode; // first node
                tail = head ;
            }

            else {

                listNode* current = head ;
                while ( current->next != NULL )
                    current = current->next ; // move to last node

                current->next = newNode; // (8+988)+7-57*(7-(7+5))
                tail = newNode ;

            } // attached to the tail of the list
            printer = head ;

        } // end try
        catch (std::bad_alloc& ba) // unable to allocate space
        { std::cerr << endl << "bad_allocation on stack caught: " << ba.what() << endl;
        } // end catch

    } // end expLIST::ins

    listNode* getHead() // get the head of list
    {
        return head ;
    } // end expLIST::getHead
    void del() // remove the head of list
    {

    } // end expLIST::del without output parameter
    void del(const string& outValue) // get the head of stack and remove it
    {

    } // end expLIST::del with output parameter
    void clearUp() // clear up the entire list
    {

        listNode* current = NULL ;
        printer = NULL ;
        tail = NULL ;
        while( !isEmpty() ) {

            current = head ;
            head = head->next;
            delete current ;

        }

    } // end expLIST::clearUp

    ~expLIST() // destructor
    { clearUp();
    } // end destructor

}; //end expLIST class

//********************************************************************************/
// The above is self-defined expLIST class, used for keeping a series of values
//********************************************************************************

class expSTACK {

private:

    stackNode *topPtr; // stack member
    listNode *infix ;  // read only infix list buffer
    expLIST postfix ;   // postfix list

public:

    expSTACK(listNode *expression): topPtr(NULL), infix(NULL)  // constructor with initialization
    { infix = expression ;
   } //end expSTACK initializer

    bool isEmpty() const // decide whether stack is empty
    { return topPtr == NULL;
    } //end expSTACK::isEmpty

    bool infix2postfix() { // produce a postfix expression list afterward

        char c,f ; // c is first char of node in infix list
        // f is first char of top node in stack

        while ( (infix != NULL ) ) {

            c = infix->value[0] ;

            if ( !isEmpty() )
                f = topPtr->value[0] ;

            if ( isOperand( c ) )
                postfix.ins( infix->value );
            else if  ( c == '(')
                push(infix->value);
            else if (c == ')') {

                while ( !isEmpty() && f != '(' ) {

                    postfix.ins(topPtr->value) ;
                    pop();

                    if ( !isEmpty() )
                        f = topPtr->value[0] ;

                }

                if ( !isEmpty() && f == '(' )
                    pop() ;

            }
            else {

                while ( !isEmpty() && isHigher(f,c) ) {

                    postfix.ins( topPtr->value ) ;
                    pop() ;

                    if ( !isEmpty() )
                        f = topPtr->value[0];

                }

                push(infix->value) ;

            }

            infix = infix->next ;

        }

        while ( !isEmpty() ) {

            postfix.ins(topPtr->value);
            pop();

        }

        if ( postfix.isEmpty() )
            return false;

        return true ;

    }

    void push(const string inValue) // add one element into stack
    { try
        {

            stackNode *newNode ;
            newNode = new stackNode;
            newNode->value = inValue ;
            newNode->next = NULL ;

            if ( isEmpty() )
                topPtr = newNode;

            else{

                newNode->next = topPtr ;
                topPtr = newNode ;

            }

        } // end try
        catch (std::bad_alloc& ba) // unable to allocate space
        { std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
        } // end catch

    } // end expSTACK::push

    stackNode* getTop() // get the top of stack without removal
    {
        return topPtr ;
    } // end expSTACK::getTop

    void pop() // remove the top of stack
    {
        if( !isEmpty() ) {

            stackNode *currentNode = topPtr ;
            topPtr = topPtr->next ;
            delete currentNode ;

        }

    } // end expSTACK::pop without output parameter

    void pop(const string & outValue) // get the top of stack and remove it
    { // getTop(outValue);

    } // end expSTACK::pop with output parameter

    ~expSTACK() // destructor
    {
        while (!isEmpty()) // clear the stack
            pop();

        postfix.clearUp() ; // clear postfix data memebrs


        listNode* current = NULL ;
        while( infix != NULL ) { // clear listNode infix

            current = infix ;
            infix = infix->next;
            delete current ;

        }

    } // end destructor

    void print(){ // final output

        cout << endl << "Postfix expression: " ;

        postfix.printList() ;

    }

}; //end expSTACK class

//********************************************************************************/
// The above is self-defined expSTACK class, used for keeping a series of values
//********************************************************************************

int main(void) {

    int command = 0; // user command

    do {
        string infixS;
        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT *";
        cout << endl << "* 1. Infix2postfix Transformation *";
        cout << endl << "***********************************";
        cout << endl << "Input a choice(0, 1): ";
        cin >> command; // get a command
        cin.ignore(MAX_LEN, '\n'); // clear the input buffer

        switch (command){

            case 0: break;
            case 1: cout << endl << "Input an infix expression: ";
            getline(cin, infixS);

            if (isExp(infixS) && // check each symbol & remove useless ones
                isBalanced(infixS) // check the validity of balanced parentheses
                && isLegal(infixS)) {// check whether it is a legal expression

                    cout << endl << "It is a legitimate infix expression." ;

                    expLIST expression(infixS);
                    expression.str2list( ); // parse a string into a linked list

                    expSTACK postfix(expression.getHead());
                    if(postfix.infix2postfix())  // transform infixS into postfixS
                        postfix.print() ; // output the result if successful

                // Mission One: check whether it is an infix expression
                // Mission Two: transform infix to postfix, stored as a linked list

            } // end if

            break;

            default: cout << endl << "Command does not exist!" << endl;

        } // end switch

        cout << endl ;

    } while (command != 0); // '0': stop the program
    system("pause"); // pause the display

    return 0;

} // end main
