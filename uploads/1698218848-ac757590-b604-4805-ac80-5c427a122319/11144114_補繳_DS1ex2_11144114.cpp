#include <string>                                       //string class
#include <cstdlib>                                      //system, atoi
#include <iostream>
#include <algorithm>
#include <cctype>

#define MAX_LEN 255                                     //maximum string length

using namespace std;

bool isExp(const string& input);        //檢查每個符號的有效性
bool isBalanced(const string input);    //檢查括號的有效性
bool isLegal(const string input);       //檢查它是否為合法的表達式
//void str2list();                      //將字串解析為鍊錶
//bool infix2postfix();                 //將中序轉換為後序

int main(void)
{
    int command = 0;                                    //user command
    do
    {
        string input;

        cout << endl << "*Arithmetic Expression Evalutor*";
        cout << endl << "*0. QUIT*";
        cout << endl << "*1. Infix2postfix Transformation*";
        cout << endl << "***************************";
        cout << endl << "Input a choice(0, 1):";
        cin >> command;                                 //get a command
        cin.ignore(MAX_LEN, '\n');                      //clear the input buffer
        switch (command)
        {
            case 0:break;

            case 1:cout << endl << "Input an infix expression:";
                getline(cin, input);
                input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());    //去除空格
                if(isExp(input) && isBalanced(input) && isLegal(input))
                {
                    cout << endl << "It is a legitimate infix expression.";
                    //str2list();                         //parse a string into a linked list
                    //if(infix2postfix())                 //transform input into postfixS
                }   //end if
                break;
            default: cout << endl << "Command does not exist!" << endl;
        }   //end switch
    }
    while (command != 0);                               //'0':stop the program
    system("pause");                                    //pause the display
    return 0;
}   //end main

bool isExp(const string& input)
{
    for (char ch : input)
    {
        if (!std::isdigit(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ')' && ch != '(')  // 包含非法字符
        {
            std::cout << endl << "Error1: "<< ch << " is not a legitimate character." << endl;
            return false;
        }
    }
    return true;
}

bool isBalanced(const string input)
{

    int open = 0;
    int close = 0;
    for (char ch : input)
    {
        if(!std::isdigit(ch) && ch == '(')
        {
            open += 1;
        }
        if(!std::isdigit(ch) && ch == ')')
        {
            close += 1;
        }
    }
    if(open == close)
    {
        return true;
    }
    else if(open >= close)
    {
        cout << endl << "Error 2: there is one extra open parenthesis.";
        return false;
    }
    else
    {
        cout << endl << "Error 2: there is one extra close parenthesis.";
        return false;
    }
}

bool isLegal(const string input)
{
    int num = 0;
    int characters = 0;
    bool inNumber = false;
    for (char ch : input)
    {
        if (std::isdigit(ch))
        {
            if (!inNumber)
            {
                inNumber = true;
                num++;
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            inNumber = false;
            characters++;
        }
    }

    if(num == characters+1)
    {
        return true;
    }
    else if(num != characters+1)
    {
        cout << endl <<"Error3: there is one extra operator.";
    }
}

//void str2list()


//bool infix2postfix()

