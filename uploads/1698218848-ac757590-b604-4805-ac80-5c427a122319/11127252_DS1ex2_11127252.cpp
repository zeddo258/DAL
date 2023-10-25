// 11127252, 雷國裕
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std ;

enum TYPE { OPERAND, OPERATOR, OPENPAREN, CLOSEPAREN, END } ;  // 資料的類型，END代表沒有資料

class TokenList { // 自定義資料類別
    private:
        struct Token {          // 串列結構
            TYPE type ;         // 資料類型
            string data ;       // 資料內容
            Token * next ;      // 下一筆資料
        } ; // struct Token
        Token * head = NULL ;   // 資料的開頭，預設為沒有資料
        Token * tail = NULL ;   // 資料的結尾，預設為沒有資料
    public:
        void AddTail( TYPE t, string token ) {
            /*
            將資料加入至結尾
            輸入：資料類型t、資料內容token
            輸出：無
            附加效果：資料會儲存在串列結尾，並且讓tail持續指著最後一份資料
            */
            if ( head == NULL ) {         // 如果串列不存在
                head = new Token ;        // 創建一個串列開頭
                head->next = NULL ;       // 還沒有下一份資料
                tail = head ;             // 開頭跟結尾都是同一份資料
                head->type = t ;          // 存入資料類型
                head->data = token ;      // 存入資料內容
            } // if
            else {                        // 已經存在串列
                tail->next = new Token ;  // 結尾創建一份資料
                tail = tail->next ;       // 更新結尾位置
                tail->type = t ;          // 存入資料類型至結尾
                tail->data = token ;      // 存入資料內容至結尾
                tail->next = NULL ;       // 結尾後面還沒有下一份資料
            } // else
        } // AddTail()

        void AddHead( TYPE t, string token ) {
            /*
            將資料從開頭加入
            輸入：資料類型t、資料內容token
            輸出：無
            附加效果：資料會儲存在串列開頭，並且讓head持續指著第一份資料
            */
            if ( head == NULL ) {            // 如果串列不存在
                head = new Token ;           // 創建一個資料開頭
                head->next = NULL ;          // 還沒有下一份資料
                tail = head ;                // 開頭跟結尾都是同一份資料
                head->type = t ;             // 存入資料類型
                head->data = token ;         // 存入資料內容
            } // if
            else {                           // 已經存在串列
                Token* newHead = new Token ; // 創建一個新的開頭
                newHead->next = head ;       // 指著原本的開頭
                head = newHead ;             // 更新開頭位置
                head->type = t ;             // 存入資料類型至開頭
                head->data = token ;         // 存入資料內容至開頭
            } // else
        } // AddHead()

        void Pop() {
            /*
            移除串列的第一份資料
            輸入：無
            輸出：無
            */
            if ( head == NULL ) {  // 如果串列不存在就略過
                return ;
            } // if

            Token* tmp = head ;    // 預備要刪除的資料
            head = head->next ;    // 先讓開頭位置變成下一份資料
            delete tmp ;           // 刪除原本的開頭

            if ( head == NULL ) {  // 如果串列被刪完了
                tail = NULL ;      // 讓結尾位置變成無
            } // if
        } // Pop()

        string GetToken( int n ) {
            /*
            取得第n筆資料內容
            輸入：資料位置n
            輸出：資料內容data
            */
            Token * tmp = head ;               // 從頭開始找資料位置
            for ( int i = 0 ; i < n ; i++ ) {  // 往下找直到要找的位置
                tmp = tmp->next ;              // 下一份資料
            } // for

            return tmp->data ;                 // 回傳資料內容
        } // GetToken()

        TYPE GetTokenType( int n ) {
            /*
            取得第n筆資料類型
            輸入：資料位置n
            輸出：資料類型type，沒有資料就回傳END
            */
            Token * tmp = head ;               // 從頭開始找資料位置
            for ( int i = 0 ; i < n ; i++ ) {  // 往下找直到要找的位置
                if ( tmp == NULL ) {           // 如果沒有資料
                    break ;                    // 離開迴圈
                } // if

                tmp = tmp->next ;              // 下一份資料
            } // for

            if ( tmp == NULL ) {               // 如果沒有資料
                return END ;                   // 回傳沒有資料的資料類型
            } // if

            return tmp->type ;                 // 回傳資料類型
        } // GetTokenType()

