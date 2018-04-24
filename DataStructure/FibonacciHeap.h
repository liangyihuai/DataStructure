#pragma once

template<class T> class FibonacciHeap;

template <class T>
class FibonacciNode {
	friend class FibonacciHeap<T>;

public:
	FibonacciNode() {}
	FibonacciNode(T &data):data(data) {}

private:

	FibonacciNode<T> *child = nullptr, *link = nullptr;

	int degree;
	T data;
};

template <class T>
class FibonacciHeap {

public:
	//the four Fibonacci heap operations
	const T& GetMin() const;
	void Insert(const T&);
	T& DeleteMin();
	void Meld(FibonacciHeap<T>*);

private :
	FibonacciNode<T> *min = nullptr;

	void JoinMinTrees(FibonacciNode<T> *, FibonacciNode<T> *);
};

template<class T>
void FibonacciHeap<T>::Insert(const T &data) {
	T tempData = data;
	FibonacciNode<T> *newNode = new FibonacciNode<T>(tempData);
	if (!min) {
		min = newNode;
		min->link = min;
		return;
	}

	FibonacciNode<T> *tempNode = min->link;
	min->link = newNode;
	newNode->link = tempNode;

	if (data < min->data) min = newNode;
}

template <class T>
void FibonacciHeap<T>::Meld(FibonacciHeap<T>* heap) {
	FibonacciNode<T> tmp = this->min->link;
	min->link = heap->min->link;
	heap->min->link = tmp;

	FibonacciNode<T> tempMin = this->min;
	
	if ((heap->min)->data < this->min->data) {
		this->min = heap->min;
	}
}

template<class T>
void insertChild(FibonacciNode<T> * father, FibonacciNode<T> * child) {
	father->degree++;

	if (!father->child) {
		father->child = child;
		child->link = child;
	}
	else {
		FibonacciNode<T> * temp = father->child->link;
		father->child->link = child;
		child->link = temp;
	}
}

template<class T>
void FibonacciHeap<T>::JoinMinTrees(FibonacciNode<T> * head1, FibonacciNode<T> *head2) {
	FibonacciNode<T> *tempMin = head1;
	FibonacciNode<T> *tempMax = head2;

	if (head2->data < head1->data) {
		tempMin = head2;
		tempMax = head1;
	}

	insertChild(tempMin, tempMax);
	head1 = tempMin;
}

template<class T> 
T& FibonacciHeap<T>::DeleteMin() {
	if (!min) throw "the heap is empty";
	if (!min->child && min->link == min) {//only one node
		T t = min->data;
		delete min;
		return t;
	}

	T x = min->data;
	FibonacciNode<T> * y = min->child;
	FibonacciNode<T> * brother = min->link;
	if (min->link == min) brother = nullptr;

	delete min;
	min = nullptr;
	min = brother;

	//break the circle of link y
	if (y) {
		FibonacciNode<T> *temp = y->link;
		y->link = nullptr;
		y = temp;
	}
	//count and maxDegree
	int count = 0;
	int maxDegree = 0;
	FibonacciNode<T> * curr = min;
	while (!curr) {
		count++;
		if (curr->degree > maxDegree) maxDegree = curr->degree;
		curr = curr->link;
	}
	curr = y;
	while (!curr) {
		count++;
		if (curr->degree > maxDegree) maxDegree = curr->degree;
		curr = curr->link;
	}
	maxDegree += count;

	//store heads in the array
	FibonacciNode<T> *arr[] = new FibonacciNode<T>[count];..
	FibonacciNode<T> * curr = min;
	int index = 0;
	while (!curr) {
		arr[index++] = curr;
		curr = curr->link;
	}
	curr = y;
	while (!curr) {
		arr[index++] = curr;
		curr = curr->link;
	}
	
	//combine min heaps who have same degree.
	FibonacciNode<T> *tree[maxDegree] = {nullptr};
	for (int i = 0; i < count; i++) {
		for (int d = arr[i]->degree; tree[d]; d++) {
			JoinMinTrees(arr[i], tree[d]);
			tree[d] = 0;
		}
		tree[d] = arr[i];
	}

	//create a circle link
	curr = nullptr;
	min = nullptr;
	FibonacciNode<T> start = nullptr;
	bool isFirst = false;
	for (int i = 0; i < maxDegree; i++) {
		if (!tree[i])continue;
		if (isFirst) {
			start = tree[i];
			curr = start;
			min = start;
			isFirst = true;
			continue;
		}
		curr->link = tree[i];
		curr = curr->link;
		if (curr->data < min->data) min = curr;
	}
	curr->link = start;

	return x;
}

