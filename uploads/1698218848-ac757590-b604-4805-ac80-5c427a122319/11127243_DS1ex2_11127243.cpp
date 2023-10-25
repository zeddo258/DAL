#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <vector>



using namespace std;



class Node { 
//linked list 類別 
	
public:
	
    string data;
    Node* next;

    Node(string d) {
    	
        data = d;
        next = NULL;
        
    }
    
    
};

class Stackop {
	
	private:
		vector<char> op;
		
	public:
		bool empty() {
			if(op.empty())  return true;
			else return false;
		}
		int size() {
			return op.size();
		}
		char top() {
			return op.back();
		}
		void pop() {
			return op.pop_back();
		} 
		void push(char ch){
			op.push_back(ch);
		}
};


class Stack {
	
//stack類別 
	
private:
	
    Node* top;

public:
	
    Stack() {
    	
        top = NULL;
        
    }

    void ins(string data) {
    	//把資料加入到linked list裡 
    	
    	
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
        
    }

    void del() {
    	//刪掉linked list裡的 head
		//並由第二個成為新的head 
    	
    	
        if (top == NULL) {
        	
            cout << "Stack is empty." << endl;
            return;
        }
        
        
        Node* temp = top;
        top = top->next;
        delete temp;
        
    }



    string gethead() {
    	
    	//抓取linked list裡 head的資料 
    	//並且回傳資料 
    	
    	
        if (top == NULL) {
        	
            return "Stack is empty.";
        }
        
        return top->data;
    }


    bool isEmpty() {
        return top == NULL;
    }
    
    
};



int precedence(char op) { 

	//回傳優先級
	//先乘除後加減 括號內的要先做
	 
	
    if (op == '+' || op == '-') {
        return 1;
    } 
	else if (op == '*' || op == '/') {
        return 2;
    } 
	else if (op == '^') {
        return 3;
    }
    return 0;  
    
    
}



void infixToPostfix(string infix_expression, Stack& postfixList) {
	
	//把中序轉成後序
	//並存入linked list 
	
	
    Stackop opStack;
    string num = "";


    for (int i = 0; i < infix_expression.length(); i++) {  
    	
        char c = infix_expression[i];
        
        if (isalnum(c)) {  
            num += c;  
			//將單一的數字 接成string  
        } 
		else {
			
            if (!num.empty()) {
            	
                postfixList.ins(num); 
				 //遇到不是數字的就先把數字丟進llinked list 
                num = "";
            }

            if (c == '(') {
            	
                opStack.push(c);   
				//將左括號丟進stack 
            } 
			else if (c == ')') {
				
				//當讀到右括號將stack裡的運算子丟進linked list直到左括號
				 
                while (!opStack.empty() && opStack.top() != '(') {
                	
                    postfixList.ins(string(1, opStack.top()));
                    opStack.pop();
                    
                }
                opStack.pop();  
                //將左括號pop出stack 
                
            } 
			else {
				
				//判斷優先級決定是否直接丟進Linked list 
				//或是將sstack裡的運算子丟進Linked list並且pop出stack 
                while (!opStack.empty() && opStack.top() != '(' && precedence(c) <= precedence(opStack.top())) {
                	
                    postfixList.ins(string(1, opStack.top()));
                    opStack.pop();
                }
                
                //將運算子丟進stack裡 
                opStack.push(c);
                
            }
            
        }
        
    }

    if (!num.empty()) { 
	 
    	//將最後的數字也丟進Linked list	
        postfixList.ins(num);
        
    }

    while (!opStack.empty()) {
    	
    	//中序全部讀完後
		//將stack剩下的運算子丟進linked list 
        postfixList.ins(string(1, opStack.top()));
        opStack.pop();
        
    }
    
    
}



void printPostfix(Stack& postfixList) {
	
	//linked list印出
	 
    Stack tempStack;
    
    
    while (!postfixList.isEmpty()) {
    	
        tempStack.ins(postfixList.gethead());
        postfixList.del();
        
    }

    while (!tempStack.isEmpty()) {
    	
        string Ans = tempStack.gethead();
        
        
        
        tempStack.del();
        cout << Ans ;
        if (!tempStack.isEmpty()) {
        	
    		cout << ",";
		}
        
    }
    
    cout << endl;
    
    
}


