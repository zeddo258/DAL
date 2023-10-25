//********************************************************************************/
// Exercise 03: Infix2Postfix & Postfix Evaluator by Wu, Yi-Hung@ICE.CYCU, 2019/10
//********************************************************************************/
//#define QUIZ
#define QUIZB
//#define REPLY                                                   // add %

#include <string>                                               // string class
#include <cstdlib>                                              // system, atoi

//#include "DS1expLIST.hpp"                                       // header file for expLIST class
//*************************************************************/
//Header file for expLIST class Yi-Hung Wu    2019/10
//*************************************************************/
#include <iostream>	                                    // endl
#include <new>	                                        // new

using namespace std;								    // standard naming space

template <class T>                                      // type template for data value in list node

class   expLIST
{   typedef struct qN								    // structure of each node in list
    {   T           value;
        struct qN   *next;    						    // next node
    }   listNode;
    listNode *head, *tail; 						        // only two data members
public:
    expLIST(): head(NULL), tail(NULL)        		    // constructor with initialization
    {	} //end expLIST initializer

    bool isEmpty()  const 							    // decide whether list is empty
    {   return head == NULL;
    }  //end expLIST::isEmpty

    void ins(const T inValue)					        // append one value into list
    {   try
        {	listNode *newPtr = new listNode;

            newPtr->value = inValue;
            newPtr->next = NULL;
            if (isEmpty())                              // create the first node
                head = newPtr;
            else
                tail->next = newPtr;                    // append the last node
            tail = newPtr;                              // move to the tail
        } // end try
        catch (std::bad_alloc& ba)					    // unable to allocate space
        {   std::cerr << endl << "bad_alloc on list caught: " << ba.what() << endl;
        }   // end catch
    }	// end expLIST::ins

    void getHead(T& outValue)						    // get the head of list without removal
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty list!" << endl;
        else
            outValue = head->value;
    }	// end expLIST::getHead

    void del()									        // remove the head of list
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty list!" << endl;
        else
        {	listNode *tempPtr = head;

            head = head->next;
            if (isEmpty())                              // the last node is removed
                tail = NULL;
            tempPtr->next = NULL;
            delete tempPtr;
            tempPtr = NULL;
        } // end else
    }	// end expLIST::del without output parameter

    void del(T& outValue)						        // get the head of stack and remove it
    {	getHead(outValue);
        del();
    }	// end expLIST::del with output parameter

    void show()                                         // display the content of each node in sequence
    {   if (!isEmpty())
        {   cout << head->value;
            for (listNode *cur = head->next; cur != NULL; cur = cur->next)
                cout << ", " << cur->value;
            cout << endl;
        }   // end if
    }   //end expLIST:show

    void clearUp()									    // clear up the entire list
    {   while (!isEmpty())
            del();
    }   // end clearUp

    expLIST(expLIST &src): head(NULL), tail(NULL)       // deep copy constructor
    {   clearUp();
        for (listNode *ptr = src.head; ptr != NULL; ptr = ptr->next)
            ins(ptr->value); // traverse the entire list
    } //end expLIST deep copy constructor

    ~expLIST()										    // destructor
    {   clearUp();
    }   // end destructor
};	//end expLIST class
//********************************************************************************/
// The above is self-defined expLIST class, used for keeping a series of strings
//********************************************************************************///

//#include "DS1expSTACK.hpp"                                      // header file for expSTACK class
//********************************************************************************/
//Header file for expSTACK class Yi-Hung Wu    2015/11/20
//********************************************************************************/
#include <iostream>	                                            // endl
#include <new>	                                                // new

using namespace std;										    // standard naming space

template <class T>                                              // type template for data value in stack node

class   expSTACK
{   typedef struct sN										    // structure of each node in stack
    {   T           value;
        struct sN   *next;    								    // next node
    }   stackNode;
    stackNode *topPtr; 										    // only one data member
public:
    expSTACK(): topPtr(NULL)        						    // constructor with initialization
    {	} //end expSTACK initializer

    bool isEmpty()  const 									    // decide whether stack is empty
    {   return topPtr == NULL;
    }  //end expSTACK::isEmpty

    void push(const T inValue)								    // add one value into stack
    {   try
        {	stackNode *newPtr = new stackNode;

            newPtr->value = inValue;
            newPtr->next = topPtr;
            topPtr = newPtr;
        } // end try
        catch (std::bad_alloc& ba)						        // unable to allocate space
        {   std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
        }   // end catch
    }	// end expSTACK::push

