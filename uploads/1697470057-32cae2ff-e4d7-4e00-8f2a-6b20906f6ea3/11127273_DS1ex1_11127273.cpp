#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

const int INF = INT_MAX;
const int ROW = 5;
const int COL = 5;

struct Node{
       int row, col, dist;
       };
       
       bool isValid(int row, int col, vector<int>>&grid,
       vector<vector<bool>>&visited)
       {
         return(riw >=0)&&(row<ROW)&&(col>=0)&&(col<COL)&&!grid[row][col]&&!visited[row][col];
         }
         
         int 
         dijksta(vector<int>>&grid){
                                    vector<vector<bool>>visited(ROW, vector<int>(COL,INF));
                                    
                                    priority_queue<Node,vector<Node>,
                                    function<bool(Node,Node)>>pq([](const Node&a, const Node&b){
                                                                          return a.dist> b.dist;
                                                                          });
                                                                          
                                                                          dist[0][0] = 0;
                                                                          pq.push({0,0,0});
                                                                          
                                                                          while (!pq.empty()){
                                                                                Node curr = pq.top();
                                                                                pq.pop();
                                                                                
                                                                                int i = curr.row;
                                                                                int j = curr.col;
                                                                                int d = curr.dist;
                                                                                
                                                                                if(i==ROW - 1 && j == COL -1){
                                                                                          return d;
                                                                                          }
                                                                                          
                                                                                          visited[i][j] = true;
                                                                                          
                                                                                          int rowNbr[] = (0,1,0,-1);
                                                                                          int colNbr[] = (1, 0, -1,0);
                                                                                          
                                                                                          for (int k = 0; k <4; ++k){
                                                                                              int ni = j + rowNbr[K];
                                                                                              int nj = j + colNbr[k];
                                                                                              
                                                                                              if(isValid(ni, nj, grid, visited)&&dist[i][j]+1;
                                                                                              pq.push({ni,nj,dist[ni][nj]);
                                                                                              }
                                                                                          }
                                                                                }
                                                                                              return -1;
                                                                                }
                                                                                int main(){
                                                                                    vector<vector<int>>grid = {
                                                                                      {0,1,0,0,0},
                                                                                      {0,1,0,1,0},
                                                                                      {0,0,0,1,0},
                                                                                      {1,1,1,1,0},
                                                                                      {0,0,0,0,0},
                                                                                    };
                                                                                    
                                                                                    int shortestPath = dijkstra(grid);
                                                                                    
                                                                                    if(shortestPath != -1){
                                                                                                    cout<< "Shortest Path Length:" << shortestPath << endl;
                                                                                                    }else{
                                                                                                          cout<<"No Path Found." << endl;
                                                                                                          }
                                                                                                          
                                                                                                          return 0;
                                                                                                    }
                                                                                    
