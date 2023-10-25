//********************************************************************************/
// Exercise 02: Infix2Postfix & Postfix Evaluator by 10827142 2023/10
//********************************************************************************/
// This is the NO LIST version. You MUST rewrite it by using a linked list!
//********************************************************************************/
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Token {
   public:
    char symbol;
    int number;
    Token() {
        symbol = '\0';
        number = 0;
    }
};

template <typename T>
class Stack {
   private:
    vector<T> stack;

   public:
    bool isEmpty() {
        return stack.empty();
    }

    int size() {
        return stack.size();
    }

    T top() {
        if (stack.size() == 0) {
            throw exception();
        }

        return stack.back();
    }

    void push(const T& value) {
        stack.push_back(value);
    }

    void pop() {
        if (stack.size() == 0) {
            throw exception();
        }

        stack.pop_back();
    }
};

class Linked_list {
   private:
    class Node {
       public:
        Token token;
        Node* next;
        Node() {
            next = nullptr;
        }
    };
    Node *head, *tail;
    int list_size;

   public:
    Linked_list() {
        head = nullptr;
        tail = nullptr;
        list_size = 0;
    }

    int size() const {
        return list_size;
    }

    void push_back(const Token& node) {
        Node* new_node = new Node;
        new_node->token = node;
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        list_size++;
    }

    class iterator {
        Node* current_node;

       public:
        iterator(Node* node) : current_node(node) {}

        iterator& operator++() {
            current_node = current_node->next;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return current_node != other.current_node;
        }

        bool operator==(const iterator& other) const {
            return current_node == other.current_node;
        }

        const Token& operator*() const {
            return current_node->token;
        }
    };

    iterator begin() const {
        return iterator(head);
    }

    iterator end() const {
        return iterator(nullptr);
    }
};

class Expression {
   private:
    void input_line_to_infix(const string& input_line) {
        string buffer;
        for (auto current : input_line) {
            if (current >= '0' && current <= '9') {
                buffer += current;
            } else {
                if (buffer.size() > 0) {
                    Token token;
                    token.number = stoi(buffer);
                    infix.push_back(token);
                    buffer = "";
                }
                if (current == '+' || current == '-' || current == '*' || current == '/' || current == '(' || current == ')') {
                    Token token;
                    token.symbol = current;
                    infix.push_back(token);
                } else if (current != ' ' and current != '\t') {
                    stringstream error_msg;
                    error_msg << "Error 1: " << current << " is not a legitimate character.";
                    throw runtime_error(error_msg.str());
                }
            }
        }

        if (buffer.size() > 0) {
            Token token;
            token.number = stoi(buffer);
            infix.push_back(token);
        }
    }

    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

    void infix_to_postfix() {
        Stack<Token> stack;
        Token previous;
        bool init = true;
        for (auto token : infix) {
            if (!init) {
                if (previous.symbol == '\0' && token.symbol == '\0') {
                    throw runtime_error("Error 3: it is not infix in the parentheses.");
                } else if (previous.symbol == '(' && token.symbol == ')') {
                    throw runtime_error("Error 3: it is not infix in the parentheses.");
                } else if (isOperator(previous.symbol) && isOperator(token.symbol)) {
                    throw runtime_error("Error 3: it is not infix in the parentheses.");
                } else if (previous.symbol == '\0' && token.symbol == '(') {
                    throw runtime_error("Error 3: it is not infix in the parentheses.");
                } else if (previous.symbol == '(' && isOperator(token.symbol)) {
                    throw runtime_error("Error 3: it is not infix in the parentheses.");
                } else if (isOperator(previous.symbol) && token.symbol == ')') {
                    throw runtime_error("Error 3: it is not infix in the parentheses.");
                } else if (previous.symbol == ')' && token.symbol == '\0') {
                    throw runtime_error("Error 3: it is not infix in the parentheses.");
                }
            }

            if (token.symbol == '\0') {
                postfix.push_back(token);
            } else {
                if (token.symbol == '(') {
                    stack.push(token);
                } else if (token.symbol == ')') {
                    try {
                        while (stack.top().symbol != '(') {
                            postfix.push_back(stack.top());
                            stack.pop();
                        }
                        stack.pop();
                    } catch (const exception& e) {
                        throw runtime_error("Error 2: there is one extra close parenthesis.");
                    }

                } else {
                    while (!stack.isEmpty() && priority(token) <= priority(stack.top())) {
                        postfix.push_back(stack.top());
                        stack.pop();
                    }

                    stack.push(token);
                }
            }

            previous = token;
            init = false;
        }

        while (!stack.isEmpty()) {
            if (stack.top().symbol == '(') {
                throw runtime_error("Error 2: there is one extra open parenthesis.");
            }
            postfix.push_back(stack.top());
            stack.pop();
        }
    }

    int priority(const Token& token) {
        if (token.symbol == '+' || token.symbol == '-') {
            return 1;
        } else if (token.symbol == '*' || token.symbol == '/') {
            return 2;
        } else {
            return 0;
        }
    }

   public:
    Linked_list infix, postfix;
    double answer;

    Expression(const string& input_line) {
        input_line_to_infix(input_line);
        infix_to_postfix();
        answer = evaluate_postfix();
    }

    double evaluate_postfix() {
        if (postfix.size() == 0) {
            throw runtime_error("### Error: Nothing to calculate! ###");
        }
        Stack<double> stack;
        for (auto token : postfix) {
            if (token.symbol == '\0') {
                stack.push(token.number);
            } else {
                double operand2;
                double operand1;
                try {
                    operand2 = stack.top();
                    stack.pop();
                    operand1 = stack.top();
                    stack.pop();
                } catch (const exception& e) {
                    throw runtime_error("Error 3: there is one extra operand.");
                }

                switch (token.symbol) {
                    case '+':
                        stack.push(operand1 + operand2);
                        break;
                    case '-':
                        stack.push(operand1 - operand2);
                        break;
                    case '*':
                        stack.push(operand1 * operand2);
                        break;
                    case '/':
                        if (operand2 == 0) {
                            stringstream error_msg;
                            error_msg << "### Error: Divided by ZERO! ###" << endl;
                            error_msg << "### It cannot be successfully evaluated! ###";
                            throw runtime_error(error_msg.str());
                        }
                        stack.push(operand1 / operand2);
                        break;
                }
            }
        }

        if (stack.size() != 1) {
            throw runtime_error("Error 3: there is one extra operand.");
        }
        return stack.top();
    }
};

int main() {
    int command = 0;  // 使用者指令
    do {
        cout << "\n* Arithmetic Expression Evaluator *" << endl;
        cout << "* 0. QUIT                         *" << endl;
        cout << "* 1. Infix2postfix Evaluation     *" << endl;
        cout << "***********************************" << endl;
        cout << "Input a choice(0, 1): ";

        cin >> command;
        cin.ignore(255, '\n');
        if (command == 0) {
            break;
        } else if (command == 1) {
            try {
                cout << "\nInput an infix expression: ";
                string input_line;
                getline(cin, input_line);
                Expression expression = input_line;
                cout << "It is a legitimate infix expression." << endl;
                cout << "Postfix expression: ";
                int counter = 0;
                for (auto node : expression.postfix) {
                    if (node.symbol != '\0') {
                        cout << node.symbol;
                    } else {
                        cout << node.number;
                    }
                    if (++counter < expression.postfix.size()) {
                        cout << ", ";
                    }
                }

                cout << endl;
                cout << "Answer: " << expression.answer << endl;
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
    } while (true);
}
