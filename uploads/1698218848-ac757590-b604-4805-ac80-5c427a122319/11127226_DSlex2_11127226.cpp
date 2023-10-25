// 11127226 李奕層
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <new>

#define MAX_LEN 255

using namespace std;

template <class T>

class expStack{ // stack類別
    typedef struct s{ // 堆疊的節點
        T value;
        struct s *next;
    } stackNode ;
    stackNode *topPtr; // 宣告最上層
public:
    expStack():topPtr(NULL) // 設為NULL
    {}

    bool isEmpty(){ // 判斷是否為空
        if(topPtr == NULL)
            return true;
        else
            return false ;
    }
    void push(T c){ // 放入資料，且新資料位於頂端的位置

        if(isEmpty()){
            topPtr = new stackNode();
            topPtr->value = c ;
            topPtr->next = NULL ;
        }
        else{
            stackNode *node = new stackNode() ;
            node->value = c ;
            node->next = topPtr ;
            topPtr = node ;
        }
    }

    T pop(){ // 拿出頂端的資料並回傳，並將拿出的資料節點刪除
        T operand = topPtr->value;
        stackNode *del = topPtr;
        topPtr = topPtr->next;
        del->next = NULL ;
        delete del;
        del = NULL;
        return operand ;

    }

    char get_top(){ // 獲取堆疊中最上層的資料
        return topPtr->value;
    }
};

template <class V>

class expList{ // 串列類別
    typedef struct q{ // 串列的節點
        V value ;
        struct q *next;

    } listNode ;

    listNode *head, *tail ; // 宣告串列的頭與尾
public:
    expList():head(NULL), tail(NULL) // 設為NULL
    {}
    bool isEmpty(){ // 判斷是否為空
        if(head == NULL)
            return true ;
        else
            return false ;
    }

    void add(string c){ // 加入資料於尾端
        if(isEmpty()){
            head = new listNode() ;
            head->value = c;
            head->next = NULL ;
            tail = head ;
        }
        else{
            tail->next = new listNode();
            tail = tail->next ;
            tail->value = c ;
            tail->next = NULL ;
        }
    }

    void print(){ // 印出串列中的資料
        listNode *current = head ;
        while(current != NULL){
            if(current->next != NULL)
                cout << current->value << ", ";
            else
                cout << current->value ;
            current = current->next;
        }
        cout << endl;
    }

};

int priority(char c){ // 判斷計算符號的計算優先級
    if( c == '*' || c == '/' )
        return 2 ;
    if(c == '+' || c == '-')
        return 1 ;
    return 0 ;
}

void infix2postfix(expList<string> &alist, string str1){ // 將中序轉換為後序運算式
    string str ;
    for(int i = 0 ; i < str1.length() ; i++){ // 將空白字元提出以利後續判斷
        if (str1[i] != ' '){
            str = str.append(str1, i, 1);
        }
    }

    expStack<char> astack ; // 宣告一個stack類別
    for(int i = 0 ; i < str.length() ; i++){ // 將中序的字元一個個判斷分析
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') { // 判斷是否為運算子
            if(astack.isEmpty()) // stack為空直接放入
                astack.push(str[i]);
            else{
                while(priority(str[i]) <= priority(astack.get_top())){ // 不斷判斷運算子的優先級，如果堆疊內部較高則拿出並直接加入後序式裡
                    string operand ;
                    operand += astack.pop();
                    alist.add(operand) ;
                    if(astack.isEmpty()) // 堆疊內部為空直接離開迴圈
                        break;
                }
                astack.push(str[i]); // 結束後再堆疊資料
            }

        }
        else if(str[i] == ')'){ // 遇到右括號便將堆疊內部的運算子拿出並加入後序式直至遇到左括號
            while(astack.get_top() != '('){
                string operand ;
                operand += astack.pop();
                alist.add(operand) ;
            }
            string o ; // 將左括號拿出
            o += astack.pop();
        }
        else if(str[i] == '('){ // 遇到左括號直接堆疊
            astack.push(str[i]);
        }
        else if(str[i] <= 57 && str[i] >= 48){ // 判斷是否為數字
            string number ;
            for(int j = i ; j < str.length() ; j++){ // 將數字一個個字元合併成完整的運算元
                if(str[j] <= 57 && str[j] >= 48){
                    i++;
                    number = number.append(str, j, 1);
                }
                else{
                    break;
                }
            }
            i--;
            alist.add(number) ; // 將合成後的運算元加入後序式中
        }


    }
    while(astack.isEmpty() == false){ // 將堆疊類別中剩下的資料依序加入後序式中
        string operand ;
        operand += astack.pop();
        alist.add(operand) ;
    }
}