    void getTop(T& outValue)								    // get the top of stack without removal
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty stack!" << endl;
        else
            outValue = topPtr->value;
    }	// end expSTACK::getTop

    void pop()											        // remove the top of stack
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty stack!" << endl;
        else
        {	stackNode *tempPtr = topPtr;

            topPtr = topPtr->next;
            tempPtr->next = NULL;
            delete tempPtr;
            tempPtr = NULL;
        } // end else
    }	// end expSTACK::pop without output parameter

    void pop(T& outValue)									    // get the top of stack and remove it
    {	getTop(outValue);
        pop();
    }	// end expSTACK::pop with output parameter

    ~expSTACK()											        // destructor
    {   while (!isEmpty())
            pop();
    }   // end destructor
};	//end expSTACK class
//********************************************************************************/
// The above is self-defined expSTACK class, used for keeping a series of values
//********************************************************************************/

#define MAX_LEN 255                                             // maximum string length
#define TAB     '\t'                                            // tabular key character
#define WS      ' '                                             // white space character

using namespace std;

bool isExp(string&);		                                    // check the validity of each symbol
bool isNumber(const char);		                                // check whether the character is a number
bool isOp(const char);		                                    // check whether the character is an operator
bool isPar(const char);		                                    // check whether the character is a parenthesis
bool isBalanced(const string);		                            // check the validity of balanced parentheses
bool isLegal(const string);		                                // check whether it is a legal expression
void str2list(const string, expLIST<string>&);                  // parse a string into a linked list
bool infix2postfix(expLIST<string>&, expLIST<string>&);         // transform infix into postfix
void postfixEval(expLIST<string>&);                             // evaluate the value of postfix
#ifdef QUIZB
void rewind(expLIST<string>&);                                  // reverse the linked lists
bool infix2prefix(expLIST<string>&, expLIST<string>&);          // transform infix into prefix
#ifdef QUIZ 
void prefixEval(expLIST<string>&);                              // evaluate the value of prefix
#endif
#endif

int main(void)
{   int command;									            // user command

    do
    {   string  infixS;

        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         *";
#ifdef QUIZ
        cout << endl << "* 1. Infix2postfix Evaluation     *";
#else
        cout << endl << "* 1. Infix2postfix Transformation *";
#endif // QUIZ
#ifdef QUIZB
#ifdef QUIZ
        cout << endl << "* 2. Infix2prefix Evaluation     *";
#else
        cout << endl << "* 2. Infix2prefix Transformation *";
#endif // QUIZ
#endif
        cout << endl << "***********************************";
#ifdef QUIZB
        cout << endl << "Input a choice(0, 1, 2): ";

#else
        cout << endl << "Input a choice(0, 1): ";
#endif
        cin >> command;     							        // get a command
        cin.ignore(MAX_LEN, '\n');							    // clear the input buffer
        switch (command)
        {	case 0: break;
            case 1: cout << endl << "Input an infix expression: ";
                    getline(cin, infixS);
                    if (isExp(infixS) &&                        // check each symbol & remove useless ones
                        isBalanced(infixS)                      // check the validity of balanced parentheses
                        && isLegal(infixS))                     // check whether it is a legal expression
                    {   expLIST<string> infixE, postfixE;

                        str2list(infixS, infixE);               // parse a string into a linked list
                        if (infix2postfix(infixE, postfixE))    // transform infix into postfix
#ifdef QUIZ
                            postfixEval(postfixE);              // evaluate the value of postfixS
#else
                            ;
#endif // QUIZ
                    }   // end if
                    break;
#ifdef QUIZB
            case 2: cout << endl << "Input an infix expression: ";
                    getline(cin, infixS);
                    if (isExp(infixS) &&                        // check each symbol & remove useless ones
                        isBalanced(infixS)                      // check the validity of balanced parentheses
                        && isLegal(infixS))                     // check whether it is a legal expression
                    {   expLIST<string> infixE, prefixE;

                        str2list(infixS, infixE);               // parse a string into a linked list
                        rewind(infixE);                         // reverse it from right to left
                        if (infix2prefix(infixE, prefixE))      // transform infix into prefix
#ifdef QUIZ
                            prefixEval(prefixE);                // evaluate the value of prefix
#else
							;
#endif
                    }   // end if
                    break;
#endif
            default: cout << endl << "Command does not exist!" << endl;
        }	// end switch
    } while (command != 0);						                // '0': stop the program
    system("pause");										    // pause the display
    return 0;
}	// end main

