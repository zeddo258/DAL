// 11020117 �L�l�q 
#include <iostream>
#include <cctype>

using namespace std;

// �o��w�q�쵲��C�`�I
struct Node {
    char data;
    Node* next;
};

// �o��w�q���|
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(char value) {
        Node* newNode = new Node{value, top};
        top = newNode;
    }

    char pop() {
        if (!isEmpty()) {
            char value = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return value;
        }
        return '\0';  // �Ű��|�N��^�Ŧr��
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    char peek() const {
        if (!isEmpty()) {
            return top->data;
        }
        return '\0';
    }
};

// �w�q�ƾǹB��l���u���v  */ >> +- 
int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;  // ��L�r���N�������~���B��l
    }
}

// �o��N���ǹB�⦡�ഫ����ǹB�⦡
string infixToPostfix(const char* infixExpression) {
    Stack operatorStack;
    string postfixExpression;

    while (*infixExpression != '\0') {
        char currentChar = *infixExpression;

        if (isdigit(currentChar)) {
            // �Ʀr�����[�J��Ǫ���F��
            while (isdigit(*infixExpression)) {
                postfixExpression += *infixExpression;
                infixExpression++;
            }
            postfixExpression += ", ";
        } else if (currentChar == '(') {
            // ���A��������J���|
            operatorStack.push(currentChar);
            infixExpression++;
        } else if (currentChar == ')') {
            // �k�A���N���|�����ƾǹB��l���[�J��Ǫ�F���A����J�쥪�A������ 
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfixExpression += operatorStack.pop();
                postfixExpression += ", ";
            }
            operatorStack.pop();  // �A�⥪�A���u�X
            infixExpression++;
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // �B��l�B�z
            while (!operatorStack.isEmpty() && getPriority(operatorStack.peek()) >= getPriority(currentChar)) {
                postfixExpression += operatorStack.pop();
                postfixExpression += ", "; //�C�Ӥ����[�W,�M�Ů�
            }
            operatorStack.push(currentChar);
            infixExpression++;
        } else if (currentChar != ' ') {
            // �Y�����X�z���r���@�˿�X���~�T�� 
            cout << "Error: " << currentChar << " is not a legitimate character." << endl;
            return "";
        } else {
            infixExpression++;
        }
    }

    // �N���|���Ѿl���ƾǹB��l�@�Ӥ@�ӥ[�J��Ǫ���F��
    while (!operatorStack.isEmpty()) {
        postfixExpression += operatorStack.pop();
        postfixExpression += ", ";
    }

    // �o��b�̫Ჾ���̫�@�ӳr���M�Ů�
    if (!postfixExpression.empty()) {
        postfixExpression.pop_back();
        postfixExpression.pop_back();
    }

    return postfixExpression;
}

// �o�O�˴����ǹB�⦡�O�_���T���̿��~���禡
bool isValidInfixExpression(const char* expression) {
    Stack parenthesesStack;
    bool operandExpected = true;  // �s�W�ܼƨӰl�ܬO�_�O�X�z���Ʀr�Υ��A��

    while (*expression != '\0') {
        char currentChar = *expression;

        if (isdigit(currentChar)) {
            // �J��Ʀr�A�ˬd�O�_�O�X�z���Ʀr�Υ��A��
            if (!operandExpected) {
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            while (isdigit(*expression)) {
                expression++;
            }
            operandExpected = false;
            continue;
        } else if (currentChar == '(') {
            // �J�쥪�A���A�ˬd�O�_�O�X�z���Ʀr
            if (!operandExpected) {
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            operandExpected = true;
            parenthesesStack.push('(');
        } else if (currentChar == ')') {
            // �J��k�A���A�ˬd�e��O�_���~ ���S�����T�����k�A�� 
            if (operandExpected || parenthesesStack.isEmpty()) {
                cout << "Error 2: there is one extra close parenthesis." << endl;
                return false;
            } else {
                parenthesesStack.pop();
            }
            operandExpected = false;
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // �J��ƾǹB��l�A�ˬd�O�_���~
            if (operandExpected) {
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            }
            char nextChar = *(expression + 1);

            if (nextChar == '\0' || nextChar == ')' || nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/') {
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            }
            operandExpected = true;
        } else if (currentChar != ' ') {
            // �Y�O���X�z���r���o��|�P�_���~ 
            cout << "Error 1: " << currentChar << " is not a legitimate character." << endl;
            return false;
        }

        expression++;
    }

    if (operandExpected || !parenthesesStack.isEmpty()) {
        cout << "Error 2: there is one extra open parenthesis." << endl;
        return false;
    }

    return true;
}

int main() {
    int choice;


   // �o�䦳�@�ӿ�����ϥΪ̨M�w�n�h�X�٬O�}�l����o�ӵ{�� 
    do { 
    	
        cout << "\n* Arithmetic Expression Evaluator *" << endl;
        cout << "* 0. QUIT                         *" << endl;
        cout << "* 1. Infix2postfix Transformation *" << endl;
        cout << "***********************************" << endl;
        cout << "Input a choice(0, 1): ";
        cin >> choice;
        cout << endl;

        cin.ignore();
        
        // �o��P�_�O 1 �٬O 0
        switch (choice) {
            case 1: {
                cout << "Input an infix expression: ";
                string expression;
                getline(cin, expression);

                if (isValidInfixExpression(expression.c_str())) {
                    cout << "It is a legitimate infix expression." << endl; // �Y�o�ӹB�⦡�O���T�����ǹB�⦡ 
                    string postfixExpression = infixToPostfix(expression.c_str()); // �o��N�⤤�ǹB�⦡�ഫ����ǹB�⦡
                    cout << "Postfix expression: " << postfixExpression << endl; // �æb�o���X 
                }

                break;
            }
            case 0:
                // ��J0�N���X�����o�ӵ{�� 
                break;
            default:
                cout << "Command does not exist!\n" << endl; // �����O 0 �άO 1 �����O��J�N��X�o��M�����ϥΪ̦A��J�@�� 
        }

    } while (choice != 0);

    return 0;
}

