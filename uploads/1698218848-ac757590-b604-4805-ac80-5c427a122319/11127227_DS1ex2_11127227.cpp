// 11127227 王筠翔

#include <iostream>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

struct Profix {
    string element; // 存儲後序式的元素
    Profix* next;
};

// 自定義Stack
template <class T>

class Stack {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* top;

public:
    Stack() {
        top = nullptr; // // 初始化stack
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) { // 創建新節點並儲存資料
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    T pop() { // 取出頂部節點的資料
        if (isEmpty()) {
            cerr << "Error: Stack is empty" << endl;
            exit(1);
        }
        Node* temp = top;
        T value = top->data;
        top = top->next;
        delete temp;
        return value;
    }

    T peek() { // 查看頂部節點的資料
        if (isEmpty()) {
            cerr << "Error: Stack is empty" << endl;
            exit(1);
        }
        return top->data;
    }

    bool isEmpty() { // 檢查堆疊是否為空
        return top == nullptr;
    }
};

// 判斷字符是否為運算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 判斷是否為括號
bool isParenthesis(char c) {
    return c == '(' || c == ')';
}

// 運算符號的優先級
int getPrecedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

// 判斷是否為正確字符
bool isExp(string infix) {
    for (char c : infix) {
        if (c != '+' && c != '-' && c != '*' && c != '/') {
            if (!isdigit(c) && c != ' ' && c != '(' && c != ')') {
                cout << "Error 1: " << c << " is not a legitimate character." << endl;
                return false;
            }
        }
        else if (c == ' ') {
            continue; // 如果字符是空格，則略過不處理
        }
    }
    return true;
}

// 判斷括號是否成對
bool isBalanced(string infix) {
    Stack<char> parenthesesStack;

    for (char c : infix) {
        if (c == ' ') {
            continue; // 如果字符是空格，則略過不處理
        }
        else if (c == '(') {
            parenthesesStack.push(c);
        }
        else if (c == ')') {
            if (parenthesesStack.isEmpty()) { // 有多餘的右括號
                cerr << "Error 2: there is one extra close parenthesis." << endl;
                return false;
            }
            else {
                parenthesesStack.pop();
            }
        }

    }

    if (!parenthesesStack.isEmpty()) { // 有多餘的左括號
        cerr << "Error 2: there is one extra open parenthesis." << endl;
        return false;
    }

    return true;
}

// 判斷是否為中序運算式
bool isLegal(string infix) {
    char lastChar = ' '; // 用於跟蹤上一個字符是否是運算子或數字，初始狀態為空
    bool lastWasOperatorOrSpace = true; // 用於跟蹤上一個字符是否是運算子或空格，初始狀態為真
    bool insideParentheses = false; // 標誌來表示是否在括號内

    if (isOperator(infix[0])) { // 第一個字符是運算符號
        cout << "Error 3: there is one extra operator." << endl;
        return false;

    }
    if (infix.empty()) { // 若infix為空
        cout << "Error 3: there is one extra operator." << endl;
        return false;

    }

    for (char c : infix) {
        if (c == ' ') {
            continue; // 如果字符是空格，則略過不處理
        }
        else if (isdigit(c)) {
            if (lastChar == ')') { // ex:")9"
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            if (c == '0' && lastChar == '/') {
                cout << "The divisor cannot be zero." << endl;
                return false;
            }

            lastWasOperatorOrSpace = false;
        }
        else if (c == '(') {
            if (isdigit(lastChar)) { // ex:"9("
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            else if (lastChar == ')') { // ex:")("
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }

            lastWasOperatorOrSpace = true;
            insideParentheses = true;
        }
        else if (c == ')') {
            if (isOperator(lastChar)) { // ex:"+)"
                cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }

            if (lastChar == '(') { // ex:"()"
                cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }

            lastWasOperatorOrSpace = false;
            insideParentheses = false;
        }
        else if (isOperator(c)) {
            if (isOperator(lastChar) && insideParentheses) { // (1++1)
                cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }
            if (isOperator(lastChar)) { // 1++1
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            }
             if (lastChar == '(') { // (+
                cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }
            lastWasOperatorOrSpace = true;
        }

        lastChar = c; // 更新上一個字符

    } // for

    if (isOperator(lastChar)) { // 最後一個字符是運算符號
        cout << "Error 3: there is one extra operator." << endl;
        return false;

    }


    return true ;

}


// 將中序式轉為後序式
Profix* infixToPostfix(string infixExpression) {
    Stack<char> operatorStack;
    Profix* postfixHead = nullptr; // 後序式的頭
    Profix* postfixTail = nullptr; // 後序式的尾端
    char lastChar; // 用於跟蹤上一個字符
    string operand; // 用來儲存完整操作數
    bool lastWasOperatorOrSpace = true; // 用於跟蹤上一個字符是否是運算子或空格，初始狀態為真
    int i = 0, a = 0;

    for (char c : infixExpression) {
        i++ ;
        if (c == ' ') { // 如果字符是空格，則略過不處理
            continue;
        }
        else if (isdigit(c)) { // 如果字符是數字
            operand += c ;
            if (i == infixExpression.length()) { // 如果當前位置為最後一位，就將操作數加入postfixHead
                Profix* newNode = new Profix;
                newNode->element = operand;
                newNode->next = nullptr;
                if (postfixTail == nullptr) {
                    postfixHead = newNode;
                    postfixTail = newNode;
                }
                else {
                    postfixTail->next = newNode;
                    postfixTail = newNode;
                }

                lastWasOperatorOrSpace = false;
            }
        } // else if (isdigit(c))

        else {
            if (isdigit(lastChar)) { // 若前一位是數字，代表此操作數已完整
                    Profix* newNode = new Profix;
                    newNode->element = operand;
                    newNode->next = nullptr;
                    if (postfixTail == nullptr) {
                        postfixHead = newNode;
                        postfixTail = newNode;
                    }
                    else {
                        postfixTail->next = newNode;
                        postfixTail = newNode;
                    }

                    lastWasOperatorOrSpace = false;
                    operand.clear();

            }

            if (c == '(') { // 如果字符是左括號則放入stack
                operatorStack.push(c);
                lastWasOperatorOrSpace = true;
            }


            if (c == ')') { // 如果字符是右括號則檢查stack
                while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                    char op = operatorStack.pop();
                    Profix* newNode = new Profix;
                    newNode->element = op;
                    newNode->next = nullptr;
                    if (postfixTail == nullptr) {
                        postfixHead = newNode;
                        postfixTail = newNode;
                    }
                    else {
                        postfixTail->next = newNode;
                        postfixTail = newNode;
                    }
                }
                operatorStack.pop(); // Pop '('
                lastWasOperatorOrSpace = false;
            } // if (c == ')')

            if (isOperator(c)) { // 如果字符是運算符號
                if (operatorStack.isEmpty()) {
                    operatorStack.push(c);
                }
                else { // 處理不同優先順序的運算子

                    while (!operatorStack.isEmpty() && operatorStack.peek() != '(' &&
                            getPrecedence(c) <= getPrecedence(operatorStack.peek())) {
                           //堆疊頂部的運算子優先順序大於或等於當前運算子 c 的優先順序
                        char op = operatorStack.pop();
                        Profix* newNode = new Profix;
                        newNode->element = op;
                        newNode->next = nullptr;
                        if (postfixTail == nullptr) {
                            postfixHead = newNode;
                            postfixTail = newNode;
                        }
                        else {
                            postfixTail->next = newNode;
                            postfixTail = newNode;
                        }
                    }
                    operatorStack.push(c);
                }

            } // if (isOperator(c))


        } // else


        lastChar = c ; // 更新上一個字符

    }

    // 處理剩餘的運算子
    while (!operatorStack.isEmpty()) {
        char op = operatorStack.pop();
        Profix* newNode = new Profix;
        newNode->element = op;
        newNode->next = nullptr;
        if (postfixTail == nullptr) {
            postfixHead = newNode;
            postfixTail = newNode;
        }
        else {
            postfixTail->next = newNode;
            postfixTail = newNode;
        }
    }


    // 用逗號隔開每個運算源和運算子
    Profix* current = postfixHead;
    while (current != nullptr) {
        if (isOperator(current->element[0]) || isdigit(current->element[0])) {
            if (current->next != nullptr) {
                current->element += ", ";
            }
        }
        current = current->next;
    }

    return postfixHead;

} // infixToPostfix()


int main() {
    string infixExpression;
    int command = 0;
    char enter;
    cout << endl << "* Arithmetic Expression Evaluator *";
    cout << endl << "* 0. QUIT                         ";
    cout << endl << "* 1. Infix2postfix Transformation  ";
    cout << endl << "*******************************";
    cout << endl << "Input a choice (0, 1): ";
    cin >> command;
    cin.ignore(numeric_limits <streamsize>::max(), '\n'); // 清除輸入流中的換行符

    while (command != 0) {
        if (command == 1) {
            cout << "Enter an infix expression: ";
            getline(cin, infixExpression);

            if (isExp(infixExpression) && isBalanced(infixExpression) && isLegal(infixExpression)) {
                cout << "It is a legitimate infix expression." << endl;
                Profix* postfixExpression = infixToPostfix(infixExpression);
                cout << "Postfix expression: ";
                Profix* current = postfixExpression;
                while (current != nullptr) {
                    cout << current->element;
                    current = current->next;
                }
                cout << endl;
                // 釋放內存
                while (postfixExpression != nullptr) {
                    Profix* temp = postfixExpression;
                    postfixExpression = postfixExpression->next;
                    delete temp;
                }

            }
        }
        else {
            cout << "Command does not exist!" << endl;
        }

        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         ";
        cout << endl << "* 1. Infix2postfix Transformation  ";
        cout << endl << "*******************************";
        cout << endl << "Input a choice (0, 1): ";
        cin >> command;
        cin.ignore(numeric_limits <streamsize>::max(), '\n');
    }

    return 0;
}