//********************************************************************************/
// Mission I. isExp(), isNumber(), isOp(), isPar(), isBalanced(), isInfix()
//********************************************************************************/
bool isExp(string &S)		                                    // check the validity of each symbol
{   for (int i = 0; i < S.size(); ++i)
        if ((S[i] == WS) || (S[i] == TAB))
        {   S.erase(S.begin()+i);                               // remove white space characters
            --i;                                                // move backward one position
        }   // end if
        else if ((!isNumber(S[i])) && (!isOp(S[i])) && (!isPar(S[i])))   // numbers, operators, parentheses only
        {   cout << "Error 1: " << S[i] << " is not a legitimate character." << endl;
            return false;
        }   // end else-if
    return true;
}   // end isExp

bool isNumber(const char c)		                                // check whether the character is a number
{   return ((c >= '0') && (c <= '9'));						    // only a single number in [0,9] is allowed
}   // end isNumber

bool isOp(const char c)		                                    // check whether the character is an operator
{
#ifdef REPLY
    return ((c == '+') || (c == '-') || (c == '*') ||
             (c == '/') || (c == '%'));                         // 5 types of operators are allowed
#else
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));  // only 4 types of operators are allowed
#endif
}   // end isOp

bool isPar(const char c)		                                // check whether the character is a parenthesis
{   return ((c == '(') || (c == ')'));                          // only 2 types of parentheses are allowed
}   // end isPar

bool isBalanced(const string S)		                            // check the validity of balanced parentheses
{   int leftC = 0;

    for (int i = 0; (i < S.size()) && (leftC >= 0); i++)
        switch (S[i])
        {   case '(':   leftC++;
                        break;
            case ')':	leftC--;
        }   // end switch
    if (leftC)
    {   if (leftC > 0)
            cout << "Error 2: there is one extra open parenthesis." << endl;
        else
            cout << "Error 2: there is one extra close parenthesis." << endl;
        return false;
    }   // end if
    return true;
}   // end isBalanced

bool isLegal(const string S)		                            // check whether it is a legal expression
{   int NO_OP = -1;

    for (int j, i = 0; ((i < S.size()) && ((NO_OP == 0) || (NO_OP == -1))); i++)
        if (isNumber(S[i]))                                     // gather contiguous numbers
        {   ++NO_OP;
            j = 1;
            while ((i+j < S.size()) && (isNumber(S[i+j])))
                ++j;
            i += j - 1;
        }   // end if
        else if (isOp(S[i]))
            --NO_OP;
		else if (isPar(S[i]))
            if (((S[i] == '(') && (isOp(S[i+1]) || (S[i+1] == ')'))) ||
                ((S[i] == ')') && (isOp(S[i-1]) || (S[i-1] == '('))))
            {   cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }   // end inner-if
    if (NO_OP)
    {   if (NO_OP > 0)
            cout << "Error 3: there is one extra operand." << endl;
        else
            cout << "Error 3: there is one extra operator." << endl;
        return false;
    }   // end if
    cout << "It is a legitimate infix expression." << endl;
    return true;
}   // end isLegal

//********************************************************************************/
// Mission II. str2list(), infix2postfix()
//********************************************************************************/
void str2list(const string S, expLIST<string> &EL)              // parse a string into a linked list
{   for (int j, i = 0; i < S.size(); i++)			            // read the characters one by one
    {   if (isNumber(S[i]))                                     // gather a series of contiguous numbers
        {   j = 1;
            while ((i+j < S.size()) && (isNumber(S[i+j])))
                ++j;
            EL.ins(S.substr(i,j));
            i += j - 1;
        }   // end if
        else if (S[i] != WS)                                    // keep one operator or delimiter
            EL.ins(S.substr(i,1));
    }   // end for
}   // end str2list

