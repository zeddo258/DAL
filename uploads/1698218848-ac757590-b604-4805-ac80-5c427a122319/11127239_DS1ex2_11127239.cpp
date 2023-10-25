// 11127239 陳映銓
# include <string>
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <new>

# define MAX_LEN 255   // 最大字串長度

using namespace std ;


bool isExp( string& ) ;            // 檢查符號是否正確
bool isBalanced( const string ) ;  // 檢查括號
bool isLegal( const string ) ;     // 檢查是否合法表示
void str2list( const string ) ;    // 將字串解析為鏈
bool infix2postfix() ;             // 將中序轉為後序


template < class T >
class expLIST {

    public :

        typedef struct qN {

            T value ;
            struct  qN *next ;

        } listNode ;
        listNode *head, *tail ; // 頭, 尾

        expLIST() : 
            head(NULL), tail(NULL){}

        bool isEmpty() const {
            if ( head == NULL ) return true ;
            else return false ;
        } // isEmpty

        void ins(const T inValue){

            /*如果開頭 == NULL*/
            if ( isEmpty() == true ) {

                head = new listNode;
                head -> value = inValue;
                head -> next = NULL;
                tail = head;

            } // if

            else {

                tail -> next = new listNode;
                tail = tail -> next ;
                tail -> value = inValue ;
                tail -> next = NULL ;

            } // else

        } // ins

        /*把整個指標印出*/
        void print(){

            for ( listNode * temp = head ; temp != NULL ; temp = temp -> next  ) {
                if ( temp -> next == NULL ) cout << temp -> value << "\n"  ;
                else cout << temp -> value << ", "  ;
                
            } // for

        } // print()

        /*取得頭 的 value */
        void getHead( T& outValue ){
            outValue = head -> value ;
        } // getHead

        /*把頭刪除*/
        void del(){
            listNode *head_old = head ; // 用來記原本頭
            head = head -> next ;
            delete head_old;
        } // del

        /*把頭刪除, 並取得原本的value*/
        void del( T& outValue ){
            listNode *head_old = head ; // 用來記原本頭
            outValue = head -> value ;
            head = head -> next ;
            delete head_old;
        } // del
        
        /*清除指標*/
        void clearUp(){

            while( isEmpty() == false ) del();

        } // clearUp

        ~expLIST(){
            clearUp() ;
        } // expLIST

} ; // expLIST


template < class T >
class expSTACK {



    public :

        typedef struct sN {

            T value ;
            struct  sN *next ;

        } stackNode ; // sN
        stackNode *topPtr ; // 頭 -> 尾

        expSTACK() : 
            topPtr(NULL){}

        bool isEmpty() const {
            if ( topPtr == NULL ) return true ;
            else return false ;
        } // isEmpty

        void push(const T inValue){

            /*如果開頭 == NULL*/
            if ( isEmpty() ) {

                topPtr = new stackNode;
                topPtr -> value = inValue;
                topPtr -> next = NULL;

            } // if

            else {

                stackNode *top_topPtr = new stackNode ;
                top_topPtr -> value = inValue ;
                top_topPtr -> next = new stackNode ;
                top_topPtr -> next = topPtr ;
                topPtr = top_topPtr ;

            } // else

        } // ins

        /*取得頭 的 value */
        void getTop( T& outValue ){
            outValue = topPtr -> value ;
        } // getHead

        /*刪除頭*/
        void pop(){
            stackNode *topPtr_old = topPtr ; // 用來記原本的頭
            topPtr = topPtr -> next ;
            delete topPtr_old ;
        } // pop

        /*刪除頭, 並取得原本的value*/
        void pop( T& outValue ){
            stackNode *topPtr_old = topPtr ; // 用來記原本的頭
            outValue = topPtr -> value ;
            topPtr = topPtr -> next ;
            delete topPtr_old ;
        } // pop

        ~expSTACK(){

            while( isEmpty() == false ) pop() ;

        } // expLIST

} ; // expSTACK

expLIST <string> L;    // 中序
expLIST <string> An;   // 後序
expSTACK <string> Stk; // 堆疊

