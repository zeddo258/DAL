// 11127231 蔡順理 
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <vector>
using namespace std;
vector<int> endx,endy;
int goal = 1;
class Map									// 存入地圖資訊 
{
public:
     int x, y;// x y 為行列數 
     vector<string> map;	
     int Val()
     {
          return ((x + 1) * y);
     }
};

void Pr(vector<string> l, int y) {
	cout<<endl << "***************" << endl;
	for ( int i = 0 ; i < y ; i++ )cout  <<   l[i] << endl;		//顯示 地圖 
}


void Go1(vector<string> &l, int x, int y, int xmax, int ymax, int &D, int & find)  // 一步一步執行 debug   
{
    int t = 0;
    int temp = D;// 紀錄初始方向 
    if ( l[y][x] == 'E')l[y][x] = 'V'; // 紀錄路徑 
    system("pause"); // 程式等待 
    Pr(l,ymax);
    while (find < goal && t <= 4) // 找到的 G個數小於設定的 以及方向轉換不超過四次 
	{ 
        if (D%4 == 0) // 往右 
        {
            if (x+1<xmax&&(l[y][x + 1] == 'E' || xmax&&l[y][x + 1] == 'G')){ //預先判讀下一個 
				if ( l[y][x + 1] == 'G') {	//找到目標 
					int n = 1;
					while ( x+n <xmax && l[y][x+n] == 'G') { // 如果有重複的G就一直判讀到不是G 
						find++;
						n++;
					}
					if ( x+n<xmax && l[y][x+n] == 'E') Go1(l, x + n, y, xmax, ymax, D,find); // 下一個是E就繼續 
					else { // 不是就轉彎 
					D++;
					}
				}
				else Go1(l, x + 1, y, xmax, ymax, D,find); // 下一個為E就繼續遞迴
			}    
            else // 下一個是O就轉彎 
            {
                D ++; // 轉彎 
                t++;
                if ( t >= 4) {
                    D = temp; // 重置方向 
                    return;
				}	
            }
        }
        if (D%4 == 1) // 向下走 
        {
            if (y+1<ymax&&(l[y + 1][x] == 'E' || l[y + 1][x] == 'G')) // Y不超過上限 
            {	
				if ( l[y+ 1][x]  == 'G') {
					int n = 1;
					while ( y+n < ymax && l[y+n][x] == 'G') {
						find++;
						n++;
					}
					if ( y+n < ymax && l[y+n][x] == 'E') Go1(l, x , y+ n, xmax, ymax, D,find);
					else D++;
				}	
				else Go1(l, x, y + 1, xmax, ymax, D,find);
			}      
            else
            {
                D++;
                t++;
                if ( t >= 4) {
                	D = temp;
                    return;
				}
            }
        }
        if (D%4 == 2) // 往左走 
        {
            if (x > 0 && (l[y][x-1] == 'E' || l[y][x - 1] == 'G')){  // X不小於0 
            	if ( l[y][x-1]== 'G') {
					int n = 1;
					while ( x-n >= 0 && l[y][x-n] == 'G') {
						find++;
						n++;
					}
					if ( x-n >= 0 && l[y][x-n] == 'E') Go1(l, x - n, y, xmax, ymax, D,find);
					else D++;
				}
				else Go1(l, x-1, y, xmax, ymax, D,find);
			}      
            else
            {
                D++;
                t++;
                if ( t >= 4) 
				{
                    D = temp;
                    return;
				}
            }
        }
        if (D%4 == 3) // 往上走 
        {
            if (y > 0 && (l[y - 1][x] == 'E' || l[y - 1][x] == 'G')) { // Y不等於0 
					if ( l[y-1][x]  == 'G') {
					int n = 1;
					while ( y-n>=0 && l[y-n][x] == 'G') {
						find++;
						n++;
					}
					if ( y-n >= 0 &&l[y-n][x] == 'E') Go1(l, x + n, y, xmax, ymax, D,find);
					else D++;
				}
				else Go1(l, x, y - 1, xmax, ymax,D, find);
			}       
            else
            {
                D++;
                t++;
                if ( t >= 4) {
                    D = temp;
                   	return;
				}
            }
        }
     	if ( l[y][x] == 'V' ) l[y][x] = 'R';  // 把到達G的路徑用R紀錄 
    }
    return ;
}
void Go2(vector<string> &l, int x, int y, int xmax, int ymax, int&D,int & find) // 直接跑出結果 結構如Go1 
{

    int t = 0;
    int temp = D;
    if ( l[y][x] == 'E')l[y][x] = 'V';
    while (find < goal)
    { 
        if (D%4 == 0)
        {
        	//cout << endl << D;
			//if ( x +1 < xmax)cout <<endl << "next is " << l[y][x+1];
            if (x+1<xmax&&(l[y][x + 1] == 'E' || xmax&&l[y][x + 1] == 'G')){
				if ( l[y][x + 1] == 'G') {
					int n = 1;
					while ( x+n <xmax && l[y][x+n] == 'G') {
						find++;
						n++;
					}
					if ( x+n<xmax && l[y][x+n] == 'E') Go2(l, x + n, y, xmax, ymax, D,find);
					else D++;
				}
				else Go2(l, x + 1, y, xmax, ymax, D,find);
			}    
            else
            {
                D ++;
                t++;
                if ( t >= 4) {
                    D = temp;
                    return;
				}	
            }
        }
        if (D%4 == 1)
        {
          	//cout << endl << D ;
			//if ( y +1 < ymax)cout << endl<< "next is " << l[y+1][x];
            if (y+1<ymax&&(l[y + 1][x] == 'E' || l[y + 1][x] == 'G'))
            {	
				if ( l[y+ 1][x]  == 'G') {
					int n = 1;
					while ( y+n < ymax && l[y+n][x] == 'G') {
						find++;
						n++;
					}
					if ( y+n < ymax && l[y+n][x] == 'E') Go2(l, x , y+ n, xmax, ymax, D,find);
					else D++;
				}
				else Go2(l, x, y + 1, xmax, ymax, D,find);
			}      
            else
            {
                D++;
                t++;
                if ( t >= 4) {
                	D = temp;
                    return;
				}
            }
        }
        if (D%4 == 2)
        {
          	//cout << endl << D;
			//if( x > 0 ) cout<<endl << "next is " << l[y][x-1];
            if (x > 0 && (l[y][x-1] == 'E' || l[y][x - 1] == 'G')){
            	if ( l[y][x-1]== 'G') {
					int n = 1;
					while ( x-n >= 0 && l[y][x-n] == 'G') {
						find++;
						n++;
					}
					if ( x-n >= 0 && l[y][x-n] == 'E') Go2(l, x - n, y, xmax, ymax, D,find);
					else D++;
				}
				else Go2(l, x-1, y, xmax, ymax, D,find);
			}      
            else
            {
                D++;
                t++;
                if ( t >= 4) 
				{
                    D = temp;
                    return;
				}
            }
        }
        if (D%4 == 3)
        {
			//cout << endl << D ;
		  	//if ( y > 0 )cout<< endl << "next is " << l[y-1][x];
            if (y > 0 && (l[y - 1][x] == 'E' || l[y - 1][x] == 'G')) {
					if ( l[y-1][x]  == 'G') {
					int n = 1;
					while ( y-n>=0 && l[y-n][x] == 'G') {
						find++;
						n++;
					}
					if ( y-n >= 0 &&l[y-n][x] == 'E') Go2(l, x + n, y, xmax, ymax, D,find);
					else D++;
				}
				else Go2(l, x, y - 1, xmax, ymax,D, find);
			}       
            else
            {
                D++;
                t++;
                if ( t >= 4) {
                    D = temp;
                   	return;
				}
            }
        }
        // if ( l[y][x] == 'V' ) l[y][x] = 'R';

    }

     return ;
} 

