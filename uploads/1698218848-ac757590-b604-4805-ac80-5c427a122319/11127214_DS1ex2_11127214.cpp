// 11127214	李赫宰 

#include <string>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>


#define MAX_LEN 255 

using namespace std; 

bool isExp(const string &str); 
bool isBalanced(const string &str);  
bool isLegal(const string &str);  
bool infix2postfix(const string& infix, string& postfix); 

int priority(char ch ){ //判斷優先 
	if( ch == '+' || ch == '-' )
		return 1;
	else if( ch == '*' || ch == '/' )
		return 2;
	return 0;
} // priority

struct Node{ // 鏈結列表節點 
	string dot;
	Node * next;
	Node(const string& value){
		dot = value;
		next = NULL;
	} 
	
}; // Node

class LinkedList{ // 鏈結練表類別 
	private :
		Node * head;
		Node * tail;

	public :
		LinkedList(){
			head = NULL;
			tail = NULL;
		}
	void ANew(const string& value){ // 新增節點 
		Node * newNode = new Node(value);
		if(!head){
			head = newNode;
			tail = newNode;
		} // if
		else{
			tail->next = newNode;
			tail = newNode;
		} // else
	} // ANew
	void print(){ // 印節點 
		Node * current = head;
		while(current){
			cout << current->dot;
			if(current->next){ // 存在或不為空 
				cout << " ";
			} // if
			current = current->next;
		} // while
		
		cout << endl;
	} // print
	
}; // class LinkedList

bool isExp(const string &str){ // 是否包含非法字符 
	int i = 0;
	char ch;
	while( i < str.length() ){
		ch = str[i];
		if( ch >= '0'&& ch <= '9'){
		} // if
		else if( ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')' && ch != ' ' ){
			cout << "Error 1: " << ch << " is not a legitimate character." << endl;
			return false;
		} // else if
		
		i++;
	} // while
	return true;
} // bool isExp

bool isBalanced(const string &str){ // 檢查括號 
	int balance = 0; //紀錄括號是否成對 
	int i = 0;
	char ch;
	while( i < str.length() ){
		ch = str[i];
		if( ch == '(' )
			balance++; //遇到左括號+1 
		else if( ch == ')')
			balance--;  //遇到右括號-1 
			
		if( balance < 0 ) {
			cout << "Error 2: there is one extra close parenthesis." << endl;
			return false;
		} // if
		i++;
	} // while
	if( balance == 0 ){
		return true;
    } // if
	else if( balance > 0 ) {
		cout << "Error 2: there is one extra open parenthesis." << endl;
		return false;
	} // else if

} // bool isBalanced

bool isLegal(const string &str) { // 算式是否合法 
	if (!isExp(str) || !isBalanced(str)) {
        return false;
    } // if
    
    stack<char> operators ;
    int i = 0 ;
    char ch ;
    while( i < str.length() ) {
    	ch = str[i];
    	if( ch == '+' || ch == '-' || ch == '*' || ch == '/' ){
    		if( i == 0 || i == str.length() - 1 ){
    			cout << "Error 3: there is one extra operator." << endl ;
    			return false;
			}
			if( str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/'){
				cout << "Error 3: there is one extra operator." << endl ;
    			return false;
			}
		}
		else if( ch == ')'){
			if( str[i+1] == '(' || ( str[i+1] >= '0' && str[i+1] <= '9' ) ){
			   	cout << "Error 3: there is one extra operand." << endl ;
    			return false;
			}
		}
		
        i++;
	}
	return true;
	
} // bool isLegal

bool infix2postfix(const string& infix, string& postfix){ // 中序轉後序 
	stack<char> operators;
	stringstream ss; // 對stirng對象進行讀寫 
	int i = 0;
	char ch;
	while( i < infix.length() ){
		ch = infix[i];
		if( ch >= '0' && ch <= '9' ){
			
			string num;
			while( i < infix.length() && ( infix[i] >= '0' && infix[i] <= '9' ) ){
				num = num + infix[i];
				i++;
			} // while
			
			ss << num << ", ";
		} // if
		else if( ch == '+' || ch == '-' || ch == '*' || ch == '/' ){
			while( !operators.empty() && operators.top() != '(' && priority(operators.top()) >= priority(ch) ){
				ss << operators.top() << ", ";
				operators.pop();
			} // while
			
			operators.push(ch);
			i++;
		} // else if
		else if( ch == '(' ){
			operators.push(ch);
			i++;
		} // else if
		else if( ch == ')' ){
			while( !operators.empty() && operators.top() != '(' ){
				ss << operators.top() << ", ";
				operators.pop();
			} // while
			
			if( operators.empty() || operators.top() != '(' ){
				cout << "Error 2: there is one extra open parenthesis." << endl;
				return false;
			} // if
			
			operators.pop();
			i++;
		} // else if
		else if( ch == ' ' ){
			i++;
		} // else if
		
		
	} // while
	
	while( !operators.empty() ){
		if( operators.top() == '(' ){
			cout << "Error 2: there is one extra open parenthesis." << endl;
			return false;
		}
		
		ss << operators.top() << ", ";
		operators.pop();
	}
	
	postfix = ss.str();
	postfix = postfix.substr( 0, postfix.length()-2 );
	return true;
	
} // bool infix2postfix

int main(void) {
	int command = 0;
	do {
		string input;
		string postfix;
		
		cout << endl << "* Arithmetic Expression Evaluator *";
		cout << endl << "* 0. QUIT                         *";
		cout << endl << "* 1. Infix2postfix Transformation *";
		cout << endl << "***********************************";
		cout << endl << "Input a choice(0, 1):";
		cin >> command;
    	cin.ignore(MAX_LEN,'\n');
    	switch (command){
			case 0: break;
			case 1: cout << endl << "Input an infix expression: ";
    		getline(cin, input); 
    		if( isExp(input) && isBalanced(input) && isLegal(input) ){
    			cout << "It is a legitimate infix expression." << endl;
    			if( infix2postfix(input, postfix ) ){
    				LinkedList last;
    				istringstream ss(postfix);// 從string對象中讀取 
					string temporary;
					while( ss >> temporary ){
						last.ANew(temporary);
					} // while
					
					cout << "Postfix Expression: ";
					last.print();
				} // if
				
			} // if
			 
			break;
		default:cout << endl << "Command does not exist" << endl;

		} // switch
		
	} // do
	
	while(command != 0 );
	
	system("pause");

    return 0; 

} // end main

