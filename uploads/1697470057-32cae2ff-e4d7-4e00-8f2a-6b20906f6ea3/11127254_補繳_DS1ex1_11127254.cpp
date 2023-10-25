// 11127254 陳岳崇

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <vector>



using namespace std;
enum Modes{
	oneG, 
	moreG,
	shortestG
};
enum Face{
	Right ,
	Down ,
	Left ,
	Up 
};
struct Goal{ // 紀錄終點(G) x,y 的位置  
	int x; 
	int y;
};

class Maze{
	char trash; // 吃空白 
	int x ,y ;
	int col ;  
	int row ;
	vector<vector<char> > matrix; // matrix 二維動態陣列 用來存迷宮 
    
	public :
		int shortest;
		
		bool load(string fileName){
			shortest = 9999999;
			string fileN = "input" + fileName + ".txt";
			ifstream inF( fileN.c_str() ); // inF是一個 以輸入來開啟檔案 
										   // 將fileN 轉換為C的字符串(以null結尾) 
			
			if(inF.is_open()){ // 檔案被開啟 
				
				inF >> x >> y ;  
				inF.get(trash); // 吃空格 
				while( trash != '\n'){ // 直到吃到換行 
					inF.get(trash);
				}
				
				col = x ; // 行 設定為 x 
				row = y ; // 列 設定為 y 
				
				
				vector<char> tempRow; // 用來儲存每一橫列的字元vector 
				string line;
    			while (getline(inF, line)) { 
    				for( int j = 0 ; j < col ; j++ ){
						tempRow.push_back(line[j]); // 每一列的字元 存在tempRow 後面	
					} // for 
					matrix.push_back(tempRow); //  將每一橫列存入matrix中 
					tempRow.clear(); // 釋放 
   			 	   
    			} // while (getline(inF, line))
    			
    			inF.close(); // 關閉檔案 
    			
    			return true;
			} // if 成功開啟 
			
			// 未被成功開啟
			cout << endl << fileN << " does not exist!" << endl;  
			return false ;
		
		
		} // bool load(string fileName)
		
		bool visit(Modes mode, Maze &aMaze) { // 拜訪目標終點 
			int number ; // 用來儲存拜訪目標個數 
			if ( mode == oneG ) number = 1;  
			else if ( mode == moreG ) { 
				cout << endl << "Number of G (goals):";
				cin >> number; // 輸入目標個數 
				while( number < 1 || number > 100 ){ // 若超出目標 
					cout << endl << "### The number must be in [1, 100] ###" << endl;
					cout << endl << "Number of G (goals):";
					cin >> number; // 輸入目標個數
				} // while 
				
			} // else if
			else if ( mode == shortestG ) number = 0;
			
			int count = 0; // 儲存找到終點個數 
			// 檢測起點 
			if (matrix[0][0]  == 'E' ) matrix[0][0] = 'V';  
			else if(matrix[0][0]  == 'G') count++;
			else return false;
			
			
			
			Face face = Right; // 面向方向 初始值為Right 
			int xr = 0, yr = 0; // 起點位置 (xr, yr) (0, 0)  
		 	Maze cMaze(aMaze); // 將 aMaze 拷貝
		 	
			if ( number >= 1 ){
		 		
			 	Goal G; // 紀錄終點(G) x,y 的位置  
				bool founded = false; // 是否找到終點
				 
				 
				walk( face, xr, yr, founded, aMaze, cMaze, count, G);
				
				if(founded) cMaze.matrix[G.y][G.x] = 'A'; // 若找到G 則將'G' 改成'A'
				
				while (count < number && founded ) { // 如果還未達所需目標個數 && 有找到新的目標 
					walk( face, xr, yr, founded, aMaze, cMaze, count, G);
					
					if(founded) cMaze.matrix[G.y][G.x] = 'A'; // 若找到G 則將'G' 改成'A'
	
				} // while
				
				if (count == number) { // 若達成目標個數 
					aMaze.matrix[0][0] = 'R'; // 將aMaze 的起點改成'R' 
					cMaze.clr(); // 釋放
					return true;	
				} // if
				cMaze.clr(); // 釋放 
				return false;
			} // if ( number >= 1 ) mode = oneG or moreG
			
			else if ( number == 0 ){ // mode = shortestG
				int node = 2; // 起點一步 + 走到G一步 = 至少2步  
				shortWalk( face, xr, yr, aMaze, cMaze, node); 
				cMaze.clr(); // 釋放 
				return false;
			} // else if ( number == 0 ) mode = shortestG
		 	
			
		} // bool visit(Modes mode, Maze &aMaze)
		
