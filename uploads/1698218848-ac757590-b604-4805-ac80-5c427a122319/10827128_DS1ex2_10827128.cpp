/*----------------百10827128 林鑫宏-----------------*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
public:
    string value;
    Node *next;

    Node(const string &val) : value(val), next(nullptr) {}
};

class Stack
{
private:
    Node *top;

public:
    Stack() : top(nullptr) {}

    void push(const string &val)
    {
        Node *newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    string pop()
    {
        if (isEmpty())
        {
            return "";
        }

        Node *temp = top;
        string val = temp->value;
        top = top->next;
        delete temp;
        return val;
    }

    string peek()
    {
        if (isEmpty())
        {
            return "";
        }
        return top->value;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }
};

int ErrorType = 0;

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperator(const string &str)
{
    return str == "+" || str == "-" || str == "*" || str == "/";
}

bool isNumber(char c)
{
    return c >= '0' && c <= '9';
}

int stringToConstant(const string &str)
{
    return stoi(str);
}

bool handleError(int errorCode, const string &errorOp)
{
    switch (errorCode)
    {
    case 1:
        cout << "Error 1: a is not a legitimate character." << endl;
        return true;
    case 2:
        cout << "Error 2: there is one extra open parenthesis." << endl;
        return true;
    case 3:
        cout << "Error 2: there is one extra close parenthesis." << endl;
        return true;
    case 4:
        cout << "Error 3: there is one extra operator." << endl;
        return true;
    case 5:
        cout << "Error 3: there is one extra operand." << endl;
        return true;
    case 6:
        cout << "Error 3: it is not infix in the parentheses." << endl;
        return true;
    case 7:
        cout << "### Error: Divided by ZERO! ###" << endl;
        cout << "### It cannot be successfully evaluated! ###" << endl;
        return true;
    default:
        return false;
    }
}

bool isValidExpression(const string &expression, string &errorOp, int &errorCode)
{
    Stack parenthesesStack;
    int len = expression.length();
    int preType = 0; // 0.没有東西 1.數 2.符 3. (  4. )

    for (int i = 0; i < len; i++)
    {
        char c = expression[i];

        if (c == ' ')
        {
            continue;
        }
        else if (c == '(')
        {
            if (preType == 1 || preType == 4 || (preType == 0 && i > 0 && isNumber(expression[i - 1])))
            {
                errorCode = 5;
                return false;
            }
            parenthesesStack.push(string(1, c));
            preType = 3;
        }
        else if (c == ')')
        {
            if (errorCode != 0)
            {
                errorCode = 6;
                return false;
            }
            else if (parenthesesStack.isEmpty())
            {
                errorCode = 3;
                return false;
            }
            parenthesesStack.pop();
            preType = 4;
        }
        else if (isOperator(c))
        {
            if (preType != 1 && preType != 4)
            {
                errorCode = 4;
                return false;
            }
            preType = 2;
        }
        else if (isNumber(c))
        {
            if (preType == 4)
            {
                errorCode = 5;
                return false;
            }
            preType = 1;
        }
        else
        { /*
          while (i < len && !isdigit(expression[i]) && !isOperator(expression[i]) && expression[i] != '(' && expression[i] != ')' && expression[i] != ' ')
          {
              errorOp.push_back(expression[i]);
              i++;
          }*/
            errorOp.push_back(expression[i]);
            errorCode = 1;
            return false;
        }
    }

    if (!parenthesesStack.isEmpty())
    {
        errorCode = 2;
        return false;
    }
    else if (preType == 2)
    {
        errorCode = 4;
        return false;
    }
    else
        return true;
}

int getPrecedence(char op)
{
    if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '+' || op == '-')
    {
        return 1;
    }
    return 0;
}

vector<string> infixToPostfix(const string &infix)
{
    Stack operators;
    vector<string> postfix;
    int len = infix.length();

    for (int i = 0; i < len; i++)
    {
        char c = infix[i];

        if (c == ' ')
        {
            continue;
        }
        else if (isdigit(c))
        {
            string number;
            while (i < len && isdigit(infix[i]))
            {
                number += infix[i];
                i++;
            }
            i--;
            postfix.push_back(number);
        }
        else if (c == '(')
        {
            operators.push(string(1, c));
        }
        else if (c == ')')
        {
            while (!operators.isEmpty() && operators.peek() != "(")
            {
                postfix.push_back(operators.pop());
            }
            operators.pop();
        }
        else if (isOperator(c))
        {
            while (!operators.isEmpty() && operators.peek() != "(" && getPrecedence(operators.peek()[0]) >= getPrecedence(c))
            {
                postfix.push_back(operators.pop());
            }
            operators.push(string(1, c));
        }
    }

    while (!operators.isEmpty())
    {
        postfix.push_back(operators.pop());
    }

    return postfix;
}

int evaluatePostfix(const vector<string> &postfix, int &errorCode)
{
    Stack operands;

    for (const string &element : postfix)
    {
        if (!isOperator(element))
        {
            operands.push(element);
        }
        else
        {
            int operand2 = stoi(operands.pop());
            int operand1 = stoi(operands.pop());

            if (element == "+")
            {
                operands.push(to_string(operand1 + operand2));
            }
            else if (element == "-")
            {
                operands.push(to_string(operand1 - operand2));
            }
            else if (element == "*")
            {
                operands.push(to_string(operand1 * operand2));
            }
            else if (element == "/")
            {
                if (operand2 == 0)
                {
                    errorCode = 5;
                    return 0;
                }
                operands.push(to_string(operand1 / operand2));
            }
        }
    }

    return stoi(operands.pop());
}

int main()
{
    int task = -1;
    while (true)
    {
        string errorOp;
        int errorCode = 0;
        string expression;
        cout << "\n* Arithmetic Expression Evaluator *\n";
        cout << "* 0. QUIT                         *\n";
        cout << "* 1. Infix2postfix Transformation *\n";
        cout << "***********************************\n";
        cout << "Input a choice(0, 1): ";
        task = -1;
        cin >> task;
        if (cin.fail())
        {
            cout << "\nCommand does not exist!\n";
            int c;
            cin.clear();
            while ((c = cin.get()) != '\n' && c != EOF)
            {
                continue;
            }
        }
        else if (task == 0)
            return 0;
        else if (task == 1)
        {
            cout << "\nInput an infix expression: ";
            cin.ignore();
            getline(cin, expression);

            if (!isValidExpression(expression, errorOp, errorCode))
            {
                handleError(errorCode, errorOp);
            }
            else
            {
                cout << "It is a legitimate infix expression.\n";
                vector<string> postfixVec = infixToPostfix(expression);
                cout << "Postfix expression: ";

                for (auto it = postfixVec.begin(); it != postfixVec.end(); ++it)
                {
                    cout << *it;
                    if (next(it) != postfixVec.end())
                    {
                        cout << ", ";
                    }
                }

                cout << endl;

                // int result = evaluatePostfix(postfixVec, errorCode);

                /*if (!handleError(errorCode, errorOp))
                    cout << "Answer: " << result << endl;*/
            }
        }
        else
            cout << "\nCommand does not exist!\n";
    }
    return 0;
}
