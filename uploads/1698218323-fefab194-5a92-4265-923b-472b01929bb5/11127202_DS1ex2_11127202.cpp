// 11127202 郭立綸


#include <iostream>

using namespace std;

struct listNode {           //用來儲存linked list的struct
    string value ;
    listNode *next;
};

class Mission {

    public :
        bool CheckInfix( string infix, listNode *infixList ){       //檢查是否為中序運算式,並且把中序式存入linked list裡

            int brackets = 0, operate = 0;                          //用來檢查是否有多的括弧或多的數字或運算符號的int
            listNode *head, *tail;                                  //用來存入和判斷中序式的兩個指標
            head = infixList;
            tail = infixList;

            for ( int i = 0 ; i < infix.length() ; i++ ){           //將輸入的字串跑過一遍

                if ( infix[i] != ' ' ){                             //跳過空白

                    if ( infix[i] >= 48 && infix[i] <= 57 ){        //用GetNum取出數字並存入
                        tail->value = GetNum( i, infix );
                        i -= 1;
                    }

                    else if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')' ){
                        tail->value += infix[i];                    //存入運算符號
                    }

                    else{                                           //有其他符號的話則判斷為錯誤
                        cout << "Error 1: " << infix[i] << " is not a legitimate character." << endl ;
                        return false;
                    }

                    if ( i < infix.length()-1 ){                    //讓最後的數字不會額外多開一個linked list
                        tail->next = new listNode;
                        tail = tail->next;
                        tail->value = "";
                        tail->next = NULL;
                    }
                }
            }

            while ( head->next != NULL ){
                if ( head->value[0] == '(' )                            //如果是左括弧,則brackets+1
                    brackets += 1;

                else if ( head->value[0] == ')' ){                      //如果是右括弧,則brackets-1
                    brackets -= 1;
                    if ( brackets < 0 ){                                //檢查前面是否有左括弧,如果沒有就印出錯誤
                        cout << "Error 2: there is one extra close parenthesis." << endl;
                        return false;
                    }
                }

                head = head->next;
            }

            if( head->value[0] == ')' )                     //檢查最後一個東西為何,並處理其相關的條件
                brackets -= 1;

            else if( head->value[0] == '(' )
                brackets += 1;

            if ( brackets > 0 ){                            //如果括弧數大於0,則代表左括弧多了
                cout << "Error 2: there is one extra open parenthesis." << endl;
                return false;
            }

            else if ( brackets < 0 ){                       //如果括弧數小於0,則代表右括弧多了
                cout << "Error 2: there is one extra close parenthesis." << endl;
                return false;
            }

            head = infixList;

            while ( head->next != NULL ){                           //判斷是否為合法的中序式

                if ( head->value[0] == '(' ){                       //檢查括弧後面的東西是否為數字或左括弧,不是的話就印出錯誤
                    if ( head->next->value[0] != '(' && ( head->next->value[0] > 57 || head->next->value[0] < 48 )){
                        cout << "Error 3: it is not infix in the parentheses." << endl ;
                        return false;
                    }
                }

                if ( head->value[0] <= 57 && head->value[0] >= 48 ){    //檢查數字後面的東西是否為左括弧,如果是就印出錯誤
                    operate += 1;
                    if ( head->next->value[0] == '(' ){
                        if ( head->next->next->value[0] <= 57 && head->next->next->value[0] >= 48 ) //如果括弧後面是接數字,則印多一個數字
                            cout << "Error 3: there is one extra operand." << endl;
                        else
                            cout << "Error 3: it is not infix in the parentheses." << endl;         //如果括弧後面是接+-*/),則印出不是中序式

                        return false;
                    }
                }

                if ( head->value[0] == '+' || head->value[0] == '-' || head->value[0] == '*' || head->value[0] == '/' ){    //檢查運算符號後面是否接數字或左括弧,如果不是就印出錯誤
                    operate -= 1;
                    if ( operate < 0 ){
                        cout << "Error 3: there is one extra operator." << endl;    //檢查前面有無數字,如果沒有就印出錯誤
                        return false;
                    }
                    if ( head->next->value[0] != '(' && ( head->next->value[0] > 57 || head->next->value[0] < 48 ) ){
                        if ( head->next->value[0] == '+' || head->next->value[0] == '-' || head->next->value[0] == '*' || head->next->value[0] == '/' )
                            cout << "Error 3: there is one extra operator." << endl;
                        else
                            cout << "Error 3: it is not infix in the parentheses." << endl;
                        return false;
                    }
                }

                if ( head->value[0] == ')' ){                           //檢查右括弧後面是否是數字或左括號,如果是就印出錯誤
                    if ( head->next->value[0] == '(' ) {
                        if ( head->next->next->value[0] <= 57 && head->next->next->value[0] >= 48 ) //如果括弧後面是接數字,則印多一個數字
                            cout << "Error 3: there is one extra operand." << endl;
                        else
                            cout << "Error 3: it is not infix in the parentheses." << endl;         //如果括弧後面是接+-*/),則印出不是中序式
                        return false;
                    }


                    else if ( head->next->value[0] >= 48 && head->next->value[0] <= 57 ){           //如果是數字,印出多一個數字
                        cout << "Error 3: there is one extra operand." << endl;
                        return false;
                    }
                }

                head = head->next;
            }

