//10926346 劉炫惠
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>


using namespace std;

class labyrinth{
    private:
        vector <string> tmp;
        vector <int> tmp2;
        int goalstimes=0; //已找goals數量(0開始比輸入值少1)
        int direction=0; //移動方向

    public:
        int path=0;
        int shortpath=99999;
        bool findG=false;
        vector <vector <int>> pathtimes;

        vector <int> where; //找到的goals位置
        vector <int> datasize;//x,y方向
        vector <vector <string>> data;//讀入資料
        vector <vector <string>> visited;
        vector <vector <string>> route;//路徑
        vector <vector <string>> route1;//任務二存取路徑用

        void del();//清空
        void Read_Openfile();//讀開檔
        bool first_mission( int x_now, int y_now );
        int is_posInt( string x );//是否為正整數
        bool second_mission( int x_now, int y_now, int goals );
        void third_mission( int x_now, int y_now );
};

ifstream file ;

int main(){
    labyrinth lab;
    do{
        cout<< "*** Path Finding ***"<< endl;
        cout<< "* 0. Quit          *"<< endl;
        cout<< "* 1. One goal      *"<< endl;
        cout<< "* 2. More goals    *"<< endl;
        cout<< "* 3. Shortest path *"<< endl;
        cout<< "********************"<< endl;
        cout<< "Input a command(0, 1, 2, 3): ";

        string cmd;
        cin >> cmd;

        if( cmd=="1" ){//任務1
            lab.del();
            lab.Read_Openfile();

            cout<< endl;
            if( lab.first_mission( 0, 0 )==true ){//有找到goals
                lab.visited[lab.where[1]][lab.where[0]]="G";//將更改掉的G改回來
                //顯示資料
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
                cout<<endl;
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.route[i][j];
                    }
                    cout<<endl;
                }
            }
            else{//未找到
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
            }
            cout<<endl;
        }
        else if( cmd=="2" ){//任務二

            lab.del();
            lab.Read_Openfile();

            string n;
            cout<< "Number of G (goals): ";
            cin>> n;
            while( lab.is_posInt( n )==-1 ){
                cout<< "Number of G (goals): ";
                cin>> n;
            }

            int goals=stoi(n);
            cout<<endl;

            if( lab.second_mission( 0, 0, goals )==true ){//有找到要求數量goals
                for( int i=0; i<lab.where.size(); i++ ){//將更改掉的G改回來
                    lab.visited[lab.where[i+1]][lab.where[i]]="G";
                    lab.route[lab.where[i+1]][lab.where[i]]="G";
                    lab.route1[lab.where[i+1]][lab.where[i]]="G";
                    i++;
                }
                //顯示資料
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
                cout<<endl;
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        if( lab.route1[i][j]=="R" || lab.route[i][j]=="R" ){//最後一次找到後沒合併，所以顯示時要做
                            cout<<"R";
                        }
                        else{
                           cout<<lab.route[i][j];
                        }
                    }
                    cout<<endl;
                }
            }
            else{//未找到要求數量goals
                for( int i=0; i<lab.where.size(); i++ ){
                    lab.visited[lab.where[i+1]][lab.where[i]]="G";
                    lab.route[lab.where[i+1]][lab.where[i]]="G";
                    lab.route1[lab.where[i+1]][lab.where[i]]="G";
                    i++;
                }
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
            }
            cout<<endl;
        }
        else if( cmd=="3" ){
            lab.del();
            lab.Read_Openfile();

            cout<< endl;
            lab.third_mission( 0, 0 );
            if( lab.findG==true ){
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
                cout<<endl;
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.route1[i][j];
                    }
                    cout<<endl;
                }
                cout<<"\nShortest path length = "<<lab.shortpath+2<<endl<<endl;
            }
            else{
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
                 cout<<"\n### There is no path to find a goal! ###"<<endl<<endl;
            }


        }
        else if( cmd=="0" ){
            break;
        }
        else{
            cout<< "\nCommand does not exist!\n"<< endl;
        }
    }while( true );
}

