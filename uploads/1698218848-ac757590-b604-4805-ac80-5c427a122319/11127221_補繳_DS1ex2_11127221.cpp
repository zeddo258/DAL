// 11127221 蘇芠嵦
# include <string>          // string class
# include <iostream>        // cin, cout, endl
# include <cstdlib>         // system, atoi
# include <new>             // new

#define MAX_LEN 255         // maximum string length

using namespace std ;
bool gLegal = true ;        // the operational expression is legal or not, default: true

template <class T>          // type template for data value in list node
class expLIST {
    typedef struct qN {                 // structure of each node in list
        T value ;
        struct qN *next ;               // next element
    }   listNode ;
    listNode *head, *tail ;
public:
    expLIST(): head(NULL), tail(NULL)           // constructor with initialization
    {} // end expLIST initializer

    bool isEmpty() const {
        return head == NULL ;
    } // end expLIST::isEmpty

    void nextElement() {
        tail = tail -> next ;
    } // end expLIST::nextElement

    void reset2Head() {
        tail = head ;
    } // end expLIST::reset2Head

    void ins(const T inValue) {                 // append one value into list
        try {
            if (isEmpty()) {
                head = new listNode() ;
                head -> value = inValue ;
                tail = head ;
            } // end if
            else {
                tail = head ;
                while (tail -> next != NULL) {
                    tail = tail -> next ;
                } // end while
                tail -> next = new listNode() ;
                tail -> next -> value = inValue ;
                tail = head ;
            } // end else
        } // end try
        catch (std::bad_alloc& ba) {
            std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl ;
        } // end catch
    } // end expLIST::ins

    void getHead(T& outValue) {
        outValue = head -> value ;
    } // end expLIST::getHead

    T getTail() {
        T outValue = tail -> value ;
        return outValue ;
    } // end expLIST::getTail

    void del() {
        listNode * temp = head ;
        head = head -> next ;
        temp -> next = NULL ;
        delete temp ;
    } // end expLIST::del without output parameter

    void del(T& outValue) {
        outValue = head -> value ;
        del() ;
    } // end expLIST::del with output parameter

    void show() {
	    listNode * temp = head ;
	    while (temp != NULL) {
		    cout << temp -> value ;
		    temp = temp -> next ;
	    } // end while
        cout << endl ;
    } // end expLIST::show

    int length() {
        int count = 0 ;
        listNode * temp = head ;
        while (temp != NULL) {
            count++ ;
            temp = temp -> next ;
        } // end while
        return count ;
    } // end expLIST::length()

    void clearUp() {
        while (!isEmpty()) 
            del() ;
    } // end expLIST::clearUp

    ~expLIST() {
        clearUp() ;
    } // end destructor
} ; // end expLIST class

template <class T>
class expSTACK {
    typedef struct sN {                     // structure of each element in stack
        T value ;
        struct sN *next ;                   // next element
    }   stackNode ;
    stackNode *topPtr ;                     // only one data member
public:
    expSTACK(): topPtr(NULL)                // constructor with initialization
    {} // end expSTACK initializer

    bool isEmpty() const {                  // decide whether stack is empty
        return topPtr == NULL ;
    } // end expSTACK::isEmpty

    void push(const T inValue) {            // add one element int stack
        try {
            if (isEmpty()) {
                topPtr = new stackNode() ;
                topPtr -> value = inValue ;
            } // end if
            else {
                stackNode * temp = new stackNode() ;
                temp -> value = inValue ;
                temp -> next = topPtr ;
                topPtr = temp ;
                temp = NULL ;
                delete temp ;
            } // end else
        } // end try
        catch (std::bad_alloc& ba) {        // unable to allocate space
            std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl ;
        } // end catch
    } // end expSTACK::push

    void getTop(T& outValue) {              // get the top of stack without removal
        if (!isEmpty()) {
            outValue = topPtr -> value ;
        } // end if
    } // end expSTACK::getTop

    void pop() {                            // remove the top of stack
        if (!isEmpty()) {
            stackNode * temp = topPtr ;
            topPtr = topPtr -> next ;
            temp -> next = NULL ;
            delete temp ; 
        } // end if                   
    } // end expSTACK::pop without output parameter

    void pop(T& outValue) {                 // get the top of stack and remove it
        if (!isEmpty()) {
            outValue = topPtr -> value ;
            pop() ;
        } // end if
    } // end expSTACK::pop with output parameter

    void show() {
	    stackNode * temp = topPtr ;
	    while (temp!=NULL) {
		    cout << temp -> value << " " ;
		    temp = temp -> next ;
	    } // end while
        cout << endl ;
    } // end expSTACK::show

    ~expSTACK() {               // destructor
        while (!isEmpty())
            pop() ;
    } // end destructor
} ; // end expSTACK class

bool isExp(string& str) ;                                   // check the validity of each symbol
bool isBalanced(const string str) ;                         // check the validity of balanced expression
bool isLegal(const string str) ;                            // check whether it is a legal expression
void str2list(const string str, expLIST<char> &nList) ;      // parse a string into a linked list
bool infix2postfix(expLIST<char> nList) ;

