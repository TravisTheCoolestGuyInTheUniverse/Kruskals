#include <iostream>

using namespace std;
#ifndef DISJOINTSETS
#define DISJOINTSETS

//how this works is before the compiler compiles, 1 replaces everywhere a MEM_ERR is with 1.
//used to target particular platforms.
#define MEM_ERR 1
#define EMPTY_DS 2
#define ITEM_NOT_FOUND 3
#define INVALID_SIZE 4

//disjoint sets error class. exception handling class
class ds_err {
	public: 
	ds_err(int ec):err_code(ec) {}
	const string errorDesc(void)
	{
		switch(err_code)
		{
			case MEM_ERR: return "out of memory";
			case EMPTY_DS: return "Disjoint Sets are empty";
			case ITEM_NOT_FOUND: return "Item not in list";
			case INVALID_SIZE: return "The number of disjoint sets must be greater than 0";
			default: return "unknown error";
		}
	}
	
	private:
	int err_code;
};

//DisjointSets class header
class DisjointSets {
	public:
	DisjointSets(int);
	~DisjointSets();
	int findSet(int);
	void unionSet(int, int);
	
	private:
	int* rep;
	int n;
	int* rank;
};
#endif