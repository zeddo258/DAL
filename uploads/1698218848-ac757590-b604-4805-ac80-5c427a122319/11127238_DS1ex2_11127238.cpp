// 11127238 王詩霈 
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#define MAX_LEN 255
using namespace std;

template <class Type>

class expList {
	
	typedef struct qN {
		Type value;
		struct qN *next;
	} listNode;
	listNode *head, *tail;

public:
	
    expList() : head(NULL), tail(NULL) {}
    
	bool isEmpty(){							// 確認是否為空 
		return head == NULL;
	}
	
    void ins(const Type inValue) {			//append one value into  list
        if ( head == NULL ) {				//裡面無東西 
            head = new listNode;
            head -> next = NULL;
            head -> value = inValue;
            tail = head;
        } else {
            tail -> next = new listNode;	//裡面有東西 
            tail = tail -> next;
            tail -> value = inValue;
            tail -> next = NULL;
        }
    }

	void getHead(Type& outValue){			//get the head of list without removal
		outValue = head -> value;
	}
	
	void del(){								//get the head of list
		listNode * headnext = head;
		head = head -> next;
		delete headnext;		
	}
	
	void del(Type& outValue){				//get the head of stack and remove it
		listNode * headnext = head;
		head = head -> next;
		outValue = headnext -> value;
		delete headnext;
	}

	void Cout() {							//print
		for ( listNode * currr = head; currr != NULL; currr = currr -> next ) {
			if( currr -> next == NULL ){
				cout << currr -> value;
			}
			else{
				cout << currr -> value << ", "; 
			}
		}
	}

	void clearUp(){							//clear up the entire list
		while(!isEmpty()){
			listNode * temp = head;
			head = head -> next;
			delete temp;
		}
	}
	
	~expList(){
		clearUp();
	}
	
};

template <class Type>

class expStack{
	
	typedef struct sN{
		Type value;
		struct sN *next;
	} stackNode;
	stackNode *topPtr;
	
public:
	
	expStack() : topPtr(NULL) {}
	
	bool isEmpty(){
		return topPtr == NULL;
	}

	void push(const Type inValue){			//add one element into stack
        if ( topPtr == NULL ) {							//裡面無東西
            topPtr = new stackNode;						 
            topPtr -> next = NULL;
            topPtr -> value = inValue;
        } 
		else {
            stackNode * staaack = new stackNode;		//裡面有東西 
			staaack -> next = topPtr;
			topPtr = staaack;
			staaack -> value = inValue;
		}
	}
	
	void getTop(Type& outValue){			//get the top of stack without removal
        outValue = topPtr -> value;
	}
	
	void pop(){								//remove the top of stack
        stackNode * staaack = topPtr;  
        topPtr = topPtr -> next;
        delete staaack;
	}
	
	void pop(Type& outValue){				//get the top of stack and remove it
        stackNode * staaack = topPtr;
        topPtr = topPtr -> next;
        outValue = staaack -> value;
        delete staaack;
	}

	~expStack(){
		while(!isEmpty()){
			pop();
		} 
	}
	
};

bool isExp(string & num){					//check the vaildity of each symbl
	int k = 0 ;
	for( int i=0 ; i<num.length() ; i++ ){
		if( num[i] == '(' || num[i] == ')' ){
			k++;
		}
		else if( (num[i] >= '0' && num[i] <= '9') || num[i] == ' ' ){        
			k++;
		}
		else if( num[i] =='+' || num[i] =='-' || num[i] =='*' || num[i] =='/' ){   
			k++;
		}
		else {
			cout << "Error 1: " << num[i] << " is not a legitimate character.";
			return false;
		}
	}
	
	return true;	
}

bool isBalanced(string & num){		//check the vaildity of balanced parentheses
	int l = 0;
	int j = 0;
	string space;
	for ( int i=0 ; i<num.length() ; i++ ) {	
		if ( num[i] != ' ' ) {					// 將除去字串中的空格  
			space = space + num[i];	
		}
	} 
	
	num = space;					
	for( int i=0 ; i<num.length() ; i++ ){
		if ( num[i] == '(' ){
			l++;
		}
		else if ( num[i] == ')' ){
			j++;
		}
	}
		
	if( l==j ){
		return true;
	}
	else if( l>j ){
		cout << "Error 2: There is one extra open parenthesis.";
		return false;
	}
	else if( j>l ){
		cout << "Error 2: There is one extra close parenthesis.";
		return false;
	}

}