bool Getnext ( vector<string> l, int x, int y ) {
	if ( l[y][x] == 'E') return true;
	else return false;
}
void  SGo(vector<string> &l, int x, int y, int xmax, int ymax, int D,int &find) // 直接跑出結果 結構如Go1 
{
    int t = 0;
    int temp = D;
    if ( l[y][x] == 'E')l[y][x] = 'V';
    while (t < 4)
    { 
        if (D%4 == 0)
        {
            if (x+1<xmax&&(l[y][x + 1] == 'E' || xmax&&l[y][x + 1] == 'G') ){
				if ( l[y][x + 1] == 'G') {
					find++;
					endx.push_back(x);
					endy.push_back(y);
					return;
				}
				else SGo(l, x + 1, y, xmax, ymax, D,find);
			}    
            else
            {
                D ++;
                t++;
                if ( t >= 4) {
                   // D = temp;
                    return;
				}	
            }
        }
        if (D%4 == 1)
        {
            if (y+1<ymax&&(l[y + 1][x] == 'E' || l[y + 1][x] == 'G'))
            {	
				if ( l[y+ 1][x]  == 'G') {
					find++;
					endx.push_back(x);
					endy.push_back(y);
					return;
				}
				else SGo(l, x, y + 1, xmax, ymax, D,find);
			}      
            else
            {
                D++;
                t++;
                if ( t >= 4) {
                	//D = temp;
                    return;
				}
            }
        }
        if (D%4 == 2)
        {
            if (x > 0 && (l[y][x-1] == 'E' || l[y][x - 1] == 'G')){
            	if ( l[y][x-1]== 'G') {
					find++;
					endx.push_back(x);
					endy.push_back(y);
					return;
				}
				else SGo(l, x-1, y, xmax, ymax, D,find);
			}      
            else
            {
                D++;
                t++;
                if ( t >= 4) 
				{
                   // D = temp;
                    return;
				}
            }
        }
        if (D%4 == 3)
        {
            if (y > 0 && (l[y - 1][x] == 'E' || l[y - 1][x] == 'G')) {
				if ( l[y-1][x]  == 'G') {
					find++;
					endx.push_back(x);
					endy.push_back(y);
					return;
				}
				else SGo(l, x, y - 1, xmax, ymax,D, find);
			}       
            else
            {
                D++;
                t++;
                if ( t >= 4) {
                   // D = temp;
                   	return;
				}
            }
        }
        
        // if ( l[y][x] == 'V' ) l[y][x] = 'R';

    }
		//D = temp;
     return ;
} 
void TurnR( vector<string> l , int xmax, int ymax ) {
	for ( int i = 0 ; i < ymax ; i++ ) {
		for ( int j = 0 ; j < xmax ; j++ ) {
			if ( l[i][j] == 'V') l[i][j] = 'R';
		}
	}
	
	Pr( l, ymax);
}
vector<string> Do(Map & m, string filename, int step )
{
     ifstream in;
     filename = "input" + filename + ".txt";
     cout << filename;
     in.open(filename.c_str()); // 打開檔案 
     if (!in.is_open()) // 如果沒打開 
     {
          cout << endl
               << filename << "does not exist!";
     }
     else
     {
          in >> m.x >> m.y;
          string line;// 讀入一橫行 
          for (int i = 0; i < m.y; i++)
          {
               in >> line;
               m.map.push_back(line);// 加入地圖 
          }
          in.close(); // 關閉檔案 
          vector<string> go(m.map);
          Pr(go,m.y);
          return go;
        
     }
}
void Findshort( vector<string> &l, int x, int y, int xmax, int ymax, bool &find, int &t) {
	l[y][x] = 'R';
	t++;
	if ( x+y == 0) find = true;
	while ( !find ) {
			if ( y > 0 && ( l[y-1][x] == 'V' || l[y-1][x] == 'E')) Findshort( l,x,y-1,xmax,ymax,find,t);
			else if ( x > 0 && ( l[y][x-1] == 'V' || l[y][x-1] == 'E')) Findshort( l,x-1,y,xmax,ymax,find,t);
			else if ( y+1 < ymax &&( l[y+1][x] == 'V'||  l[y+1][x] == 'E')) Findshort( l,x,y+1,xmax,ymax,find,t);
			else if ( x+1 < xmax && (l[y][x+1] == 'V'||l[y][x+1] == 'E')) Findshort( l,x+1,y,xmax,ymax,find,t);
			else return ;
		}
	return ;
	} 