		// 走過的路徑 
		void walk( Face face, int x, int y, bool& founded, Maze &aMaze, Maze cMaze, int &count, Goal &G ){
			//cout << x << ", " << y << endl;
			
			for ( int i = 0; i < 4 ;) { // 檢測四個方向 依序 右 下 左 上 
				
				if ( i < 4 && face == Right ){ // 向右  
					if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' ){ // 若未超出邊界 且找到G 
						
						founded = true; // 找到G 
						count = count + 1; // 找到G的個數加一 
						G.x = x+1; // 紀錄G的x座標 
						G.y = y; // 紀錄G的y座標

						return;
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' )
					 
					if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V'){ 
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V) 
						
						if ( cMaze.matrix[y][x+1] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y][x+1] = 'V';
							this -> matrix[y][x+1] = 'V';
						} // if ( cMaze.matrix[y][x+1] == 'E') 
						
						walk( face, x+1, y, founded, aMaze, cMaze, count, G ); // 繼續向右 
						
						if ( founded ) {  
							if (aMaze.matrix[y][x + 1] != 'G') aMaze.matrix[y][x + 1] = 'R'; // 找到G後將aMaze的路徑'R'表示 
							return; 
						} // if ( founded ) 
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V')
					
					face = Down; // 換方向 向下 
					i++; // 方向種類加一 
					
				} // if ( i < 4 && face == Right )
				
				if ( i < 4 && face == Down ){ // 向下 
					if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ){ // 若未超出邊界 且找到G  

						founded = true; // 找到G
						count = count + 1; // 找到G的個數加一 
						G.x = x; // 紀錄G的x座標  
						G.y = y+1; // 紀錄G的y座標 
						return;
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ) 
					
