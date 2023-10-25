// 學號:11127232 姓名:林鈺宸 
 
#include <iostream>
#include <vector>
#include <limits.h>
#include <string>
#include <fstream>

/* 
註解後有括弧(任務三)的程式，
代表這些變數或是function僅會在指令3用到。 
*/

 
using namespace std;

const int direct[4][2] = { { 0 , 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } }; // 分別代表往右、下、左、上行走一步 

struct Coor{ // 用來存座標位置的資料型態 
	
	int x;
	int y;
	
};

class Maze {
	
private:
	
	int check; 				// 檢查是否有找到G(目標) 
	int width; 				// 迷宮長度 
	int height; 			// 迷宮高度 
	int shortpath;			// 最短路徑 
	int limit;				// 遞迴次數(任務三) 
	int run_times;			// 目前走的步數(任務三) 
	vector<string> data;	// 迷宮的資料  
	vector<string> backup;	// 迷宮資料的備份( 用於儲存找到G(目標)的路徑R ) 
	vector<string> mapV;	// 儲存路徑V(任務三) 
	vector<string> mapR;	// 儲存路徑R(任務三) 
	vector<Coor> target;	// 用來儲存G(目標)的位置 
	int g_num;				// 表示總共要尋找幾個G(目標) 
	bool success;			// 表示是否有成功在迷宮中找到相對應數量的目標 
	
	ifstream file;			// 創造一個可用來讀取檔案的物件 

	
public:
	
	bool load() {							// 讀入資料 
		
        string name = "";					
        
        cin >> name;						// 輸入文件名稱 
        name = "input" + name + ".txt";
		 
		file.open(name.c_str());			// 打開對應文件的檔案 
		
	    if (!file.is_open()) {				// 確認檔案是否有被打開 
	    	
	        cout << "\n" << name << " does not exist!" << endl;	
	    	return false;					// 代表輸入錯誤的檔名 
	        
	    }
	    
	    check = 0;							// 初始化check( 0為尚未找到目標 ) 
	    g_num = 1;							// 初始化目標的個數( 預設1個 ) 
	    success = false;					// 初始化success( 判斷是否有成功找到g_num個目標 ) 
	    Setdata();							// 輸入迷宮資料 
	    mapV = data;						// 儲存迷宮資料(任務三) 
	    mapR = data;						// 儲存迷宮資料(任務三) 
	    file.close();						// 關閉文件檔 
	    
	    return true;						// 成功輸入正確檔名 
    }
	
	void Setdata() {						
		
		string input = "";
		
		file >> width;
		file >> height;
		
		for ( int i = 0; i < height; i++ ) {
			
			file >> input;
			data.push_back( input );
			
		}
		
	}
	
	void Setgoal() {
		
		cin >> g_num;
		
	}
	
	void Revise( int x, int y, char ch ) {		// 更改迷宮資訊 
		data[x][y] = ch;				
	}
	
