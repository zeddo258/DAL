// 11127209	郭安峻

#include <iostream> 
#include <string>

using namespace std;

struct Node { // 處理Stack 
  char data;
  Node* next;
  Node(char d) : data(d), next(NULL) {} // 建構子 
}; // struct


struct Node2 { // 處理linklist 
  string data2;
  Node2* next;
  Node2(string d) : data2(d), next(NULL) {} // 建構子  
}; // struct

class Stack {
private:
  Node* top;

public:
  Stack() : top(NULL) {} // 建構子

  bool isEmpty() {  // 確認是否是空堆疊 
    return top == NULL;
  } // bool

  void push( char value ) { //新增一個char 
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
  } // void

  void pop() { // 移除一個 
    if (isEmpty()) {
      return;
    } // if
    
    Node* temp = top;
    top = top->next;
    delete temp;
  } // void

  void displayStack() {  // 展示整個堆疊 
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
    
  char getTop() { // 取得最上面的一個數值但不移除 
    if ( isEmpty() ) {
      return '0' ;
	} // if
	
	return top->data ;
  } // char
    
}; // class


int getPrecedence( char op ) { // 判斷符號的優先 
  if (op == '+' || op == '-') {
    return 1;
  } // if 
  
  else if (op == '*' || op == '/') {
    return 2;
  } // else if
  
  return 0; 
} // int


string infixToPostfix( string infix, Stack stack ) { // 中序轉後序 
  string postfix;
    

  for ( int i = 0; i < infix.length(); ++i ) {
    if ( infix[i] == ' ' ) { // 抓空格	
	} // if
    	
    else if ( isdigit(infix[i]) ) {  // 數字就直接加到後序 
      while ( i < infix.length() && isdigit(infix[i]) ) { // 避免雙位數以上導致判斷失誤 
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
      
      
      stack.pop(); // 移除左括弧 
      
    } // else if
	
	else { // 若為符號
      while ( !stack.isEmpty() && getPrecedence(stack.getTop()) >= getPrecedence(infix[i]) && stack.getTop() != '(' ) {
        postfix += stack.getTop();
        postfix += ' ';
        stack.pop();
      } // while
      
      
      stack.push(infix[i]);
    } // else
    
  } // for

    
  while ( !stack.isEmpty() ) { // 將堆疊中剩餘的符號彈出 
    postfix += stack.getTop();
    postfix += ' ';
    stack.pop();
  } // while

  return postfix;
} // string



bool isValid( string s ) { //判斷是否合法 
  int leftCount = 0;
  int rightCount = 0;
  char pre = ' '; // 前一位數值 
  bool isOperandExpected = true; // 用來判斷符號的位置是否合理 
  
  
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
	  
	  if ( pre == '(' ) { // 括弧內沒東西 
	    cout << "Error 3: it is not infix in the parentheses." << endl;
        return false ;
	  } // if
	  
	  isOperandExpected = false;
	} // else if
	
	
	else if ( s[a] == '+' || s[a] == '-' || s[a] == '*' || s[a] == '/' ) {
      if ( isOperandExpected || a == s.size() - 1 || s[a + 1] == ')' || s[a + 1] == '+' || s[a + 1] == '-' || s[a + 1] == '*' || s[a + 1] == '/' ) {
      	// 如果isOperandExpected是true，代表是開頭，左括弧後一位跟符號後一位，就會出現error 
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
	  
      while ( a < s.size() && isdigit(s[a]) ) { // 避免雙位數以上導致判斷失誤 
        a++;
      } // while
      
      a--;
      isOperandExpected = false;
    } // else if
	
	else { // 非合理符號 
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


void addToList( Node2* &list, string data ) { // 新增節點 
  Node2* curr = list;
  Node2* newNode = new Node2(data);
  if ( curr == NULL ) { // 如果鏈結串列為空，則將新節點設置為鏈結串列的開始 
    list = newNode;  
    return;
  } // if

  while ( curr->next != NULL ) {
    curr = curr->next;
  } // while

  curr->next = newNode;
  
} // void

Node2* postfixToList( string postfix ) { // 將後序儲存進鏈結串列裡 
  Node2* list = NULL ;
  string m;
  for ( int i = 0 ; i < postfix.length() ; i++ ) { // 遇到空格就儲存一次，因為中序有在每個單位中加入空格
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
  	
  	cin.ignore(); // 清除輸入緩衝區，確保沒有無效字符導致輸入發生錯誤 
  	
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
	  	while ( current != NULL ) { // 印出後序 
	  	  cout << " " <<  current->data2  ;
	  	  current = current->next ;
	  	  
	  	  if ( current != NULL ) {
	  	    cout << "," ;
		  } // if
		  
		} // while
		
		cout << endl ;
		
		current = postfixlist ; // delete節點 
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





