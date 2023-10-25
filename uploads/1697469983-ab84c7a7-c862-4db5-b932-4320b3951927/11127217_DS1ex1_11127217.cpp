// 11127217 陳彥汝 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class maze {
	private:
	public:
		int goalnum, findstart ; // 尋找的目標數 ;第幾次找到原點
		vector<vector<char> > graph, final, finalpath; // 最終路徑圖
		vector<int> goalx, goaly; // 目標所在的x軸和y軸 
		int width, high; // // 迷宮的寬和高 
		vector<vector<char> > Right( vector<vector<char> >, int, int, int, int); //尋找走過的路線(右) 
		vector<vector<char> > Down( vector<vector<char> >, int, int, int, int);//尋找走過的路線(下) 
		vector<vector<char> > Left( vector<vector<char> >, int, int, int, int);//尋找走過的路線(左) 
		vector<vector<char> > Up( vector<vector<char> >, int, int, int, int);//尋找走過的路線(上) 
		vector<vector<char> > Pathright( vector<vector<char> >, int, int, int, int);//尋找最終路線(右) 
		vector<vector<char> > Pathdown( vector<vector<char> >, int, int, int, int);//尋找最終路線(下) 
		vector<vector<char> > Pathleft( vector<vector<char> >, int, int, int, int);//尋找最終路線(左) 
		vector<vector<char> > Pathup( vector<vector<char> >, int, int, int, int);//尋找最終路線(上) 
		void Draw( vector<vector<char> > );//繪製迷宮 
		void Change( vector<vector<char> >, int );//轉換迷宮 
};

int main() {
	maze tsum;
	int test, round; 
	char command = 'a', point; // 輸入的指令 
	string filename; // 檔案編號 
	ifstream in;
	while ( command != '0' ) { //當指令不為0就一直進行 
		vector<vector<char> > maze; // 暫存迷宮 
		tsum.graph.clear();
		tsum.goalx.clear(); //清空所有存放的地方 
		tsum.goaly.clear();
		cout << endl << "*** Path Finding ***" << endl;
		cout << "* 0. Quit          *" << endl;
		cout << "* 1. One goal      *" << endl;
		cout << "* 2. More goals    *" << endl;
		cout << "********************" << endl;
		cout << "Input a command(0, 1, 2): ";
		cin >> command; //輸入指令 
		cout << endl;
		if(command=='0')  //如果指令為0就結束 
			break;
		else if ( command!='1' && command != '2' ) //輸入1和2以外的指令 
			cout << "Command does not exist!" << endl;
		else {
			cout  << "Input a file number: ";
			cin >> filename;
			filename = "input" + filename + ".txt"; // 串起完整的檔案名稱 
			in.open(filename.c_str()); //開啟檔案 
			if ( in.fail() ) // 當檔案不存在就輸出filename does not exist! 
				cout << endl << filename << " does not exist!"<< endl;
			else{
				if ( command == '1' ) //當指令為1時設定尋找目標數為1 
					tsum.goalnum = 1;
				else{ //當指令為2時設定尋找目標數為輸入的數字 
					cout << endl << "Number of G (goals): ";
					cin >> tsum.goalnum;
				}
				
				round = tsum.goalnum; //
				in >> tsum.width >> tsum.high; // 輸入迷宮的寬和高 
				
				for(int i=0; i < tsum.high; i++) {  //將迷宮讀入至暫存的位置 
        			vector<char> line;                  
        			for(int j=0; j < tsum.width; j++) {   
		    			in >> point;                             
            			line.push_back(point);            
        			} // for
		  
        			maze.push_back(line);            
    			} // for 
    			
				in.close();	 //關閉檔案 
				tsum.graph = maze;  // 把迷宮放入 
				tsum.graph = tsum.Right( tsum.graph, tsum.width, tsum.high, 0, 0); //尋找走過的路徑 
				
				if ( tsum.goalnum > 0 ) { //當路徑不存在時就輸出所有走過的路 
					tsum.Draw( tsum.graph );
				}// if
				else { //當路徑存在就找出最終路徑 
					tsum.findstart = 0; //到達原點的次數 
					tsum.final = tsum.Pathright( tsum.final, tsum.width, tsum.high, tsum.goalx[0], tsum.goaly[0]) ; //尋找第一個G的路線 
    				for ( int p = 1; p < round; p++) { //尋找其他G的路線 
    					tsum.findstart = 0;
    					tsum.Change(tsum.finalpath, p); //修改迷宮的顯示狀態 
	    				tsum.final = tsum.Pathright( tsum.finalpath, tsum.width, tsum.high, tsum.goalx[p], tsum.goaly[p]) ;
    				} // for
    				tsum.Change(tsum.finalpath, -1); // -1表示要進行迷宮的最後修改 
    				tsum.Draw(tsum.finalpath); //輸出最終路線 
				}// else
			}//else
		} // else
		
	}//while
}

