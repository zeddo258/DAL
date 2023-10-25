// 11127205 屈怡安
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

template <class T>
class expLIST {

typedef struct qN { // list結構
    T value ; // symbol
    struct qN *next ;
} listNode ;

listNode *head, *tail ;

public:
    expLIST(): head(NULL), tail(NULL) // constructor with initializer
    {} // end expLIST initializer

    bool isEmpty() const { // check if the list is empty
        return head == NULL ;
    }


    void ins( const T inValue ) {  // append one value into list
        listNode *n = new listNode ;
        n -> value = inValue ;
        n -> next = NULL ;
        if ( isEmpty() == true ) {
            head = n ;
            tail = n ;
        }

        else {
            tail -> next = n ;
            tail = n ;
        }
    } // void ins( const int inValue )


    void getHead( T& outValue )  { // get the head of list without removal
        outValue = head -> value ;
    }

    bool isEnding() { // 確認是不是只剩一個symbol
        if ( head -> next != NULL )
            return false ;
        else
            return true ;
    }


    void del() { // remove the head of list
        listNode *temp = head ;
        head = head -> next ;
        delete temp ;
    }


    void del( T& outValue ) { // get the head of list and remove it
        outValue = head -> value ;
        listNode *temp = head ;
        head = head -> next ;
        delete temp ;
    }


    void clearUp() { // clear up the entire list
        while ( head != NULL ) {
            listNode *temp = head ;
            head = head -> next ;
            delete temp ;
        }
    }

    ~expLIST() { // destructor
        clearUp() ;
    }

} ; // class expLIST




template <class T>
class expSTACK {

typedef struct sN { // stack結構
    T value ; // symbol
    struct sN *next ;
} stackNode ;

stackNode *topPtr ;

public:
    expSTACK(): topPtr(NULL)
    {} // end expSTACK initializer

    bool isEmpty() const { // decide whether stack is empty
        if ( topPtr == NULL )
            return true ;
        else
            return false ;
    }


    void push( const T inValue ) { // add one element into stack
        stackNode *n = new stackNode ;
        n -> value = inValue ;
        n -> next = NULL ;
        if ( isEmpty() == true ) {
            topPtr = n ;
        }
        else {
            n-> next = topPtr ;
            topPtr = n ;
        }
    }


    void getTop( T& outValue ) { // get the top of stack without removal
        outValue = topPtr -> value ;
    }


    void pop() { // remove the top of stack
        stackNode *temp = topPtr ;
        topPtr = topPtr -> next ;
        delete temp ;
    }


    void pop( T& outValue ) { // get the top if stack and remove it
        outValue = topPtr -> value ;
        stackNode *temp = topPtr ;
        topPtr = topPtr -> next ;
        delete temp ;
    }


    void clearUp() {
        while ( topPtr != NULL ) {
            stackNode *temp = topPtr ;
            topPtr = topPtr -> next ;
            delete temp ;
        }
    }

    ~expSTACK() { // destructor
        clearUp() ;
    }

}; // end expSTACK class






bool isExp( const char* charArray, int &error, int &error1_index ) { // check the validity of each symbol
    for ( int i = 0; charArray[i] != NULL; i ++ ) {
        if ( charArray[i] != '0' && charArray[i] != '1' && charArray[i] != '2' && charArray[i] != '3' && charArray[i] != '4' &&
             charArray[i] != '5' && charArray[i] != '6' && charArray[i] != '7' && charArray[i] != '8' && charArray[i] != '9' &&
             charArray[i] != '+' && charArray[i] != '-' && charArray[i] != '*' && charArray[i] != '/' &&
             charArray[i] != '(' && charArray[i] != ')' && charArray[i] != ' ' ) {
            error = 1 ;
            error1_index = i ; // 不合法symbol的位置
            return false ;
        }
    }
    return true ;
}

bool isBalanced( const char* charArray, int &error, int &parenthesis ) { // check the validity of balanced parenthesis
    int p = 0 ; // 紀錄左右括號出現狀態

    // 左括號總是先出現，右括號一比左括號多就錯誤
    // 左、右括號的數量應相等
    for ( int i = 0; charArray[i] != NULL; i ++ ) {
        if ( charArray[i] == '(' )
            p ++ ;
        else if ( charArray[i] == ')' )
            p -- ;
        if ( p < 0 ) { // extra close parenthesis
            error = 2 ;
            parenthesis = 2 ;
            return false ;
        }
    }

    if ( p == 0 ) // balanced
        return true ;

    else if ( p > 0 ) { // extra open parenthesis
        error = 2 ;
        parenthesis = 1 ;
        return false ;
    }
}

