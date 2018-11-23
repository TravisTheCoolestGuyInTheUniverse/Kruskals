#include"MinHeap.h"
//MinHeap class implementation

/* constructor MinHeap() - constructs MinHeap object.
 ` precondition: n is number of elements, T is the data type of 
 ` the heap.
 ` 
 ` postcondition: MinHeap object is constructed with private member
 ` array heapArray having space for n elements of type T.
*/
template<class T>
MinHeap<T>::MinHeap(int n)
{
	//T[n+1] because heapArray will be a 1 indexed array
	heapArray = new T[n+1];
	heapSize = 0;
	maxSize = n;
}

/* class function leftChild() - returns index of left child in heap.
 ` precondition: cIndex is the current index.
 ` 
 ` postcondition: return index of left child to element at cIndex.
*/
template<class T>
int MinHeap<T>::LeftChild(int cIndex)
{
	return cIndex*2;
}

/* class function rightChild() - returns index of right child in heap.
 ` precondition: cIndex is the current index.
 ` 
 ` postcondition: return index of right child to element at cIndex.
*/
template<class T>
int MinHeap<T>::RightChild(int cIndex)
{
	return cIndex*2+1;
}

/* class function Parent() - returns index of parent in heap.
 ` precondition: cIndex is the current index.
 ` 
 ` postcondition: return index of parent to element at cIndex. 
*/
template<class T>
int MinHeap<T>::Parent(int cIndex)
{
	return cIndex/2;
}

/* class function HeapInsert() - inserts element into heap
 ` precondition: key is an object of type T
 ` 
 ` postcondition: key is positioned correctly in private T array
 ` heapArray according to the definition of Min Heap, and private 
 ` int variable heapSize incremented by 1. 
*/
template<class T>
void MinHeap<T>::HeapInsert(T key)
{
	heapSize = heapSize+1;
	HeapIncreaseKey(heapSize, key);
}

/* class function HeapIncreaseKey() - positions element correctly in array
 ` precondition: i is an int and key is of type T.
 `
 ` postcondition: heapArray is shifted until key is in the correct position.
*/
template<class T>
void MinHeap<T>::HeapIncreaseKey(int i, T key)
{
	heapArray[i] = key;
	while(i>1 && heapArray[Parent(i)] > heapArray[i])
	{
		exchange(heapArray[i], heapArray[Parent(i)]);
		i = Parent(i);
	}
}

/* class function MinHeapify() - organizes heapArray according to the 
 ` definition of Min Heap. 
 ` 
 ` precondition: i is the index of element whose left and right trees are to be MinHeapifyed.
 ` if i=1, whole heap will be MinHeapifyed.
 `
 ` postcondition: heapArray or portion of heapArray is organized according to the definition of 
 ` Min Heap.
*/
template<class T>
void MinHeap<T>::MinHeapify(int i)
{
	int l = LeftChild(i), r = RightChild(i), smallest;
	
	if (l<=heapSize && heapArray[l] < heapArray[i])
	{
		smallest = l;
	} else {
		smallest = i;
	}
	if (r<=heapSize && heapArray[r] < heapArray[smallest])
	{
		smallest = r;
	}
	if (smallest != i)
	{
		exchange(heapArray[i], heapArray[smallest]);
		MinHeapify(smallest);
	}
}

/* class function HeapMinimum() - returns minumum value in the heap.
 ` precondition: heapArray is populated.
 ` 
 ` postcondition: max T value in heap is returned.
*/
template<class T>
T MinHeap<T>::HeapMinimum()
{
	if (heapSize > 0)
		return heapArray[1];
}

/* class function HeapExtractMin() - returns min value in heap and deletes it.
 ` precondition: heapArray is populated.
 `
 ` postcondition: max T value in heap is returned, removed from heapArray.
 ` heapArray is reorganized.
*/
template<class T>
T MinHeap<T>::HeapExtractMin()
{
	if (heapSize < 1)
	{
		cerr << "Error: Heap is empty" << endl;
	} else {
		T Min = heapArray[1];
		heapArray[1] = heapArray[heapSize];
		heapSize = heapSize - 1;
		MinHeapify(1);
		return Min;
	}
}

/* class function exchange() - exchanges values of two variables
 ` precondition: firstItem and secondItem are both references to T's.
 ` 
 ` postcondition: firstItem contains the initial value of secondItem 
 ` and vice versa.
*/
template<class T>
void MinHeap<T>::exchange(T& firstItem, T& secondItem)
{
	T tmp = firstItem;
	firstItem = secondItem;
	secondItem = tmp;
}

/* class function HeapPrint() - prints contents of heapArray.
 ` precondition: private member array heapArray is populated.
 `
 ` postcondition: contents of heapArray are printed to standard ouotput.
*/
template<class T>
void MinHeap<T>::HeapPrint()
{
	for (int i=1; i<=heapSize; i++)
	{
		cout << i << ": " << heapArray[i] << endl;
	}
}

/* class destructor ~MinHeap()
 ` postcondition: memory allocated for private member array heapArray is 
 ` deallocated.
*/
template<class T>
MinHeap<T>::~MinHeap()
{
	delete [] heapArray;
	heapArray = NULL;
}