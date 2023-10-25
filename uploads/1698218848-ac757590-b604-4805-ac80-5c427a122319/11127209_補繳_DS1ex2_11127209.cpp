// 11127209	���w�m

#include <iostream> 
#include <string>

using namespace std;

struct Node { // �B�zStack 
  char data;
  Node* next;
  Node(char d) : data(d), next(NULL) {} // �غc�l 
}; // struct


struct Node2 { // �B�zlinklist 
  string data2;
  Node2* next;
  Node2(string d) : data2(d), next(NULL) {} // �غc�l  
}; // struct

class Stack {
private:
  Node* top;

public:
  Stack() : top(NULL) {} // �غc�l

  bool isEmpty() {  // �T�{�O�_�O�Ű��| 
    return top == NULL;
  } // bool

  void push( char value ) { //�s�W�@��char 
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
  } // void

  void pop() { // �����@�� 
    if (isEmpty()) {
      return;
    } // if
    
    Node* temp = top;
    top = top->next;
    delete temp;
  } // void

  void displayStack() {  // �i�ܾ�Ӱ��| 
    if ( isEmpty() ) {
    return;
    } // if
      
    Node* temp = top;
    while ( temp != NULL ) {
      cout << temp->data << " ";
      temp = temp->next;
    } // while
      
      
    cout << endl;
  } // void
    
  char getTop() { // ���o�̤W�����@�ӼƭȦ������� 
    if ( isEmpty() ) {
      return '0' ;
	} // if
	
	return top->data ;
  } // char
    
}; // class


int getPrecedence( char op ) { // �P�_�Ÿ����u�� 
  if (op == '+' || op == '-') {
    return 1;
  } // if 
  
  else if (op == '*' || op == '/') {
    return 2;
  } // else if
  
  return 0; 
} // int


string infixToPostfix( string infix, Stack stack ) { // �������� 
  string postfix;
    

  for ( int i = 0; i < infix.length(); ++i ) {
    if ( infix[i] == ' ' ) { // ��Ů�	
	} // if
    	
    else if ( isdigit(infix[i]) ) {  // �Ʀr�N�����[���� 
      while ( i < infix.length() && isdigit(infix[i]) ) { // �קK����ƥH�W�ɭP�P�_���~ 
        postfix += infix[i];
        i++;
      } // while
      
      postfix += ' ';  
      i--;  
      
    } // else if
	
	else if ( infix[i] == '(' ) {
      stack.push(infix[i]);
    } // else if
	
	else if ( infix[i] == ')' ) {
      while ( !stack.isEmpty() && stack.getTop() != '(' ) {
        postfix += stack.getTop();
        postfix += ' ';
        stack.pop();
      } // while
      
      
      stack.pop(); // �������A�� 
      
    } // else if
	
	else { // �Y���Ÿ�
      while ( !stack.isEmpty() && getPrecedence(stack.getTop()) >= getPrecedence(infix[i]) && stack.getTop() != '(' ) {
        postfix += stack.getTop();
        postfix += ' ';
        stack.pop();
      } // while
      
      
      stack.push(infix[i]);
    } // else
    
  } // for

    
  while ( !stack.isEmpty() ) { // �N���|���Ѿl���Ÿ��u�X 
    postfix += stack.getTop();
    postfix += ' ';
    stack.pop();
  } // while

  return postfix;
} // string



