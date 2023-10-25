#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

#define MAX 255

using namespace std;

struct Word {
public:
  Word() {
    number = -1;
    op = ' ';
    right = NULL;
    left = NULL;
  } // Word()

  Word *Tree(Word *ptr, char tmp) {
    if (ptr->op == ' ') {
      ptr->op = tmp;
    } // if()
    else if (ptr->op == '+' || ptr->op == '-' || ptr->op == '*' ||
             ptr->op == '/') {
      Word *branch = ptr->left;
      ptr->left = new Word;
      ptr->left->op = ptr->op;
      ptr->op = tmp;
      ptr->left->left = branch;
      branch = NULL;
      ptr->left->right = ptr->right;
      ptr->right = NULL;
    } // else if
    return ptr;
  } // Tree() - input the Op

  Word *Tree(Word *ptr, int tmp) {
    if (ptr->left == NULL) {
      ptr->left = new Word;
      ptr->left->number = tmp;
    } // if left is empty

    else if (ptr->right == NULL) {
      ptr->right = new Word;
      ptr->right->number = tmp;
    } // if right is empty

    return ptr;
  } // Tree()  input the number

  Word *Tree(Word *ptr, Word *copy) {
    if (ptr->left == NULL) {
      ptr->left = copy;
      copy = NULL;
    } // if()

    else if (ptr->right == NULL) {
      ptr->right = copy;
      copy = NULL;
    } // else if

    return ptr;
  } // Tree() input the result in the parenthesis

  void Print_infix(Word *ptr, int &max) {
    max = max + 1 ;
    if (ptr->left != NULL && max <= 10 ) {
      Print_infix(ptr->left, max);
      cout << ',' << op;
      if (ptr->right != NULL)
        Print_infix(ptr->right, max);
    } // if
    else {
      cout << number;
    }
  } // Print_infix()

  char returnOp() { return op; }

  int returnNumber() { return number; }

private:
  int number;
  char op;
  Word *right;
  Word *left;
};

struct Node {
public:
  Node() {
    head = new Word;
    cur = head;
    prnumber = 0;

    char tmp;
    cout << endl << "Input an Infix expression: ";
    getline(cin, function);
    for (int i = 0; i <= function.length(); i++) {
      tmp = function[i];
      if (tmp == '(' || tmp == ')') {
        if (tmp == '(')
          prnumber++;
        else
          prnumber--;
      } // if()
    }   // for()
  }     // Node()

  bool IsLegal(char &mis) {
    bool legal = true;
    for (int i = 0; i < function.length() && legal; i++) {
      if (function[i] >= '0' && function[i] <= '9')
        legal = true;
      else if (function[i] == '+' || function[i] == '-' || function[i] == '*' ||
               function[i] == '/' || function[i] == ' ')
        legal = true;
      else if (function[i] == '(' || function[i] == ')')
        legal = true;
      else {
        mis = function[i];
        legal = false;
      } // else
    }   // for()
    return legal;
  } // check the char in the function is legal or not

  bool Extra_Check(int &n, char &c) {
    for (int i = 0; i < function.length(); i++) {
      if (function[i] >= '0' && function[i] <= '9') {
        if (function[i + 1] == '(') {
          n = -1;
          return false;
        } // if
      }   // if

      else if (function[i] == '+' || function[i] == '-' || function[i] == '*' ||
               function[i] == '/') {
        if (function[i + 1] == '+' || function[i + 1] == '-' ||
            function[i + 1] == '*' || function[i + 1] == '/') {
          c = 'X';
          return false;
        } // if
      }   // else if
      else if (function[i] == ')') {
        if (function[i + 1] >= '0' && function[i + 1] <= '9') {
          n = -1;
          return false;
        } // if
      }   // else if
    }     // for()
    return true;
  } // Extra_Check()