bool isExp(string str){ // 判斷是否有中序運算式中無法使用的字元，錯誤則輸出錯誤訊息
    int len = str.length();
    int legal_char = 0;
    for(int i = 0 ; i < len ; i++){
        if(str[i] == '+' || str[i] == '-' || str[i] == '*'
           || str[i] == '/' || (str[i] <= 57 && str[i] >= 48)
           || str[i] == ' ' || str[i] == '(' || str[i] == ')'){

            legal_char++ ;
        }
        else {
            cout << "Error 1: " << str[i] << "is not a legitimate character."<< endl;
            return false ;
        }
    }
    return true ;
}

bool isBalanced(const string str){ // 看左右的括號有沒有依序對上，順序錯或少了則輸出錯誤訊息
    int len = str.length();
    int right_bracket = 0, left_bracket = 0 ;
    for(int i = 0 ; i < len ; i++){
        if(str[i] == '(')
            left_bracket++;
        if(str[i] == ')')
            right_bracket++;
        if(right_bracket > left_bracket){
            cout << "Error 2: there is one extra close parenthesis."<< endl ;
            return false ;
        }
    }
    if(left_bracket > right_bracket){
        cout << "Error 2: there is one extra open parenthesis." << endl;
        return false ;
    }

    return true ;
}
bool isLegal(const string str1){ // 判斷是否為合法中序式
    string str ;
    for(int i = 0 ; i < str1.length() ; i++){
        if (str1[i] != ' '){
            str = str.append(str1, i, 1);
        }
    }

    int len = str.length();
    for(int i = 0 ; i < len-1 ; i++){
        if(str[i] == '('){
            if(str[i+1] == '-' || str[i+1] == '+' || str[i+1] == '*' || str[i+1] == '/' || str[i+1] == ')'){
                cout << "Error 3: it is not infix in the parentheses."<< endl ;
                return false ;
           }
        }
    }
    for(int i = 1 ; i < len ; i++){
        if(str[i] == ')'){
            if(str[i-1] == '-' || str[i-1] == '+' || str[i-1] == '*' || str[i-1] == '/' || str[i-1] == '('){
                cout << "Error 3: it is not infix in the parentheses."<< endl ;
                return false ;
           }
        }
    }

    if(str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/'){
        cout << "Error 3: there is one extra operator."<< endl ;
        return false ;
    }
    if(str[0] <= 57 && str[0] >= 48){
        for(int i = 0 ; i < len-1; i++){
            if(str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/'){
                break;
            }
            else if(str[i] == ')' || str[i] == '('){
                cout << "Error 3: there is one extra operand."<< endl ;
                return false ;
            }
        }
    }
    for(int i = 1 ; i < len-1 ; i++){
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
            if(str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '*' || str[i-1] == '/'){
                cout << "Error 3: there is one extra operator."<< endl ;
                return false ;
            }
        }
        if(str[i] <= 57 && str[i] >= 48){
            if(str[i-1] == ')'){
                cout << "Error 3: there is one extra operand."<< endl ;
                return false ;
            }
            if(str[i+1] == '('){
                cout << "Error 3: there is one extra operand."<< endl ;
                return false ;
            }
        }

    }
    if(str[len-1] <= 57 && str[len-1] >= 48){
        for(int i = len-1 ; i >= 0; i--){
            if(str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/'){
                break;
            }
            else if(str[i] == ')' || str[i] == '('){
                cout << "Error 3: there is one extra operand."<< endl ;
                return false ;
            }
        }
    }
    if(str[len-1] == '+' || str[len-1] == '-' || str[len-1] == '*' || str[len-1] == '/'){
        cout << "Error 3: there is one extra operator."<< endl ;
        return false ;
    }
    return true ;
}

int main()
{
    int command = 0 ;
    do{
        string infixS;
        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         *";
        cout << endl << "* 1.Infix2postfix Transformation  *";
        cout << endl << "*******************************";
        cout << endl << "Input a choice(0, 1): ";
        cin >> command;
        cin.ignore(MAX_LEN, '\n');
        switch(command){ // 依照指令行動
            case 0: break; // 指令0，結束
            case 1:
                cout << endl << "Input an infix expression: ";
                getline(cin, infixS);
                if(isExp(infixS) && isBalanced(infixS) && isLegal(infixS) ){ // 判斷是否為合法中序式
                    cout << "It is a legitimate infix expression.";
                    expList<string> alist ; // 宣告一個串列類別用以儲存轉換後的後序式
                    infix2postfix(alist, infixS); // 轉換
                    cout << endl << "Postfix expression: ";
                    alist.print(); // 印出結果
                }
                break;

            default: cout << endl << "Command does not exist!" << endl;

        }
    }while (command != 0);

    system("pause");
    return 0;
}
