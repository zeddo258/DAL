// ����j�� ��T�G�A 11127225 ��D��  Data Structure Excerise02

#include <iostream>
using namespace std;

class Input{ // �B�z������J 

public:
	
	// ��J���O0,1,2�A�_�h�^��-1��ܵL�ī��O  
	static int input_command() {  
		
		string input_str;		
		cin >> input_str;

		if (input_str.length() == 1)  // �ˬd�O�_��J���׬�1�B��0,1,2
			if (input_str[0] == '0' or input_str[0] == '1' or input_str[0] == '2' )
				return int(input_str[0] - '0');
			
		return -1; 
		
	} // input_command()
		
}; // class Input

class MyStack{ // ���|�e�� 
	
private:
	
	struct Node { // �`�I 
		string val;
		Node *next;
	};
	Node *top; // ���V�e���̤W�� 

public:
	
	MyStack () { // �غc�l 
		top = NULL;
	}
	
	bool isEmpty() { // �^�ǬO�_���� 
		return top == NULL;
	} 
	
	void push ( string val ) { // �N�ȱ��J���|�e���� 
	
		try{
			Node *temp = top ; 
				
			top = new Node;   
			top -> val = val;  
			top -> next = temp; 			
		}
		
		catch(bad_alloc& ba) {
			cerr << "\n" << "bad_alloc on stack caught:" << ba.what() << "\n";
		}
				
		
	}

	bool get_top ( string &val ) { // ���ը��otop���ȡA�^�ǬO�_���\ 
		
		if ( isEmpty() ) 
			return 0;
		
		val = top -> val;
		return 1;
		
	}
	
	bool pop ( string &val ) { // ���ը��otop���ȨçR��top�`�I�A�^�ǬO�_���\ 
		
		if ( isEmpty() ) 
			return 0;
		
		val = top -> val;
		
		Node *temp = top;
		top = top -> next;
		delete temp;
		return 1;
		
	}
	
	bool pop () { // ���էR��top�`�I�A�^�ǬO�_���\
	
		if ( isEmpty() )
			return 0;
			
		Node *temp = top;
		top = top -> next;
		delete temp;
		return 1;
	}
	
	void init() { // ��l�� = �R���Ҧ��`�I 
		while ( pop() );	
	}
	
};

class Mylist{ // �쵲��C 

	struct Node { // �`�I 
		string val;
		Node *next;
	};
		
	Node *head,*tail; // ���V�Y�P�� 
public:
		
	Mylist () { // �غc�l 
		head = NULL;
		tail = NULL;
	}
	
	bool isEmpty() { // �^�ǬO�_���� 
		return head == NULL;
	} 
	
	void push_back ( string val ) { // �N�ȱ��Jlist���� 
	
		try{
			
			if ( isEmpty() ) {
			
				head = new Node;
				head -> val = val;
				head -> next = NULL;
				tail = head;
		
			}
			
			else {
				
				tail -> next = new Node;
				tail = tail -> next;
				tail -> val = val;		
				tail -> next = NULL;				
					
			}			
		}
		
		catch(bad_alloc& ba) {
			cerr << "\n" << "bad_alloc on stack caught:" << ba.what() << "\n";
		}
		
	}
	
	bool get_head( string &val ) { // ���ը��ohead���ȡA�^�ǬO�_���\ 
		
		if ( isEmpty() ) 
			return 0;
		

		val = head -> val;
		return 1;
		
	}
	
	bool del_head ( string &val ) { // ���ը��ohead���ȨçR��top�`�I�A�^�ǬO�_���\  
		
		if ( isEmpty() )
			return 0;
		
		Node *temp = head;
		head = head -> next;
		delete temp;
		
		return 1;
	}
	
	bool del_head () { // ���էR��top�`�I�A�^�ǬO�_���\  
		
		if ( isEmpty() )
			return 0;
		
		Node *temp = head;
		head = head -> next;
		delete temp;
		
		return 1;
	}


	bool get_node( string &val, int num) { // ���ը��o���w�`�I���ȡA�^�ǬO�_���\ 
		
		if ( isEmpty() )
			return 0;
			
		Node * temp = head;
		
		while (num) {
		
			temp = temp -> next;
			if (temp == NULL)
				return 0;
			num --;

		}
		
		val = temp -> val;
		return 1;
		
	}
	
	void init() { // ��l�� = �R���Ҧ��`�I 
		while ( del_head() );	
	}
	
};

class Expression { // �x�s�P�B�z�B�⦡��class  
	
private:
	
	int left_Par_count;  // ���A�����ƶq 
	int right_Par_count; // �k�A�����ƶq 
	MyStack stack; // ���| 
	Mylist list;   // �쵲��C 
	string in_str; // �ϥΪ̿�J���B�⦡�r�� 
	int error_type; // ���~������ 
	char error_char; // �X�����r��	

public:
	
