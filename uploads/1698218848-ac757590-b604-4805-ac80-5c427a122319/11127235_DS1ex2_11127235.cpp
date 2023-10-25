// 11127235 許倚菁 
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
        Node(string d) : data(d), next(NULL) {} //初始化Node類 
    };

    Node* top;
    Stack() : top(NULL) {} //初始化Stack類

    void push(string data) { // 將新節點添加到頂部 
        Node* newNode = new Node(data);
        if (top == NULL) {
            top = newNode;
        } else {
            newNode->next = top;
            top = newNode;
        }
    }

    string pop() { //回傳頂部節點的值並刪除 
        if (top == NULL) {
            return "";
        }
        string data = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }

    string peek() { //獲取頂部節點的值且不會刪除 
        if (top == NULL) {
            return "";
        }
        return top->data;
    }

    bool isEmpty() { //檢查堆疊是否為空 
        return top == NULL;
    }
};

class Node {
public:
    string data;
    Node* next;

    Node(string d) : data(d), next(NULL) {} //初始化Node類 
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(NULL) {} //初始化LinkedList類 

    void insert(string data) { //將新節點插入到串列尾端 
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

    void display() { //將串列從頭到尾輸出 
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

    void toPostfix() {  //將中序轉換成後序 
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
              postfixStack.pop(); // 將"("掉 
          } else {
              postfix.insert(temp->data) ;
          }
          
          temp = temp->next;
      }
      
      
      while (!postfixStack.isEmpty()) { //將剩下的運算元儲存到要輸出的串列 
        postfix.insert(postfixStack.pop());
      }
      postfix.display();
      
    }



    ~LinkedList() { //執行完畢後釋放所有動態內存 
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

void infixToProfix(string input) {  //將輸入的字串用串列儲存再調用 'list.toPostfix()'完成目標 
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

bool isNumberOrSymbol (string input) { //判斷輸入字串是否有不合法字元 
	for(int i = 0; i < input.length(); i++ ) {
		char c = input[i];
		if ( !std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' ) {
			cout << "Error 1: " << c << " is not a legitimate character." << endl;
			return false ;
		}
	}
	return true;
}

bool isBalance (string input) {  //判斷輸入字串中的括號是否成對 
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

bool isLegal (string input) { //判斷輸入字串是否符合中序運算式格式 
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
		cin.ignore(MAX_LEN, '\n') ; //忽略輸入緩衝區最大'MAX_LEN'個字符或直到遇到換行符 
		switch (command) //根據command的值選擇要執行哪個case 
		{ case 0 :break;
		  case 1 :cout << endl << "Input an infix expression:";
		        	getline(cin, input); //讀取包含空格在內的所有字元直到換行符 
		        	input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end()); //清除讀入字串中的空格 
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
