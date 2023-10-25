
// 11127229 廖翊崴

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <iostream>
using namespace std ;


struct Node {
    char ch ;
    Node * next ;
};

typedef Node * NodePtr ;  // make code look better to read
typedef int Arr30 [30] ;  // in order to call by reference between function


class Stack {
public:
    int operator_sum ;  // record have how many operator
    char * sta ;  // for do stack
    void ToPostfix( NodePtr infix, NodePtr &postfix ) ;
};


int SetInfix( NodePtr &infix ) ;
int CheckError( NodePtr infix ) ;
void CheckDivisor( NodePtr infix ) ;
int RecordNumber( NodePtr infix, Arr30 &num_len ) ;
int Priority( char op ) ;
void PrintPostfix( NodePtr postfix, Arr30 num_len ) ;
void Print( NodePtr head ) ;


// main code
int main( void ) {
    while ( true ) {
        printf( "\n* Arithmetic Expression Evaluator *\n" ) ;
        printf( "* 0. QUIT                         *\n" ) ;
        printf( "* 1. Infix2postfix Transformation *\n" ) ;
        printf( "***********************************\n" ) ;
        printf( "Input a choice(0, 1): " ) ;
        char command[50] ;  // to avoid user input a string
        gets( command ) ;
        printf( "\n" ) ;
        if ( (int)command[0] - 48 == 0 && command[1] == '\0' ) return 0 ;  // command is 0
        else if ( (int)command[0] - 48 == 1 && command[1] == '\0' ) {  // command is 1
            NodePtr infix = NULL ;
            NodePtr postfix = NULL ;
            printf( "Input an infix expression: " ) ;

            int num_len[30] = {0} ;  // to store every number's length
            int num_len_sum = 0 ;
            Stack s ;

            s.operator_sum = SetInfix( infix ) ;
            if ( CheckError( infix ) == 0 ) {
                printf( "It is a legitimate infix expression.\n" ) ;
                CheckDivisor( infix ) ;
                num_len_sum = RecordNumber( infix, num_len ) ;
                s.ToPostfix( infix, postfix ) ;
                PrintPostfix( postfix, num_len ) ;
            }

            NodePtr temp1 = NULL ;
            while ( infix != NULL ) {  // free infix
                temp1 = infix ;
                infix = infix -> next ;
                free( temp1 ) ;
            }

            NodePtr temp2 = NULL ;
            while ( postfix != NULL ) {  // free postfix
                temp2 = postfix ;
                postfix = postfix -> next ;
                free( temp2 ) ;
            }
        }
        else {
            printf( "Command does not exist!\n" ) ;
        }
    }

    return 0 ;
}


// set up infix, return sum of operator
int SetInfix( NodePtr &infix ) {
    NodePtr temp = NULL ;
    int operator_sum = 0 ;
    char ch ;
    scanf( "%c", &ch ) ;
    if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' ) operator_sum++ ;
    while ( true ) {
        if ( ch != ' ' && ch != '\t' && ch != '\n' ) {
            if ( infix == NULL ) {
                infix = new Node ;
                infix -> ch = ch ;
                infix -> next = NULL ;
                temp = infix ;
            }
            else {
                temp -> next = new Node ;
                temp = temp -> next ;
                temp -> ch = ch ;
                temp -> next = NULL ;
            }
        }

        scanf( "%c", &ch ) ;
        if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' ) operator_sum++ ;
        else if ( ch == '\n' ) break ;
    }

    return operator_sum ;
}


// check errors, have error return 1, haven't error return 0
int CheckError( NodePtr infix ) {
    char ch ;
    NodePtr temp = NULL ;
    // check error which have illegitimate character
    temp = infix ;
    while ( temp != NULL ) {
        ch = temp -> ch ;
        if ( (int)ch < 48 || (int)ch > 57 ) {
            if ( ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')' ) {
                printf( "Error 1: %c is not a legitimate character.\n", ch ) ;
                return 1 ;
            }
        }

        temp = temp -> next ;
    }

    // check error which have extra open or close parenthesis
    temp = infix ;
    int open = 0, close = 0 ;
    while ( temp != NULL ) {
        if ( temp -> ch == '(' ) open++ ;
        else if ( temp -> ch == ')' ) close++ ;

        temp = temp -> next ;
    }

    if ( open > close ) {
        if ( open - close == 1 ) printf( "Error 2: there is one extra open parenthesis.\n" ) ;
        else if ( open - close == 2 ) printf( "Error 2: there is two extra open parenthesis.\n" ) ;
        else if ( open - close == 3 ) printf( "Error 2: there is three extra open parenthesis.\n" ) ;
        return 1 ;
    }
    else if ( open < close ) {
        if ( close - open == 1 ) printf( "Error 2: there is one extra close parenthesis.\n" ) ;
        else if ( close - open == 2 ) printf( "Error 2: there is two extra close parenthesis.\n" ) ;
        else if ( close - open == 3 ) printf( "Error 2: there is three extra close parenthesis.\n" ) ;
        return 1 ;
    }

    // check error which have extra operator or operand
    NodePtr temp1 = infix, temp2 = infix -> next ;
    char ch1, ch2 ;
    while ( temp2 != NULL ) {
        ch1 = temp1 -> ch ;
        ch2 = temp2 -> ch ;
        if ( ch1 == '+' || ch1 == '-' || ch1 == '*' || ch1 == '/' ) {
            if ( ch2 == '+' || ch2 == '-' || ch2 == '*' || ch2 == '/' ) {
                printf( "Error 3: there is one extra operator.\n" ) ;
                return 1 ;
            }
        }
        else if ( (int)ch1 >= 48 && (int)ch1 <= 57 && ch2 == '(' ) {
            printf( "Error 3: there is one extra operand.\n" ) ;
            return 1 ;
        }
        else if ( ch1 == ')' && (int)ch2 >= 48 && (int)ch2 <= 57 ) {
            printf( "Error 3: there is one extra operand.\n" ) ;
            return 1 ;
        }

        temp1 = temp1 -> next ;
        temp2 = temp2 -> next ;
    }

    return 0 ;
}


