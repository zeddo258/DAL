//��u�G�A 10911110 ���ݭ�

#include<iostream>
#include<string>

using namespace std;
template <typename T>


class Stack{
private:
    struct Node{    //�`�I
        T data;     //���
        Node* next; //�U�Ӹ`�I������
    };
    Node head;      //�쵲��C���Y
    Node* topNode=&head;    //�쵲��C������
public:

    bool isEmpty(){     //�ˬd�쵲��C�O�_����
        if(topNode==&head) return true;
        return false;
    }
    void push(T newData){   //�s�W�s���쵲
        Node* newNode=new Node;
        newNode->data=newData;
        newNode->next=topNode;
        topNode=newNode;
    }
    void pop(){             //�R���쵲������
        if(!isEmpty()){
            Node* temp=topNode;
            topNode=topNode->next;
            delete temp;
        }
    }
    T top(){                //�쵲���ݪ����
        if(!isEmpty()) return topNode->data;
    }

    ~Stack(){               //�M���쵲��C
        while(!isEmpty()){
            pop();
        }
    }
};

class Infix_To_Postfix{
private:
//�ˬd�O�_���Ʀr
bool isNumber(char c){
    if(c>='0'&&c<='9'){
        return true;
    }
    else return false;
}
//�ˬd�O�_���B��l
bool isOperator(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/') return true;
    return false;
}
//�ˬd�O�_���A��
bool isParentheses(char c){
    if(c=='('||c==')') return true;
    return false;
}
//����e��B��l���u����
bool isHigher(char a,char b){
    if((a=='+'||a=='-')&&(b=='*'||b=='/')) return true;
    return false;
}

//�ˬd���~Error 1 (���D�k�r��)
bool checkError_1(char c){
    if(!isNumber(c)&&!isOperator(c)&&c!='('&&c!=')'&&c!=' ') return true;
    return false;
}
//�ˬd���~Error 3 (���h�l���B��l�Τ��ŦX���Ǧ��⦡)
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
string Error_1;     //�D�k�r��
#define Error_2 "Error 2: there is one extra open parenthesis."    //�h���A��
#define Error_2_1 "Error 2: there is one extra close parenthesis." //�h�k�A��
#define Error_3 "Error 3: there is one extra operator."            //�h�l�B��l
#define Error_3_1 "Error 3: it is not infix in the parentheses."   //���ŦX���Ǧ�

int infixToPostfix(string infix,Stack<string>* postfix){    //���Ǧ����Ǧ��A�^�ǵ��G�N��
    Stack<char> Operator;   //�s�W�B��l���|
    string number="";       //�Ʀr
    char c=NULL;            //�x�s�W�@�Ӧr��
    for(char token : infix){
        if(checkError_1(token)) {   //�ˬd�D�k�r��
            Error_1.clear();
            Error_1+="Error 1: ";Error_1+=token;Error_1+=" is not a legitimate character.";
            return 1;       //�^�ǿ��~1
        }
        if(c!=NULL){        //�ˬd���Ǧ��榡
            if(checkError_3(c,token)==3) return 3;          //�^�ǿ��~3
            else if(checkError_3(c,token)==31) return 31;   //�^�ǿ��~3_1
            c=token;
        }else if(c==NULL) {
            if(isOperator(token)) return 3;     //�ˬd�}�Y�r�����B��l�A�^�ǿ��~3
            if(token==')') return 21;           //�ˬd�}�Y�r�����k�A���A�^�ǿ��~2_1
            c=token;
        }

        if(isNumber(token)){    //�x�s�Ʀr
            number+=token;
        }
        else if(isOperator(token)){
            if(!number.empty()){
                postfix->push(number);  //���|�Ʀr
                number.clear();
            }
            //�ˬd�O�_���x�s���B��l
            if(!Operator.isEmpty()&&isOperator(Operator.top())){
                //����B��l�u����
                if(isHigher(Operator.top(),token)){
                    //�x�s�B��l
                    Operator.push(token);
                }else{
                    while(!Operator.isEmpty()&&Operator.top()!='('){
                    string temp="";temp+=Operator.top();
                    postfix->push(temp);        //���|�B��l
                    Operator.pop();}
                    Operator.push(token);
                }
            }else{
                Operator.push(token);   //�x�s�B��l
            }

        }else if(token=='('){       //�x�s���A��
            Operator.push(token);
        }else if(token==')'){
            if(!number.empty()){    //���Ʀr
                postfix->push(number);
                number.clear();
            }
            while(!Operator.isEmpty()&&Operator.top()!='('){
                string temp="";temp+=Operator.top();
                postfix->push(temp);    //���|�B��l���쥪�A��
                Operator.pop();
            }
            if(Operator.isEmpty()){
                return 21;          //�䤣�쥪�A���A�^�ǿ��~2_1
            }else if(Operator.top()=='(') Operator.pop();   //�������A��
        }else if(token==' ') ;  //���L�Ů�

    }

    if(!number.empty()){    //���|�Ѿl�Ʀr
        postfix->push(number);
        number.clear();
    }
    if(isOperator(c)) return 3;    //�h�l�B��l�A�^�ǿ��~3


    while(!Operator.isEmpty()){
        if(isParentheses(Operator.top())) return 2; //�h�l���A���A�^�ǿ��~1
        string temp="";temp+=Operator.top();
        postfix->push(temp);        //���|�Ѿl�B��l
        Operator.pop();
        }


    return 0;   //�^��0�N���\�ഫ
}

};



int main(){
    string infix;   //���Ǧ��⦡
    Infix_To_Postfix ITP;
    Stack<string> postfix;  //��Ǧ��⦡
    int mode,n=0;

    while(1){
            postfix.~Stack(); //�M�Ű��|
        //��X����
        cout<<"\n* Arithmetic Expression Evaluator *\n";
        cout<<"* 0. QUIT                         *\n";
        cout<<"* 1. Infix2postfix Transformation *\n";
        cout<<"***********************************\n";
        cout<<"Input a choice(0, 1): ";
        cin>>mode;      //��J���O

        if(mode==1){    //��J���O1
            cout<<"\nInput an infix expression: ";
            getchar();
            getline(cin,infix);     //Ū�����Ǧ��⦡
            if(infix.empty()) {     //�ˬd�O�_�����`��J
                    cout<<Error_3<<endl;
                    continue;}
            n=ITP.infixToPostfix(infix,&postfix);   //���Ǧ����Ǧ�

            if(n==0){   //�N���\�ഫ
                    Stack<string> PostfixList;
                while(!postfix.isEmpty()){
                    PostfixList.push(postfix.top());
                    postfix.pop();
                }
                    cout<<"It is a legitimate infix expression.\nPostfix expression: ";
                    cout<<PostfixList.top();
                    PostfixList.pop();
                while(!PostfixList.isEmpty()){      //��X��Ǧ�
                    cout<<", "<<PostfixList.top();
                    PostfixList.pop();
                }
            }
            else if(n==1) cout<<ITP.Error_1;    //�D�k�r��
            else if(n==2) cout<<Error_2;        //�h�l���A��
            else if(n==21) cout<<Error_2_1;     //�h�l�k�A��
            else if(n==3) cout<<Error_3;        //�h�l�B��l
            else if(n==31) cout<<Error_3_1;     //�D���Ǧ�

            cout<<endl;

        }
        else if(mode==0){       //��J���O0
            break;          //����{��
        }
        else cout<<"\nCommand does not exist!\n"; //���O���~
        postfix.~Stack();   //�M�Ű��|
    }

    return 0;
}

