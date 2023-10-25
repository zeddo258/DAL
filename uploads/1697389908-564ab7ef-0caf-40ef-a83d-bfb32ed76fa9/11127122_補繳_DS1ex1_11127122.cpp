// 11127122 胡沛頎
# include <iostream>
# include <string.h>
# include <stdlib.h>
# include <vector>
# include <fstream>
# include<string>
# include <math.h>

using namespace std ;

typedef vector <vector<char>> vChar ;

class Maze{
  public :
    vChar vMaze, rMaze ; // vMaze vector ，存走過的所有地方 ; rMaze vector ，存路徑
    int goalNum, findGoalNum ; // goalNum 存的是目標的個數，findGoalNum 存的是目前找到的目標個數
    int hight , width ; // hight 存的是迷宮的長, width 存的是迷宮的寬
    int preWidth, preHight ; // preWidth 存的是最近老鼠退回來的長座標, preHight 存的是最近老鼠退回來的寬座標
    vector <vector<int>>  goalPosition ; // 儲存G的位置

    Maze( string fileName ) { // 設定Maze裡面的東西
      setLength( fileName ) ;  // 設定 hight , width ，也就是迷宮的長寬
      preWidth = 0 ; // 初始化preWidth
      preHight = 0 ; // 初始化preHight
      vMaze = setvMaze( fileName ) ; //將迷宮原始的樣貌放入vMaze
      rMaze = vMaze ; // 複製vMaze，放入rMaze
      checkG( vMaze ) ; // 設定goalPosition，也就是記錄下G的位置，放入goalPosition
      findGoalNum = 0 ; // 設定一開始還未找到任何G
    } // maze()

    bool findGoal( vChar m, int nowWidth, int nowHight, int direction ) { // 尋找能找到所有在迷宮中的G的遞迴

      if ( vMaze[nowHight].at(nowWidth) == 'V' ) // 若這是已經走過的路，則回傳錯誤
        return false ;
      else if ( vMaze[nowHight].at(nowWidth) == 'G' ) { // 如果現在的位置是G
        if ( checkGisNew( nowHight , nowWidth ) ) { // 如果這個G是第一次經過
          findGoalNum ++ ;                          // 找到G的數量+1，也就是findGoalNum +1
          if ( findGoalNum == goalNum ) {   // 如果加上這個G就已經把所有的G都找完了
            completeRMaze(m) ;              // 用m填補rMaze的空洞，因為在這之前rMaze只負責記錄退回來但仍是路徑的R，而m紀錄的是走過一次，且確定可以到達G的R
            return true ;
          } // if()
        } // if()
        else
          return false ;                   // If this G has found, then return false
      } // else if()
      else {                                  // 如果現在的位置不是G，也不是V
        vMaze[nowHight].at(nowWidth) = 'V' ;  // 代表這個位置是E，所以將其標記上V於vMaze
        m[nowHight].at(nowWidth) = 'R' ;      // 也將其標記上R於m
      } // else

      int directSet[4][2] = { {-1,0},{0,1} ,{1,0} ,{0,-1} } ; // 上下左右移動時，長的位置，與寬的位置的增減

      for ( int i = 0; i < 4 ; i++ ) { // 上下左右走走看
        int dir = (direction+i)%4 ;  // 先設定前進的方向
        if ( ( nowHight + directSet[dir][0] >= 0 ) && ( nowHight + directSet[dir][0] < hight ) &&   //接著判斷是否超過迷宮邊界
             ( nowWidth + directSet[dir][1] >= 0 ) && ( nowWidth + directSet[dir][1] < width ) ) {
          char nextChar = vMaze[nowHight + directSet[dir][0]].at(nowWidth + directSet[dir][1]) ;    // 記錄下未來一格會是哪一種地格


          if ( ( nextChar =='E' ) || ( nextChar =='G' ) ) { // 如果不是走過的路，或是O


            bool next = findGoal( m, nowWidth + directSet[dir][1], nowHight + directSet[dir][0], dir ) ; // 使用遞迴，看下一個位置延伸出去的路徑，是否可以到達全部的G
            if ( next ){ // 如果可以
              preHight = 0 ;  // 初始化preHight
              preWidth = 0 ;  // 初始化preWidth
              return true ;  // return success
            }
            else {  // 如果不行
                if ( ( rMaze[nowHight + directSet[dir][0]].at(nowWidth + directSet[dir][1]) =='R' ) ){ // 看下一個位置是否在 rMaze 上標註過
                    if ( rMaze[nowHight].at(nowWidth) != 'G' ) // 如果是，代表目前這一格也會是R，這時當格不等於G
                      rMaze[nowHight].at(nowWidth) = 'R' ;

                } // if()
                else if ( m[preHight].at(preWidth) == 'G' )   // 如果是從G退回來的，則此格也為R
                  rMaze[nowHight].at(nowWidth) = 'R' ;
            } // else
          } // if()
        } // if()
      } // for()

      preHight = nowHight ;  // 當上下左右都不行走，代表已經無路可走了，只能原路返回
      preWidth = nowWidth ;  // 故記錄下當時的長和寬，以便之後使用

      return false ;  // return not success
    } // findGoal()


