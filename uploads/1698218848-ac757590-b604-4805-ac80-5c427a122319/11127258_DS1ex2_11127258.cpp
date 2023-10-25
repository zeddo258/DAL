//11127258, 簡珮涵 
#include <string> // string class
#include <cstdlib> // system, atoi
#include <iostream>
#include <stdio.h>
#define MAX_LEN 255 // maximum string length

using namespace std ;

struct Node {
    string data;  
    Node* next ;
};

class Stack {
public:
    Node* s ; 

    Stack() { // 設置堆疊串鍊 
        s = NULL ;
    }

    void push(string input) { // 新增
	    if (s == NULL) {
			s = new Node ;
			s->data = input ;
			s->next = NULL ;
		}
	
		else { // s != NULL
			Node* head = s ;
			while(head->next != NULL) {
				head = head->next ;
			}
		
			head->next = new Node ;
			head = head->next ;
			head->data = input ;
			head->next = NULL ;
		}
    }
    
    string gettop() { // 回傳最後點
		if (s == NULL) {
	    	return "" ; // 無 
	    }
	    
	    Node* top = s ;
	    while(top->next != NULL) {
	    	top = top->next ;
	    }
	    
	    return top->data ;
    }

    void pop() { // 刪除最後
    	if (s == NULL) {
			return ;
		}
		 
		if (s->next == NULL) { // 直接刪除 
        	delete s ;
        	s = NULL ;
        	return ;
    	}

	    Node* top = s ;
    	while (top->next->next != NULL) {
        	top = top->next ;
    	}

    	delete top->next;
    	top->next = NULL; 
    }

    bool isEmpty() { // 判斷是否為空 
    	if (s == NULL) {
    		return true ;
    	}
    	
        return false ;
    }
    
    void delStack() { // 釋放stack 
    	while (s != NULL) {
        	Node* temp = s;
        	s = s->next;
        	delete temp;
    	}
	}
};

bool isExp(string& input) ; // 檢查符號 ()+-*/
bool isBalanced(const string input) ; // 檢查括號平衡 
bool isLegal(const string input) ; // 檢查是否為中序 
void str2list(Node*& inlist, const string input) ; // 字串解析成linked list
void infix2postfix(Node* inlist, Node*& postlist) ; // 將中序轉換為後序 
void printLinkedList(Node* head) ; // 印出串列 
bool isnum(string str) ; // 判斷字串是否是數字 
void inputList(Node*& list, string input) ; // 將str存入list中 
void dellist(Node*& list) ; // 釋放list 

int main(void) {
    int command = 0 ;

	do {
		string infixS ;
		cout << endl << "* Arithmetic Expression Evaluator *" ;
		cout << endl << "* 0. QUIT                         *" ;
		cout << endl << "* 1. Infix2postfix Transformation *" ;
		cout << endl << "***********************************" ;
		cout << endl << "Input a choice(0, 1): " ;
		cin >> command ; // get a command

		cin.ignore(MAX_LEN, '\n') ; // clear the input buffer
		
		switch (command) {
			case 0: break ; // 結束程式碼 
			case 1: cout << endl << "Input an infix expression: " ;
				getline(cin, infixS) ; // 讀入運算式
				 
				if (isExp(infixS) && isBalanced(infixS) && isLegal(infixS)) { // 檢查運算式是否合法  
					cout << "It is a legitimate infix expression." << endl ; 
					
					Node* inlist = NULL ;
					str2list(inlist, infixS) ; // parse a string into a linked list

					Node* postlist = NULL ;
					infix2postfix(inlist, postlist) ; // transform infixS into postfixS
					
					printLinkedList(postlist) ; // 印出 
					
					// 釋放
					dellist(inlist) ;
					dellist(postlist) ;
				} // end if

				break ;
			default: cout << endl << "Command does not exist!" << endl ;
		} // end switch
	} while (command != 0) ; // 'O': stop the program

    system("pause"); // Pause the display
    return 0;
}

bool isExp(string& input) {
	// 移除運算式中空白
	string s ;
	for(int i=0; i<input.size(); i++) {
		if (input[i] != ' ') {
			s = s + input[i] ;
		} 
	}
	
	input = s ; // 無空白的運算式

	// ()+-*/ 
	for(int i=0; i<input.size(); i++) {
		if ((input[i] != '(') && (input[i] != ')') && (input[i] != '+') 
		 && (input[i] != '-') && (input[i] != '*') && (input[i] != '/')) { // 是否符號 
			if (input[i] < '0' || input[i] > '9') { // 是否數字 
				cout << "Error 1: " << input[i] << " is not a legitimate character." << endl ;
				return false ;
			} 
		} 
	}
	
	return true ;
}