                                                            //檢查最後一個東西為何,並處理其相關的條件
            if ( head->value[0] == '+' || head->value[0] == '-' || head->value[0] == '*' || head->value[0] == '/' || head->value[0] == '(' )
                operate -= 1;

            else if ( head->value[0] <= 57 && head->value[0] >=48 )
                operate += 1;

            if ( operate > 1 ){                             //如果運算元大於1,則代表數字多了
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            }

            else if ( operate < 1 ){                        //如果運算元小於1,則代表運算符號多了
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            }

            return true;

        }

        string GetNum( int &i, string infix ){      //將遇到的數字丟入同一個字串裡

            string num = "";
            while ( i < infix.length() ){           //檢查字串直到字串結束

                if ( infix[i] == ' ' )              //跳過空白
                    i++;

                else if ( infix[i] >= 48 && infix[i] <= 57 ){       //如果是數字就存入
                    num += infix[i];
                    i++;
                }

                else                                                //不是數字就回傳
                    return num;
            }
            return num;
        }

        void Postfix( listNode *infixList, listNode *postfixList ){     //把中序變後序

            listNode *stackList, *infix, *postfix, *temp;               //建立一個堆疊的linked list 和指向中序和後序的pointer

            infix = infixList;
            postfix = postfixList;
            stackList = NULL;

            while ( infix != NULL ){                                    //跑到中序全部都跑過一遍後

                if ( infix->value[0] >= 48 && infix->value[0] <= 57 ){  //如果是數字就直接存入後序裡
                    postfix->value += infix->value;
                    postfix->next = new listNode;
                    postfix = postfix->next;
                    postfix->value = "";
                    postfix->next = NULL;
                }
                                                                        //如果是數字以外的則進入以下判斷
                else if ( infix->value[0] == '(' || infix->value[0] == ')' || infix->value[0] == '+' || infix->value[0] == '-' || infix->value[0] == '*' || infix->value[0] == '/' ){

                    if ( infix->value[0] == '(' ){                      //左括弧直接丟進堆疊裡
                        Push( stackList, infix );
                    }

                    else if ( infix->value[0] == '+' || infix->value[0] == '-' ){  //當遇到+或-時
                        if ( stackList != NULL && ( stackList->value[0] == '+' || stackList->value[0] == '-' || stackList->value[0] == '*' || stackList->value[0] == '/' ) ){
                            while ( stackList != NULL && ( stackList->value[0] == '+' || stackList->value[0] == '-' || stackList->value[0] == '*' || stackList->value[0] == '/' ) ){
                                Pop( stackList, postfix );              //把堆疊的東西放到後序裡,直到堆疊的第一個是左括弧或者沒東西
                            }

                            Push( stackList, infix );                   //將遇到的+或-存入堆疊
                        }
                        else{
                            Push( stackList, infix );                   //遇到堆疊沒東西或者是左括弧時,存入堆疊
                        }

                    }

                    else if ( infix->value[0] == '*' || infix->value[0] == '/' ){   //當遇到*或/
                        if ( stackList == NULL || stackList->value[0] == '(' || stackList->value[0] == '+' || stackList->value[0] == '-' ){
                            Push( stackList, infix );                               //如果堆疊的第一個是左括弧、+、-,則將*或/存入堆疊
                        }

                        else if ( stackList != NULL && ( stackList->value[0] == '*' || stackList->value[0] == '/' ) ){
                            Pop( stackList, postfix );                              //如果堆疊的第一個是*或/,則將堆疊裡的東西存入後序
                            Push( stackList, infix );                               //再把遇到的*或/存入堆疊
                        }
                    }

                    else if ( infix->value[0] == ')' ){                             //如果遇到右括弧
                        while ( stackList->value[0] != '(' ){                       //則把堆疊的東西存到後序裡,直到遇到左括弧為止
                            Pop( stackList, postfix );
                        }

                        temp = stackList;                                           //將左括弧從堆疊中移除
                        stackList = stackList->next;
                        delete temp;
                    }
                }

                infix = infix->next;
            }

            while ( stackList != NULL ){            //將堆疊裡剩下的東西存入後序中
                Pop( stackList, postfix );
            }

            temp = postfixList;                     //把後序的空白連結給刪掉
            while( temp->next->next != NULL ){
                temp = temp->next;
            }

            delete temp->next;
            temp->next = NULL;
        }

        void Push( listNode* &stackList, listNode *infix ){     //將中序遇到的東西存入堆疊
            listNode *temp;
            temp = stackList;
            stackList = new listNode;
            stackList->value = infix->value;
            stackList->next = temp;
        }

        void Pop( listNode* &stackList, listNode* &postfix ){   //將堆疊裡的東西放進後序裡
            listNode *temp;
            postfix->value += stackList->value;
            postfix->next = new listNode;
            postfix = postfix->next;
            postfix->value = "";
            postfix->next = NULL;

            temp = stackList;
            stackList = stackList->next;
            delete temp;
        }

        void PrintPostfix( listNode *postfixList ){             //印出後序式
            listNode *temp;
            temp = postfixList;
            cout << endl << "Postfix expression:";
            while( temp != NULL ){
                cout << " " << temp->value;
                if ( temp->next != NULL )
                    cout << ',';
                temp = temp->next;
            }
        }

        void DeleteList( listNode *clean ){                     //刪除linked list
            listNode *temp;
            while( clean != NULL ){
                temp = clean;
                clean = clean->next;
                delete temp;
            }
        }
};

