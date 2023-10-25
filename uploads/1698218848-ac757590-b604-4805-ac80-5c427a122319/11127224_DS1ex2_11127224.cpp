//11127224許宥騏
#include<cstdlib>
#include<iostream>
#define MAX_LEN 255

using namespace std;

bool isOperator(char in){
    if ( in =='+'||in =='-'||in =='*' ||in =='/' ){
        return true;
    }
    return false;
}// 是否為運算符號

bool isOpen(char in){
    if (in =='('){
        return true;
    }
    return false;
    
}//是否為(

bool isClose(char in){
    if (in ==')'){
        return true;
    }
    return false;
    
}//是否為)

bool isOperand(string in,int &i){
    if(isdigit(in[i])==1){
        i = i+1;
        if(isOperand(in,i)){
            
        }
        return true;
    }
    return false;
}//是否為數字

bool isLegal(string in){
    int i = 0;
    int size = in.size();
    if(in.empty()){
        cout << "Error 3: there is one extra operator.";
        return false;
    }
    while(i < size){
        if (in[i] =='+'||in[i] =='-'||in[i] =='*' ||in[i] =='/'||in[i] =='('||in[i] ==')'||isdigit(in[i])==1||in[i]==' '){
            i = i + 1;
        }
        else{
            cout << "Error 1: "<< in[i] << " is not a legitimate character.";
            return false;
        }
    }
    return true;
}//內容是否合法

bool isBalance(string in) {
    int i = 0;
    int size = in.size();
    int count = 0;
    while (i < size)
    {
        if(in[i] == '('){
            count = count + 1;
        }
        else if (in[i]==')'){
            count = count - 1;
            if(count<0){
                cout << "Error 2: there is one extra close parenthesis.";
                return false;
            }
        }
        i = i + 1;
    }

    if (count == 0){
        return true;
    }
    else if (count>0){
        cout << "Error 2: there is one extra open parenthesis.";
        return false;
    }
    return false;
    
    
}//括號是否成對且順序正確

bool cIsDigit(string command){
    int i = 0;
    if(command[i]=='-'){
        i = i + 1;
    }
    
    while(i < command.size()) {
        if(isdigit(command[i]) == 1){
            i = i + 1;
        }
        else{
            return false;
        }
    }
    return true;
}//command 是否為數字

void skipSpace(string in,int &i){
    while(in[i]==' '){
        i = i + 1;
    }
}//跳過空格

bool isOK(string in, int &i) {
    bool det = true;
    int size = in.size();
    skipSpace(in,i);
    if(i == size){
        cout << "Error 3: there is one extra operator.";
        return false;
    }//若跳過空白後沒東西
    if(isOpen(in[i])){
        i = i + 1;
        skipSpace(in,i);
        if(isClose(in[i])){
            cout << "Error 3: it is not infix in the parentheses.";
            return false;
        }//左括號後不可為運算符號
        if(!isOK(in,i)){
            return false;
        }//若不是分類為數字
    }
    else if(isOperator(in[i])){
        cout << "Error 3: there is one extra operator.";
        return false;
    }//數字開頭為運算符號，不合法
    else if(isOperand(in,i)){
        skipSpace(in,i);
        if(isOpen(in[i])){
            cout << "Error 3: there is one extra operand.";
            return false;
        }//若數字後為左括號，不合法
        else if(isOperator(in[i])){
            i = i+1;
            skipSpace(in,i);
            if (isClose(in[i])){
                cout << "Error 3: it is not infix in the parentheses.";
                return false;
            }//運算子後不可為又括號
            else if(!isOK(in,i)){
                return false;
            }//運算子後不是分類為數字
        }//若數字後為運算子
        else if (isClose(in[i])){
            i = i + 1;
        }//跳過數字後的右括號
    }

    skipSpace(in,i);
    while (isClose(in[i]))
    {
        i = i + 1;
    }//跳過數字後的右括號
    skipSpace(in,i);

    if(i < size){
        if(isOperator(in[i])){
            i = i + 1;
            skipSpace(in,i);
            if(isOperator(in[i])){
                cout << "Error 3: there is one extra operator.";
                return false;
            }
            if(isClose(in[i])){
                cout << "Error 3: it is not infix in the parentheses.";
                return false;
            }
            else if(!isOK(in,i)){
                return false;
            }
        }//分類為數字後可為一個運算符號
        else if(isOpen(in[i])){
            cout << "Error 3: there is one extra operand.";
            return false;
        }//分類為數字後不可為左括號
    }//若未偵測完全，繼續判斷
    
    return true;

}

struct LIST
{
    char input;
    LIST *next;
};//字元指標

struct TURN
{
    string input;
    TURN *next;
};//字串指標


class LinkedList {
public:
    LIST* head;
    LIST* tail;

    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    bool isEmpty() {
        if(head == NULL){
            return true;
        }
        return false;
    }//是否為空

    void ins(char in) {
        LIST* ins = new LIST;
        ins->input = in;
        ins->next = NULL;
        if (isEmpty()){
            head = ins;
            tail = ins;
        }
        else {
            tail->next = ins;
            tail = ins;
        }
    }//增加資料
    void Set(string in){
        int i = 0;
        while(in[i]!='\0'){
            if(in[i] != ' '){
                ins(in[i]);
            }
            i = i + 1;
        }
    }//設定鏈結串列