    bool findShortestPath( vChar m, vChar &vRecord, int nowWidth, int nowHight, int direction, vChar &shortestPath ) { // 尋找能找到所有在迷宮中的G的遞迴

      if ( vMaze[nowHight].at(nowWidth) == 'G' ) { // 如果現在的位置是G
        shortestPath = m ;
        return true ;
      } // if()
      else if ( ( pathLength( m ) ) >= ( pathLength( shortestPath ) ) ) { // 如果還未到達的路徑長已經>=之前能找到的最短路徑
        return false ;
      }
      else if ( vRecord[nowHight].at(nowWidth) == 'E' ) {   // 如果還未走過，且為E
        m[nowHight].at(nowWidth) = 'R' ;
        vRecord[nowHight].at(nowWidth) = 'V' ;

        if ( vMaze[nowHight].at(nowWidth) =='E' )
          vMaze[nowHight].at(nowWidth) = 'V' ;
      } // else if()


      vChar preVRecord = vRecord ;   // 存之前該路徑走過的所有地格
      vChar preShortest = shortestPath ;  // 存之前的最短路徑
      bool haveNewShortest = false ;     // 存是否有找到新的最短路徑
      int directSet[4][2] = { {-1,0},{0,1} ,{1,0} ,{0,-1} } ; // 上下左右移動時，長的位置，與寬的位置的增減

      for ( int i = 0; i < 4 ; i++ ) { // 上下左右走走看
        int dir = (direction+i)%4 ;  // 先設定前進的方向

        if ( ( nowHight + directSet[dir][0] >= 0 ) && ( nowHight + directSet[dir][0] < hight ) &&   //接著判斷是否超過迷宮邊界
             ( nowWidth + directSet[dir][1] >= 0 ) && ( nowWidth + directSet[dir][1] < width ) ) {

          char nextChar = vRecord[nowHight + directSet[dir][0]].at(nowWidth + directSet[dir][1]) ;    // 記錄下未來一格會是哪一種地格
          if ( ( ( nextChar == 'E' ) || ( nextChar =='G' ) ) &&
               ( (nowHight + directSet[dir][0] != preHight ) || ( nowWidth + directSet[dir][1] != preWidth ) ) ) { // 如果是空格或是G，且並非上一個退下來的格子

            bool next = findShortestPath( m, vRecord, nowWidth + directSet[dir][1], nowHight + directSet[dir][0], dir, shortestPath ) ; // 使用遞迴，看下一個位置延伸出去的路徑，是否可以找到新的最短路徑
            if ( next ){ // 如果可以
              if ( pathLength( preShortest ) <= pathLength( shortestPath ) ) {  // 看有沒有比之前的最短路徑還要短
                shortestPath = preShortest ;    // 沒有的話，還原shortestPath
              } // if()
              else {
                preShortest = shortestPath ;    // 有的話，取代shortestPath
                haveNewShortest = true ;        // 並且標示已經找到新的最短路徑
              } // else
            } // if()
          } // if()
        } // if()

        vRecord = preVRecord ; // 還原vRecord
      } // for( i = 4 )

      preHight = nowHight ;  // 當上下左右都不行走，代表已經無路可走了，只能原路返回
      preWidth = nowWidth ;  // 故記錄下當時的長和寬，以便之後使用

      if ( ( nowHight == 0 ) && ( nowWidth == 0 ) && ( haveNewShortest ) ) // 當退回原點時，把rMaze更新成真正的最短路徑(如果存在的話)
        rMaze = shortestPath ;

      return haveNewShortest ;  // return yes or not find the new shortest path
    } // findGoal()

