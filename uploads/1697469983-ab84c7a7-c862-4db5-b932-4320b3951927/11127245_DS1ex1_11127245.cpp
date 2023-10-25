// 11127245 ������  ��u�G�A 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum direction{
// �A���D���A�o�˶i��P�_���ɭԤ������� 
	Right = 0, 
	Down  = 1,
	Left  = 2,
	Up    = 3,
};



// ��class�M���B�z��ƿ�J�æs�i�]�m���ܼƸ̭� 
class FileHandler {
public:
    FileHandler(string temp) {
    // �b�c�ب�Ƥ��]�m���W
        fileName = temp;
    } // FileHandler()

    bool openAndCheckFile() {
    // �T�{�O�_�������Q���} 
        file.open(fileName.c_str());         // �H�N�r���ন�r�����} 
        
        if (!file.is_open()) {
            cout << endl << fileName << " does not exist!" << endl;
            return false;
        }
        else{
        	return true;	
		}
    } // openAndCheckFile()
    
    void readData(int &x, int &y) {
    // Ū�J�g�c�һݪ��j�p 
    	int  number;
    	char nextChar;
    	x = 0, y = 0;
		while (file >> number) {        // �NŪ�J�쪺���Ʀr�s�inumber 
        	if (x == 0)  x = number;
			else         y = number;
			
        	nextChar = file.get();
        	
        	if (nextChar == '\n')  return;
			
    	} // while()
    	
	} // readData()
	
	vector<char> setMatrix(int row, int column) {
	// �]�m�x�}�ҥ]�t���� 
    	vector <char> maze(row*column);
    	char nextChar;
    	file >> nextChar;
	    for (int i = 0; i < row*column ; i++) {
	    	
	    	if (nextChar == 'O')       maze[i] = 'O';
	        else if (nextChar == 'E')  maze[i] = 'E';
	        else if (nextChar == 'G')  maze[i] = 'G';
			else cout << endl << "There has illeage element: " << nextChar << endl;
			
			file >> nextChar;    // Ū�J�U�@�Ӧr���æs�JnextChar 
    	} // for()
    	
    	return maze;
	} // setMatrix()

    void closeFile() {      // ��������� 
        file.close();
    } // closeFile()

private:
    string fileName;
    ifstream file;         // �гyifstream ���� file 
    
}; // class FileHandler



// ��class�B�z������V�M�һݲ��ʪ���V��� 
class WalkingLogic{
public:
	int row, column;      // �y�� 
	
	WalkingLogic(int x, int y) {
	// �ϥκc�ب�ƪ�l�Ʀ�B�C 
		row    = x;
		column = y;
	}
	
	int decideDirec(int location, int direc) {
	// �M�w�n������V 
		if      (direc == Right) return goRight(location);
		else if (direc == Down)  return goDown(location);
		else if (direc == Left)  return goLeft(location);
		else if (direc == Up)    return goUp(location);
	} // decideDirec()
	
	int goRight(int location) { // �V�k���@�� 
		return location+=1;
	} // goRight()
	
	int goDown(int location) {  // �V�U���@��
		return location+=row;
	} // goDown()
	
	int goLeft(int location) {  // �V�����@��
		return location-=1; 
	} // goLeft()
	
	int goUp(int location) {    // �V�W���@��
		return location-=row;
	} // goUp()
	
private:
	
}; // class WalkingLogic



// �B�z�g�c����Ʊ�
// e.g.(�O�_�i�H���ʡB�O�_�W�L���ʰϰ�B�j�����|�B�L�X�g�c....) 
class Maze : public WalkingLogic{
public:
	vector <char> maze;          // �g�c������ 
	vector <int>  G_Location;    // ���� G����m
	vector <int>  R_Location;    // ���� R����m 
	int G_Amount;                // �ؼв��I�Ӽ� 
	
	Maze(int x, int y, int amount, vector <char> temp) : WalkingLogic(x, y) {
	// Maze����l�ơA���K�I�s WalkingLogic���c�ب�ƶi���l�� 
		row      = x;
		column   = y;
		maze     = temp;
		G_Amount = amount;            // �w�]��0 
	} // Maze() : WalkingLogic()
	
	void walked(int location) {  // �Z���L���d�UV 
		maze[location]  = 'V';
	} // walked()
	
