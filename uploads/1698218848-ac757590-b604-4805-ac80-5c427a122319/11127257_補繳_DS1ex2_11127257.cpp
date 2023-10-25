// 11127257, �J�[�� 
#include <string>
#include <cstdlib>
#include <iostream>
#include "expLISTclass.h"
#include "expSTACK.h"

#define MAX_LEN 255

using namespace std;

expLIST<string> list;
expSTACK<char> stack;

bool isExp (string& input); // �ˬd�B�⦡���O�_�u���X�k�r�� 
bool isBalanced(const string input); // �ˬd�O�_���ʤ֩Φh�X���A��
bool isLegal(const string input); // �ˬd�O�_�ŦX���ǹB�⦡��F�W�h
void str2postfix(string input); // �N�B�⦡�ഫ����C
void printList(expLIST<string> list); // �N���ǹB�⦡�ഫ����ǹB�⦡

int main (void) {
	int command = 0;
	
	do {
		
		string infixS;
	
		cout<<endl<<"* Arithmetic Expression Evaluator *";
		cout<<endl<<"* 0. QUIT                         *";
		cout<<endl<<"* 1. Infix2postfix Transformation *";
		cout<<endl<<"***********************************";
		cout<<endl<<"input a choice(0, 1): ";
		
		cin>>command;
		cin.ignore(MAX_LEN, '\n');
		
		switch (command)
		{
			case 0: break;
			case 1:cout << endl << "Input an infix expression: ";
			
					getline(cin, infixS);
			
					if (isExp(infixS) &&         // �P�_��J���r��O�_���X�k�����ǹB�⦡��F�k 
			    		isBalanced(infixS) &&
			    		isLegal(infixS)) 
					{
						cout << "It is a legitimate infix expression.";
						str2postfix(infixS);
						
						while ( !stack.isEmpty() ) {
							stack.pop();
						} // while
						
						cout << endl << "Postfix expression: ";
			    		printList(list);
			    		list.clearUp();
			    		cout << endl;
					} // if
					
					stack.~expSTACK();
					list.~expLIST();
					break;
					
			default: cout << endl << "Command does not exist!" << endl;
			
		} // switch
		
	} while(command != 0);
	
	return 0;
	
} // main()

bool isExp (string& input) {
	int i = 0, len = 0;
	char c;
	
	len = input.length();
	
	while( i < len ) {    // �M��input�r��
		c = input[i];
		
		if ( !isdigit(c) && c != '+' && c != '-'          // �ˬd�r�ꤤ�O�_���D�k�r�� 
	     	 && c != '*' && c != '/' && c != '('
		 	 && c != ')' && c != ' ' ) {
		 	cout<<"Error 1: "<<c<<"is not a legitimate character."<<endl;
			return false;
		} // if
		 
		 i++;
	} // while()
	
	return true;
} // isExp()

bool isBalanced(const string input) {
	int i = 0, len = 0, left = 0, right = 0;
	char c;
	
	len = input.length();
	
	while( i < len ) {            
		c = input[i];
		
		if ( c == '(' )           
			left++;
		else if ( c == ')' )
			right++;
		
		i++;
	} // while
	
	if (left == right) {      // �Υ��A���P�k�A�����ƶq�P�_�A���O�_���� 
		return true;
	} // if
	
	else if (left > right) {
		cout<<"Error 2: there is one extra open parenthesis."<<endl;
		return false;
	} // else if
	
	else if (right > left) {
		cout<<"Error 2: there is one extra close parenthesis."<<endl;
	    return false;
	} // else if
	
} // isBalanced()

