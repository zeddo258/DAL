// �Ǹ�:11127232 �m�W:�L౮f 

#include <iostream>
#include <string>
#include <cstdlib>
#include <new>

using namespace std;

template < class T > 				// �ϥ�template�ҪO�A�Ψӫ��w���A 

class expLIST {
	
	private:
		
		typedef struct listNode {	// �Ыئ�C��Ƶ��c 
			
			T value;
			listNode *next;
			
		} listNode;					
		
		listNode *head, *tail;		// �ŧi��C��head�Btail���� 
	
	public:
		
		expLIST () {				// ��l��head��tail���VNULL 
			
			head = NULL;
			tail = NULL;
		
		}
		
		bool isEmpty() const {		// �P�_��C�O�_���� 
			
			if ( head == NULL )
				return true;
			else
				return false;
			
		}
		
		void append( const T invalue ) {	// �s�W��Ʀܦ�C 
			
			if ( head == NULL ) {			
				
				head = new listNode;
				head -> value = invalue;
				head -> next = NULL;
				tail = head;
				
			}
			 
			else {							
								
				tail -> next = new listNode;
				tail = tail -> next;
				tail -> value = invalue;
				tail -> next = NULL;
				
			}
			
		}
		
		void gethead( T & outvalue ) {		// ���o��C��head���� 
			
			outvalue = head -> value;
			
		}
		
		void del( ) {						// �R����C��head������ 
			
			if ( !isEmpty() ) {
				
				listNode *temp = new listNode;
				temp = head;
				head = head -> next;
				temp -> next = NULL;
				delete temp;
				
			}
			
		}
		
		void del( T & outvalue ) {			// �R����C���Y���Шè��o��value 
			
			if ( !isEmpty() ) {
				
				outvalue = head -> value;
				listNode *temp = new listNode;
				temp = head;
				head = head -> next;
				temp -> next = NULL;
				delete temp;
				
			}
			
		}
		
		void clearup() {					// �R��linklist
			
			while ( head != NULL ) {
				
				listNode *temp = new listNode;
				temp = head;
				head = head -> next;
				delete temp;
				
			}
			
			tail = NULL;
			
		}
		
		void copy( expLIST & copy ) {		// �ƻslinklist��t�@���O�� 
			
			for ( listNode * cur = head ; cur != NULL; cur = cur -> next ) {
				
				copy.append( cur -> value );

			}
			
		}
		
		void print() {						// �L�Xlinklist���� 
			
			for ( listNode * cur = head ; cur != NULL; cur = cur -> next ) {
				
				cout << " " << cur -> value;
				
				if ( cur -> next != NULL ) 	
					cout << ",";

			}
			
		}
	
};

template < class T > 						// �ϥ�template�ҪO�A�Ψӫ��w���A 

class expSTACK {
	
	private:
		
		typedef struct stackNode {			// �Ыذ��|��Ƶ��c 
			
			T value;
			stackNode *next;
			
		} stackNode ;
		
		stackNode *topPtr;
	
	public:
		
		expLIST<string> list;				// �Ы�Linklist��Ƶ��c( ���Ǫ�� ) 
		expLIST<string> answer;				// �Ы�Linklist��Ƶ��c( ��Ǫ�� ) 
		
		expSTACK () {						// ��l�ƫ���topPtr���VNULL 
			
			topPtr = NULL;

		}
		
		bool isEmpty() const {				// �P�_���|�O�_���� 
			
			if ( topPtr == NULL )
				return true;
			else
				return false;
			
		}
		
		void push( const T invalue ) {		// �s�W��Ʀܰ��|���c 
			
			if ( topPtr == NULL ) {
				
				topPtr = new stackNode;
				topPtr -> value = invalue;
				topPtr -> next = NULL;
				
			}
			
			else {
				
				stackNode *temp = new stackNode;
				temp -> value = invalue;
				temp -> next = topPtr;
				topPtr = temp;
				temp = NULL;
				delete temp;
				
			}
			
		}
		
		void getTop( T & outvalue ) {		// ���otopPtr���V���� 
			
			outvalue = topPtr -> value;
			
		}
		
		void pop( ) {						// ����topPtr���V����m��� 
			
			if ( !isEmpty() ) {
				
				stackNode *temp = new stackNode;
				temp = topPtr;
				topPtr = topPtr -> next;
				temp -> next = NULL;
				delete temp;
				
			}
			
		}
		
		void pop( T & outvalue ) {			// ����topPtr���V����m��ƨè��o��� 
			
			if ( !isEmpty() ) {
				
				outvalue = topPtr -> value;
				stackNode *temp = new stackNode;
				temp = topPtr;
				topPtr = topPtr -> next;
				temp -> next = NULL;
				delete temp;
				
			}
			
		}
		