	void Delete_V() {							// 將迷宮中所有的V改成E( 將已行走的路徑還原 ) 
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( data[x][y] == 'V' )
		    		Revise( x, y, 'E' );
			}
		}
		
	}
	
	void VtoR() {								// 將路徑V改成R(任務三) 
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( data[x][y] == 'V' )
		    		mapR[x][y] = 'R';
			}
		}
		
	}
	
	void RtoE() {								// 將路徑R改成E(任務三) 			
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( mapR[x][y] == 'R' )
		    		mapR[x][y] = 'E';
			}
		}
		
	}
	
	void Copy_V( int x, int y ) {				// 將mapV中對應座標改成V(任務三) 
		
		mapV[x][y] = 'V';
		
	}
	
	void Restore_G() {							// 將迷宮中所有的G還原
		
		for( int i = 0; i < target.size(); i++ ) 
			data[target[i].x][target[i].y] = 'G';
		
	}
	
	void Copy_R() {								// 儲存路徑R的位置到另一張備份地圖上 
		
		for( int x = 0; x < height; x++ ) {
			for( int y = 0; y < width; y++ ){
		    	if ( data[x][y] == 'R' && backup[x][y] != 'G' )
		    		backup[x][y] = 'R';
			}
		}
		
	}
	
	bool IsValid( int x, int y ) {				// 判斷老鼠是否移動到超出邊界或是撞牆
	
		if ( x >= 0 && y >= 0 && x < height && y < width &&
		     data[x][y] != 'O' && data[x][y] != 'V' )
			return true;
			
		return false;
	
	}
	
	void Print_V() {							// 印出完整迷宮的V路徑資訊 (任務三)
		
		for( int i = 0; i < height; i++ )
			cout << mapV[i] << endl;
		  
	}
	
	void Print_R() {							// 印出完整迷宮的R路徑資訊 (任務三)
		
		cout << endl;
		for( int i = 0; i < height; i++ )
			cout << mapR[i] << endl;
		  
	}
	
	void Print() {								// 印出完整迷宮資訊 
		
		for( int i = 0; i < height; i++ )
			cout << data[i] << endl;
		  
	}
	
	void Move_V( int x, int y, int last ) {		// 老鼠移動 ( 用來記錄路徑V ) 
	
		for ( int i = last; i < last + 4 && check == 0 ; i++ ) {	// 四個方向 
			
			int path = i % 4;	
			x = x + direct[path][0];			// 往特定方向移動一格 
			y = y + direct[path][1];
	
			if ( IsValid( x, y ) ) {			// 確認無撞牆及超出邊界				
				
				
				if ( data[x][y] == 'G' ) {		// 找到目標的話 
					Coor g_xy = { x, y };		// 儲存目標位置 
					target.push_back( g_xy );	// 記錄找到的目標位置 
				}
													
				Revise( x, y, 'V' );			// 將此座標修改為V( 走過的路 ) 
				 
				if ( target.size() == g_num ) {	// 如果所有目標都被找到的話  
					success = true;				// 代表搜尋成功
					
					check = 1;
					break;
					
				}
				
				Move_V( x, y, path );
			}
			
			x = x - direct[path][0];
			y = y - direct[path][1];
	
			
		}
		
	}
	
	void Move_R( int x, int y, int last ) {		// 老鼠移動 ( 用來記錄路徑R ) 
	
		for ( int i = last; i < last + 4 && check == 0 ; i++ ) { 
			
			int path = i % 4;
			x = x + direct[path][0];
			y = y + direct[path][1];
			
			if ( IsValid( x, y ) ) {
				
				if ( data[x][y] == 'G' ) {
				 	
					Revise( x, y, 'E' );		// 尋找到G的話就把他修改成E 
					check = 1;					// 結束遞迴 
					break;
					
				}
				
				Revise( x, y, 'V' );	
				Move_R( x, y, path );
				
				if ( check == 1 ) {				// 往回新增路徑R
					Revise( x, y, 'R' );	
				}
				
			}
			
			x = x - direct[path][0];
			y = y - direct[path][1];
	
			
		}
		
	}
	
	void Move_V2( int x, int y, int last, int road ) {	// 老鼠移動 (任務三) 
	
		if ( run_times > limit )				// 超過地圖步數結束遞迴 
			return;
	
		for ( int i = last; i < last + 4 && shortpath > road + 1 ; i++ ) {	// 四個方向 
			
			int path = i % 4;	
			x = x + direct[path][0];			// 往特定方向移動一格 
			y = y + direct[path][1];
	
			if ( IsValid( x, y ) ) {			// 確認無撞牆及超出邊界	
				
				road++;
				run_times++;
				
				if ( data[x][y] == 'G' ) {		// 找到目標的話 
				
					shortpath = road; 
					check = 1;
					
					RtoE();						// 將路徑R改成E
					VtoR();						// 將路徑V改成R
	
				}
				
				else {

					Revise( x, y, 'V' );		// 將此座標修改為V( 走過的路 ) 
					Copy_V( x, y );				// 將路徑V複製到mapV中 
					
				}	
				 
				Move_V2( x, y, path, road );	// 繼續走 
				
				road--;							// 路徑長減一( 往回走 ) 
			}
					
			x = x - direct[path][0];
			y = y - direct[path][1];
	
			
		}
		
	    if (  data[x][y] != 'G' ) {			// 將返回的路改成E 
				
			Revise( x, y, 'E' );
			
		}
		
	}
	
	void Clean() {								// 清除資料 
		
		data.clear();
		backup.clear();
		target.clear();
		
	}
	
	void Findgoals() {
		
		Revise( 0, 0, 'V');						//  將開頭設為已走過的路徑( 開頭必為E )  
		Move_V( 0, 0, 0 ); 						//  從頭開始往右移動 
				
		Restore_G();							//  將被改成V的目標還原成G 
		Print(); 								//  印出走過路徑V的地圖 
		Delete_V();								//  將走過的路徑V刪除並替換成E( 還原地圖 ) 
		backup = data;							//  設置備用地圖 
		
		if ( success ) {						//  如果有成功找到指定數量的目標的話  
			
			for ( int i = 0; i < g_num; i++ ) {	//  搜尋g_num次迷宮 
			
				check = 0;
				Move_R( 0, 0, 0 );			
				Delete_V();			 
				Copy_R();						//  將找到的路徑R依序複製到備份迷宮中 
			}

			data = backup;						//  找完後使得data等於備份迷宮的地圖 
			Revise( 0, 0, 'R' );				//  將開頭改為路徑R( 開頭必為R )
				
			cout << endl;
			Print(); 							//  印出data中的資料 
			
		}
		
		cout << endl;
 
	}
	
	void Test3() {
		
		shortpath = INT_MAX;			// 假設步數為最大 
		limit = width * height * 4;		// 極限步數 
		run_times = 0;
		data[0][0] = 'V';				// 開頭必為E 
		mapV[0][0] = 'V';				// 開頭必為E  
		
		Move_V2( 0, 0, 0, 1 );			// 從原點開始往右，一開始路徑長為1 
		
		
		Print_V();						// 印出走過的路徑 
		
		if ( check == 1 ) {				// 如果有找到G 
			
			Print_R();
			cout << endl << endl << "Shortest path length = " << shortpath << endl;
		}
		
		else {							// 如果沒找到G 
			cout << endl << endl << "### There is no path to find a goal! ###" << endl;
		}
		
		system("pause");
			
	}
	
};