	void input_str() { // Ū�J�@���B�⦡ 
		while (in_str == "")
			getline(cin,in_str);
	}

	void legal_check(int &char_count ) { // �ˬd�B�⦡�O�_�X�k 
					
		int Operant_count = 0; // �B�⤸�`�� 
		int Operator_count = 0; // �B��l�`�� 
		
		while (char_count < in_str.length() and in_str[char_count] == ' ') // ���L�e�����Ů� 
			char_count ++;
				
		while ( char_count < in_str.length() ) {  // �}�l�M���B�⦡�r�� 

			if ( in_str[char_count] >= '0' and in_str[char_count] <= '9'  ) { // ���ΥX�Ʀr(�B�⤸) 
				
				do {
					char_count ++;
				}while( ( char_count < in_str.length() ) and ( (in_str[char_count] >= '0' and in_str[char_count] <= '9') or in_str[char_count] == ' ') );
				
				Operant_count ++;
				
			}
			
			else if (in_str[char_count] == '(') { // �J�쥪�A���A�i�滼�j 
				
				left_Par_count ++;
				Operant_count ++;
				char_count ++;
				legal_check(char_count);
	
			}
			
			else if (in_str[char_count] == ')') { // �J��k�A���A�ˬd�ثe���A�����O�_�X�k��return 
				
				right_Par_count++;

				if (left_Par_count < right_Par_count) { // �k�A���Ӧh 
					error_char = ')';
					error_type = 2;
				}
					
					
				else if ( ( Operant_count  == Operator_count ) and  ( Operator_count == 0 ) ) { // �A���̨S���B��l�]�S���B�⤸ 
					error_char = ' ';
					error_type = 3;	
				} 
				else if (Operant_count - 1 > Operator_count) { // �ֹB��l 
					error_char = '1';
					error_type = 3;
				}
				else if (Operant_count - 1 < Operator_count) { // �ֹB�⤸ 
					error_char = '+';
					error_type = 3;
				}
				
				char_count ++;
				return ;
				
			}
			
			else if (in_str[char_count] == '+' or in_str[char_count] == '-' or
					 in_str[char_count] == '*' or in_str[char_count] == '/' ) { // ���ΥX�B��l 
				Operator_count ++ ;	 	
				char_count ++;	 	
			}
			
			else { // �����X�k�r�� 
				
				error_char = in_str[char_count];
				error_type = 1;
				
			} 
			
			if (error_type != 0) // �p�G�w�g������������j 
				return;
			
			while (char_count < in_str.length() and in_str[char_count] == ' ') // ���L�Ů� 
				char_count ++;

		
		} // while
		

		if (left_Par_count  > right_Par_count) { // ���A���Ӧh 
			error_type = 2;
			error_char = '(';
		}

		else if (Operant_count - 1 > Operator_count) { // �B�⤸�Ӧh 
			error_char = '1';
			error_type = 3;
		}
		
		else if (Operant_count - 1 < Operator_count) { // �B��l�Ӧh 
			error_char = '+';
			error_type = 3;
		}
			
		return;
		
	}
	
	bool print_if_legal () { // �p�G�X�k�^��true�A�_�h�^��false�M���X���������� 
		
		if (error_type == 0) 
			return 1;
		
		else if (error_type == 1) {
			cout << "Error 1: " << error_char  << " is not a legitimate character.\n";
			return 0;
		}
		else if (error_type == 2) {
			
			if (error_char == '(')
				cout << "Error 2: there is one extra open parenthesis.\n";
			else if (error_char == ')')
				cout << "Error 2: there is one extra close parenthesis.\n";
			return 0;
		}
		else if (error_type == 3) {
			
			if (error_char == '1')
				cout << "Error 3: there is one extra operand.\n";
			else if (error_char == '+')
				cout << "Error 3: there is one extra operator.\n";
			else
				cout << "Error 3: it is not infix in the parentheses.\n";
			return 0;
			
		}
	}
	
	
	void stack_pushing() { // �ϥΰ��|�N�����ର��� 
		
		string val = "";
		int char_count = 0;
		
		while (char_count < in_str.length() and in_str[char_count] == ' ') // ���L�e�����Ů� 
			char_count ++;
			
		while (char_count < in_str.length() ) { // �}�l�M���B�⦡�r�� 
			
			val = ""; // ��l��val 

			if (in_str[char_count] >= '0' and in_str[char_count] <= '9') { // ���ΥX�Ʀr(�B�⤸) 
				
				while ( in_str[char_count] >= '0' and in_str[char_count] <= '9') {
					
					val += in_str[char_count];
					char_count++;	
					
					while (in_str[char_count] == ' ')
						char_count++;			
					
					if( char_count > in_str.length() ) 
						break;
				}	
				
				list.push_back(val);			
					
			}
	
			else if ( in_str[char_count] == '(' ) {  // �J�쥪�A���A���Jstack 
				
				val += in_str[char_count];
				stack.push(val);
				char_count++;
				
			}
				

			else if ( in_str[char_count] == ')' ) { // �J��k�ܸ��A���X�A�����Ҧ��B��l 
			
				val += in_str[char_count];
	
				string top_val = "";
				int top_type = 0;
				
				stack.get_top(top_val);
				
				while ( top_val != "(" ) {
					list.push_back(top_val);	
					stack.pop() ;
					stack.get_top(top_val);
				}	
				stack.pop() ;
			
				char_count++;
				
			}
						
			else if ( in_str[char_count] == '+' or in_str[char_count] == '-' or
					  in_str[char_count] == '*' or in_str[char_count] == '/') { // �J��B��l�A�ھڹB��l���ŨM�w�O�_�n���Xstack�����¹B��l�A�M����J�s�B��l 
				
				val += in_str[char_count];
		
				string top_val = "";
				stack.get_top(top_val);
			
				while ( get_operand_level(top_val) >= get_operand_level(val) ) {

					list.push_back(top_val);	
					stack.pop() ;
					if ( not stack.get_top(top_val)  )
						break;
						
				}	
				
				stack.push(val);				
				char_count++;
			}
			
			while (char_count < in_str.length() and in_str[char_count] == ' ') // ���L�Ů� 
				char_count ++;
			
		}
		
		while (	stack.pop(val) ) // ����|�ѤU���F�賣���X�Ӧs��list 
			list.push_back(val);
		
	} // stack_pushing()
	
