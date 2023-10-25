// 11127222 邱妤蓁 
#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Node {
    string data;
    Node* next;
};

// 括號數量
bool numOfParentheses(Node* str) {
  Node* current = str;
  int open = 0, close = 0;
  
  while (current != NULL) {
  	// 計算括號數 
  	if (current->data == "(") {
  	  open++;
  	}
  	else if (current->data == ")"){
  	  close++;
  	} 
  	
  	// 多了一個後括號 
  	if (close > open) {
		  cout << "Error 2: there is one extra close parenthesis.\n" << endl;
      return false; 
		}
		
		current = current->next;
	}
	
	// 檢查前後括號數量是否一樣
	if(open == close)
	  return true;
		// 不一樣則Error2 
	else {
	  cout << "Error 2: there is one extra open parenthesis.\n" << endl;
	  return false;
	}
}

// 前括號
bool openParenthesis(Node* head) {
    Node* current = head;
    Node* previous = NULL;

    while (current) {
        if (current->data == "(") {
            // 如果 "(" 前面有數字，則Error3 
            if (previous && isdigit(previous->data[0])) {
                cout << "Error 3: There is one extra operand.\n" << endl;
                return false;
            }
            // 如果後面是+-*/，則Error3
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

// 後括號 
bool closeParenthesis(Node* head) {
    Node* current = head;
    Node* previous = NULL;

    while (current) {
        if (current->data == ")") {
            // 如果 ")" 後面是數字，則Error3 
            if (current->next && isdigit(current->next->data[0])) {
                cout << "Error 3: There is one extra operand.\n" << endl;
                return false;
            }
            // 如果前面有+-*/， 則Error3 
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

// 連續+-*/
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
 
// 中序轉後序 
Node* infixToPostfix(Node* infix) {
  Node* postfixHead = NULL; // 用于指向后?表?式?表的?部
  Node* postfixCurrent = NULL; // 用于构建后?表?式?表
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

  // 后?表?式?表是反向的，需要翻??表，同?更新 postfixHead
  Node* temp = NULL;
  while (postfixCurrent != NULL) {
    temp = postfixCurrent->next;
    postfixCurrent->next = postfixHead;
    postfixHead = postfixCurrent;
    postfixCurrent = temp;
  }

  return postfixHead;
}

// 印出後序式 
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

// 釋放指標內存 
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
        
      // 將算式存進head指標 
      while (i < expression.length()) {
        if (isdigit(expression[i])) {
          string numStr;
          // 讀取數字自符，直到遇到非數字字符
          while (i < expression.length() && isdigit(expression[i])) {
            numStr += expression[i];
            i++;
          }
          
          // 將數字新增至指標內 
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
        // 將符號新增進鏈結節點 
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
        // 忽略空格 
	  		else if (expression[i] == ' ') {
          i++;
        } 
        // 沒有此符號，則Error1 
        else {
        	printf("Error 1: %c is not a legtimate infix expression.\n\n", expression[i]);
          error = 1;
          break;
				}
    	}

      // 檢查是否有Error
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

      // 釋放內存 
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
