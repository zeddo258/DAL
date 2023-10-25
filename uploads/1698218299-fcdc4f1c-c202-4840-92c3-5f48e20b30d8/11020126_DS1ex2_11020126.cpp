// 電資三 11020126 鄭祐昀
// 使用C++11

#include <iostream>
#include <cstring>
#include "DS1ex2.h"
using namespace std;

// Print the menu and read in the command and handle the case where the command is wrong
void GetCommand(int &command)
{
    while (true) {
        cout << "\n";
        cout << "* Arithmetic Expression Evaluator *\n";
        cout << "* 0. Quit                         *\n";
        cout << "* 1. Infix Validation             *\n";
        cout << "* 2. Infix2postfix Transformation *\n";
        cout << "***********************************\n";
        cout << "Input a command(0, 1, 2): ";
        cin >> command;

        // If the command is valid, exit the loop
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nCommand does not exist!\n";
            continue;
        }
        if (command >= 0 && command <= 2) {
            break;
        } else {
            cout << "\nCommand does not exist!" << "\n";
        }
    }
}

bool isOperator(char c)
{
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

bool isNumber(char c)
{
    return c >= '0' && c <= '9';
}

bool isBalanceParenthesis(const string &inorder)
{
    Stack s;
    for (char c : inorder) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.isEmpty())
                return false;
            s.pop();
        }
    }

    return s.isEmpty();
}

// Check if there's any syntax error with the equation
bool checkInorder(const string &inorder) 
{
    Stack s;
    // bool hasOperand = false;
    bool needOperand = true;

    for (size_t i = 0; i < inorder.length(); i++) {
        if (inorder[i] == ' ') continue;
        
        if (inorder[i] >= '0' && inorder[i] <= '9') {
            if (!needOperand) {
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            // Skip the full number
            while (i < inorder.length() && inorder[i] >= '0' && inorder[i] <= '9') {
                i++;
            }
            i--; // Go back one character as for loop will make i++
            // hasOperand = true;
            needOperand = false;
        } else if (inorder[i] == '+' || inorder[i] == '-' || inorder[i] == '*' || inorder[i] == '/') {
            if (needOperand) {
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            }
            needOperand = true;
        } else if (inorder[i] == '(') {
            if (!needOperand) {
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            s.push(inorder[i]);
        } else if (inorder[i] == ')') {
            if (needOperand) {
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            }
            
            if (s.isEmpty() || s.peek() != '(') {
                cout << "Error 2: there is one extra close parenthesis." << endl;
                return false;
            }
            s.pop();
        } else {
            cout << "Error 1: " << inorder[i] << " is not a legitimate character." << endl;
            return false;
        }
    }

    if (needOperand) {
        cout << "Error 3: there is one extra operator." << endl;
        return false;
    }

    if (!s.isEmpty()) {
        cout << "Error 2: there is one extra open parenthesis." << endl;
        return false;
    }

    return true;
}

int getOperatorWeight(char operatorSymbol)
{
    switch (operatorSymbol) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

bool hasHigherPrecedence(char operator1, char operator2)
{
    int operator1Weight = getOperatorWeight(operator1);
    int operator2Weight = getOperatorWeight(operator2);

    return operator1Weight >= operator2Weight;
}

List infixToPostfix(string infix)
{
    Stack s;
    List postfix;
    size_t i = 0;
    while (i < infix.size()) {
        if (infix[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(infix[i])) {
            string operand;
            while (i < infix.size() && isdigit(infix[i])) {
                operand += infix[i];
                i++;
            }
            postfix.append(operand);
            continue;
        }

        if (isOperator(infix[i])) {
            while (!s.isEmpty() && s.peek() != '(' && hasHigherPrecedence(s.peek(), infix[i])) {
                postfix.append(s.peek());
                s.pop();
            }
            s.push(infix[i]);
            i++;
            continue;
        }

        if (infix[i] == '(') {
            s.push(infix[i]);
            i++;
            continue;
        }

        if (infix[i] == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix.append(s.peek());
                s.pop();
            }
            s.pop();
            i++;
            continue;
        }

        i++;
    }

    while (!s.isEmpty()) {
        postfix.append(s.peek());
        s.pop();
    }

    return postfix;
}

int main()
{
    int command;
    string inorder;

    do {
        GetCommand(command);
        switch (command) {
            case 0:
                break;
            case 1:
                cout << "Input: ";
                cin.ignore();
                getline(cin, inorder);
                if (checkInorder(inorder)) {
                    cout << "It is a legitimate infix expression." << '\n';
                }
                break;
            case 2:
                cout << "Input: ";
                cin.ignore();
                getline(cin, inorder);
                if (checkInorder(inorder)) {
                    List postfix = infixToPostfix(inorder);
                    cout << "Postfix expression: ";
                    postfix.printList();
                }
                break;
        }
    } while (command != 0);

    return 0;
}
