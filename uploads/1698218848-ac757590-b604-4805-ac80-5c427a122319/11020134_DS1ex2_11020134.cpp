// 11020134 呂宗凱

#include <cstdio> 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // 用到isdigit
#include <iostream>
#include <string>
#include <cstdlib> 

#define MAX_LEN 255

using namespace std;

bool g_correct = true;

typedef struct Token{
	char ope;
	struct Token* next;
};

class Stack {
	public:
		Stack();
		Stack(const Stack& aStack);
		~Stack();
		bool isEmpty();
		void push(Token* newToken);  //  新增 
		void pop();  //  移除 
		void getTop(Token*& stackTop);  //  擷取 
		void pop(Token*& stackTop);  //  擷取後移除
		void clearStack(Stack& postfix);  //  清空Stack 
		void clearTopStack(Stack& postfix);
	
	private:
		struct StackNode {
			Token* item;
			StackNode *next;
		}; 
		StackNode *topPtr;	
};  //  end Stack

Stack::Stack() {
	topPtr = NULL;
}

Stack::Stack(const Stack& aStack) {  //  aStack為已做好的linked list，topPtr是head 
	if (aStack.topPtr == NULL) {
		topPtr = NULL;  //  empty 
	}
	else {
		topPtr = new StackNode;
		topPtr->item = aStack.topPtr->item;
		StackNode *newPtr = topPtr;
		for (StackNode *origPtr = aStack.topPtr->next;
		     origPtr != NULL; origPtr = origPtr->next) {
		     	newPtr->next = new StackNode;
		     	newPtr = newPtr->next;
		     	newPtr->item = origPtr->item;
		}
		newPtr->next = NULL;
			 
	}
}  //  copy constructor

Stack::~Stack(){
	while (!isEmpty()) {
		pop();
	}
}  //  end destructer

bool Stack::isEmpty() {  //  是否為空 
	return topPtr == NULL;
}

void Stack::push(Token* newToken) {  //  新增 
	try{
		StackNode *newNode = new StackNode;
		newNode->item = newToken;
		newNode->next = topPtr;
		topPtr = newNode;
	}  //  end try
	
	catch(bad_alloc ba){
		std::cerr << endl << "bad_alloc on stack caught:" << ba.what() << endl;
	}
}

void Stack::pop() {  //  移除 
	if (!isEmpty()) {
		StackNode *temp = topPtr;
		topPtr = topPtr->next;
		temp->next = NULL;
		delete temp;
	}
}   //  end pop

void Stack::getTop(Token*& stackTop) {  //  擷取 
	if (!isEmpty()) {
		stackTop = topPtr->item; 
	}
}  //  end getTop

void Stack::pop(Token*& stackTop) {  //  擷取後移除 
	if (!isEmpty()) {
		stackTop = topPtr->item;
		StackNode *temp = topPtr;
		topPtr = topPtr->next;
		temp->next = NULL;
		delete temp; 
	}
}  //  end pop

void Stack::clearTopStack(Stack &postfix) {  //  適當印出 
	bool first = true;
	
	Token* stackTop;
	postfix.getTop(stackTop);
	postfix.pop(stackTop);
	
	if ( stackTop->ope != ' ' && stackTop->ope != '\n' && stackTop->ope != '(' && stackTop->ope != ')' ) {
		
		printf("%c, ", stackTop->ope);
	}

		delete stackTop; 
}

void Stack::clearStack(Stack &postfix) {  //  全部印出 
	bool first = true;
	
	while(!postfix.isEmpty()) {
		Token* stackTop;
		postfix.pop(stackTop);
		
		if ( stackTop->ope != ' ' && stackTop->ope != '\n' && stackTop->ope != '(' && stackTop->ope != ')' ) {
			if (!first) {
				printf(", ");
			}
			
			printf("%c", stackTop->ope);
			first = false;
		}

		delete stackTop; 
	}
}

void FreeList(Token* &ptr) {
	Token* cur = ptr;
	while ( cur != NULL ) {
	Token* temp = cur;
	cur = cur->next;
	delete temp;
	}
	
	ptr = NULL;
}

void InsertToken( Token* &head, char token ) {
	
	
	Token* insert = new Token;
	insert->next = NULL;
	insert->ope = token;
	
	if ( head == NULL ) {
		head = insert;
		return;
	}
	
	else {
		Token* current = head;
		while ( current->next != NULL ) {
			current = current->next;
		}
		
		current->next = insert;
	}
	
	return;
}

