// 11127251 林柏安

#include <string>	// string class
#include <cstdlib>	// system, atoi
#include <iostream> // endl
#include <new>		// new

#define MAX_LEN 255	// maximun string length


using namespace std; // standard naming space


template<class T>		// type template for data value in stack node
class expLIST {
	typedef struct qN{
		T value;
		struct qN *next;
	} listNode;
	
	listNode *head, *tail;
	
public:
	// constructor with initialization
	expLIST(): head(NULL), tail(NULL){
		
	} // end expLIST initializer
	
	// decide whether list is empty
	bool isEmpty() const {
		return head == NULL;
	}
	
	// append one value into list
	void ins(const T inValue ) {
		try {
			listNode* newNode = new listNode;
			newNode->value = inValue;
			newNode->next = NULL;
			if ( head == NULL ) {
				head = newNode;
				tail = newNode;
			}
			else {
				tail->next = newNode;
				tail->next = newNode;
				tail = tail->next;
			}
			
		}
		
		catch( std:: bad_alloc& ba ) {
			std:: cerr << endl << "bad_alloc on stack caught " <<ba.what() << endl;
		}
	}
	
	// get the head of list without removal
	void getHead(T& outValue ) {
		outValue = head->value;
		
	}
	
	// remove the head of list
	void del() {
		listNode* temp = head;
		
		head = head->next;
		delete temp;
		
	}
	
	// get the head of stack and remove it
	void del(T& outValue ) {
		listNode* temp = head;
		
		head = head->next;
		outValue = temp->value;
		delete temp;
		
	}
	
	
	// clear up the entire list
	void clearUp() {
		listNode* current = head;
		while ( current ) {
			listNode* temp = current;
			current = current->next;
			delete temp;
		}
		
		head = NULL;
		tail = NULL;
	}
	
	
	// destructor
	~expLIST() {
		clearUp();
	}
	
};

template<class T>		// type template for data value in stack node
class expSTACK {
	typedef struct sN {		// structure of each element in stack
		T value;
		struct sN *next;	// next element
	} stackNode;
	
	stackNode *topPtr;		// only one data member
public:
	
	// constructor with initialization
	expSTACK(): topPtr(NULL){
		
	}
	
	// decide whether stack is empty
	bool isEmpty() const {
		return topPtr == NULL;
	}
	
	// add one element into stack
	void push( const T inValue ) {
		try {
			if ( isEmpty() ) {
				topPtr = new stackNode;
				topPtr->value = inValue;
				topPtr->next = NULL;
			}
			else {
				stackNode* temp = new stackNode;
				temp->value = inValue;
				temp->next = topPtr;
				topPtr = temp;
			}
			
		} // end try
		catch(std::bad_alloc& ba) {
			std::cerr<<endl<<"bad_alloc on stack caught " << ba.what() << endl;
		} // end catch
	}
	
	// get the top of stack without removal
	void getTop(T& outValue) {
		outValue = topPtr->value;
			
	}
	
	// remove the top of stack
	void pop() {
		stackNode* temp = topPtr;
		topPtr = topPtr->next;
		delete temp;
		
	}
	
	// get the top of stack and remove it
	void pop(T& outValue){
		getTop(outValue);
		pop();
		
	}
	
	// print out the postfix;
	void print() {
		stackNode* temp = topPtr;
		cout << "Postfix expression: ";
		while ( temp != NULL ) {
			cout << temp->value;
			temp = temp->next;
			if ( temp != NULL ) cout << ", ";
		}
		
		cout << endl;
	}
	
	
	
	// destructor
	~expSTACK() {
		while ( !isEmpty() ) {
			pop();
		} 
		
	}
	
};


// 判斷string str是否為數字 
bool isNumber( string str ) {
	for ( int i = 0 ; i < str.length() ; i ++ ) {
		if ( str[i] - '0' > 9 || str[i] - '0' < 0 ) {
			return false;
		}
		
	}
	
	return true;
}

