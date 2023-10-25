// 11127217 ���ۦ� 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class maze {
	private:
	public:
		int goalnum, findstart ; // �M�䪺�ؼм� ;�ĴX�������I
		vector<vector<char> > graph, final, finalpath; // �̲׸��|��
		vector<int> goalx, goaly; // �ؼЩҦb��x�b�My�b 
		int width, high; // // �g�c���e�M�� 
		vector<vector<char> > Right( vector<vector<char> >, int, int, int, int); //�M�䨫�L�����u(�k) 
		vector<vector<char> > Down( vector<vector<char> >, int, int, int, int);//�M�䨫�L�����u(�U) 
		vector<vector<char> > Left( vector<vector<char> >, int, int, int, int);//�M�䨫�L�����u(��) 
		vector<vector<char> > Up( vector<vector<char> >, int, int, int, int);//�M�䨫�L�����u(�W) 
		vector<vector<char> > Pathright( vector<vector<char> >, int, int, int, int);//�M��̲׸��u(�k) 
		vector<vector<char> > Pathdown( vector<vector<char> >, int, int, int, int);//�M��̲׸��u(�U) 
		vector<vector<char> > Pathleft( vector<vector<char> >, int, int, int, int);//�M��̲׸��u(��) 
		vector<vector<char> > Pathup( vector<vector<char> >, int, int, int, int);//�M��̲׸��u(�W) 
		void Draw( vector<vector<char> > );//ø�s�g�c 
		void Change( vector<vector<char> >, int );//�ഫ�g�c 
};

int main() {
	maze tsum;
	int test, round; 
	char command = 'a', point; // ��J�����O 
	string filename; // �ɮ׽s�� 
	ifstream in;
	while ( command != '0' ) { //����O����0�N�@���i�� 
		vector<vector<char> > maze; // �Ȧs�g�c 
		tsum.graph.clear();
		tsum.goalx.clear(); //�M�ũҦ��s�񪺦a�� 
		tsum.goaly.clear();
		cout << endl << "*** Path Finding ***" << endl;
		cout << "* 0. Quit          *" << endl;
		cout << "* 1. One goal      *" << endl;
		cout << "* 2. More goals    *" << endl;
		cout << "********************" << endl;
		cout << "Input a command(0, 1, 2): ";
		cin >> command; //��J���O 
		cout << endl;
		if(command=='0')  //�p�G���O��0�N���� 
			break;
		else if ( command!='1' && command != '2' ) //��J1�M2�H�~�����O 
			cout << "Command does not exist!" << endl;
		else {
			cout  << "Input a file number: ";
			cin >> filename;
			filename = "input" + filename + ".txt"; // ��_���㪺�ɮצW�� 
			in.open(filename.c_str()); //�}���ɮ� 
			if ( in.fail() ) // ���ɮפ��s�b�N��Xfilename does not exist! 
				cout << endl << filename << " does not exist!"<< endl;
			else{
				if ( command == '1' ) //����O��1�ɳ]�w�M��ؼмƬ�1 
					tsum.goalnum = 1;
				else{ //����O��2�ɳ]�w�M��ؼмƬ���J���Ʀr 
					cout << endl << "Number of G (goals): ";
					cin >> tsum.goalnum;
				}
				
				round = tsum.goalnum; //
				in >> tsum.width >> tsum.high; // ��J�g�c���e�M�� 
				
				for(int i=0; i < tsum.high; i++) {  //�N�g�cŪ�J�ܼȦs����m 
        			vector<char> line;                  
        			for(int j=0; j < tsum.width; j++) {   
		    			in >> point;                             
            			line.push_back(point);            
        			} // for
		  
        			maze.push_back(line);            
    			} // for 
    			
				in.close();	 //�����ɮ� 
				tsum.graph = maze;  // ��g�c��J 
				tsum.graph = tsum.Right( tsum.graph, tsum.width, tsum.high, 0, 0); //�M�䨫�L�����| 
				
				if ( tsum.goalnum > 0 ) { //����|���s�b�ɴN��X�Ҧ����L���� 
					tsum.Draw( tsum.graph );
				}// if
				else { //����|�s�b�N��X�̲׸��| 
					tsum.findstart = 0; //��F���I������ 
					tsum.final = tsum.Pathright( tsum.final, tsum.width, tsum.high, tsum.goalx[0], tsum.goaly[0]) ; //�M��Ĥ@��G�����u 
    				for ( int p = 1; p < round; p++) { //�M���LG�����u 
    					tsum.findstart = 0;
    					tsum.Change(tsum.finalpath, p); //�ק�g�c����ܪ��A 
	    				tsum.final = tsum.Pathright( tsum.finalpath, tsum.width, tsum.high, tsum.goalx[p], tsum.goaly[p]) ;
    				} // for
    				tsum.Change(tsum.finalpath, -1); // -1��ܭn�i��g�c���̫�ק� 
    				tsum.Draw(tsum.finalpath); //��X�̲׸��u 
				}// else
			}//else
		} // else
		
	}//while
}

