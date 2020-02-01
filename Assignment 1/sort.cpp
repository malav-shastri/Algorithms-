#include <cstdio>
#include <cstdlib>
#include "sort.h"
#include <iostream>


int ivector_length(int* v, int n){
  int sum;
  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];
  return sum;
}


/*________________________________________________Naive Insertion Sort____________________________________________________*/

void insertion_sort(int** A, int n, int l, int r){ 
  int i;
  int* key;
  for (int j = l+1; j <= r; j++){
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n))){
          A[i+1] = A[i];
          i = i - 1;
        }
      A[i+1] = key;
    }
}

/*________________________________________________Improved Insertion Sort____________________________________________________*/

void insertion_sort_im(int** A, int n, int l, int r)
{ 
  int i;
  int* key;
  int vectorLengthArray[r+1];            //Array to store precomputed lengths of vectors.
  int* pointvectorlen=vectorLengthArray;     //Pointer to point to the vector length array.
  int k = 0;
  while(k<=r){
    vectorLengthArray[k]=(ivector_length(A[k], n));      //To pre-compute the sum of vector members before entering in the sorting process which will bring down the complexity from O(N^3) to O(N^2)
    k++;                                                        
  }

  for (int j = l+1; j <= r; j++){
      key = A[j]; // key is pointer that points to first vector of unsorted vectors
      i = j - 1;
      int keylength=vectorLengthArray[j]; //integer that stores the length of the vector that key points to
      while ((i >= l) && (pointvectorlen[i] > keylength)){ //Compare the vector lengths of array elements.
        A[i+1] = A[i];  //shift array elements
        vectorLengthArray[i+1]= vectorLengthArray[i]; //shift vector elements
        i = i - 1;
      }
      A[i+1] = key;
      vectorLengthArray[i+1]=keylength;
      } 
  //delete[] key;
}

/*________________________________________________Merge Sort____________________________________________________*/

void merge(int** A, int* vectorLengthArray, int l, int midpoint, int r, int n){
  int **tempA = new int*[r-l+1];  //Temporary two dimensional array to store the intermediate merging values
  int *vectorLengthTemp = new int[r-l+1];  //Temporary vector length array to store intermediate vector length merging values 
  int i = l;
  int k = 0;
  int j = midpoint + 1;
    while (i <= midpoint && j <= r){   //For the divided left and right arrays run loop till it reaches the end point of anyone of the 2 arrays
        if (vectorLengthArray[i] < vectorLengthArray[j]){   //Compare vector lengths
            vectorLengthTemp[k] = vectorLengthArray[i];
            tempA[k]= A[i];
            k++;
            i++;
        }
        else{
            vectorLengthTemp[k] = vectorLengthArray[j];
            tempA[k] = A[j];
            k++;
            j++;
        }
    }
    while (i <= midpoint){
        vectorLengthTemp[k] = vectorLengthArray[i];
        tempA[k] = A[i];
        k++;
        i++;
    }
    while (j <= r){
        vectorLengthTemp[k] = vectorLengthArray[j];
        tempA[k] = A[j];
        k++;
        j++;
    }
    for (i = l; i <= r; i++){
        vectorLengthArray[i] = vectorLengthTemp[i-l];
        A[i] = tempA[i-l];
    }
delete [] tempA;
delete [] vectorLengthTemp;
}

void merge_sort_logic(int** A, int* vectorLengthArray, int l, int r, int n){
  int midpoint ;
  if(l < r){
    midpoint = (l + r) / 2;     //Find the midpoint
    merge_sort_logic(A, vectorLengthArray, l, midpoint, n);   //Recursively call function again to divide in left array
    merge_sort_logic(A, vectorLengthArray, midpoint+1, r, n); //Recursively call function again to divide in right array
    merge(A, vectorLengthArray, l, midpoint,r, n);    //Merge both of them.
  }
}

void merge_sort(int **A, int n, int l, int r){      //Main Program is calling this function, and this function iscalling actual merge sort as we want to pre-compute the vector lengths.
  int z = l;
  int vectorLengthArray[r+1];
  while(z<=r){
    vectorLengthArray[z] = ivector_length(A[z], n);
    z++;
    }
    merge_sort_logic(A,vectorLengthArray,l,r,n);
}
/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}

/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

