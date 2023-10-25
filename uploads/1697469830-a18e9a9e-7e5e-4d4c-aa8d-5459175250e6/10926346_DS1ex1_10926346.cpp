//10926346 �B���f
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
        int goalstimes=0; //�w��goals�ƶq(0�}�l���J�Ȥ�1)
        int direction=0; //���ʤ�V

    public:
        vector<int> where; //��쪺goals��m
        vector <int> datasize;//x,y��V
        vector <vector <string>> data;//Ū�J���
        vector <vector <string>> visited;
        vector <vector <string>> route;//���|
        vector <vector <string>> route1;//���ȤG�s�����|��

        void del();//�M��
        void Read_Openfile();//Ū�}��
        bool first_mission( int x_now, int y_now );
        int is_posInt( string x );//�O�_�������
        bool second_mission( int x_now, int y_now, int goals );
};

ifstream file ;

int main(){
    labyrinth lab;
    do{
        cout<< "*** Path Finding ***"<< endl;
        cout<< "* 0. Quit          *"<< endl;
        cout<< "* 1. One goal      *"<< endl;
        cout<< "* 2. More goals    *"<< endl;
        cout<< "********************"<< endl;
        cout<< "Input a command(0, 1, 2): ";

        string cmd;
        cin >> cmd;

        if( cmd=="1" ){//����1
            lab.del();
            lab.Read_Openfile();

            cout<< endl;
            if( lab.first_mission( 0, 0 )==true ){//�����goals
                lab.visited[lab.where[1]][lab.where[0]]="G";//�N��ﱼ��G��^��
                //��ܸ��
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
            else{//�����
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
            }
            cout<<endl;
        }
        else if( cmd=="2" ){//���ȤG

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

            if( lab.second_mission( 0, 0, goals )==true ){//�����n�D�ƶqgoals
                for( int i=0; i<lab.where.size(); i++ ){//�N��ﱼ��G��^��
                    lab.visited[lab.where[i+1]][lab.where[i]]="G";
                    lab.route[lab.where[i+1]][lab.where[i]]="G";
                    lab.route1[lab.where[i+1]][lab.where[i]]="G";
                    i++;
                }
                //��ܸ��
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        cout<<lab.visited[i][j];
                    }
                    cout<<endl;
                 }
                cout<<endl;
                for(int i=0;i<lab.datasize[1];i++){
                    for( int j=0; j<lab.datasize[0]; j++ ){
                        if( lab.route1[i][j]=="R" || lab.route[i][j]=="R" ){//�̫�@������S�X�֡A�ҥH��ܮɭn��
                            cout<<"R";
                        }
                        else{
                           cout<<lab.route[i][j];
                        }
                    }
                    cout<<endl;
                }
            }
            else{//�����n�D�ƶqgoals
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
        else if( cmd=="0" ){
            break;
        }
        else{
            cout<< "\nCommand does not exist!\n"<< endl;
        }
    }while( true );
}

void labyrinth::del(){
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
    //�}�ɮ�
    file.open( "input"+name+".txt",ios_base::in );
    while( file.is_open()==false ){
        cout<< "\ninput"<< name<< ".txt does not exist!\nPlease input a file number again. ";
        cin>> name;
        file.open( "input"+name+".txt",ios_base::in );
    }
    //Ū�����
    string s;
    getline(file, s);
    //�����r��y
    int col_row;
    istringstream sizestream(s);
    while( sizestream>>col_row ){//�e��Ӭ���C��
        datasize.push_back(col_row);
    }

    while ( getline(file, s) ) {

        for( int i=0; i<s.length(); i++ ){//�̦r���s�Jtmp
            string accessuse;
            stringstream ss;
            ss << s[i];
            ss >> accessuse;
            tmp.push_back(accessuse);
        }
        data.push_back(tmp);
        visited.push_back(tmp);
        route.push_back(tmp);
        route1.push_back(tmp);
        tmp.clear();

    }

    file.close() ;

}

bool labyrinth::first_mission( int x_now, int y_now ){
    int times=0;
    bool endcontrol=false;//�O�_���
    bool e=true;

    while( e==true ){
        if( times==4 ){//���I4�Ӥ�V�����L�F
            visited[y_now][x_now]="V";//���I�����L
            route[y_now][x_now]="E";//���I�D���|
            if( direction==0 ){//�N�e����諸��V��^�e�@�Ӥ�V
                direction=3;
            }
            else{
                direction--;
            }
            return false;
        }
        else if( direction==0 ){//���k
            if( x_now<datasize[0]-1 && data[y_now][x_now+1]!="O" && visited[y_now][x_now+1]!="V" ){//���b�̥k�B�k�䦳���B�k�䥼���L

                visited[y_now][x_now]="V";//�������I
                route[y_now][x_now]="R";//���I�ȩw�����|

                if( data[y_now][x_now+1]!="G" ){//�U�I�Dgoal
                    endcontrol=first_mission( x_now+1, y_now );

                }
                else{//�U�I��goal
                    visited[y_now][x_now+1]="V";//����Ω�Ngoal�h���H��K�����goal����ӨS�Ψ�����v�T�N�S��^��
                    data[y_now][x_now+1]="E";
                    //������goal��m
                    where.push_back(x_now+1);
                    where.push_back(y_now);
                    return true;
                }
                times=0;//���s���I���L��V
            }
            else{//���I���i���k��
                direction++;//���ܤ�V
            }
        }
        else if( direction==1 ){//�U
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
        else if( direction==2 ){//��
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
        else if( direction==3 ){//�W
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
        times++;//�w���L��V
        if( endcontrol==true ){//�w���goal
            return true;
        }

    }
    return false;

}

int labyrinth::is_posInt( string x ){

    int number;

    istringstream stream(x);//�Nx�����r��y
    if (stream >> number) {//�p�G�}�Y�i�H�ন�Ʀr�h�~��
        if( stream.eof() ){//�קK�u���}�Y�O�Ʀr�����pe.g.:12sdf
            if( number>0 )//�T�{�Ʀr�϶�
                return number;
            else {
                cout<< "�D����ơA�����L�Ŀ�J"<< endl;
                return -1;
            }
        }
        else { //�r��u���}�Y�O�Ʀr
            cout<< "�D����ơA�����L�Ŀ�J"<< endl;
            return -1;
        }
    } else {//�r��}�Y�N���O�Ʀr
        cout<< "�D����ơA�����L�Ŀ�J"<< endl;
        return -1;
    }

    return true;

}

bool labyrinth::second_mission( int x_now, int y_now, int goals ){
    int times=0;
    bool e=true;

    while( e==true ){

        if( goalstimes==goals ){//�w�g����h�������}
            return true;
        }

        if( times==4 ){//���I�|�Ӥ�V�Ҩ��L
            visited[y_now][x_now]="V";//���I�����L
            route[y_now][x_now]="E";//���I�D���|
            if( direction==0 ){
                direction=3;//�N�e����諸��V��^�e�@�Ӥ�V
            }
            else{
                direction--;
            }
            return false;
        }
        else if( direction==0 ){//���k
            times++;//���L��V+1
            if( x_now<datasize[0]-1 && data[y_now][x_now+1]!="O" && visited[y_now][x_now+1]!="V" ){//�k(���b�̥k�B�k�䦳���B�k�䥼���L)
                times=0;
                visited[y_now][x_now]="V";//�������I
                route[y_now][x_now]="R";//���I�ȩw�����|

                if( data[y_now][x_now+1]!="G" ){//�U�I�Dgoal
                    if(second_mission( x_now+1, y_now, goals )){
                        continue;
                    }

                }
                else if( goalstimes+1<goals ){//�U�I��goal�B�|���䧹
                    //����Ω�Ngoal�h���H��K�����goal
                    visited[y_now][x_now+1]="V";
                    data[y_now][x_now+1]="E";
                    //������goal��m
                    where.push_back(x_now+1);
                    where.push_back(y_now);
                    //�N���|�X�֦�route1�P�ɭ��sroute�H�~���goal
                    for(int i=0;i<datasize[1];i++){
                        for( int j=0; j<datasize[0]; j++ ){
                            if( route[i][j]=="R"){
                                route1[i][j]="R";

                            }
                            route[i][j]=data[i][j];
                        }
                    }
                    goalstimes++;//goal���ƶq+1
                    //�~���U��
                    if(second_mission( x_now+1, y_now, goals )){
                        continue;
                    }


                }
                else{//�U�I��goal�B�䧹�n�D�ƶq
                    visited[y_now][x_now+1]="V";
                    data[y_now][x_now+1]="E";
                    where.push_back(x_now+1);
                    where.push_back(y_now);
                    goalstimes=goals;
                    return true;
                }

            }//���I���i���k��
            else{
                direction++;//���ܤ�V
            }
        }
        else if( direction==1 ){//�U
            times++;
            if(  y_now<datasize[1]-1 && data[y_now+1][x_now]!="O" && visited[y_now+1][x_now]!="V" ){//�U

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
        else if( direction==2 ){//��
            times++;
            if( x_now!=0 && data[y_now][x_now-1]!="O" && visited[y_now][x_now-1]!="V" ){//��

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
        else if( direction==3 ){//�W
           times++;
           if(  y_now!=0 && data[y_now-1][x_now]!="O" && visited[y_now-1][x_now]!="V" ){//�W

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