int main() {

    int command = 0 ;

    do {
        string infixS ; // 原數學運算式

        cout << "\n* Arithmetic Expression Evaluator *" ;
        cout << "\n* 0. QUIT                         *" ;
        cout << "\n* 1. Infix2postfix Transformation *" ;
        cout << "\n***********************************" ;
        cout << "\nInput a choice(0, 1):" ;
        cin >> command ;

        cin.ignore(MAX_LEN, '\n') ;  // 達到最大值or"\n"前的東西都從緩衝區刪除

        switch (command) {

            case 0 : 
                break;

            case 1 : 
                cout << "\nInput an infix expression:" ;
                getline(cin, infixS) ; // 
                if ( isExp(infixS) && isBalanced(infixS) && isLegal(infixS) ) {
                    cout << "It is a legitimate infix expression\n" ;
                    str2list(infixS) ;

                    if(infix2postfix() == true){

                        An.print() ;

                    } // if

                } // if

                An.~expLIST() ;
                L.~expLIST() ;
                Stk.~expSTACK() ;

                break;

            default:
                cout << "\nCommand does not exist!\n" ;
                break;

        } // switch

    } // do
    while ( command != 0 ) ;
    system("pause") ;
    return 0 ;

} // main()


/*檢查符號是否正確*/
/* !!! 我的程式碼會將所有不符合的字元都輸出 !!! */
bool isExp( string &infixS ) {
    int lin = infixS.length() ; // 記運算式總長
    int error_number = 0 ;      // 記 Error_Exp 的位置
    char Error_Exp[30] ;        // 錯誤字元存放區
    bool TF = true;             // 是否有錯誤字元 true:正確 false:有錯

    while( lin > 0 ){

        /*判斷是否為數字0~9*/
        if ( infixS[lin-1] <= 57 && infixS[lin-1] >= 48 ) {
            lin -- ;
            continue;
        } // if

        /*判斷是否為運算子*/
        else if ( infixS[lin-1] == '+' || infixS[lin-1] == '-' ||
                  infixS[lin-1] == '*' || infixS[lin-1] == '/' ||
                  infixS[lin-1] == ' ' || infixS[lin-1] == '(' || infixS[lin-1] == ')' ) {
            lin -- ;
            continue;
        } // else if

        /*不為數字及不為允許的運算子*/
        else {
            Error_Exp[error_number] = infixS[lin-1] ; // 儲存錯誤的字元
            error_number ++ ;
            lin -- ;
            TF = false ;
            // break;
        } // else

    } // while

    if ( TF == false ) {

        error_number = error_number - 1 ;
        cout << "Error 1: " ;

        /*印出所有錯的字元*/
        while( error_number >= 0 ){
            cout << Error_Exp[error_number] << ' ' ;
            error_number -- ;
        } // while
        

        cout << "is not a legitimate character.\n" ;

        return false ;

    } // if    

    else return true ;

} // isExp()

/*檢查括號*/
bool isBalanced( const string infixS ) {

    int lin = 0 ;           // 用來跑運算式的位置
    int up_down_times = 0 ; // 計算 '(' 數 是否與 ')' 數 相等
    bool TF = true ;        // 是否有錯誤括號 true:正確 false:有錯

    while( lin < infixS.length() ){

        /* 如果為 ')' 先於 '(' 為錯誤情況 */
        if ( up_down_times < 0 ) {
            TF = false ;
            break;
        }

        /*判斷是否為 '(' */
        else if ( infixS[lin] == '(' ) {
            up_down_times ++ ;
            lin ++ ;
            continue;
        } // else if

        /*判斷是否為運算子*/
        else if ( infixS[lin] == ')' ) {
            up_down_times -- ;
            lin ++ ;
            continue;
        } // else if

        /*不為 '(' ')' 就繼續往下找*/
        else{
            lin ++ ;
            continue;
        } // else

    } // while

    /*右括號先於左括號 || 左右括號數不相等*/
    if ( TF == false || up_down_times != 0 ) {
        if ( up_down_times > 0 ) cout << "Error 2: there is one extra open parenthesis.\n" ;
        else if ( up_down_times < 0 ) cout << "Error 2: there is one extra close parenthesis.\n" ;
        else cout << "Error 2: there is one extra close parenthesis.\n" ;
        return false ;
    } // if

    else return true ;

} // isBalanced()

