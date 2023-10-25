// 11027172 資工三甲 陳港生
#include <iostream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

#define MAX_LEN 256

template <typename T>
class Stack {
private:
    T *data;
    int size;
    int top;
public:
    Stack(int size = 100) {
        this->size = size;
        data = new T[size];
        top = -1;
    }
    ~Stack() {
        delete[] data;
    }
    bool empty() {
        return top == -1;
    }
    bool full() {
        return top == size - 1;
    }
    void push(T x) {
        if (full()) {
            cout << "Stack overflow" << endl;
            return;
        }
        data[++top] = x;
    }
    T pop() {
        if (empty()) {
            cout << "Stack underflow" << endl;
            return T();
        }
        return data[top--];
    }
    T getTop() {
        if (empty()) {
            cout << "Stack underflow" << endl;
            return T();
        }
        return data[top];
    }
};

int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

string infixToPostfix(const string &infix) {
    string postfix;
    Stack<char> operators;

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == ' ') {
            continue;
        } else if (isdigit(infix[i])) {
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix += infix[i];
                i++;
            }
            postfix += ',';
            i--;
        } else if (infix[i] == '(') {
            operators.push(infix[i]);
        } else if (infix[i] == ')') {
            while (!operators.empty() && operators.getTop() != '(') {
                postfix += operators.getTop();
                postfix += ',';
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();
            }
        } else {
            while (!operators.empty() && operators.getTop() != '(' && getPrecedence(operators.getTop()) >= getPrecedence(infix[i])) {
                postfix += operators.getTop();
                postfix += ',';
                operators.pop();
            }
            operators.push(infix[i]);
        }
    }

    while (!operators.empty()) {
        postfix += operators.getTop();
        postfix += ',';
        operators.pop();
    }

    // Remove trailing comma if it exists
    if (!postfix.empty() && postfix.back() == ',') {
        postfix.pop_back();
    }

    return postfix;
}

bool isExp(const string &exp) {
    for (char c : exp) {
        if (c != '.' && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' && c != ' ' && !isdigit(c)) {
            cout << "Error 1: " << c << " is not a legitimate character." << endl;
            return false;
        }
    }
    for (int i = 1; i < exp.length(); i++) {
        if (isdigit(exp[i])) {
            if (exp[i - 1] == ')') {
                cout << "Error 3: there is one extra operand."  << endl;
                return false;
            }
        
        }
    }
    return true;
}

bool isBlanced(const string &exp) {
    int open = 0;
    int close = 0;
    for (char c : exp) {
        if (c == '(') {
            open++;
        } else if (c == ')' && open > close) {
            close++;
        }
    }
    int count = open - close;
    if (count < 0) {
        cout << "Error 2: there is " << -count << " extra open parentheses." << endl;
    }
    if (count > 0) {
        cout << "Error 2: there is " << count << " extra close parentheses." << endl;
    }
    return count == 0;
}

bool isLegal(const string &exp) {
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == ' ') {
            continue;
        } else if (isdigit(exp[i])) {
            while (i < exp.length() && (isdigit(exp[i]) || exp[i] == '.')) {
                i++;
            }
            i--;
        } else if (exp[i] == '(') {
            if (i + 1 < exp.length() && exp[i + 1] == ')') {
                cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }
        } else if (exp[i] == ')') {
            if (i - 1 >= 0 && exp[i - 1] == '(') {
                cout << "Error 3: there is no operator between parentheses." << endl;
                return false;
            }
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            if (i + 1 < exp.length() && (exp[i + 1] == '+' || exp[i + 1] == '-' || exp[i + 1] == '*' || exp[i + 1] == '/')) {
                cout << "Error 3: there is one extra operator."  << endl;
                return false;
            }else if (i == 0){
                cout << "Error 3: there is one extra operator."  << endl;
                return false;
            }        
        } else {
            cout << "Error 1: " << exp[i] << " is not a legitimate character." << endl;
            return false;
        }
    }
    return true;
}

int main(void) {
    int command = 0;
    do {
        cout << endl << "Arithmetic Expression Evaluator" ;
        cout << endl << "0. Quit" ;
        cout << endl << "1. Infix to Postfix Transformation" ;
        cout << endl << "*******************************" ;
        cout << endl << "Input a choice (0,1) : " ;
        cin >> command ;
        cin.ignore(MAX_LEN, '\n');
        switch (command)
        {
        case 0: 
            break;
        
        case 1: string infix;
            cout << endl << "Input an infix expression : " ;
            getline(cin, infix);
            if (isExp(infix) && isBlanced(infix) && isLegal(infix)) {
                string postfix = infixToPostfix(infix);
                cout << "Postfix: " << postfix << endl;
            }
            break;
        }
    } while (command != 0);
}
