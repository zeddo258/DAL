// 中原大學 資訊二乙 11127225 賴枋佑  Data Structure Excerise02

#include <iostream>
using namespace std;

class Input{ // 處理複雜輸入 

public:
	
	// 輸入指令0,1,2，否則回傳-1表示無效指令  
	static int input_command() {  
		
		string input_str;		
		cin >> input_str;

		if (input_str.length() == 1)  // 檢查是否輸入長度為1且為0,1,2
			if (input_str[0] == '0' or input_str[0] == '1' or input_str[0] == '2' )
				return int(input_str[0] - '0');
			
		return -1; 
		
	} // input_command()
		
}; // class Input

class MyStack{ // 堆疊容器 
	
private:
	
	struct Node { // 節點 
		string val;
		Node *next;
	};
	Node *top; // 指向容器最上面 

public:
	
	MyStack () { // 建構子 
		top = NULL;
	}
	
	bool isEmpty() { // 回傳是否為空 
		return top == NULL;
	} 
	
	void push ( string val ) { // 將值推入堆疊容器中 
	
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

	bool get_top ( string &val ) { // 嘗試取得top的值，回傳是否成功 
		
		if ( isEmpty() ) 
			return 0;
		
		val = top -> val;
		return 1;
		
	}
	
	bool pop ( string &val ) { // 嘗試取得top的值並刪除top節點，回傳是否成功 
		
		if ( isEmpty() ) 
			return 0;
		
		val = top -> val;
		
		Node *temp = top;
		top = top -> next;
		delete temp;
		return 1;
		
	}
	
	bool pop () { // 嘗試刪除top節點，回傳是否成功
	
		if ( isEmpty() )
			return 0;
			
		Node *temp = top;
		top = top -> next;
		delete temp;
		return 1;
	}
	
	void init() { // 初始化 = 刪除所有節點 
		while ( pop() );	
	}
	
};

class Mylist{ // 鏈結串列 

	struct Node { // 節點 
		string val;
		Node *next;
	};
		
	Node *head,*tail; // 指向頭與尾 
public:
		
	Mylist () { // 建構子 
		head = NULL;
		tail = NULL;
	}
	
	bool isEmpty() { // 回傳是否為空 
		return head == NULL;
	} 
	
