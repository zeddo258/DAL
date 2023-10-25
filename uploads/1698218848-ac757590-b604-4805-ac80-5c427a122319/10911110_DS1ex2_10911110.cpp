//資工二乙 10911110 江侑倫

#include<iostream>
#include<string>

using namespace std;
template <typename T>


class Stack{
private:
    struct Node{    //節點
        T data;     //資料
        Node* next; //下個節點的指標
    };
    Node head;      //鏈結串列的頭
    Node* topNode=&head;    //鏈結串列的頂端
public:

    bool isEmpty(){     //檢查鏈結串列是否為空
        if(topNode==&head) return true;
        return false;
    }
    void push(T newData){   //新增新的鏈結
        Node* newNode=new Node;
        newNode->data=newData;
        newNode->next=topNode;
        topNode=newNode;
    }
    void pop(){             //刪除鏈結的頂端
        if(!isEmpty()){
            Node* temp=topNode;
            topNode=topNode->next;
            delete temp;
        }
    }
    T top(){                //鏈結頂端的資料
        if(!isEmpty()) return topNode->data;
    }

    ~Stack(){               //清空鏈結串列
        while(!isEmpty()){
            pop();
        }
    }
};

class Infix_To_Postfix{
private:
//檢查是否為數字
bool isNumber(char c){
    if(c>='0'&&c<='9'){
        return true;
    }
    else return false;
}
//檢查是否為運算子
bool isOperator(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/') return true;
    return false;
}
//檢查是否為括號
bool isParentheses(char c){
    if(c=='('||c==')') return true;
    return false;
}
//比較前後運算子的優先序
bool isHigher(char a,char b){
    if((a=='+'||a=='-')&&(b=='*'||b=='/')) return true;
    return false;
}

//檢查錯誤Error 1 (有非法字元)
bool checkError_1(char c){
    if(!isNumber(c)&&!isOperator(c)&&c!='('&&c!=')'&&c!=' ') return true;
    return false;
}
//檢查錯誤Error 3 (有多餘的運算子或不符合中序式算式)
int checkError_3(char a,char b){
    if((isOperator(a)&&isOperator(b))||(isNumber(a)&&b=='(')||((isNumber(b)&&a==')'))){
        return 3;
    }
    else if(a=='('&&isOperator(b)||b==')'&&isOperator(a)||a=='('&&b==')'){
        return 31;
    }
    else return false;
}

public:
string Error_1;     //非法字元
#define Error_2 "Error 2: there is one extra open parenthesis."    //多左括號
#define Error_2_1 "Error 2: there is one extra close parenthesis." //多右括號
#define Error_3 "Error 3: there is one extra operator."            //多餘運算子
#define Error_3_1 "Error 3: it is not infix in the parentheses."   //不符合中序式

int infixToPostfix(string infix,Stack<string>* postfix){    //中序式轉後序式，回傳結果代號
    Stack<char> Operator;   //新增運算子堆疊
    string number="";       //數字
    char c=NULL;            //儲存上一個字元
    for(char token : infix){
        if(checkError_1(token)) {   //檢查非法字元
            Error_1.clear();
            Error_1+="Error 1: ";Error_1+=token;Error_1+=" is not a legitimate character.";
            return 1;       //回傳錯誤1
        }
        if(c!=NULL){        //檢查中序式格式
            if(checkError_3(c,token)==3) return 3;          //回傳錯誤3
            else if(checkError_3(c,token)==31) return 31;   //回傳錯誤3_1
            c=token;
        }else if(c==NULL) {
            if(isOperator(token)) return 3;     //檢查開頭字元為運算子，回傳錯誤3
            if(token==')') return 21;           //檢查開頭字元為右括號，回傳錯誤2_1
            c=token;
        }

        if(isNumber(token)){    //儲存數字
            number+=token;
        }
        else if(isOperator(token)){
            if(!number.empty()){
                postfix->push(number);  //堆疊數字
                number.clear();
            }
            //檢查是否有儲存的運算子
            if(!Operator.isEmpty()&&isOperator(Operator.top())){
                //比較運算子優先序
                if(isHigher(Operator.top(),token)){
                    //儲存運算子
                    Operator.push(token);
                }else{
                    while(!Operator.isEmpty()&&Operator.top()!='('){
                    string temp="";temp+=Operator.top();
                    postfix->push(temp);        //堆疊運算子
                    Operator.pop();}
                    Operator.push(token);
                }
            }else{
                Operator.push(token);   //儲存運算子
            }

        }else if(token=='('){       //儲存左括號
            Operator.push(token);
        }else if(token==')'){
            if(!number.empty()){    //堆放數字
                postfix->push(number);
                number.clear();
            }
            while(!Operator.isEmpty()&&Operator.top()!='('){
                string temp="";temp+=Operator.top();
                postfix->push(temp);    //堆疊運算子直到左括號
                Operator.pop();
            }
            if(Operator.isEmpty()){
                return 21;          //找不到左括號，回傳錯誤2_1
            }else if(Operator.top()=='(') Operator.pop();   //移除左括號
        }else if(token==' ') ;  //跳過空格

    }

    if(!number.empty()){    //堆疊剩餘數字
        postfix->push(number);
        number.clear();
    }
    if(isOperator(c)) return 3;    //多餘運算子，回傳錯誤3


    while(!Operator.isEmpty()){
        if(isParentheses(Operator.top())) return 2; //多餘左括號，回傳錯誤1
        string temp="";temp+=Operator.top();
        postfix->push(temp);        //堆疊剩餘運算子
        Operator.pop();
        }


    return 0;   //回傳0代表成功轉換
}

};



int main(){
    string infix;   //中序式算式
    Infix_To_Postfix ITP;
    Stack<string> postfix;  //後序式算式
    int mode,n=0;

    while(1){
            postfix.~Stack(); //清空堆疊
        //輸出介面
        cout<<"\n* Arithmetic Expression Evaluator *\n";
        cout<<"* 0. QUIT                         *\n";
        cout<<"* 1. Infix2postfix Transformation *\n";
        cout<<"***********************************\n";
        cout<<"Input a choice(0, 1): ";
        cin>>mode;      //輸入指令

        if(mode==1){    //輸入指令1
            cout<<"\nInput an infix expression: ";
            getchar();
            getline(cin,infix);     //讀取中序式算式
            if(infix.empty()) {     //檢查是否有正常輸入
                    cout<<Error_3<<endl;
                    continue;}
            n=ITP.infixToPostfix(infix,&postfix);   //中序式轉後序式

            if(n==0){   //代表成功轉換
                    Stack<string> PostfixList;
                while(!postfix.isEmpty()){
                    PostfixList.push(postfix.top());
                    postfix.pop();
                }
                    cout<<"It is a legitimate infix expression.\nPostfix expression: ";
                    cout<<PostfixList.top();
                    PostfixList.pop();
                while(!PostfixList.isEmpty()){      //輸出後序式
                    cout<<", "<<PostfixList.top();
                    PostfixList.pop();
                }
            }
            else if(n==1) cout<<ITP.Error_1;    //非法字元
            else if(n==2) cout<<Error_2;        //多餘左括號
            else if(n==21) cout<<Error_2_1;     //多餘右括號
            else if(n==3) cout<<Error_3;        //多餘運算子
            else if(n==31) cout<<Error_3_1;     //非中序式

            cout<<endl;

        }
        else if(mode==0){       //輸入指令0
            break;          //停止程式
        }
        else cout<<"\nCommand does not exist!\n"; //指令錯誤
        postfix.~Stack();   //清空堆疊
    }

    return 0;
}

