#include "graph.h"
#include <iostream>
using namespace std;

int main(){
    int nodesbfs = 7;
    int nodesdfs = 12;
    int **matrixbfs = new int*[nodesbfs];;      //Create and initialized empty Adjacency matrix
    for (int i = 0; i < nodesbfs; i++){
        matrixbfs[i] = new int[nodesbfs];
        for (int j = 0; j < nodesbfs; j++){
            matrixbfs[i][j] = 0;
        }
    }
    int **matrixdfs = new int*[nodesdfs];;      //Create and initialized empty Adjacency matrix
    for (int i = 0; i < nodesdfs; i++){
        matrixdfs[i] = new int[nodesdfs];
        for (int j = 0; j < nodesdfs; j++){
            matrixdfs[i][j] = 0;
        }
    }

    Graph* bfs = new Graph(nodesbfs); //Use this when you want to pass only number of nodes in the Constructor. And set edges using set_edge() function.
    Graph* dfs = new Graph(nodesdfs); //Use this when you want to pass only number of nodes in the Constructor. And set edges using set_edge() function.

    /*         //To use Adjacency matrix
    matrixbfs[0][1] = 1;
    matrixbfs[0][3] = 1;
    matrixbfs[0][4] = 1;
    matrixbfs[1][6] = 1;
    matrixbfs[1][5] = 1;
    matrixbfs[1][2] = 1;
    matrixbfs[1][0] = 1;
    matrixbfs[4][0] = 1;
    matrixbfs[3][0] = 1;
    matrixbfs[6][1] = 1;
    matrixbfs[5][1] = 1;
    matrixbfs[2][1] = 1;
    */
    /*          //To use Adjacency matrix
    matrixdfs[0][3] = 1;
    matrixdfs[3][0] = 1;
    matrixdfs[1][3] = 1;
    matrixdfs[3][1] = 1;
    matrixdfs[3][4] = 1;
    matrixdfs[4][3] = 1;
    matrixdfs[2][1] = 1;
    matrixdfs[2][4] = 1;
    matrixdfs[6][4] = 1;
    matrixdfs[6][10] = 1;
    matrixdfs[7][6] = 1;
    matrixdfs[5][7] = 1;
    matrixdfs[8][7] = 1;
    matrixdfs[5][8] = 1;
    matrixdfs[8][5] = 1;
    matrixdfs[10][7] = 1;
    matrixdfs[9][10] = 1;
    matrixdfs[10][11] = 1;
    matrixdfs[11][9] = 1;
    */
                //To use set_edge() function
    bfs->set_edge(0,1,1);
    bfs->set_edge(0,3,1);
    bfs->set_edge(0,4,1);
    bfs->set_edge(1,6,1);
    bfs->set_edge(1,5,1);
    bfs->set_edge(1,2,1);
    bfs->set_edge(1,0,1);
    bfs->set_edge(4,0,1);
    bfs->set_edge(3,0,1);
    bfs->set_edge(6,1,1);
    bfs->set_edge(5,1,1);
    bfs->set_edge(2,1,1);
                //To use set_edge() function
    dfs->set_edge(0,3,1);
    dfs->set_edge(3,0,1);
    dfs->set_edge(1,3,1);
    dfs->set_edge(3,1,1);
    dfs->set_edge(3,4,1);
    dfs->set_edge(4,3,1);
    dfs->set_edge(2,1,1);
    dfs->set_edge(2,4,1);
    dfs->set_edge(6,4,1);
    dfs->set_edge(6,10,1);
    dfs->set_edge(7,6,1);
    dfs->set_edge(5,7,1);
    dfs->set_edge(8,7,1);
    dfs->set_edge(5,8,1);
    dfs->set_edge(8,5,1);
    dfs->set_edge(10,7,1);
    dfs->set_edge(9,10,1);
    dfs->set_edge(10,11,1);
    dfs->set_edge(11,9,1);
    
    
    //Graph* bfs = new Graph(matrixbfs, nodesbfs); //Use this when you want to initialize using pre defined Adjacency matrix and number of nodes
    //Graph* dfs = new Graph(matrixdfs, nodesdfs); //Use this when you want to initialize using pre defined Adjacency matrix and number of nodes
    

    bfs->bfs(0);        //Run bfs
    dfs->dfs();         //Run dfs

    delete bfs;
    delete dfs;
    for(int i=0; i<nodesbfs; i++){
        delete[] matrixbfs[i];
    }
    delete[] matrixbfs;
    for(int i=0; i<nodesdfs; i++){
        delete[] matrixdfs[i];
    }
    delete[] matrixdfs;
    //delete matrixbfs;
    //delete matrixdfs;
    return 0;
}