bool isValid( string s ) { //�P�_�O�_�X�k 
  int leftCount = 0;
  int rightCount = 0;
  char pre = ' '; // �e�@��ƭ� 
  bool isOperandExpected = true; // �ΨӧP�_�Ÿ�����m�O�_�X�z 
  
  
  for ( int a = 0 ; a < s.size() ; a++ ) {
    if ( s[a] == '(' ) {
      leftCount++;
      isOperandExpected = true;
      if ( isdigit(pre) ) {  
      	cout << "Error 3: there is one extra operand." << endl;
        return false ;
	  } // if
	} // if
	
	else if ( s[a] == ')' ) {
	  rightCount++;
	  if ( rightCount > leftCount ) {
	    cout << "Error 2: there is one extra close parenthesis." << endl ;
	    return false;
	  } // if
	  
	  if ( pre == '(' ) { // �A�����S�F�� 
	    cout << "Error 3: it is not infix in the parentheses." << endl;
        return false ;
	  } // if
	  
	  isOperandExpected = false;
	} // else if
	
	
	else if ( s[a] == '+' || s[a] == '-' || s[a] == '*' || s[a] == '/' ) {
      if ( isOperandExpected || a == s.size() - 1 || s[a + 1] == ')' || s[a + 1] == '+' || s[a + 1] == '-' || s[a + 1] == '*' || s[a + 1] == '/' ) {
      	// �p�GisOperandExpected�Otrue�A�N��O�}�Y�A���A����@���Ÿ���@��A�N�|�X�{error 
        cout << "Error 3: there is one extra operator." << endl;
        return false;
      } // if
      
      isOperandExpected = true;
      
    } // else if
	  
	else if ( isdigit(s[a]) ) {
	  if ( pre == ')' ) {
	  	cout << "Error 3: there is one extra operand." << endl;
	  	return false ;
	  } // if
	  
      while ( a < s.size() && isdigit(s[a]) ) { // �קK����ƥH�W�ɭP�P�_���~ 
        a++;
      } // while
      
      a--;
      isOperandExpected = false;
    } // else if
	
	else { // �D�X�z�Ÿ� 
	  if ( s[a] != ' ' ) {
	  	cout << "Error 1: " << s[a] << " is not a legitimate character." << endl;
        return false;
	  } // if
    } // else
	
	
	
	
	
    if ( s[a] != ' ' ) {
      pre = s[a];
    } // if
  
    
  } // for
  
  if ( leftCount > rightCount ) {
  	cout << "Error 2: there is one extra open parenthesis." << endl ;
	return false;
  } // if
  
  
  
  return true ;
  
} // bool


void addToList( Node2* &list, string data ) { // �s�W�`�I 
  Node2* curr = list;
  Node2* newNode = new Node2(data);
  if ( curr == NULL ) { // �p�G�쵲��C���šA�h�N�s�`�I�]�m���쵲��C���}�l 
    list = newNode;  
    return;
  } // if

  while ( curr->next != NULL ) {
    curr = curr->next;
  } // while

  curr->next = newNode;
  
} // void

Node2* postfixToList( string postfix ) { // �N����x�s�i�쵲��C�� 
  Node2* list = NULL ;
  string m;
  for ( int i = 0 ; i < postfix.length() ; i++ ) { // �J��Ů�N�x�s�@���A�]�����Ǧ��b�C�ӳ�줤�[�J�Ů�
  	if ( postfix[i] != ' ' ) {
  	  m += postfix[i] ;
	} // if
	
    else {
      addToList( list, m );
      m = "";
	} // else
    
  } // for
  
  return list ;
  
  
} // Node2*


int main() {
  
  char command = ' ';
  string str = "\0" ;
  Stack stack ;
  
  while ( command != '0' ) {
  	cout << endl << "* Arithmetic Expression Evaluator *";
  	cout << endl << "* 0. QUIT                         *";
  	cout << endl << "* 1. Infix2postfix Transformation *";
  	cout << endl << "***********************************";
  	
  	cout << endl << "Input a choice(0, 1):" ;
  	cin >> command ;
  	
  	cin.ignore(); // �M����J�w�İϡA�T�O�S���L�Ħr�žɭP��J�o�Ϳ��~ 
  	
  	if ( command == '0' ) {
  	  return 0;
	} // if
	
	else if ( command == '1' ) {
	  
	  cout << endl << "Input an infix expression: " ;
	  getline( cin, str );
	  
	  
	  if ( isValid( str ) ) {
	  	string postfix;
	  	cout << "It is a legitimate infix expression." << endl ;
	  	postfix = infixToPostfix( str, stack );
	  	Node2* postfixlist = postfixToList( postfix ) ;
	  	Node2* current = postfixlist ;
	  	cout << "Postfix expression:" ;
	  	while ( current != NULL ) { // �L�X��� 
	  	  cout << " " <<  current->data2  ;
	  	  current = current->next ;
	  	  
	  	  if ( current != NULL ) {
	  	    cout << "," ;
		  } // if
		  
		} // while
		
		cout << endl ;
		
		current = postfixlist ; // delete�`�I 
		Node2* temp;
		while ( current != NULL ) {
		  temp = current;
		  current = current->next;
		  delete temp;
		} // while 
		
	  	
	  } // if
	  
	} // else if
	
	else {
	  cout << endl << "Command does not exist!" << endl ;
	} // else 
	
  } // while
  	
  	
  
  	
} // main





