#include<fstream>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <stack>
#include <stdexcept> // Include the header for exceptions
#define MAX_LEN 255

using namespace std;

struct StackNode{
	char value ;
	StackNode *next ;
};

template <typename T>
class ExpStack {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* top;

public:
    ExpStack() : top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const T& data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    T getTop() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return top->data;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        Node* temp = top;
        T popped = temp->data;
        top = top->next;
        delete temp;
        return popped;
    }
    
    ~ExpStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};


enum numOrOpeCompile{
	Num = 45641,
	Ope = 73157,
	ParR = 23857,
	ParL = 51569,
	Nothing = 67594 
};

class Infix{
	private:
		char tmp[1000] ;
	public:	
	    bool legal = false ;
	    string s ;
		void readInput() {
			cout << endl << "Input an infix expression:" ;
			memset (tmp, 0,1000); 
			cin.getline(tmp,1000);
			// Ū�J�@�� 
			s.assign(tmp) ;
		}  
		
		bool isNum( int i ) {
			if( tmp[i] >= '0' and tmp[i] <= '9' ) 
				return true ;
			else return false ;
			// �P�_�Ʀr 
		}
		
		bool isSpace( int i ) {
			if( tmp[i] == '\n' or tmp[i] == ' ' or tmp[i] == '	' or tmp[i] == '\0' or tmp[i] == '\t' )
				return true ;
			else return false ;
			// �P�_�Ů� 
		}
		
		bool isOperator( int i ) {
			if( tmp[i] == '+' or tmp[i] == '-' or tmp[i] == '*' or tmp[i] == '/' )
				return true ;
			else return false ;
			// �P�_�[��� 
		}
		
		bool isParenthesis( int i ) {
			if( tmp[i] == '(' or tmp[i] == ')' ) 
				return true ;
			else return false ;
			// �P�_�A�� 
		}
		
		void whatsWrong( int i, int type, int type1 ) {
			if( type == 1 ) {
				cout << endl << "Error1: " ;
				cout << tmp[i] << " is not a legitimate character." ;
			}
			if( type == 2 ) {
				cout << endl << "Error2: " ;
				cout << "there is" ;
				if( type1 == 1 ) cout << " one extra open parenthesis." ;
				if( type1 == 2 ) cout << " one extra close parenthesis." ;
			}
			if( type == 3 ) { 
				cout << endl << "Error3: " ;
				if( type1 == 1 ) cout << "there is one extra operator." ;
				if( type1 == 2 ) cout << "there is one extra operand." ;
				if( type1 == 3 ) cout << "it is not inflix in the parentheses." ;
			}
			// ���~��X 
		}
		
		void judgeTmp() {
			
			bool canRun = true ;  // �ण��] 			
			numOrOpeCompile noc = Nothing ;  // �W�ӫD�Ů�r���Oԣ 		
			int i = 0 ;  // tmp��m 			
			int type = 0 ;
			int type1 = 0 ;  // ���~�Φ� 			
			int numOfPar = 0 ;  // �A���ƶq 
			
			while( i < 1000 ) {
				if( isSpace(i) == true ) {
					i++ ;
				}  // space�L�ҥ~ 		
				else if( isNum(i) == true ) {
					i++ ;
					/* �u���� 1 > 2 > 3 
					  �Perror�o�ͷ|�мg */
					if( noc == ParL and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 2 ;
						canRun = false ;
					}
					// num�ҥ~ : 3 2 �ֹB�� ex. )1 
					noc = Num ;
				}
				else if( isOperator(i) == true ) {
					i++ ;
					if( noc == Ope and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 1 ;
						canRun = false ;
					}
					// ope�ҥ~ : 3 3 ()���S�F�� ex. (+
					if( noc == ParR and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 3 ;
						canRun = false ;
					}
					// ope�ҥ~ : 3 1 �h�B�� ex. )+
					if( noc == Nothing and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 1 ;
						canRun = false ;
					}
					// ope�ҥ~ : 3 1 �h�B�� ex. +1 
					noc = Ope ;
				}
				else if( isParenthesis(i) == true ) {
					if( tmp[i] == '(' ) {
						if( noc == Num and type != 2 and type != 3 ) {
							type = 3 ;
							type1 = 2 ;
							canRun = false ;
						}
						// parR�ҥ~ : 3 2 �ֹB�� ex. 1(
						if( noc == 	ParL ) {
							if( numOfPar < 0 and type != 2  and type != 3 ) {
								type = 2 ;
								type1 = 2 ;
								canRun = false ;
							} // �h�A�� 
							else {
								if( type != 2 and type != 3 ) {
									type = 3 ;
									type = 2 ;
									canRun = false ;
								}
							} // �ֹB�� 
						} 
						// parR�ҥ~ : )(�S���p �h) or 3 2 �ֹB�� ex. )(
						numOfPar++ ;
						noc = ParR ;
					}  // �e�A�� 
					if( tmp[i] == ')' ) {
						if( noc == Ope and type != 3 ) {
							type = 3 ;
							type1 = 3 ;
							canRun = false ;
						}
						// parL�ҥ~ : 3 3 ()�S�F�� ex. +)
						if( noc == ParR and type != 3 ) {
							type = 3 ;
							type1 = 3 ;
							canRun = false ;
						}
						// parL�ҥ~ : 3 3 ()�S�F�� ex. ()
						numOfPar-- ;
						noc = ParL ;
					}  // ��A�� 
					
					i++ ;
				}
				else {
					type = 1 ;
					type1 = 0 ;
					canRun = false ;
					break ;
				}  // ���X�z�r�� 	
			}
			if( noc == Ope  and type != 3 ) {
				canRun = false ;
				type = 3 ;
				type1 = 1 ;
			}
			// ��O�����O�B��
			// 3 1 �h�B�� 
			if( numOfPar != 0  and type != 2 ) {
				type = 2 ;
				if( numOfPar > 0 ) type1 = 1 ;
				if( numOfPar < 0 ) type1 = 2 ;
				canRun = false ;
			}
			// �e��A���ƶq���@
			// �e�A��++ ��A��-- �ƶq�ۦP numOfPar == 0 
			if( canRun == false ) whatsWrong( i, type, type1 ) ;
			else {
				cout << "It's a legitimate infix expression." << endl ;
				legal = true ;
			}
		}
		