  int NumSys(string f, int &in, int &total) {
    total = total * 10;
    if (f[in] == '1')
      total = total + 1;
    else if (f[in] == '2')
      total = total + 2;
    else if (f[in] == '3')
      total = total + 3;
    else if (f[in] == '4')
      total = total + 4;
    else if (f[in] == '5')
      total = total + 5;
    else if (f[in] == '6')
      total = total + 6;
    else if (f[in] == '7')
      total = total + 7;
    else if (f[in] == '8')
      total = total + 8;
    else if (f[in] == '9')
      total = total + 9;
    if (f[in + 1] >= '0' && f[in + 1] <= '9') {
      in = in + 1;
      total = NumSys(f, in, total);
    } // if
    return total;
  } // NumSys()

  string small_one(string origin, int &index) {
    int start = 0;
    string s;
    bool stop = false;
    bool skip = false;
    index++;
    while (!stop) {
      if (origin[index] == '(')
        skip = true;
      s[start] = origin[index];
      start++;
      index++;
      if (origin[index] == ')') {
        if (!skip)
          stop = true;
        else
          skip = false;
      } // if
    }   // while
    return s;
  } // small_one()

  void Build() {
    int index = 0;
    Build(index, function, cur);
  } // call from main

  Word *Build(int i, string f, Word *ptr) {
    int num = 0;
    int small_i = 0;
    bool stop = false;

    while (i <= f.length()) {
      if (f[i] == '(') {
        ptr = ptr->Tree(ptr, Build(small_i, small_one(f, i), ptr));
        small_i = 0;
      } // if encounter a parenthsis

      else if (f[i] >= '0' && f[i] <= '9') {
        ptr = ptr->Tree(ptr, NumSys(f, i, num));
        num = 0;
      } // if encounter a number

      else if (f[i] == '+' || f[i] == '-' || f[i] == '*' || f[i] == '/') {
        ptr = ptr->Tree(ptr, f[i]);
      } // if encounter a operator
      i++;
    } // while()

    return ptr;
  } // Build()

  int returnPr() { return prnumber; } // return_prnumber()

  void PrintOut() {
    int max = 0;
    cur->Print_infix(cur, max);
  } // PrintOut()

private:
  Word *head;
  Word *cur;
  int prnumber;
  string function;
};

int main(void) {
  bool stop = false;
  int command;
  int n = 0;
  char ch;
  while (!stop) {
    cout << endl << "* Arithmetic Expression Evaluator *";
    cout << endl << "* 0. Quit                         *";
    cout << endl << "* 1. Infix2postfix Transformation *";
    cout << endl << "***********************************";
    cout << endl << "Input a choice(0,1):";
    cin >> command;
    cin.ignore(MAX, '\n');
    if (command == 0)
      stop = true;
    else {
      Node start;

      /* code dwonward is to check whether the function has unexpected char
      if it's the wrong word, then print out the Error1 */
      char word;
      if (!start.IsLegal(word)) {
        cout << endl
             << "Error 1: " << word << " is not a legitimate character."
             << endl;
      } // if()

      /*downward will check the number of the parentheses in the function
      if the number isn't 0, it will printout the Error2 or Error3 */
      else if (start.returnPr() > 0 || start.returnPr() < 0) {
        if (start.returnPr() > 0) {
          cout << endl << "Error 2: there ";
          if (start.returnPr() == 1)
            cout << "is one extra open parenthesis.";
          else
            cout << "are " << start.returnPr() << " extra open parentheses.";
          cout << endl;
        } // if()

        else {
          cout << endl << "Error 3: there ";
          if (start.returnPr() == -1)
            cout << "is one extra close parenthesis.";
          else
            cout << "are " << 0 - start.returnPr()
                 << " extra close parentheses.";
          cout << endl;
        } // else
      }   // check and report Error2 or Error3

      else if (!start.Extra_Check(n, ch)) {
        if (n == -1)
          cout << "Error 5: there is one extra operand.";
        else if (ch == 'X')
          cout << "Error 4: there is one extra operator. ";
      } // else if

      else {
        cout << "It is a legitimate infix expression." << endl;
        start.Build();
        start.PrintOut();
      } // else

    } // else
  }   // while()
  return 0;

} // main()
