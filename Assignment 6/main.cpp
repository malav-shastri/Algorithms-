#include <iostream>

#include "graph.h"
#include "random_generator.h"

using namespace std;

int main(int argc, char* argv[])
{
    int n, m, w;
    //Reference: Previous assignment skelleton codes.
    if (argc == 4){ 
        n = atoi(argv[1]);
        if (n<2){
            cout<<"Number of vertices should be more than 1"<<endl;
            return 0;
        }
        m = atoi(argv[2]);
        if (m<1){
            cout<<"Number of edges cannot be less than 1"<<endl;
            return 0;
            }
        w = atoi(argv[3]);
    }
  else{
      cout << "hw7: [n] [m] [w]" << endl;
      cout << "[n]              number of vertices in the graph" << endl;
      cout << "[m]              number of edges in the graph" << endl;
      cout << "[w]              interval for weights" << endl;
      cout << endl;
      return 0;
    }
    
    graph* random;
    random = new graph(n);
    random->random_graph(m,w);
    random->output();
    random->bellmanFord(0);
    random->FloydWarshall();

    //Book example of bellmanford
    /*int nodesbf = 5; 
    graph* bf;
    bf = new graph(nodesbf);
    bf->set_edge(0,1,6);
    bf->set_edge(0,3,7);

    bf->set_edge(1,2,5);
    bf->set_edge(1,3,8);
    bf->set_edge(1,4,-4);
   
    bf->set_edge(2,1,-2);

    bf->set_edge(3,2,-3);
    bf->set_edge(3,4,9);
    
    bf->set_edge(4,0,2);
    bf->set_edge(4,2,7);

    bf->bellmanFord(0);*/

    //delete bf;

    //Book Example of FloydWarshall
    /*graph* fw;
    int fw_nodes = n;
    fw = new graph(fw_nodes);
    
    fw->set_edge(0,1,3);
    fw->set_edge(0,2,8);
    fw->set_edge(0,4,-4);

    fw->set_edge(1,4,7);
    fw->set_edge(1,3,1);
   
    fw->set_edge(2,1,4);

    fw->set_edge(3,2,-5);
    fw->set_edge(3,0,2);
    
    fw->set_edge(4,3,6);

    
    fw->FloydWarshall();

    
    delete fw;*/
    //delete random;


    return 0;
}
  