    int pathLength( vChar m ) {  // 算迷宮m中，R有幾個 == 路徑長
      int num = 0 ;
      for ( int i = 0 ; i < hight ; i++ ) {
        for( int j = 0 ; j < width ; j++ ) {
          if ( m[i].at(j) == 'R' )
            num++ ;
        } // for()
      } // for()

      return num + 1 ;
    } // pathLength

    bool checkGisNew( int hight, int width ) { // 確認這個位置，若是G，有沒有走過
      bool newG = true ;  // 先設為true
      for ( int i = 0; i < goalPosition.size() ; i++ ) { // 接著檢查每組G的長寬是否符合參數提供的值
        if ( ( width == goalPosition[i].at(1) ) &&  ( hight == goalPosition[i].at(0) ) ) { // 若符合
          if ( goalPosition[i].at(2) == 1 ){   // 發現之前已經走過了
            newG = false ;        // return false
          } // if()
          else {
            goalPosition[i].at(2) = 1 ;        // 若沒有，則紀錄已經有走訪過此G了
          } // else


          i = goalPosition.size() ;           // 找到有匹配的G了，跳出迴圈
        } // if()
      } // for()

      return newG ;         // return the result
    } // checkGisNew()

    void checkG( vChar m  ) {     // 記錄下所有G的位置於goalPosition
      int num = 0 ;     // 充當index
      for ( int i = 0 ; i < hight ; i++ ) {
        for ( int j = 0 ; j < width ; j++ ) {
          if ( m[i].at(j) == 'G') { // 若位置為G
            vector <int> temp ;
            goalPosition.push_back(temp) ;
            goalPosition[num].push_back( i ) ;   // 則將此位置存入goalPosition
            goalPosition[num].push_back( j ) ;
            goalPosition[num].push_back( 0 ) ;
            num++ ;
          } // if()
        } // for()
      } // for()
    } // checkG()


    void completeRMaze( vChar m ) {  // 把m的R補到rMaze上
      for ( int i = 0 ; i < hight ; i++ ) {
        for ( int j = 0 ; j < width ; j++ ) {
          if ( m[i].at(j) == 'R' ) // 當m是R時就補rMaze上
            rMaze[i].at(j) = m[i].at(j) ;
        } // for()
      } // for()
    } // completeRMaze()

