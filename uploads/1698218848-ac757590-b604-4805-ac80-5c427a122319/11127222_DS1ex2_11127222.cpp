// 11127222 ����� 
#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Node {
    string data;
    Node* next;
};

// �A���ƶq
bool numOfParentheses(Node* str) {
  Node* current = str;
  int open = 0, close = 0;
  
  while (current != NULL) {
  	// �p��A���� 
  	if (current->data == "(") {
  	  open++;
  	}
  	else if (current->data == ")"){
  	  close++;
  	} 
  	
  	// �h�F�@�ӫ�A�� 
  	if (close > open) {
		  cout << "Error 2: there is one extra close parenthesis.\n" << endl;
      return false; 
		}
		
		current = current->next;
	}
	
	// �ˬd�e��A���ƶq�O�_�@��
	if(open == close)
	  return true;
		// ���@�˫hError2 
	else {
	  cout << "Error 2: there is one extra open parenthesis.\n" << endl;
	  return false;
	}
}

// �e�A��
bool openParenthesis(Node* head) {
    Node* current = head;
    Node* previous = NULL;

    while (current) {
        if (current->data == "(") {
            // �p�G "(" �e�����Ʀr�A�hError3 
            if (previous && isdigit(previous->data[0])) {
                cout << "Error 3: There is one extra operand.\n" << endl;
                return false;
            }
            // �p�G�᭱�O+-*/�A�hError3
            else if (current->next && (current->next->data == "+" || current->next->data == "-" || current->next->data == "*" || current->next->data == "/")) {
            	cout << "Error 3: it is not infix in the parentheses.\n" << endl;
            	return false;
            }
        }
        previous = current;
        current = current->next;
    }
    
    return true;
}

// ��A�� 
bool closeParenthesis(Node* head) {
    Node* current = head;
    Node* previous = NULL;

    while (current) {
        if (current->data == ")") {
            // �p�G ")" �᭱�O�Ʀr�A�hError3 
            if (current->next && isdigit(current->next->data[0])) {
                cout << "Error 3: There is one extra operand.\n" << endl;
                return false;
            }
            // �p�G�e����+-*/�A �hError3 
            else if (previous && (previous->data == "+" || previous->data == "-" || previous->data == "*" || previous->data == "/")) {
            	cout << "Error 3: it is not infix in the parentheses.\n" << endl;
            	return false;
            } 
        }
        
        previous = current;
        current = current->next;
    }
    
    return true;
}

// �s��+-*/
bool symbol(Node* head) {
	Node* current = head;
	while (current != NULL) {
		if (current->data == "+" || current->data == "-" || current->data == "*" || current->data == "/") {
			if (current->next->data == "+" || current->next->data == "-" || current->next->data == "*" || current->next->data == "/") {
        cout << "Error 3: There is one extra operand.\n" << endl;
        return false;
			}
		}
		
		current = current->next;
	}
	
	return true;
}
 
// �������� 
Node* infixToPostfix(Node* infix) {
  Node* postfixHead = NULL; // �Τ_���V�Z?��?��?��?��
  Node* postfixCurrent = NULL; // �Τ_�۫ئZ?��?��?��
  Node* stack = NULL;

  while (infix != NULL) {
    if (infix->data == "(") {
      stack = new Node{"(", stack};
    }
    else if (infix->data == ")") {
      while (stack != NULL && stack->data != "(") {
        postfixCurrent = new Node{stack->data, postfixCurrent};
        stack = stack->next;
      }
      if (stack != NULL) {
        stack = stack->next;
      }
    }
    else if (infix->data == "+" || infix->data == "-") {
      while (stack != NULL && (stack->data == "+" || stack->data == "-" || stack->data == "*" || stack->data == "/")) {
        postfixCurrent = new Node{stack->data, postfixCurrent};
        stack = stack->next;
      }
      stack = new Node{infix->data, stack};
    }
    else if (infix->data == "*" || infix->data == "/") {
      while (stack != NULL && (stack->data == "*" || stack->data == "/")) {
        postfixCurrent = new Node{stack->data, postfixCurrent};
        stack = stack->next;
      }
      stack = new Node{infix->data, stack};
    }
    else {
      postfixCurrent = new Node{infix->data, postfixCurrent};
    }
    infix = infix->next;
  }

  while (stack != NULL) {
    postfixCurrent = new Node{stack->data, postfixCurrent};
    stack = stack->next;
  }

  // �Z?��?��?��O�ϦV���A�ݭn½??��A�P?��s postfixHead
  Node* temp = NULL;
  while (postfixCurrent != NULL) {
    temp = postfixCurrent->next;
    postfixCurrent->next = postfixHead;
    postfixHead = postfixCurrent;
    postfixCurrent = temp;
  }

  return postfixHead;
}

