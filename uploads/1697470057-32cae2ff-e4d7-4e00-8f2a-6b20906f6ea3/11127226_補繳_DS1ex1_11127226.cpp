// 11127226 �����h
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class MazeClass {
    private:
        char maze[100][100];

    public:
        int length = 0, width = 0; // �g�c���e�ŧi
        bool load(string fileName){ // �ɤJ�ɮ�
            ifstream in ;
            string file = "input" + fileName + ".txt"; // �X���ɦW
            in.open(file); // �}���ɮ�

            if(in.fail()){ // �T�{�ɮ׬O�_���`�}��
                cout << endl << "input file opening failed or does not exist";
                return false ; // �}�Ҳ��`�h�^�� false
            }

            in >> width >> length ; // �]�w�g�c���e

            for(int i = 0 ; i < length ; i++) { // �]�w�g�c��T
                for(int j = 0 ; j < width ; j++){
                    in >> maze[i][j] ;
                }
            }

            return true; // �]�w�����h�^�� true

        }

        int shortpath = 0;
        bool findShortPath(MazeClass &vMaze, int x, int y, int direction, int path_len){ // �O��C��vMaze�ҧ��ܪ���T, x�By�N��ثe��m, direction�N��ثe��|��V, path_len���ثe�B��
            vMaze.changeV(0, 0); // �N��l�a�]���w���L
            if(path_len >= shortpath && shortpath != 0) // �p�G�B�Ƥj��ثe�̵u�����|�h�^��false
                return false ;

            bool turn_up = false ; // �O�_���ؼ�

            for (int i = direction; i < direction + 4; i++) { // �Ni�]���ثe��V, �è̷Ӷ��ǥk�B�U�B���B�W���j�]�L�ܤ�4��, �۹�����V�ҥN���ƭȬ�0�B1�B2�B3, �|��: i = 2, �ثe��V����, �ӥL���U�ӷ|�̥��B�W�B�k�B�U�h�P�_�O�_����
                if (i%4 == 0) {
                    if((vMaze.locationData(x, y+1) == 'E' || vMaze.locationData(x, y+1) == 'G' || (vMaze.locationData(x, y+1) == 'V' && shortpath != 0))){// �T�{�k��O�_��q��, ���n���ؼЫ�~��g�L�w���L����
                        if(vMaze.locationData(x, y+1) == 'G'){ // �T�{�O�_�k�䬰�ؼ�
                            if(shortpath == 0){ // �]�w��쪺�Ĥ@�Ӹ��|
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }
                            else if(path_len < shortpath){ // �p�G�s�������u�h��s
                                refresh() ;
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }

                        }
                        else
                            vMaze.changeV(x, y+1); // �p�G�k��i�q��B���O�ؼЫh�O�����w��g

                        if(findShortPath(vMaze, x, y+1, i, path_len+1)){ // ���k��i�滼�j, �p�G���򻼰j�����ؼ�, �h�N�ثe��m�]����ؼЪ����|���@
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';

                           turn_up = true;
                        }

                    }
                }
                else if (i%4 == 1) { // ���B�Ұ��欰�P�W, ����V���V�U
                    if((vMaze.locationData(x+1, y) == 'E' || vMaze.locationData(x+1, y) == 'G' || (vMaze.locationData(x+1, y) == 'V' && shortpath != 0))){
                        if(vMaze.locationData(x+1, y) == 'G'){
                            if(shortpath == 0){
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }
                            else if(path_len < shortpath){
                                refresh() ;
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x+1, y);

                        if(findShortPath(vMaze, x+1, y, i, path_len+1)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';

                            turn_up = true;
                        }

                    }
                }
                else if (i%4 == 2 ) { // ���B�Ұ��欰�P�W, ����V���V��
                    if((vMaze.locationData(x, y-1) == 'E' || vMaze.locationData(x, y-1) == 'G' || (vMaze.locationData(x, y-1) == 'V' && shortpath != 0))){ // 2
                        if(vMaze.locationData(x, y-1) == 'G'){
                            if(shortpath == 0){
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }
                            else if(path_len < shortpath){
                                refresh() ;
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x, y-1);

                        if(findShortPath(vMaze, x, y-1, i, path_len+1)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';

                            turn_up = true;
                        }

                    }
                }
                else if (i%4 == 3) { // ���B�Ұ��欰�P�W, ����V���V�W
                     if((vMaze.locationData(x-1, y) == 'E' || vMaze.locationData(x-1, y) == 'G' || (vMaze.locationData(x-1, y) == 'V' && shortpath != 0))){ // 3
                        if(vMaze.locationData(x-1, y) == 'G'){
                            if(shortpath == 0){
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }
                            else if(path_len < shortpath){
                                refresh() ;
                                maze[x][y] = 'R';
                                shortpath = path_len++ ;
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x-1, y);

                        if(findShortPath(vMaze, x-1, y, i, path_len+1)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';

                            turn_up = true;
                        }

                    }
                }

            }

            return turn_up ;
        }

        bool findGoals(MazeClass &vMaze, int x, int y, int direction, int & num_goals){ // �O��C��vMaze�ҧ��ܪ���T, x�By�N��ثe��m, direction�N��ثe��|��V, num_goals���ثe�ٻݭn�䪺�ؼмƶq
            vMaze.changeV(0, 0); // �N��l�a�]���w���L

            for (int i = direction; i < direction + 4; i++) { // �Ni�]���ثe��V, �è̷Ӷ��ǥk�B�U�B���B�W���j�]�L�ܤ�4��, �۹�����V�ҥN���ƭȬ�0�B1�B2�B3, �|��: i = 2, �ثe��V����, �ӥL���U�ӷ|�̥��B�W�B�k�B�U�h�P�_�O�_����
                if (i%4 == 0) { // �T�{�ثe��V�V�k
                    if((vMaze.locationData(x, y+1) == 'E' || vMaze.locationData(x, y+1) == 'G')){ // �T�{�k��O�_��q��
                        if(vMaze.locationData(x, y+1) == 'G'){ // �p�G�k�䬰�ؼ�, ���N�Ӧ�m��T����Q, �H�Q����P�_, �P�ɱN�ݭn�M�䪺�ؼм�-1
                            vMaze.changeQ(x, y+1);
                            num_goals--;
                            if(num_goals == 0){ // �p�G���F�����ؼ�, �h�N�^��true, �P�ɤ@�B�B�O���^�Ǩ��l��m���������|��aMaze��
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else // �p�G�k��i�q��B���O�ؼЫh�O�����w��g
                            vMaze.changeV(x, y+1);

                        if(findGoals(vMaze, x, y+1, i, num_goals)){ // ���k��i�滼�j, �p�G���򻼰j�����ؼ�, �h�N�ثe��m�]����ؼЪ����|���@
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0) // �p�G�������ؼЫh�i��^��true
                                return true ;
                        }

                    }
                }
                else if (i%4 == 1) { // ���B�Ұ��欰�P�W, ����V���V�U
                    if((vMaze.locationData(x+1, y) == 'E' || vMaze.locationData(x+1, y) == 'G')){
                        if(vMaze.locationData(x+1, y) == 'G'){
                            vMaze.changeQ(x+1, y);
                            num_goals--;
                            if(num_goals == 0){
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x+1, y);

                        if(findGoals(vMaze, x+1, y, i, num_goals)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0)
                                return true ;
                        }

                    }
                }
                else if (i%4 == 2 ) { // ���B�Ұ��欰�P�W, ����V���V��
                    if((vMaze.locationData(x, y-1) == 'E' || vMaze.locationData(x, y-1) == 'G')){ // 2
                        if(vMaze.locationData(x, y-1) == 'G'){
                            vMaze.changeQ(x, y-1);
                            num_goals--;
                            if(num_goals == 0){
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x, y-1);

                        if(findGoals(vMaze, x, y-1, i, num_goals)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0)
                                return true ;
                        }

                    }
                }
                else if (i%4 == 3) { // ���B�Ұ��欰�P�W, ����V���V�W
                     if((vMaze.locationData(x-1, y) == 'E' || vMaze.locationData(x-1, y) == 'G')){ // 3
                        if(vMaze.locationData(x-1, y) == 'G'){
                            vMaze.changeQ(x-1, y);
                            num_goals--;
                            if(num_goals == 0){
                                maze[x][y] = 'R';
                                return true ;
                            }
                        }
                        else
                            vMaze.changeV(x-1, y);

                        if(findGoals(vMaze, x-1, y, i, num_goals)){
                            if(maze[x][y] != 'G')
                                maze[x][y] = 'R';
                            if(num_goals == 0)
                                return true ;
                        }

                    }
                }

            }

            if (num_goals == 0) { // ���ƥؼЧ��h�^��ture
                return true;
            }

            return false; // �L�k������ؼЦ^��false
        }

        void changeV(int x, int y){ // �N�ҶǤJ����m��T����'V'
            maze[x][y] = 'V';
        }

        void changeQ(int x, int y){ // �N�ҶǤJ����m��T����'Q'
            maze[x][y] = 'Q';
        }

        char locationData(int x, int y){ // �ΥH���o�g�c��m����T
            return maze[x][y] ;
        }

        void show(){ // �ϥΰj��N�g�c���C�L�X��
            cout << endl;
            for( int i = 0 ; i < length ; i++ ) {
                for( int j = 0 ; j < width ; j++ ){
                    if(maze[i][j] == 'Q')
                        cout << 'G' ;
                    else
                        cout << maze[i][j] ;
                }
                cout << endl;
            }
        }

        void refresh(){
            for( int i = 0 ; i < length ; i++ ) {
                for( int j = 0 ; j < width ; j++ ){
                    if(maze[i][j] == 'R')
                        maze[i][j] = 'E' ;
                }
            }
        }

        void clr(){ // �ϥΰj��N�g�c�U��m�]��'\0'
            for( int i = 0 ; i < length ; i++ ) {
                for( int j = 0 ; j < width ; j++ ){
                    maze[i][j] = '\0' ;
                }
            }
            shortpath = 0 ;
        }
};

int main()
{
    int command = 0 ;

    do{
        string fileName ; // �ŧi�ɦW���s��
        MazeClass aMaze ; // �ŧi�@�Ӱg�cClass, �ΨӦs����ؼЪ����|��T
        int num_goals = 1 ; // �ŧi�g�c�ؼмƶq
        cout << endl << "*** Path Finding *****";
        cout << endl << "* 0. Quit            *";
        cout << endl << "* 1. One goal        *";
        cout << endl << "* 2. More gloals     *";
        cout << endl << "* 3. Shorttest path  *";
        cout << endl << "**********************";
        cout << endl << "Input a Command(0, 1, 2, 3): ";
        cin >> command ;
        if (command == 1 || command == 2 || command == 3){
            cout << endl << "Input a file number(e.g.,101, 102...): ";
            cin >> fileName ; // ��J�ɦW
            if(command == 2){ // �p�G���h�ӥؼЫh�hŪ���ؼмƶq
                cout << endl << "Number of G (goals): ";
                cin >> num_goals ;
            }

            if(aMaze.load(fileName)){ // �ɤJ�ɮרýT�{���L���`�}��
                MazeClass vMaze(aMaze); // �ŧi�@�Ӱg�cClass, �ΥH�s����g���|
                bool success = false;
                if (command == 3)
                    success = aMaze.findShortPath(vMaze, 0, 0, 0, 1); // �i�J��M�ؼЪ��禡, �����ؼЫh�Nsuccess�]��true, �L�hfalse
                else
                    success = aMaze.findGoals(vMaze, 0, 0, 0, num_goals); // �i�J��M�ؼЪ��禡, �����ؼЫh�Nsuccess�]��true, �L�hfalse

                vMaze.show(); // �N��g���|�i��
                if(success){ // �p�G���ؼЫh�N��ؼЪ����|��T�i��
                    aMaze.show();
                    if(command == 3)
                        cout << endl << "Shortest path length = " << aMaze.shortpath+1 << endl;
                }
                else if(command == 3)
                    cout << endl << "### There is no path to find a goal! ###" << endl ;

                vMaze.clr(); // �M���g�c��T
            }
            aMaze.clr(); // �M���g�c��T
        }
        else if(command == 0){ // �̷ӫ��O���}�j��
            break;
        }
        else{ // �L�����O
            cout << endl << "Command does not exist!" << endl;
        }

    }while(true);


    return 0;
}


