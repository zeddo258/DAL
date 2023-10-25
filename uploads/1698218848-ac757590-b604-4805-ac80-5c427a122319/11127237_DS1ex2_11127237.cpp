// 11127237 林翰

#include<string>
#include<cstdlib>
#include<iostream>
#include<new>

#define MAX_LEN 255

using namespace std;

template<class T>
class expLIST {
    typedef struct qN {
        T value;
        struct qN *next;       
    } listNode;
    listNode *head, *tail;

public:
    expLIST():head(NULL),tail(NULL)
    {}

    bool isEmpty() const {
        return head == NULL;
    }

    void ins(const T inValue) {
        try {
            if (head == NULL) {
                head = new listNode;
                head -> value = inValue;
                head -> next = NULL;
                tail = head;
            }

            else {
                tail -> next = new listNode;
                tail = tail -> next;
                tail -> value = inValue;
                tail -> next = NULL;
            }

        }
        catch(bad_alloc& ba) {
            cerr << endl << "bad_alloc on stack caught" << ba.what() << endl;
        }
    }

    void getHead(T& outValue) {
        if ( head != NULL )
            outValue = head -> value;
    }

    void del() {
        listNode *temp = head;
        head = head -> next;
        delete temp;
        temp = NULL;
    }

    void del(T& outValue) {
        outValue = head -> value;
        del();
    }

    void clearUp() {
        listNode *temp = head;
        while ( !isEmpty()){
            head = head -> next;
            temp -> next = NULL;
            delete temp;
            temp = NULL;
            temp = head;
        }
        tail = NULL;      
    }

    void PrintAnser() {
        listNode *temp = head;  
		cout << "Postfix expression: ";
        while ( temp != NULL ) {
            cout << temp -> value;
            if ( temp != tail )
                cout << ", "; 
            temp = temp -> next;  
        }  
        cout << endl;  
    }

    ~expLIST() {
        clearUp();
    }
};

template<class T>
class expSTACK {
    typedef struct sN {
        T value;
        struct sN *next;
    } stackNode;

    stackNode *topPtr;

public:
    expSTACK():topPtr(NULL)
    { }

    bool isEmpty() const {
        return topPtr == NULL;
    }    

    void push(const T inValue) {
        try {
            if (topPtr == NULL) {
                topPtr = new stackNode;
                topPtr -> value = inValue;
                topPtr -> next = NULL;
            }

            else {
                stackNode *temp = topPtr;
                topPtr = NULL;
                topPtr = new stackNode;
                topPtr -> value = inValue;
                topPtr -> next = temp;
                temp = NULL;
                delete temp;
            }
        }
        catch(bad_alloc& ba) {
            cerr << endl << "bad_alloc on stack caught" << ba.what() << endl; 
        }
    }

    void getTop(T& outValue) {
        if ( topPtr != NULL )
            outValue = topPtr -> value; 
    }

    void pop() {
        if ( topPtr != NULL ) {
            stackNode *temp = topPtr;
            topPtr = topPtr -> next;
            temp -> next = NULL;
            delete temp;
            temp = NULL;
        }
    }

    void pop(T& outValue) {
        if (topPtr != NULL ) {
            outValue = topPtr -> value;
            pop();
        }
    }

    void PrintAnser() {
        stackNode *temp = topPtr;  
		cout << "Postfix expression: ";
        while ( temp != NULL ) {
            cout << temp -> value << ",";
            temp = temp -> next;  
        }  
        cout << endl;  
    }

    ~expSTACK() {
        while (!isEmpty()) {
            pop();
        }
    }
}; 


bool isExp(string&); //Error 1 : 判斷是否為合法字元 
bool isBalanced(const string); // Error 2 : 判斷括號是否成對
bool isLegal(const string); // Error 3 : 判斷是是否多出運算元或運算子，且判斷最後是否為中序
void infix2postfix(const string); // 轉後續

bool isNumber(const char); // 判斷是否為運算元
bool isOperator( const char); // 判斷是否為運算子

int main(void) {
	int command = 0;

	do {
		string infixS;

		cout << endl << "* Arithmetic Expression Evaluator *";
		cout << endl << "* 0. QUIT                         *";
		cout << endl << "* 1. Infix2postfix Transformation *";
		cout << endl << "***********************************";
		cout << endl << "Input a choice(0, 1):";
		cin >> command;
		cin.ignore(MAX_LEN,'\n');
		switch(command) {
			case 0: break;
			case 1: cout << endl << "Input an infix expression:";
					getline(cin,infixS);
					if ( isExp(infixS) && isBalanced(infixS)
						 && isLegal(infixS))
					{
						infix2postfix(infixS);
					}	 
					break;
			default: cout << endl << "Command does not exist" << endl;			
		}
	}while(command != 0);
	return 0;

}

bool isNumber(const char c) {
	return c >= '0' && c <= '9';
} 

