//11120411 陳瀚傑
#include <iostream>
#include <string>       //string class
#include <cstdlib>      //system, atoi
#include <new>
#include <cctype>
#include <vector>

#define MAX_LEN 255

using namespace std;

void mission_1();                   //mission1
bool isExp(string&);                //check the validity of each symbol
bool isBalanced(const string);      //check the validity of balanced parentheses
bool isLegal(const string);         //check whether it is a legal expression
//void str2list();                    //parse a string into a linked list
bool infix2postfix();               //transform infix into postfix
int priority(char op);              //check the priority of +-*/
string PrintOut(string expression);   //print out the function
bool isOperator(char c);
bool isOperator(string c);



template <class T>   // type template for data value in list node
class myList
{
    typedef struct qN   // structure of each node in list
    {   
        T   value;
        struct qN *next;  // next element
        
    }listNode;

    listNode*head,*tail;    // only two data members

public:

    //constructor with initialization
    myList():head(NULL),tail(NULL)     
    {}  


    bool isEmpty() const
    {
        return head == NULL;
    }

    void add(const T& value) {
        listNode *newNode = new listNode;
        newNode->value = value;
        newNode->next = NULL;
        if(isEmpty()){

            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    // get the head of list without removal
    bool getHead(T &outValue)   
    {
        if (!isEmpty()) {
            outValue = head->value;
            return true;
        }
        return false;
    }

    // remove the head of list
    void del()  
    {
        if (!isEmpty()) {
            listNode* temp = head;
            if(head == tail){
                head = head->next;
                tail = tail->next;
            }else{
                head = head->next;
            }
            delete temp;
            temp = 0;
        }
        if(isEmpty()){
            tail = NULL;
        }
    }

    // get the head of stack and remove it
    bool del(T &outValue)  
    {
        if(getHead(outValue)){
            del();
            return true;
        }
        return false;
    }   
    
    // clear up the entire list
    void clearUp()  
    {
        while (!isEmpty()){
           tail->next = NULL;
           del();
        }
        head = tail = NULL;
    }

    // destructor
    ~myList()  
    {
        clearUp();
    } 
};


template <class T>
class myStack
{   
    typedef struct sN{
        T   value;
        struct sN *next;
    }stackNode;

    stackNode *topPtr;
public:

    myStack():topPtr(NULL)
    {} //end myStack initializer

    bool isEmpty()  const
    {   
        return topPtr == NULL;
    }

    void push(const T inValue)
    {   try
        {
            stackNode *newNode = new stackNode;
            newNode->value = inValue;
            newNode->next = topPtr;
            topPtr = newNode;
        }
        catch(bad_alloc& ba)
        {   
            cerr << endl << "bad_alloc on stack caught:"<< ba.what() << endl;
        }
    }

    char getTop()
    {
        if(!isEmpty()){
            char outValue;
            outValue = topPtr->value;
            return outValue;
        }
    }

    void pop()
    {
        if(!isEmpty()){
            stackNode *temp = topPtr;
            topPtr = topPtr->next;
            delete temp;
        }
    }//end myStack::pop without output parameter


    ~myStack()
    {   while (!isEmpty())
            pop();
    }  
};    


bool isOperator(char c) {   //判斷+-*/符號
    return c == '+' || c == '-' || c == '*' || c == '/' ;
}
bool isOperator(string c) {   //判斷+-*/符號
    return c == "+" || c == "-" || c == "*" || c == "/" ;
}

//check the validity of each symbol
bool isExp(string& inp){
    int space = 0;
    string temp;
    for(int i = 0 ; i < inp.size() ; i++){   //一格一格查看是否正確
        if (!isspace(inp[i])){
            if(inp[i] >= '0' && inp[i] <= '9'){
                continue;    //如果是數字那繼續
            } 
            else if(isOperator(inp[i]) || inp[i] == ' ' || inp[i] == '(' || inp[i] == ')'){
                 continue;  //合法的符號也繼續
            }
            else {
                cout << "Error 1: " << inp[i] << " is not a legitimate character.\n";   //如果是其他東西就錯誤
                return false;
                }
        }
        
    }
    for(int i = 0 ; i < inp.size() ; i++){
        if (!isspace(inp[i])) {
            temp.append(1, inp[i]);
        }
    }
    inp = temp;

    if (inp.empty()) {  // 如果都是空格，顯示錯誤
		cout << "Error 3: there is one extra operator.\n";
		return false;
	    }
    return true;
}

//check the validity of balanced parentheses
bool isBalanced(const string inp){
    myStack<char> stack;

    for(char c : inp){
        if (c == '('){     //遇到左括號把它放入stack裡
            stack.push(c);
        }
        else if (c == ')'){     //遇到右括號看stack裡有沒有左括號
            if (stack.isEmpty()) {  //沒有的話顯示多一個右括號
                cout << "Error 2: there is one extra close parenthesis." << endl;
                return false;
            }
            stack.pop();    //有的話把左括號去除
        }
    }
    if(stack.isEmpty()){    //如果掃描完stack是空的那就正確
        return true;
    }else {           //如果stack還有東西顯示多一個左括號
        cout << "Error 2: there is one extra open parenthesis." << endl;
        return false;
    }
}

//check whether it is a legal expression
bool isLegal(const string inp){

    for(int i = 0 ; i < inp.size() ; i++){

        if(isOperator(inp[i]) && isOperator(inp[i-1])){  //前後兩個符號不能同時是+-*/
            cout << "Error 3: there is one extra operator." << endl;
            return false;
        }
        if(inp[i-1] == ')' && (!isOperator(inp[i]) && inp[i] != ')')){  //右括號後面只能是符號 '+-*/' 和 ')'
            cout << "Error 3: there is one extra operand." << endl;
            return false;
        }
        if( inp[i] == ')' && isOperator(inp[i-1]) ){    //右括號前面不能是 +-*/
            cout << "Error 3:  Error 3: it is not infix in the parentheses." << endl;
            return false;
        }
        if(inp[i] == '('){   
            if ((inp[i-1] >= '0' &&  inp[i-1] <= '9')) {    //左括號前面不能是數字
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            if ( inp[i-1] == ')' ) {       //左括號前面也不能是右括號
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }
            if(isOperator(inp[i+1]) || inp[i+1] == ')'){ //左括號後面不能是+-*/或右括號
                cout << "Error 3: it is not infix in the parentheses." << endl;
                return false;
            }
        }

        if(isOperator(inp[inp.size()-1]) || isOperator(inp[0])){    //第一個或最後一個不能是+-*/
            cout << "Error 3: there is one extra operator." << endl;
            return false;
        }
    }
    return true;
}     

//transform infix into postfix
void infix2postfix(string &infix, myList<string> &postList){
    myStack<char> stack;
    string temp;

    for(int i = 0; i <= infix.length(); i++) {
       
        if(infix[i] >='0' && infix[i] <= '9'){  //如果是0~9就直接將他們加入後序式
            if(i < infix.length()){
                if (!(infix[i+1] >= '0' && infix[i+1] <= '9')) {  //如果下一個不是數字即存入
					temp = temp + infix[i] + ",";
                    postList.add(temp);
					temp = "";
				}
				else if ( infix[i+1] >= '0' && infix[i+1] <= '9' ) {  //如果下一個還是數字就繼續接上去 
					temp = temp + infix[i];
				}
            }

        }else if(infix[i] == '('){  //左括號先放進 stack 中

            stack.push(infix[i]);

        }else if(infix[i] == ')'){  //右括號就把堆疊內的運算符號彈出，直到遇見左括號

            while(!stack.isEmpty() && stack.getTop() != '('){
                string push(1, stack.getTop()); //把stack第一項強制轉型成string
                postList.add(push);     //把運算符號丟進 link list 裡面
                stack.pop();    //刪除stack最外面的標點符號
            }
            stack.pop();    // 移除左括號

        }else{      //如果是+-*/，先處理他們的優先順序

            while(!stack.isEmpty() && priority(stack.getTop()) >= priority(infix[i])){
                string push(1, stack.getTop());     //把stack第一項強制轉型成string
                postList.add(push);     //把運算符號丟進 link list 裡面
                stack.pop();    //刪除stack最外面的標點符號
            }
            stack.push(infix[i]);
        }
    }
} 

//確認先 */ 後 +-
int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
}

//印出後序式
string PrintOut(myList<string> &formula){
    string value = "";
    string format = "";
    int count = 0;

    while (formula.getHead(value)) {    //如果 link list 裡的 head 還有值的話就一直讀
        if(count>0){
            format += ',';  //放逗號
        }
        for(int i = 0; i <= value.length(); i++){
            if(isOperator(value[i]) || value[i] == '(' || value[i] == ')'){     //讀括號
                format += value[i];
            }else if(value[i] >= '0' && value[i] <= '9'){       //讀數字
                format += value[i];     
            }
        }
        formula.del();  //讀完就刪除那格link
        count++;    //計算逗號
    }
    return format;
}

//mission 1
void mission_1(){
    string infixS;
    myList<string> postfixList;
    cout << "Input an infix expression: ";
    getline(cin, infixS);
    getline(cin, infixS);
    cout << endl;

    if (isExp(infixS) &&        // 檢查每個符號並刪除無用的符號
        isBalanced (infixS) &&  // 檢查括號的有效性 是否對稱
        isLegal(infixS)         // 檢查它是否為合法的表達式
        ) 
    {     
        cout << "It is a legitimate infix expression.\n";

        infix2postfix(infixS, postfixList); // 將 infixS 轉換為後序式

        string out = PrintOut(postfixList); //將後序式轉成string
        
        cout << endl << "postfixs: " << out << endl << endl; //印出後序式

    }
}

int main()
{
    char startnum = 0;

    while (1) {
        cout <<"* Arithmetic Expression Evaluator*" << endl;
        cout <<"* 0. Quit                        *" << endl;
        cout <<"* 1. Infix2postfix Transformation*" << endl;
        cout <<"**********************************" << endl;
        cout <<"Input a command(0, 1):  ";
        startnum = getchar();   //擷取字串
        if(startnum == '\n'){   //以防緩存區存到enter
            startnum = getchar();
        }
        cout << endl;
        
        switch (startnum)
        {
        case '0':     //0的話直接結束
            exit(0);
        case '1':     //1進入任務1
            mission_1();
            break;
        default:    //其他顯示錯誤
            cout << "Command does not exist!" << endl << endl;
            break;
        }
        
        
    }
    return 0;
}