bool isLegal(const string & num){ 				//check whether it is a legal expression
	for( int i=0 ; i<num.length() ; i++ ){
		if( num[i] == ')'){
			if( i<num.length()-1 && (num[i+1] >= '0' && num[i+1] <= '9') ){
				cout << "Error 3: There is one extra operand.";
				return false;
			}
		}
		else if ( num[i] == '('){
			if ( i>=0 && (num[i-1] >= '0' && num[i-1] <= '9') ){
				cout << "Error 3: There is one extra operand.";
				return false;
			}
		}
		else if( num[i] == '+' || num[i] == '-' || num[i] == '*' || num[i] == '/' ){   
			if( i<num.length()-1 && ( num[i+1] == '+' || num[i+1] == '-' || num[i+1] == '*' || num[i+1] == '/' ) ){
				cout << "Error 3: There is one extra operater.";
				return false;
			}
		}
	}
	
	return true;
}

expList<string> sister;
expStack<string> brother;
expList<string> family;

int precedence(string & ch) {					//設定先後順序 
    if ( ch == "+" || ch == "-") {
        return 1;
    } 
	else if ( ch == "*" || ch == "/") {
        return 2;
    }
    else return 0;
}

void str2list(const string & num){				//parse a string into a linked list
	for( int i=0 ; i<num.length() ; i++ ){
		string store;
        if ( num[i] >= '0' && num[i] <= '9' ) {
        	store = store + num[i];
        	while ( num[i+1] >= '0' && num[i+1] <= '9' ){
        		i++;
        		store = store + num[i];
			}
			sister.ins(store);	
        } 
		else if ( num[i] == '(' || num[i] == ')' ) {
			store = store + num[i];
			sister.ins(store);
        } 
		else if ( num[i] == '+' || num[i] == '-' || num[i] == '*' || num[i] == '/' ) {
            store = store + num[i];
			sister.ins(store);
        }
	}	
}


bool infix2postfix(){					//transfrom infix into postfix
	while( !sister.isEmpty() ){
		string cat;
		string number;
		string head;
		sister.getHead(cat);
		if( cat[0] >= '0' && cat[0] <= '9' ){  
			family.ins(cat);	
			sister.del();	
		}
		else if ( cat == "(" ) {
			brother.push(cat);
			sister.del();
        } 
        else if ( cat == ")" ){
        	brother.pop(cat);
        	while ( cat != "(" ) {  	//不是左括號就一直pop 
    			family.ins(cat);
            	brother.pop(cat);
			}  
			sister.del();
		}
		else if ( cat == "+" || cat == "-" || cat == "*" || cat == "/" ) {
			if ( brother.isEmpty() ){		//stack為空就直接丟進去 
				brother.push(cat);
			}
			else {							//判斷順序 
				brother.getTop(number);
				if ( precedence(cat) > precedence(number) ){			// 輸入 > 原本 (輸入的存進去) 
					brother.push(cat);
				}
				else if ( precedence(cat) == precedence(number) ){		// 輸入 = 原本 (原本的丟出去 輸入的存進去) 
					brother.pop(number);
					family.ins(number);
					brother.push(cat);
				}
				else if ( precedence(cat) < precedence(number) ){		// 輸入 < 原本 (原本的丟出去) 
					brother.pop(number);
					family.ins(number);
					if ( !brother.isEmpty() ){							// 如果stack不為空 繼續比順序 
						brother.getTop(number);
						if ( precedence(cat) <= precedence(number) ){	// 輸入 > 原本 (原本的丟出去) 
							brother.pop(number);
							family.ins(number);
						}
					}
					brother.push(cat);									// (輸入的存進去) 
				}
			}
            sister.del();
        }
	}
		
	while( !brother.isEmpty() ){	// 如果stack不為空 繼續把東西丟出來 
		string number;
		brother.pop(number);
		family.ins(number);
	}	
		

	cout << "\nPostfix expression: ";
    family.Cout();
    cout << endl;
	return true;
}

int main(void) {

	int command=0;
	do{
		string infixS;
		cout<< endl << "* Arithmetic Expression Evaluator *";
		cout<< endl << "* 0. QUIT                         *";
		cout<< endl << "* 1. Infix2postfix Transformation *";
		cout<< endl << "***********************************";
		cout<< endl << "Input a choice(0, 1): ";
		cin >> command;
		cin.ignore(MAX_LEN, '\n');
		if ( command == 0 ){
			break;
		}
		else if ( command == 1 ){
			cout<< endl << "Input an infix expression: ";
			getline(cin, infixS);
			if(isExp(infixS) && isBalanced(infixS) && isLegal(infixS)){
				cout << "It is a legitimate infix expression.";
				str2list(infixS);
				infix2postfix();
				sister.~expList();
				family.~expList(); 
			}
			sister.clearUp();
			
		}
		else {
			cout << endl << "Command does not exist!" << endl;
		}
	} while(command!=0); 
	
	system("pause");
	return 0;
}