bool isOperator( const char c ){
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isExp(string& infixS) {
	bool True; // 判斷是否合法
	for ( int i = 0; i < infixS.size(); ++i) {
		True = false;
		if ( isNumber(infixS[i]) ) {
			True = true;
		}

		else if ( isOperator(infixS[i]) || infixS[i] == '(' || infixS[i] == ')' ) {
			True = true;
		}

		else if ( infixS[i] == ' ' ) {
			infixS.erase(i,1);
			True = true;
		}	

		if (!True) {
			cout << "Error 1: " << infixS[i] << " is not a legitimate character." << endl;
			return false;
		}
	}
	return true;
}

bool isBalanced(const string infixS) {
	expSTACK<char> stack_c; //初始化堆疊類別
	int i = 0; // 字串位置
	while (i < infixS.size()) {
		if ( infixS[i] == '(') {  // 如果為"("，丟入堆疊
			stack_c.push(infixS[i]);
		}
		if ( infixS[i] == ')') {  // 如果為")"，將堆疊內內容刪除
			if ( !stack_c.isEmpty() ) {
				stack_c.pop();
			}

			else {  // 當堆疊為空，代表多出一個")"
				cout << "Error 2: " << "there is one extra close parenthesis." << endl;
				stack_c.~expSTACK();
				return false;
			}
		}
		i++;
	} 

	if (stack_c.isEmpty()) {
		stack_c.~expSTACK();
		return true;
	}

	else { // 當堆疊不為空，代表多一個"("
		cout << "Error 2: " << "there is one extra open parenthesis." << endl;
		stack_c.~expSTACK();
		return false;
	}
}

bool isLegal(const string infixS) {
	int i = 0; // 字串位置
	bool True = true; // 數字是否多出，因為要先判斷括號內，所以用一個bool儲存狀態
	while ( i < infixS.size()) {
		if (isNumber(infixS[i])) { // 為運算元
		    if ( infixS[i + 1] == '(') {
				True = false;  
			}
		}

		else if ( isOperator(infixS[i])) {  // 為運算子

			if ( i == 0 ) {  // 開頭不為運算子
				cout << "Error 3: " << "there is one extra operator." << endl;
				return false;
			}
			else if ( i == infixS.size() - 1 ) {  // 結尾不為運算子
				cout << "Error 3: " << "there is one extra operator." << endl;
				return false;				
			}
			else if ( isOperator(infixS[i + 1]) ) {  // 運算子疊在一起
				cout << "Error 3: " << "there is one extra operator." << endl;
				return false;
			}
		}

		else if ( infixS[i] == '(') {
			if ( isOperator(infixS[i+1]) || infixS[i+1] == ')') {  // 左括號後為運算子或右括號
				cout << "Error 3: " << "it is not infix in the parentheses." << endl;
				return false;
			}
		}

		else if ( infixS[i] == ')' ) {
			if ( isNumber(infixS[i+1]) ) { // 右括號後為數字
				cout << "Error 3: " << "there is one extra operand." << endl;
				return false;
			}
		}

		i++;
	}

	if ( !True ) {  // 前面儲存的狀態
		cout << "Error 3: " << "there is one extra operand." << endl;
		return false;
	}
	else
		return true;
}

void infix2postfix(const string infixS) {
	expSTACK<char> operator_stack;  // 堆疊類別
	expLIST<string>  infix2postfix;  // 串列類別
	int i = 0; // 字串位置

	cout << "It is a legitimate infix expression." << endl;
	while ( i < infixS.size() ) {  // 判斷是否在字串長度範圍內
		if ( infixS[i] == '(') {
			operator_stack.push(infixS[i]);  // 將右括號丟進堆疊
		}
		else if ( isNumber(infixS[i]) ) {
			int temp_i = i;
			int z = 0;
			while ( i < infixS.size() && isNumber(infixS[i]) ) {  // 將字串後為運算元位置記住
				z++;
				i++;
			}
			infix2postfix.ins(infixS.substr(temp_i,z)); // 擷取開頭運算元到剛判斷之運算元接成字串丟入串列
			i--;
		}
		else if ( isOperator(infixS[i]) ) {
			if ( infix2postfix.isEmpty()) {
				operator_stack.push(infixS[i]);	 // 如果堆疊為空，將運算子丟入堆疊			
			}

			else {
				if ( infixS[i] == '+' || infixS[i] == '-' ) {  // 為加減
					char c;
					operator_stack.getTop(c);  // 取得堆疊頂部
					if ( c == '*' || c == '/' ) {  // 碰到優先
						while ( !operator_stack.isEmpty() && c != '(') {  // 將堆疊丟入串列
							if ( isOperator(c) ) {
								operator_stack.pop();
								string str(1,c);
								infix2postfix.ins(str);
							}

							operator_stack.getTop(c);							
						}
						operator_stack.push(infixS[i]);
					}
					else if ( c == '+' || c == '-' ){  // 同級先將堆疊丟入串列
						operator_stack.pop();
						string str(1,c);
						infix2postfix.ins(str);
						operator_stack.push(infixS[i]);						
					}
                    else {
                        operator_stack.push(infixS[i]); // 直接丟入堆疊
                    }
				}

				else if ( infixS[i] == '*' || infixS[i] == '/' ) {  // 為乘除
					char c;
					operator_stack.getTop(c);
                    if ( c == '+' || c =='-' )  // 碰到後
					    operator_stack.push(infixS[i]); // 直接丟入堆疊
                    else if ( c == '*' || c == '/' ) {  // 同級
 						operator_stack.pop();  
						string str(1,c);					
						infix2postfix.ins(str);  // 將堆疊串列  
						operator_stack.push(infixS[i]); // 丟入堆疊                       
                    } 
                    else {
                        operator_stack.push(infixS[i]); // 直接堆疊                
                    }   					
				}
			}
		}
		else if ( infixS[i] == ')') { // 為右括號
			char c;
			operator_stack.pop(c);
			while (c != '(') {  // 左括號前全部丟入串列
				string str(1,c);					
				infix2postfix.ins(str);
				operator_stack.pop(c);	
			}
		}		
		i++;
	}

    // 判斷堆疊內是否為空，如果還有運算子，全都丟入串列
	if ( operator_stack.isEmpty() ) {
		infix2postfix.PrintAnser();	
	}
	else {
		char c;
		while ( !operator_stack.isEmpty() ) {
			operator_stack.pop(c);
			string str(1,c);
			infix2postfix.ins(str);

		}
		infix2postfix.PrintAnser();
	}
}