    void setLength( string fileName ) {  // 設定迷宮的長與寬
      ifstream ifs( "input" + fileName + ".txt" ) ; // 開檔
      string temp[2], s ;

      getline( ifs, s ) ; // 從檔案中取得一行，存在s中
      s = s + " " ; // 幫s的最後加上一個空格，因為判斷獨立數字時要使用
      int index = 0 ;  // s的index
      for ( int i = 0 ; i < 2 ; i++ ) {  //找到兩個數字即可停下
        while ( s[index] != ' ' ) {   // 當不為空格時持續紀錄數字的字元
          temp[i] = temp[i] + s[index] ;
          index++ ;
        } // while()

        index++ ;
      } // for()

      hight = 0 ;  // 使hight和width歸於0，以便等會兒紀錄數字
      width = 0 ;
      for( int i = 0 ; i < 2 ; i++ ) {
        int stringSize = temp[i].size() ; // 記下該數字的最高位數
        for( int j = 0 ; j < stringSize ; j++ ) {
          if ( i == 1 )
            hight = hight + ( int( temp[i][j] ) - 48 ) *pow(10,stringSize - j - 1 ) ; // 計算方法為，該位數的數字，乘以十位數的次方
          else
            width = width + ( int( temp[i][j] ) - 48 ) *pow(10,stringSize - j - 1 ) ; // 寬亦同
        } // for()
      } // for(
    } // setlength()


    vChar setvMaze( string fileName ) { // 把迷宮原始模樣放入一個vChar中，並回傳
      ifstream ifs( "input" + fileName + ".txt" ) ;
      vChar original ; // 將迷宮存入此vChar
      string s ; //紀錄迷宮一行的字串
      getline( ifs, s ) ; // 先將表示長寬的那行讀掉
      for ( int i = 0 ; i < hight ; i++ ) {
        vector <char> temp ;  // 接著設一個char的vector
        original.push_back(temp) ; // 將此vector添加在original的最後一個元素的後方
        getline( ifs, s ) ;  // 開始正式讀迷宮資料
        for ( int j = 0 ; j < width ; j++ ) {  // 將個別的字母一一填入
          original[i].push_back(s[j]) ;
        } // for()
      } // for()

      return original ; // return the maze
    } // setvMaze()

    vChar setvAllR() { // 回傳一個全是R的迷宮
      vChar r ;
      for ( int i = 0 ; i < hight ; i++ ) {
        vector <char> temp ;  // 接著設一個char的vector
        r.push_back(temp) ; // 將此vector添加在r的最後一個元素的後方
        for ( int j = 0 ; j < width ; j++ ) {  // 將R一一填入
          r[i].push_back('R') ;
        } // for()
      } // for()

      return r ;
    } // setvAllR


    void show( char type ) {     // 印出迷宮矩陣
      vChar m ;
      if ( type == 'v' )          // type為v，是要印vMaze，不是的話則是rMaze，以此設定m
        m = vMaze ;
      else
        m = rMaze ;


      for ( int i = 0 ; i < hight ; i++ ) {        // 將m以迷宮的規格印出
        for ( int j = 0 ; j < width ; j++ ) {
          cout << m[i].at(j) ;
        } // for()

        cout << endl ;
      } // for()

      cout << endl ;

    } // show()

    void clr() {  // 清除 Maze 中，所有 vector 中的元素
      for ( int i = 0 ; i < hight ; i++ ) {
            vMaze[i].clear() ;
            rMaze[i].clear() ;
      } // for()

      for ( int i = 0 ; i < goalNum ; i++ ) {
             goalPosition[i] ;
      } // for()

    } // clr()

    int isNumber( string s ) {  // 處理傳入的字元，轉化成數字並回傳，字元非真正數字，則回傳0
      int sSize = s.size() ;  // 記下s的大小
      string number = "" ;    // 另立一個字串，給真正的數字
      bool isNum = true ;     // 紀錄是否為數字
      for ( int i = 0 ; i < sSize ; i++ ) {
        if ( s[i] != ' ' ) {  // 當此字元不等於空格
          int t = int( s[i] ) ;  // 取得其ascii code的數字
          if ( ( t - 48 < 0 ) || ( t - 48 > 9 ) ){   // 檢查其是否為1-9
            isNum = false ;             // 不是則設定isNum為false
          } // if()
          else
            number = number + s[i] ;    // 是的話，放入number
        } // if()
      } // for()

      if ( isNum ) {   // 若是數字，開始轉化成int
        int numSize = number.size() ; // 記下該數字的最高位數
        if ( numSize != 0 ) { // 若最高位不為0(排除都是空格的狀況)
          int num = 0 ;
          for( int j = 0 ; j < numSize ; j++ ) {
            num = num + ( int ( number[j] ) -48 ) * pow( 10, numSize - j - 1 ) ; // 計算方法為，該位數的數字，乘以該位的十位數的次方
          } // for()

          return num ;  // 成功則回傳該數字
        } // for()
      } // if()

      return 0 ;   // 否則傳回  0

    } // isNumber()


};