bool isLegal( const char* charArray, int &error, int &operate ) { // check whether it is a legal expression

    if ( charArray[0] == '+' || charArray[0] == '-' || charArray[0] == '*' || charArray[0] == '/' ) { // extra operator
        error = 3 ;
        operate = 1 ;
        return false ;
    }

    for ( int i = 0; charArray[i] != NULL; i ++ ) {
        while ( charArray[i] == ' ' ) // 排除空格
            i ++ ;
        if( charArray[i] == '+' || charArray[i] == '-' || charArray[i] == '*' || charArray[i] == '/' ) { // extra operator
            while ( charArray[i+1] == ' ' ) // 排除空格
                i ++ ;
            if ( charArray[i+1] == '+' || charArray[i+1] == '-' || charArray[i+1] == '*' || charArray[i+1] == '/'  ) {
                error = 3 ;
                operate = 1 ;
                return false ;
            }
            else if ( charArray[i+1] == ')' ) {
                // there should be an operand between an operator and ')'
                // it is not a infix expression in parenthesis
                error = 3 ;
                operate = 3 ;
                return false ;
            }
        }
        else if ( charArray[i] == '(' ) {
            while ( charArray[i+1] == ' ' ) // 排除空格
                i ++ ;
            if ( charArray[i+1] == '+' || charArray[i+1] == '-' || charArray[i+1] == '*' || charArray[i+1] == '/' ) {
                // there should be an operand between an operator and '('
                // it is not a infix expression in parenthesis
                error = 3 ;
                operate = 3 ;
                return false ;
            }
            else if ( charArray[i+1] == ')' ) {
                // nothing between ()
                // it is not a infix expression in parenthesis
                error = 3 ;
                operate = 3 ;
                return false ;
            }
        }
        else if ( charArray[i] == ')' ) {
            while ( charArray[i+1] == ' ' )
                i ++ ;
            if ( charArray[i+1] == '(' ||
                 ( charArray[i+1] == '0' || charArray[i+1] == '1' || charArray[i+1] == '2' || charArray[i+1] == '3' || charArray[i+1] == '4' ||
                   charArray[i+1] == '5' || charArray[i+1] == '6' || charArray[i+1] == '7' || charArray[i+1] == '8' || charArray[i+1] == '9') ) {
                // there should be an operator between ')' and an operand
                // there should be an operator between ')' and an '('
                // extra operand
                error = 3 ;
                operate = 2 ;
                return false ;
            }
        }
    }

    return true ;
}


void infix2postfix( const char* charArray ) { // transform a infix expression into postfix

    expLIST<char> infix ;
    expLIST<char> postfix ;
    expSTACK<char> stackMethod ;

    // 把輸入的式子存到linked list
    for ( int i = 0; charArray[i] != NULL; i ++ ) {
        if ( charArray[i] != ' ' )
            infix.ins( charArray[i] ) ;
    }


    // 把infix轉成postfix
    //    轉換方式:
    //    1.若目前符號為運算元或「(」: 目前符號加入後序式
    //    2.若目前符號為「)」: 將stack中直到遇到「(」前的所有運算子加入後序式
    //    3.若目前符號為運算子，便和stack top比較優先順序(乘除 > 加減):
    //      (1)目前符號 > stack top : 目前符號加入stack，看下一個符號
    //      (2)目前符號 < stack top : stack top加入後序式、移除stack top，目前符號繼續和新的stack top比
    //      (3)目前符號 = stack top : stack top加入後序式、移除stack top，目前符號加入stack

    char value ; // 目前符號
    while ( infix.isEmpty() == false ) {
        infix.getHead( value ) ;
        if ( value == '0' || value == '1' || value == '2' || value == '3' || value == '4' ||
             value == '5' || value == '6' || value == '7' || value == '8' || value == '9' ) {
            postfix.ins( value ) ;
            infix.del() ;
            if ( infix.isEmpty() != true ) {
                char temp ; // value後的下一個symbol
                char t ; // stack top
                infix.getHead( temp ) ;

                if ( temp != '0' && temp != '1' && temp != '2' && temp != '3' && temp != '4' &&
                     temp != '5' && temp != '6' && temp != '7' && temp != '8' && temp != '9' ) {
                    postfix.ins( ',' ) ;
                    postfix.ins( ' ' ) ;
                }
            }
        }
        else if ( value == '(' ) {
            stackMethod.push(value ) ;
            infix.del() ;
        }
        else if ( value == '*' || value == '/' ) {
            if ( stackMethod.isEmpty() == true ) {
                stackMethod.push( value ) ;
                infix.del() ;
            }
            else {
                char topValue ;
                stackMethod.getTop( topValue ) ;
                if ( topValue == '+' || topValue == '-' ) {
                    stackMethod.push( value ) ;
                    infix.del() ;
                }
                else if ( topValue == '*' || topValue == '/' ) {
                    postfix.ins( topValue ) ;
                    stackMethod.pop() ;
                    stackMethod.push( value ) ;
                    infix.del() ;
                    if ( infix.isEmpty() == false ) {
                        postfix.ins( ',' ) ;
                        postfix.ins( ' ' ) ;
                    }
                }
                else if ( topValue == '(' ) {
                    stackMethod.push( value ) ;
                    infix.del() ;
                }
            }
        }
        else if ( value == '+' || value == '-' ) {
            if ( stackMethod.isEmpty() == true ) {
                stackMethod.push( value ) ;
                infix.del() ;
            }
            else {
                char topValue ;
                stackMethod.getTop( topValue ) ;
                if ( topValue == '*' || topValue == '/' ) {
                    postfix.ins( topValue ) ;
                    stackMethod.pop() ;
                    postfix.ins( ',' ) ;
                    postfix.ins( ' ' ) ;
                }
                else if ( topValue == '+' || topValue == '-' ) {
                    postfix.ins( topValue ) ;
                    stackMethod.pop() ;
                    stackMethod.push( value ) ;
                    infix.del() ;
                    if ( infix.isEmpty() == false ) {
                        postfix.ins( ',' ) ;
                        postfix.ins( ' ' ) ;
                    }
                }
                else if ( topValue == '(' ) {
                    stackMethod.push( value ) ;
                    infix.del() ;
                }
            }
        }
        else if ( value == ')' ) {
            // 將stack中直到遇到「(」前的所有運算子加入後序式
            infix.del() ;
            char topValue ;
            stackMethod.getTop( topValue ) ;
            while ( topValue != '(' ) {
                postfix.ins( topValue ) ;
                if ( stackMethod.isEmpty() == false ) {
                    postfix.ins( ',' ) ;
                    postfix.ins( ' ' ) ;
                }
                stackMethod.pop() ;
                stackMethod.getTop( topValue ) ;
            }
            stackMethod.pop() ; // 刪掉「(」
        }
    }


    while ( postfix.isEmpty() == false ) {
        char outValue ;
        postfix.del( outValue ) ;

        if ( outValue != ',' )
            cout << outValue ;

        // 若postfix的list的結尾為「， 」就不需要印
        else if ( outValue == ',' && postfix.isEmpty() == false ) {
            char temp ;
            postfix.getHead( temp ) ;
            bool ending = postfix.isEnding() ;
            if ( temp == ' ' && ending == true )
                break ;
            else
                cout << outValue ;
        }
    }



    while ( stackMethod.isEmpty() == false ) {
        cout << ", " ;
        char outValue ;
        stackMethod.pop( outValue ) ;
        cout << outValue ;
    }

    cout << endl ;

    // 清空所有list和stack
    infix.clearUp() ;
    postfix.clearUp() ;
    stackMethod.clearUp() ;

}