/*檢查是否合理*/
bool isLegal( const string infixS ) {

    int lin = 0 ;    // 用來跑運算式的位置
    int times = 1 ;  // 持續往上找 or 往下找需要使用到
    bool TF = true ; // 為false 代表有錯
    int error = 0 ;  // 偵測是甚麼錯(1:運算子錯誤, 2:數字錯誤, 3:中序錯誤)

    /*如果一開時為空格, 省略*/
    while ( infixS[times-1] == ' ' ) times ++ ;

    /*一開始必為數字or()*/
    if ( infixS[times-1] == '+' || infixS[times-1] == '-' ||
         infixS[times-1] == '*' || infixS[times-1] == '/'  ) {

            TF = false ;
            error = 1 ;

    } // if

    else {
        times = 1 ;
        while( lin < infixS.length() ){

            /* '(' 前面要有運算子, 後面要是數字 */
            if ( infixS[lin] == '(' ) {

                /*偵測 '(' 前面*/

                if ( lin > 0 ){
                    if( infixS[lin-1] == '+' || infixS[lin-1] == '-' ||
                        infixS[lin-1] == '*' || infixS[lin-1] == '/' ) {

                        /*正常狀況*/

                    } // if

                    /* '(' 前面為數字及')'皆是錯誤狀況 */
                    else if( ( infixS[lin-1] >= 48 && infixS[lin-1] <= 57 ) ||
                            infixS[lin-1] == ')' ){

                        TF = false ;
                        error = 2 ;

                    } // else if

                    else if (infixS[lin-times] == ' ' || infixS[lin-times] == '(' ) {
                        times ++ ;
                        /*需繼續往上找*/
                        while( lin-times >= 0 ) {

                            /* '(' 前面有運算子(為正確情形) */
                            if( infixS[lin-times] == '+' || infixS[lin-times] == '-' ||
                                infixS[lin-times] == '*' || infixS[lin-times] == '/' ){
                                    break;
                            } // if

                            /* '(' 前面無運算子直接為數字or為 ')' (為錯誤情形) */
                            else if ( infixS[lin-times] >= 48 && infixS[lin-times] <= 57 ||
                                    infixS[lin-times] == ')' ){
                                TF = false ;
                                error = 2 ;
                                break;
                            } // else if

                            else {
                                times ++ ;
                            } // else

                        } // while

                        /*如果前面沒東西也正確*/
                        times = 1 ;

                    } // else if
                } // if

                /*偵測 '(' 後面*/
                if( infixS[lin+1] == '+' || infixS[lin+1] == '-' ||
                    infixS[lin+1] == '*' || infixS[lin+1] == '/' ||
                    infixS[lin+1] == ')' ) {

                        TF = false ;
                        error = 3 ;
                        break;

                } // if

                else if ( infixS[lin+1] >= 48 && infixS[lin+1] <= 57 ){
                    /*正確情況*/
                } // else if

                else if (infixS[lin+times] == ' ' || infixS[lin+times] == '(' ) {
                    times ++ ;
                    /*需繼續往下找*/
                    while( lin+times < infixS.length() ) {

                        /* '(' 後面有運算子及 ')' (為錯誤情形) */
                        if( infixS[lin+times] == '+' || infixS[lin+times] == '-' ||
                            infixS[lin+times] == '*' || infixS[lin+times] == '/' ||
                            infixS[lin+times] == ')' ){
                            TF = false ;
                            error = 3 ;
                            break;
                        } // if

                        /* '(' 後面為數字(為正確情形) */
                        else if ( infixS[lin+times] >= 48 && infixS[lin+times] <= 57 ){
                            break;
                        } // else if

                        else {
                            times ++ ;
                        } // else

                    } // while

                    /*如果前面沒東西也正確*/
                    times = 1 ;

                } // else if

            } // if 



            /* ')' 前面需為數字 後面要有運算子 */
            else if ( infixS[lin] == ')' ) {

                if ( lin < infixS.length() ){
                    /* ')'後面需為運算子 */
                    if( infixS[lin+1] == '+' || infixS[lin+1] == '-' ||
                        infixS[lin+1] == '*' || infixS[lin+1] == '/' ) {

                        /*正常狀況*/

                    } // if

                    else if ( infixS[lin+1] >= 48 && infixS[lin+1] <= 57 ||
                            infixS[lin+1] == '(' ){
                        TF = false ;
                        error = 2 ;
                    } // else if

                    else if (infixS[lin+times] == ' '|| infixS[lin+times] == ')' ) {

                        times ++ ;
                        /*需繼續往下找*/
                        while( lin+times < infixS.length() ) {

                            /* ')' 後面有運算子(為正確情形) */
                            if( infixS[lin+times] == '+' || infixS[lin+times] == '-' ||
                                infixS[lin+times] == '*' || infixS[lin+times] == '/' ){
                                    break;
                            } // if

                            /* ')' 後面無運算子直接為數字 or 為 '(' (為錯誤情形) */
                            else if ( infixS[lin+times] >= 48 && infixS[lin+times] <= 57 ||
                                    infixS[lin+times] == '(' ){
                                TF = false ;
                                error = 2 ;
                                break;
                            } // else if

                            else {
                                times ++ ;
                            } // else

                        } // while

                        /*如果後面沒東西也正確*/
                        times = 1 ;

                    } // else if

                } // if

                
                /* ')'前面為運算元為 錯誤情形 */
                if( infixS[lin-1] == '+' || infixS[lin-1] == '-' ||
                    infixS[lin-1] == '*' || infixS[lin-1] == '/' ||
                    infixS[lin-1] == '(' ) {

                    TF = false ;
                    error = 3 ;

                } // if

                /* ')'前面為數字為 錯誤情形 */
                else if ( infixS[lin-1] >= 48 && infixS[lin-1] <= 57 ){
                    /*正確狀況*/
                } // else if

                /* ')'前面為' ' or ')' 往上繼續找 */
                else if (infixS[lin-times] == ' ' || infixS[lin-times] == ')' ) {

                    times ++ ;
                    /*需繼續往上找*/
                    while( lin-times >= 0 ) {

                        /* ')' 前面有運算子 or '(' (為錯誤情形) */
                        if( infixS[lin-times] == '+' || infixS[lin-times] == '-' ||
                            infixS[lin-times] == '*' || infixS[lin-times] == '/' ||
                            infixS[lin-times] == '(' ){

                            TF = false ;
                            error = 3 ;
                            break;
                        } // if

                        /* ')' 前面無運算子直接為數字  (為正確情形) */
                        else if ( infixS[lin-times] >= 48 && infixS[lin-times] <= 57 ){
                            break;
                        } // else if

                        else {
                            times ++ ;
                        } // else

                    } // while

                    /*如果後面沒東西也正確*/
                    times = 1 ;

                } // else if

            } // else if 


            /* 運算子後面不能是運算子 */
            else if ( infixS[lin] == '+' || infixS[lin] == '-' ||
                      infixS[lin] == '*' || infixS[lin] == '/'  ) {

                /*正確狀況*/
                if ( ( infixS[lin+1] <= 57 && infixS[lin+1] >= 48 ) || 
                       infixS[lin + 1] == '(' || infixS[lin + 1] == ')' ) {

                    /*除數為0, 產生錯誤訊息, 並維持正常運作*/
                    if ( infixS[lin] == '/' && infixS[lin+1] == '0' ) {
                        cout << "Error : The division sign cannot be followed by 0 \n" ;
                    } // if

                } // if

                else if ( infixS[lin+1] == '+' || infixS[lin+1] == '-' ||
                        infixS[lin+1] == '*' || infixS[lin+1] == '/'  ) {

                    TF = false ;
                    error = 1 ;

                } // else if

                else if ( infixS[lin + times] == ' ' ) {

                    /*往下繼續找*/
                    while( lin+times < infixS.length() ) {

                        /* 後面有運算子(為錯誤情形) */
                        if( infixS[lin+times] == '+' || infixS[lin+times] == '-' ||
                            infixS[lin+times] == '*' || infixS[lin+times] == '/' ){
                                TF = false ;
                                error = 1 ;
                                break;
                        } // if

                        /* '後面無運算子直接為數字(為正確情形) */
                        else if ( infixS[lin+times] >= 48 && infixS[lin+times] <= 57 ){
                            break;
                        } // else if

                        else {
                            times ++ ;
                        } // else

                    } // while

                    times = 1 ;

                } // else if

            } // else if ( 運算子後面不能是運算子 )

            lin ++ ;
            if ( TF == false ) break;

        } // while

    } // else

    

    if ( TF == false ) {
        if ( error == 1 ) cout << "Error 3: there is one extra operator.\n" ;
        else if ( error == 2 ) cout << "Error 3: there is one extra operand.\n" ;
        else if ( error == 3 ) cout << "Error 3: it is not infix in the parentheses.\n" ;
        return false ;
    }
    else return true ;
    

} // isLegal()