void labyrinth::del(){
    path=0;
    shortpath=99999;
    findG=false;
    pathtimes.clear();
    tmp2.clear();
    direction=0;
    goalstimes=0;
    where.clear();
    tmp.clear();
    datasize.clear();
    data.clear();
    visited.clear();
    route.clear();
    route1.clear();

}

void labyrinth::Read_Openfile(){
    string name;
    cout<<"Input a file number(e.g., 101, 102): ";
    cin>> name;
    //開檔案
    file.open( "input"+name+".txt",ios_base::in );
    while( file.is_open()==false ){
        cout<< "\ninput"<< name<< ".txt does not exist!\nPlease input a file number again. ";
        cin>> name;
        file.open( "input"+name+".txt",ios_base::in );
    }
    //讀取資料
    string s;
    getline(file, s);
    //打成字串流
    int col_row;
    istringstream sizestream(s);
    while( sizestream>>col_row ){//前兩個為行列值
        datasize.push_back(col_row);
    }

    while ( getline(file, s) ) {

        for( int i=0; i<s.length(); i++ ){//依字元存入tmp
            string accessuse;
            stringstream ss;
            ss << s[i];
            ss >> accessuse;
            tmp.push_back(accessuse);
            tmp2.push_back(99999);
        }
        data.push_back(tmp);
        visited.push_back(tmp);
        route.push_back(tmp);
        route1.push_back(tmp);
        pathtimes.push_back(tmp2);
        tmp.clear();

    }

    file.close() ;

}

bool labyrinth::first_mission( int x_now, int y_now ){
    int times=0;
    bool endcontrol=false;//是否找到
    bool e=true;

    while( e==true ){
        if( times==4 ){//該點4個方向都走過了
            visited[y_now][x_now]="V";//此點有走過
            route[y_now][x_now]="E";//此點非路徑
            if( direction==0 ){//將前面更改的方向改回前一個方向
                direction=3;
            }
            else{
                direction--;
            }
            return false;
        }
        else if( direction==0 ){//往右
            if( x_now<datasize[0]-1 && data[y_now][x_now+1]!="O" && visited[y_now][x_now+1]!="V" ){//不在最右、右邊有路、右邊未走過

                visited[y_now][x_now]="V";//紀錄此點
                route[y_now][x_now]="R";//此點暫定為路徑

                if( data[y_now][x_now+1]!="G" ){//下點非goal
                    endcontrol=first_mission( x_now+1, y_now );

                }
                else{//下點為goal
                    visited[y_now][x_now+1]="V";//原先用於將goal去掉以方便找後續的goal但後來沒用到但不影響就沒改回來
                    data[y_now][x_now+1]="E";
                    //紀錄此goal位置
                    where.push_back(x_now+1);
                    where.push_back(y_now);
                    return true;
                }
                times=0;//重製該點走過方向
            }
            else{//此點不可往右走
                direction++;//改變方向
            }
        }
        else if( direction==1 ){//下
            if(  y_now<datasize[1]-1 && data[y_now+1][x_now]!="O" && visited[y_now+1][x_now]!="V" ){

                visited[y_now][x_now]="V";
                route[y_now][x_now]="R";


                if( data[y_now+1][x_now]!="G" ){
                    endcontrol=first_mission( x_now, y_now+1 );
                    times=0;
                }
                else{
                    visited[y_now+1][x_now]="V";
                    data[y_now+1][x_now]="E";
                    where.push_back(x_now);
                    where.push_back(y_now+1);
                    return true;
                }
            }
            else{
                direction++;
            }
        }
        else if( direction==2 ){//左
            if( x_now!=0 && data[y_now][x_now-1]!="O" && visited[y_now][x_now-1]!="V" ){

                visited[y_now][x_now]="V";
                route[y_now][x_now]="R";

                if( data[y_now][x_now-1]!="G" ){
                    endcontrol=first_mission( x_now-1, y_now );
                    times=0;
                }
                else{
                    visited[y_now][x_now-1]="V";
                    data[y_now][x_now-1]="E";
                    where.push_back(x_now-1);
                    where.push_back(y_now);
                    return true;
                }
            }
            else{
                direction++;
            }
        }
        else if( direction==3 ){//上
           if(  y_now!=0 && data[y_now-1][x_now]!="O" && visited[y_now-1][x_now]!="V" ){

                visited[y_now][x_now]="V";
                route[y_now][x_now]="R";

                if( data[y_now-1][x_now]!="G" ){
                    endcontrol=first_mission( x_now, y_now-1 );
                    times=0;
                }
                else{
                    visited[y_now-1][x_now]="V";
                    data[y_now-1][x_now]="E";
                    where.push_back(x_now);
                    where.push_back(y_now-1);
                    return true;
                }
            }
            else{
                direction=0;
            }
        }
        times++;//已走過方向
        if( endcontrol==true ){//已找到goal
            return true;
        }

    }
    return false;

}

