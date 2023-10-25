# include <iostream>
# include <string>

using namespace std;

typedef struct Node{

string ch = "" ;
Node* next ;

};

typedef Node* NodePintor ;


class Steck {

    NodePintor head = NULL ;


    void delete_steck(){ // 刪掉堆疊中的最上面

        if ( head->next == NULL ) { // 指標只有一個
            delete head ;
            head = NULL ;
        }
        else {  // 多個指標
            NodePintor temp = head ;
            head = head->next ;
            temp->next = NULL ;
            delete temp ;
            temp = NULL ;
        }


    }

    public :


    string catch_steck(){  // 拿取堆疊中的最上面

        if ( head == NULL ){
            return NULL ;
        }
        else{
            string ch = head->ch ;
            delete_steck() ;
            return ch ;
        }



    }

    void add_steck( string ch ) { // 放進堆疊中的最上面

        if ( head == NULL ){
            head = new Node() ;
            head->next = NULL ;
            head->ch = ch ;
        }
        else{
            NodePintor temp = new Node() ;
            temp->ch = ch ;
            temp->next = head ;
            head = temp ;
        }


    }

    NodePintor get_head(){

        return head ;

    }
    string get_head_ch(){

        return head->ch ;

    }
    // */ 優先於+-
    bool priority( char ch1, char ch2 ){

        if ( ch1 == '+' || ch1 =='-' ){
            if ( ch2 == '*' || ch2 == '/') {
                return true ;
            }
        }

        return false ;



    }  // priority



};



class expList {


  NodePintor head = NULL;
  NodePintor postfix_head = NULL ;
  string str = "" ;
  Steck steck ;

  void insert_mid_pointer( NodePintor &temp, string ch ) {
        temp->ch = ch ;
        temp->next = new Node() ;
        temp = temp->next ;
  }
  void insert_tail_pointer( NodePintor &temp, string ch ){

        temp->ch = ch ;
        temp->next = NULL;
        temp = temp->next ;
  }

  // 增加Node
  void insert_pointer( NodePintor &temp, string ch, int commit ){

    if ( commit == 1 ){
        insert_mid_pointer( temp, ch );
    }
    else if ( commit == 2 ){
        insert_tail_pointer( temp, ch );
    }


  }

  string analyze( string a, int &num ) {

      string opreator = "" ;

      if ( a.length() == num ){
        return NULL;
      }
      else if ( a.length() == num + 1 ){ // str最後的數字&符號必定回傳
        opreator.append(1, a[num]) ;
        num++ ;
        return opreator ;
      }
      else if ( IsDighit( a[num] ) ){ // 有數字看下一個是不是數字
        if ( IsDighit( a[num+1] ) ){ // 下一個是數字，數字與數字間合併合併(用recrution)
            opreator.append(1, a[num]) ;
            num++ ;
            return opreator + analyze( a, num ) ;
        }
        else { // 不是，回傳
            opreator.append(1, a[num]);
            num++ ;
            return opreator ;
        }
      }
      else { // 符號直接回傳
        opreator.append(1, a[num]);
        num++ ;
        return opreator ;
      }



  }

  // 創建中序LinkList
  bool CostructNode( NodePintor temp, string a, int num ) {

      string s = "" ;

      if ( a.length() == num ){
        return true;
      } // if
      else{
        s = analyze( a, num ) ;

        if ( num == a.length() ){ // num到str的長度表示最後一個node，接地
            insert_pointer( temp, s , 2 ) ;
        }
        else{
            insert_pointer( temp, s , 1 ) ;
        }

        return CostructNode( temp, a, num ) ;

      } // else


  } // CostructNode