		void cleanTmp() {
			memset (tmp, 0,1000); 
		}
		
};

class Infix2Postfix{
	public:
		int precedence(char op) {
	        if(op == '+' || op == '-')
		        return 1 ;
	        if(op == '*' || op == '/')
		        return 2 ;
	        return 0 ;
        } 
        
        void in2post(string str) {
	        
            ExpStack<char> stack;
            StackNode* head = nullptr ;
            head = new StackNode() ;
            StackNode* cur = head ; 
            

            for (int i = 0; i < str.length(); i++) {
                char x = str[i];
                if (isdigit(x)) {
                    cur->value = x ;
                    cur->next = new StackNode() ;
                    cur = cur->next ; 
                } 
	        	else if (x == '(') {
                    stack.push(x);
                } 
		        else if (x == ')') {
		        	cur->value = ',' ;
                    cur->next = new StackNode() ;
                    cur = cur->next ; 
                    while (!stack.isEmpty() && stack.getTop() != '(') {
                        cur->value = stack.pop() ;
                        cur->next = new StackNode() ;
                        cur = cur->next ; 
                    }
                    if (!stack.isEmpty() && stack.getTop() == '(') {
                        stack.pop(); // Pop the '(' from the stack
                    }
                } else {
                	cur->value = ',' ;
                    cur->next = new StackNode() ;
                    cur = cur->next ; 
                    while (!stack.isEmpty() && precedence(x) <= precedence(stack.getTop())) {
                        cur->value = stack.pop() ;
                        cur->next = new StackNode() ;
                        cur = cur->next ;       
                    }
                    stack.push(x);
                }
            }

            // Pop any remaining operators from the stack and append to postfixExpression
            while (!stack.isEmpty()) {
                cur->value = stack.pop() ;
                cur->next = new StackNode() ;
                cur = cur->next ; 
            }
    
            cur = head ;
            while (cur != nullptr) {
                if (cur->value != '\0') {
                	cout << cur->value ;
                	if(cur->next->value == '+' or cur->next->value == '-' or cur->next->value == '*' or cur->next->value == '/') {
        		        if(cur->value != ',')
        		            cout << "," ;
		        	}
            
                }
                cur = cur->next;
            }

            // Output the final postfix expression

        }
};

void LetsGo() {
	Infix in ;
	Infix2Postfix post ;
	string str ;
	in.readInput() ;  // Ū�J 
	in.judgeTmp() ;  // �P�_ 
    in.cleanTmp() ;  // �M�� 
	if(in.legal) {
		for(int i = 0 ; i < in.s.length() ; i++) 
			str+=in.s[i] ;
		post.in2post(str) ;
		
	}
} 

int main() {
	
    int command = 0 ;
    
    do{
    	cout << endl ;
    	cout << endl << "* Arithmetic Expression Evaluator *" ;
    	cout << endl << "* 0. QUIT                         *" ;
    	cout << endl << "* 1. Infix2postfix Transformation *" ;
    	cout << endl << "***********************************" ;
    	cout << endl << "Input a choice(0, 1):" ;
	    cin >> command ;
	    
	    cin.ignore(MAX_LEN, '\n' ) ; 
	    // �M���bbuffer�����O 
	    
	    if ( command == 1 ) {
	    	LetsGo() ;
		} // �]�m�ߤ@ 
		
		
		else if( !command ) break ;
		
		else cout << endl << "Command does not exist!" << endl ;
		
	}while(true) ;
	
    system("pause") ;
    return 0 ;
    
} // main

