#include <cstdio>
#include <cstdlib>

#include "sort.h"
#include "timer.h"
#include "random_generator.h"

int main(int argc, char* argv[])
{
  random_generator rg;
  timer t;
  int n, m, d, a;
  
  if (argc > 1)
    { 
      m = atoi(argv[1]);
      m = (m < 1) ? 1 : m;
    }
  else
    {
      cout << "hw1: [m] [n] [direction]" << endl;
      cout << "[m]              size of the random integer vector array" << endl;
      cout << "[n]              dimension of integer vector array" << endl;
      cout << "[direction]      0: random" << endl;
      cout << "                 1: sorted" << endl;
      cout << "                 -1: reverse sorted" << endl;
      cout << endl;
      return 0;
    }

  if (argc > 2)
    {
      n = atoi(argv[2]);
      n = (n < 0) ? 0 : n;
    }
  else
    n = 0;

  if (argc > 3)
    d = atoi(argv[3]);
  else
    d = 0;

  int** input_array_i;
  int** input_array_im;
  int** input_array_m;

/*
 * create input array sorted/reverse sorted/random 
 * depending on program argument
 * -> input_array_i is allocated!
*/
  t.start();
  if (d == 0)
    input_array_i = create_random_ivector(n, m, true);
  else
    {
      if (d < 0)
	input_array_i = create_reverse_sorted_ivector(n, m);
      else
	input_array_i = create_sorted_ivector(n, m);
    }
  t.stop();

  cout << "Timer (generate): " << t << endl;


// output the first 2 elements for debugging purposes
 
  /*for (int i = 0; (i < m) && (i < 2); i++)
    {
      cout << "[ ";
      for (int j = 0; j < n; j++)
	cout << input_array_i[i][j] << " ";
      cout << "]" << endl;
    }
  cout << endl;*/


 //Do naiv insertion sort

  cout << "Running insertion sort algorithm: " << endl;
  t.start();
  insertion_sort(input_array_i, n, 0, m-1);
  t.stop();
  cout << "Timer (sort): " << t << endl;


  //check whether or not the naive insertion algorithm sorted the array

  if (check_sorted(input_array_i, n, 0, m-1))
    cout << "The output is sorted!" << endl;
  else
    cout << "ERROR: The output is not sorted!" << endl;

/*
 * create input array sorted/reverse sorted/random 
 * depending on program argument
 * -> input_array_im is allocated!
*/

  t.start();
  if (d == 0)
    input_array_im = create_random_ivector(n, m, true);
  else
    {
      if (d < 0)
	input_array_im = create_reverse_sorted_ivector(n, m);
      else
	input_array_im = create_sorted_ivector(n, m);
    }
  t.stop();

  cout << "Timer (generate): " << t << endl;


 // Do improved insertion sort

  cout << "Running improved insertion sort algorithm: " << endl;
  cout<<"----------------------------------------------"<<endl;
  t.start();
  insertion_sort_im(input_array_im, n, 0, m-1);
  t.stop();
  cout << "Timer (sort): " << t << endl;

 //check whether or not the algorithm sorted the array

  if (check_sorted(input_array_im, n, 0, m-1))
    cout << "The output is sorted!" << endl;
  else
    cout << "ERROR: The output is not sorted!" << endl;

/*
 * create input array sorted/reverse sorted/random 
 * depending on program argument
 * -> input_array_m is allocated!*/

  t.start();
  if (d == 0)
    input_array_m = create_random_ivector(n, m, true);
  else
    {
      if (d < 0)
	input_array_m = create_reverse_sorted_ivector(n, m);
      else
	input_array_m = create_sorted_ivector(n, m);
    }
  t.stop();

  cout << "Timer (generate): " << t << endl;

/*
 * Do merge sort
 */
  cout << "Running merge sort algorithm: " << endl;
  cout << "---------------------------------------"<< endl;
  t.start();
  merge_sort(input_array_m, n, 0, m-1);
  t.stop();
  cout << "Timer (sort): " << t << endl;

/*
 * check whether or not the algorithm sorted the array
 */
  if (check_sorted(input_array_m, n, 0, m-1))
    cout << "The output is sorted!" << endl;
  else
    cout << "ERROR: The output is not sorted!" << endl;

/*
 * output the first 2 elements for debugging purposes

  for (int i = 0; (i < m) && (i < 2); i++)
    {
      cout << "[ ";
      for (int j = 0; j < n; j++)
	cout << input_array_m[i][j] << " ";
      cout << "]" << endl;
    }
  cout << endl;

/*
 * free the allocated storage
 */
  remove_ivector(input_array_i, m);
  remove_ivector(input_array_im, m);
  remove_ivector(input_array_m, m);

  return 0;
}

