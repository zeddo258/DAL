#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <vector>



using namespace std;



class Node { 
//linked list ���O 
	
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
	
//stack���O 
	
private:
	
    Node* top;

public:
	
    Stack() {
    	
        top = NULL;
        
    }

    void ins(string data) {
    	//���ƥ[�J��linked list�� 
    	
    	
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
        
    }

    void del() {
    	//�R��linked list�̪� head
		//�åѲĤG�Ӧ����s��head 
    	
    	
        if (top == NULL) {
        	
            cout << "Stack is empty." << endl;
            return;
        }
        
        
        Node* temp = top;
        top = top->next;
        delete temp;
        
    }



    string gethead() {
    	
    	//���linked list�� head����� 
    	//�åB�^�Ǹ�� 
    	
    	
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

	//�^���u����
	//��������[�� �A�������n����
	 
	
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
	
	//�⤤���ন���
	//�æs�Jlinked list 
	
	
    Stackop opStack;
    string num = "";


    for (int i = 0; i < infix_expression.length(); i++) {  
    	
        char c = infix_expression[i];
        
        if (isalnum(c)) {  
            num += c;  
			//�N��@���Ʀr ����string  
        } 
		else {
			
            if (!num.empty()) {
            	
                postfixList.ins(num); 
				 //�J�줣�O�Ʀr���N����Ʀr��illinked list 
                num = "";
            }

            if (c == '(') {
            	
                opStack.push(c);   
				//�N���A����istack 
            } 
			else if (c == ')') {
				
				//��Ū��k�A���Nstack�̪��B��l��ilinked list���쥪�A��
				 
                while (!opStack.empty() && opStack.top() != '(') {
                	
                    postfixList.ins(string(1, opStack.top()));
                    opStack.pop();
                    
                }
                opStack.pop();  
                //�N���A��pop�Xstack 
                
            } 
			else {
				
				//�P�_�u���ŨM�w�O�_������iLinked list 
				//�άO�Nsstack�̪��B��l��iLinked list�åBpop�Xstack 
                while (!opStack.empty() && opStack.top() != '(' && precedence(c) <= precedence(opStack.top())) {
                	
                    postfixList.ins(string(1, opStack.top()));
                    opStack.pop();
                }
                
                //�N�B��l��istack�� 
                opStack.push(c);
                
            }
            
        }
        
    }

    if (!num.empty()) { 
	 
    	//�N�̫᪺�Ʀr�]��iLinked list	
        postfixList.ins(num);
        
    }

    while (!opStack.empty()) {
    	
    	//���ǥ���Ū����
		//�Nstack�ѤU���B��l��ilinked list 
        postfixList.ins(string(1, opStack.top()));
        opStack.pop();
        
    }
    
    
}



void printPostfix(Stack& postfixList) {
	
	//linked list�L�X
	 
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
	
	//�P�_�O�_�����F�[����H�~���Ÿ� 
	
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

	//�P�_�A���ƶq�O�_���`
	 
    int i = 0;
    int left = 0, right = 0;

    while (i < infixS.size()) {
    	
        if (infixS[i] == '(') { 
        
            left++;
        } 
        else if (infixS[i] == ')') {
            right++;
			 
            if (right > left) {  
			//��k�A���ƶq�j�󥪬A�����ɭ� 
			// �^��eroor 2
			 
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
	
	//�P�_���ǬO�_�ŦX�B��W�h
	//�S���h�@�ӹB��l�άO����m���諸���p
	//�]�S���A�����èS�����T������ 
	
    int i = 0;
    
    
    
    while (i < infixS.size()) {
    	
    	
        if (infixS[i] == '+' || infixS[i] == '-' || infixS[i] == '*' || infixS[i] == '/') {
        	
            if (i == 0 || i == (infixS.size() - 1)) {
            	// �B��l���i��b�Ĥ@�өάO�̫�@�� 
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
