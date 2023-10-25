// 11127246 陳柏劭


#include <iostream>
#include <string>
#include <cstdlib>
#define MAX_LEN 255

using namespace std;

bool isExp( string &inputString );  // check is there any illegal characters
bool isBalance(  string&);          // check () is all balance or not
bool isLegal(  string& inputString );   // check expression
bool isOperator( char c );          // check target c is operator or not
bool contentInBrackets( string inputString );   // sub function for is Legal check is there any empty () in expression
bool isOperator( string c );        // same for char c but this time using string
int operatorOrder(char arg );       // determine order for operator
bool highprecendence(char a, char b );  // compare order


// Define a Node class for the linked list and stack
class Node {
public:
    string data;
    Node* next;
    // like constructor for C++
    Node(const string& value) : data(value), next(nullptr) {}
};
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    // Push a string onto the stack
    void push(const string& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Pop and remove the top string from the stack
    string pop() {
        if (top == nullptr) {
            cerr << "Error: Stack is empty." << endl;
            return "";
        }
        string value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    // Get the top string of the stack without removing it
    string peek() {
        if (top == nullptr) {
            cerr << "Error: Stack is empty." << endl;
            return "";
        }
        return top->data;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }
};

//  LinkedList class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}


    // Append a new node to the end of the linked list
    void append(const string& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    void display() {
        Node* current = head;
        while (current -> next != nullptr ) {
            cout << current->data << ", ";
            current = current->next;
        }
        cout << current  ->data << endl;
    }



    LinkedList infixToPostfix(LinkedList infix) {
        LinkedList postfix;
        Stack stack;

        Node* current = infix.head;
        while (current) {   // loop for all linkedList
            string token = current->data;

            if (token[0] == '(') {
                stack.push(token);
            } else if (token[0] == ')') {
                while (stack.peek() != "(") {
                    postfix.append(stack.pop());
                }
                stack.pop(); // Pop the "("
            } else if (isOperator(token)) {
                while (!stack.isEmpty() && !highprecendence(token[0], stack.peek()[0])) {
                    postfix.append(stack.pop());
                }
                stack.push(token);
            } else if ( !isOperator(token)) {
                postfix.append(token); // Operand
            }

            current = current->next;
        }
        // convert all operator to linkedlist
        while (!stack.isEmpty()) {
            postfix.append(stack.pop());
        }

        return postfix;
    }
};


bool highprecendence(char a, char b ) {
    int weighta = operatorOrder(a);
    int weightb = operatorOrder(b); // stack peek args
    if(weighta >= weightb)
        return true;
    return false;
}



bool isOperator( char c ){
    if (  c == '+' || c == '-' || c == '*'
          || c == '/')
        return true;

    return false;
}

bool isOperator( string c ){
    if (  c[0]=='+' || c[0]=='-' || c[0]== '*'
          || c[0]== '/')
        return true;

    return false;
}


bool contentInBrackets( string inputString ){
    if (inputString.empty()) {
        // If the string is empty, there are no unmatched parentheses.
        return true;
    }

    if ( inputString.size() > 1 ) {
        if (inputString[0] == '(' && inputString[1] == ')') {
            return false;
        }
        return contentInBrackets(inputString.substr(1, inputString.size()));
    }

    return true;
}
bool isLegal(  string& inputString ){

    if ( ( isOperator(inputString[0]) && isOperator(inputString[inputString.size()-1] ) )  ) {
        cout << "Error 3: it is not infix in the parentheses." << endl;
        return false;
    }
    for ( int i = 0; i < inputString.size() - 1 ; i++ ) {
        int  c = i + 1;
        while ( inputString[c] == '(' || inputString[c] == ')' ){
            c++;
        }
        if ( (isOperator(inputString[i]) && isOperator(inputString[c] ) ) ) {
            cout << "Error 3: it is not infix in the parentheses." << endl;
            return false;
        }

    }

    if ( contentInBrackets(inputString) ){
        return true;
    } else{
        cout << "Error 3: it is not infix in the parentheses." << endl;
        return false;
    }
}


bool isBalance(  string& inputString ){
    string final_str;
    int count = 0;
    for ( char  c : inputString ){
        if ( c != ' ' && c != '\n' )
            final_str += c;


        if (c == '('){
            count++;

        } else if( c == ')' ){
            count--;
        }
        if (count < 0 ) {
            cout << "Error 2: there is one extra close parenthesis." << endl;
            return false ;
        }
    }

    if (count > 0 ){
        cout << "Error 2: there is one extra open parenthesis." << endl;
        return false;
    }

    inputString = final_str;

    return true;
}

bool isExp( string & inputString ){
    for( char c: inputString ){
        if ( !( ( c >= '0' && c <= '9' ) || isOperator(c) || c == '(' || c == ')' ) ) {
            cout << " Error 1: " << c << " is not a legitimate character.";
            return false;
        }
    }
    return true;
}

LinkedList stringToLinkedList(const string& inputString) {
    LinkedList linkedList;
    string token;

    for (char c : inputString) {
        if (c == ' ' || c == '\t') {
            if (!token.empty()) {
                linkedList.append(token);
                token.clear();
            }
        } else if (c == '(' || c == ')' || isOperator(c)) {
            if (!token.empty()) {
                linkedList.append(token);
                token.clear();  // cleaning ram
            }
            linkedList.append(string(1, c));
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        linkedList.append(token);
    }

    return linkedList;
}

int operatorOrder(char arg )//Add weight to the operator
{
    if ( arg == '+' || arg == '-' )
        return 1;
    if ( arg == '*' || arg == '/' )
        return 2;

    return 0;
}


int main( ) {
    //Stack stack;
    int command = 0 ;
    do {
        string infixS; // store infix String
        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         *";
        cout << endl << "* 1. Infix2postfix Transformation *";
        cout << endl << "*********************************";
        cout << endl << "input a choice(0,1): ";
        cin >> command;
        cin.ignore( MAX_LEN, '\n');
    switch( command )
    {
        case 0: break;

        case 1: cout << endl << "input an infix expression: ";
                getline( cin, infixS );
                if (   isBalance( infixS ) && isExp( infixS ) && isLegal( infixS ) ){
                    LinkedList list = stringToLinkedList( infixS );
                    list = list.infixToPostfix( list );
                    cout << "It is a legitimate infix expression." << endl;
                    cout << "Postfix expression: ";
                    list.display();
                    break;
                }
        default: cout << endl << "Command does not exist" << endl;

    }

    } while ( command != 0);
    system("pause");
    return 0;
}   // end main
