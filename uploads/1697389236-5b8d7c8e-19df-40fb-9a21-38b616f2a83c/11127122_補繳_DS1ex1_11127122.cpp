// 11127122 �J�K��
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
    vChar vMaze, rMaze ; // vMaze vector �A�s���L���Ҧ��a�� ; rMaze vector �A�s���|
    int goalNum, findGoalNum ; // goalNum �s���O�ؼЪ��ӼơAfindGoalNum �s���O�ثe��쪺�ؼЭӼ�
    int hight , width ; // hight �s���O�g�c����, width �s���O�g�c���e
    int nowWidth, nowHight ; // nowHight �s���O�ثe���ѹ������y��, nowWidth �s���O�ثe���ѹ����e�y��
    int preWidth, preHight ; // preWidth �s���O�̪�ѹ��h�^�Ӫ����y��, preHight �s���O�̪�ѹ��h�^�Ӫ��e�y��
    vector <vector<int>>  goalPosition ; // �x�sG����m

    Maze( string fileName ) { // �]�wMaze�̭����F��
      setLength( fileName ) ;  // �]�w hight , width �A�]�N�O�g�c�����e
      nowWidth = 0 ; // �]�w�{�b����m�b���I
      nowHight = 0 ; // �]�w�{�b����m�b���I
      preWidth = 0 ; // ��l��preWidth
      preHight = 0 ; // ��l��preHight
      vMaze = setvMaze( fileName ) ; //�N�g�c��l���˻���JvMaze
      rMaze = vMaze ; // �ƻsvMaze�A��JrMaze
      checkG( vMaze ) ; // �]�wgoalPosition�A�]�N�O�O���UG����m�A��JgoalPosition
      findGoalNum = 0 ; // �]�w�@�}�l�٥�������G
    } // maze()

    bool findGoal( vChar m, int nowWidth, int nowHight, int direction ) { // �M�����Ҧ��b�g�c����G�����j

      if ( vMaze[nowHight].at(nowWidth) == 'V' ) // �Y�o�O�w�g���L�����A�h�^�ǿ��~
        return false ;
      else if ( vMaze[nowHight].at(nowWidth) == 'G' ) { // �p�G�{�b����m�OG
        if ( checkGisNew( nowHight , nowWidth ) ) { // �p�G�o��G�O�Ĥ@���g�L
          findGoalNum ++ ;                          // ���G���ƶq+1�A�]�N�OfindGoalNum +1
          if ( findGoalNum == goalNum ) {   // �p�G�[�W�o��G�N�w�g��Ҧ���G���䧹�F
            completeRMaze(m) ;              // ��m���rMaze���Ŭ}�A�]���b�o���erMaze�u�t�d�O���h�^�Ӧ����O���|��R�A��m�������O���L�@���A�B�T�w�i�H��FG��R
            return true ;
          } // if()
        } // if()
        else
          return false ;                   // If this G has found, then return false
      } // else if()
      else {                                  // �p�G�{�b����m���OG�A�]���OV
        vMaze[nowHight].at(nowWidth) = 'V' ;  // �N��o�Ӧ�m�OE�A�ҥH�N��аO�WV��vMaze
        m[nowHight].at(nowWidth) = 'R' ;      // �]�N��аO�WR��m
      } // else

      int directSet[4][2] = { {-1,0},{0,1} ,{1,0} ,{0,-1} } ; // �W�U���k���ʮɡA������m�A�P�e����m���W��

      for ( int i = 0; i < 4 ; i++ ) { // �W�U���k������
        int dir = (direction+i)%4 ;  // ���]�w�e�i����V
        if ( ( nowHight + directSet[dir][0] >= 0 ) && ( nowHight + directSet[dir][0] < hight ) &&   //���ۧP�_�O�_�W�L�g�c���
             ( nowWidth + directSet[dir][1] >= 0 ) && ( nowWidth + directSet[dir][1] < width ) ) {
          char nextChar = vMaze[nowHight + directSet[dir][0]].at(nowWidth + directSet[dir][1]) ;    // �O���U���Ӥ@��|�O���@�ئa��


          if ( ( nextChar =='E' ) || ( nextChar =='G' ) ) { // �p�G���O���L�����A�άOO


            bool next = findGoal( m, nowWidth + directSet[dir][1], nowHight + directSet[dir][0], dir ) ; // �ϥλ��j�A�ݤU�@�Ӧ�m�����X�h�����|�A�O�_�i�H��F������G
            if ( next ){ // �p�G�i�H
              preHight = 0 ;  // ��l��preHight
              preWidth = 0 ;  // ��l��preWidth
              return true ;  // return success
            }
            else {  // �p�G����
                if ( ( rMaze[nowHight + directSet[dir][0]].at(nowWidth + directSet[dir][1]) =='R' ) ){ // �ݤU�@�Ӧ�m�O�_�b rMaze �W�е��L
                    if ( rMaze[nowHight].at(nowWidth) != 'G' ) // �p�G�O�A�N��ثe�o�@��]�|�OR�A�o�ɷ�椣����G
                      rMaze[nowHight].at(nowWidth) = 'R' ;

                } // if()
                else if ( m[preHight].at(preWidth) == 'G' )   // �p�G�O�qG�h�^�Ӫ��A�h����]��R
                  rMaze[nowHight].at(nowWidth) = 'R' ;
            } // else
          } // if()
        } // if()
      } // for()

      preHight = nowHight ;  // ��W�U���k�����樫�A�N��w�g�L���i���F�A�u������^
      preWidth = nowWidth ;  // �G�O���U��ɪ����M�e�A�H�K����ϥ�

      return false ;  // return not success
    } // findGoal()

    void completeRMaze( vChar m ) {  // ��m��R�ɨ�rMaze�W
      for ( int i = 0 ; i < hight ; i++ ) {
        for ( int j = 0 ; j < width ; j++ ) {
          if ( m[i].at(j) == 'R' ) // ��m�OR�ɴN��rMaze�W
            rMaze[i].at(j) = m[i].at(j) ;
        } // for()
      } // for()
    } // completeRMaze()

    void setLength( string fileName ) {  // �]�w�g�c�����P�e
      ifstream ifs( "input" + fileName + ".txt" ) ; // �}��
      string temp[2], s ;

      getline( ifs, s ) ; // �q�ɮפ����o�@��A�s�bs��
      s = s + " " ; // ��s���̫�[�W�@�ӪŮ�A�]���P�_�W�߼Ʀr�ɭn�ϥ�
      int index = 0 ;  // s��index
      for ( int i = 0 ; i < 2 ; i++ ) {  //����ӼƦr�Y�i���U
        while ( s[index] != ' ' ) {   // �����Ů�ɫ�������Ʀr���r��
          temp[i] = temp[i] + s[index] ;
          index++ ;
        } // while()

        index++ ;
      } // for()

      hight = 0 ;  // ��hight�Mwidth�k��0�A�H�K���|������Ʀr
      width = 0 ;
      for( int i = 0 ; i < 2 ; i++ ) {
        int stringSize = temp[i].size() ; // �O�U�ӼƦr���̰����
        for( int j = 0 ; j < stringSize ; j++ ) {
          if ( i == 1 )
            hight = hight + ( int( temp[i][j] ) - 48 ) *pow(10,stringSize - j - 1 ) ; // �p���k���A�Ӧ�ƪ��Ʀr�A���H�Q��ƪ�����
          else
            width = width + ( int( temp[i][j] ) - 48 ) *pow(10,stringSize - j - 1 ) ; // �e��P
        } // for()
      } // for(
    } // setlength()


    vChar setvMaze( string fileName ) { // ��g�c��l�Ҽ˩�J�@��vChar���A�æ^��
      ifstream ifs( "input" + fileName + ".txt" ) ;
      vChar original ; // �N�g�c�s�J��vChar
      string s ; //�����g�c�@�檺�r��
      getline( ifs, s ) ; // ���N��ܪ��e������Ū��
      for ( int i = 0 ; i < hight ; i++ ) {
        vector <char> temp ;  // ���۳]�@��char��vector
        original.push_back(temp) ; // �N��vector�K�[�boriginal���̫�@�Ӥ��������
        getline( ifs, s ) ;  // �}�l����Ū�g�c���
        for ( int j = 0 ; j < width ; j++ ) {  // �N�ӧO���r���@�@��J
          original[i].push_back(s[j]) ;
        } // for()
      } // for()

      return original ; // return the maze
    } // setvMaze()

    bool checkGisNew( int hight, int width ) { // �T�{�o�Ӧ�m�A�Y�OG�A���S�����L
      bool newG = true ;  // ���]��true
      for ( int i = 0; i < goalPosition.size() ; i++ ) { // �����ˬd�C��G�����e�O�_�ŦX�Ѽƴ��Ѫ���
        if ( ( width == goalPosition[i].at(1) ) &&  ( hight == goalPosition[i].at(0) ) ) { // �Y�ŦX
          if ( goalPosition[i].at(2) == 1 ){   // �o�{���e�w�g���L�F
            newG = false ;        // return false
          } // if()
          else {
            goalPosition[i].at(2) = 1 ;        // �Y�S���A�h�����w�g�����X�L��G�F
          } // else


          i = goalPosition.size() ;           // ��즳�ǰt��G�F�A���X�j��
        } // if()
      } // for()

      return newG ;         // return the result
    } // checkGisNew()

    void show( char type ) {     // �L�X�g�c�x�}
      vChar m ;
      if ( type == 'v' )          // type��v�A�O�n�LvMaze�A���O���ܫh�OrMaze�A�H���]�wm
        m = vMaze ;
      else
        m = rMaze ;


      for ( int i = 0 ; i < hight ; i++ ) {        // �Nm�H�g�c���W��L�X
        for ( int j = 0 ; j < width ; j++ ) {
          cout << m[i].at(j) ;
        } // for()

        cout << endl ;
      } // for()

      cout << endl ;

    } // show()

    void checkG( vChar m  ) {     // �O���U�Ҧ�G����m��goalPosition
      int num = 0 ;     // �R��index
      for ( int i = 0 ; i < hight ; i++ ) {
        for ( int j = 0 ; j < width ; j++ ) {
          if ( m[i].at(j) == 'G') { // �Y��m��G
            vector <int> temp ;
            goalPosition.push_back(temp) ;
            goalPosition[num].push_back( i ) ;   // �h�N����m�s�JgoalPosition
            goalPosition[num].push_back( j ) ;
            goalPosition[num].push_back( 0 ) ;
            num++ ;
          } // if()
        } // for()
      } // for()
    } // checkG()

    void clr() {  // �M�� Maze ���A�Ҧ� vector ��������
      for ( int i = 0 ; i < hight ; i++ ) {
            vMaze[i].clear() ;
            rMaze[i].clear() ;
      } // for()

      for ( int i = 0 ; i < goalNum ; i++ ) {
             goalPosition[i] ;
      } // for()

    } // clr()

    int isNumber( string s ) {  // �B�z�ǤJ���r���A��Ʀ��Ʀr�æ^�ǡA�r���D�u���Ʀr�A�h�^��0
      int sSize = s.size() ;  // �O�Us���j�p
      string number = "" ;    // �t�ߤ@�Ӧr��A���u�����Ʀr
      bool isNum = true ;     // �����O�_���Ʀr
      for ( int i = 0 ; i < sSize ; i++ ) {
        if ( s[i] != ' ' ) {  // ���r��������Ů�
          int t = int( s[i] ) ;  // ���o��ascii code���Ʀr
          if ( ( t - 48 < 0 ) || ( t - 48 > 9 ) ){   // �ˬd��O�_��1-9
            isNum = false ;             // ���O�h�]�wisNum��false
          } // if()
          else
            number = number + s[i] ;    // �O���ܡA��Jnumber
        } // if()
      } // for()

      if ( isNum ) {   // �Y�O�Ʀr�A�}�l��Ʀ�int
        int numSize = number.size() ; // �O�U�ӼƦr���̰����
        if ( numSize != 0 ) { // �Y�̰��줣��0(�ư����O�Ů檺���p)
          int num = 0 ;
          for( int j = 0 ; j < numSize ; j++ ) {
            num = num + ( int ( number[j] ) -48 ) * pow( 10, numSize - j - 1 ) ; // �p���k���A�Ӧ�ƪ��Ʀr�A���H�Ӧ쪺�Q��ƪ�����
          } // for()

          return num ;  // ���\�h�^�ǸӼƦr
        } // for()
      } // if()

      return 0 ;   // �_�h�Ǧ^  0

    } // isNumber()
};