  // 刪除所有LinkList
  void DeleteNode( NodePintor head ) {

      NodePintor temp = NULL ;
      if ( head == NULL ){
        return ;
      }
      else if ( head->next == NULL ){ // 最後一個尾巴
        delete head ;
        return ;
      } // else if
      else {
        temp = head->next ;
        head = NULL ;
        delete head ;
        DeleteNode( temp ) ;
      } // else

  } // DeleteNode
  // 是否為整數
  bool IsDighit( char ch ) {

      if ( ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' ||
            ch == '7' || ch == '8' || ch == '9') {



            return true ;

        } // if()

        return false ;


  } // IsDighit
  // 是否為+-*/
  bool IsSign( char ch ){

      if ( ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/'  ) {
        return true ;
      } // if

      return false ;

  } // IsSign
  // 是否為空白
  bool IsWhiteSpace( char ch ) {

      if ( ch == ' ' ) {
        return true ;
      } // if

      return false ;

  } // IsWhiteSpace
  // 括號是否成對
  bool illegal_brackets( NodePintor temp, int num ) {

      if ( temp == NULL ){

        if ( num == 0 ){
            return true ;
        } // if
        else {
            return false ;
        } // else

      } // if
      else{

        if ( temp->ch[0] == '(' ){
            num++ ;
        } // if
        else if ( temp->ch[0] == ')' ){
            num-- ;
        } // else if

        return illegal_brackets( temp->next, num ) ;

      } // else

  } // illegal_brackets


  // 一個合法的運算在不包含 '('and ')'的情況下 運算子數量 = 整數數量 - 1
  // test example: 1++, 10(2+5)
  bool illegalSign( NodePintor temp, int digit, int sign ){

      if( temp == NULL ){
        if ( digit - 1 == sign ) {
            return false ;
        } // if
        else {
            return true ;
        } // else
      } // if
      else {

        if ( IsDighit( temp->ch[0] ) ){
            digit++ ;
        } // if
        else if ( IsSign( temp->ch[0] )  ){
            if ( temp->ch[0] != '(' && temp-> ch[0] != ')'){
                sign++ ;
            } // if
        } // else

        return illegalSign( temp->next, digit, sign ) ;


      } // else

  } // illegalSign

  // 有非合法符號
  bool error_one( string a ){


    for( int i = 0 ; i < a.length() ; i++ ){

        if( IsDighit( a[i] ) == false && IsSign( a[i] ) == false ){
            cout << "Error 1: " << a[i] << " is not a legitimate character." << endl ;
            return false ;
        } //if


    } // for

    return true ;

  }


  // 中序轉後序
  void insfix_translate_postfix(){
    postfix_head = new Node() ;
    postfix_head->ch = head->ch ;
    if ( head->next != NULL ){
        postfix_head->next = new Node() ;
    }
    else{
        postfix_head->next = NULL ;
        return ;
    }

    NodePintor temp = head ;
    NodePintor postfix_temp = postfix_head ;
    bool pro = false; // /* 先 +- 後優先順序
    bool Is = false ; // 沒有對當前temp做任何操作，所以不用temp = temp->next

    while( temp != NULL ){

        if ( IsDighit( temp->ch[0] ) ){
            insert_pointer( postfix_temp, temp->ch, 1 ) ;
        }
        else if ( steck.get_head() == NULL ){ // 堆疊為空
            steck.add_steck( temp->ch ) ;
        }
        else if( temp->ch[0] == '(' ){
            steck.add_steck( temp->ch ) ;
        }
        else if( temp->ch[0] == ')' ){ // 遇到')'把'('前全部輸出

            while( steck.get_head_ch()[0] != '(' ){ // 輸出all(前的東西
                if ( temp->next == NULL && steck.get_head()->next->next == NULL ) // '('括號下沒東西且元素是中序式的最後一個->tail
                    insert_pointer( postfix_temp, steck.catch_steck(), 2 ) ;
                else
                    insert_pointer( postfix_temp, steck.catch_steck(), 1 ) ;
            } // while()

            steck.catch_steck() ; // 清除'('前全部輸出

        }
        else if ( IsSign( temp->ch[0] ) && steck.get_head_ch()[0] == '(' ) { // 前面是'('所以放入，相當於堆疊為空的概念
            steck.add_steck( temp->ch ) ;
        } // else if()
        else if ( steck.get_head_ch()[0] == '/' || steck.get_head_ch()[0] == '*' ){ // */為優先順序，當被放在堆疊時有兩種狀況:下面是+-,下面是(，無論哪種都要取出
            Is = true ; // 因為沒有對當前temp做任何操作，所以不用temp = temp->next
            insert_pointer( postfix_temp, steck.catch_steck(), 1 ) ;
        }
        else if ( IsSign( temp->ch[0] ) && IsSign( steck.get_head_ch()[0] ) && steck.get_head_ch()[0] != '('){
            pro = steck.priority( steck.get_head_ch()[0], temp->ch[0] ) ; // 優先順序判定
            if ( pro ){ // ex:+* ,優先順序放進來
                steck.add_steck( temp->ch ) ;
            }
            else{
                if (  steck.get_head()->next == NULL && temp->next == NULL ) // steck只剩此元素且此元素是中序式的最後一個->tail
                    insert_pointer( postfix_temp, steck.catch_steck(), 2 ) ;
                else
                    insert_pointer( postfix_temp, steck.catch_steck(), 1 ) ;
                steck.add_steck( temp->ch ) ;
            }

        } // else if()
        else { // 上面包括所有狀況，不會走到這裡
            cout << "wrong..." << endl ;
        }


        if ( Is == false )
           temp = temp->next ;
        else
            Is = false ;


    } // while

    while( steck.get_head() != NULL ){ // 把所有堆疊中的東西取出
        if (  steck.get_head()->next != NULL )
            insert_pointer( postfix_temp, steck.catch_steck(), 1 ) ;
        else
            insert_pointer( postfix_temp, steck.catch_steck(), 2 ) ;

    } // while()



  } // Run_two()