					if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V'){
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V) 
						
						if ( cMaze.matrix[y+1][x] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y+1][x] = 'V';
							this -> matrix[y+1][x] = 'V';
						} // if ( cMaze.matrix[y+1][x] == 'E')
						
						walk( face, x, y+1, founded, aMaze, cMaze, count, G ); // 繼續向下 
						
						if ( founded ) {
							if (aMaze.matrix[y + 1][x] != 'G') aMaze.matrix[y + 1][x] = 'R'; // 找到G後將aMaze的路徑'R'表示 
							return; 
						} // if ( founded )
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V')
	
						face = Left; // 換方向 向左 
						i++; // 方向種類加一  
						
				} // if ( i < 4 && face == Down )
				
				if ( i < 4 && face == Left ){ // 向左 
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' ){ // 若未超出邊界 且找到G  

						founded = true; // 找到G 
						count = count + 1; // 找到G的個數加一 
						G.x = x-1; // 紀錄G的x座標  
						G.y = y; // 紀錄G的y座標 
						return;
						
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' )
					
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V'){
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V)
						 
						if ( cMaze.matrix[y][x-1] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y][x-1] = 'V';
							this -> matrix[y][x-1] = 'V';
						} // if ( cMaze.matrix[y][x-1] == 'E')
						
						walk( face, x-1, y, founded, aMaze, cMaze, count, G ); // 繼續向左 
						
						if ( founded ) {
							
							if (aMaze.matrix[y][x - 1] != 'G') aMaze.matrix[y][x - 1] = 'R'; // 找到G後將aMaze的路徑'R'表示 
							return; 
							
						} // if ( founded ) 
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V')
					
						face = Up; // 換方向 向上 
						i++; // 方向種類加一  
						
				} // if ( i < 4 && face == Left )
				
				if ( i < 4 && face == Up ){ // 向上 
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' ){ // 若未超出邊界 且找到G  
						
						founded = true; // 找到G 
						count = count + 1; // 找到G的個數加一 
						G.x = x; // 紀錄G的x座標  
						G.y = y-1; // 紀錄G的y座標 
						return;
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' )
					
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V'){
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V) 
						
						if ( cMaze.matrix[y-1][x] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y-1][x] = 'V';
							this -> matrix[y-1][x] = 'V';
						} // if ( cMaze.matrix[y-1][x] == 'E')
		
						walk( face, x, y-1, founded, aMaze, cMaze, count, G ); // 繼續向上 
						
						if ( founded ) { // 找到G後將aMaze的路徑'R'表示
							if (aMaze.matrix[y - 1][x] != 'G') aMaze.matrix[y - 1][x] = 'R';  
							return; 	
						} // if ( founded )
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V')
					
						face = Right; // 換方向 向右 
						i++; // 方向種類加一  
						
				} // if ( i < 4 && face == Up )
				
			} // for ( int i = 0; i < 4 ;) 
			
			founded = false;
			return;
			
		} // walk( Face face, int x, int y, bool& founded, Maze &aMaze, Maze cMaze, int &count, Goal &G ) 
		
		void shortWalk( Face face, int x, int y, Maze &aMaze, Maze cMaze, int &node ){
			
			
			for ( int i = 0; i < 4 && node < shortest;) { // 檢測四個方向 依序 右 下 左 上 
														  // 且步數不超過最短路徑步數 
				if ( i < 4 && face == Right && node < shortest ){ // 向右  
					if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' ){ // 若未超出邊界 且找到G 
						
						if ( node < shortest ) { // 找到比目前最短路徑還少 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze的'R'路徑還原 
							aMaze.matrix[0][0] = 'R'; // aMaze起點仍設為'R' 
							shortest = node; // 更新最短路徑步數 
							alter(cMaze, aMaze, 'V', 'R'); // 將cMaze的(最短)路徑'V' 在 aMaze用'R'標示 
						}
						

						return;
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] == 'G' )
					 
					if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V'){ 
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V) 
						
						if ( cMaze.matrix[y][x+1] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y][x+1] = 'V';
							this -> matrix[y][x+1] = 'V';
							node++; // 步數加一 
						} // if ( cMaze.matrix[y][x+1] == 'E') 
						
						shortWalk( face, x+1, y, aMaze, cMaze, node ); // 繼續向右 
				
						node--; // 因遞迴後回前一步 步數減一 
						cMaze.matrix[y][x+1] = 'E'; // 將走過的路還原 為了不影響找最短路徑 
						
						//cout << "*" << count << endl;
						
						
					} // if ( x+1 < col && cMaze.matrix[y][x+1] != 'O' && cMaze.matrix[y][x+1] != 'V')
					
					face = Down; // 換方向 向下 
					i++; // 方向種類加一 
					
				} // if ( i < 4 && face == Right )
				
				if ( i < 4 && face == Down && node < shortest ){ // 向下 
					if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ){ // 若未超出邊界 且找到G  
						
						if ( node < shortest ) { // 找到比目前最短路徑還少 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze的'R'路徑還原 
							aMaze.matrix[0][0] = 'R'; // aMaze起點仍設為'R' 
							shortest = node; // 更新最短路徑步數 
							alter(cMaze, aMaze, 'V', 'R'); // 將cMaze的(最短)路徑'V' 在 aMaze用'R'標示 
						}
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] == 'G' ) 
					
					if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V'){
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V) 
						
						if ( cMaze.matrix[y+1][x] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y+1][x] = 'V';
							this -> matrix[y+1][x] = 'V';
							node++; // 步數加一 
						} // if ( cMaze.matrix[y+1][x] == 'E')
						
						shortWalk( face, x, y+1, aMaze, cMaze, node ); // 繼續向下
						
						node--; // 因遞迴後回前一步 步數減一  
						cMaze.matrix[y+1][x] = 'E'; // 將走過的路還原 為了不影響找最短路徑  
						
						
						
					} // if ( y+1 < row && cMaze.matrix[y+1][x] != 'O' && cMaze.matrix[y+1][x] != 'V')
	
						face = Left; // 換方向 向左 
						i++; // 方向種類加一  
						
				} // if ( i < 4 && face == Down )
				
				if ( i < 4 && face == Left && node < shortest ){ // 向左 
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' ){ // 若未超出邊界 且找到G  
						
						if ( node < shortest ) { // 找到比目前最短路徑還少 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze的'R'路徑還原 
							aMaze.matrix[0][0] = 'R'; // aMaze起點仍設為'R' 
							shortest = node; // 更新最短路徑步數 
							alter(cMaze, aMaze, 'V', 'R'); // 將cMaze的(最短)路徑'V' 在 aMaze用'R'標示 
						}
						
						return;
						
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] == 'G' )
					
					if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V'){
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V)
						 
						if ( cMaze.matrix[y][x-1] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y][x-1] = 'V';
							this -> matrix[y][x-1] = 'V';
							node++; // 步數加一
						} // if ( cMaze.matrix[y][x-1] == 'E')
						
						shortWalk( face, x-1, y, aMaze, cMaze, node ); // 繼續向左 
				
						node--; // 因遞迴後回前一步 步數減一  
						cMaze.matrix[y][x-1] = 'E'; // 將走過的路還原 為了不影響找最短路徑  
					
				
						
					} // if ( x-1 >= 0 && cMaze.matrix[y][x-1] != 'O' && cMaze.matrix[y][x-1] != 'V')
					
						face = Up; // 換方向 向上 
						i++; // 方向種類加一  
						
				} // if ( i < 4 && face == Left )
				
				if ( i < 4 && face == Up && node < shortest ){ // 向上 
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' ){ // 若未超出邊界 且找到G  
						
						if ( node < shortest ) { // 找到比目前最短路徑還少 
							alter(aMaze, aMaze, 'R', 'E'); // aMaze的'R'路徑還原 
							aMaze.matrix[0][0] = 'R'; // aMaze起點仍設為'R' 
							shortest = node; // 更新最短路徑步數 
							alter(cMaze, aMaze, 'V', 'R'); // 將cMaze的(最短)路徑'V' 在 aMaze用'R'標示 
						}
						
						return;
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] == 'G' )
					
					if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V'){
						// 下一步未超出邊界 且 未撞牆(O) && 不能走走過的路(V) 
						
						if ( cMaze.matrix[y-1][x] == 'E') { // 下一步的'E'改成'V' 
							cMaze.matrix[y-1][x] = 'V';
							this -> matrix[y-1][x] = 'V';
							node++; // 步數加一 
						} // if ( cMaze.matrix[y-1][x] == 'E')
		
						shortWalk( face, x, y-1, aMaze, cMaze, node ); // 繼續向上 
				
						node--; // 因遞迴後回前一步 步數減一  
						cMaze.matrix[y-1][x] = 'E'; // 將走過的路還原 為了不影響找最短路徑  
						
						
						
					} // if ( y-1 >= 0 && cMaze.matrix[y-1][x] != 'O' && cMaze.matrix[y-1][x] != 'V')
					
						face = Right; // 換方向 向右 
						i++; // 方向種類加一  
						
				} // if ( i < 4 && face == Up )
				
			} // for ( int i = 0; i < 4 ;) 
		
			return;
			
		} // walk( Face face, int x, int y, Maze &aMaze, Maze cMaze, int &node ) 
		
		// 對應位置轉換字元  
		void alter( Maze cMaze, Maze &aMaze, char ch, char to ) {  
			
			for (int j = 0 ; j < row ; j++){
    			for( int i = 0 ; i < col ; i++ ){
    				if (cMaze.matrix[j][i] == ch) aMaze.matrix[j][i] = to; // cMaze 中所有ch字元 在對應到aMaze 中的位置轉換為to字元  
				}  
			}
			return;
		}
	
		// 釋放記憶體 
		void clr(){
			matrix.clear();
		} // void clr()
		
		
		void show(){ // 印出所有迷宮資料 
			for (int j = 0 ; j < row ; j++){
    			for( int i = 0 ; i < col ; i++ ){
    				cout << matrix[j][i];   
				} 
				cout << endl; 
			}
			cout << endl;  
		} // void show()
	
	
};


