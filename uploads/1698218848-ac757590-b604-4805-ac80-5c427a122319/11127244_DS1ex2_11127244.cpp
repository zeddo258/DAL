//資訊二乙 11127244 黃婕菱
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cassert>
#include <iostream>
#include <list> 
#include <cstring>
#include <string>
#include <new>

#define MAX_LEN 255

using namespace std;

struct Node {
	string data;
    Node* next;
    
    Node(){
    	next = NULL;
	}
};
	
class Stack {
public:

    bool isEmpty() {
    	if ( head != NULL )
    		return false;
    	return true;
	}

    void push(string& str) {  // 加入 
    	if ( head == NULL ) {
    		head = new Node;
    		head -> next = NULL; 
			head -> data = str; 
		
		}
		else {
		    Node* tail = new Node;

			tail -> next = head;
			head = tail;
			head -> data = str;
		} 
    }

    void pop(string& str) { // 移除 
		Node* temp = head;
		str = temp -> data;
		head = head -> next;
		delete(temp);
    }

    string ttop() { //第一個 
		string re;
		re = head -> data;
		return re;
    }
	
	void clear(){
		head = NULL ;
	}
	
private:
    Node* head;
    string strrrr;


};

class two {
public:
	
	two() : head(NULL), f(NULL) {}
	
	void add( string str) { //list後面增加東西 
    	Node* tail = new Node;
        tail->data = str;
        tail->next = NULL;

        if (head == NULL) {
            head = tail;
            f = tail;
        } else {
            f->next = tail;
            f = tail;
        }
	}

	void Print( ) { // 輸出
		Node* temp = head; 
		while ( temp != NULL ) {
			if ( temp -> next == NULL )
				cout << temp -> data;
			else 
				cout << temp -> data << ", ";
			temp = temp -> next;
		}
		cout << endl;
	}
	
	~two(){
		while (head != NULL) {
            Node* p = head;
            head = head->next;
            delete p;
        }
	}


private:
    Node* head;
    Node* f;
    string strrrr;

};

class Exp {

public:

	bool isOperator(char c) { // 加減乘除 
    	if( c == '+' || c == '-' || c == '*' || c == '/' )
    		return true;
    	return false;
    	
	}
	
	int order( string str ) {   // 先*/後+- 
    	int p = 0; 

		if ( str == "+" || str == "-" ) 
			p = 1;
	 	else if ( str == "*" || str == "/" ) 
			p = 2;

		return p;
	} 
	
	bool isExp(string &str){ // +-*/() 
		int x = 0;
		int space = 0; // 算空格 
		while ( x < str.size()){
			if ( !isdigit(str[x]) && !isOperator(str[x]) && str[x] != '(' && str[x] != ')' && str[x] != ' '){
				cout << "Error 1:" << str[x] << "is not a legitimate character." << endl;
				return false;
			}
			if ( str[x] == ' ')
				space++;
			x++;  
		}	
		
		if ( space == str.size() ) { // 全空 
			cout << "\nError 3: there is one extra operator.";
			return false;
		} 
		return true;
	}
	
	bool isBalanced(string str){ // 括號是否成對 
		int x = 0;
		int y;
		int i = 0, j = 0;
		while ( x < str.size()){
			if( str[x] == '(' ) 
				i++; 
			if( str[x] == ')' )
				i--;
			
			x++;
		}
		if( i == 0 ) 
			return true;
		else if ( i > 0 ){
			cout << "Error 2: there is one extra open parenthesis." << endl;
			return false;
		}
		else if ( i < 0 ){
			cout << "Error 2: there is one extra close parenthesis." << endl;
			return false;
		}
	}     

	bool isLegal(string str){ // 是否合理 
		int x = 0;
		int y = str.size();
		
		if( isOperator( str[0] ) || isOperator( str[y-1] )) { // 最後一個 or第一個為加減乘除 
			cout << "Error 3: there is one extra operator." << endl;
			return false;
		}
		while( x < str.size() ){
			if( isOperator( str[x] ) ){
				if( str[x+1] == ' '){
					x++;
					continue;
				}
				if( isOperator( str[x+1]) ) {
					cout << "Error 3: there is one extra operator." << endl;
					return false;
				}
				if( str[x+1] == ')') {
					cout << "Error 3: it is not infix in the parentheses." << endl;
					return false;
				}
			}	
			if ( isdigit(str[x]) ){
				if( str[x+1] == '(') {
					cout << "Error 3: there is one extra operand." << endl; // 5(
					return false;
				}
			}
			if ( str[x] == ')'){
				if( isdigit(str[x+1]) || str[x+1] == '(') {
					cout << "Error 3: there is one extra operand." << endl; // )5 or )(
					return false;
				}
			}		
			x++;
		}
		return true;
	}

};