// check the validity of each symbol
bool isExp( string& formula ) {
	for ( int i = 0 ; i < formula.length() ; i ++ ) {
		
		// 判斷是否是數字元 
		if ( formula[i] - '0' > 9 || formula[i] - '0' < 0 ) {
			
			// 判斷是否是運算符號 
			if ( formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' ) {
				continue;
			}
			// 判斷是否是括弧 
			else if ( formula[i] == '(' || formula[i] == ')' ) {
				continue;
			}
			
			cout << "Error 1: " << formula[i] << " is not a legitimate character."<< endl;
			return false;
		}
		
	}
	
	return true;
}

// check the validity of balanced parentheses
bool isBalance( const string formula ) {
	int forward = 0, backward = 0;
	for ( int i = 0 ; i < formula.length() ; i ++ ) {
		if ( formula[i] == '(') forward += 1;	// 右括弧數量 
		if ( formula[i] == ')') backward += 1;	// 左括弧數量 
		
		// 左括弧數不會多於右括弧數 
		if ( forward < backward ) {
			cout << "Error 2: there is one extra close parenthesis." << endl;
			return false;
		}
		
	}
	
	// 有多餘的右括弧 
	if ( forward > backward ) {
		cout << "Error 2: there is one extra open parenthesis." << endl;
		return false; 
	}
	
	return true;
}

// check wkether it is a legal expression
bool isLegal( const string formula ) {
	
	// 運算式為空 
	if ( formula == "" ) {
		cout << "Error 3: there is one extra operator." << endl;
		return false;
	}
	
	// 判斷有沒有多餘的運算符號 
	bool check = true;
	for ( int i = 0 ; i < formula.length() ; i ++ ) {
		if ( formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' ) {
			cout << "Error 3: there is one extra operator." << endl;
			return false;
		}
		
		break;
	}
	
	// 判斷是否有多餘的數字或符號 且判斷是否符合中序運算式 
	char last;
	for ( int i = 0 ; i < formula.length() ;  i ++ ) {
		
		// 判斷數字 
		last = formula[i];
		if ( formula[i] - '0' <= 9 && formula[i] - '0' >= 0 ) {
			int j = i + 1;
			for ( ; j < formula.length() ; j ++ ) {
				if ( formula[j] == '(' ) {
					cout << "Error 3: there is one extra operand." << endl;
					return false;
				}
				
				break;
				
			}
			
		}
		
		// 判斷是否符合中序運算式 
		else if ( formula[i] == '(' ) {
			int j = i + 1;
			for ( ; j < formula.length() ; j ++ ) {
				if ( formula[j] == '+' || formula[j] == '-' || formula[j] == '*' || formula[j] == '/' || formula[j] == ')' ) {
					cout << "Error 3: it is not infix in the parentheses." << endl;
					return false;
				}
				
				break;
			}
		}
		
		// 判斷是否有多於運算符號 
		else if ( formula[i] == ')' ) {
			int j = i + 1;
			for ( ; j < formula.length() ; j ++ ) {
				if ( formula[j] - '0' <= 9 && formula[j] - '0' >= 0 ) {
					cout << "Error 3: there is one extra operand." << endl;
					return false;
				}
				
				break;
			}
		} 
		
		// 判斷是否有多於運算符號和是否符合中序運算式 
		else if ( formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' ) {
			int j = i + 1;
			for ( ; j < formula.length() ; j ++ ) {
				if ( formula[j] == '+' || formula[j] == '-' || formula[j] == '*' || formula[j] == '/' ) {
					cout << "Error 3: there is one extra operator." << endl;
					return false;
				}
				else if ( formula[j] == ')' ) {
					cout << "Error 3: it is not infix in the parentheses." << endl;
					return false;
				}
				
				break;
			}
		}
		
	}
	
	// 判斷是否有多於運算符號 
	if ( last == '+' || last == '-' || last == '*' || last == '/' ) {
		cout << "Error 3: there is one extra operator." << endl;
		return false;
	}
	
	return true;
}


// parse a string into a linked list
void str2list( const string& infix, expLIST<string>& myList ) {
	for ( int i = 0 ; i < infix.length() ; i ++ ) {
		string newNode = "";
		
		// 將數字先存入變數 newNode 
		if ( infix[i] - '0' <= 9 && infix[i] - '0' >= 0 ) {
			newNode += infix[i];
			i += 1;
			while ( infix[i] - '0' <= 9 && infix[i] - '0' >= 0 ) {
				if ( infix[i] != ' ' ) newNode += infix[i];
				i++;
			}
			
			i -= 1;
			
		}
		
		// 將運算符號先存入 newNode 
		if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')' ) {
			newNode += infix[i];
		}
		
		// 如果 newNode 不是空的 將 newNode 存入 linked list 
		if ( !newNode.empty() ) {
			myList.ins( newNode );
		}
		
	}
	
	
	
}