	bool callFindExit(int curLocation, int curDirection) {
	// �̾ڲ��I�Ӽƶi��h���I�s findExit()
		while(G_Amount != 0) {
			if (!findExit(curLocation, curDirection))
				return false;
			else
				G_Amount-=1;   // ���\���@�Ӳ��I�ɡA�ݧ���I�`��-1 
		}
		
		return true;
	} // callFindExit()
	
	bool findExit(int curLocation, int curDirection) {
	// ####### �D�n�B��覡�����j�Abase case������ G�Y return true #######
		
		if (maze[curLocation] == 'G') {           // base case
			G_Location.push_back(curLocation);    // �N G����m�O���U�� 
			maze[curLocation] = 'R';              // �N G�л\�A�קK�M��h�Ӳ��I�ɡA���ƦP���I 
			return true;                          // �^��true�A�Y��ܦ��\���@�Ӳ��I 
		}
		
		walked(curLocation);                      // �Z���L���d�U V 
		
		for (int i = 0; i < 4 ; i++) {                                   // �k�W���U��4���`�� 
		
			// e.g.[�Y�{�b�����A(��+0)%4 = ���B(��+1)%4 =�W�B(��+2)%4 = �k�B(��+3)%4 =�U ] 
			int newDirection = (curDirection+i) % 4;
			int newLocation  = decideDirec(curLocation, newDirection);   // ���M�w����V�i�沾��
			
			if (canMove(newLocation, newDirection) && maze[newLocation] != 'V') {
			// �T�{�O�_�i��(����ê���A�W�X�x�}) �P �O�_�������j���L���� 
				
				if (findExit(newLocation, newDirection)) {               // ���ܹJ��base case   
				
					// �������j�ɡA�|�q�����I�^��_�I 
					// �B�b�w���L���W�^�h�ɡA���|��¶�������p 
					maze[curLocation] = 'R';                             // �^�h�����令 R 
					bool repeat = false;                                 // �O�_����
					for (int j = 0 ; j < R_Location.size() ; j++){
						if(R_Location[j] == curLocation) repeat = true;  // �O�_�b���� R����Ƹ̭������Ƹ�� 
					} // for() 
					
					if(!repeat) 
						R_Location.push_back(curLocation);               // �S���N�x�s 
						
					return true; // �����I 
				} // if(�����I)
			} // if(�i�H���ʥB�S���L) 
		} // for(�|�Ӥ�V) 
		
		return false; // �S�����I 
	} // findExit() 
	
	bool canMove(int newLocation, int mode) {
	// �T�{�S�����ζW�X���Ψ���I�F 
		if (!overBlock(newLocation, mode) && !hasObstacle(newLocation)) // �W�X�ϰ� && ����ê�� 
			return true;
		else 
			return false;
	} // canMove()
	
	bool overBlock(int newLocation, int mode) {  
	// �V�k�N�T�{ X���d��B�V���N�T�{ X���d��
	// �V�U�h�T�{ Y���d��B�V�W�h�T�{ Y���d�� 
		if (newLocation < 0 || newLocation > row*column-1)  return true;  // �W�X��Ӱg�c 
		else if (mode == Right && newLocation%row == 0)     return true;  // �V�k���W�X�d��
		else if (mode == Down && newLocation >= row*column) return true;  // �V�k���W�X�d��
		else if (mode == Left && (newLocation+1)%row == 0)  return true;  // �V�k���W�X�d��
		else if (mode == Up && newLocation < 0)             return true;  // �V�k���W�X�d��
		else                                                return false;
	} // overBlock()
	
	bool hasObstacle(int newLocation) {
	// �T�{�e��O�_����ê�� 
		if(maze[newLocation] == 'O')  return true;
		else                          return false;
	} // hasObstacle()
	
	void printV() {
	// �L�X�]�t V���|���g�c 
		cout << endl;
		for (int i = 0 ; i < G_Location.size() ; i++) {
		// �]�� G�b�i�滼�j�ɳQ�\�L�h�A�ҥH�ݭn�_��L�쥻����m
			int temp = G_Location[i];
			maze[temp] = 'G';
		} // for() 
		
		for (int i = 0 ; i < maze.size() ; i++) {
		// �]�� V�b�������j�ɳQ R�\�L�h�A�ҥH�ݭn�_��L�쥻����m
			if (maze[i] == 'R') cout << 'V';
			else                cout << maze[i];
			
	    	if ((i + 1) % row == 0) cout << endl;
		} // for()
	} // printV()
	