		void clearup() {					// �M�����|��� 
			
			while ( topPtr != NULL ) {
				
				stackNode *temp = new stackNode;
				temp = topPtr;
				topPtr = topPtr -> next;
				delete temp;
				
			}
		
		}
		
		void print() {					
			
			cout << endl;
			
			for ( stackNode * cur = topPtr ; cur != NULL; cur = cur -> next ) {
				
				cout << cur -> value;
				
			}
			
			cout << endl;
		}
	
};

void str2list( const string );					// �N���Ǧr��s�J��C��		
void infix2postfix();							// �N�����ର��� 

bool IsExp( string & );							// �ˬd�Ÿ��O�_���T 
bool IsBalence( const string );					// �ˬd�A���O�_��� 
bool IsLegal( const string );					// �ˬd�O�_���X�k���� 
bool math( int & );								// �p���Ǧ�����						

expSTACK<string> data;							// �Ыذ��|���� 

bool IsExp( string & input ) {
	
	string temp = "";
	
	for( int i = 0; i < input.size(); i++ ) {	// �M�ŪŮ� 
		
		if ( input[i] != ' ' )
			temp = temp + input[i];
		
	}
	
	input = temp;
	temp.clear();
	
	for( int i = 0; i < input.size(); i++ ) {
		
		if ( ( input[i] >= '0' && input[i] <= '9' ) || input[i] == '+' || input[i] == '-' ||
			 input[i] == '*' || input[i] == '/' || input[i] == '(' || input[i] == ')' ) {
			   	
			   	//  do nothing
			   	
		}
		
		else {
			
			cout << "Error 1: " << input[i] << " is not a legitimate character.";
			return false;
			
		}
		
	}
	
	return true;
}

bool IsBalence( const string input ) {	//�P�_�A���O�_��� 
	
	int left = 0, right = 0;
	
	for( int i = 0; i < input.size(); i++ ) {
		
		if ( input[i] == '(' ) {
			
			left++;
			
		}
		
		if ( input[i] == ')' ) {
			
			right++;
			
		}
		
		if ( right > left ) {
			
			cout << "Error 2: there is one extra close parenthesis.";
			return false;
			
		}
		
	}
	
	if ( left == right ) {
		return true;
	}
	
	else {
		cout << "Error 2: there is one extra open parenthesis.";
		return false;
	}
	
}

bool IsLegal( const string input ) {
	
	int last = 0;		// �W�@�檺�r������ ( 1:�Ʀr, 2:�B���, 3:���A��, 4:�k�A�� ) 
	
	for( int i = 0; i < input.size(); i++ ) {
		
		if ( input[i] >= '0' && input[i] <= '9' ) {
			
			if ( last == 4 ) {			
				
				cout << "Error 3: there is one extra operand.";
				return false;
				
			}
			
			last = 1;
			
		}
		
		else if ( input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) {
			
			if ( last == 2 || i == 0 || i == input.size() - 1 ) {	 
				
				cout << "Error 3: there is one extra operator.";
				return false;
				
			}
			
			else if ( last == 3 ) {
				
				cout << "Error 3: it is not infix in the parentheses.";
				return false;
					
			}
			
			last = 2;
			
		}
		
		else if ( input[i] == '(' || input[i] == ')' ) {
			
			if ( ( last == 1 || last == 4 ) && input[i] == '(' ) {
				
				for ( int j = i + 1; j < input.size(); j++ ) {
					
					if ( input[j] == '(' )
						continue;
					
					if ( input[j] >= '0' && input[j] <= '9' ) 
						cout << "Error 3: there is one extra operand.";
					else
						cout << "Error 3: it is not infix in the parentheses.";
						
					return false;
					
				}
				
			}
			
			
			if ( ( last == 3 || last == 2 ) && input[i] == ')' ) {
				
				cout << "Error 3: it is not infix in the parentheses.";
				return false;
				
			}
			
			if ( input[i] == '(' ) {
				
				last = 3;
				
			}
			
			else {

				last = 4;
				
			}
				
		}
		
	}
	
	return true;
	
}

void str2list( const string input ) {			// �r���ରlinklist 
	
	for ( int i = 0; i < input.size(); i++ ) {
		
		string temp = "";
		temp = temp + input[i];
		
		if ( input[i] >= '0' && input[i] <= '9' ) {
			i++;
			
			while ( i < input.size() && input[i] >= '0' && input[i] <= '9' ) {
				
				temp = temp + input[i];
				i++;
				
			}
			
			i--;
		}
		
		data.list.append( temp );
	}
	
}