int main(void) {
  int command = 0 ; // �ΥH�x�s

  do {
    string fileName ;  // �ΥH�x�s�ɮצW��

    cout << endl << "*** Path Finding ***" ; // ��X����
    cout << endl << "* 0.Quit           *" ;
    cout << endl << "* 1.One goal       *" ;
    cout << endl << "* 2.More goals     *" ;
    cout << endl << "********************" ;
    cout << endl << "Input a command(0,1,2): " ;
    cin >> command ;

    if ( ( command == 1 ) || ( command == 2 ) ) { // �p�G�S���n���}
      cout << endl << "Input a file number: " ;
      cin >> fileName ;
      ifstream ifs("input" + fileName + ".txt"); //�}��
      int exist = ifs.is_open() ; // �����O�_�}��
      if ( ! exist ) // �Y�L�k�}�ɡA��X���ܡA�ö}�ҤU�@��
          cout << endl << "input" + fileName + ".txt" + " does not exist!" << endl ;
      else {  // �Y�i�H�A�h�}�l����B�z
        Maze maze( fileName ) ; // �]��maze
        string number = "" ;
        int goalNum = -1 ;    // ��Ƭ�int���ؼмƶq(�{�b�٨S��)
        if ( command == 1 )   // command == 1�A�N��ؼХu���@��
          goalNum = 1 ;       // �G�A��sgoalNum��1
        else {   // �Y���h�ӥؼ�
          while ( ( goalNum % 1 != 0 ) || ( goalNum < 1 ) ) {  // ���J���r��ëD�u�����X��Ʀr��
            cout << endl << "Number of G (goals): " ;
            cin >> number ;   // �ШϥΪ̿�J�r��
            goalNum  = maze.isNumber( number ) ; // �P�_�r��A�óB�z��^�ǦX��Ʀr�A�Ϊ̪�ܿ��~��0
          } // while()
        } // else

        maze.goalNum = goalNum ;  // �̲ױo�쪺 goalNum �]�� maze.goalNum
        bool success = maze.findGoal( maze.vMaze, 0, 0, 1 ) ; // �����O�_���\�����|
        maze.show( 'v' ) ;  // �L�צp��A���q�Xv���g�c
        if ( success ) {  // �Y���\�A�u�����@�����|��F����G
          maze.show( 'r' ) ;  // �h�q�Xr���g�c
        } // if()

        maze.clr() ; // �̫�o�ʲM��A�H�ǳƦn�ﱵ�U�@�ӽ��j
      } // else()
    } // if()
    else if ( command == 0 ) // �p�G��J��command == 0 �A�h���}�o�Ӱj��
      break ;
    else  // �p�G��J�F���~���O�A�h���������A�ê����}�ҤU�ӽ��j
      cout << endl << "Command does not exist!" << endl ;
  } while(true) ; // �b�S����L���p�U�A�j��|�i���û�

  return 0 ;
} // main()
