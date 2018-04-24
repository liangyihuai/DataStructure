#include <iostream>

#include "FibonacciHeap.h"

using namespace std;

int main() {
	FibonacciHeap<int> heap;
	heap.Insert(2);
	heap.Insert(3);
	heap.Insert(6);
	heap.Insert(4);
	heap.Insert(5);

	cout << heap.DeleteMin() << endl;
	
	return 0;
}