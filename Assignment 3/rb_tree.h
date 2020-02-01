#ifndef __RB_TREE_H__
#define __RB_TREE_H__
#include <iostream>

using namespace std;

enum rb_tree_color 
{
  RB_RED,
  RB_BLACK
};

struct rb_tree_node 
{
  int		key;
  int		color;
  rb_tree_node*	left;
  rb_tree_node*	right;
  rb_tree_node*	p;
};

class rb_tree
{ 
  protected:
    rb_tree_node*	T_nil;
    rb_tree_node*	T_root;

  public:
    int input_rbt = 0;
    int black_height_left = 0;
    int leftHeight = 0;
    int rightHeight = 0;
    int duplicate_rbt = 0;
    int is_case1=0;
    int is_case2=0;
    int is_case3=0;
    int leftrotate=0;
    int rightrotate=0;
    int array_index_rbt = 0;
    rb_tree();
    ~rb_tree();

    void insert(int*, int);
    void insert(int);

    void getcounters(){
      cout<<"Number of duplicate values="<<duplicate_rbt<<endl;
      cout<<"Number of times insertion case 1 happened="<<is_case1<<endl;
      cout<<"Number of times insertion case 2 happened="<<is_case2<<endl;
      cout<<"Number of times insertion case 3 happened="<<is_case3<<endl;
      cout<<"Number of times left rotate happened="<<leftrotate<<endl;
      cout<<"Number of times right rotate happened="<<rightrotate<<endl;
    }
    void test_black_height(){
      black_height_left = black_height(T_root)+1;       //Root node is always black
      cout<<"Black Height="<<black_height_left<<endl;
      if(black_height_left){
        cout<<"Property 5 Satisfies"<<endl;
      }
      else{
        cout<<"Something wrong with RBT"<<endl;
      }
      //cout<<"Right Black Height"<<black_height_right<<endl;
    }
    int inorder_tree_walk(int* output_array_rbt){
      array_index_rbt = 0;
      inorder_output(T_root, output_array_rbt, 1);
      return input_rbt-duplicate_rbt;
      }
    void output()
      { output(T_root, 1); }

  protected:
    int black_height(rb_tree_node*);
    void insert(rb_tree_node*);
    void insert_fixup(rb_tree_node*&);

    void remove_all(rb_tree_node*);

    void left_rotate(rb_tree_node*);
    void right_rotate(rb_tree_node*);

    void inorder_output(rb_tree_node*, int*, int);
    void output(rb_tree_node*, int);
};


#endif