        void ClearList() {
            /*
            清除串列的所有內容
            輸入：無
            輸出：無
            */
            Token* tmp = NULL ;                // 預備要刪除的資料
            while ( head != NULL ) {           // 刪到沒有資料為止
                tmp = head ;                   // 預備要刪除的資料
                head = head->next ;            // 開頭指著下一份資料
                delete tmp ;                   // 刪除原本的開頭
            } // while

            tail = NULL ;                      // 讓結尾位置變成無
        } // ClearList()
} ; // class TokenList

string GetLine() ;  // 輸入一行字串
string RemSpace( string line ) ;  // 去除字串的空白字元
bool IsExp( string input ) ;  // 判斷有沒有無效字元
bool IsBalanced( TokenList aList ) ;  // 判斷括號是否成對
bool IsLegal( TokenList aList ) ;  // 判斷是否為合法中序運算式
void Infix2Postfix( TokenList aList ) ;  // 中序轉成後序
void Infix2Postfix_2( TokenList aList, TokenList & aStack, TokenList & postfixList, int & i ) ;  // 括號內中序轉成後序
void InputToken( TokenList & aList, string input ) ;  // 字串資料存入串列

int main() {
    int command = 0 ;                                                 // 指令
    TokenList aList ;                                                 // 串列
    while( true ) {                                                   // 重複執行
        cout << endl << "* Arithmetic Expression Evaluator *" ;
        cout << endl << "* 0.QUIT                          *" ;
        cout << endl << "* 1.Infix2postfix Transformation  *" ;
        cout << endl << "***********************************" ;
        cout << endl << "Input a choice(0, 1): " ;
        cin >> command ;                                              // 輸入指令
        cin.ignore( 255, '\n' ) ;                                     // 跳過指令後的內容直到換行
        if ( command == 0 ) {                                         // 輸入0
            break ;                                                   // 結束指令輸入
        } // if
        else if ( command == 1 ) {                                    // 輸入1
            cout << endl << "Input an infix expression: " ;
            string line = GetLine();                                  // 輸入一行字串
            string input = RemSpace( line ) ;                         // 字串去除空白
            if ( IsExp( input ) ) {                                   // 如果沒有無效字元
                InputToken( aList, input ) ;                          // 字串資料存入串列
                if ( IsBalanced( aList ) && IsLegal( aList ) ) {      // 如果括號成對且是合法中序運算式
                    cout << "It is a legitimate infix expression." ;  // 輸出這是合法中序運算式
                    Infix2Postfix( aList ) ;                          // 中序轉成後序
                } // if
            } // if

            aList.ClearList() ;                                       // 清除串列資料
            cout << endl ;
        } // if
        else {                                                        // 輸入無效指令
            cout << endl << "Command does not exist!" ;
        } // else
    } // while

    system( "pause" ) ;
    return 0 ;
} // main()

string GetLine() {
    /*
    讀入一行資料
    輸入：無
    輸出：一行字串line
    */
    string line = "" ;                                               // 創建一個空字串
    char nextChar = '\0' ;                                           // 創建一個空字元
    while ( scanf( "%c", &nextChar ) != EOF && nextChar != '\n' ) {  // 持續讀入直到換行或是沒有輸入
        line += nextChar ;                                           // 字串接上這個字元
    } // while

    return line ;                                                    // 回傳字串
} // GetLine()

string RemSpace( string line ) {
    /*
    移除字串中的空白字元
    輸入：要處理的字串line
    輸出：沒有空白的字串input
    */
    string input = "" ;                            // 創建一個空字串
    for ( int i = 0 ; i < line.size() ; i++ ) {    // 持續檢查直到字串結尾
        if ( line[i] != ' ' ) {                    // 不是空白字元
            input += line[i] ;                     // 字串接上這個字元
        } // if
    } // for

    return input ;                                 // 回傳新的字串
} // RemSpace()

bool IsExp( string input ) {
    /*
    檢查有沒有無效字元
    輸入：無空白的字串input
    輸出：沒有無效字元true，有無效字元false
    */
    for ( int i = 0 ; i < input.size() ; i++ ) {                                   // 檢查每一個字元
        if ( input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' &&
             input[i] != '(' && input[i] != ')' && ( input[i] < '0' || input[i] > '9' ) &&
             input[i] != ' ' ) {                                                   // 如果出現無效字元
            cout << "Error 1: " << input[i] << " is not a legitimate character." ; // 印出錯誤1
            return false ;                                                         // 回傳有無效字元
        } // if
    } // for

    return true ;                                                                  // 回傳沒有無效字元
} // IsExp()

