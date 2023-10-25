#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#define right 0 
#define down 1
#define left 2
#define up 3

using namespace std ;

class Node {
    public :
        int node  ;
        int right_Neighbor, left_Neighbor, up_Neighbor, down_Neighbor ;
        int previousNode[2] ;
        int tempNode ;

    void creatNode( char c ) {
        if ( c == 'E' ) {
            node = 0 ;
        }
        else if ( c == 'O' ) {
            node = 1 ;
        }
        else if ( c == 'G' ) {
            node = 2 ;
        }

        return ;
    }

    Node() {
        right_Neighbor = left_Neighbor = up_Neighbor = down_Neighbor = -1 ;
        previousNode[0] = 0 ;
        previousNode[1] = 0 ; 
    }



};

class Map {
    public:
        vector<string> line_Vector ;
        vector<vector<Node>> map_V;
        int array_column, array_row ;
        int count_goal = 0 ;


    void Create_map( int row, int column ) {
        
        cout << "N = " ;
        cin >> count_goal ;

        for ( int i = 0 ; i < row ; i++ ) {
            vector<Node> node_vector ;
            map_V.push_back(node_vector) ; 
            for ( int n = 0 ; n < column ; n++ ) {
                Node node ;
                map_V[i].push_back(node) ;

                map_V[i][n].creatNode(line_Vector[i][n] ) ;
            }
        }


        
    }

    void SetNeighbor() {
        for ( int i = 0 ; i < array_row ; i++ ) {
            for ( int n = 0 ; n < array_column ; n++ ) {

                if ( i != 0 ) {
                    map_V[i][n].up_Neighbor = map_V[i-1][n].node ;

                }

                if ( n != 0 ) {
                    map_V[i][n].left_Neighbor = map_V[i][n-1].node ;

                }

                if ( i != array_row - 1 ) {
                    map_V[i][n].down_Neighbor = map_V[i+1][n].node ;
                }

                if ( n != array_column - 1 ) {
                    map_V[i][n].right_Neighbor = map_V[i][n+1].node ;
                }                
            }
        }
    }

    Map() {
        string fileName ;
        cout << "Input the file name : " ;
        cin >> fileName ;
        ifstream file( fileName ) ;
        string temp_line ;
        string temp_num_str[2] ;
        char c ;
        int n = 0 ;
        while ( file.get( c ) && c != '\n' ) {     

            if ( c != ' ' ) {
                temp_num_str[n].push_back( c ) ;
            }
            else {
                n++ ;
            }
            
        }

        array_column = stoi(temp_num_str[0]) ;
        array_row = stoi(temp_num_str[1]) ;

        if ( file.is_open() ) {
            while ( getline( file, temp_line ) ) {
                line_Vector.push_back(temp_line) ;
            }

        }
    }

    bool HavePath(int x,int y) {
        if ( x == 0 && y == 0 ) {
            if ( map_V[x+1][y].node == 0 || map_V[x][y+1].node == 0 ||
                 map_V[x+1][y].node == 2 || map_V[x][y+1].node == 2 ) {
                return true ;
            }
        }
        else if ( x == 0 && y == array_column - 1 ) {
            if ( map_V[x+1][y].node == 0 || map_V[x][y-1].node == 0 ||
                 map_V[x+1][y].node == 2|| map_V[x][y-1].node == 2 ) {
                return true ;
            }            
        }
        else if ( x == array_row - 1 && y == array_column - 1 ) {
            if ( map_V[x-1][y].node == 0 || map_V[x][y-1].node == 0 ||
                 map_V[x-1][y].node == 2 || map_V[x][y-1].node == 2 ) {
                return true ;
            }
        }
        else if ( x == array_row - 1 && y == 0 ) {
            if ( map_V[x-1][y].node == 0 || map_V[x][y+1].node == 0 ||
                 map_V[x-1][y].node == 2 || map_V[x][y+1].node == 2 ) {
                return true ;
            }
        }
        else if ( x == 0 ) {
            if ( map_V[x+1][y].node == 0 || map_V[x][y-1].node == 0 || map_V[x][y+1].node == 0 ||
                 map_V[x+1][y].node == 2 || map_V[x][y-1].node == 2 || map_V[x][y+1].node == 2 ) {
                return true ;
            }             
        }
        else if ( y == array_column - 1 ) {
            if ( map_V[x+1][y].node == 0 || map_V[x][y-1].node == 0 || map_V[x-1][y].node == 0 ||
                 map_V[x+1][y].node == 2 || map_V[x][y-1].node == 2 || map_V[x-1][y].node == 2 ) {
                return true ;
            }             
        }
        else if ( y == 0 ) {
            if ( map_V[x-1][y].node == 0 || map_V[x][y+1].node == 0 || map_V[x+1][y].node == 0 ||
                 map_V[x-1][y].node == 2 || map_V[x][y+1].node == 2 || map_V[x+1][y].node == 2 ) {
                return true ;
            }  
        }
        else if ( x == array_row - 1 ) {
            if ( map_V[x-1][y].node == 0 || map_V[x][y-1].node == 0 || map_V[x][y+1].node == 0 ||
                 map_V[x-1][y].node == 2 || map_V[x][y-1].node == 2 || map_V[x][y+1].node == 2 ) {
                return true ;
            }    
        }
        else if (  x != array_row - 1 && y != 0 && x != 0 && y != array_column - 1 ) {
            if ( map_V[x+1][y].node == 0 || map_V[x][y-1].node == 0 || map_V[x][y+1].node == 0 || map_V[x-1][y].node == 0 ||
                 map_V[x+1][y].node == 2 || map_V[x][y-1].node == 2 || map_V[x][y+1].node == 2 || map_V[x-1][y].node == 2 ) {
                return true ;
            }  
        }


        return false ;
    }

