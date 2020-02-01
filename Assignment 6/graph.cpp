
#include "graph.h"
#include <list>
#include <iostream>
using namespace std;

/*
 * constructor/destructor
 */
graph::graph(int n)
{ /*<<<*/
  no_vert = (n > 0) ? n : 1;

/*
 * allocate adjacency matrix
 */
  max_edges = no_vert*no_vert - no_vert;   //Max edges allowed to avoid self directed cycles.
  m_edge = new int*[no_vert];
  for (int i = 0; i < no_vert; i++)
    m_edge[i] = new int[no_vert];
  initialize();
} /*>>>*/

graph::~graph()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  for (int i = 0; i < no_vert; i++){
    delete[] m_edge[i];
    delete[] shortest_weight[i];
    delete[] predecer[i];
  }
  delete[] m_edge;
  delete[] shortest_weight;
  delete[] predecer;
  delete[] d;
  delete[] pie;
} /*>>>*/


void graph::initialize()
{ /*<<<*/
/*
 * initialize adjacency matrix
 * -> use infinity to allow 0 weight edges
 */
  for (int i = 0; i < no_vert; i++)
    for (int j = 0; j < no_vert; j++)
      m_edge[i][j] = INT_MAX;

} /*>>>*/
void graph::random_graph(int m, int w){
  if(m>max_edges){
    cout<<"Number of edges are greater then allowed maximum edges inorder to avoid self directed cycles"<<endl;
    return;
  }
  else{
    int count = 0;
    int *random_vertices = new int(no_vert);
    while(count<m){     //Execute only if already randomly created values have not exceeded given edges number m.
      permutation(random_vertices,no_vert);
      int i = 0;
      while(i<no_vert-1){
        int pred = random_vertices[i];
        int succ = random_vertices[i+1];
        if(m_edge[pred][succ]==INT_MAX && count<m){ //Check whether randomly generated edges do not exceed given edge value m
          random_generator rg;
          int random_weight;
          rg >> random_weight;
          int heighest = w;
          int lowest = -w;
          random_weight = random_weight%(2*heighest+1)+lowest;
          set_edge(pred,succ,random_weight);    //Call set edge to set the edge.
          count++;
        }
        i++; 
      }
    }
    //delete random_vertices; 
  }
}
void graph::set_edge(int i,int j, int w){
  m_edge[i][j]=w;
}

void graph::init_single_source(int s){ /*<<<*/
  d = new int[no_vert];     //array d holds the distance from the source s to vertex u
  pie = new int[no_vert];   //array pie holds the predecer of a vertex
  for (int i = 0; i < no_vert; i++)
  {
    d[i] = INT_MAX;           //Initialize d and pie values for each vertex
    pie[i] = 0;
  }
  d[s] = 0;
} /*>>>*/
void graph::relax(int u, int v, int w){ /*<<<*/
  if (d[v] > (d[u] + w)){
    d[v] = d[u] + w;
    pie[v] = u;
  }
} /*>>>*/
void graph::bellmanFord(int s){ /*<<<*/
  init_single_source(s);
  for (int n = 0; n < no_vert - 1; n++){
    for(int i = 0; i < no_vert; i++){
      for (int j = 0; j < no_vert; j++){
        if (m_edge[i][j] != INT_MAX){      //Necessary to check otherwise it might happen that it relaxes and edge which actually is not existing eventually resulting in unnecessary negative weight cycle. 
          relax(i, j, m_edge[i][j]);
        }
      }
    }
  }
  for (int i = 0; i < no_vert; i++){
    for (int j = 0; j < no_vert; j++){
      if (m_edge[i][j] != INT_MAX){    //Necessary to check otherwise it might result in unnecessary negative weight cycle.
        if (d[j] > d[i] + (m_edge[i][j])){
          cout<<"------------------------------"<<endl;
          cout<<"BellmanFord:Negative weight cycle exist"<<endl;
          cout<<"------------------------------"<<endl;
          return;         //If negative weight cycle exists exit the function.
        }
      }
    }
  }
  cout<<"------------------------------"<<endl;
  cout<<"BellmanFord:No negative weight cycle exist"<<endl;
  cout<<"------------------------------"<<endl;
  for (int i = 0; i < no_vert; i++){
    if(d[i]==INT_MAX){
      cout<<"Distance from source to vertex "<<i<<":"<<"inf"<<endl;
    }
    cout<<"Distance from source to vertex "<<i<<":"<<d[i]<<endl;
  }
  cout<<"------------------------------"<<endl;
  for (int i = 0; i < no_vert; i++){
    cout<<"Predecer of a vertex "<<i<<":"<<pie[i]<<endl;
  }
  cout<<"------------------------------"<<endl;
}

