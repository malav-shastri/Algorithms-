#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "sort.h"
using namespace std;

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;
  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

/*________________________________________________string compare according to d____________________________________________________*/

int string_compare_digit(char* s1, char *s2, int A_len, int key_len, int d)
{ 
/*
  We assume that s1 and s2 are non-null pointers
*/
  if(d<=A_len && d<=key_len){       //While position d is present in the string
    if(s1[d-1] == s2[d-1]){        //while both the characters at dth position are equal (d-1 because if position is d then at that position index is d-1)
      return 0;
    }
    else{
      if (s1[d-1] < s2[d-1]){    //While char at d in s1 is smaller then char at d in s2
        return -1;
      }
      else{
        return 1;
      }
    }
  }
  else if(d>A_len && d>key_len){    //when in both the strings given position d is not present, d is greater then its length
    return 0;
  }
  else{
    if(d>A_len && d<=key_len){    //When position d is empty in
      return -1;
    }
    else if(d>key_len && d<=A_len){
      return 1;
    }
  }
} 

/*________________________________________________Insertion Sort according to digit____________________________________________________*/

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{ 
  int i;
  char* key;
  int key_len;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      key_len = A_len[j];
      i = j - 1;
      while ((i >= l) && (string_compare_digit(A[i], key, A_len[i], key_len, d) > 0)) //Created new function to compare 2 strings according to char at d similar to one given in the skeleton code.
        {
          A[i+1] = A[i];
          A_len[i+1] = A_len[i];
          i = i - 1;
        }
      A[i+1] = key;
      A_len[i+1] = key_len;
    }
  //cout<<"Updated Insertion Sort Completed";
}

/*________________________________________________Insertion Sort (Given skeleton code)____________________________________________________*/

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;
  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;
      while ((i >= l) && (string_compare(A[i], key) > 0))
        {
          A[i+1] = A[i];
          i = i - 1;
        }
      A[i+1] = key;
    }
  //cout<<"Insertion Sort Completed";
}

/*________________________________________________Radix sort with insertion sort____________________________________________________*/

void radix_sort_is(char** A, int* A_len, int n, int m)
{
  for(int d = m ; d>0; d--){
    insertion_sort_digit(A, A_len, 0, n-1, d);
  }
}

/*___________________To find max among dth(d-1 index) from all the input strings______________________________________________*/

/*int getMax(char** array, int n, int d) {
   int max = array[0][d-1];
   for(int i = 1; i<n; i++){          //To use when running with the approach of assigning max value as the size of counter array
      if(array[i][d-1] > max){        //Good practice for saving space and to create dinamically sized array every time but then the counting sort would not be a fully non comparing algorithm any more.
         max = array[i][d-1];
         }
   }
   return max;
}*/

//_________________________Counting Sort algorithm_________________________________________________________

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
  //int max = getMax(A, n, d); //Rather then taking C[256] ive set the size of the counter to the max value among all the characters from dth position in every string.
  //int *count = new int[max+1]; //Using max value rather then C[256] will avoid using unnecessary extra space blocked by count array.
  int max = 256;         //To run it with fixt sized storage array 
  int *count = new int[max];      //To run it with fixed size storage array.
  for(int i = 0; i<=max; i++){
    count[i] = 0;
  }
  for(int i = 0; i < n; i++){
    if(d>A_len[i]){       //if string does not have dth position.
      count[0]++;
    }
    else{
      count[A[i][d-1]]++; //increase counter to count the frequencies of values in input array at (d-1)th index.
    }
  }
  for(int i = 1; i<=max; i++){
    count[i] += count[i-1]; //find cumulative frequency
  }
  for(int i = n-1; i>=0; i--){
    if(d<=A_len[i]){
      B[count[A[i][d-1]]-1] = A[i];
      B_len[count[A[i][d-1]]-1] = A_len[i];
      count[A[i][d-1]] -= 1;
    }
    else{               //When d is larger then length, dth position is empty.
      B[count[0]-1] = A[i];
      B_len[count[0]-1] = A_len[i];
      count[0] -= 1;
    }
  }
  /*
  cout<<"In the counting sort cumulative count array is"<<endl;
  for(int i = 0; i<=max; i++){
    cout<<count[i];
  }
  cout<<endl;*/
  for(int i = 0; i<n; i++){
    A[i] = B[i]; //store temporary output array to main array
    A_len[i] = B_len[i];
  }
delete[] count;   //Free allocated storage
}

//_______________________________________Radix sort with counting sort_______________________________________

void radix_sort_cs(char** A, int* A_len, int n, int m)
{
  char** output_array= new char*[n];    //temporary array to store output 
  int* output_len = new int[n];   //Temporary array strings lengths
  for(int d = m ; d>0; d--){
    counting_sort_digit(A, A_len, output_array, output_len, n, d);
  }
  delete[] output_array;  //Free allocated storage
  delete[] output_len;    //Free allocated storage
}
/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
