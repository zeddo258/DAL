// 11127231 �����z 
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <vector>
using namespace std;
vector<int> endx,endy;
int goal = 1;
class Map									// �s�J�a�ϸ�T 
{
public:
     int x, y;// x y ����C�� 
     vector<string> map;	
     int Val()
     {
          return ((x + 1) * y);
     }
};

void Pr(vector<string> l, int y) {
	cout<<endl << "***************" << endl;
	for ( int i = 0 ; i < y ; i++ )cout  <<   l[i] << endl;		//��� �a�� 
}


void Go1(vector<string> &l, int x, int y, int xmax, int ymax, int &D, int & find)  // �@�B�@�B���� debug   
{
    int t = 0;
    int temp = D;// ������l��V 
    if ( l[y][x] == 'E')l[y][x] = 'V'; // �������| 
    system("pause"); // �{������ 
    Pr(l,ymax);
    while (find < goal && t <= 4) // ��쪺 G�ӼƤp��]�w�� �H�Τ�V�ഫ���W�L�|�� 
	{ 
        if (D%4 == 0) // ���k 
        {
            if (x+1<xmax&&(l[y][x + 1] == 'E' || xmax&&l[y][x + 1] == 'G')){ //�w���PŪ�U�@�� 
				if ( l[y][x + 1] == 'G') {	//���ؼ� 
					int n = 1;
					while ( x+n <xmax && l[y][x+n] == 'G') { // �p�G�����ƪ�G�N�@���PŪ�줣�OG 
						find++;
						n++;
					}
					if ( x+n<xmax && l[y][x+n] == 'E') Go1(l, x + n, y, xmax, ymax, D,find); // �U�@�ӬOE�N�~�� 
					else { // ���O�N���s 
					D++;
					}
				}
				else Go1(l, x + 1, y, xmax, ymax, D,find); // �U�@�Ӭ�E�N�~�򻼰j
			}    
            else // �U�@�ӬOO�N���s 
            {
                D ++; // ���s 
                t++;
                if ( t >= 4) {
                    D = temp; // ���m��V 
                    return;
				}	
            }
        }
        if (D%4 == 1) // �V�U�� 
        {
            if (y+1<ymax&&(l[y + 1][x] == 'E' || l[y + 1][x] == 'G')) // Y���W�L�W�� 
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
        if (D%4 == 2) // ������ 
        {
            if (x > 0 && (l[y][x-1] == 'E' || l[y][x - 1] == 'G')){  // X���p��0 
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
        if (D%4 == 3) // ���W�� 
        {
            if (y > 0 && (l[y - 1][x] == 'E' || l[y - 1][x] == 'G')) { // Y������0 
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
     	if ( l[y][x] == 'V' ) l[y][x] = 'R';  // ���FG�����|��R���� 
    }
    return ;
}
void Go2(vector<string> &l, int x, int y, int xmax, int ymax, int&D,int & find) // �����]�X���G ���c�pGo1 
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
void  SGo(vector<string> &l, int x, int y, int xmax, int ymax, int D,int &find) // �����]�X���G ���c�pGo1 
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
     in.open(filename.c_str()); // ���}�ɮ� 
     if (!in.is_open()) // �p�G�S���} 
     {
          cout << endl
               << filename << "does not exist!";
     }
     else
     {
          in >> m.x >> m.y;
          string line;// Ū�J�@��� 
          for (int i = 0; i < m.y; i++)
          {
               in >> line;
               m.map.push_back(line);// �[�J�a�� 
          }
          in.close(); // �����ɮ� 
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
     int cmd = 0; // ��J���O 
     int step = 1; // ��ܬO�_��ܹL�{ 
     do
     {
     	endx.clear();
     	endy.clear();

          string filename; // �ɮ׽s�� 
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
/*  debug�� 
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
			   if (cmd == 2 ) { // �h�ؼ� 
			   	cout << endl << "Number of G (goals): ";
			   	cin >> goal;
			   }
			   if ( cmd == 3 ) Shortest ( m, filename,step);
               else {
               	vector<string> go = Do(m,filename,step);
          		int D = 0; // �w�]��V���k 
          		int find = 0;
          		if ( step == 2 )	Go1(go, 0, 0, m.x, m.y, D, find);
          		else Go2(go, 0, 0, m.x, m.y, D,find);
				Pr(go,m.y);
        		TurnR( go,m.x,m.y);
			   }
          }
          else if ( cmd == 0) break; // ���X 
          else {
          	cout << endl << "Command does not exist!"<< endl;
		  }

     } while (true);
}