int labyrinth::is_posInt( string x ){

    int number;

    istringstream stream(x);//將x打成字串流
    if (stream >> number) {//如果開頭可以轉成數字則繼續
        if( stream.eof() ){//避免只有開頭是數字之狀況e.g.:12sdf
            if( number>0 && number<=100 )//確認數字區間
                return number;
            else {
                cout<< "輸入範圍為1~100(包含頭尾)"<< endl;
                return -1;
            }
        }
        else { //字串只有開頭是數字
            cout<< "非正整數，此為無效輸入"<< endl;
            return -1;
        }
    } else {//字串開頭就不是數字
        cout<< "非正整數，此為無效輸入"<< endl;
        return -1;
    }

    return true;

}

bool labyrinth::second_mission( int x_now, int y_now, int goals ){
    int times=0;
    bool e=true;

    while( e==true ){

        if( goalstimes==goals ){//已經找齊則直接離開
            return true;
        }

        if( times==4 ){//該點四個方向皆走過
            visited[y_now][x_now]="V";//此點有走過
            route[y_now][x_now]="E";//此點非路徑
            if( direction==0 ){
                direction=3;//將前面更改的方向改回前一個方向
            }
            else{
                direction--;
            }
            return false;
        }
        else if( direction==0 ){//往右
            times++;//走過方向+1
            if( x_now<datasize[0]-1 && data[y_now][x_now+1]!="O" && visited[y_now][x_now+1]!="V" ){//右(不在最右、右邊有路、右邊未走過)
                times=0;
                visited[y_now][x_now]="V";//紀錄此點
                route[y_now][x_now]="R";//此點暫定為路徑

                if( data[y_now][x_now+1]!="G" ){//下點非goal
                    if(second_mission( x_now+1, y_now, goals )){
                        continue;
                    }

                }
                else if( goalstimes+1<goals ){//下點為goal且尚未找完
                    //原先用於將goal去掉以方便找後續的goal
                    visited[y_now][x_now+1]="V";
                    data[y_now][x_now+1]="E";
                    //紀錄此goal位置
                    where.push_back(x_now+1);
                    where.push_back(y_now);
                    //將路徑合併至route1同時重製route以繼續找goal
                    for(int i=0;i<datasize[1];i++){
                        for( int j=0; j<datasize[0]; j++ ){
                            if( route[i][j]=="R"){
                                route1[i][j]="R";

                            }
                            route[i][j]=data[i][j];
                        }
                    }
                    goalstimes++;//goal找到數量+1
                    //繼續找下個
                    if(second_mission( x_now+1, y_now, goals )){
                        continue;
                    }


                }
                else{//下點為goal且找完要求數量
                    visited[y_now][x_now+1]="V";
                    data[y_now][x_now+1]="E";
                    where.push_back(x_now+1);
                    where.push_back(y_now);
                    goalstimes=goals;
                    return true;
                }

            }//此點不可往右走
            else{
                direction++;//改變方向
            }
        }
        else if( direction==1 ){//下
            times++;
            if(  y_now<datasize[1]-1 && data[y_now+1][x_now]!="O" && visited[y_now+1][x_now]!="V" ){//下

                visited[y_now][x_now]="V";
                route[y_now][x_now]="R";


                if( data[y_now+1][x_now]!="G" ){
                   times=0;
                   if(second_mission( x_now, y_now+1, goals )){
                        continue;
                    }
                }
                else if( goalstimes+1<goals ){
                    visited[y_now+1][x_now]="V";
                    data[y_now+1][x_now]="E";
                    where.push_back(x_now);
                    where.push_back(y_now+1);
                    for(int i=0;i<datasize[1];i++){
                        for( int j=0; j<datasize[0]; j++ ){
                            if( route[i][j]=="R"){
                                route1[i][j]="R";

                            }
                            route[i][j]=data[i][j];
                        }
                    }
                    goalstimes++;
                    times=0;
                    if(second_mission( x_now, y_now+1, goals )){
                        continue;
                    }


                }
                else{
                    visited[y_now+1][x_now]="V";
                    data[y_now+1][x_now]="E";
                    where.push_back(x_now);
                    where.push_back(y_now+1);
                    goalstimes=goals;
                    return true;
                }
            }
            else{
                direction++;
            }
        }
        else if( direction==2 ){//左
            times++;
            if( x_now!=0 && data[y_now][x_now-1]!="O" && visited[y_now][x_now-1]!="V" ){//左

                visited[y_now][x_now]="V";
                route[y_now][x_now]="R";

                if( data[y_now][x_now-1]!="G" ){
                    times=0;
                    if(second_mission( x_now-1, y_now, goals )){
                        continue;
                    }

                }
                else if( goalstimes+1<goals ){
                    visited[y_now][x_now-1]="V";
                    data[y_now][x_now-1]="E";
                    where.push_back(x_now-1);
                    where.push_back(y_now);
                    for(int i=0;i<datasize[1];i++){
                        for( int j=0; j<datasize[0]; j++ ){
                            if( route[i][j]=="R"){
                                route1[i][j]="R";

                            }
                            route[i][j]=data[i][j];
                        }
                    }
                    goalstimes++;
                    times=0;
                    if(second_mission( x_now-1, y_now, goals )){
                        continue;
                    }

                }
                else{
                    visited[y_now][x_now-1]="V";
                    data[y_now][x_now-1]="E";
                    where.push_back(x_now-1);
                    where.push_back(y_now);
                    goalstimes=goals;
                    return true;
                }
            }
            else{
                direction++;
            }
        }
        else if( direction==3 ){//上
           times++;
           if(  y_now!=0 && data[y_now-1][x_now]!="O" && visited[y_now-1][x_now]!="V" ){//上

                visited[y_now][x_now]="V";
                route[y_now][x_now]="R";

                if( data[y_now-1][x_now]!="G" ){
                    times=0;
                    if( second_mission( x_now, y_now-1, goals ) ){
                        continue;
                    }

                }
                else if( goalstimes+1<goals ){
                    visited[y_now-1][x_now]="V";
                    data[y_now-1][x_now]="E";
                    where.push_back(x_now);
                    where.push_back(y_now-1);
                    for(int i=0;i<datasize[1];i++){
                        for( int j=0; j<datasize[0]; j++ ){
                            if( route[i][j]=="R"){
                                route1[i][j]="R";

                            }
                            route[i][j]=data[i][j];
                        }
                    }
                    goalstimes++;
                    times=0;
                    if(second_mission( x_now, y_now-1, goals )){
                        continue;
                    }

                }
                else{
                    visited[y_now-1][x_now]="V";
                    data[y_now-1][x_now]="E";
                    where.push_back(x_now);
                    where.push_back(y_now-1);
                    goalstimes=goals;
                    return true;
                }
            }
            else{
                direction=0;
            }
        }

    }

    return false;

}