  public :

    void Set_str( string a ){

     str = a ;

    } // Set_str

    void Print( NodePintor temp ){

        if ( temp->next == NULL ){
            cout << " " << temp->ch ;
            return ;
        }
        else{
            cout << " " << temp->ch << "," ;
            Print( temp->next ) ;
        }


    } // Print


    void Run() {

      bool IsLegal = false ; // 是不是合法中敘式
      NodePintor temp = NULL;
      int num = 0 ;

      if( str.empty() == true ){ // str為空
        cout << "Error 3:there is one extra oprator." << endl ;
      }
      else if( error_one( str ) ){ // error_one有無非合法符號
        head = new Node() ;
        head->ch = analyze( str, num ) ;
        if ( str.length() != num ){ // 多個node
            head->next = new Node() ;
            IsLegal = CostructNode( head->next, str, num ) ;
        } // if
        else { // 一個node
            head->next = NULL ;
            IsLegal = true ;
        } // else
      } // else if


      if ( IsLegal ) {

          temp = head ;
          IsLegal = illegal_brackets( temp, 0 ) ;
          if ( IsLegal == false ) {
            cout << "Error 2: there is one close parenthesis." << endl ;
          } // if
          else {

            temp = head ;
            if ( illegalSign( temp, 0, 0 ) ){ // 1++
                    cout << "Error 3: there is one extra oprator." << endl ;
                    IsLegal = false ;
            } // else if

          } // else
      } // if

      if ( IsLegal ) {

        cout << "It is a legitimate infix expression." << endl ;
        insfix_translate_postfix() ;
        cout << "Postfix expression:" ;
        Print( postfix_head ) ;
        cout << endl ;
        DeleteNode( postfix_head ) ;
      } // if

      DeleteNode( head ) ;
      head = NULL ;
      postfix_head = NULL ;
      IsLegal = false ;


    } // Run()


}; // expList()



string InputStr() ;

int main()
{
    int command = 0 ;
    expList exp ;
    string str = "";
    char ch ;

    do{
        cout << endl << "* Arithmetic Expression Evaluator *" ;
        cout << endl << "* 0.QUIT                          *" ;
        cout << endl << "* 1.Infix2postfix Transformation  *" ;
        cout << endl << "***********************************" ;
        cout << endl << "Input a choice(0, 1): " ;
        scanf( "%d", &command );
        if ( command == 1 ){
            cout << endl << "Input an infix expression: " ;
            str = InputStr() ; // 直接忽略空白
            exp.Set_str( str ) ; // 設定初始str
            exp.Run() ; // 跑整個流程

        }
        else if ( command != 0  ) {
            cout << endl << " Command does not exit! " ;
        }

    } // do
    while( command != 0  ) ;

    cout << "請按任意鍵繼續 . . ." << endl;
    return 0;
}

string InputStr() {


  string temp = " " ;
  string result = "" ;
  char ch = ' ' ;
  scanf( "%c", &ch );
  scanf( "%c", &ch );
  while( ch != '\n' ){

    if ( ch == ' ' ){
        scanf( "%c", &ch );
    }
    else {
        temp[0] = ch ;
        result = result + temp ;
        scanf( "%c", &ch );
    }

  }

  return result ;
}
