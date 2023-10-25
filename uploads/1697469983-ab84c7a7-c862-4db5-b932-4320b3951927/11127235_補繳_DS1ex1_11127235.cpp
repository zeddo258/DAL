// 11127235 �\�ʵ� 
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

class Maze {
public:
    vector<vector<char> > maze; // �ϥΤG��vector�x�s�g�c 
    int rows; // �g�c����� 
    int cols; // �g�c���C�� 

    // �c�y��ơA��l�ưg�c����
    Maze(int rows, int cols) : rows(rows), cols(cols), maze(rows, vector<char>(cols, ' ')) {};

    // ���J�g�c��� 
    bool loadMaze(string fileName) {
        ifstream inFile(fileName.c_str()); // �Ыؤ@���y��H'inFile'�A���}�PŪ�����w��󤺮e 
        if (!inFile) {                     //  '.c_str()'�N�r�Ŧ��ഫ��C����r�Ŧ�     
            cout << fileName << " doesn't exist!" << endl;
            return false;
        }

        inFile >> cols >> rows; // Ū���g�c����ƩM�C�� 

        // ���s���t�g�c�j�p
        maze = vector<vector<char> >(rows, vector<char>(cols, ' '));

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                char cell;
                inFile >> cell;
                maze[row][col] = cell;
                if (inFile.peek() == '\n') { // �ˬd���U�@�r�ŬO�_������� �A'inFile.peek()' ��^�U�@�Ӧr�ŦӤ��q�y�������� 
                    inFile.get(); // Ū���éI�������
                }
            }
        }
        inFile.close(); //�������y'inFile' 
    }

    bool findV(int x, int y, int direction) {
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            return false; // �W�X�g�c��ɡA��^false
        }

        // �p�G��e��m�O��ê�� 'O' �Τw�g���L�� 'V'�A��^false
        if (maze[x][y] == 'O' || maze[x][y] == 'V') {
            return false;
        }

        // �p�G���ؼ� 'G'�A��^true
        if (maze[x][y] == 'G') {
            return true;
        }

        // �Хܦ���m�w���L 
        maze[x][y] = 'V';


        // �w�q�|�Ӳ��ʤ�V�������q�A(dx, dy) ���O��ܥk�B�U�B���B�W�|�Ӥ�V
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};

        // ���ե��b�ϥΪ���V
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if (findV(newX, newY, direction)) {
            return true; // �p�G���q���A��^true
        }

        // ���դU�@�Ӥ�V 
        for (int newD = (direction + 1) % 4; newD != direction; newD = (newD + 1) % 4) { //(direction + 1) % 4 ��e��V���U�@�Ӥ�V 
            newX = x + dx[newD];
            newY = y + dy[newD];
            if (findV(newX, newY, newD)) {
                return true; // �p�G���q���A��^true
            }
        }

        // �p�G�|�Ӥ�V���S�������A��^false
        return false;
    }
    
    bool findMoreV(int x, int y, int direction, int numOfG ) {
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            return false; // �W�X�g�c��ɡA��^false
        }

        // �p�G��e��m�O��ê�� 'O' �Τw�g���L�� 'V'�A��^false
        if (maze[x][y] == 'O' || maze[x][y] == 'V') {
            return false;
        }

        // �p�G���ؼ� 'G'�A��^true
        if (maze[x][y] == 'G') {
        	numOfG -- ;
        	if ( numOfG == 0 ) {			
              return true;
            }
        }

        // �Хܦ���m�w���L 
        if ( maze[x][y] != 'G') {
          maze[x][y] = 'V';
        }

        // �w�q�|�Ӳ��ʤ�V�������q�A(dx, dy) ���O��ܥk�B�U�B���B�W�|�Ӥ�V
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};

        // ���ե��b�ϥΪ���V
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if (findMoreV(newX, newY, direction, numOfG)) {
            return true; // �p�G���q���A��^true
        }

        // ���դU�@�Ӥ�V 
        for (int newD = (direction + 1) % 4; newD != direction; newD = (newD + 1) % 4) {
            newX = x + dx[newD];
            newY = y + dy[newD];
            if (findMoreV(newX, newY, newD, numOfG)) {
                return true; // �p�G���q���A��^true
            }
        }

        // �p�G�|�Ӥ�V���S�������A��^false
        return false;
    }

    // �L�X�g�c 
    void printMaze() {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                cout << maze[row][col];
            }
            cout << endl;
        }
    }

    //��X����V�ݼаO��R�άOE 
    bool findR(int x, int y) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == 'O' || maze[x][y] == 'E' ) {
            return false; // �W�X��ɩΤ��O�Ө�����m
        }

        // �p�G�O�ؼ� 'G'�A��^true��ܤw����
        if (maze[x][y] == 'G') {
            return true;
        }
        
        // �w�g�ˬd�L����m�F 
        if (maze[x][y] == 'R') {
            return false;
        }
        // �аO��e��m�w���L 
        maze[x][y] = 'R';

       
        // �V�k��
        if (findR(x, y + 1)) {
            return true;
        }
        // �V�U��
        if (findR(x + 1, y)) {
            return true;
        }

         // �V����
        if (findR(x, y - 1)) {
            return true;
        }
        
        // �V�W��
        if (findR(x - 1, y)) {
            return true;
        }


        // �p�G�|�Ӥ�V���S�������A�^���A�аO�� 'E'
        maze[x][y] = 'E';
        return false;
    }
    
    bool findMoreR(int x, int y, int numOfG) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == 'O' || maze[x][y] == 'E' ) {
            return false; // �W�X��ɩΤ��O�Ө�����m
        }

        // �p�G�O�ؼ� 'G'�A��^true��ܤw����
        if (maze[x][y] == 'G') {
        	numOfG -- ;
        	if ( numOfG == 0) {
              return true;
            }
        }
        
        // �w�g�ˬd�L����m�F 
        if (maze[x][y] == 'R') {
            return false;
        }
        
        // �аO��e��m�w���L 
        if (maze[x][y] != 'G') {
          maze[x][y] = 'R';
        }

        // �V�k��
        if (findMoreR(x, y + 1, numOfG)) {
            return true;
        }

        // �V�U��
        if (findMoreR(x + 1, y, numOfG)) {
            return true;
        }


        // �V����
        if (findMoreR(x, y - 1, numOfG)) {
            return true;
        }
        
        // �V�W��
        if (findMoreR(x - 1, y, numOfG)) {
            return true;
        }

        
        // �p�G�|�Ӥ�V���S�������A�^���A�аO�� 'E'
        maze[x][y] = 'E';
        return false;
    }
};

