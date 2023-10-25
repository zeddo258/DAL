// 11127251 �L�f�w

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


// �P�_string str�O�_���Ʀr 
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
		
		// �P�_�O�_�O�Ʀr�� 
		if ( formula[i] - '0' > 9 || formula[i] - '0' < 0 ) {
			
			// �P�_�O�_�O�B��Ÿ� 
			if ( formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' ) {
				continue;
			}
			// �P�_�O�_�O�A�� 
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
		if ( formula[i] == '(') forward += 1;	// �k�A���ƶq 
		if ( formula[i] == ')') backward += 1;	// ���A���ƶq 
		
		// ���A���Ƥ��|�h��k�A���� 
		if ( forward < backward ) {
			cout << "Error 2: there is one extra close parenthesis." << endl;
			return false;
		}
		
	}
	
	// ���h�l���k�A�� 
	if ( forward > backward ) {
		cout << "Error 2: there is one extra open parenthesis." << endl;
		return false; 
	}
	
	return true;
}

// check wkether it is a legal expression
bool isLegal( const string formula ) {
	
	// �B�⦡���� 
	if ( formula == "" ) {
		cout << "Error 3: there is one extra operator." << endl;
		return false;
	}
	
	// �P�_���S���h�l���B��Ÿ� 
	bool check = true;
	for ( int i = 0 ; i < formula.length() ; i ++ ) {
		if ( formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' ) {
			cout << "Error 3: there is one extra operator." << endl;
			return false;
		}
		
		break;
	}
	
	// �P�_�O�_���h�l���Ʀr�βŸ� �B�P�_�O�_�ŦX���ǹB�⦡ 
	char last;
	for ( int i = 0 ; i < formula.length() ;  i ++ ) {
		
		// �P�_�Ʀr 
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
		
		// �P�_�O�_�ŦX���ǹB�⦡ 
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
		
		// �P�_�O�_���h��B��Ÿ� 
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
		
		// �P�_�O�_���h��B��Ÿ��M�O�_�ŦX���ǹB�⦡ 
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
	
	// �P�_�O�_���h��B��Ÿ� 
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
		
		// �N�Ʀr���s�J�ܼ� newNode 
		if ( infix[i] - '0' <= 9 && infix[i] - '0' >= 0 ) {
			newNode += infix[i];
			i += 1;
			while ( infix[i] - '0' <= 9 && infix[i] - '0' >= 0 ) {
				if ( infix[i] != ' ' ) newNode += infix[i];
				i++;
			}
			
			i -= 1;
			
		}
		
		// �N�B��Ÿ����s�J newNode 
		if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')' ) {
			newNode += infix[i];
		}
		
		// �p�G newNode ���O�Ū� �N newNode �s�J linked list 
		if ( !newNode.empty() ) {
			myList.ins( newNode );
		}
		
	}
	
	
	
}

// transform infix into postfix
bool infix2postfix( expLIST<string>& myList, expSTACK<string>& myStack ) {
	expSTACK<string> temp;	// �Ȧs�B��Ÿ��� stack
	string current;			// ��e�`�I�����e 
	
	// ���檽�� linked list ���� 
	while ( !myList.isEmpty() ) {
		myList.del( current );	// Ū�X�@�� Node �s�J current 
		
		// �p�G current �O�Ʀr�h�s�JmyStack 
		if ( isNumber( current ) ) {
			myStack.push( current );
		}
		
		// �p�G current �O�k�A�� �h���򬰷s���@�B�⦡�B�u���s�J mystack 
		else if ( current == "(") {
			infix2postfix( myList, myStack );
		}
		
		// �p�G current �O���A�� �h������e�B�⦡������ 
		else if ( current == ")" ) {
			while ( !temp.isEmpty() ) {	// �Ntemp �����B��Ÿ��s�JmyStack 
				string node;
				temp.pop( node );
				myStack.push( node );
			}
			
			return true;
		}
		else {		// �B��Ÿ� 
			if ( temp.isEmpty() ) { // �p�G�Ȧs�Ϭ��� �N�B��Ÿ��s�J 
				temp.push( current );
			}
			else if ( current == "+" || current == "-" ) { // �p�G current �O�[�� or� �N��etemp�s�JmyStack ��Ncurrent�s�Jtemp 
				while ( !temp.isEmpty() ) {
					string node;
					temp.pop( node );
					myStack.push( node );
				}
				
				temp.push( current );
			}
			else if ( current == "*" || current == "/" ) {	// �p�G current �O���� or ���� ���Xtemp���̤W����� �p�G�O"*" or "/"�h�s�JmyStack 
				string node;
				temp.getTop( node );
				if ( node == "*" || node == "/" ) {
					myStack.push( node );
					temp.pop();
				}
				
				temp.push( current );	// �B��Ÿ��s�J stack temp
			}
			
		}
		
	}
	
	// �N stack temp ���Ѿl���B��Ÿ��s�JmyStack 
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
				
				// �N�Ů�R�� 
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
						while ( !tempStack.isEmpty() ) {			// �վ� stack �������� 
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

