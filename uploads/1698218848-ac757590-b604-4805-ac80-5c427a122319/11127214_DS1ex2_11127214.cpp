// 11127214	�����_ 

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

int priority(char ch ){ //�P�_�u�� 
	if( ch == '+' || ch == '-' )
		return 1;
	else if( ch == '*' || ch == '/' )
		return 2;
	return 0;
} // priority

struct Node{ // �쵲�C��`�I 
	string dot;
	Node * next;
	Node(const string& value){
		dot = value;
		next = NULL;
	} 
	
}; // Node

class LinkedList{ // �쵲�m�����O 
	private :
		Node * head;
		Node * tail;

	public :
		LinkedList(){
			head = NULL;
			tail = NULL;
		}
	void ANew(const string& value){ // �s�W�`�I 
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
	void print(){ // �L�`�I 
		Node * current = head;
		while(current){
			cout << current->dot;
			if(current->next){ // �s�b�Τ����� 
				cout << " ";
			} // if
			current = current->next;
		} // while
		
		cout << endl;
	} // print
	
}; // class LinkedList

bool isExp(const string &str){ // �O�_�]�t�D�k�r�� 
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

bool isBalanced(const string &str){ // �ˬd�A�� 
	int balance = 0; //�����A���O�_���� 
	int i = 0;
	char ch;
	while( i < str.length() ){
		ch = str[i];
		if( ch == '(' )
			balance++; //�J�쥪�A��+1 
		else if( ch == ')')
			balance--;  //�J��k�A��-1 
			
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

bool isLegal(const string &str) { // �⦡�O�_�X�k 
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

bool infix2postfix(const string& infix, string& postfix){ // �������� 
	stack<char> operators;
	stringstream ss; // ��stirng��H�i��Ū�g 
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
    				istringstream ss(postfix);// �qstring��H��Ū�� 
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