int main(void) {
    int cmd = 0 ;               // user command

    do {
        string infixS;
        expLIST<char> nList ;

        cout << endl << "* Arithmetic Expression Evaluator *" ;
        cout << endl << "* 0. QUIT                         *" ;
        cout << endl << "* 1. Infix2postfix Transformation *" ;
        cout << endl << "***********************************" ;
        cout << endl << "Input a choice(0, 1): " ;
        cin >> cmd ;                            // get a command
        cin.ignore(MAX_LEN, '\n') ;             // clear the input buffer
        switch (cmd) {
            case 0: break ;
            case 1: cout << endl << "Input an infix expression: " ;
                    getline(cin, infixS) ;
                    if (isExp(infixS) &&                // check each symbol & remove useless ones
                        isBalanced(infixS) &&           // check the validity of balanced parentheses
                        isLegal(infixS)) {              // check whether it is a legal expression
                            cout << "It is a legitimate infix expression." << endl ;
                            str2list(infixS, nList) ;           // parse a string into a linked list
                            if(infix2postfix(nList)) ;          // transform infixS into postfixS


                        } // end if
                        break ;
            default: cout << endl << "Command does not exist!" << endl ;
        } // end switch
        gLegal = true ;                     // reset gLegal to default
        nList.clearUp() ;
    } while (cmd != 0) ;                    // "0": stop the program
    system("pause") ;                       // pause the display
    return 0 ;
}

bool isExp(string& str) {
    for (int j = str.size() - 1 ; j > -1 ; j--) {
        if (str[j] == ' ')
            str.erase(j,1) ;
    } // end for loop


    for (int i = 0 ; i < str.size() ; i++) {
        if (str.at(i) != '+' && str.at(i) != '-' && str.at(i) != '*' && str.at(i) != '/' && str.at(i) != '(' && str.at(i) != ')' ) {
            if (str.at(i) < 48 || str.at(i) > 57) {
                cout << "Error 1: " << str[i] << " is not a legitimate character." << endl ;
                gLegal = false ;
                return false ;
            } // end if
        } // end if
    } // end for loop

    return true ;
} // end isExp

bool isBalanced(const string str) {
    if (gLegal == false) return false ;

    int left = 0, right = 0 ;

    for (int i = 0 ; i < str.size() ; i++) {
        if (str[i] == '(')
            left++ ;
        else if (str[i] == ')') {
            if (left == 0) {
                cout << "Error 2: there is one extra close parenthesis." ;
                gLegal = false ;
                return false ;
            } // end if
            else
                right++ ;
        } // end else if
    } // end for loop

    if (left != right) {
            cout << "Error 2: there is one extra " ;
        if (left > right)
            cout << "open parenthesis." ;
        else if (left < right) 
            cout << "close parenthesis." ;

        cout << endl ;
        gLegal = false ;
        return false ;
    } // end if
    else
        return true ;
} // end isBalanced

bool isLegal(const string str) {
    if (gLegal == false) return false ;

    for (int i = 0 ; i < str.size() ; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            if (i == 0 || i == str.size()-1) {
                cout << "Error 3: there is one extra operator." << endl ;
                gLegal = false ;
                return false ;
            } // end if
            if (i+1 != str.size()) {
                if (str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/') {
                    cout << "Error 3: there is one extra operator." << endl ;
                    gLegal = false ;
                    return false ;
                } // end if
            } // end if
        } // end if
        else if (str[i] == '(') {
            if (i+1 != str.size()) {
                if (str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/' || str[i+1] == ')') {
                    cout << "Error 3: it is not infix in the parentheses." << endl ;
                    gLegal = false ;
                    return false ;
                } // end if
            } // end if
            if (i-1 > -1) {
                if (str[i-1] >= 48 && str[i-1] <= 57) {
                    cout << "Error 3: there is one extra operand." << endl ;
                    gLegal = false ;
                    return false ;
                } // end if
            } // end if
        } // end else if
        else if (str[i] == ')') {
            if (i+1 != str.size()) {
                if (str[i+1] >= 48 && str[i-1] <= 57) {
                    cout << "Error 3: there is one extra operand." << endl ;
                    gLegal = false ;
                    return false ;
                } // end if
            } // end if
            if (i-1 > -1) {
                if (str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '*' || str[i-1] == '/' || str[i-1] == ')') {
                    cout << "Error 3: it is not infix in the parentheses." << endl ;
                    gLegal = false ;
                    return false ;
                } // end if
            } // end if
        } // end else if
    } // end for loop

    return true ;
} // end isLegal

void str2list(const string str, expLIST<char> &nList) {
    for (int i = 0 ; i < str.size() ; i++)
        nList.ins(str.at(i)) ;
} // end str2list

bool infix2postfix(expLIST<char> nList) {
    char topValue = '\0', value = '\0' ;
    expSTACK<char> nStack ;
    for (int i = 0 ; i < nList.length() ; i++) {
        nStack.show() ;
        if (nList.getTail() == '(') {
            if (i != 0) 
                cout << ", " ;
            nStack.push(nList.getTail()) ;
        } // end if
        else if (nList.getTail() >= 48 && nList.getTail() <= 57) {
            cout << nList.getTail() ;
        } // end else if
        else if (nList.getTail() == '+' || nList.getTail() == '-' || nList.getTail() == '*' || nList.getTail() == '/') {
            cout << ", " ;
            nStack.push(nList.getTail()) ;
        } // end else if
        else if (nList.getTail() == ')') {
            nStack.getTop(topValue) ;
            while (topValue != '(') {
                nStack.pop(value) ;
                cout << ", " << value ;
                nStack.getTop(topValue) ;
            } // end while
            nStack.pop() ;
        } // end else if
        nList.nextElement() ;
    } // end for loop

    while (!nStack.isEmpty()) {
        nStack.pop(value) ;
        cout << ", ", value ;
    } // end while
    return true ;
} // end infix2postfix