bool isExp(const string& infixS) { 
	
	//判斷是否有除了加減乘除以外的符號 
	
    int i = 0;

    while (i < infixS.size()) {

    	if (infixS[i] != '+' && infixS[i] != '-' && infixS[i] != '*' && infixS[i] != '/' && infixS[i] != '(' && infixS[i] != ')') {
            if (48 > infixS[i] || 57 < infixS[i]) {
            	
                cout << "Error 1 : " << infixS[i] << " is not a legitimate character.";
                return false;
            }
		}

        i++;
    }

    return true;
}


bool isBalance(const string& infixS) { 

	//判斷括號數量是否正常
	 
    int i = 0;
    int left = 0, right = 0;

    while (i < infixS.size()) {
    	
        if (infixS[i] == '(') { 
        
            left++;
        } 
        else if (infixS[i] == ')') {
            right++;
			 
            if (right > left) {  
			//當右括號數量大於左括號的時候 
			// 回傳eroor 2
			 
                cout << "Error 2 : there is one extra close parenthesis.";
                return false;
            }
            
        }
        
        
        i++;
        
	}

    if (left == right) { 
        return true;
    } 
    else {

        if (left > right) { 
            cout << "Error 2 : there is one extra open parenthesis.";
		}
		 
    }

    return false;
    
}


bool isLegal(const string& infixS) {
	
	//判斷中序是否符合運算規則
	//沒有多一個運算子或是有位置不對的情況
	//也沒有括號中並沒有正確的中序 
	
    int i = 0;
    
    
    
    while (i < infixS.size()) {
    	
    	
        if (infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/') {
        	
            if (i == 0 || i == (infixS.size() - 1)) {
            	// 運算子不可能在第一個或是最後一個 
                cout << "Error 3 : there is one extra operator.";
                return false;
            }
            else if (infixS[i + 1] == '+' || infixS[i + 1] == '-' || infixS[i + 1] == '*' || infixS[i + 1] == '/') {
                cout << "Error 3 : there is one extra operator.";
                return false;
            }
            
        }
        if (infixS[i] == '(') {
        	
            if (i != 0 && (48 <= infixS[i - 1] && infixS[i - 1] <= 57)) {
                cout << "Error 3 : there is one extra operand.";
                return false;
            }
            else if (48 > infixS[i + 1] || 57 < infixS[i + 1]) {
            	if( infixS[i + 1] != 'C' ) {
				
            	    cout << "Error 3 : it is not infix in the parentheses.";
                	return false;
                }
                
            }
            
        }
        else if (infixS[i] == ')') {
        	
        	
            if (i != (infixS.size() - 1) && (48 <= infixS[i + 1] && infixS[i + 1] <= 57)) {
                cout << "Error 3 : there is one extra operand.";
                return false;
            }
            else if (48 > infixS[i - 1] || 57 < infixS[i - 1]) {
            	
            	if( infixS[i - 1] != ')' ) {
				
                	cout << "Error 3 : it is not infix in the parentheses.";
                	return false;
            	}
            	
            }
            
        }
        
        
        i++;
    }

    return true ;
    
    
}



int main() {
	
	Stack postfixList;
	int command;
    string infixS;
    string temp ;

    cout << endl << "Arithmetic Expression Evaluator    ";
    cout << endl << "* 0. Quit                          ";
    cout << endl << "* 1. Infix2postfix Transformation  ";
    cout << endl << "*********************************";
    cout << endl << "Input a choice (0, 1): ";
    cin >> command;

    while (command != 0) {
    	
    	
        if (command == 1) {
        	
            cout << endl << "Input an infix expression: ";
            cin.ignore(); 
            getline(cin, infixS);

			
        	infixS.erase(remove_if(infixS.begin(), infixS.end(), ::isspace), infixS.end());
        	
            if (isExp(infixS)) {
            	
                if (isBalance(infixS)) {
                	
                    if (isLegal(infixS)) {
                    	
                        cout << "It is a legitimate infix expression. ";
                        cout << endl ;
                    	infixToPostfix(infixS, postfixList);
						printPostfix(postfixList);
					}
					
                }
                
            }
            
        }
        else { 
            cout << endl << "Command does not exist!";
		}
		 
        cout << endl << endl << "Arithmetic Expression Evaluator    ";
        cout << endl << "* 0. Quit                          ";
        cout << endl << "* 1. Infix2postfix Transformation  ";
        cout << endl << "*********************************";
        cout << endl << "Input a choice (0, 1): ";
        cin >> command;
        
        
    }

    
	
	
    
}