	void print_postfix() { // ��X��ǹB�⦡ 
		
		string val;
		cout << "Postfix expression:";
		
		while ( list.get_head(val) ) {
			cout  << " " << val << ",";
			list.del_head();
		}
		cout <<char(8)<< " \n";
		
		
	}
	
	
	int get_operand_level ( string val ) { // �^�ǹB��l�u������ 
	
		if ( val == "*" or val == "/" )  // ���P�����Ť���� 
			return 2;  
		else if ( val == "+" or val == "-" ) // �[�P��Ť���C 
			return 1;
		else // �����B��l 
			return -1;
			
	}
	
	Expression () { // �غc�l 
		
		left_Par_count = 0;
		right_Par_count = 0;
		stack = MyStack();
		list = Mylist();
		in_str = "";
		error_type = 0;
		error_char = ' ';
		
	}
	
	void init () { // ��l�� 
		
		left_Par_count = 0;
		right_Par_count = 0;
		stack.init();
		list.init();
		in_str = "";
		error_type = 0;
		error_char = ' ';
		
	}
};

int main() {
	
	Expression expr_obj = Expression(); // �B�⦡���� 
	
	int command;	
	
	do{
		
		cout <<"\n*** Arithmetic Expression Evaluator ***";
		cout <<"\n* 0. Quit Program                     *";
		cout <<"\n* 1. Infix Expression Legal Test      *";
		cout <<"\n* 2. Infix to Postfix Transform       *";
		cout <<"\n***************************************"; 
		cout <<"\nPlease input a command(0, 1, 2): ";
		
		command = Input::input_command(); // will get 0, 1, 2 or -1(�L�ī��O)
		expr_obj.init(); // ��l�� 
		
		if ( command == 1 ) { // Task 1 
		
			cout << "\nInput an infix expression:";
			expr_obj.input_str(); // Ū�J�B�⦡�r��  
			int char_count = 0; 
			
			expr_obj.legal_check(char_count); // �q��0���r���}�l�ˬd��J���B�⦡�O�_�X�k 
			
			if ( expr_obj.print_if_legal()) // ��X�ˬd���G������ 
				cout << "It is a legitimate infix expression.\n";
		
		}

		else if ( command == 2 ) { // Task 2 (But first using Task 1 to check if expression legal)
		
			cout << "\nInput an infix expression:";
			expr_obj.input_str(); // Ū�J�B�⦡�r�� 
			
			int char_count = 0;
			expr_obj.legal_check(char_count); // �q��0���r���}�l�ˬd��J���B�⦡�O�_�X�k  
			
			if ( expr_obj.print_if_legal() ) { // �p�G�B�⦡�X�k�A�}�l�N���ର��� 
				
				expr_obj.stack_pushing(); // �N�r���@�Ӥ@�Ӹ`�I�A�èϥ�stack�ର��ǥ���ilist�� 
				expr_obj.print_postfix(); // �qlist�̿�X��ǹB�⦡ 
			}
			
		}
			
		else if ( command == 0 )  // 0 means stop the program
			break;
		else  
			cout << "\nThere is no such command!\n";
			
	} while(true);
	
	cout << "\n";
	system("pause");

} // main() 