/*將字串解析為鏈*/
void str2list( const string infixS ) {

    int lin = 0 ;            // 用來跑運算式的位置
    bool one_times = false ; // 判斷數字是否跑完
    // 字元數字轉字串int
    while( lin < infixS.length() ) {

        string str = "\0" ;

        while ( lin < infixS.length() && infixS[lin] >= 48 && infixS[lin] <= 57 ){
            str = str + infixS[lin];
            lin++;
            one_times = true ;
        } // if

        if ( lin - 1 >= 0 && infixS[lin-1] >= 48 && infixS[lin-1] <= 57 && one_times == true ) {
            one_times = false ;
            lin--;
        } 

        else if ( infixS[lin] == ' ' ){

            lin++ ;
            continue ; // 把空格跳掉

        } // else if

        else {

            str = str + infixS[lin];

        } // else

        L.ins( str ) ;
        
        lin++ ;
    } // while

    // L.print() ;

} // str2list()


/*將中序轉為後序*/
bool infix2postfix() {

    string str = "\0" ;         // 跑中序的value
    string str_value = "\0" ;   // 跑堆疊的value
    bool str_BL = false ;       // true : * or / false : + or -
    bool str_value_BL = false ; // true : * or / false : + or -

    /*要先將他排序 '()' > '*, /' > '+, -' */
    while( L.isEmpty() == false ) {
        
        L.getHead(str) ;

        /*遇到數字就放進後續指標(An)*/
        if ( str != "+" && str != "-" &&
             str != "*" && str != "/" &&
             str != "(" && str != ")" ){

            An.ins(str) ;
            L.del() ;

        } // if

        /*放入堆疊裡*/
        else if ( str == "("  ) {

            Stk.push(str) ;
            L.del() ;

        } // else if

        /*把到 "(" 前的運算子全部釋放出來*/
        else if ( str == ")" ) {
            L.del() ;
            do{
                Stk.getTop(str_value) ;

                if ( str_value != "(" ){
                    An.ins(str_value) ;
                    Stk.pop(str_value);
                } // if

                else{
                    Stk.pop(str_value);
                } // else

            }
            while( str_value != "(" ) ;

        } // else if

        /*放入堆疊裡，並比較前一個誰大，直到( */
        else if ( str == "+" || str == "-" ||
                  str == "*" || str == "/" ){

            L.del() ;

            if (Stk.isEmpty() == true ) Stk.push(str) ; // 將新的放入堆疊中 ;
            else {
                Stk.getTop(str_value) ;
                if ( str == "*" || str == "/" ) str_BL = true ;
                if ( str_value == "*" || str_value == "/" ) str_value_BL = true ;

                /*釋放前一個*/
                if( str_BL == str_value_BL || ( str_value_BL == true && str_BL == false) ){

                    if ( str_value == "(" ) Stk.push(str) ; // 將新的放入堆疊中
                    else{
                        An.ins(str_value) ;  // 將前一個放下來
                        Stk.pop(str_value) ; // 釋放前一個
                    
                        if ( Stk.isEmpty() == false  && str_value != "(" ) Stk.getTop(str_value) ;
                        if ( str_value != "(" && Stk.isEmpty() != true ) {
                            An.ins(str_value) ;  // 將前一個放下來
                            Stk.pop(str_value) ; // 釋放前一個
                        } // if 

                        Stk.push(str) ; // 將新的放入堆疊中
                    } // else

                } // if

                /*繼續往上疊*/
                else if( str_value_BL == false && str_BL == true ) {

                    Stk.push(str) ; // 將新的放入堆疊中

                } // else if

                str_BL = false ;
                str_value_BL = false ;

            } // else
        } // else if
        

    } // while

    /*將堆疊裡剩下的依照順序放入後序中*/
    while( Stk.isEmpty() == false ) {

        Stk.getTop(str_value) ;
        Stk.pop(str_value);
        An.ins(str_value) ;

    }

    return true ;

} // infix2postfix()