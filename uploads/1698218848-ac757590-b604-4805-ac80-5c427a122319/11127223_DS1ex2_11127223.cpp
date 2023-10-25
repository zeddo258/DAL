// 11127223 陳郁豊
#include <iostream>
#include <string>

using namespace std;

class Stack
{
typedef struct node {
        string data;
        struct node *next;
    } NODE;

private:
    struct node *top;
    struct node *tail;
    
public:
    Stack(/* args */) {
        top = NULL;
        tail = NULL;
    } // Stack()
    ~Stack() {
        tail = NULL;
        NODE *temp;
        while (top != NULL) {
            temp = top;
            top = top->next;
            delete temp;
        } // while
    } // ~Stack()

    void push( string data ) {
        NODE *newNode = new NODE;
        newNode->data = data;
        newNode->next = top;
        if ( top == NULL ) tail = newNode;
        top = newNode;
    } // push()

    void pushBack( string data ) {
        NODE *newNode = new NODE;
        newNode->data = data;
        newNode->next = NULL;
        if ( top == NULL ) {
            top = newNode;
            tail = newNode;
        } // if
        else {
            tail->next = newNode;
            tail = newNode;
        } // else
    } // pushBack()

    string pop() {
        if ( top == NULL ) return "";
        else {
            NODE *temp = top;
            string data = top->data;
            top = top->next;
            if ( top == NULL ) tail = NULL;
            delete temp;
            return data;
        } // else
    } // pop()

    string getTop() {
        if ( top == NULL ) return "";
        else return top->data;
    } // getTop()

    string getElementsAt( int index ) {
        if ( index < 0 ) return "";
        else {
            NODE *temp = top;
            for ( int i = 0; i < index; i++ ) {
                if ( temp == NULL ) return "";
                else temp = temp->next;
            } // for

            if ( temp == NULL ) return "";
            else return temp->data;
        } // else
    } // getElementsAt()

    bool isEmpty() {
        if ( top == NULL ) return true;
        else return false;
    } // isEmpty()

}; // class Stack

class Expression
{
private:
    string infixExp;
    Stack postfixExp;

    bool isOperator( char c ) {
        if ( c == '+' || c == '-' || c == '*' || c == '/' ) return true;
        else return false;
    } // isOperator()

    bool isDigit( char c ) {
        if ( c >= '0' && c <= '9' ) return true;
        else return false;
    } // isDigit()

    bool onlyLegitimateChar() {
        for ( int i = 0; i < infixExp.length(); i++ ) {
            if ( infixExp[ i ] == ' ' ) continue;
            else if ( isOperator( infixExp[ i ] ) ) continue;
            else if ( infixExp[ i ] == '(' || infixExp[ i ] == ')' ) continue;
            else if ( isDigit( infixExp[ i ] ) ) continue;
            else {
                cout << "Error 1: " << infixExp[ i ] << " is not a legitimate character.";
                return false;
            } // else
        } // for
        return true;
    } // onlyLegitimateChar()

    bool parenthesisMatch() {
        int count = 0;
        for ( int i = 0; i < infixExp.length(); i++ ) {
            if ( infixExp[ i ] == '(' ) count++;
            else if ( infixExp[ i ] == ')' ) count--;

            if ( count < 0 ) {
                cout << "Error 2: there is one extra close parenthesis.";
                return false;
            }
        } // for

        if ( count > 0 ) {
            cout << "Error 2: there is one extra open parenthesis.";
            return false;
        } // if
        else return true;
    }

    string getNextNumber( int & index ) {
        string number = "";
        while ( isDigit( infixExp[ index ] ) ) {
            number += infixExp[ index++ ];
            if ( index >= infixExp.length() ) break;
        } // while

        return number;
    } // getNextNumber()

    int indexOfMatchingParenthesis( int index ) {
        int count = 1;
        while ( index < infixExp.length() ) {
            if ( infixExp[ index ] == '(' ) count++;
            else if ( infixExp[ index ] == ')' ) count--;

            if ( count == 0 ) return index;
            else index++;
        } // while

        return -1;
    } // indexOfMatchingParenthesis()

    int isInfix( int & index ) { 
        // return 0: infix, 1: one extra operator, 2: not infix in the parentheses, 3: there is one extra operand.
        // 我不想做 throw exception，所以用 return 來表示錯誤
        // <infix> = <number> || <number><operator><infix> || <(><infix><)> || <(><infix><)><operator><infix>

        if ( infixExp[ index ] == '(' ) {
            // <(><infix><)> || <(><infix><)><operator><infix>
            int indexOfMatching = indexOfMatchingParenthesis( ++index );
            Expression expInParenthesis( infixExp.substr( index, indexOfMatching - index ) );
            index = indexOfMatching + 1; // move index to next character
            int indexForInfix = 0;
            if ( expInParenthesis.isInfix( indexForInfix ) != 0 ) return 2; // not infix in the parentheses
            else if ( index >= infixExp.length() ) return 0; // end of string, satisfy <(><infix><)>
            else if ( isOperator( infixExp[ index ] ) ) return isInfix( ++index ); // <(><infix><)><operator><infix>
            else return 3; // <(><infix><)><number> || <(><infix><)><parenthesis>
        } // if
        else if ( isDigit( infixExp[ index ] ) ) {
            // <number> || <number><operator><infix>
            getNextNumber( index ); // move index to next non-digit character
            if ( index >= infixExp.length() ) return 0; // end of string, satisfy <number>
            else if ( isOperator( infixExp[ index ] ) ) return isInfix( ++index ); // <number><operator><infix>
            else return 3; // <number><parenthesis>
        } // else if
        else return 1; // <operator><infix> || <operator>
    } // isInfix()

