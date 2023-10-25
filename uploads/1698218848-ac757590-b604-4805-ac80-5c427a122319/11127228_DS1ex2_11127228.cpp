//11127228  周義庭
#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
};

struct CharNode {
    char data;
    CharNode* next;
};

// Define a stack data structure for characters.
struct MyStack {
    CharNode* top;

    MyStack() {
        top = nullptr;
    }

    // Push a character onto the stack.
    void push(char c) {
        CharNode* newNode = new CharNode;
        newNode->data = c;
        newNode->next = top;
        top = newNode;
    }

    // Pop the top character from the stack.
    void pop() {
        if (top != nullptr) {
            CharNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Get the top character of the stack.
    char Top() {
        if (top != nullptr) {
            return top->data;
        }
        return '\0';
    }

    // Check if the stack is empty.
    bool isEmpty() {
        return top == nullptr;
    }
};

// Function to check the validity of each symbol.
bool isExp(string &str);

// Function to check if parentheses in the string are balanced.
bool isBalanced(const string str);

// Function to check if the input string is a legal expression.
bool isLegal(const string str);

// Function to parse a string into a linked list.
Node* str2list(const string str);

// Function to transform infix into postfix
Node* infix2postfix(Node* head);

// Function to push a node onto a linked list.
Node* pushNode(Node* &head, Node* &tail, string data);

int main() {
    int command = 0;

    do {
        string infixS;

        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         *";
        cout << endl << "* 1. Infix2postfix Transformation *";
        cout << endl << "***********************************";
        cout << endl << "Input a choice (0, 1): ";
        cin >> command;
        cin.ignore();

        if (command == 0)
            break;
        else if (command == 1) {
            cout << endl << "Input an infix expression: ";
            getline(cin, infixS);

            if (isExp(infixS) && isBalanced(infixS) && isLegal(infixS)) {
                cout << "It is a legitimate infix expression.";

                Node* linkedList = str2list(infixS);
                Node* postfix = infix2postfix(linkedList);

                cout << endl << "Postfix expression: ";
                Node* temp = postfix;
                while (temp != nullptr) {
                    if (temp -> next != nullptr)
                        cout << temp -> data << ",";
                    else
                        cout << temp -> data;
                    temp = temp -> next;
                }
                cout << endl;

                delete linkedList;
                delete postfix;
            }
        }
        else
            cout << endl << "Command does not exist!" << endl;

    } while (true);

    return 0;
}

// Function to check the validity of each symbol.
bool isExp(string &str) {
    string temp = "";

    for (char c : str) {
        if (c == ' ') {
            continue;
        }

        if (c != '(' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/') {
            if (!isdigit(c)) {
                cout << "Error 1: " << c << " is not a legitimate character." << endl;
                return false;
            }
        }

        temp += c;
    }

    str = temp;
    return true;
}

// Function to check if parentheses in the string are balanced.
bool isBalanced(const string str) {
    int numL = 0, numR = 0;

    for (char c : str){
        if (c == '(')
            numL++;

        else if (c == ')')
            numR++;

        if (numL < numR) {
            cout << "Error 2: there is one extra close parenthesis." << endl;
            return false;
        }
    }

    if (numL != numR) {
        cout << "Error 2: there is one extra close parenthesis." << endl;
        return false;
    }

    return true;
}

// Function to check if the input string is a legal expression.
bool isLegal(const string str) {
    bool isLegal = true;

    char firstChar = str[0];
    if ((firstChar == '+' || firstChar == '-' || firstChar == '*' || firstChar == '/')) {
        cout << "Error 3: there is one extra operator." << endl;
        return false;
    }

    for (int i = 0; i < str.length() - 1; i++) {

        char currentChar = str[i];
        char nextChar = str[i + 1];

        if (isdigit(currentChar)) {
            if (!(isdigit(nextChar) || nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/' || nextChar == ')')) {
                isLegal = false;
            }
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            if (!(isdigit(nextChar) || nextChar == '(')) {
                isLegal = false;
            }
        }
        else if (currentChar == '(') {
            if (!(isdigit(nextChar) || nextChar == '(')) {
                isLegal = false;
            }
        }
        else if (currentChar == ')') {
            if (!(nextChar == '+' || nextChar == '-' || nextChar == '*' || nextChar == '/' || nextChar == ')')) {
                isLegal = false;
            }
        }

        if (!isLegal) {
            cout << "Error 3: it is not infix in the parentheses." << endl;
            return false;
        }
    }

    char lastChar = str[str.length() - 1];
    if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/' || lastChar == '(') {
        cout << "Error 3: there is one extra operator." << endl;
        return false;
    }

    return true;
}

// Function to parse a string into a linked list.
Node* str2list(const string str) {
    int i = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

    while (i < str.length()) {
        string temp = "";

        if (isdigit(str[i])) {
            while (i < str.length() && isdigit(str[i])) {
                temp += str[i];
                i++;
            }
        }
        else {
            temp += str[i];
            i++;
        }

        if (!temp.empty()) {
            pushNode(head, tail, temp);
        }
    }

    return head;
}

// Function to transform infix into postfix
Node* infix2postfix(Node* inorderHead) {
    MyStack operators;// Create a stack to hold operators.
    Node* head = nullptr;
    Node* tail = nullptr;

    Node* current = inorderHead;
    while (current != nullptr) {
        string data = current -> data;

        if (isdigit(data[0])) {
            pushNode(head, tail, data);
        }
        else if (data == "+" || data == "-") {
            while (!operators.isEmpty() && operators.Top() != '(') {
                pushNode(head, tail, string(1, operators.Top()));
                operators.pop();
            }
            operators.push(data[0]);// Push the current operator onto the stack.
        }
        else if (data == "*" || data == "/") {
            while (!operators.isEmpty() && (operators.Top() == '*' || operators.Top() == '/')) {
                pushNode(head, tail, string(1, operators.Top()));
                operators.pop();
            }
            operators.push(data[0]);
        }
        else if (data == "(") {
            operators.push(data[0]);
        }
        else if (data == ")") {
            while (!operators.isEmpty() && operators.Top() != '(') {
                // Pop operators from the stack and add them to the output until a left parenthesis is encountered.
                pushNode(head, tail, string(1, operators.Top()));
                operators.pop();
            }

            if (operators.Top() == '(') {
                operators.pop();
            }
        }

        current = current -> next;
    }

    // After processing all tokens, any remaining operators on the stack should be popped and added to the output.
    while (!operators.isEmpty()) {
        pushNode(head, tail, string(1, operators.Top()));
        operators.pop();
    }

    return head;
}

// Function to push a node onto a linked list.
Node* pushNode(Node* &head, Node* &tail, string data) {
    Node* newNode = new Node;
    newNode -> data = data;
    newNode -> next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail -> next = newNode;
        tail = newNode;
    }
}
