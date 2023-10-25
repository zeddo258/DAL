//11127258, ²�\�[ 
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

    Stack() { // �]�m���|���� 
        s = NULL ;
    }

    void push(string input) { // �s�W
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
    
    string gettop() { // �^�ǳ̫��I
		if (s == NULL) {
	    	return "" ; // �L 
	    }
	    
	    Node* top = s ;
	    while(top->next != NULL) {
	    	top = top->next ;
	    }
	    
	    return top->data ;
    }

    void pop() { // �R���̫�
    	if (s == NULL) {
			return ;
		}
		 
		if (s->next == NULL) { // �����R�� 
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

    bool isEmpty() { // �P�_�O�_���� 
    	if (s == NULL) {
    		return true ;
    	}
    	
        return false ;
    }
    
    void delStack() { // ����stack 
    	while (s != NULL) {
        	Node* temp = s;
        	s = s->next;
        	delete temp;
    	}
	}
};

bool isExp(string& input) ; // �ˬd�Ÿ� ()+-*/
bool isBalanced(const string input) ; // �ˬd�A������ 
bool isLegal(const string input) ; // �ˬd�O�_������ 
void str2list(Node*& inlist, const string input) ; // �r��ѪR��linked list
void infix2postfix(Node* inlist, Node*& postlist) ; // �N�����ഫ����� 
void printLinkedList(Node* head) ; // �L�X��C 
bool isnum(string str) ; // �P�_�r��O�_�O�Ʀr 
void inputList(Node*& list, string input) ; // �Nstr�s�Jlist�� 
void dellist(Node*& list) ; // ����list 

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
			case 0: break ; // �����{���X 
			case 1: cout << endl << "Input an infix expression: " ;
				getline(cin, infixS) ; // Ū�J�B�⦡
				 
				if (isExp(infixS) && isBalanced(infixS) && isLegal(infixS)) { // �ˬd�B�⦡�O�_�X�k  
					cout << "It is a legitimate infix expression." << endl ; 
					
					Node* inlist = NULL ;
					str2list(inlist, infixS) ; // parse a string into a linked list

					Node* postlist = NULL ;
					infix2postfix(inlist, postlist) ; // transform infixS into postfixS
					
					printLinkedList(postlist) ; // �L�X 
					
					// ����
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
	// �����B�⦡���ť�
	string s ;
	for(int i=0; i<input.size(); i++) {
		if (input[i] != ' ') {
			s = s + input[i] ;
		} 
	}
	
	input = s ; // �L�ťժ��B�⦡

	// ()+-*/ 
	for(int i=0; i<input.size(); i++) {
		if ((input[i] != '(') && (input[i] != ')') && (input[i] != '+') 
		 && (input[i] != '-') && (input[i] != '*') && (input[i] != '/')) { // �O�_�Ÿ� 
			if (input[i] < '0' || input[i] > '9') { // �O�_�Ʀr 
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
            if (l.isEmpty()) { // )�h 
                cout << "Error 2: there is one extra close parenthesis." << endl;
                l.delStack() ; // ���|����
                return false;
			}
			
			l.pop() ; 
		} 
	}
	
    if (!l.isEmpty()) { // (�h 
        cout << "Error 2: there is one extra open parenthesis." << endl;
        l.delStack() ; // ���|����  
        return false;
    }

	l.delStack() ; // ���|����  
    return true;
}

bool isLegal(const string input) {
	// ���`�Ÿ��ݬ��Ʀr-1 
	int number = 0 ; // �Ʀr operand
	int symbol = 0 ; // �Ÿ� operator
	
	for(int i=0; i<input.size(); i++) {
		if (input[i] >= '0' && input[i] <= '9') {
			number++ ;
			while(input[i+1] >= '0' && input[i+1] <= '9') {
				i++ ;
			}
		}
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			if (input[i+1] == ')') {
				cout << "Error 3: it is not infix in the parentheses." << endl ; // �A�����������T 
				return false ;
			}
			else {
				symbol++ ;
			}
		}
		if (input[i] == '(') {
			if ((input[i+1] < '0' || input[i+1] > '9') && input[i+1] != '(') {
				cout << "Error 3: it is not infix in the parentheses." << endl ; // �A�����������T 
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
		} // �Ʀr�զX���r�� 
		
		else {
			n.push_back(input[i]) ; // +-*/()
		} 
		
		inputList(inlist, n) ; // �N�r��s�Jlist 
	}
}

void infix2postfix(Node* inlist, Node*& postlist) {
    Stack instack;

	// ��J���|
	while (inlist != NULL) {
		if (isnum(inlist->data) == true) { // �Ʀr������J���� 
			inputList(postlist, inlist->data) ;		
		} 
		
		else { // �D�Ʀr��J���|��
			if (instack.isEmpty() || inlist->data == "(" || (instack.gettop() == "(" && inlist->data != ")")) {
				instack.push(inlist->data); // ������J���|�� 
			}
			else {
				if (inlist->data == ")") { // ���J���� 
					while (instack.gettop() != "(") { // ��X���|����( 
						inputList(postlist, instack.gettop()) ;
						instack.pop() ;
					}
					
					instack.pop() ; // �������|( 
				} 
				
				else if ((inlist->data == "*" ) || (inlist->data == "/" )){
					while (!instack.isEmpty() && instack.gettop() != "(" && (instack.gettop() == "*" || instack.gettop() == "/")) { // top���J����
						inputList(postlist, instack.gettop()) ;
						instack.pop() ;
					}
					
					instack.push(inlist->data); // ��J���|
				}
				
				else if (inlist->data == "+" || inlist->data == "-" ) { // top���J����
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
                
	//�Ѿl��X
	while (!instack.isEmpty()) {
		inputList(postlist, instack.gettop()) ;						
		instack.pop() ;
	}	
	
	instack.delStack() ; // ���|���� 
}

bool isnum(string str) {
	int len = str.size() ;
	
	for(int i = 0; i < len; i++) {
		if (!isdigit(str[i])) { // �O�_�O�Ʀr 
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

// �L�X
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

void dellist(Node*& list) { // ����list
    while (list != NULL) {
        Node* temp = list;
        list = list->next;
        delete temp;
    }
}