bool infix2postfix(expLIST<string> &ifxE, expLIST<string> &pfxE)    // transform infixS into postfixS
{   expSTACK<string>    aStack;							        // stack object: value type is <char>

    while (!ifxE.isEmpty())                                     // read the list elements one by one
    {   string  cur;

        ifxE.del(cur);
        if (isNumber(cur[0]))							        // directly output the operand
            pfxE.ins(cur);
        else if (isOp(cur[0]))                                  // newcomer is an operator
            while (!aStack.isEmpty())
            {   string  temp;

                aStack.pop(temp);
                if (isOp(temp[0]))                              // another operator on top of stack
                {                                               // validate the operator precedence
#ifdef REPLY
                    if (((cur[0] == '*') || (cur[0] == '/') || (cur[0] == '%')) &&
                        ((temp[0] == '+') || (temp[0] == '-')))
#else
                    if (((cur[0] == '*') || (cur[0] == '/')) &&
                        ((temp[0] == '+') || (temp[0] == '-')))

#endif
                    {                                           // only case to stop removing top of stack
                        aStack.push(temp);                      // put operator back
                        break;
                    }   // end inner if
                    else
                        pfxE.ins(temp);                         // output the operand (top of stack)
                }   // end outer if
                else if (temp[0] == '(')
                {
                    aStack.push(temp);                          // put '(' back for future ')'
                    break;
                }   // end inner else-if
                else
                    return false;                               // other symbols mean invalid
            }   // end while
        if ((cur[0] == '(') || (isOp(cur[0])))                  // keep the operator in stack
            aStack.push(cur);
        else if (cur[0] == ')')
            do
            {   string  temp;

                if (aStack.isEmpty())                           // unable to find '('
                    return false;
                aStack.pop(temp);
                if (temp[0] == '(')                             // find a matched '('
                    break;
                if (isOp(temp[0]))
                    pfxE.ins(temp);                             // output the operator
                else
                    return false;                               // other symbols mean invalid
            } while (1);
    }   // end for
    while (!aStack.isEmpty())
    {   string  temp;

        aStack.pop(temp);
        if (isOp(temp[0]))
            pfxE.ins(temp);                                     // output the operator
        else
            return false;                                       // other symbols such as '(' mean invalid
    }   // end while
    cout << "Postfix expression: ";
    pfxE.show();                                                // show the postfix expression as a result
    return true;
}   // end infix2postfix

//********************************************************************************/
// Mission III. postfixEval()
//********************************************************************************/
void postfixEval(expLIST<string> &pE)                           // evaluate the value of postfix
{   bool            success = true;                             // see whether it is an invalid expression
    int             value;
    expSTACK<int>   aStack;                                     // stack object with type <int>

    while (success && (!pE.isEmpty()))                          // read the list elements one by one
    {   string  cur;

        pE.del(cur);
        if (isNumber(cur[0]))                                   // keep the operands in stack
            aStack.push(atoi(cur.c_str()));					    // transform a character into a number
        else if (isOp(cur[0]) && (!aStack.isEmpty()))		    // newcomer is an operator
        {   int   v2;

            aStack.pop(v2);					                    // the second operand
            if (!aStack.isEmpty())
            {   int   v1, temp;

                aStack.pop(v1);						            // the first operand
                switch (cur[0])					                // calculate the temporary result
                {   case '+':   temp = v1 + v2;
                                break;
                    case '-':   temp = v1 - v2;
                                break;
                    case '*':   temp = v1 * v2;
                                break;
                    case '/':   if (v2)
                                    temp = (int)v1 / v2;
                                else                            // Error: Divided by ZERO!!
                                {   cout << "### Error: Divided by ZERO! ###" << endl;
                                    success = false;
                                }   // end else
                                break;
#ifdef REPLY
                    case '%':   if (v2)
                                    temp = (int)v1 % v2;
                                else                            // Error: Divided by ZERO!!
                                {   cout << "### Error: Divided by ZERO! ###" << endl;
                                    success = false;
                                }   // end else
                                break;
#endif
                    default:    success = false;
                }   // end switch
                aStack.push(temp);                              // save the temporary result
            }   // end inner if
            else
                success = false;
        }   // end else-if
        else
            success = false;
    }   // end while
    if (!aStack.isEmpty())
        aStack.pop(value);
    if (success && aStack.isEmpty())
        cout << "Answer: " << value << endl;                   // show the computed value as a result
    else
        cout << "### It cannot be successfully evaluated! ###" << endl;
}   // end postfixEvalrewind

#ifdef QUIZB
//********************************************************************************/
// New Mission. rewind(), infix2prefix(), prefixEval()
//********************************************************************************/
void rewind(expLIST<string> &ifxE)                             // reverse the linked lists
{   expSTACK<string>    buf;
    string              temp;

    while (!ifxE.isEmpty())
    {   ifxE.del(temp);
        buf.push(temp);                                         // keep it in the LIFO order
    }   // end while
    while (!buf.isEmpty())
    {   buf.pop(temp);
        ifxE.ins(temp);                                         // restore it reversely
    }   // end while
}   // end rewind

