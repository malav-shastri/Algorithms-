#ifndef __BS_TREE_H__
#define __BS_TREE_H__
#include <iostream>
using namespace std;

struct bs_tree_node
{
    int key;
    bs_tree_node* left;
    bs_tree_node* right;
    bs_tree_node* p;
};


class bs_tree
{ 
  protected:
    bs_tree_node* T_root;

  public:
    int input_bst = 0;
    int duplicate_bst = 0;
    int array_index_bst;
    bs_tree();
    ~bs_tree();
    void insert(int*, int);
    void insert(int);

    void getcounters(){
      cout<<"Number of duplicate values="<<duplicate_bst<<endl;
    }
    int inorder_tree_walk(int* output_array_bst){
      array_index_bst = 0;
      inorder_output(T_root, output_array_bst);
      return input_bst-duplicate_bst;
      }
    void output()
      { output(T_root, 1); }


   protected:
    void insert(bs_tree_node*);
    void remove_all(bs_tree_node*);
    void inorder_output(bs_tree_node*, int*);
    void output(bs_tree_node*, int);
};


#endif
