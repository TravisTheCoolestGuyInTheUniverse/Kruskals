#include"DisjointSets.h"
//DisjointSets class implementation

/* constructor DisjointSets() - constructs DisjointSets object.
 ` precondition: n is the number of disjoint sets and must be greater than 0.
 ` 
 ` postcondition: private member int arrays rep and rank 
 ` are allocated memory for n ints, all elements in rep 
 ` are -1 (n disjoint sets), and all elements in rank are 0.
*/
DisjointSets::DisjointSets(int n)
{

		/*replaces
		if (n<1) {
			cerr << "Invalid size";
			exit(1);
		}*/			
	if (n<1)
	    throw ds_err(INVALID_SIZE);
	rep = new int[n];
	if (rep == NULL)
		throw ds_err(MEM_ERR);
	rank = new int[n];
	if (rank == NULL)
		throw ds_err(MEM_ERR);
	
	for (int i=0; i<n; i++)
	{
		rep[i] = -1;
		rank[i] = 0;
	}
}

/* class function findSet() - finds set containing a value.
 ` precondition: i is value whose set is being searched for.
 ` 
 ` postcondition: returns an int that is the representative of the set which
 ` contains i.
*/
int DisjointSets::findSet(int i)
{
	int r=i;
	while(rep[r] != -1)
	{
		r = rep[r];
	}
	return r;
}

/* class function unionSet() - unions two sets together if their representatives are not the same.
 ` precondition: u and v are ints that are representatives of two sets that may or may not be the same.
 ` 
 ` postcondition: if u and v are not the same, then sets u and v are combined into one set.
 ` rank is updated.
*/
void DisjointSets::unionSet(int u, int v)
{
	if (u != v)
	{
		if (rank[u] < rank[v])
		{
			rep[u] = v;
		} else if (rank[u] == rank[v]){
			rep[v] = u;
			rank[v]++;
		} else {
			rep[v] = u;
		}
	}
}

/* class destructor ~DisjointSets() - deallocates memory used by instances of object
 ` postcondition: memory allocated for private member arrays rep and rank are deallocated.
*/
DisjointSets::~DisjointSets()
{
	delete [] rep;
	delete [] rank;
	rep = NULL;
	rank = NULL;
}