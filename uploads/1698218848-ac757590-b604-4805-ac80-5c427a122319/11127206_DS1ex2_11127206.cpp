// 11127206 �����|
#include <iostream>
using namespace std;

class Postfixer {
public:
    struct Node {
        string data;
        Node* next;

        Node(const string& value) {
            data = value;
            next = NULL;
        }
    };

    Postfixer() {
        top = NULL;
    }//constructor

    ~Postfixer() {
        cleanup(top);
    }//destructor

    bool isDigit(char x) {
        return x >= '0' && x <= '9';
    }

    int precedence(char op) {
      if (op == '+' || op == '-') {
        return 1;
      }
      else if (op == '*' || op == '/') {
        return 2;
      }
      return 0;
    }
 bool isValid(const string& expression) {
    Stack parentheses;
    int operatornum = 0;
    int operandnum = 0;
    bool lastWasOperator = true;
    bool error = false;
    char lastOperator = '\0';
    bool lastWasDivision = false;
    bool numAfter = false;

    for (size_t i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if (c != ' ' && c != '(' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/') {
            if (!isDigit(c)) {
                cout << "Error: " << c << " is not a legitimate character." << endl;
                error = true;
                return false;
            }
        }
        if (c == ' ') {
            continue;
        }
        else if (isDigit(c)) {
            if (lastWasOperator) {
                operandnum++;//�e���O+-*/�~�O�ާ@��
                lastWasOperator = false;
            }
            if (lastWasDivision && c == '0') {
                cout << "Error4: division by zero." << endl;
                error = true;
                return false;
            }
            if ( numAfter ) {
                cout << "Error3: there is one extra operand." << endl;
                error = true;
                numAfter = false;
                return false;
            }

            lastWasDivision = false;//���m
        }
        else if (c == '(') {
            numAfter = false;
            if (!lastWasOperator && lastOperator != '(' && lastOperator != ')' ) {
                cout << "Error3: there is one extra operand." << endl;
                error = true;
                return false;
            }// �Ҧp2(2+3)
            while (expression[i] == ' ') {
                i++;
            }
            if (i < expression.size() - 1 && expression[i + 1] == ')') {
                cout << "Error3: it is not infix in the parentheses." << endl;
                error = true;
                return false;
            }//�Ҧp()
            if (i < expression.size() - 1 && ( expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' ||  expression[i + 1] == '-' || expression[i + 1] == '/' ) ){
                cout << "Error3: it is not infix in the parentheses." << endl;
                error = true;
                return false;
            }//(+)

            while (expression[i+1] == ' ') {
                i++;
            }//�Ȧ��ťդz�Z
            if (i < expression.size() - 1 && ( expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' ||  expression[i + 1] == '-' || expression[i + 1] == '/' ) ){
                cout << "Error3: it is not infix in the parentheses." << endl;
                error = true;
                return false;
            }//(+)
            Node* node = new Node(string(1, c));
            parentheses.push(node);
            lastWasOperator = true;
        }
        else if (c == ')') {
          numAfter = true;
          if (parentheses.isEmpty()) {
            cout << "Error2: there is one extra close parenthesis." << endl;
            error = true;
            return false;
          }
          else {
            Node* top = parentheses.top;
            if (top->data[0] == '(') {
              size_t pre = i - 1;
              while (pre > 0 && expression[pre] == ' ') {
                pre--;
              }
              if (!isDigit(expression[pre]) && expression[pre] != ')' && expression[pre] != '(') {
                cout << "Error3: it is not infix in the parentheses." << endl;
                error = true;
                return false;
              }
              lastWasOperator = false;
              lastOperator = ')';
              delete parentheses.pop();
            }
          }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
          numAfter = false;
          operatornum++;
          lastOperator = c;
          if (operatornum > operandnum) {
            cout << "Error3: there is one extra operator." << endl;
            error = true;
            return false;
          }//2++3
          if (c == '/') {
            lastWasDivision = true;
          } // �ΨӧP�_�U�@�ӬO���O0��
          lastWasOperator = true;
          if (i == expression.size() - 1) {
            cout << "Error3: there is one extra operator.2" << endl;
            error = true;
            return false;
          }//2++

}

    }

    if (!parentheses.isEmpty()) {
        cout << "Error2: There is one extra open parenthesis." << endl;
        error = true;
    }//�p�G�t�����A���k�A���٦��Ѫ��ܥN���h


    if (!error) {
        cout << "it is a legitimate infix expression." << endl;
    }

    return !error;
}






    Node* infixToPostfix(const string& expression) {
        Stack operatorStack;
        Stack postfixList;
        string currentOperand;

        for (size_t i = 0; i < expression.size(); i++) {
            char c = expression[i];

            if (c == ' ') {
                continue;
            }
            else if (isDigit(c)  ){
                currentOperand += c;
            }
            else {
                if (!currentOperand.empty()) {
                    Node* operandNode = new Node(currentOperand);
                    postfixList.push(operandNode);
                    currentOperand.clear();
                }

                if (c == '(') {
                    Node* node = new Node(string(1, c));// �Ыؤ@��Node ��H���l�Ƭ� c
                    operatorStack.push(node);
                }
                else if (c == ')') {
                    while (!operatorStack.isEmpty() and operatorStack.top->data[0] != '(') {
                        postfixList.push(operatorStack.pop());
                    }
                    if (!operatorStack.isEmpty() and operatorStack.top->data[0] == '(') {
                        delete operatorStack.pop();
                    }
                }
                else if (c == '+' or c == '-' or c == '*' or c == '/') {
                    while (!operatorStack.isEmpty() and precedence(operatorStack.top->data[0]) >= precedence(c)) {
                        postfixList.push(operatorStack.pop());
                    }
                    Node* node = new Node(string(1, c));
                    operatorStack.push(node);
                }
            }
        }

        if (!currentOperand.empty()) {
            Node* operandNode = new Node(currentOperand);
            postfixList.push(operandNode);
        }

        while (!operatorStack.isEmpty()) {
            postfixList.push(operatorStack.pop());
        }//�H�Wif & while�T�O�������ܦ���ǤF

        return postfixList.pop();
    }

    void cleanup(Node* node) {
        while (node) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }

private:
    struct Stack {
        Node* top;

        Stack() {
            top = NULL;
        }

        void push(Node* node) {
            if (node) {
                node->next = top;
                top = node;
            }
        }

        Node* pop() {
            if (top == NULL) {
                return NULL;
            }
            Node* node = top;
            top = top->next;
            return node;
        }

        bool isEmpty() {
            return top == NULL;
        }
    };

    Node* top;
};

int main() {
    Postfixer p;

    while (true) {
        string input;
        cout << "* Arithmetic Expression Evaluator *\n";
        cout << "* exit. QUIT                      *\n";
        cout << "* 1. Infix2postfix Transformation *\n";
        cout << "***********************************\n";
        cout << "Input(exit/1): ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        if (input == "1") {
            cout << "Enter an infix expression: ";
            getline(cin, input);
            if (p.isValid(input)) {
                Postfixer::Node* postfix = p.infixToPostfix(input);
                Postfixer::Node* reversedPostfix = NULL;

                while (postfix) {
                    Postfixer::Node* temp = new Postfixer::Node(postfix->data);
                    temp->next = reversedPostfix;
                    reversedPostfix = temp;
                    postfix = postfix->next;
                }

                bool first = true;

                while (reversedPostfix) {
                    if (!first) {
                        cout << ", ";
                    }
                    cout << reversedPostfix->data;
                    Postfixer::Node* temp = reversedPostfix;
                    reversedPostfix = reversedPostfix->next;
                    delete temp;
                    first = false;
                }
                cout << endl;
            }
        }
        else cout << "Command does not exist!"<< endl;
        cout << endl;
    }

    return 0;
}