void ScanTheStr(Token* &tokenPtr) {
	char curTok = '0';
	while(scanf( "%c", &curTok) != EOF) {
		InsertToken(tokenPtr, curTok);
		if ( curTok == '\n' ) {
			break;
		}
	}
}

void Error1Det(Token* head) {  //  不符合的token 
	Token* test = head;
	while ( test != NULL ) {
		if ( test->ope != '+' && test->ope != '-' && test->ope != '*' && test->ope != '/' &&
				test->ope != '0' && test->ope != '1' &&  test->ope != '2' && test->ope != '3' &&
				 test->ope != '4' && test->ope != '5' && test->ope != '6' && test->ope != '7' &&
				  test->ope != '8' && test->ope != '9' && test->ope != '\n' && test->ope != ' ' &&
				   test->ope != '(' && test->ope != ')' ) {
			printf("Error 1: %c is not a legitimate character.\n", test->ope);
			g_correct = false;
			break;  	
		}
		else {
			test = test->next;
			if ( test->ope == '\n' ) {
				break;
			}
		}
	}
}

void Error2Det(Token* head) {  //  不對的括號數量 
	Token* test = head;
	int open = 0;
	int close = 0;
	while ( test != NULL ) {
		if (test->ope == '(') {
			open++;
		}
		else if (test->ope == ')' ) {
			close++;
		}
		if ( close > open ) {
			printf("Error 2: there is one extra close parenthesis.\n");
			g_correct = false;
			break;
		}
		if ( test->next == NULL && open > close ) {
			printf("Error 2: there is one extra open parenthesis.\n");
			g_correct = false;
			break;
		}
		
		test = test->next;
	}
}

void Error3Det(Token* head) {  //  運算符號後不能接運算符號  //  後括號後不能接數字   //  數字後不能接前括號 
	Token* test = head;
	int pastToken = 0;  //  +,-,*,/ = 1  // 後括號 = 2  // 前括號 = 3  //  數字 = 4 
	while(test != NULL) {
		
		if ( pastToken == 1 ){
			if ( test->ope == '+' || test->ope == '-' || test->ope == '*' || test->ope == '/' ) {
				printf("Error 3: there is one extra operator.\n");
				g_correct = false;
				break;
			}
		}
		
		else if ( pastToken == 2 ) {
			if (isdigit(test->ope)) {
				printf("Error 3: there is one extra operand.\n");
				g_correct = false;
				break;
			}
		}
		
		else if ( pastToken == 4 ) {
			if ( test->ope == '(' ) {
				printf("Error 3: there is one extra operand.\n");
				g_correct = false;
				break;
			}
		}
		
		else if ( pastToken == 3 ) {
			if (test->ope == ')' ) {
				printf("Error 3: it is not infix in the parentheses.\n");
				g_correct = false;
				break;
			}
		}
		
				//  判斷這是哪一種token 
		
		if ( test->ope == '+' || test->ope == '-' || test->ope == '*' || test->ope == '/' ) {
			pastToken = 1;
		}
		else if ( test->ope == ')' ) {
			pastToken = 2;
		}
		else if ( test->ope == '(' ) {
			pastToken = 3;
		}
		else {
			pastToken = 4;  //  數字!!!ALL SAFE!!! 
		}
		
		test = test->next;
	}	
}

/*  
//  印出linked list，留著或許有用 
void PrintStr(Token* head) {
	Token* test = head;
	while ( test != NULL ) {
		printf("%c", test->ope);
		test = test->next;
		break;
	}
}
*/ 