    bool HavePath_ForFindPath(int x,int y) {
        if ( x == 0 && y == 0 ) {
            if ( map_V[x+1][y].node == 3 || map_V[x][y+1].node == 3 ||
                 map_V[x+1][y].node == 4 || map_V[x][y+1].node == 4 ) {
                return true ;
            }
        }
        else if ( x == 0 && y == array_column - 1 ) {
            if ( map_V[x+1][y].node == 3 || map_V[x][y-1].node == 3 ||
                 map_V[x+1][y].node == 4 || map_V[x][y-1].node == 4 ) {
                return true ;
            }            
        }
        else if ( x == array_row - 1 && y == array_column - 1 ) {
            if ( map_V[x-1][y].node == 3 || map_V[x][y-1].node == 3 ||
                 map_V[x-1][y].node == 4 || map_V[x][y-1].node == 4 ) {
                return true ;
            }
        }
        else if ( x == array_row - 1 && y == 0 ) {
            if ( map_V[x-1][y].node == 3 || map_V[x][y+1].node == 3 ||
                 map_V[x-1][y].node == 4 || map_V[x][y+1].node == 4 ) {
                return true ;
            }
        }
        else if ( x == 0 ) {
            if ( map_V[x+1][y].node == 3 || map_V[x][y-1].node == 3 || map_V[x][y+1].node == 3 ||
                 map_V[x+1][y].node == 4 || map_V[x][y-1].node == 4 || map_V[x][y+1].node == 4 ) {
                return true ;
            }             
        }
        else if ( y == array_column - 1 ) {
            if ( map_V[x+1][y].node == 3 || map_V[x][y-1].node == 3 || map_V[x-1][y].node == 3 ||
                 map_V[x+1][y].node == 4 || map_V[x][y-1].node == 4 || map_V[x-1][y].node == 4 ) {
                return true ;
            }             
        }
        else if ( y == 0 ) {
            if ( map_V[x-1][y].node == 3 || map_V[x][y+1].node == 3 || map_V[x+1][y].node == 3 ||
                 map_V[x-1][y].node == 4 || map_V[x][y+1].node == 4 || map_V[x+1][y].node == 4 ) {
                return true ;
            }  
        }
        else if ( x == array_row - 1 ) {
            if ( map_V[x-1][y].node == 3 || map_V[x][y-1].node == 3 || map_V[x][y+1].node == 3 ||
                 map_V[x-1][y].node == 4 || map_V[x][y-1].node == 4 || map_V[x][y+1].node == 4 ) {
                return true ;
            }    
        }
        else if (  x != array_row - 1 && y != 0 && x != 0 && y != array_column - 1 ) {
            if ( map_V[x+1][y].node == 3 || map_V[x][y-1].node == 3 || map_V[x][y+1].node == 3 || map_V[x-1][y].node == 3 ||
                 map_V[x+1][y].node == 4 || map_V[x][y-1].node == 4 || map_V[x][y+1].node == 4 || map_V[x-1][y].node == 4 ) {
                return true ;
            }  
        }


        return false ;
    }