	void printR() {
	// �L�X�]�t R���|���g�c
		cout << endl;
		for (int i = 0 ; i < R_Location.size() ; i++) {
		// ���� R�|�Q�h�����j��V�\�L�h�A�ҥH�ݭn�_��L�쥻����m
			int temp = R_Location[i];
			maze[temp] = 'R';
		} // for()
		
		for (int i = 0 ; i < G_Location.size() ; i++) {
		// �]�� G�b�i�滼�j�ɳQ�\�L�h�A�ҥH�ݭn�_��L�쥻����m
			int temp = G_Location[i];
			maze[temp] = 'G';
		} // for()
		
		for (int i = 0 ; i < maze.size() ; i++) {
		// �]�� V�b�L�X R���|���g�c�S�ΡA�ҥH V�ର E 
			if (maze[i] == 'V') cout << 'E';
			else                cout << maze[i];
	    	if ((i + 1) % row == 0) cout << endl;
		} // for()
	} // printR()
	
	void end(){          // �����òM�z�Ŷ� 
		maze.clear();
		G_Location.clear();
		R_Location.clear();
	} // end()
};

int main(void) {
	int  command = 0;
	bool continueMaze = true;
	
	do {
		string  fileName;           // ���W 
		int     G_Amount;           // �ؼ��`�� 
		
		cout << endl << "*** Path Finding ***";
		cout << endl << "* 0. Quit          *";
		cout << endl << "* 1. One goal      *";
		cout << endl << "* 2. More goals    *";
		cout << endl << "********************";
		cout << endl << "Input a commnad(0, 1, 2): ";
		cin >> command;
		
		if ((command == 1) || (command == 2)) {
			
			int           row, column;      // ��C 
			vector<char>  mazeList;       // �g�c���� 
			G_Amount = 1;                   // ���w���@�ӥؼСA�w�]��1 
			
    		cout << endl << "Input a file number (e.g., 201, 202,...): ";
    		cin >> fileName;
    		fileName = "input" + fileName + ".txt";

    		FileHandler fileHandler(fileName);   // �N��J�����W��J FileHandler���c�ب�� 

    		if (fileHandler.openAndCheckFile()) {                      // �T�{�O�_��Ū�즹�ɮ� 
    			fileHandler.readData(row, column);                     // Ū�i�̭������
    			if (row > 0 && column > 0) {                           // �קK�� 0�M�t�Ưx�} 
	    			mazeList = fileHandler.setMatrix(row, column);    // �N�g�c�s�_�� 
	     			fileHandler.closeFile();                          // �������ɮ� 
	     			
	     			if (command == 2) {              // �߰ݻݭn���ؼ��`�� 
		    			int tempNum = 1;             // �ȮɥΨӦs�ؼЪ� 
		    			
		    			cout << endl << "Number of G (goals): ";
		    			cin  >> tempNum;
		    			while (tempNum <= 0 || tempNum > 100) {
		    			// �S�ؼЫܥi�d�A�ؼФӦh�e������ 
		    				cout << endl << "### The number must be in [1,100] ###" << endl;
		    				cout << endl << "Number of G (goals): ";
		    				cin >> tempNum;
						} // while()
						
						G_Amount = tempNum;
					} // if(command = 2) 
		   			
				    Maze  aMaze(row, column, G_Amount, mazeList);  // �N�g�c���򥻸�ƶ�J Maze���c�ب�� 
				    
					if (aMaze.callFindExit(0, Right)) {            // �����������ؼмơA��X�L�� V�BR���| 
				    	aMaze.printV();
				    	aMaze.printR();
					} // if()
					else {                                         // ���Ѫ��u�ા�D���L���� 
				    	aMaze.printV();
					} // else()
					
				    aMaze.end();                                   // �B�z�@�U�Ŷ�
				    mazeList.clear();                              // �B�z�@�U�g�c���� 
				} // if(���`�x�}�j�p)
				else {
					cout << endl << "There's something wrong with the size of this maze"  <<endl;
				}
    		} // if(���i�H�}��)
		} // if (1 || 2)
		
		else if (command == 0)
			continueMaze = false;                              // ������g�c�{�� 
			
		else
			cout << endl << "Command does not exist!" << endl; // �W�X�A�Ƚd�� 
		
	} while(continueMaze); // ���F 0�A���򦹰g�c���� 
	
} // main()