void labyrinth::third_mission( int x_now, int y_now ){
    int times=0;
    bool e=true;
    if( pathtimes[y_now][x_now]>path ){
        pathtimes[y_now][x_now]=path;
    }
    visited[y_now][x_now]="V";//紀錄此點
    route[y_now][x_now]="R";//此點暫定為路徑

    while( e==true ){
        if( path>=shortpath ){
            route[y_now][x_now]="E";//此點非路徑
            path--;
            break;
        }
        else if( times==4 ){//該點4個方向都走過了
            route[y_now][x_now]="E";//此點非路徑
            path--;
            if( direction==0 ){//將前面更改的方向改回前一個方向
                direction=3;
            }
            else{
                direction--;
            }
            break;
        }
        else if( direction==0 ){//往右
            if( x_now<datasize[0]-1 && data[y_now][x_now+1]!="O" && path<shortpath ){//不在最右、右邊有路、右邊未走過
                if( visited[y_now][x_now+1]!="V" ){
                    if( data[y_now][x_now+1]!="G" ){//下點非goal
                        path++;
                        third_mission( x_now+1, y_now );
                        times=0;//重製該點走過方向
                    }
                    else{//下點為goal
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }
                }
                else if( path+1<pathtimes[y_now][x_now+1] ){
                    if( data[y_now][x_now+1]!="G" ){//下點非goal
                        path++;
                        third_mission( x_now+1, y_now );
                        times=0;//重製該點走過方向
                    }
                    else{//下點為goal
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }

                }
                else{
                    times++;//已走過方向
                    direction++;//改變方向
                }
            }
            else{//此點不可往右走
                times++;//已走過方向
                direction++;//改變方向
            }
        }
        else if( direction==1 ){//下
            if(  y_now<datasize[1]-1 && data[y_now+1][x_now]!="O" && path<shortpath ){
                if( visited[y_now+1][x_now]!="V" ){
                    if( data[y_now+1][x_now]!="G" ){
                        path++;
                        times=0;
                        third_mission( x_now, y_now+1 );

                    }
                    else{
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }
                }
                else if( path+1<pathtimes[y_now+1][x_now] ){
                    if( data[y_now+1][x_now]!="G" ){
                        path++;
                        times=0;
                        third_mission( x_now, y_now+1 );

                    }
                    else{
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }
                }
                else{
                    direction++;
                    times++;//已走過方向
                }
            }
            else{
                direction++;
                times++;//已走過方向
            }
        }
        else if( direction==2 ){//左
            if( x_now!=0 && data[y_now][x_now-1]!="O"  && path<shortpath ){
                if( visited[y_now][x_now-1]!="V" ){
                    if( data[y_now][x_now-1]!="G" ){
                        path++;
                        times=0;
                        third_mission( x_now-1, y_now );
                    }
                    else{
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }
                }
                else if( path+1<pathtimes[y_now][x_now-1] ){
                    if( data[y_now][x_now-1]!="G" ){
                        path++;
                        times=0;
                        third_mission( x_now-1, y_now );
                    }
                    else{
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }
                }
                else{
                    times++;//已走過方向
                    direction++;//改變方向
                }
            }
            else{
                direction++;
                times++;//已走過方向
            }
        }
        else if( direction==3 ){//上
           if(  y_now!=0 && data[y_now-1][x_now]!="O" && path<shortpath ){
                if( visited[y_now-1][x_now]!="V" ){
                    if( data[y_now-1][x_now]!="G" ){
                        path++;
                        third_mission( x_now, y_now-1 );
                        times=0;
                    }
                    else{
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }
                }
                else if( path+1<pathtimes[y_now-1][x_now] ){
                    if( data[y_now-1][x_now]!="G" ){
                        path++;
                        third_mission( x_now, y_now-1 );
                        times=0;
                    }
                    else{
                        if( path<shortpath ){
                            findG=true;
                            shortpath=path;
                            for(int i=0;i<datasize[1];i++){
                                for( int j=0; j<datasize[0]; j++ ){
                                    route1[i][j]=route[i][j];
                                }
                            }
                        }
                        route[y_now][x_now]="E";//此點非路徑
                        path--;
                        break;
                    }
                }
                else{
                    direction=0;
                    times++;//已走過方向
                }

            }
            else{
                direction=0;
                times++;//已走過方向
            }
        }
    }
}