bool IsBalanced( TokenList aList ) {
    /*
    判斷括號是否有成對
    輸入：一個串列aList
    輸出：括號有成對true，括號沒有成對false
    */
    int balance = 0 ;                                                       // 成對基準
    for ( int i = 0 ; aList.GetTokenType( i ) != END ; i++ ) {              // 檢查每一份資料
        if ( aList.GetTokenType( i ) == OPENPAREN ) {                       // 如果有上括號
            balance += 1 ;                                                  // 基準+1
        } // if
        else if ( aList.GetTokenType( i ) == CLOSEPAREN ) {                 // 如果有下括號
            balance -= 1 ;                                                  // 基準-1
            if ( balance == -1 ) {                                          // 如果下括號比上括號先出現
                cout << "Error 2: there is one extra close parenthesis." ;  // 印出錯誤2(多下括號)
                return false ;                                              // 回傳沒有成對
            } // if
        } // if
    } // for

    if ( balance >= 1 ) {                                                   // 如果上括號比較多
        cout << "Error 2: there is one extra open parenthesis." ;           // 印出錯誤2(多上括號)
        return false ;                                                      // 回傳沒有成對
    } // if

    return true ;                                                           // 回傳有成對
} // IsBalanced()

bool IsLegal( TokenList aList ) {
    /*
    檢查是否為中序運算式
    輸入：一個串列aList
    輸出：是合法中序true，不是合法中序false
    */
    TYPE lastTokenType ;                                                      // 前一份資料類型
    string lastToken = "" ;                                                   // 前一份資料內容
    if ( aList.GetTokenType( 0 ) == OPERAND || aList.GetTokenType( 0 ) == OPENPAREN ) {
                                                                              // 開頭是數字或上括號
        lastTokenType = aList.GetTokenType( 0 ) ;                             // 紀錄這份資料類型
        for ( int i = 1 ; aList.GetTokenType( i ) != END ; i++ ) {            // 檢查每一份資料
            if ( lastTokenType == OPERAND ) {                                 // 如果上一個是數字
                if ( aList.GetTokenType( i ) == OPENPAREN ) {                 // 如果這一個是上括號
                    cout << "Error 3: there is one extra operand." ;          // 印出錯誤3(多一個數字)
                    return false ;                                            // 回傳不是合法中序
                } // if
            } // if
            else if ( lastTokenType == OPERATOR ) {                           // 如果上一個是運算符號
                if ( aList.GetTokenType( i ) == CLOSEPAREN ) {                // 如果這一個是下括號
                    cout << "Error 3: it is not infix in the parentheses." ;  // 印出錯誤3(括號內不是中序)
                    return false ;                                            // 回傳不是合法中序
                } // if
                else if ( aList.GetTokenType( i ) == OPERATOR ) {             // 如果這一個是運算符號
                    cout << "Error 3: there is one extra operator." ;         // 印出錯誤3(多一個運算符號)
                    return false ;                                            // 回傳不是合法中序
                } // if
                else if ( lastToken == "/" && aList.GetToken( i ) == "0" ) {  // 如果直接除以0
                    cout << "Error 3: divide by zero" ;                       // 印出錯誤3(除以0)
                    return false ;                                            // 回傳不是合法中序
                } // if
            } // if
            else if ( lastTokenType == OPENPAREN ) {                          // 如果上一個是上括號
                if ( aList.GetTokenType( i ) == CLOSEPAREN ) {                // 如果這一個是下括號
                    cout << "Error 3: it is not infix in the parentheses." ;  // 印出錯誤3(括號內不是中序)
                    return false ;                                            // 回傳不是合法中序
                } // if
                else if ( aList.GetTokenType( i ) == OPERATOR ) {             // 如果這一個是運算符號
                    cout << "Error 3: it is not infix in the parentheses." ;  // 印出錯誤3(括號內不是中序)
                    return false ;                                            // 回傳不是合法中序
                } // if
            } // if
            else if ( lastTokenType == CLOSEPAREN ) {                         // 如果上一個是下括號
                if ( aList.GetTokenType( i ) == OPENPAREN ) {                 // 如果這一個是上括號
                    cout << "Error 3: there is one extra operand." ;          // 印出錯誤3(多一個數字)
                    return false ;                                            // 回傳不是合法中序
                } // if
                else if ( aList.GetTokenType( i ) == OPERAND ) {              // 如果這一個是數字
                    cout << "Error 3: there is one extra operand." ;          // 印出錯誤3(多一個數字)
                    return false ;                                            // 回傳不是合法中序
                } // if
            } // if

            lastTokenType = aList.GetTokenType( i ) ;                         // 記錄前一份資料類型
            lastToken = aList.GetToken( i ) ;                                 // 紀錄前一份資料內容
        } // for
    } // if
    else if ( aList.GetTokenType( 0 ) == OPERATOR || aList.GetTokenType( 0 ) == END ) {
                                                                              // 如果是運算符號開頭或是沒有東西
        cout << "Error 3: there is one extra operator." ;                     // 印出錯誤3(多一個運算符號)
        return false ;                                                        // 回傳不是合法中序
    } // if

    return true ;                                                             // 回傳是合法中序
} // IsLegal()

