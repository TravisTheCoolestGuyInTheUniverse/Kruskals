#include <iostream>

using namespace std; 

//MinHeap class header
template<class T>
class MinHeap {
	public:
		MinHeap(int);
		~MinHeap();
		int LeftChild(int);
		int RightChild(int);
		int Parent(int);
		void HeapInsert(T);
		void HeapIncreaseKey(int, T);
		void exchange(T&, T&);
		void MinHeapify(int);
		T HeapMinimum();
		T HeapExtractMin();
		void HeapPrint();
	private:
		T* heapArray;
		int heapSize;
		int maxSize;
};