int main()
{

    int command ;

    while ( true ) {
        string inputExpression ;
        int error = -1 ; // error type
        int error1_index = -1 ; // index of the wrong symbol
        int parenthesis = -1 ; // 1: extra open parenthesis, 2: extra close parenthesis
        int operate = -1 ; // 1: extra operator, 2: extra operand, 3: it is not infix in the parentheses

        cout << endl ;
        cout << "* Arithmetic Expression Evaluator *\n" ;
        cout << "* 0. QUIT                         *\n" ;
        cout << "* 1. Infix2postfix Transformation *\n" ;
        cout << "***********************************\n" ;
        cout << "Input a choice(0, 1): " ;
        cin >> command ;

        if ( command == 0 )
            break ;
        else if ( command == 1 ) {
            cout << "\nInput an infix expression: " ;
            getline(cin.ignore(), inputExpression) ;
            const char* charArray = inputExpression.c_str();

            // if input expression is legitimate infix, transform it into a postfix expression
            if ( isExp( charArray, error, error1_index ) && isBalanced( charArray, error, parenthesis ) && isLegal( charArray, error, operate ) ) {
                int symbol = 0 ;
                for ( int i = 0; charArray[i] != NULL; i++ ) {
                    if ( charArray[i] == '0' || charArray[i] == '1' || charArray[i] == '2' || charArray[i] == '3' || charArray[i] == '4' ||
                         charArray[i] == '5' || charArray[i] == '6' || charArray[i] == '7' || charArray[i] == '8' || charArray[i] == '9' ||
                         charArray[i] == '+' || charArray[i] == '-' || charArray[i] == '*' || charArray[i] == '/' || charArray[i] == '(' || charArray[i] == ')' )
                        symbol ++ ;
                }
                if ( symbol == 0 )
                    cout << "Error 3: there is one extra operator.\n" ;
                else {
                    cout << "It is a legitimate infix expression.\n" ;
                    cout << "Postfix expression: " ;
                    infix2postfix( charArray ) ;
                }
            }
            else {
                if ( error == 1 )
                    cout << "Error 1: " << charArray[error1_index] << " is not a legitimate character.\n" ;
                else if ( error == 2 && parenthesis == 1 )
                    cout << "Error 2: there is one extra open parenthesis.\n" ;
                else if ( error == 2 && parenthesis == 2 )
                    cout << "Error 2: there is one extra close parenthesis.\n" ;
                else if ( error == 3 && operate == 1 )
                    cout << "Error 3: there is one extra operator.\n" ;
                else if ( error == 3 && operate == 2 )
                    cout << "Error 3: there is one extra operand.\n" ;
                else if ( error == 3 && operate == 3 )
                    cout << "Error 3: it is not infix in the parentheses.\n" ;
            }
        }
        else
            cout << "\nCommand does not exist!\n" ;

    } // while

    return 0;
}
