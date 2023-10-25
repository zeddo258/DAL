// ����Ȥ@����
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Maze {
private:
    // ��ɤj�p
    int l_x = 0, l_y = 0;
    // �]�@�ӤG��vector�s�g�c
    vector<vector<char>>maze = {};
    bool success = false;
public:
    int ny = 0;

    bool IsEmpty() {
        if (maze.empty())
            return true;
        return false;
    } // IsEmpty()

    void setXY( int limit_x, int limit_y ){
        l_x = limit_x;
        l_y = limit_y;
    } // setXY

    void SuCCess(){
        success = true;
    } // SuCCess()

    bool GetSuc(){
        return success;
    } // GetSuc()

    int GetX(){
        return l_x;
    } // GetX

    int GetY(){
        return l_y;
    } // GetX

    void SetLineMaze( string s ) {
        int len = s.length();
        maze.push_back(vector<char>());
        for ( int i = 0 ; ny < l_y && l_x - i > 0 && i < len ; i ++ ) {
            char item;
            item = s[i];
            //cout << "item: " << item << endl;
            maze[ny].push_back(item);
            //cout << "maze: " << maze[ny][i] << endl;
        } // for

        ny = ny + 1;
    } // SetLineMaze

    void PrintAllMaze(){
        for ( int j = 0 ; j < l_y && j < maze.size() ; j ++ ) {
            for ( int i = 0 ; i < l_x && i < maze[j].size() ; i ++ ) {
                //char element = maze.at(j).at(i);
                char element = maze[j][i];
                if ( element == 'R' || element == 'T' )
                    cout << "V";
                else
                    cout << element;

            } // for(i)

            cout << endl;
        } // for(j)
    } // PrintAllMaze()

    void PrintMaze(){
        for ( int j = 0 ; j < l_y && j < maze.size() ; j ++ ) {
            for ( int i = 0 ; i < l_x && i < maze[j].size() ; i ++ ) {
                //char element = maze.at(j).at(i);
                char element = maze[j][i];
                if ( element == 'T' || element == 'V' )
                    cout << "E";
                else
                    cout << element;

            } // for(i)

            cout << endl;
        } // for(j)
    } // PrintMaze()


    void ChangeItem( int i, int j, char letter ){
        maze[i][j] = letter;
    } // ChangeItem()


    void ChangeElement( int i, int j ){
        if( maze[i][j] == 'E' )
            maze[i][j] = 'R';
        else if( maze[i][j] == 'R' )
            maze[i][j] = 'V';
        else if( maze[i][j] == 'V' )
            maze[i][j] = 'T';
    } // ChangeElement()



    char GetItem( int i, int j ){
        return maze[i][j];
    } // GetItem()

    bool CanGo( int i, int j, int round ){
        if( round < 4 ) {
            //cout << "Round: " << round << endl;
            if ( maze[i][j] == 'E' || maze[i][j] == 'G' )
                return true;
        } // ( < 4 )
        else if( round >= 4 && round < 8) {
            if ( maze[i][j] == 'R' ) {
                maze[i][j] = 'E';
                return true;
            } // ( R )
        } // ( 4 <= round < 8 )
        else if( round >= 8 ) {
            if ( maze[i][j] == 'V' ) {
                maze[i][j] = 'R';
                return true;
            } // ( R )
        } // ( 8 <= round < 12 )

        return false;
    } // CanGo

};