void task2(string str){
	Exp ex; //class1
	Stack stack; //class2
	two l;
	string str2;
	Node *h = NULL;
	Node *t = NULL;
	
	if ( ex.isExp(str) && ex.isBalanced(str) && ex.isLegal(str)){ // 如果式子合理	         
		cout << "It is a legitimate infix expression.\n";
    	for ( int i = 0 ; i < str.size() ; i++ ) { 
			if ( str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')' ) 
				str2 = str2 + str[i];
			else if ( isdigit(str[i]) ) 
				str2 = str2 + str[i];
			else if ( str[i] == ' ' || str[i] == '\n' || str[i] == '\t' )
				continue;
		} //將空格去掉  
		
		int i = 0, j = 0;
		int x = 0, y = 0;
		string output; // 要輸出的 
		string c ; // 要堆疊的 
		while ( i < str2.size() ){
		 	if ( isdigit(str2[i]) ){ // 數字
			 	if ( i < str2.size()-1 ) {
					if ( !isdigit( str2[i+1] ) ){  // 下一個不是數字 
						output = output + str2[i]; // 接完add進去 
						l.add(output); 
						output = "";
					}  
					else if ( isdigit( str2[i+1] ) )  {  // 下一個還是數字  
						output = output + str2[i]; //繼續接上去
					}  // else if
			
				}
				if( i == str2.size() - 1 ){ // 最後一個為數字 
					output = output + str2[i];
					l.add( output );
					output = "";
				}
			}
			else if ( ex.isOperator(str2[i]) ) {  // 如果是+-*/ 
				c = c + str2[i]; // 第一個遇到 
				if( stack.isEmpty() ){
					stack.push(c);
					c = "";
				}
				else if ( !stack.isEmpty() ) {  // 確認堆疊中是否有+-*/ 
					string tt = stack.ttop();
					x = ex.order( tt ); // 原先的    兩者算權重 
					y = ex.order( c ); // 後來的 
						
					if ( x >= y ) {  // 原>後 先拿出來 再把 str[i]放進去stack
						while ( !stack.isEmpty() && stack.ttop() != "(" ) {
							stack.pop(tt);
							l.add(tt); 
							tt = "";
						}  
						stack.push( c );
						c = "";
					} 
					else { // <
						stack.push( c );
						c = "";
					} 
				} 
			}
			else if( str2[i] == '(' ){ // 左括號 
				c = c + str2[i];
				stack.push(c);
				c = "";
			}
			else if( str2[i] == ')'){ // 右括號 
				string re = stack.ttop();
				while(!stack.isEmpty() && re != "(") {
					stack.pop(re);
					l.add(re); //////
					re = stack.ttop();
				}		
			}
			i++;
		} 
		
		while ( !stack.isEmpty() ) {   // if stack 裡還有東西  
			string strr = stack.ttop();
			stack.pop( strr );
			if ( strr != "(" ) {
				l.add(strr);	
			}  // if
		} 

		cout << "Postfix expression: ";
		l.Print();
	}
}

int main() {
	int command = 0;
	Exp e; 
	do
	{
		string infixS;
		cout << endl << "* Arithmetic Expression Evaluator *";
		cout << endl << "* 0. QUIT                         *";
		cout << endl << "* 1. Infix2postfix Transformation *";
		cout << endl << "***********************************";
		cout << endl << "Input a choice(0, 1): ";
		cin >> command;	// get a command
		cin.ignore(MAX_LEN, '\n');	// clear the input buffer
		switch (command)
		{
			case 0: break;
			case 1: cout << endl << "Input an infix expression: ";
				getline (cin, infixS);
//				if ( e.isExp(infixS) && e.isBalanced(infixS) && e.isLegal(infixS))
//				{
				if ( command == 1 ) {
					task2(infixS);
				}
				break;
			default:cout << endl << "Command does not exist!" << endl;
		}
		
	}while (command !=0 );
	system("pause");
	return 0;
}