// �L�X��Ǧ� 
void PrintList(Node* head) {
	Node* current = head;
	cout << "It is a legtimate postfix expression." << endl << "Postfix expression: ";
	if (current != NULL) {
  	cout << current->data;
  	current = current->next;
	}
	
  while (current != NULL) {
    cout << ", " << current->data;
    current = current->next;
  }
  
  cout << endl << endl;
}

// ������Ф��s 
void free(Node* head) {
  while (head != NULL) {
	  Node* temp = head;
    head = head->next;
    delete temp;
  }
}

int main() {

	while(1) {
  	Node* head = NULL;
	  Node* postfixExpression = NULL;
    Node* current = head;
    int command;
    string expression;
    
	  printf("* Arithmetic Expression Evaluator *\n");
  	printf("* 0. QUIT                         *\n");
  	printf("* 1. Infix2postfix Transformation *\n");
  	printf("***********************************\n");
  	printf("Input a choice(0, 1):");
    cin >> command;
  	if ( command == 1 ) {
  		Node* head = NULL;
      Node* current = head;
      int i = 0;
      int error = 0;
       
   	  cout << "\nInput an infix expression:";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      getline(cin, expression);
        
      // �N�⦡�s�ihead���� 
      while (i < expression.length()) {
        if (isdigit(expression[i])) {
          string numStr;
          // Ū���Ʀr�۲šA����J��D�Ʀr�r��
          while (i < expression.length() && isdigit(expression[i])) {
            numStr += expression[i];
            i++;
          }
          
          // �N�Ʀr�s�W�ܫ��Ф� 
          if (head == NULL) {
            head = new Node{numStr, NULL};
            current = head;
          } 
					else {
            current->next = new Node{numStr, NULL};
            current = current->next;
          }
        } 
				else if (expression[i] == '(' || expression[i] == ')' || expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
        // �N�Ÿ��s�W�i�쵲�`�I 
          string operatorStr(1, expression[i]);
          if (head == NULL) {
            head = new Node{operatorStr, NULL};
            current = head;
          } 
				  else {
            current->next = new Node{operatorStr, NULL};
            current = current->next;
          }
            
          i++;
        }
        // �����Ů� 
	  		else if (expression[i] == ' ') {
          i++;
        } 
        // �S�����Ÿ��A�hError1 
        else {
        	printf("Error 1: %c is not a legtimate infix expression.\n\n", expression[i]);
          error = 1;
          break;
				}
    	}

      // �ˬd�O�_��Error
      if (error == 0 && numOfParentheses(head)) {
        if(openParenthesis(head)) {
          if (closeParenthesis(head)) {
          	if (symbol(head)) {
        	    Node* test = head;
              postfixExpression = infixToPostfix(test);
              PrintList(postfixExpression);
			      }
			 		}
			  }
      }

      // ���񤺦s 
      expression = "";
      free(head);
      free(postfixExpression);

      
    }
    else if ( command == 0 ) {
  	  break;
    }
	  else {
	    printf("Command doesn't exsit.\n");		
	  }
	} 
}
