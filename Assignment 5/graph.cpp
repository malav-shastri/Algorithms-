#include "graph.h"
#include<iostream>
#include <queue>
using namespace std;
Graph::Graph(int n){
    if(n>0){            //To check whether negative number of nodes are provided or not
        nodes = n;      //Assign number of nodes to nodes data member of graph class
        matrix = new int*[n];
        //Create and initialize empty Adjacency Matrix 
        for(int i=0; i<n; i++){
            matrix[i] = new int[n];
        }
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                matrix[i][j] = 0;
            }
        }
    }
    else{               //Without this condition code was terminating without any error in case of invalid number and was just throwing Segmentation fault.
        cout<<"Number of nodes are less then 1"<<endl;
        return;
    }
}
Graph::Graph(int** adjmat, int n){
    if(n>0){
        nodes = n;      //Assign number of nodes to nodes data member of graph class
        matrix = new int*[n];       
        for(int i=0; i<n; i++){
            matrix[i] = new int[n];
        }
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                matrix[i][j] = adjmat[i][j];    //Assign Adjacency matrix to matrix data member of class Graph
            }
        }
    }
    else{           //Without this condition code was terminating without any error in case of invalid number and was just throwing Segmentation fault.
        cout<<"Number of nodes are less then 1"<<endl;
        return;
    }
}
Graph::~Graph(){            //Destructor method
    for(int i=0; i<nodes; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}
bool Graph::set_edge(int u,int v,int w){
    if(u<nodes && v<nodes && u>=0 && v>=0){          //To check if any invalid number of nodes are given in Argument or not
        matrix[u][v] = w;
        return true;
    }
    else{        //Without this condition code was terminating without any error in case of invalid number and was just throwing Segmentation fault.
        cout<<"invalid nodes";
        return false;
    }
    
    
}
void Graph::bfs(int node){
    if(node>=0 && node<nodes-1){                //To check the invalid value of nodes
        set <int>* visited = new set<int>;      //Create new set for storing Visited Nodes
        cout<<"Order of BFS Traversal"<<endl;
        bfs(node,visited);                     
    }
    else{
        cout<<"Invalid Starting Node";
        return;
    }
    cout<<endl;
}
void Graph::bfs(int node, set<int>* visited){
    //Reference: algorithm given in slides
    queue <int> Que;
    Que.push(node);
    visited->insert(node);
    cout<<node<<'\t';           //Node id starts from 0
    while (!Que.empty()){
        int top = Que.front();      //Oldest element of queue would be taken for further exploration of its Adjacent nodes
        Que.pop();
        for (int i = 0; i < nodes; i++){
            if (matrix[top][i]==1 && visited->count(i)==0){         //Check whether there is edge between top node and all other nodes and whether among all other nodes any node has been already visited or not
                Que.push(i);
                visited->insert(i);
                cout<<i<<'\t';  
            }
        }
    }
delete visited;
}
void Graph::dfs(){ 
    //Reference: algorithm given in slides
    set <int>* visited = new set<int>;          //Create new set for storing Visited Nodes
    cout<<"Order of DFS Traversal"<<endl;
    for (int node = 0; node < nodes; node++){
        if (visited->count(node)==0){
            dfs(node,visited);              //it would check whether any node has been left for Exploring or not
        }
    }
    delete visited;
    cout<<endl;
}
// No need to use stack Explicitly we are opting Recursive Approach according to given in slide which ensures we that we are visiting every node and its Adjacent nodes level wise.
void Graph::dfs(int node, set<int>* visited){
    visited->insert(node);
    cout<<node<<'\t';           //Node id starts from 0 
    for (int i = 0; i < nodes; i++){
        if (matrix[node][i]==1 && visited->count(i)==0){
            dfs(i,visited);             //Recursively visit all Adjacent nodes. Node id starts from 0.
        }
    }
}