int main()
{
    int command = 0;                       //創建讀入指令的字元
    do {
        string infix;                       //創建讀入中序式的字串
        Mission mission;
        listNode *infixList, *postfixList;  //創建中序和後序的linked list
        infixList = new listNode;
        infixList->value = "";
        infixList->next = NULL;
        postfixList = new listNode;
        postfixList->value = "";
        postfixList->next = NULL;

        cout << endl << "* Arithmetic Expression Evaluator *";
        cout << endl << "* 0. QUIT                         *";
        cout << endl << "* 1. Infix2postfix Transformation *";
        cout << endl << "***********************************";
        cout << endl << "Input a choice(0, 1):";
        cin >> command;                     //輸入指令
        cin.ignore( 255, '\n' );

        if ( command == 0 )
            break;

        else if ( command == 1 ){
            cout << endl << "Input an infix expression:";
            getline( cin, infix );          //取得中序式
            if ( mission.CheckInfix( infix, infixList ) ) {     //如果檢查的結果是中序式
                cout << endl << "It is a legitimate infix expression.";
                mission.Postfix( infixList, postfixList );      //轉成後序式
                mission.PrintPostfix( postfixList );            //印出後序式
            }

            mission.DeleteList( infixList );                    //刪除兩個linked list
            mission.DeleteList( postfixList );
        }

        else
            cout << endl << "Command does not exist!";


    } while( command != 0 );

    return 0;
}