void Infix2Postfix( TokenList aList ) {
    /*
    遞迴方法將括號內的中序轉成後序
    輸入：中序串列aList
    輸出：無
    附加效果：列印後序運算式
    */
    TokenList aStack ;                                                                  // 儲存運算符號的堆疊
    TokenList postfixList ;                                                             // 儲存後序運算式
    bool nextFirst = false ;                                                            // 是否要先乘除
    for ( int i = 0 ; aList.GetTokenType( i ) != END ; i++ ) {                          // 檢查串列所有資料
        if ( aList.GetTokenType( i ) == OPERAND ) {                                     // 如果這一個是數字
            postfixList.AddTail( aList.GetTokenType( i ), aList.GetToken( i ) ) ;       // 加在後序結尾
            if ( nextFirst ) {                                                          // 如果先乘除
                postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ; // 加入運算符號
                aStack.Pop() ;                                                          // 移除一個運算符號
                nextFirst = false ;                                                     // 重置先乘除
            } // if
        } // if
        else if ( aList.GetTokenType( i ) == OPENPAREN ) {                              // 如果這一個是上括號
            aStack.AddHead( aList.GetTokenType( i ), aList.GetToken( i ) ) ;            // 放入堆疊
            i++ ;                                                                       // 下一份資料
            Infix2Postfix_2( aList, aStack, postfixList, i ) ;                          // 進入另一個遞迴
            if ( nextFirst ) {                                                          // 如果先乘除
                postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ; // 加入運算符號
                aStack.Pop() ;                                                          // 移除一個運算符號
                nextFirst = false ;                                                     // 重置先乘除
            } // if
        } // if
        else {
            if ( aStack.GetTokenType( 0 ) == OPERATOR && ( 
                 aList.GetToken( i ) == "-" || aList.GetToken( i ) == "+" ) ) {         // 如果沒有遇到先乘除
                postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ; // 加入運算符號
                aStack.Pop() ;                                                          // 移除一個運算符號
            } // if

            aStack.AddHead( aList.GetTokenType( i ), aList.GetToken( i ) ) ;            // 保存運算符號
            if ( aStack.GetToken( 0 ) == "*" || aStack.GetToken( 0 ) == "/" ) {         // 如果存到乘除
                nextFirst = true ;                                                      // 之後要先乘除
            } // if
        } // else
    } // for

    while ( aStack.GetTokenType( 0 ) != END ) {                                         // 放入剩下的運算符號
        postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ;         // 放入運算符號
        aStack.Pop() ;                                                                  // 移除一個運算符號
    } // while

    cout << endl << "Postfix expression: " << postfixList.GetToken( 0 ) ;               // 列印後序運算式第一份資料
    for ( int i = 1 ; postfixList.GetTokenType( i ) != END ; i++ ) {                    // 列印所有後序運算式資料
        cout << ", " << postfixList.GetToken( i ) ;
    } // for

    aStack.ClearList() ;                                                                // 清除堆疊資料
    postfixList.ClearList() ;                                                           // 清除後序運算式資料
} // Infix2Postfix()