// check divisor which can't be zero
void CheckDivisor( NodePtr infix ) {
    NodePtr temp1 = infix, temp2 = infix -> next ;
    while ( temp2 != NULL ) {
        if ( temp1 -> ch == '/' && temp2 -> ch == '0' ) {
            printf( "The divisor cannot be zero !\n" ) ;
            return ;
        }

        temp1 = temp1 -> next ;
        temp2 = temp2 -> next ;
    }
}


// record each of number's length, and return sum of them
int RecordNumber( NodePtr infix, Arr30 &num_len ) {
    NodePtr temp = infix ;
    int i = 0, len = 0, boo = 0 ;
    char ch ;
    while ( true ) {
        ch = temp -> ch ;
        while ( (int)ch >= 48 && (int)ch <= 57 ) {
            len++ ;
            boo = 1 ;  // finished a number
            temp = temp -> next ;
            if ( temp == NULL ) {  // to avoid keeping doing
                num_len[i] = len ;
                i++ ;
                return i ;
            }

            ch = temp -> ch ;
        }

        if ( boo == 1 ) {
            num_len[i] = len ;
            i++ ;
            len = 0 ;
            boo = 0 ;
        }

        temp = temp -> next ;
        if ( temp == NULL ) return i ;
    }
}


// turn infix into postfix
void Stack::ToPostfix( NodePtr infix, NodePtr &postfix ) {
    NodePtr temp = infix, temp_post = NULL ;
    postfix = new Node ;
    temp_post = postfix ;
    sta = ( char * ) malloc( sizeof( char ) * operator_sum ) ;
    for ( int i = 0 ; i < operator_sum ; i++ ) sta[i] = '\0' ;
    int stack_i = 0 ;
    for ( ; temp != NULL ; temp = temp -> next ) {
        if ( temp -> ch == '(' ) {  // it's left parenthesis
            sta[++stack_i] = temp -> ch ;  // put it into stack
        }
        else if ( temp -> ch == '+' || temp -> ch == '-' || temp -> ch == '*' || temp -> ch == '/' ) {  // if it's operator
            while ( Priority( sta[stack_i] ) >= Priority( temp -> ch ) && stack_i >= 0 ) {  // judge the priority of operator
                temp_post -> ch = sta[stack_i--] ;  // put into postfix
                temp_post -> next = new Node ;
                temp_post = temp_post -> next ;
            }

            sta[++stack_i] = temp -> ch ;
        }
        else if ( temp -> ch == ')' ) {  // it's right parenthesis
            while ( sta[stack_i] != '(' ) {  // output untial encounter the left parenthesis
                temp_post -> ch = sta[stack_i--] ;  // put into postfix
                temp_post -> next = new Node ;
                temp_post = temp_post -> next ;
            }

            stack_i-- ;  // ignore right parenthesis
        }
        else {  // it's number
            temp_post -> ch = temp -> ch ;  // put into postfix
            temp_post -> next = new Node ;
            temp_post = temp_post -> next ;
        }
    }

    while ( stack_i > 0 ) {
        temp_post -> ch = sta[stack_i--] ;  // put into postfix
        temp_post -> next = new Node ;
        temp_post = temp_post -> next ;
    }

    temp_post -> next = NULL ;  // the last node's next ( temp_post -> ch = '\0' )
    free( sta ) ;  // free stack
}


// priority of operator, multiplication and division first, then addition and subtraction
int Priority( char op ) {
    if ( op == '+' || op == '-' ) return 1 ;
    else if ( op == '*' || op == '/' ) return 2 ;
    else return 0 ;  // left parenthesis, right parenthesis and else
}


// output the postfix
void PrintPostfix( NodePtr postfix, Arr30 num_len ) {
    printf( "Postfix expression: " ) ;
    NodePtr temp = NULL ;
    temp = postfix ;
    int num_len_i = 0, boo = 0 ;
    char ch = temp -> ch ;
    while ( true ) {
        if ( (int)ch >= 48 && (int)ch <= 57 ) {  // in order to restore the original numbers
            for ( int i = 1 ; i <= num_len[num_len_i] ; i++ ) {
                printf( "%c", ch ) ;
                temp = temp -> next ;
                if ( temp -> next == NULL ) break ;
                ch = temp -> ch ;
                boo = 1 ;  // already jumped to the next one
            }
        }
        else {
            printf( "%c", ch ) ;
        }

        if ( temp -> next == NULL ) break ;

        if ( boo == 0 ) {
            temp = temp -> next ;
            if ( temp -> next == NULL ) break ;
            ch = temp -> ch ;
        }
        else {
            num_len_i++ ;
            boo = 0 ;
        }

        if ( temp -> next == NULL ) break ;
        printf( ", " ) ;
    }

    printf( "\n" ) ;
}