bool isBalanced(const string input) {
    Stack l;

	for(int i=0; i<input.size(); i++) {
		if ((input[i] == '(')) {
			l.push("(");
		} 
		if ((input[i] == ')')) {
            if (l.isEmpty()) { // )多 
                cout << "Error 2: there is one extra close parenthesis." << endl;
                l.delStack() ; // 堆疊釋放
                return false;
			}
			
			l.pop() ; 
		} 
	}
	
    if (!l.isEmpty()) { // (多 
        cout << "Error 2: there is one extra open parenthesis." << endl;
        l.delStack() ; // 堆疊釋放  
        return false;
    }

	l.delStack() ; // 堆疊釋放  
    return true;
}

bool isLegal(const string input) {
	// 正常符號需為數字-1 
	int number = 0 ; // 數字 operand
	int symbol = 0 ; // 符號 operator
	
	for(int i=0; i<input.size(); i++) {
		if (input[i] >= '0' && input[i] <= '9') {
			number++ ;
			while(input[i+1] >= '0' && input[i+1] <= '9') {
				i++ ;
			}
		}
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			if (input[i+1] == ')') {
				cout << "Error 3: it is not infix in the parentheses." << endl ; // 括弧內部不正確 
				return false ;
			}
			else {
				symbol++ ;
			}
		}
		if (input[i] == '(') {
			if ((input[i+1] < '0' || input[i+1] > '9') && input[i+1] != '(') {
				cout << "Error 3: it is not infix in the parentheses." << endl ; // 括弧內部不正確 
				return false ;
			} 
		}
	}
	
	if (symbol >= number) {
		cout << "Error 3: there is one extra operator." << endl ;
		return false ;
	} 
	if (symbol < number-1) {
		cout << "Error 3: there is one extra operand." << endl ;
		return false ;
	}
		
	return true ;
}

void str2list(Node*& inlist, const string input) {
	for(int i=0; i<input.size(); i++) {
		string n ;

		if (input[i] >= '0' && input[i] <= '9') {
			n.push_back(input[i]) ;
			while(input[i+1] >= '0' && input[i+1] <= '9') {
				i++ ;
				n = n + input[i] ;
			}
		} // 數字組合成字串 
		
		else {
			n.push_back(input[i]) ; // +-*/()
		} 
		
		inputList(inlist, n) ; // 將字串存入list 
	}
}

void infix2postfix(Node* inlist, Node*& postlist) {
    Stack instack;

	// 放入堆疊
	while (inlist != NULL) {
		if (isnum(inlist->data) == true) { // 數字直接放入串鍊 
			inputList(postlist, inlist->data) ;		
		} 
		
		else { // 非數字放入堆疊中
			if (instack.isEmpty() || inlist->data == "(" || (instack.gettop() == "(" && inlist->data != ")")) {
				instack.push(inlist->data); // 直接放入堆疊中 
			}
			else {
				if (inlist->data == ")") { // 移入串鍊 
					while (instack.gettop() != "(") { // 輸出堆疊直到( 
						inputList(postlist, instack.gettop()) ;
						instack.pop() ;
					}
					
					instack.pop() ; // 移除堆疊( 
				} 
				
				else if ((inlist->data == "*" ) || (inlist->data == "/" )){
					while (!instack.isEmpty() && instack.gettop() != "(" && (instack.gettop() == "*" || instack.gettop() == "/")) { // top移入串鍊
						inputList(postlist, instack.gettop()) ;
						instack.pop() ;
					}
					
					instack.push(inlist->data); // 放入堆疊
				}
				
				else if (inlist->data == "+" || inlist->data == "-" ) { // top移入串鍊
					while (!instack.isEmpty() && instack.gettop() != "(") {
						inputList(postlist, instack.gettop()) ;
						instack.pop() ;
					}
					
					instack.push(inlist->data) ;
				}
			} 
		}
		
		inlist = inlist->next ;
	}
                
	//剩餘輸出
	while (!instack.isEmpty()) {
		inputList(postlist, instack.gettop()) ;						
		instack.pop() ;
	}	
	
	instack.delStack() ; // 堆疊釋放 
}

bool isnum(string str) {
	int len = str.size() ;
	
	for(int i = 0; i < len; i++) {
		if (!isdigit(str[i])) { // 是否是數字 
			return false ;
		}
	}
	
	return true ;
} // isnum

void inputList(Node*& list, string input) {
	if (list == NULL) {
		list = new Node ;
		list->data = input ;
		list->next = NULL ;
	}
	
	else { // list != NULL
		Node* head = list ;
		while(head->next != NULL) {
			head = head->next ;
		}
		
		head->next = new Node ;
		head = head->next ;
		head->data = input ;
		head->next = NULL ;
	}
} // inputList

// 印出
void printLinkedList(Node* head) {
    Node* current = head ;
    
    cout << "Postfix expression: " ;
    
    while (current != NULL) {
        cout << current->data ;
        current = current->next ;
        
        if (current != NULL) {
        	cout << ", " ;
        }
    }

    cout << endl ;
} // printLinkedList 

void dellist(Node*& list) { // 釋放list
    while (list != NULL) {
        Node* temp = list;
        list = list->next;
        delete temp;
    }
}