    void Print(){
        LIST *run;
        run = head;
        while(run->next != NULL){
            cout << run->input << ", ";
            run = run->next;
        }
        cout << run->input;
    }//輸出

    void clear(){
        LIST *clear;
        clear = head;
        while(head->next != NULL){
            head = head->next;
            delete clear;
            clear = head;
        }
        delete head;
    }
};

class TurnList {
public:
    TURN* head;
    TURN* tail;

    TurnList() {
        head = NULL;
        tail = NULL;
    }

    bool isEmpty() {
        if(head == NULL){
            return true;
        }
        return false;
    }//是否為空

    void ins(string in) {
        TURN* ins = new TURN;
        ins->input = in;
        ins->next = NULL;
        if (isEmpty()){
            head = ins;
            tail = ins;
        }
        else {
            tail->next = ins;
            tail = ins;
        }
    }//新增資料

    void Print(){
        TURN *run;
        run = head;
        while(run->next != NULL){
            cout << run->input << ", ";
            run = run->next;
        }
        cout << run->input;
    }//輸出

    void clear(){
        TURN *clear;
        clear = head;
        while(head->next != NULL){
            head = head->next;
            delete clear;
            clear = head;
        }
        delete head;
    }
};//設定字串指標

class STACK{
public:
    LIST *head;

    STACK(){
        head = NULL;
    }

    bool isEmpty(){
        if(head == NULL){
            return true;
        }
        return false;
    }//堆疊是否為空

    void push(char in){
        LIST *push = new LIST;
        push->input = in;
        push->next = NULL;
        if(isEmpty()){
            head = push;
        }
        else {
            push->next = head;
            head = push;
        }
    }//疊資料

    void pop(){
        LIST *pop;
        if(head->next != NULL){
            pop = head->next;
            delete head;
            head = pop;
        }
        else {
            delete head;
            head = NULL;
        }
    }//刪除

    char getTOP(){
        return head->input;
    }//取得最上層資料

    void clear(){
        LIST *clear;
        clear = head;
        while(head->next != NULL){
            head = head->next;
            delete clear;
            clear = head;
        }
        delete head;
    }


};

int priority(char in){
    if(in =='*'||in =='/'){
        return 2;
    }
    if(in =='+'||in =='-'){
        return 1;
    }
    return 0;
}//優先順序

void turn(LinkedList str){
    STACK stack;//堆疊
    LIST *current = str.head;//處裡的資料
    TurnList post;//輸出陣列
    char op ;//資料判斷暫存
    string digit="";//存入輸出陣列之字串
    cout << endl << "Postfix expression:";
    while ( current != NULL ){
        digit ="";
        op = current->input;
        if(isdigit(op)){
            digit= digit+op;
            while(current->next != NULL&&isdigit(current->next->input)){
                if(isdigit(current->next->input)){
                    current = current->next;
                    op = current->input;
                    digit= digit+op;
                }
            }
            post.ins(digit);
            
        }//若為一個數字

        if(isOperator(op)){
            digit ="";
            while(!stack.isEmpty()&&isOperator(stack.getTOP())&&priority(stack.getTOP())>=priority(op)){
                digit= digit+stack.getTOP();
                post.ins(digit);
                stack.pop();
            }
            stack.push(op);
        }//若為運算符號
        else if(op =='('){
            stack.push(op);
        }//若為左括號
        else if(op == ')'){
            while(!stack.isEmpty()&&stack.getTOP() !='('){
                digit= stack.getTOP();
                post.ins(digit);
                stack.pop();
            }
            if(!stack.isEmpty()&&stack.getTOP()=='('){
                stack.pop();
            }
        }//若為右括號
        current = current->next;
    }

    while(!stack.isEmpty()){
        digit= stack.getTOP();
        post.ins(digit);
        stack.pop();
    }//堆疊數據輸出


    post.Print();
    cout << endl;
    post.clear();

}//中序轉後序


int main(void){
    string command ;

    do{
        string infixS;

        cout << endl << "*Arithmetic Expression Evaluator*";
        cout << endl << "*0.QUIT                         *";
        cout << endl << "*1.Infix2postfix Transformation *";
        cout << endl << "*********************************";
        cout << endl << "Input a choice(0,1):";
        cin >> command;
        cin.ignore(MAX_LEN,'\n');

        if (command == "0") {
            break;
        }
        else if (command == "1"){
            cout << endl << "Input an infix expression: ";
            getline(cin,infixS);
            if ( isLegal(infixS) ){
                if(isBalance(infixS)){
                    int i = 0;
                    if (isOK(infixS,i)){
                        cout << "It is a legitimate infix expression.";
                        LinkedList List;
                        List.Set(infixS);//存入鏈結串列
                        turn(List);//轉為後序
                        List.clear();



                    }//是否為一中序
                }//左右括號是否平衡

            }//是否合法
        }
        else if(cIsDigit(command)){
            cout << endl << "Command does not exist!" << endl;
        }
        else{
            break;
        }
    }while(command != "0");

    system("pause");
    return 0;
    
}