    static void PrintPoint( int point ) {
        if ( point == 0 ) {
            cout << "E" ;
        }
        else if ( point == 1 ) {
            cout << "O" ;
        }
        else if ( point == 2 || point == 4 || point == 6 ) {
            cout << "G" ;
        }
        else if ( point == 3 ) {
            cout << "V" ;
        }
        else if ( point == 5 ) {
            cout << "R" ;
        }

        return ;
    }


};



class Rat {
    public :
        int rat_Location[2] = {0,0} ; // rat is at the start point 
        int moving_diration = right ; // 0 = right , 1 = down , 2 = left , 3 = up
        Map rat_map ;
        int goal_found = 0 ;



    bool moving( int row, int column ) {

           


        if ( rat_Location[0] == 0 && rat_Location[1] == 0 ) {
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 3 ;            
        }


        if (  moving_diration == right && ( rat_Location[1] == column - 1 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 1 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 3 ||
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 4 ) ) {
            moving_diration = down ;

        }
        else if ( moving_diration == right && rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 0 ) {
            rat_Location[1]++ ;            
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] - 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 3 ;

        }
        else if ( moving_diration == right && rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 2 ) {
            rat_Location[1]++ ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] - 1 ;     
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;       
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 4 ;               
            goal_found++  ;

        }            


        if (  moving_diration == down && ( rat_Location[0] == row - 1 || 
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 1 || 
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 3 ||
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 4 ) ) {
            moving_diration = left ;

        }
        else if ( moving_diration == down && rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 0 ) {          
            rat_Location[0]++ ; 
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] - 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ;   
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;     
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 3 ;  
       
        }
        else if ( moving_diration == down && rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1] ].node == 2 ) {
            rat_Location[0]++ ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] - 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 4 ;              
            goal_found++  ;

        }            



        if (  moving_diration == left && ( rat_Location[1] == 0 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 1 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 3 ||
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 4 ) ) {
            moving_diration = up ;

        }
        else if ( moving_diration == left && rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node == 0 ) {     
            rat_Location[1]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] + 1 ; 
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 3 ;
        }

        else if ( moving_diration == left && rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node == 2 ) {
            rat_Location[1]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] + 1 ;  
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;           
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 4 ;         
            goal_found++  ;

        }            

        if ( moving_diration == up && ( rat_Location[0] == 0 || 
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 1 || 
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 3 ||
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 4 ) ) {
            moving_diration = right ;

        }
        else if ( moving_diration == up && rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 0 ) {         
            rat_Location[0]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] + 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ; 
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;  
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 3 ;

        }
        else if ( moving_diration == up && rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1] ].node == 2 ) {
            rat_Location[0]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] + 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ;  
            rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode = rat_map.map_V[rat_Location[0]][rat_Location[1]].node ;           
            rat_map.map_V[rat_Location[0]][rat_Location[1] ].node = 4 ;
            goal_found++  ;
        }            
        


        if ( goal_found == rat_map.count_goal ) {
            return false ;
        }


        if ( !rat_map.HavePath(rat_Location[0],rat_Location[1]) ) {
            int tempLocation1 = rat_Location[0] ;
            int tempLocation2 = rat_Location[1] ;
            if ( rat_Location[0] == 0 && rat_Location[1] == 0 ) {
                return false ;
            }
            rat_Location[0] = rat_map.map_V[tempLocation1][tempLocation2].previousNode[0] ;
            rat_Location[1] = rat_map.map_V[tempLocation1][tempLocation2].previousNode[1] ;
        }

        return true ;
    }

    bool FindPath( int row, int column ) {

           


        if ( rat_Location[0] == 0 && rat_Location[1] == 0 ) {
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 5 ;            
        }


        if (  moving_diration == right && ( rat_Location[1] == column - 1 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 1 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 0 ||
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 5 ||
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 6 ||
            rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 2 ) ) {
            moving_diration = down ;

        }
        else if ( moving_diration == right && rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 3 ) {
            rat_Location[1]++ ;            
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] - 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 5 ;

        }
        else if ( moving_diration == right && rat_map.map_V[rat_Location[0]][rat_Location[1] + 1 ].node == 4 ) {
            rat_Location[1]++ ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] - 1 ;            
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 6 ;               
            goal_found++  ;

        }            


        if (  moving_diration == down && ( rat_Location[0] == row - 1 || 
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 1 || 
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 0 ||
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 5 ||
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 6 ||
            rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 2 ) ) {
            moving_diration = left ;

        }
        else if ( moving_diration == down && rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1]].node == 3 ) {          
            rat_Location[0]++ ; 
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] - 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ;        
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 5 ;  
       
        }
        else if ( moving_diration == down && rat_map.map_V[rat_Location[0] + 1 ][rat_Location[1] ].node == 4 ) {
            rat_Location[0]++ ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] - 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 6 ;              
            goal_found++  ;

        }            



        if (  moving_diration == left && ( rat_Location[1] == 0 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 1 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 0 ||  
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 5 || 
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 6 ||          
            rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node  == 2 ) ) {
            moving_diration = up ;

        }
        else if ( moving_diration == left && rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node == 3 ) {     
            rat_Location[1]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] + 1 ; 
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 5 ;
        }

        else if ( moving_diration == left && rat_map.map_V[rat_Location[0]][rat_Location[1] - 1 ].node == 4 ) {
            rat_Location[1]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] + 1 ;             
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 6 ;         
            goal_found++  ;

        }            

        if ( moving_diration == up && ( rat_Location[0] == 0 || 
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 1 || 
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 0 ||
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 5 ||
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 6 ||
            rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 2 ) ) {
            moving_diration = right ;

        }
        else if ( moving_diration == up && rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1]].node == 3 ) {         
            rat_Location[0]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] + 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ;   
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = 5 ;

        }
        else if ( moving_diration == up && rat_map.map_V[rat_Location[0] - 1 ][rat_Location[1] ].node == 4 ) {
            rat_Location[0]-- ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[0] = rat_Location[0] + 1 ;
            rat_map.map_V[rat_Location[0]][rat_Location[1]].previousNode[1] = rat_Location[1] ;             
            rat_map.map_V[rat_Location[0]][rat_Location[1] ].node = 6 ;
            goal_found++  ;
        }            
        

        if ( goal_found == rat_map.count_goal ) {
            return false ;
        }

        

        if ( !rat_map.HavePath_ForFindPath(rat_Location[0],rat_Location[1]) ) {
            int tempLocation1 = rat_Location[0] ;
            int tempLocation2 = rat_Location[1] ;
            if ( rat_Location[0] == 0 && rat_Location[1] == 0 ) {
                return false ;
            }
            rat_map.map_V[rat_Location[0]][rat_Location[1]].node = rat_map.map_V[rat_Location[0]][rat_Location[1]].tempNode ;
            rat_Location[0] = rat_map.map_V[tempLocation1][tempLocation2].previousNode[0] ;
            rat_Location[1] = rat_map.map_V[tempLocation1][tempLocation2].previousNode[1] ;
        }


        return true ;
    }

    void PrintMap( int row, int column ) {
        int count = 0 ;
        for ( int i = 0 ; i < row ; i++ ) {
            for ( int n = 0 ; n < column ; n++ ) {

                rat_map.PrintPoint(rat_map.map_V[i][n].node) ;
            
            }

            cout << endl ;
        }
    }

    void Print_Rat () {
        cout << rat_Location[0] << ", " << rat_Location[1] << endl ;
        if ( moving_diration == right ) {
            cout << "moving to right" << endl ;
        }
        else if ( moving_diration == left ) {
            cout << "moving to left" << endl ;
        }
        else if ( moving_diration == up ) {
            cout << "moving to up" << endl ;
        }
        else if ( moving_diration == down ) {
            cout << "moving to down" << endl ;
        }
    }

    void PrintMap_Num( int row, int column ) {
        int count = 0 ;
        for ( int i = 0 ; i < row ; i++ ) {
            for ( int n = 0 ; n < column ; n++ ) {

                cout << rat_map.map_V[i][n].node ;
            
            }

            cout << endl ;
        }
    }
};

int main() {
    Rat rat1 ;
    rat1.rat_map.Create_map( rat1.rat_map.array_row, rat1.rat_map.array_column ) ;
    while ( rat1.moving( rat1.rat_map.array_row, rat1.rat_map.array_column ) ) {
        Sleep(0) ;
    }

    if ( rat1.rat_Location[0] == 0 && rat1.rat_Location[1] == 0 ) {
        rat1.PrintMap( rat1.rat_map.array_row , rat1.rat_map.array_column ) ;
    } 
    else {
        rat1.PrintMap( rat1.rat_map.array_row , rat1.rat_map.array_column ) ; 
        cout << endl ;    
        rat1.rat_Location[0] = rat1.rat_Location[1] = 0 ;
        rat1.goal_found = 0 ;
        while ( rat1.FindPath( rat1.rat_map.array_row, rat1.rat_map.array_column ) ) {
            Sleep(0) ;
        }
        rat1.PrintMap( rat1.rat_map.array_row , rat1.rat_map.array_column ) ;            
    }

    return 0 ;
}