/*
 * Floyd-Warshall Algorithm for all-pairs shortest path
 */

void graph::FloydWarshall(){ 
//To implement this without intermediate matrix one method is to use dynamic programming tabular method without memoization.
//Without memoization because we need to retain value at each cell in metrix with respect to different vertex.

  shortest_weight = new int *[no_vert];       //To store the sortest path weights
  predecer = new int *[no_vert];              //To store the predecers 

  for (int i = 0; i < no_vert; i++){
    shortest_weight[i] = new int[no_vert];
    predecer[i] = new int[no_vert];
  }

  for (int i = 0; i < no_vert; i++){          //Initialize weight matrix, Reference: TextBook, Chapter 25, Page 694
    for (int j = 0; j < no_vert; j++){
      if (i == j){
        shortest_weight[i][j] = 0;
      }
      else{
        shortest_weight[i][j] = m_edge[i][j];
      }
    }
  }

  for (int i = 0; i < no_vert; i++){        //Initialize predecer matrix, Reference: TextBook, Chapter 25, Page 695
    for (int j = 0; j < no_vert; j++){
      if (i != j && m_edge[i][j] < INT_MAX){      //Equation 25.6
        predecer[i][j] = i;
      }
      else{
        predecer[i][j] = INT_MAX;
      }
    }
  }
  for (int k = 0; k < no_vert; k++){      //Run for each vertex.
    for (int i = 0; i < no_vert; i++){
      for (int j = 0; j < no_vert; j++){
        //No need to compute for edges which does not exist.(INT_MAX)
        if (shortest_weight[i][k] != INT_MAX && shortest_weight[k][j] != INT_MAX && (shortest_weight[i][k] + shortest_weight[k][j] < shortest_weight[i][j])){//Equation 25.7 Textbook  //Rather then taking min(shortest_weight[i][k] + shortest_weight[k][j],shortest_weight[i][j]) we are making it as a condition so according to TextBook we can compute value of predecers cells along with it.  
          shortest_weight[i][j] = shortest_weight[i][k] + shortest_weight[k][j];      //Compute cell values for both the matrix. Reference: TextBook, Chapter 25, Page 695, 697.
          predecer[i][j] = predecer[k][j];        //If the given if condition fails keep the same values as the previous iteration 
        }
      }
    }
  //Print the shortest weight matrix D(n)
  cout << "------------------FloydWarshall::D"<<"("<<k<<")------------------"<< endl;
  //cout << "[";
  for (int i = 0; i < no_vert; i++)
    {
      cout << "[\t";
      for (int j = 0; j < no_vert; j++)
	if (shortest_weight[i][j] == INT_MAX)
	  cout << "Inf\t";
	else
	  cout << shortest_weight[i][j] << "\t";
      cout << "]" << endl;
    }
  //cout << "]" << endl;
  //Print predecer matrix P(n)
  cout << "------------------FloydWarshall::P"<<"("<<k<<")------------------"<< endl;
  //cout << "[";
  for (int i = 0; i < no_vert; i++)
    {
      cout << "[\t";
      for (int j = 0; j < no_vert; j++)
	if (predecer[i][j] == INT_MAX)
	  cout << "NIL\t";
	else
	  cout << predecer[i][j] << "\t";
      cout << "]" << endl;
    }
  //cout << "]" << endl;
  }
}

void graph::permutation(int* perm, int n)
{ /*<<<*/
  random_generator rg;
  int p_tmp, p_pos;

  for (int i = 0; i < n; i++)
    perm[i] = i;
  
  for (int i = 0; i < n; i++)
    {
      rg >> p_pos;
      p_pos = (p_pos % (n - i)) + i;

      p_tmp = perm[i];
      perm[i] = perm[p_pos];
      perm[p_pos] = p_tmp;
    }
} /*>>>*/

void graph::output()
{ /*<<<*/
  cout << "[";
  for (int i = 0; i < no_vert; i++)
    {
      cout << "[\t";
      for (int j = 0; j < no_vert; j++)
	if (m_edge[i][j] == INT_MAX)
	  cout << "Inf\t";
	else
	  cout << m_edge[i][j] << "\t";
      cout << "]" << endl;
    }
  cout << "]" << endl;
} /*>>>*/