void Infix2Postfix_2( TokenList aList, TokenList & aStack, TokenList & postfixList, int & i ) {
    /*
    遞迴方法將括號內的中序轉成後序
    輸入：中序串列aList，運算符號堆疊aStack，後序串列postfixList，目前檢查到的串列位置i
    輸出：無
    附加效果：去除堆疊aStack中的一個上括號，資料會存入後序串列postfixList，檢查到的位置更新i
    */
    bool nextFirst = false ;                                                            // 是否要先乘除
    while ( aList.GetTokenType( i ) != END ) {                                          // 檢查括號內所有資料
        if ( aList.GetTokenType( i ) == OPERAND ) {                                     // 如果這一個是數字
            postfixList.AddTail( aList.GetTokenType( i ), aList.GetToken( i ) ) ;       // 加在後序結尾
            if ( nextFirst ) {                                                          // 如果先乘除
                postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ; // 加入運算符號
                aStack.Pop() ;                                                          // 移除一個運算符號
                nextFirst = false ;                                                     // 重置先乘除
            } // if
        } // if
        else if ( aList.GetTokenType( i ) == OPENPAREN ) {                              // 如果這一個是上括號
            aStack.AddHead( aList.GetTokenType( i ), aList.GetToken( i ) ) ;            // 放入堆疊
            i++ ;                                                                       // 下一份資料
            Infix2Postfix_2( aList, aStack, postfixList, i ) ;                          // 進入另一個遞迴
            if ( nextFirst ) {                                                          // 如果先乘除
                postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ; // 加入運算符號
                aStack.Pop() ;                                                          // 移除一個運算符號
                nextFirst = false ;                                                     // 重置先乘除
            } // if
        } // if
        else if ( aList.GetTokenType( i ) == CLOSEPAREN ) {                             // 如果這一個是下括號
            while ( aStack.GetTokenType( 0 ) != OPENPAREN ) {                           // 直到上括號
                postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ; // 加入運算符號
                aStack.Pop() ;                                                          // 移除一個運算符號
            } // while

            aStack.Pop() ;                                                              // 移除上括號
            return ;                                                                    // 遞迴結束
        } // if
        else {
            if ( aStack.GetTokenType( 0 ) == OPERATOR && ( 
                 aList.GetToken( i ) == "-" || aList.GetToken( i ) == "+" ) ) {         // 如果沒有遇到先乘除
                postfixList.AddTail( aStack.GetTokenType( 0 ), aStack.GetToken( 0 ) ) ; // 加入運算符號
                aStack.Pop() ;                                                          // 移除一個運算符號
            } // if

            aStack.AddHead( aList.GetTokenType( i ), aList.GetToken( i ) ) ;            // 保存運算符號
            if ( aStack.GetToken( 0 ) == "*" || aStack.GetToken( 0 ) == "/" ) {         // 如果存到乘除
                nextFirst = true ;                                                      // 之後要先乘除
            } // if
        } // else

        i++ ;                                                                           // 下一份資料
    } // while
} // Infix2Postfix_2()

void InputToken( TokenList & aList, string input ) {
    /*
    從字串轉換成串列資料
    輸入：串列aList，無空白字串input
    輸出：無
    附加效果：資料會存入串列aList
    */
    int i = 0 ;                                              // 第i個字元
    while ( i < input.size() ) {                             // 檢查所有字元
        string token = "" ;                                  // 將要存入的資料內容
        TYPE type ;                                          // 將要存入的資料類型
        if ( input[i] >= '0' && input[i] <= '9' ) {          // 如果是數字
            while ( input[i] >= '0' && input[i] <= '9' ) {   // 放入所有數字
                token += input[i] ;                          // 放入一個數字
                i++ ;                                        // 下一個字元
            } // while

            type = OPERAND ;                                 // 設定資料類型為數字
        } // if
        else if ( input[i] == '(' ) {                        // 如果是上括號
            token += input[i] ;                              // 放入上括號
            type = OPENPAREN ;                               // 設定資料類型為上括號
            i++ ;                                            // 下一個字元
        } // if
        else if ( input[i] == ')' ) {                        // 如果是下括號
            token += input[i] ;                              // 放入下括號
            type = CLOSEPAREN ;                              // 設定資料類型為下括號
            i++ ;                                            // 下一個字元
        } // if
        else if ( input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) {
                                                             // 如果是運算符號
            token += input[i] ;                              // 放入運算符號
            type = OPERATOR ;                                // 設令資料類型為運算符號
            i++ ;                                            // 下一個字元
        } // if

        aList.AddTail( type, token ) ;                       // 把資料存入串列
    } // while
} // InputToken()