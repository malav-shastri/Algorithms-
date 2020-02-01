#include <cstdio>
#include <cstdlib>

#include "sort.h"
#include "bs_tree.h"
#include "rb_tree.h"
#include "timer.h"
#include "random_generator.h"

int main(int argc, char* argv[])
{ 
	random_generator rg;
	timer t;
	int n, direction, tree;

/*
 * check arguments
 */
	if (argc > 1)
	{ 
		n = atoi(argv[1]);
		n = (n < 1) ? 1 : n;
	}
	else
	{
		cout << argv[0] << " [n] [direction] [tree]" << endl;
		cout << "[n]              size of the random string array" << endl;
		cout << "[direction]            -1: input is sorted descending" << endl;
		cout << "                 1: input is sorted ascending" << endl;
		cout << "                 0: input is random" << endl;
		cout << "[tree]           0: using bs tree" << endl;
		cout << "                 1: using rb tree" << endl;
		cout << endl;
		return 0;
	}

	if (argc > 2)
		direction = atoi(argv[2]);
	else
		direction = 0;

	if (argc > 3)
		tree = atoi(argv[3]);
	else
		tree = 0;


/*
 * allocated and generate integer array
 */
	rb_tree rb;
	bs_tree bs;
	int* input_array;
	int new_size = 0;
	// int* output_array;
	// int bh;

	t.start();
	if (direction == 0)
		input_array = create_random(n);
	else
	{
		if (direction < 0)
			input_array = create_reverse_sorted(n);
		else
			input_array = create_sorted(n);
	}
	t.stop();

	cout << "Timer (generate): " << t << endl;

	// for (int i = 0; (i < n) && (i < 20); i++)
	// 	cout << input_array[i] << endl;
	// cout << endl;

/*
 * run algorithms
 */
	if (tree == 0)
	{
		cout << "Inserting Values in BS trees: " << endl;
		cout<< " size of input: " << n <<endl;
		t.start();
		bs.insert(input_array, n);
		t.stop();
		cout << "Timer for insertion in tree: " << t << endl;
		cout<<"Storing sorted values back in array: "<<endl;
		new_size = bs.inorder_tree_walk(input_array);
		bs.getcounters();
	}
	else
	{
		cout << "Running sort using RB trees: " << endl;
		cout<< " size of input: " << n <<endl;
		t.start();
		rb.insert(input_array, n);
		t.stop();
		cout << "Timer for insertion in tree: " << t << endl;
		cout<<"Storing sorted values back in array: "<<endl;
		new_size = rb.inorder_tree_walk(input_array);
		rb.getcounters();
		cout<<"Check Black Height"<<endl;
		rb.test_black_height();
	}

	cout << "Timer (sort): " << t << endl;
	cout << "New size: " << new_size << endl;


/*
 * check output
 */

	if (check_sorted(input_array, 0, new_size-1))
		cout << "The output is sorted!" << endl;
	else
		cout << "ERROR: The output is not sorted!" << endl;

	// for (int i = 0; (i < n) && (i < 20); i++)
	// 	cout << input_array[i] << endl;
	// cout << endl;

/*
 * free allocated storage
 */
	delete[] input_array;

	return 0;
}