void Tr( vector<string> &l, int x,int y){
	for ( int i = 0 ; i < y ; i++ ) {
		for ( int j = 0 ; j < x ; j++ ) {
			if ( l[i][j] == 'V') l[i][j] = 'E';
		}
	}
	
	Pr( l, y);
}
void Shortest( Map &m,string filename, int step) {
	int find = 0,D = 0;
	vector<string> go = Do( m, filename, step);
	//Pr(go,m.y);
    SGo(go, 0, 0, m.x, m.y, D,find);
    Pr(go,m.y);
    if ( find == 0 ) cout << "### There is no path to find a goal!! ###";
    else {
    	//cout << endl << endx.size()<< endl;
    	bool f = false;
   		int t = 999;
   		int t2= 1;
   		int s = 0;
   		for ( int i = 0 ; i < find ; i++ ){
   			t2 = 1;
   			f = false;
   			vector<string> g(go);
   			Findshort( g, endx[i],endy[i],m.x,m.y, f,t2);
   			if ( t2 < t ){
   				t = t2;
   				s = i;
			   }
		   }  
    	//cout << endl << endx << "  ,  " << endy << endl;
    	// if ( f )cout << s << endl;
    	vector<string> g(go);
    	f = false;
    	Findshort( g, endx[s],endy[s],m.x,m.y, f,t2);
    	Tr(g,m.x,m.y);
    	cout << endl << "Shortest path length = " << t<< endl;
	}

}