int main() {
	
	do {
		
		cout << "*** Path Finding ***\n";
	    cout << "* 0. Quit          *\n";
	    cout << "* 1. One goal      *\n";
	    cout << "* 2. More goals    *\n";
	    cout << "* 3. Shortest path *\n";
	    cout << "********************\n";
	    cout << "Input a command(0, 1, 2, 3): ";
	    
	    Maze map;
	    string command;
	    
		cin >> command;												// 輸入指令 
		
		if ( command.compare( "1" ) == 0 || command.compare( "2" ) == 0 || command.compare( "3" ) == 0 ) {	// 1是找一個目標,2是找多個目標 
		
			cout << "\nInput a file number: ";	 
			
			if ( map.load() ) {										// 讀入資料 
				
		    	if ( command.compare( "2" ) == 0 ) {
		    		
		    		cout << "\nNumber of G (goals): ";
					map.Setgoal();									// 設定要找多少目標 
		    		
				}
				
		    	if ( command.compare( "3" ) == 0 ) {
		    		
					map.Test3();							
		    		
				}
				
				else if ( command.compare( "3" ) != 0 ) {
				
					map.Findgoals();   								// 尋找並印出答案 
					
				}
				
			}
			
		}
		
		else if ( command.compare( "0" ) == 0 )						// 輸入指令0則結束 
			break;
			
		else														// 輸入未知指令( 不是0、1、2、3 ) 
			cout << "\nCommand does not exist!" << endl;
	
		cout << endl;
		
		map.Clean();												// 清除資料 
		
	} while ( true );
	
} 