int main(void) {
  int command = 0 ; // 用以儲存

  do {
    string fileName ;  // 用以儲存檔案名稱

    cout << endl << "*** Path Finding ***" ; // 輸出指引
    cout << endl << "* 0.Quit           *" ;
    cout << endl << "* 1.One goal       *" ;
    cout << endl << "* 2.More goals     *" ;
    cout << endl << "* 3.Shortest path  *" ;
    cout << endl << "********************" ;
    cout << endl << "Input a command(0, 1, 2, 3): " ;
    cin >> command ;

    if ( ( command == 1 ) || ( command == 2 ) || ( command == 3 ) ) { // 如果沒有要離開
      cout << endl << "Input a file number: " ;
      cin >> fileName ;
      ifstream ifs("input" + fileName + ".txt"); //開檔
      int exist = ifs.is_open() ; // 紀錄是否開檔
      if ( ! exist ) // 若無法開檔，輸出提示，並開啟下一輪
          cout << endl << "input" + fileName + ".txt" + " does not exist!" << endl ;
      else {  // 若可以，則開始後續處理
        Maze maze( fileName ) ; // 設立maze
        string number = "" ;
        int goalNum = -1 ;    // 轉化為int的目標數量(現在還沒有)
        if ( ( command == 1 ) || ( command == 3 ) )  // command == 1 或== 3 ，代表目標只有一個
          goalNum = 1 ;       // 故，更新goalNum為1
        else {   // 若有多個目標
          while ( ( goalNum % 1 != 0 ) || ( goalNum < 1 ) ) {  // 當輸入的字串並非真正的合格數字時
            cout << endl << "Number of G (goals): " ;
            cin >> number ;   // 請使用者輸入字串
            goalNum  = maze.isNumber( number ) ; // 判斷字串，並處理後回傳合格數字，或者表示錯誤的0
          } // while()
        } // else

        maze.goalNum = goalNum ;  // 最終得到的 goalNum 設給 maze.goalNum
        bool success = false ;
        if ( command == 3 ) {   // 如果是要尋找最短路徑
          vChar temp = maze.vMaze; // 設定一個變數 temp ，存入最原始的迷宮
          vChar shortPath = maze.setvAllR() ;  // 設定一個變數 shortPath ，存入全部都為R的迷宮
          success = maze.findShortestPath( maze.vMaze, temp,0, 0, 1, shortPath ) ; // 紀錄是否成功找到路徑
        } // if()
        else
          success = maze.findGoal( maze.vMaze, 0, 0, 1 ) ; // 紀錄是否成功找到路徑

        maze.show( 'v' ) ;  // 無論如何，先秀出v的迷宮
        if ( success ) {  // 若成功找到路徑
          maze.show( 'r' ) ;  // 則秀出r的迷宮
          if ( command == 3 )   // 若是要尋找最短路徑
            cout << endl << "Shortest path length = " << maze.pathLength( maze.rMaze ) << endl; // 輸出最短路徑的長度
        } // if()

        maze.clr() ; // 最後發動清潔，以準備好迎接下一個輪迴
      } // else()
    } // if()
    else if ( command == 0 ) // 如果輸入的command == 0 ，則離開這個迴圈
      break ;
    else  // 如果輸入了錯誤指令，則給予提醒，並直接開啟下個輪迴
      cout << endl << "Command does not exist!" << endl ;
  } while(true) ; // 在沒有其他狀況下，迴圈會進行到永遠

  return 0 ;
} // main()