void infix2postfix() {				// �������� 
	
	string value = " ";
	string op = " ";
	
	while ( ! data.list.isEmpty() ) {
		
		data.list.gethead( value );
		
		if ( value[0] >= '0' && value[0] <= '9' ) {
			
			data.answer.append( value );
				
		}	
		
		else if ( value[0] == '(' ) {
			
			data.push( value );
			
		}
		
		else if ( value[0] != ')' ) {
			
			if ( data.isEmpty() ) {
				
				data.push( value );
				data.list.del();
				continue;
				
			}
			
			data.getTop( op );
					
			if ( ( ( op[0] == '*' || op[0] == '/' ) && ( value[0] == '*' || value[0] == '/' ) ) ||
			     ( ( op[0] == '+' || op[0] == '-' ) && ( value[0] == '+' || value[0] == '-' ) ) ) {
				
				data.pop( op );
				data.answer.append( op );
				
			}
				
			else if ( ( op[0] == '*' || op[0] == '/' ) && ( value[0] == '+' || value[0] == '-' ) ) {
					
				data.pop( op );
				data.answer.append( op );
				
				if ( ! data.isEmpty() ) {
					
					data.getTop( op );
				
					if ( op[0] == '+' || op[0] == '-' ) {
						
						data.pop( op );
						data.answer.append( op );	
						
					}

				}
					
			}
			
			data.push( value );
			
		}
		
		else {
			
			data.pop( op );	
			
			while ( op[0] != '(' ) {
				
				data.answer.append( op );
				data.pop( op );
				
			}
				
		}
		
		data.list.del();
	}
	
	while ( ! data.isEmpty() ) {
		
		data.pop( op );
		data.answer.append( op );	
		
	}
	
}

bool math( int & sum ) {					// �p���Ǧ����� 
	
	int element;
	string value ;
	bool num ;
	expSTACK<int> stack;
	expLIST<string> formu ;
	data.answer.copy( formu );
	
	while ( !formu.isEmpty() ) {
		num = false;
		element = 0;
		formu.del( value );
		for ( int i = 0; i < value.size() && value[i] >= '0' && value[i] <= '9' ; i++ ) {
			
			element = element * 10 + value[i] - '0'; 
			num = true;
			
		}
		
		if ( num ) {
			
			stack.push( element );
			
		}
		
		else {
				
			int digit_one, digit_two;
			stack.pop( digit_one );
			stack.pop( digit_two );
			
			if ( value[0] == '+' ) {
				
				sum = digit_two + digit_one;
				
			}
			
			else if ( value[0] == '-' ) {
				
				sum = digit_two - digit_one;
				
			}
			
			else if ( value[0] == '*' ) {
				
				sum = digit_two * digit_one;
				
			}
			
			else if ( value[0] == '/' ) {
				
				if ( digit_one == 0 ) {		// �X�{���Ƭ�0�����~ 
					
					formu.clearup();
					stack.clearup();
					cout << "Error: The divisor is zero!";
					return false;
					
				}
					
				sum = digit_two / digit_one;
				
			}
			
			stack.push( sum );
			
			
		}
		
	}
 
 	formu.clearup();
	stack.clearup();
	return true;
	
}

int main(void) {
	
	int sum = 0;
	string command = "";
	
	do {
		
		string input;
		
		cout << endl << "* Arithmetic Expression Evaluator *";
		cout << endl << "* 0. QUIT                         *";
		cout << endl << "* 1. Infix2postfix Transformation *";
   		cout << endl << "***********************************";
		cout << endl << "Input a choice(0, 1): ";
		
		cin >> command;
		cin.ignore( 255, '\n' );		// �M�ſ�J�Ȧs
		
		if ( command.compare("0") == 0 )
			break;
				
		else if ( command.compare("1") == 0 ) {
			cout << endl << "Input an infix expression: ";
			getline( cin, input );
				
			if ( IsExp( input ) && IsBalence( input ) && IsLegal( input ) ) {
					
				str2list( input );
				infix2postfix();
				
				if ( math( sum ) ) {	// �P�_�O�_�����Ƭ�0�����~ 
					
					cout << "It is a legitimate infix expression.";
					cout << endl << "Postfix expression:";
					data.answer.print(); 
					
				}
				
				data.clearup();
				data.list.clearup();
				data.answer.clearup();

			}

		}
		
		else {
			
			cout << endl << "Command does not exist!";
			
		}
		
		cout << endl;
			
	} while( command.compare("0") != 0 );
	
	system("pause");
	return 0;
	
}