void Infix2Postfix(Token* exp) {
	printf("Postfix expression: ");
	
	int level = 0;  //  */等級一優先  //  +-等級2次要 
	int openPar = 0;
	bool time_divide = false;
	Token* curPtr = exp;
	Stack postfix;
	
	while ( curPtr != NULL ) {
		if ( curPtr->ope == '0' || curPtr->ope == '1' || curPtr->ope == '2' || curPtr->ope == '3' || 
			curPtr->ope == '4' || curPtr->ope == '5' || curPtr->ope == '6' || 
			curPtr->ope == '7' || curPtr->ope == '8' || curPtr->ope == '9' ) {
				
				//  因為我不是儲存int而是儲存char，所以要多加條件才可以輸出多位數 
				
				if ( curPtr->next->ope == '0' || curPtr->next->ope == '1' || curPtr->next->ope == '2' || curPtr->next->ope == '3' || 
						curPtr->next->ope == '4' || curPtr->next->ope == '5' || curPtr->next->ope == '6' || 
						curPtr->next->ope == '7' || curPtr->next->ope == '8' || curPtr->next->ope == '9' ) {
					printf("%c", curPtr->ope);
				}
				else {
					printf("%c, ", curPtr->ope);
				}

				
		}  //  正常輸出數字 
		
		else if ( curPtr->ope == ')' && openPar > 0 ) {  //  遇到後括號
			postfix.clearStack(postfix);
			openPar--;
		}
		
		else if ( (curPtr->ope == '+' || curPtr->ope == '-') && time_divide == true ) {  //  遇到+-符號，且前面有*/符號 
			postfix.clearStack(postfix);
			
			time_divide = false;
			postfix.push(curPtr);
			if ( curPtr->ope == '(' ) {
				openPar = true;
			}
			else if ( curPtr->ope == '*' || curPtr->ope == '/' ) {
				time_divide = true;
				level = 1;
			}
			else if ( curPtr->ope == '+' || curPtr->ope == '-' ) {
				time_divide = false;
				level = 2;
			}
		}
		
		else if ( (curPtr->ope == '+' || curPtr->ope == '-') && level == 2 ) {  //  +-符號，從左到右計算
			postfix.clearTopStack(postfix);
			
			time_divide = false;
			postfix.push(curPtr);
			if ( curPtr->ope == '(' ) {
				openPar = true;
			}
			else if ( curPtr->ope == '*' || curPtr->ope == '/' ) {
				time_divide = true;
				level = 1;
			}
			else if ( curPtr->ope == '+' || curPtr->ope == '-' ) {
				time_divide = false;
				level = 2;
			}
		} 
		
		else if ( (curPtr->ope == '*' || curPtr->ope == '/') && level == 1 ) {  //  */符號，從左到右計算 
			postfix.clearTopStack(postfix);
			
			time_divide = false;
			postfix.push(curPtr);
			if ( curPtr->ope == '(' ) {
				openPar = true;
			}
			else if ( curPtr->ope == '*' || curPtr->ope == '/' ) {
				time_divide = true;
				level = 1;
			}
			else if ( curPtr->ope == '+' || curPtr->ope == '-' ) {
				time_divide = false;
				level = 2;
			}
		}
		 
		else {  //  無事發生，放入堆疊 
			postfix.push(curPtr);
			if ( curPtr->ope == '(' ) {
				openPar = true;
			}
			else if ( curPtr->ope == '*' || curPtr->ope == '/' ) {
				time_divide = true;
				level = 1;
			}
			else if ( curPtr->ope == '+' || curPtr->ope == '-' ) {
				time_divide = false;
				level = 2;
			}
		}
		
		curPtr = curPtr->next;
		if ( curPtr == NULL ) {  //  算式結束了，清空堆疊 
			postfix.clearStack(postfix);
		}
	}
	
	printf("\n");
}

int main() {
	Token *tokenPtr = NULL;
	int command = -9999;
	while( command != 0) {
		g_correct = true;
		printf("\n* Arithmetic Expression Evaluator *");
		printf("\n* 0. QUIT                         *");
		printf("\n* 1. Infix2postfix Transformation *");
		printf("\n***********************************");
		printf("\nInput a choice(0, 1): ");
		
		scanf("%d", &command);
		cin.ignore(MAX_LEN, '\n');
		if (command == 1) {
			FreeList(tokenPtr);
			printf("\nInput an infix expression: ");
			ScanTheStr(tokenPtr);
			Error1Det(tokenPtr);
			Error2Det(tokenPtr);
			Error3Det(tokenPtr);
			if ( g_correct ) {  //  如果g_correct為false就不用跑中序轉後序了 
				printf("It is a legitimate infix expression.\n");
				Infix2Postfix(tokenPtr);
			}
		}
		else if (command == 0) {
			break;
		}
		else {
			printf("\nCommand does not exist!\n");
		}
	}
	
	FreeList(tokenPtr);
	system("pause");
	return 0;
} 