vector<vector<char> > maze::Right( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	
	if ( xaxis == width ) { //當走到邊界就停止前進 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'G') { //找到G 
		if ( goalnum >= 0 ) { //當目前找到的G的數量不超過需要的數量就把G的位置存起來 
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // goal
		maze[yaxis][xaxis] = 'D'; //將過的G更改為D避免重複計算 
		goalnum = goalnum - 1; //找到就將目標數減一 
		if ( goalnum == 0 ){ // 如果找齊數量就輸出走過的路 
			Draw( maze );
			final = maze;
		}
		maze = Right( maze, width, high, xaxis+1, yaxis); //繼續前進 
		maze = Down( maze, width, high, xaxis, yaxis+1); //轉彎  
		maze = Left( maze, width, high, xaxis-1, yaxis); //轉彎  
		maze = Up( maze, width, high, xaxis, yaxis-1); //轉彎  
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E') { //碰到E就繼續走 
		maze[yaxis][xaxis] = 'V'; //把走過的路更改為V 
		maze = Right( maze, width, high, xaxis+1, yaxis); //繼續前進  
		maze = Down( maze, width, high, xaxis, yaxis+1); //轉彎  
		maze = Left( maze, width, high, xaxis-1, yaxis); //轉彎  
		maze = Up( maze, width, high, xaxis, yaxis-1); //轉彎  
		return maze;
	}
	else { //碰到其他不能走的符號就結束 
		return maze;
	}
}// Right

vector<vector<char> > maze::Down( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	if ( yaxis == high ) { //當走到邊界就停止前進 
		return maze;
	}
	if ( maze[yaxis][xaxis] == 'G') { //找到G 
		if ( goalnum >= 0 ) { //當目前找到的G的數量不超過需要的數量就把G的位置存起來  
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // if
		maze[yaxis][xaxis] = 'D'; //將過的G更改為D避免重複計算 
		goalnum = goalnum - 1; //找到就將目標數減一 
		if ( goalnum == 0 ){  // 如果找齊數量就輸出走過的路
			Draw( maze);
			final = maze;
		}
		maze = Down( maze, width, high, xaxis, yaxis+1); //繼續前進 
		maze = Left( maze, width, high, xaxis-1, yaxis); //轉彎  
		maze = Up( maze, width, high, xaxis, yaxis-1); //轉彎  
		maze = Right( maze, width, high, xaxis+1, yaxis); //轉彎  
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E' ) { //碰到E就繼續走 
		maze[yaxis][xaxis] = 'V'; //把走過的路更改為V 
		maze = Down( maze, width, high, xaxis, yaxis+1); //繼續前進 
		maze = Left( maze, width, high, xaxis-1, yaxis); //轉彎  
		maze = Up( maze, width, high, xaxis, yaxis-1); //轉彎  
		maze = Right( maze, width, high, xaxis+1, yaxis); //轉彎  
		return maze;
	}
	else {//碰到其他不能走的符號就結束
		return maze;
	}
} // Down

vector<vector<char> > maze::Left( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	if ( xaxis < 0 ) { //當走到邊界就停止前進 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'G') { //找到G 
		if ( goalnum >= 0 ) { //當目前找到的G的數量不超過需要的數量就把G的位置存起來  
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // if
		maze[yaxis][xaxis] = 'D'; //將過的G更改為D避免重複計算 
		goalnum = goalnum - 1; //找到就將目標數減一 
		if ( goalnum == 0 ){ // 如果找齊數量就輸出走過的路 
			Draw( maze);
			final = maze;
		}
		maze = Left( maze, width, high, xaxis-1, yaxis); //繼續前進 
		maze = Up( maze, width, high, xaxis, yaxis-1); //轉彎  
		maze = Right( maze, width, high, xaxis+1, yaxis); //轉彎  
		maze = Down( maze, width, high, xaxis, yaxis+1); //轉彎  
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E') { //碰到E就繼續走 
		maze[yaxis][xaxis] = 'V'; //把走過的路更改為V 
		maze = Left( maze, width, high, xaxis-1, yaxis); //繼續前進 
		maze = Up( maze, width, high, xaxis, yaxis-1); //轉彎  
		maze = Right( maze, width, high, xaxis+1, yaxis); //轉彎  
		maze = Down( maze, width, high, xaxis, yaxis+1); //轉彎  
		return maze;
	}
	else {//碰到其他不能走的符號就結束
		return maze;
	}
}// Left

vector<vector<char> > maze::Up( vector<vector<char> > maze, int width, int high, int xaxis, int yaxis) {
	if ( yaxis < 0 ) { //當走到邊界就停止前進 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'G') { //找到G 
		if ( goalnum >= 0 ) { //當目前找到的G的數量不超過需要的數量就把G的位置存起來  
			goalx.push_back(xaxis); 
			goaly.push_back(yaxis); 
		} // if
		maze[yaxis][xaxis] = 'D'; //將過的G更改為D避免重複計算 
		goalnum = goalnum - 1; //找到就將目標數減一 
		if ( goalnum == 0 ){ // 如果找齊數量就輸出走過的路 
			Draw( maze );
			final = maze;
		}
		else{
			maze = Up( maze, width, high, xaxis, yaxis-1 ); //繼續前進 
			maze = Right( maze, width, high, xaxis+1, yaxis); //轉彎  
			maze = Down( maze, width, high, xaxis, yaxis+1); //轉彎  
			maze = Left( maze, width, high, xaxis-1, yaxis); //轉彎  
		}//else
		 
		return maze;
	}
	
	if ( maze[yaxis][xaxis] == 'E' ) { //碰到E就繼續走 
		maze[yaxis][xaxis] = 'V'; //把走過的路更改為V 
		maze = Up( maze, width, high, xaxis, yaxis-1 ); //繼續前進 
		maze = Right( maze, width, high, xaxis+1, yaxis); //轉彎  
		maze = Down( maze, width, high, xaxis, yaxis+1); //轉彎  
		maze = Left( maze, width, high, xaxis-1, yaxis); //轉彎  
		return maze;
	}
	else { //碰到其他不能走的符號就結束 
		return maze;
	}
} // Up

void maze::Draw( vector<vector<char> > maze) {
	for(int i=0;i<maze.size();i++) {         
        for(int j=0;j<maze[i].size();j++) {  
            if( maze[i][j] == 'D') //因為D原本是G所以將其輸出成G 
            	cout<<'G';
			else
          	  cout<<maze[i][j]; 
        } // for
		                                                 
        cout << endl;                                                            
    }  // for
    		
    cout << endl; 
} // Draw

vector<vector<char> > maze::Pathright( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {
	if ( xaxis == width ) { //當走到邊界就停止前進 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //走回原點或是走到其他G的最終路線 
		if ( ( yaxis == 0 && xaxis == 0))  //走回原點將其標記成A 
			maze3[yaxis][xaxis] = 'A';
		findstart = findstart + 1; //回原點或是其他G的最終路線的次數 
		if ( findstart == 1 ) //第一次回原點或是其他G的最終路線就更新finalpath 
			finalpath = maze3;
		return maze3;
	}

	if ( maze3[yaxis][xaxis] == 'V' || maze3[yaxis][xaxis] == 'D') { //只有V可以走,D就是原本的G 
		if ( maze3[yaxis][xaxis] == 'V') //將走過的V標記成A,D標記成C 
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //繼續前進
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1); //轉彎  
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //轉彎  
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //轉彎  
		if(maze3[yaxis][xaxis] == 'C') //重新走回來就將其修改回去 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A') 
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //碰到其他不能走的符號就結束  
		return maze3;
	}
}

vector<vector<char> > maze::Pathdown( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {

	if ( yaxis == high ) { //當走到邊界就停止前進 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //走回原點或是走到其他G的最終路線 
		if ( ( yaxis == 0 && xaxis == 0))
			maze3[yaxis][xaxis] = 'A'; //走回原點將其標記成A 
		findstart = findstart + 1; //回原點或是其他G的最終路線的次數 
		if ( findstart == 1 ) //第一次回原點或是其他G的最終路線就更新finalpath 
			finalpath = maze3;
		return maze3;
	}
	
	if ( maze3[yaxis][xaxis] == 'V'|| maze3[yaxis][xaxis] == 'D') { //只有V可以走,D就是原本的G  
		if ( maze3[yaxis][xaxis] == 'V')
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1);  //繼續前進 
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //轉彎  
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //轉彎  
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //轉彎  
		if(maze3[yaxis][xaxis] == 'C') //重新走回來就將其修改回去 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A')
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //碰到其他不能走的符號就結束  
		return maze3;
	}
}

vector<vector<char> > maze::Pathleft( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {

	if ( xaxis < 0 ) { //當走到邊界就停止前進 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //走回原點或是走到其他G的最終路線 
		if ( ( yaxis == 0 && xaxis == 0))
			maze3[yaxis][xaxis] = 'A'; //走回原點將其標記成A 
		findstart = findstart + 1; //回原點或是其他G的最終路線的次數 
		if ( findstart == 1 ) //第一次回原點或是其他G的最終路線就更新finalpath 
			finalpath = maze3;
		return maze3;
	}

	
	if ( maze3[yaxis][xaxis] == 'V'|| maze3[yaxis][xaxis] == 'D') { //只有V可以走,D就是原本的G  
		if ( maze3[yaxis][xaxis] == 'V')
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //繼續前進 
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //轉彎  
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //轉彎  
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1); //轉彎  
		if(maze3[yaxis][xaxis] == 'C') //重新走回來就將其修改回去 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A')
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //碰到其他不能走的符號就結束  
		return maze3;
	}
}

vector<vector<char> > maze::Pathup( vector<vector<char> > maze3, int width, int high, int xaxis, int yaxis) {

	if ( yaxis < 0 ) { //當走到邊界就停止前進 
		return maze3;
	}
	
	if (( yaxis == 0 && xaxis == 0)  ||maze3[yaxis][xaxis] == 'R'||maze3[yaxis][xaxis] == 'G') { //走回原點或是走到其他G的最終路線 
		if ( ( yaxis == 0 && xaxis == 0)) //走回原點將其標記成A 
			maze3[yaxis][xaxis] = 'A';
		findstart = findstart + 1; //回原點或是其他G的最終路線的次數 
		if ( findstart == 1 ) //第一次回原點或是其他G的最終路線就更新finalpath 
			finalpath = maze3;
		return maze3;
	}
	
	if ( maze3[yaxis][xaxis] == 'V'|| maze3[yaxis][xaxis] == 'D') { //只有V可以走,D就是原本的G  
		if ( maze3[yaxis][xaxis] == 'V')
			maze3[yaxis][xaxis] = 'A';
		if(maze3[yaxis][xaxis] == 'D')
			maze3[yaxis][xaxis] = 'C';
		maze3 = Pathup( maze3, width, high, xaxis, yaxis-1); //繼續前進 
		maze3 = Pathright( maze3, width, high, xaxis+1, yaxis); //轉彎 
		maze3 = Pathdown( maze3, width, high, xaxis, yaxis+1); //轉彎  
		maze3 = Pathleft( maze3, width, high, xaxis-1, yaxis); //轉彎  
		if(maze3[yaxis][xaxis] == 'C') //重新走回來就將其修改回去 
			maze3[yaxis][xaxis] = 'D';
		if(maze3[yaxis][xaxis] == 'A') 
			maze3[yaxis][xaxis] = 'V';
		return maze3;
	}
	else { //碰到其他不能走的符號就結束  
		return maze3;
	}
}

void maze::Change( vector<vector<char> > maze, int q) {
	for(int i=0;i<maze.size();i++) {         
        for(int j=0;j<maze[i].size();j++) {  
            if( maze[i][j] == 'A') { //A表示最終的路線,將其改成R 
            	maze[i][j] = 'R';
			}// if
			if( maze[i][j] == 'C') { //C表示目標,將其改成G
            	maze[i][j] = 'G';
			}// if
			if( q == -1){ // 判斷目標是否全部找完, 全找完就可以將其他的V改回E 
				if( maze[i][j] == 'V') 
            		maze[i][j] = 'E';
			}
				
        } // for                                                            
    }  // for
    finalpath = maze; //將修改後的迷宮傳到finalpath 
} // Draw