int main()
{
     int cmd = 0; // 輸入指令 
     int step = 1; // 選擇是否顯示過程 
     do
     {
     	endx.clear();
     	endy.clear();

          string filename; // 檔案編號 
          cout << endl
               << "*** Path Finding ***";
          cout << endl
               << "* 0. Quit          *";
          cout << endl
               << "* 1. One goal      *";
          cout << endl
               << "* 2. More goals    *";
          cout << endl 
		  	   << "* 3. shortest path *";
          cout << endl
               << "*****************";
          cout << endl
               << "Input a command(0,1,2,3):";
          cin >> cmd;
/*  debug用 
          cout << endl
               << "*** Mode chose ***";
          cout << endl
               << "* 0. Quit          *";
          cout << endl
               << "* 1. One step       *";
          cout << endl
               << "* 2. Step by step    *";
          cout << endl
               << "*****************";
          cout << endl
               << "Input a command(0,1,2):";
          cin >> step;
          */ 
          if ((cmd == 1 || cmd == 2)|| cmd == 3)
          { 
          	Map m;
               cout << endl
                    << " Input a file number (e.g., 201, 202, ...):";
               cin >> filename;
			   if (cmd == 2 ) { // 多目標 
			   	cout << endl << "Number of G (goals): ";
			   	cin >> goal;
			   }
			   if ( cmd == 3 ) Shortest ( m, filename,step);
               else {
               	vector<string> go = Do(m,filename,step);
          		int D = 0; // 預設方向為右 
          		int find = 0;
          		if ( step == 2 )	Go1(go, 0, 0, m.x, m.y, D, find);
          		else Go2(go, 0, 0, m.x, m.y, D,find);
				Pr(go,m.y);
        		TurnR( go,m.x,m.y);
			   }
          }
          else if ( cmd == 0) break; // 跳出 
          else {
          	cout << endl << "Command does not exist!"<< endl;
		  }

     } while (true);
}
