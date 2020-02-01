#ifndef __AM_GRAPH_H__
#define __AM_GRAPH_H__

#include <limits.h>
#include "random_generator.h"
    
class graph
{
  protected:
    int max_edges;
    int**	m_edge;
    int		no_vert;
    int* d;
    int* pie;
    int **shortest_weight;
    int **predecer;



  public:
    graph(int);
    ~graph();

    int get_no_of_vertices()
      { return no_vert; }

    void output();
    void set_edge(int,int, int);
    void relax(int,int,int);
    void bellmanFord(int);
    void init_single_source(int);
    void FloydWarshall();
    void random_graph(int,int);
  protected:
    void initialize();
    void permutation(int*, int);
};



#endif
