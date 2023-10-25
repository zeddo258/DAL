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
			// 讀入一行 
			s.assign(tmp) ;
		}  
		
		bool isNum( int i ) {
			if( tmp[i] >= '0' and tmp[i] <= '9' ) 
				return true ;
			else return false ;
			// 判斷數字 
		}
		
		bool isSpace( int i ) {
			if( tmp[i] == '\n' or tmp[i] == ' ' or tmp[i] == '	' or tmp[i] == '\0' or tmp[i] == '\t' )
				return true ;
			else return false ;
			// 判斷空格 
		}
		
		bool isOperator( int i ) {
			if( tmp[i] == '+' or tmp[i] == '-' or tmp[i] == '*' or tmp[i] == '/' )
				return true ;
			else return false ;
			// 判斷加減乘除 
		}
		
		bool isParenthesis( int i ) {
			if( tmp[i] == '(' or tmp[i] == ')' ) 
				return true ;
			else return false ;
			// 判斷括號 
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
			// 錯誤輸出 
		}
		
		void judgeTmp() {
			
			bool canRun = true ;  // 能不能跑 			
			numOrOpeCompile noc = Nothing ;  // 上個非空格字元是啥 		
			int i = 0 ;  // tmp位置 			
			int type = 0 ;
			int type1 = 0 ;  // 錯誤形式 			
			int numOfPar = 0 ;  // 括號數量 
			
			while( i < 1000 ) {
				if( isSpace(i) == true ) {
					i++ ;
				}  // space無例外 		
				else if( isNum(i) == true ) {
					i++ ;
					/* 優先級 1 > 2 > 3 
					  同error發生會覆寫 */
					if( noc == ParL and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 2 ;
						canRun = false ;
					}
					// num例外 : 3 2 少運算 ex. )1 
					noc = Num ;
				}
				else if( isOperator(i) == true ) {
					i++ ;
					if( noc == Ope and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 1 ;
						canRun = false ;
					}
					// ope例外 : 3 3 ()內沒東西 ex. (+
					if( noc == ParR and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 3 ;
						canRun = false ;
					}
					// ope例外 : 3 1 多運算 ex. )+
					if( noc == Nothing and type != 2 and type != 3 ) {
						type = 3 ;
						type1 = 1 ;
						canRun = false ;
					}
					// ope例外 : 3 1 多運算 ex. +1 
					noc = Ope ;
				}
				else if( isParenthesis(i) == true ) {
					if( tmp[i] == '(' ) {
						if( noc == Num and type != 2 and type != 3 ) {
							type = 3 ;
							type1 = 2 ;
							canRun = false ;
						}
						// parR例外 : 3 2 少運算 ex. 1(
						if( noc == 	ParL ) {
							if( numOfPar < 0 and type != 2  and type != 3 ) {
								type = 2 ;
								type1 = 2 ;
								canRun = false ;
							} // 多括號 
							else {
								if( type != 2 and type != 3 ) {
									type = 3 ;
									type = 2 ;
									canRun = false ;
								}
							} // 少運算 
						} 
						// parR例外 : )(特殊情況 多) or 3 2 少運算 ex. )(
						numOfPar++ ;
						noc = ParR ;
					}  // 前括號 
					if( tmp[i] == ')' ) {
						if( noc == Ope and type != 3 ) {
							type = 3 ;
							type1 = 3 ;
							canRun = false ;
						}
						// parL例外 : 3 3 ()沒東西 ex. +)
						if( noc == ParR and type != 3 ) {
							type = 3 ;
							type1 = 3 ;
							canRun = false ;
						}
						// parL例外 : 3 3 ()沒東西 ex. ()
						numOfPar-- ;
						noc = ParL ;
					}  // 後括號 
					
					i++ ;
				}
				else {
					type = 1 ;
					type1 = 0 ;
					canRun = false ;
					break ;
				}  // 不合理字元 	
			}
			if( noc == Ope  and type != 3 ) {
				canRun = false ;
				type = 3 ;
				type1 = 1 ;
			}
			// 算是結尾是運算
			// 3 1 多運算 
			if( numOfPar != 0  and type != 2 ) {
				type = 2 ;
				if( numOfPar > 0 ) type1 = 1 ;
				if( numOfPar < 0 ) type1 = 2 ;
				canRun = false ;
			}
			// 前後括號數量不一
			// 前括號++ 後括號-- 數量相同 numOfPar == 0 
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
	in.readInput() ;  // 讀入 
	in.judgeTmp() ;  // 判斷 
    in.cleanTmp() ;  // 清除 
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
	    // 清掉在buffer的指令 
	    
	    if ( command == 1 ) {
	    	LetsGo() ;
		} // 跑練習一 
		
		
		else if( !command ) break ;
		
		else cout << endl << "Command does not exist!" << endl ;
		
	}while(true) ;
	
    system("pause") ;
    return 0 ;
    
} // main