Maze Task1( Maze aMaze ) {
    //int i = 0, j = 0;
    int nowX = 0, nowY = 0;
    int mode = 1, round = 0;
    //�٨S����I�A�Χ䤣����I
    while( aMaze.GetItem( nowX, nowY ) != 'G' && aMaze.GetItem( nowX, nowY ) != 'T' ){
        //i = nowX;
        //j = nowY;
        // test :cout << "X: " << nowX << " Y: " << nowY << endl;
        // test :cout << "before" << aMaze.GetItem( nowX, nowY ) << endl;

        aMaze.ChangeElement( nowX, nowY );

        // test :cout << "after" << aMaze.GetItem( nowX, nowY ) << endl;
        // cout << "LX: " << aMaze.GetX() <<" LY: " << aMaze.GetY() << endl;
        for ( round = 0 ; round < 12 ; round ++ ) {
            if( mode == 1 && nowY + 1 < aMaze.GetX() ) {
                if( aMaze.CanGo( nowX, nowY + 1,round ) ) {
                    if( round >= 4 )
                        aMaze.ChangeElement( nowX, nowY );
                    nowY = nowY + 1;
                    break;
                } // if ( y + 1 )
            } // if (1)(�k)
            else if( mode == 2 && nowX + 1 < aMaze.GetY() ) {
                if( aMaze.CanGo( nowX + 1, nowY, round ) ) {
                    if( round >= 4 )
                        aMaze.ChangeElement( nowX, nowY );
                    nowX = nowX + 1;
                    break;
                } // if ( x + 1 )
            } // else if (2)(�U)
            else if( mode == 3 && nowY != 0 ) {
                if( aMaze.CanGo( nowX, nowY - 1, round ) ) {
                    if( round >= 4 )
                        aMaze.ChangeElement( nowX, nowY );
                    nowY = nowY - 1;
                    break;
                } // if ( y - 1 )
            } // else if (3)(��)
            else if( mode == 4 && nowX != 0 ) {
                if( aMaze.CanGo( nowX - 1, nowY, round ) ) {
                    if( round >= 4 )
                        aMaze.ChangeElement( nowX, nowY );
                    nowX = nowX - 1;
                    break;
                } // if ( x - 1 )
            } // else if (2)(�W)

            mode = mode + 1;
            if( mode > 4 ) mode = mode - 4;
        } // for

        // aMaze.PrintMaze();

        // cout << "_______________________"<< endl;

    } // while

    if(aMaze.GetItem( nowX, nowY ) == 'G')
        aMaze.SuCCess();
    return aMaze;
} // Task1()

Maze INPUT_TXT(string fileName, Maze aMaze) {

    fileName = "input" + fileName + ".txt";

    // ���}�奻�ɮץH�i��Ū��
    ifstream inputtxt; // �w���ɮת�cin�Aifstream�����O�ݭn����Ƥ@�Ӫ���~�ள�ӥΡC
    inputtxt.open(fileName);

    // �ˬd�O�_���\���}�ɮ�
    if (!inputtxt) {
        cout << endl << fileName <<" does not exist!" << endl;
        // �N���~�T��������X��׺ݡ]�Τ��^�A�Ӥ��g�L�зǿ�X�w�İϡC�o�ϱo���~�T���i�H�Y����ܡA�Ӥ����w�İϼv�T�C
        return aMaze ; // ��^���ק諸 aMaze
    } // if (!inputtxt)

    //��Ū��ɤj�p
    int limit_x = 0, limit_y = 0;

    inputtxt >> limit_x >> limit_y;
    aMaze.setXY( limit_x, limit_y );
    // �v��Ū���ɮפ��e
    string line;
    getline(inputtxt, line); // �⴫��Ū��
    while (getline(inputtxt, line)) {
        // �B�z�C�@�檺���e�A�Ҧp��X��зǿ�X
        // test : cout << line << endl;
        aMaze.SetLineMaze( line ) ;
    } // while (getline(inputtxt, line))

    // �����ɮ�
    inputtxt.close();

    return aMaze;
}

int main()
{
    int command = 0;

    while (true){
        Maze    aMaze;         // a matrix
        string  fileName;      // a file name
        // Modes mode = oneG;     // default: one goal
        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "******************";
        cout << endl << "Input a command(0, 1, 2): ";
        cin >> command;    // get the command
        if ((command == 1) || (command == 2)) {
            /*
            if (command ==2)
                mode = moreG; // one or more goals
            */
            cout << endl << "Input a file number (e.g., 201, 202, ...): ";
            cin >> fileName;
            aMaze = INPUT_TXT(fileName, aMaze);


            if ( !aMaze.IsEmpty() ) {
                if ( command == 1 )
                    aMaze = Task1( aMaze );
            } // if

            aMaze.PrintAllMaze();


            cout << endl;
            if(aMaze.GetSuc()){
                aMaze.ChangeItem( 0, 0, 'R' );
                aMaze.PrintMaze();
            } // if sucess





        } // end outer-if

        else if ( command == 0 )        // '0': stop the program
            break;
        else
            cout << endl << "Command does not exist!" << endl;
    } // while(true)

    system("pause"); // ���{���b�����e�Ȱ��A�H�K�Τ����ݨ�{������X�A�æb�Τ���U���N��������{�������C
    return 0;
}