int main(){
	
	int command = 0;
	do
	{
		Maze aMaze; 
		string fileName; // fileName 用來存要開啟的文件名稱 
		Modes mode = oneG; // 設定mode 初始值為oneG 
		
		cout<<endl<<"*** Path Finding ***";
		cout<<endl<<"* 0. Quit          *";
		cout<<endl<<"* 1. One goal      *";
		cout<<endl<<"* 2. More goals    *";
		cout<<endl<<"* 3. Shortest path *";
		cout<<endl<<"********************";
		cout<<endl<<"Input a command(0, 1, 2, 3):";
		cin>>command;
		
		if((command == 1) || (command == 2) || (command == 3 )){ 
			if(command == 2) mode = moreG; // 設定mode 為moreG 
			if(command == 3) mode = shortestG; // 設定mode 為shortestG
			cout<<endl<<"Input a file number (e.g., 201, 202, ...): ";
			cin>>fileName; // 輸入文件名稱 
			
			if(aMaze.load(fileName)){ // 載入文件內容 並存入aMaze中 
				Maze vMaze(aMaze); // 複製aMaze 到新創的物件 vMaze中  
				bool success = vMaze.visit(mode, aMaze); // 拜訪(所經過的路徑) 是否最後有找到 要找的所有目標 
	
				mode = oneG; // 設定為初始值 
				vMaze.show(); // 將走過的路徑的matrix 印出來 
				
				if ( (command == 1) || (command == 2 ) ){
					if ( success ) aMaze.show(); // 若達成找到所有目標 將 到目標路徑的matrix 印出來 
				}
				
				if ( command == 3 ){
					if ( vMaze.shortest != 9999999 ) {
						aMaze.show();
						cout << endl << "Shortest path lenth = " << vMaze.shortest << endl;
						
					}
					else cout << "### There is no path to find a goal! ###" << endl;
					system("pause");
				}
				vMaze.clr(); // 釋放 
				aMaze.clr(); // 釋放
			}
			
		}
		else if(command == 0) break; // 離開(跳出迴圈結束) 
		else cout<<endl<<"Command does not exist!"<<endl; // 不存在的指令         
	} while(true);
	system("pause");
	return 0;
}