// transform infix into postfix
bool infix2postfix( expLIST<string>& myList, expSTACK<string>& myStack ) {
	expSTACK<string> temp;	// 暫存運算符號的 stack
	string current;			// 當前節點的內容 
	
	// 執行直到 linked list 為空 
	while ( !myList.isEmpty() ) {
		myList.del( current );	// 讀出一個 Node 存入 current 
		
		// 如果 current 是數字則存入myStack 
		if ( isNumber( current ) ) {
			myStack.push( current );
		}
		
		// 如果 current 是右括弧 則後續為新的一運算式且優先存入 mystack 
		else if ( current == "(") {
			infix2postfix( myList, myStack );
		}
		
		// 如果 current 是左括弧 則視為當前運算式的結束 
		else if ( current == ")" ) {
			while ( !temp.isEmpty() ) {	// 將temp 中的運算符號存入myStack 
				string node;
				temp.pop( node );
				myStack.push( node );
			}
			
			return true;
		}
		else {		// 運算符號 
			if ( temp.isEmpty() ) { // 如果暫存區為空 將運算符號存入 
				temp.push( current );
			}
			else if ( current == "+" || current == "-" ) { // 如果 current 是加號 or減號 將當前temp存入myStack 後將current存入temp 
				while ( !temp.isEmpty() ) {
					string node;
					temp.pop( node );
					myStack.push( node );
				}
				
				temp.push( current );
			}
			else if ( current == "*" || current == "/" ) {	// 如果 current 是成號 or 除號 取出temp的最上筆資料 如果是"*" or "/"則存入myStack 
				string node;
				temp.getTop( node );
				if ( node == "*" || node == "/" ) {
					myStack.push( node );
					temp.pop();
				}
				
				temp.push( current );	// 運算符號存入 stack temp
			}
			
		}
		
	}
	
	// 將 stack temp 中剩餘的運算符號存入myStack 
	while ( !temp.isEmpty() ) {
		string node;
		temp.pop( node );
		myStack.push( node );
	}
    
	return true;
}


int main () {
	int command = 0;	// user command 
	
	
	do {
		string infixS = "";
		string tempInfixS;
		
		cout << endl << "* Arithmetic Expression Evaluator *";
		cout << endl << "* 0.QUIT                          *";
		cout << endl << "* 1.Infix2postfix Transformation  *";
		cout << endl << "***********************************";
		cout << endl << "Input a choice(0, 1): ";
		cin >> command;					// get a command
		cin.ignore( MAX_LEN, '\n' );	// clear the input buffer
		switch ( command ) {
			case 0:
				break;
			case 1:
				cout << endl << "Input an infix expression: ";
				getline( cin, tempInfixS );
				
				// 將空格刪除 
		        for ( int i = 0 ; i < tempInfixS.length() ; i ++ ) {
		        	if ( tempInfixS[i] != ' ' ) {
		        		infixS += tempInfixS[i];
					}
				}
				 
				if ( isExp(infixS) && 			// check each symbol & remove useless ones
						isBalance(infixS) 		// check the validity of balanced parentheses
						&& isLegal(infixS)){	// check whether it is a legal expression
					
					expLIST<string> myList;
					str2list( infixS, myList);					// parse a string into a linked list

					cout << "It is a legitimate infix expression." << endl;

					expSTACK<string> myStack;
					expSTACK<string> tempStack;
					if ( infix2postfix( myList, tempStack ) ) {		// transform infixS into postfixS
						while ( !tempStack.isEmpty() ) {			// 調整 stack 中的順序 
							string node;
							tempStack.pop( node );
							myStack.push( node );
						}
					
					}
					
					myStack.print();
					
				} // end if
				
			default:
				if ( command != 1 ) cout << "command does not exist!" << endl;
			
			
		} // end switch
	} while ( command != 0 );		// '0': stop the program
	
	system("pause");				// pause the display
	
	return 0;
} // end main

