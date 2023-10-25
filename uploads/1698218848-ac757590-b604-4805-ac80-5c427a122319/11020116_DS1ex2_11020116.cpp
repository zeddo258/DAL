// 電資三 11020116 潘皓群 
// 有使用C++11 

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <string>
#include <deque>
#include <string.h>
#include <cctype>
#include <cstring>
using namespace std;
void GetCommand( int &command) { // 印出使用介面並讀入指令以及處理指令出錯的情況 
    printf("\n"); 
	printf("* Arithmetic Expression Evaluator *\n");
	printf("* 0. Quit                         *\n");	
	printf("* 1. Infix2postfix Transformation *\n");
	printf("***********************************\n");
	printf("Input a command(0, 1,): ");
	cin >> command;
		
}

class Stack { //用pointer建立stack的Class 
private:
    struct Node { 
        char data;
        Node* next;
        Node(char c) : data(c), next(nullptr) {}
    };

    Node* topNode; //紀錄stack最上方 

public:
    Stack() : topNode(nullptr) {}

    void clearstack() { //用來delete stack 
        while (!isEmpty()) {
            deletetop();
        }
    }

    bool isEmpty() const { //確認stack是否為空? 
        return topNode == nullptr;
    }

    void push(char c) { //將資料放進stack 
        Node* newNode = new Node(c);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() { //將最上方的資料印出並刪除 
        if (isEmpty()) {
            return '\0'; 
        }
        if(topNode->data != '(' && topNode->data != ')')
        	cout<< topNode->data; //<< "clear\n";
        Node* temp = topNode;
        char data = topNode->data;
        topNode = topNode->next;
        delete temp;
        return data;
    }
    
    void deletetop(){ //單純刪除不印出 
    	Node* temp = topNode;
    	topNode = topNode->next;
    	delete temp;
	}

    char top() const { //查看現在最上面的是甚麼? 
        if (isEmpty()) {
            return '\0'; 
        }
        return topNode->data;
    }
};
int priority(char c){ //用來決定+-*/的優先順序，先 * / 後 + - 
	switch(c){
		case'+':
			return 1;
		case'-':
			return 1;
		case'*':
			return 2;
		case'/':
			return 2;
		default:
			return 0;
	}
}
bool isOperator(char c) { //是否是正確的計算符號? 
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isValidExpression(const string& expression) { //檢查是不是合法的中序式 
    int brackets = 0; //用來判別括號數量是否正確 
    char prev = '+'; //用來存上一個字元 


    for (char c : expression) {
        if (c == ' ') {
            continue;  // 跳過空白字元
        }

        if (isOperator(c)) {
        	if(isOperator(prev)){ 
        		cout << "Error3: there is one extra operator.\n"; 
        		return false; //連續兩個計算符號，錯誤  
			}


        } 
		else if (c == '(') {
            brackets++; 
        } 
		else if (c == ')') {
            brackets --;
        }
		else if (isdigit(c)){ 
			if(!isOperator(prev) && !isdigit(prev) && prev !='('){
        		cout << "Error3: there is one extra operand.\n";	
        		return false;	 //多出的數字，錯誤			
			}
		} 
		else if (!isdigit(c)) {
        	cout << "Error1:" << c << " is not a legitimate character.\n";
            return false;  // 非法符號， 錯誤 
        }
        prev = c; // 存下當前字元 
    }

	if( brackets != 0 ){
		if(brackets > 0) cout << "Error2: there is an extra open parenthesis.\n"; // 多出前括號 
		else if(brackets<0) cout << "Error2: there is an extra close parenthesis.\n"; // 少一個後括號 
		return false;
	} 
    return true;
}

int main() {
		
	int command = 0;  
	bool correct = true;
	GetCommand(command);
	while(command != 0){ //當指令不為0，就繼續讀取指令 
		if(command == 1){			
    		string expression;
    		cout << "Input an infix expression: ";
    		cin.ignore(); // 如果在getline前用過cin，就要用ignore把後面沒讀的東西讀掉 
    		getline(cin,expression); // 讀入目標字串 
    		
			if(expression.length()==0) { //啥都沒輸入，錯誤 
				cout << "Error3: there is one extra operator.\n";
				correct = false;
				return 0;
			}
			else{
    			if (isValidExpression(expression)) { //檢查算式是否合法 
    				cout << "It is a legit infix expression.\n";
    				
    			}
    			else correct = false;
			}
			
			if(correct == true){ //如果算式不合法，就不用繼續了 

				Stack stack; //建立一個stack 

				for(int i = 0 ; i < expression.length() ; i++){  

					if(isdigit(expression[i])){ //如果當前字元是數字 
						int temp = i+1;
						cout<< expression[i] ;
						while(isdigit(expression[temp])){ //則檢查接下來的字元是不是數字?如果是就直接印在後面 
							i++;
							cout<< expression[i] ;
							temp = i+1;
						}
						cout << ", ";


					}
					else if(!isdigit(expression[i])){ // 如果當前字元不是數字 
							if(stack.isEmpty()){ // 如果stack是空的，直接把符號放進去 
								stack.push(expression[i]);	
							}
							else if((expression[i]=='(')){ //左括弧也是直接放 
								stack.push(expression[i]);
							}
							else if(isOperator(expression[i])){ //如果是計算符號，就看當前的計算符號有沒有順位大於在stack頂部的符號 
								while(priority(expression[i])<= priority(stack.top())){
									stack.pop();
									cout << ", "; //如果沒有大於，就先把stack裡面的符號印出來 
								}
								stack.push(expression[i]); //印完再把當前的符號放進去 
							}
							else if(expression[i] == ')'){ //如果遇到右括弧 就把遇到左括弧之前的計算符都印出來 
								while(stack.top()!='('){
									stack.pop();
									cout << ", ";
								}
								stack.deletetop(); //然後把左括弧刪掉 
							}						
					} 


				}
				while(!stack.isEmpty()){ //如果stack裡面還有東西 就印出來 
					stack.pop();
					if(!stack.isEmpty())cout << ", ";
				}
				cout<<"\n";
				stack.clearstack(); //釋放記憶體 
			}

			
		}
		else{
			printf("Command does not exist!\n"); //錯誤指令 
		}

		GetCommand(command);

			
		
	}
	


    return 0;
}

