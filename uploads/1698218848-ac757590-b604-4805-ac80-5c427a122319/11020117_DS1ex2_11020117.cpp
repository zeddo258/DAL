// 11020117 林子皓 
#include <iostream>
#include <cctype>

using namespace std;

// 這邊定義鏈結串列節點
struct Node {
    char data;
    Node* next;
};

// 這邊定義堆疊
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
        return '\0';  // 空堆疊就返回空字元
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

// 定義數學運算子的優先權  */ >> +- 
int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;  // 其他字元就視為錯誤的運算子
    }
}

// 這邊將中序運算式轉換為後序運算式
string infixToPostfix(const char* infixExpression) {
    Stack operatorStack;
    string postfixExpression;

    while (*infixExpression != '\0') {
        char currentChar = *infixExpression;

        if (isdigit(currentChar)) {
            // 數字直接加入後序的表達式
            while (isdigit(*infixExpression)) {
                postfixExpression += *infixExpression;
                infixExpression++;
            }
            postfixExpression += ", ";
        } else if (currentChar == '(') {
            // 左括號直接放入堆疊
            operatorStack.push(currentChar);
            infixExpression++;
        } else if (currentChar == ')') {
            // 右括號將堆疊中的數學運算子先加入後序表達式，直到遇到左括號為止 
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfixExpression += operatorStack.pop();
                postfixExpression += ", ";
            }
            operatorStack.pop();  // 再把左括號彈出
            infixExpression++;
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // 運算子處理
            while (!operatorStack.isEmpty() && getPriority(operatorStack.peek()) >= getPriority(currentChar)) {
                postfixExpression += operatorStack.pop();
                postfixExpression += ", "; //每個之間加上,和空格
            }
            operatorStack.push(currentChar);
            infixExpression++;
        } else if (currentChar != ' ') {
            // 若有不合理的字元一樣輸出錯誤訊號 
            cout << "Error: " << currentChar << " is not a legitimate character." << endl;
            return "";
        } else {
            infixExpression++;
        }
    }

    // 將堆疊中剩餘的數學運算子一個一個加入後序的表達式
    while (!operatorStack.isEmpty()) {
        postfixExpression += operatorStack.pop();
        postfixExpression += ", ";
    }

    // 這邊在最後移除最後一個逗號和空格
    if (!postfixExpression.empty()) {
        postfixExpression.pop_back();
        postfixExpression.pop_back();
    }

    return postfixExpression;
}

// 這是檢測中序運算式是否正確哪裡錯誤的函式
bool isValidInfixExpression(const char* expression) {
    Stack parenthesesStack;
    bool operandExpected = true;  // 新增變數來追蹤是否是合理的數字或左括號

    while (*expression != '\0') {
        char currentChar = *expression;

        if (isdigit(currentChar)) {
            // 遇到數字，檢查是否是合理的數字或左括號
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
            // 遇到左括號，檢查是否是合理的數字
            if (!operandExpected) {
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            operandExpected = true;
            parenthesesStack.push('(');
        } else if (currentChar == ')') {
            // 遇到右括號，檢查前後是否有誤 有沒有正確的左右括號 
            if (operandExpected || parenthesesStack.isEmpty()) {
                cout << "Error 2: there is one extra close parenthesis." << endl;
                return false;
            } else {
                parenthesesStack.pop();
            }
            operandExpected = false;
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // 遇到數學運算子，檢查是否有誤
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
            // 若是不合理的字元這邊會判斷錯誤 
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


   // 這邊有一個選單讓使用者決定要退出還是開始執行這個程式 
    do { 
    	
        cout << "\n* Arithmetic Expression Evaluator *" << endl;
        cout << "* 0. QUIT                         *" << endl;
        cout << "* 1. Infix2postfix Transformation *" << endl;
        cout << "***********************************" << endl;
        cout << "Input a choice(0, 1): ";
        cin >> choice;
        cout << endl;

        cin.ignore();
        
        // 這邊判斷是 1 還是 0
        switch (choice) {
            case 1: {
                cout << "Input an infix expression: ";
                string expression;
                getline(cin, expression);

                if (isValidInfixExpression(expression.c_str())) {
                    cout << "It is a legitimate infix expression." << endl; // 若這個運算式是正確的中序運算式 
                    string postfixExpression = infixToPostfix(expression.c_str()); // 這邊就把中序運算式轉換成後序運算式
                    cout << "Postfix expression: " << postfixExpression << endl; // 並在這邊輸出 
                }

                break;
            }
            case 0:
                // 輸入0就跳出結束這個程式 
                break;
            default:
                cout << "Command does not exist!\n" << endl; // 當有不是 0 或是 1 的指令輸入就輸出這行然後讓使用者再輸入一次 
        }

    } while (choice != 0);

    return 0;
}