int main() {
	char command = '0'; // �Ω���O��J 
    do  {
      
	  int fileNumber = 0;
      cout << endl ;
      cout << "*** Path Finding ***\n";
      cout << "* 0.Quit           *\n";
      cout << "* 1.One goal       *\n";
      cout << "* 2.More goals     *\n";
      cout << "********************\n";
      cout << "Input a command(0,1,2):";
      cin >> command;
	  if (command == '1' || command == '2') {
        int x = 0, y = 0, startDirection = 0; // ��l��m�����W��(0, 0)
        cout << endl << "Input a file number:";
        cin >> fileNumber;
        string fileName;  
        stringstream ss; //�Ыؤ@�Ӧr�Ŧ�y 
        ss << "input" << fileNumber << ".txt"; //�N��J�ɮ׸��X�������ɮצW 
        fileName = ss.str();  //�ե�'ss.str()�N�ɮצW�٦s�b'fileName'�� 
        Maze maze(0, 0); // �Ыؤ@��Maze����H�A�ê�l�� 
        if (maze.loadMaze(fileName)) { //�ˬd�O�_�����ɮסA���h�N���e�x�s�imaze 
            if (command == '1') { // ��@��'G' 
                if (maze.findV(x, y, startDirection)) { //�O�_�����'G' 
                    x = 0, y = 0; //���s��l�Ʀ�m�ܥ��W��(0,0) 
                    Maze vMaze(maze); //�Ыؤ@��Maze����HvMaze�Ψ��x�s�t��'V'����m�B���\���'G' 
                    cout << endl;
                    if (maze.findR(x, y)) { // ��X���\���|'R' 
                        vMaze.printMaze(); //��X�Ҧ��g�L��m���g�c 
                        cout << endl;
                        maze.printMaze(); // ��X�t���\���|���g�c 
                        cout << endl;
                    } 
                }
                else {
                	cout << endl;
                    maze.printMaze();
                    cout << endl;
				}
            } else if (command == '2') {
                cout << endl << "Number of G (goals):";
                int numOfG;
                cin >> numOfG; //��J�Q�n��X��'G' 
                x = 0, y = 0, startDirection = 0; 
                if (maze.findMoreV(x, y, startDirection, numOfG)) {
                	x = 0, y = 0; //���s��l�Ʀ�m�ܥ��W��(0,0) 
                    Maze vMaze(maze); //�Ыؤ@��Maze����HvMaze�Ψ��x�s�t��'V'����m�B���\���'G' 
                    cout << endl;
                    if (maze.findMoreR(x, y, numOfG)){ // ��X���\���|'R' 
                        vMaze.printMaze(); //��X�Ҧ��g�L��m���g�c 
                        cout << endl;
                        maze.printMaze(); // ��X�t���\���|���g�c 
                        cout << endl;
                    } 
                }
                else {
                	cout << endl;
                    maze.printMaze();  //��X���L��m���g�c 
                    cout << endl;
				}
			  }
            }
          
        
      } 
      else if (command == '0') {
        break;
      }
      else {
        cout << endl << "Command does not exist!" << endl;
      }
    } while (true);
	system("pause");
    return 0;
}