	void push_back ( string val ) { // 將值推入list尾巴 
	
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
	
	bool get_head( string &val ) { // 嘗試取得head的值，回傳是否成功 
		
		if ( isEmpty() ) 
			return 0;
		

		val = head -> val;
		return 1;
		
	}
	
	bool del_head ( string &val ) { // 嘗試取得head的值並刪除top節點，回傳是否成功  
		
		if ( isEmpty() )
			return 0;
		
		Node *temp = head;
		head = head -> next;
		delete temp;
		
		return 1;
	}
	
	bool del_head () { // 嘗試刪除top節點，回傳是否成功  
		
		if ( isEmpty() )
			return 0;
		
		Node *temp = head;
		head = head -> next;
		delete temp;
		
		return 1;
	}


	bool get_node( string &val, int num) { // 嘗試取得指定節點的值，回傳是否成功 
		
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
	
	void init() { // 初始化 = 刪除所有節點 
		while ( del_head() );	
	}
	
};

class Expression { // 儲存與處理運算式的class  
	
private:
	
	int left_Par_count;  // 左括號的數量 
	int right_Par_count; // 右括號的數量 
	MyStack stack; // 堆疊 
	Mylist list;   // 鏈結串列 
	string in_str; // 使用者輸入的運算式字串 
	int error_type; // 錯誤的類型 
	char error_char; // 出錯的字元	

public:
	
	void input_str() { // 讀入一整行運算式 
		while (in_str == "")
			getline(cin,in_str);
	}

	void legal_check(int &char_count ) { // 檢查運算式是否合法 
					
		int Operant_count = 0; // 運算元總數 
		int Operator_count = 0; // 運算子總數 
		
		while (char_count < in_str.length() and in_str[char_count] == ' ') // 跳過前面的空格 
			char_count ++;
				
		while ( char_count < in_str.length() ) {  // 開始遍歷運算式字串 

			if ( in_str[char_count] >= '0' and in_str[char_count] <= '9'  ) { // 切割出數字(運算元) 
				
				do {
					char_count ++;
				}while( ( char_count < in_str.length() ) and ( (in_str[char_count] >= '0' and in_str[char_count] <= '9') or in_str[char_count] == ' ') );
				
				Operant_count ++;
				
			}
			
			else if (in_str[char_count] == '(') { // 遇到左括號，進行遞迴 
				
				left_Par_count ++;
				Operant_count ++;
				char_count ++;
				legal_check(char_count);
	
			}
			
			else if (in_str[char_count] == ')') { // 遇到右括號，檢查目前的括號內是否合法並return 
				
				right_Par_count++;

				if (left_Par_count < right_Par_count) { // 右括號太多 
					error_char = ')';
					error_type = 2;
				}
					
					
				else if ( ( Operant_count  == Operator_count ) and  ( Operator_count == 0 ) ) { // 括號裡沒有運算子也沒有運算元 
					error_char = ' ';
					error_type = 3;	
				} 
				else if (Operant_count - 1 > Operator_count) { // 少運算子 
					error_char = '1';
					error_type = 3;
				}
				else if (Operant_count - 1 < Operator_count) { // 少運算元 
					error_char = '+';
					error_type = 3;
				}
				
				char_count ++;
				return ;
				
			}
			
			else if (in_str[char_count] == '+' or in_str[char_count] == '-' or
					 in_str[char_count] == '*' or in_str[char_count] == '/' ) { // 切割出運算子 
				Operator_count ++ ;	 	
				char_count ++;	 	
			}
			
			else { // 不為合法字元 
				
				error_char = in_str[char_count];
				error_type = 1;
				
			} 
			
			if (error_type != 0) // 如果已經有錯直接停止遞迴 
				return;
			
			while (char_count < in_str.length() and in_str[char_count] == ' ') // 跳過空格 
				char_count ++;

		
		} // while
		

		if (left_Par_count  > right_Par_count) { // 左括號太多 
			error_type = 2;
			error_char = '(';
		}

		else if (Operant_count - 1 > Operator_count) { // 運算元太多 
			error_char = '1';
			error_type = 3;
		}
		
		else if (Operant_count - 1 < Operator_count) { // 運算子太多 
			error_char = '+';
			error_type = 3;
		}
			
		return;
		
	}
	
	bool print_if_legal () { // 如果合法回傳true，否則回傳false然後輸出對應的說明 
		
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
	
	
	void stack_pushing() { // 使用堆疊將中序轉為後序 
		
		string val = "";
		int char_count = 0;
		
		while (char_count < in_str.length() and in_str[char_count] == ' ') // 跳過前面的空格 
			char_count ++;
			
		while (char_count < in_str.length() ) { // 開始遍歷運算式字串 
			
			val = ""; // 初始化val 

			if (in_str[char_count] >= '0' and in_str[char_count] <= '9') { // 切割出數字(運算元) 
				
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
	
			else if ( in_str[char_count] == '(' ) {  // 遇到左括號，推入stack 
				
				val += in_str[char_count];
				stack.push(val);
				char_count++;
				
			}
				

			else if ( in_str[char_count] == ')' ) { // 遇到右話號，拿出括號內所有運算子 
			
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
					  in_str[char_count] == '*' or in_str[char_count] == '/') { // 遇到運算子，根據運算子等級決定是否要拿出stack內的舊運算子，然後推入新運算子 
				
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
			
			while (char_count < in_str.length() and in_str[char_count] == ' ') // 跳過空格 
				char_count ++;
			
		}
		
		while (	stack.pop(val) ) // 把堆疊剩下的東西都拿出來存到list 
			list.push_back(val);
		
	} // stack_pushing()
	
	void print_postfix() { // 輸出後序運算式 
		
		string val;
		cout << "Postfix expression:";
		
		while ( list.get_head(val) ) {
			cout  << " " << val << ",";
			list.del_head();
		}
		cout <<char(8)<< " \n";
		
		
	}
	
	
	int get_operand_level ( string val ) { // 回傳運算子優先等級 
	
		if ( val == "*" or val == "/" )  // 乘與除等級比較高 
			return 2;  
		else if ( val == "+" or val == "-" ) // 加與減等級比較低 
			return 1;
		else // 不為運算子 
			return -1;
			
	}
	
	Expression () { // 建構子 
		
		left_Par_count = 0;
		right_Par_count = 0;
		stack = MyStack();
		list = Mylist();
		in_str = "";
		error_type = 0;
		error_char = ' ';
		
	}
	
	void init () { // 初始化 
		
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
	
	Expression expr_obj = Expression(); // 運算式物件 
	
	int command;	
	
	do{
		
		cout <<"\n*** Arithmetic Expression Evaluator ***";
		cout <<"\n* 0. Quit Program                     *";
		cout <<"\n* 1. Infix Expression Legal Test      *";
		cout <<"\n* 2. Infix to Postfix Transform       *";
		cout <<"\n***************************************"; 
		cout <<"\nPlease input a command(0, 1, 2): ";
		
		command = Input::input_command(); // will get 0, 1, 2 or -1(無效指令)
		expr_obj.init(); // 初始化 
		
		if ( command == 1 ) { // Task 1 
		
			cout << "\nInput an infix expression:";
			expr_obj.input_str(); // 讀入運算式字串  
			int char_count = 0; 
			
			expr_obj.legal_check(char_count); // 從第0號字元開始檢查輸入的運算式是否合法 
			
			if ( expr_obj.print_if_legal()) // 輸出檢查結果的說明 
				cout << "It is a legitimate infix expression.\n";
		
		}

		else if ( command == 2 ) { // Task 2 (But first using Task 1 to check if expression legal)
		
			cout << "\nInput an infix expression:";
			expr_obj.input_str(); // 讀入運算式字串 
			
			int char_count = 0;
			expr_obj.legal_check(char_count); // 從第0號字元開始檢查輸入的運算式是否合法  
			
			if ( expr_obj.print_if_legal() ) { // 如果運算式合法，開始將其轉為後序 
				
				expr_obj.stack_pushing(); // 將字串拆為一個一個節點，並使用stack轉為後序先放進list裡 
				expr_obj.print_postfix(); // 從list裡輸出後序運算式 
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