    bool isOperatorHigherPriority( char op1, Stack & stack ) {
        if ( stack.getTop() == "(" ) return true;
        else if ( stack.isEmpty() ) return true;
        else if ( stack.getTop() == "+" || stack.getTop() == "-" ) {
            if ( op1 == '*' || op1 == '/' ) return true;
            else return false;
        } // else if
        else return false;
    } // isOperatorHigherPriority()

public:
    Expression( string input ) {
        infixExp = input;
    } // Expression()
    ~Expression() {
        postfixExp.~Stack();
    } // ~Expression()

    bool isALegitimateInfixExpression() {
        if ( !onlyLegitimateChar() ) return false;
        if ( !parenthesisMatch() ) return false;

        int index = 0;
        int result = isInfix( index );
        if ( result == 1 ) {
            cout << "Error 3: there is one extra operator.";
            return false;
        } // if
        else if ( result == 2 ) {
            cout << "Error 3: it is not infix in the parentheses.";
            return false;
        } // else if
        else if ( result == 3 ) {
            cout << "Error 3: there is one extra operand.";
            return false;
        } // else if
        else {
            return true;
        }
    } // isALegitimateInfisExpression()

    void convertIntoPostfix() {
        Stack stack;
        int index = 0;
        while ( index < infixExp.length() ) {
            if ( infixExp[ index ] == '(' ) stack.push( "(" );
            else if ( isDigit( infixExp[ index ] ) ) {
                string number = getNextNumber( index );
                postfixExp.pushBack( number );
                continue; // already move to next character
            } // else if
            else if ( isOperator( infixExp[ index ] ) ) {
                if ( isOperatorHigherPriority( infixExp[ index ], stack ) ) {
                    stack.push( string( 1, infixExp[ index ] ) ); // a string length = 1 and only contain infixExp[ index ]
                } // if
                else {
                    // pop all operators with higher or equal priority
                    while ( !stack.isEmpty() && !isOperatorHigherPriority( infixExp[ index ], stack ) ) {
                        postfixExp.pushBack( stack.pop() );
                    } // while

                    stack.push( string( 1, infixExp[ index ] ) );
                } // else
            } // else if
            else if ( infixExp[ index ] == ')' ) {
                while ( !stack.isEmpty() && stack.getTop() != "(") {
                    postfixExp.pushBack( stack.pop() );
                } // while

                stack.pop(); // pop "("
            } // else if

            index++;
        } // while

        while ( !stack.isEmpty() ) {
            postfixExp.pushBack( stack.pop() );
        } // while
    } // convertIntoPostfix()

    void printPostfix() {
        cout << endl << "Postfix expression:";
        int index = 0;
        string data = postfixExp.getElementsAt( index++ );
        while ( data != "" ) {
            cout << " " << data;
            data = postfixExp.getElementsAt( index++ );
            if ( data != "" ) cout << ",";
        } // while

        cout << endl;
    } // printPostfix()
}; // class Expression

int getCommand() {
string input;
    getline( cin, input );
    if ( input.length() != 1 ) return -1;
    else return input[ 0 ] - '0';
} // getCommand()

string getInput() {
    string input = "";
    char ch;
    cout << endl << "Input an infix Expression: ";
    while ( cin.get( ch ) ) {
        if ( ch == '\n' ) break;
        else if ( ch == ' ' ) continue; // ignore space
        else input += ch;
    } // while

    if ( input.length() == 0 ) return getInput(); // input nothing or only space
    else return input;
} // getInput()

int main() {
    int command = -1;
    string infixStr;

    do {
        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         *";
        cout << endl << "* 1. Infix2postfix Transformation *";
        cout << endl << "***********************************";
        cout << endl << "Input a choice(0, 1): ";

        command = getCommand();
        if ( command == 0 ) {
            break;
        } // if
        else if ( command == 1 ) {
            string input = getInput();

            Expression exp( input );
            if ( exp.isALegitimateInfixExpression() ) cout << "It is a legitimate infix Expression.";
            else {
                cout << endl;
                continue;
            } // else

            exp.convertIntoPostfix();
            exp.printPostfix();

        } // if
        else {
            cout << endl << "Command does not exist!" << endl;
        } // else
    } while ( command != 0 );

    system( "pause" );
    return 0;
} // main()