bool infix2prefix(expLIST<string> &ifxE, expLIST<string> &pfxE) // transform infixS into postfixS
{   expSTACK<string>    aStack;							        // stack object: value type is <char>

    while (!ifxE.isEmpty())                                     // read the list elements one by one
    {   string  cur;

        ifxE.del(cur);
        if (isNumber(cur[0]))							        // directly output the operand
            pfxE.ins(cur);
        else if (isOp(cur[0]))                                  // newcomer is an operator
            while (!aStack.isEmpty())
            {   string  temp;

                aStack.pop(temp);
                if (isOp(temp[0]))                              // another operator on top of stack
                {                                               // validate the operator precedence
#ifdef REPLY
                    if (((cur[0] == '+') || (cur[0] == '-')) &&
                        ((temp[0] == '*') || (temp[0] == '/') || (temp[0] == '%')))
#else
                    if (((cur[0] == '+') || (cur[0] == '-')) &&
                        ((temp[0] == '*') || (temp[0] == '/')))
#endif
                        pfxE.ins(temp);                         // output the operand (top of stack)
                    else
                    {                                           // cases to stop removing top of stack
                        aStack.push(temp);                      // put operator back
                        break;
                    }   // end inner if
                }   // end outer if
                else if (temp[0] == ')')
                {
                    aStack.push(temp);                          // put ')' back for future '('
                    break;
                }   // end inner else-if
                else
                    return false;                               // other symbols mean invalid
            }   // end while
        if ((cur[0] == ')') || (isOp(cur[0])))                  // keep the operator in stack
            aStack.push(cur);
        else if (cur[0] == '(')
            do
            {   string  temp;

                if (aStack.isEmpty())                           // unable to find '('
                    return false;
                aStack.pop(temp);
                if (temp[0] == ')')                             // find a matched '('
                    break;
                if (isOp(temp[0]))
                    pfxE.ins(temp);                             // output the operator
                else
                    return false;                               // other symbols mean invalid
            } while (1);
    }   // end for
    while (!aStack.isEmpty())
    {   string  temp;

        aStack.pop(temp);
        if (isOp(temp[0]))
            pfxE.ins(temp);                                     // output the operator
        else
            return false;                                       // other symbols such as '(' mean invalid
    }   // end while
    rewind(pfxE);                                               // restore it from left to right
    cout << "Prefix expression: ";
    pfxE.show();                                                // show the postfix expression as a result
    return true;
}   // end infix2prefix

#ifdef QUIZ
void prefixEval(expLIST<string> &pE)                            // evaluate the value of postfix
{   bool            success = true;                             // see whether it is an invalid expression
    int             value;
    expSTACK<int>   aStack;                                     // stack object with type <int>

    rewind(pE);                                                 // reverse it from right to left
    while (success && (!pE.isEmpty()))                          // read the list elements one by one
    {   string  cur;

        pE.del(cur);
        if (isNumber(cur[0]))                                   // keep the operands in stack
            aStack.push(atoi(cur.c_str()));					    // transform a character into a number
        else if (isOp(cur[0]) && (!aStack.isEmpty()))		    // newcomer is an operator
        {   int   v1;

            aStack.pop(v1);					                    // the first operand
            if (!aStack.isEmpty())
            {   int   v2, temp;

                aStack.pop(v2);						            // the second operand
                switch (cur[0])					                // calculate the temporary result
                {   case '+':   temp = v1 + v2;
                                break;
                    case '-':   temp = v1 - v2;
                                break;
                    case '*':   temp = v1 * v2;
                                break;
                    case '/':   if (v2)
                                    temp = (int)v1 / v2;
                                else                            // Error: Divided by ZERO!!
                                {   cout << "### Error: Divided by ZERO! ###" << endl;
                                    success = false;
                                }   // end else
                                break;
#ifdef REPLY
                    case '%':   if (v2)
                                    temp = (int)v1 % v2;
                                else                            // Error: Divided by ZERO!!
                                {   cout << "### Error: Divided by ZERO! ###" << endl;
                                    success = false;
                                }   // end else
                                break;
#endif

                    default:    success = false;
                }   // end switch
                aStack.push(temp);                              // save the temporary result
            }   // end inner if
            else
                success = false;
        }   // end else-if
        else
            success = false;
    }   // end while
    if (!aStack.isEmpty())
        aStack.pop(value);
    if (success && aStack.isEmpty())
        cout << "Answer: " << value << endl;                   // show the computed value as a result
    else
        cout << "### It cannot be successfully evaluated! ###" << endl;
}   // end prefixEval
#endif
#endif
//********************************************************************************/
