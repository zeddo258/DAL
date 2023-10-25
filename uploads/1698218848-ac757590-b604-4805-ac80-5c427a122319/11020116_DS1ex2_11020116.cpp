// �q��T 11020116 ��q�s 
// ���ϥ�C++11 

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
void GetCommand( int &command) { // �L�X�ϥΤ�����Ū�J���O�H�γB�z���O�X�������p 
    printf("\n"); 
	printf("* Arithmetic Expression Evaluator *\n");
	printf("* 0. Quit                         *\n");	
	printf("* 1. Infix2postfix Transformation *\n");
	printf("***********************************\n");
	printf("Input a command(0, 1,): ");
	cin >> command;
		
}

class Stack { //��pointer�إ�stack��Class 
private:
    struct Node { 
        char data;
        Node* next;
        Node(char c) : data(c), next(nullptr) {}
    };

    Node* topNode; //����stack�̤W�� 

public:
    Stack() : topNode(nullptr) {}

    void clearstack() { //�Ψ�delete stack 
        while (!isEmpty()) {
            deletetop();
        }
    }

    bool isEmpty() const { //�T�{stack�O�_����? 
        return topNode == nullptr;
    }

    void push(char c) { //�N��Ʃ�istack 
        Node* newNode = new Node(c);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() { //�N�̤W�誺��ƦL�X�çR�� 
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
    
    void deletetop(){ //��§R�����L�X 
    	Node* temp = topNode;
    	topNode = topNode->next;
    	delete temp;
	}

    char top() const { //�d�ݲ{�b�̤W�����O�ƻ�? 
        if (isEmpty()) {
            return '\0'; 
        }
        return topNode->data;
    }
};
int priority(char c){ //�ΨӨM�w+-*/���u�����ǡA�� * / �� + - 
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
bool isOperator(char c) { //�O�_�O���T���p��Ÿ�? 
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isValidExpression(const string& expression) { //�ˬd�O���O�X�k�����Ǧ� 
    int brackets = 0; //�ΨӧP�O�A���ƶq�O�_���T 
    char prev = '+'; //�ΨӦs�W�@�Ӧr�� 


    for (char c : expression) {
        if (c == ' ') {
            continue;  // ���L�ťզr��
        }

        if (isOperator(c)) {
        	if(isOperator(prev)){ 
        		cout << "Error3: there is one extra operator.\n"; 
        		return false; //�s���ӭp��Ÿ��A���~  
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
        		return false;	 //�h�X���Ʀr�A���~			
			}
		} 
		else if (!isdigit(c)) {
        	cout << "Error1:" << c << " is not a legitimate character.\n";
            return false;  // �D�k�Ÿ��A ���~ 
        }
        prev = c; // �s�U��e�r�� 
    }

	if( brackets != 0 ){
		if(brackets > 0) cout << "Error2: there is an extra open parenthesis.\n"; // �h�X�e�A�� 
		else if(brackets<0) cout << "Error2: there is an extra close parenthesis.\n"; // �֤@�ӫ�A�� 
		return false;
	} 
    return true;
}

int main() {
		
	int command = 0;  
	bool correct = true;
	GetCommand(command);
	while(command != 0){ //����O����0�A�N�~��Ū�����O 
		if(command == 1){			
    		string expression;
    		cout << "Input an infix expression: ";
    		cin.ignore(); // �p�G�bgetline�e�ιLcin�A�N�n��ignore��᭱�SŪ���F��Ū�� 
    		getline(cin,expression); // Ū�J�ؼЦr�� 
    		
			if(expression.length()==0) { //ԣ���S��J�A���~ 
				cout << "Error3: there is one extra operator.\n";
				correct = false;
				return 0;
			}
			else{
    			if (isValidExpression(expression)) { //�ˬd�⦡�O�_�X�k 
    				cout << "It is a legit infix expression.\n";
    				
    			}
    			else correct = false;
			}
			
			if(correct == true){ //�p�G�⦡���X�k�A�N�����~��F 

				Stack stack; //�إߤ@��stack 

				for(int i = 0 ; i < expression.length() ; i++){  

					if(isdigit(expression[i])){ //�p�G��e�r���O�Ʀr 
						int temp = i+1;
						cout<< expression[i] ;
						while(isdigit(expression[temp])){ //�h�ˬd���U�Ӫ��r���O���O�Ʀr?�p�G�O�N�����L�b�᭱ 
							i++;
							cout<< expression[i] ;
							temp = i+1;
						}
						cout << ", ";


					}
					else if(!isdigit(expression[i])){ // �p�G��e�r�����O�Ʀr 
							if(stack.isEmpty()){ // �p�Gstack�O�Ū��A������Ÿ���i�h 
								stack.push(expression[i]);	
							}
							else if((expression[i]=='(')){ //���A���]�O������ 
								stack.push(expression[i]);
							}
							else if(isOperator(expression[i])){ //�p�G�O�p��Ÿ��A�N�ݷ�e���p��Ÿ����S������j��bstack�������Ÿ� 
								while(priority(expression[i])<= priority(stack.top())){
									stack.pop();
									cout << ", "; //�p�G�S���j��A�N����stack�̭����Ÿ��L�X�� 
								}
								stack.push(expression[i]); //�L���A���e���Ÿ���i�h 
							}
							else if(expression[i] == ')'){ //�p�G�J��k�A�� �N��J�쥪�A�����e���p��ų��L�X�� 
								while(stack.top()!='('){
									stack.pop();
									cout << ", ";
								}
								stack.deletetop(); //�M��⥪�A���R�� 
							}						
					} 


				}
				while(!stack.isEmpty()){ //�p�Gstack�̭��٦��F�� �N�L�X�� 
					stack.pop();
					if(!stack.isEmpty())cout << ", ";
				}
				cout<<"\n";
				stack.clearstack(); //����O���� 
			}

			
		}
		else{
			printf("Command does not exist!\n"); //���~���O 
		}

		GetCommand(command);

			
		
	}
	


    return 0;
}