vector<vector<char> > maze::Right( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	
	if ( xaxis == width ) { //������ɴN����e�i 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'G') { //���G 
		if ( goalnum >= 0 ) { //��ثe��쪺G���ƶq���W�L�ݭn���ƶq�N��G����m�s�_�� 
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // goal
		maze[yaxis][xaxis] = 'D'; //�N�L��G��אּD�קK���ƭp�� 
		goalnum = goalnum - 1; //���N�N�ؼмƴ�@ 
		if ( goalnum == 0 ){ // �p�G����ƶq�N��X���L���� 
			Draw( maze );
			final = maze;
		}
		maze = Right( maze, width, high, xaxis+1, yaxis); //�~��e�i 
		maze = Down( maze, width, high, xaxis, yaxis+1); //���s  
		maze = Left( maze, width, high, xaxis-1, yaxis); //���s  
		maze = Up( maze, width, high, xaxis, yaxis-1); //���s  
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E') { //�I��E�N�~�� 
		maze[yaxis][xaxis] = 'V'; //�⨫�L������אּV 
		maze = Right( maze, width, high, xaxis+1, yaxis); //�~��e�i  
		maze = Down( maze, width, high, xaxis, yaxis+1); //���s  
		maze = Left( maze, width, high, xaxis-1, yaxis); //���s  
		maze = Up( maze, width, high, xaxis, yaxis-1); //���s  
		return maze;
	}
	else { //�I���L���ਫ���Ÿ��N���� 
		return maze;
	}
}// Right

vector<vector<char> > maze::Down( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	if ( yaxis == high ) { //������ɴN����e�i 
		return maze;
	}
	if ( maze[yaxis][xaxis] == 'G') { //���G 
		if ( goalnum >= 0 ) { //��ثe��쪺G���ƶq���W�L�ݭn���ƶq�N��G����m�s�_��  
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // if
		maze[yaxis][xaxis] = 'D'; //�N�L��G��אּD�קK���ƭp�� 
		goalnum = goalnum - 1; //���N�N�ؼмƴ�@ 
		if ( goalnum == 0 ){  // �p�G����ƶq�N��X���L����
			Draw( maze);
			final = maze;
		}
		maze = Down( maze, width, high, xaxis, yaxis+1); //�~��e�i 
		maze = Left( maze, width, high, xaxis-1, yaxis); //���s  
		maze = Up( maze, width, high, xaxis, yaxis-1); //���s  
		maze = Right( maze, width, high, xaxis+1, yaxis); //���s  
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E' ) { //�I��E�N�~�� 
		maze[yaxis][xaxis] = 'V'; //�⨫�L������אּV 
		maze = Down( maze, width, high, xaxis, yaxis+1); //�~��e�i 
		maze = Left( maze, width, high, xaxis-1, yaxis); //���s  
		maze = Up( maze, width, high, xaxis, yaxis-1); //���s  
		maze = Right( maze, width, high, xaxis+1, yaxis); //���s  
		return maze;
	}
	else {//�I���L���ਫ���Ÿ��N����
		return maze;
	}
} // Down

vector<vector<char> > maze::Left( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	if ( xaxis < 0 ) { //������ɴN����e�i 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'G') { //���G 
		if ( goalnum >= 0 ) { //��ثe��쪺G���ƶq���W�L�ݭn���ƶq�N��G����m�s�_��  
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // if
		maze[yaxis][xaxis] = 'D'; //�N�L��G��אּD�קK���ƭp�� 
		goalnum = goalnum - 1; //���N�N�ؼмƴ�@ 
		if ( goalnum == 0 ){ // �p�G����ƶq�N��X���L���� 
			Draw( maze);
			final = maze;
		}
		maze = Left( maze, width, high, xaxis-1, yaxis); //�~��e�i 
		maze = Up( maze, width, high, xaxis, yaxis-1); //���s  
		maze = Right( maze, width, high, xaxis+1, yaxis); //���s  
		maze = Down( maze, width, high, xaxis, yaxis+1); //���s  
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E') { //�I��E�N�~�� 
		maze[yaxis][xaxis] = 'V'; //�⨫�L������אּV 
		maze = Left( maze, width, high, xaxis-1, yaxis); //�~��e�i 
		maze = Up( maze, width, high, xaxis, yaxis-1); //���s  
		maze = Right( maze, width, high, xaxis+1, yaxis); //���s  
		maze = Down( maze, width, high, xaxis, yaxis+1); //���s  
		return maze;
	}
	else {//�I���L���ਫ���Ÿ��N����
		return maze;
	}
}// Left

vector<vector<char> > maze::Up( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	if ( yaxis < 0 ) { //������ɴN����e�i 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'G') { //���G 
		if ( goalnum >= 0 ) { //��ثe��쪺G���ƶq���W�L�ݭn���ƶq�N��G����m�s�_��  
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // if
		maze[yaxis][xaxis] = 'D'; //�N�L��G��אּD�קK���ƭp�� 
		goalnum = goalnum - 1; //���N�N�ؼмƴ�@ 
		if ( goalnum == 0 ){ // �p�G����ƶq�N��X���L���� 
			Draw( maze );
			final = maze;
		}
		else{
			maze = Up( maze, width, high, xaxis, yaxis-1 ); //�~��e�i 
			maze = Right( maze, width, high, xaxis+1, yaxis); //���s  
			maze = Down( maze, width, high, xaxis, yaxis+1); //���s  
			maze = Left( maze, width, high, xaxis-1, yaxis); //���s  
		}//else
		 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E' ) { //�I��E�N�~�� 
		maze[yaxis][xaxis] = 'V'; //�⨫�L������אּV 
		maze = Up( maze, width, high, xaxis, yaxis-1 ); //�~��e�i 
		maze = Right( maze, width, high, xaxis+1, yaxis); //���s  
		maze = Down( maze, width, high, xaxis, yaxis+1); //���s  
		maze = Left( maze, width, high, xaxis-1, yaxis); //���s  
		return maze;
	}
	else { //�I���L���ਫ���Ÿ��N���� 
		return maze;
	}
} // Up

void maze::Draw( vector<vector<char> > maze) {
	for(int i=0;i<maze.size();i++) {         
        for(int j=0;j<maze[i].size();j++) {  
            if( maze[i][j] == 'D') //�]��D�쥻�OG�ҥH�N���X��G 
            	cout<<'G';
			else
          	  cout<<maze[i][j]; 
        } // for
		                                                 
        cout << endl;                                                            
    }  // for
    		
    cout << endl; 
} // Draw

vector<vector<char> > maze::Pathright( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {
	if ( xaxis == width ) { //������ɴN����e�i 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //���^���I�άO�����LG���̲׸��u 
		if ( ( yaxis == 0 && xaxis == 0))  //���^���I�N��аO��A 
			maze3[yaxis][xaxis] = 'A';
		findstart = findstart + 1; //�^���I�άO��LG���̲׸��u������ 
		if ( findstart == 1 ) //�Ĥ@���^���I�άO��LG���̲׸��u�N��sfinalpath 
			finalpath = maze3;
		return maze3;
	}

	if ( maze3[yaxis][xaxis] == 'V' || maze3[yaxis][xaxis] == 'D') { //�u��V�i�H��,D�N�O�쥻��G 
		if ( maze3[yaxis][xaxis] == 'V') //�N���L��V�аO��A,D�аO��C 
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //�~��e�i
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1); //���s  
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //���s  
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //���s  
		if(maze3[yaxis][xaxis] == 'C') //���s���^�ӴN�N��ק�^�h 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A') 
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //�I���L���ਫ���Ÿ��N����  
		return maze3;
	}
}

vector<vector<char> > maze::Pathdown( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {

	if ( yaxis == high ) { //������ɴN����e�i 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //���^���I�άO�����LG���̲׸��u 
		if ( ( yaxis == 0 && xaxis == 0))
			maze3[yaxis][xaxis] = 'A'; //���^���I�N��аO��A 
		findstart = findstart + 1; //�^���I�άO��LG���̲׸��u������ 
		if ( findstart == 1 ) //�Ĥ@���^���I�άO��LG���̲׸��u�N��sfinalpath 
			finalpath = maze3;
		return maze3;
	}
	
	if ( maze3[yaxis][xaxis] == 'V'|| maze3[yaxis][xaxis] == 'D') { //�u��V�i�H��,D�N�O�쥻��G  
		if ( maze3[yaxis][xaxis] == 'V')
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1);  //�~��e�i 
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //���s  
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //���s  
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //���s  
		if(maze3[yaxis][xaxis] == 'C') //���s���^�ӴN�N��ק�^�h 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A')
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //�I���L���ਫ���Ÿ��N����  
		return maze3;
	}
}

vector<vector<char> > maze::Pathleft( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {

	if ( xaxis < 0 ) { //������ɴN����e�i 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //���^���I�άO�����LG���̲׸��u 
		if ( ( yaxis == 0 && xaxis == 0))
			maze3[yaxis][xaxis] = 'A'; //���^���I�N��аO��A 
		findstart = findstart + 1; //�^���I�άO��LG���̲׸��u������ 
		if ( findstart == 1 ) //�Ĥ@���^���I�άO��LG���̲׸��u�N��sfinalpath 
			finalpath = maze3;
		return maze3;
	}

	
	if ( maze3[yaxis][xaxis] == 'V'|| maze3[yaxis][xaxis] == 'D') { //�u��V�i�H��,D�N�O�쥻��G  
		if ( maze3[yaxis][xaxis] == 'V')
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //�~��e�i 
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //���s  
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //���s  
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1); //���s  
		if(maze3[yaxis][xaxis] == 'C') //���s���^�ӴN�N��ק�^�h 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A')
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //�I���L���ਫ���Ÿ��N����  
		return maze3;
	}
}

vector<vector<char> > maze::Pathup( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {

	if ( yaxis < 0 ) { //������ɴN����e�i 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //���^���I�άO�����LG���̲׸��u 
		if ( ( yaxis == 0 && xaxis == 0)) //���^���I�N��аO��A 
			maze3[yaxis][xaxis] = 'A';
		findstart = findstart + 1; //�^���I�άO��LG���̲׸��u������ 
		if ( findstart == 1 ) //�Ĥ@���^���I�άO��LG���̲׸��u�N��sfinalpath 
			finalpath = maze3;
		return maze3;
	}
	
	if ( maze3[yaxis][xaxis] == 'V'|| maze3[yaxis][xaxis] == 'D') { //�u��V�i�H��,D�N�O�쥻��G  
		if ( maze3[yaxis][xaxis] == 'V')
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //�~��e�i 
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //���s 
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1); //���s  
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //���s  
		if(maze3[yaxis][xaxis] == 'C') //���s���^�ӴN�N��ק�^�h 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A') 
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //�I���L���ਫ���Ÿ��N����  
		return maze3;
	}
}

void maze::Change( vector<vector<char> > maze, int q) {
	for(int i=0;i<maze.size();i++) {         
        for(int j=0;j<maze[i].size();j++) {  
            if( maze[i][j] == 'A') { //A��̲ܳת����u,�N��令R 
            	maze[i][j] = 'R';
			}// if
			if( maze[i][j] == 'C') { //C��ܥؼ�,�N��令G
            	maze[i][j] = 'G';
			}// if
			if( q == -1){ // �P�_�ؼЬO�_�����䧹, ���䧹�N�i�H�N��L��V��^E 
				if( maze[i][j] == 'V') 
            		maze[i][j] = 'E';
			}
				
        } // for                                                            
    }  // for
    finalpath = maze; //�N�ק�᪺�g�c�Ǩ�finalpath 
} // Draw