bool isLegal(const string input) {
	int i = 0, j = 0, len = 0;
	char c, next;      
	
	len = input.length();
	
	while (i < len - 1) {  // �M��input�r���˼ƲĤG�Ӧr�� 
		j = i+1;
		c = input[i];
		if (c != ' ') {
			next = input[j];
			
			while ( next == ' ' ) {
				next = input[j++];
			} // while
			
			if ( c == '+' || c == '-' || c == '*' ||    // �Ψ�Ӭ۳s���r���P�_�r��O�_�ŦX���ǹB�⦡�W�h 
		     	 c == '/' ) {
				if (!isdigit(next) && next != '(') {                   // '+', '-', '*', '/',�᭱���౵�Ʀr�M'('�H�~���r�� 
					cout<<"Error 3: there is one extra operator."<<endl;
					return false;
				} // if
				
			} // if
			
			else if ( c == '(' ) {
				if ( !isdigit(next) ) {
					cout<<"Error 3: there is one extra operator."<<endl;
					return false;
				} // if
				
			} // else if
			
			else if ( c == ')') {
				if (isdigit(next)) {    // ')'�᭱���౵�Ʀr 
					cout<<"Error 3: there is one extra operand."<<endl;
					return false;
				} // if
				
			} // else if
			
		} // if
		
		i++;
	} // while
	
	
	c = input[len-1];  // input�r�ꪺ�̫�@�Ӧr������O'+', '-', '*', '/', '(' 
	if (c == '+' || c == '-' || c == '*' || 
	    c == '/' || c == '(' ) {
	    cout<<"Error 3: there is one extra operator."<<endl;
		return false;
	} // if
	else 
		return true;
	

} // isLegal()

void str2postfix(string input) {
	string node, temp;
	char c, pre, out;
	int i = 0, len = 0, n = 0;
	
	len = input.length();
	
	while ( i < len ) {
		c = input[i];
		node = "";
		n = 0;
		
		while ( isdigit(c) || c == ' ' ) {
			if ( isdigit(c) ) {
				node = node + c;
				n++;
			} // if
			
			if ( i <= len - 1 )
				i++;
			c = input[i];
		} // while
		
		if ( n != 0 )
			list.ins(node);
		
		if ( !isdigit(c) && c != ')' ) {
			if ( stack.isEmpty() )
				stack.push(c);
				
			else {
				stack.getTop(pre);
				
				if ( ( pre == '*'  || pre == '/' ) &&
			     	 ( c == '+' || c == '-' || c == '*' || c == '/' ) ) {
			     	do {
			     			temp = pre;	
			     			list.ins(temp);
			     			stack.pop();
			     			if (!stack.isEmpty())
			     				stack.getTop(pre);
			     			else pre = '\0';
			     	} while ( ( c == '+' || c == '-' || c == '*' || c == '/' ) &&
						      ( pre == '+' || pre == '-' || pre == '*' || pre == '/' ) );
					stack.push(c);
			    } // if
				
				else if ( ( pre == '+' || pre == '-' ) &&
			     	 ( c == '+' || c == '-' ) ) {
			     	do {
			     			temp = pre;	
			     			list.ins(temp);
			     			stack.pop();
			     			if (!stack.isEmpty())
			     				stack.getTop(pre);
			     			else pre = '\0';
			     	} while ( ( c == '+' || c == '-' || c == '*' || c == '/' ) &&
						      ( pre == '+' || pre == '-' || pre == '*' || pre == '/' ) );
			    	stack.push(c);
				} // else if
					
				else if ( ( pre == '+' || pre == '-' ) &&
				          ( c == '*' || c == '/' ) )
				    stack.push(c);
				    
				else if ( pre == '(' || c == '(' )
					stack.push(c);
					
			} // else
			
			i++;
		} // if
		
		else if ( c == ')' ) {
			stack.pop(out);
			
			while(out != '(') {
				temp = out;
				list.ins(temp);
				stack.pop(out);
			} // while

			i++;
		} // else if
		
	} // while 
	
	while ( !stack.isEmpty() ) {
		stack.pop(out);
		temp = out;
		list.ins(temp);
	} // while
	
} // str2postfix()

void printList(expLIST<string> list) {
	string out;
	while ( !list.isEmpty() ) {
		list.del(out);
		cout<<out;
		if ( !list.isEmpty() )
			cout<<", ";
	} // while
	
} // printList()

