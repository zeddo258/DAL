// 11127235 �\�ʵ� 
#include <string>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <algorithm>


#define MAX_LEN 255
 
using namespace std;

class Stack {


public:
	struct Node {
        string data;
        Node* next;
        Node(string d) : data(d), next(NULL) {} //��l��Node�� 
    };

    Node* top;
    Stack() : top(NULL) {} //��l��Stack��

    void push(string data) { // �N�s�`�I�K�[�쳻�� 
        Node* newNode = new Node(data);
        if (top == NULL) {
            top = newNode;
        } else {
            newNode->next = top;
            top = newNode;
        }
    }

    string pop() { //�^�ǳ����`�I���ȨçR�� 
        if (top == NULL) {
            return "";
        }
        string data = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }

    string peek() { //��������`�I���ȥB���|�R�� 
        if (top == NULL) {
            return "";
        }
        return top->data;
    }

    bool isEmpty() { //�ˬd���|�O�_���� 
        return top == NULL;
    }
};

class Node {
public:
    string data;
    Node* next;

    Node(string d) : data(d), next(NULL) {} //��l��Node�� 
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(NULL) {} //��l��LinkedList�� 

    void insert(string data) { //�N�s�`�I���J���C���� 
        Node* newNode = new Node(data);
        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() { //�N��C�q�Y�����X 
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data;
            if (temp->next != NULL) {
                cout << ", ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    void toPostfix() {  //�N�����ഫ����� 
      Stack postfixStack;
      Node* temp = head;
      bool last = false;
      LinkedList postfix;
      while (temp != NULL) {
          if (temp->data == "(") {
              postfixStack.push(temp->data);
          } else if (temp->data == "+" || temp->data == "-") {
              while (!postfixStack.isEmpty() && (postfixStack.peek() == "*" || postfixStack.peek() == "/" || postfixStack.peek() == "+" || postfixStack.peek() == "-")) {
                  postfix.insert(postfixStack.pop()) ;
              }
              postfixStack.push(temp->data);
          } else if (temp->data == "*" || temp->data == "/") {
              while (!postfixStack.isEmpty() && (postfixStack.peek() == "*" || postfixStack.peek() == "/")) {
                  postfix.insert(postfixStack.pop()) ;
              }
              postfixStack.push(temp->data);
          } else if (temp->data == ")") {
              while (!postfixStack.isEmpty() && postfixStack.peek() != "(") {
                  postfix.insert(postfixStack.pop()) ;
              }
              postfixStack.pop(); // �N"("�� 
          } else {
              postfix.insert(temp->data) ;
          }
          
          temp = temp->next;
      }
      
      
      while (!postfixStack.isEmpty()) { //�N�ѤU���B�⤸�x�s��n��X����C 
        postfix.insert(postfixStack.pop());
      }
      postfix.display();
      
    }



    ~LinkedList() { //���槹��������Ҧ��ʺA���s 
        Node* current = head;
        Node* next = NULL;
        while (current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
        head = NULL;
    }
};

void infixToProfix(string input) {  //�N��J���r��Φ�C�x�s�A�ե� 'list.toPostfix()'�����ؼ� 
	LinkedList list;
    string num;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '(' || input[i] == ')') {
            string s(1, input[i]);
            list.insert(s);
        } else {
            num = "";
            while (isdigit(input[i])) {
                num += input[i];
                i = i + 1;
            }
            list.insert(num);
            i = i - 1;
        }
    }

     
    cout << "Postfix expression: ";
    list.toPostfix();

}

bool isNumberOrSymbol (string input) { //�P�_��J�r��O�_�����X�k�r�� 
	for(int i = 0; i < input.length(); i++ ) {
		char c = input[i];
		if ( !std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' ) {
			cout << "Error 1: " << c << " is not a legitimate character." << endl;
			return false ;
		}
	}
	return true;
}

bool isBalance (string input) {  //�P�_��J�r�ꤤ���A���O�_���� 
	int open = 0;
	int close = 0;
	for(int i = 0; i < input.length(); i++ ) {
		char c = input[i];
		if (c == '(') 
			open = open + 1;

		if(c == ')') 
			close = close + 1;
		
	}
	
	if (open == close) {
		return true;
	}
	else if (open > close) {
		cout << "Error 2: there is one extra open parenthesis." << endl ;
		return false; 
	}
	else if (open < close) {
		cout << "Error 2: there is one extra close parenthesis." << endl ;
		return false;
	}
}

bool isLegal (string input) { //�P�_��J�r��O�_�ŦX���ǹB�⦡�榡 
	int countOperator = 0;
	int operand = 0;
	for(int i = 0; i < input.length(); i++ ) {
		char c = input[i];
		if ( c == '(' || c == ')') {
			continue;
		}
		else if ( c == '+' || c == '-' || c == '*' || c == '/' ) {
			countOperator = countOperator + 1;
		}
		else {
			while (std::isdigit(c) ) { 
				i = i + 1; 
				c = input[i]; 
			}
			i = i - 1;
			operand = operand + 1;
		}
	}
	
	int check = operand - countOperator;
	if ( check == 1 ) {
		return true;
    }
	else if ( operand > countOperator ) {
		cout << "Error 3: there is one extra operand." << endl;
		return false;
	} 
	else if ( operand < countOperator ) {
		cout << "Error 3: there is one extra operator." << endl;
		return false;
	} 
	else if ( operand == countOperator) {
		cout << "Error 3: it is not infix in the parentheses." << endl;
		return false;
	} 
	 
}
int main() {
	int command = 0;
	do {
		string input;
		cout << endl << "* Arithmetic Expression Evaluator *";
		cout << endl << "* 0. QUIT                         *";
		cout << endl << "* 1. Infix2postfix Transformation *";
		cout << endl << "***********************************";
		cout << endl << "Input a choice(0, 1):";
		cin >> command;
		cin.ignore(MAX_LEN, '\n') ; //������J�w�İϳ̤j'MAX_LEN'�Ӧr�ũΪ���J�촫��� 
		switch (command) //�ھ�command���ȿ�ܭn�������case 
		{ case 0 :break;
		  case 1 :cout << endl << "Input an infix expression:";
		        	getline(cin, input); //Ū���]�t�Ů�b�����Ҧ��r�����촫��� 
		        	input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end()); //�M��Ū�J�r�ꤤ���Ů� 
		            if (isNumberOrSymbol(input)) {
		           		if (isBalance(input)) {
		           			if (isLegal(input)) {
		           				cout << "It is a legitimate infix expression.\n" ;
		           				infixToProfix(input);  
		           			}
						} 
				    } 
				    break;
		  default: cout << endl << "Command does not exist!" << endl;           
		            
		}
	} while (command != 0);
	system( "pause" ) ;
	return 0 ;
}
