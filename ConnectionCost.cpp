/*
` Class: CSC2710
 ` Description: This program takes a list of weighted edges and finds the edges 
 ` that connect all the devices (verticies) in the graph for the least cost using Kruskals algorithm.
 `
 ` to compile: g++ ConnectionCost.cpp -o CC.
 ` (make sure MinHeap.h, MinHeap.cpp, DisjointSets.h, and DisjointSets.cpp are in the same directory)
 ` 
 ` to execute the program using I/O redirection where output goes to
 ` standard output: CC <test.txt
 `
 ` if you want the output to go somewhere else, execute 
 ` this way: CC < test.txt > output.txt 
*/


#include<iostream>
#include<iomanip>
#include"MinHeap.cpp"
#include"DisjointSets.cpp"

using namespace std;

// data structure for containing information about an edge
struct Edge {
	int device1;
	int device2;
	int weight;
};

//function prototypes
void load(string*&, Edge*&, int&, int&);
int findInArray(string*&, string, int);
void appendIfNotInArray(string*&, string, int, int&);
void print(string*&, int);
void print(Edge*&, int);
bool kruskal(int, int, Edge*&, Edge*&);
void DESTROYALLTHEDATA(string*, Edge*, Edge*);
bool operator>(const Edge&, const Edge&);
bool operator<(const Edge&, const Edge&);
ostream& operator<<(ostream&, const Edge&);

//driver function
int main()
{
	int numCustomers;
	cin >> numCustomers;
	for (int i=1; i<=numCustomers; i++)
	{
		string* devices;
		Edge* edges, * solution;
		int numEdges, n;
		load(devices, edges, numEdges, n);
		cout << "Customer " << i << ":" << endl;
		if (kruskal(n, numEdges, edges, solution))
		{
			int minCost=0;
			for (int j=1; j<=n-1; j++)
			{
				cout << "(" << devices[(solution[j].device1)] << ", " 
				<< devices[(solution[j].device2)] << ") " << solution[j].weight << endl;
				minCost += solution[j].weight;
			} 
			cout << "Minimum Cost: " << minCost << endl;
		} else {
			cout << "No Solution";
		}
		cout << endl;
	} 
}

/* function load() - loads in list of edges and their respective weights from a file.
 ` ("vertex, vertex, weight" without the quotes.
 `
 ` precondition: devices is a reference pointer to a string, edges is a reference to a pointer to an Edge, 
 ` numEdges and n are both references to an int.
 `
 ` postcondition: devices is populated with all devices (verticies) in the graph, 
 ` edges is populated with all the edges in the graph, numEdges contains the number 
 ` of edges and n conntains the number of verticies.
*/
void load(string*& devices, Edge*& edges, int& numEdges, int& n)
{
	cin >> numEdges >> n;
	devices = new string[n+1];
	edges = new Edge[numEdges+1];
	
	int dCount=0, weight;
	string device1, device2;
	getline(cin, device1); //to get rid of empty line
	for (int i=1; i<=numEdges; i++){
		getline(cin, device1, ',');
		cin.get();
		getline(cin, device2, ',');
		cin >> weight;
		appendIfNotInArray(devices, device1, n, dCount);
		appendIfNotInArray(devices, device2, n, dCount);
		edges[i] = {findInArray(devices, device1, dCount), findInArray(devices, device2, dCount), weight};
		getline(cin, device1); //to get rid of empty line
	}
}
/* function findInArray() - searches for an element in a string array.
 ` 
 ` precondition: devices is a one-indexed populated string array, device is
 ` the element being searched for in devices, size is the number of elements in devices.
 ` 
 ` postcondition: returns the index of device if found, returns -1 if not found.
*/
int findInArray(string*& devices, string device, int size)
{
	for (int i=1; i<=size; i++)
	{
		if (devices[i] == device)
			return i;
	}
	return -1;
}

/* function appendIfNotInArray() - appends an element to the end of an array 
 ` if it is not already present in the array.
 `
 ` precondition: devices is a populated string array, device is a string that is to be searched for
 ` in devices, maxSize is the maximum number of elements that can be stored in the array and dCount 
 ` is the number of elements currently in the array.
 ` 
 ` postcondition: if device is not already in devices, device is appended to the end of devices and 
 ` 1 is added to dCount. otherwise, nothing changes.
*/
void appendIfNotInArray(string*& devices, string device, int maxSize, int& dCount)
{
	if (findInArray(devices, device, dCount) == -1)
	{
		dCount++;
		if (dCount <= maxSize)
			devices[dCount] = device;
	}
}

/* function print() - prints the contents of a string array.
 ` 
 ` precondition: devices is a populated string array and n is the number of 
 ` elements in the array.
 `
 ` postcondition: elements in devices printed to standard output.
*/
void print(string*& devices, int n)
{
	for (int i=1; i<=n; i++)
	{
		cout << i << ": " << devices[i] << endl;
	}
	cout << endl;
}

/*  function print() - prints the contents of an Edge array.
 `
 ` precondition: edges is a poopulated Edge array and n is the number of 
 ` elements in the array.
 `
 ` postcondition: information about elements in edges printed to standard output.
*/
void print(Edge*& edges, int n)
{
	for (int i=1; i<=n; i++)
	{
		cout << i << ": " << edges[i].device1 << " "<< edges[i].device2 << " " 
		<< edges[i].weight << endl;
	}
	cout << endl;
}

/* function Kruskals() - given a set of edges, finds the set of edges that connect the graph
 ` for the minimum cost.
 `
 ` precondition: n is the number of verticies in the graph, numEdges is the number of 
 ` edges in the graph, edges is an Edge array that contains data about each edge, 
 ` solution is a reference to a pointer to an Edge.
 `
 ` postcondition: if there is a solution, (i. e. if the graph is connected,) then
 ` returns true and solution is a dynamically allocated array of Edges that contains
 ` edges that compose the solution. otherwise, return false.
*/
bool kruskal(int n, int numEdges, Edge*& edges, Edge*& solution)
{
	int i, vCnt, d1, d2;
	Edge edge;
	MinHeap<Edge> sortedEdges(numEdges);
	//organize edges using MinHeap
	for (int i=1; i<=numEdges; i++)
		sortedEdges.HeapInsert(edges[i]);
	
	solution = new Edge[n+1];
	DisjointSets Dsets(n);
	
	i=0;
	vCnt=0;
	//process edges until solution is found or run out of edges
	while(i<numEdges && vCnt != n-1)
	{
		int Sd1, Sd2;
		//extract the edge with the smallest weight from the heap
		edge = sortedEdges.HeapExtractMin();
		d1 = edge.device1;
		d2 = edge.device2;
		if ((Sd1=Dsets.findSet(d1)) != (Sd2=Dsets.findSet(d2)))
		{
			//case where d1 and d2 are not already in the same set:
			vCnt++;
			Dsets.unionSet(Sd1, Sd2);
			solution[vCnt] = edge;
		}
		i++;
	}
	
	if (vCnt == n-1)
	{
		//case where all verticies are used in solution(solution found)
		return true;
	}
	//case where not all verticies are used in solution(no solution)
	return false;  
}


/* operator overload >() - provides a way to compare edges based on their weight.
 ` returns true if lhs.weight > rhs.weight, false otherwise.
*/
bool operator>(const Edge& lhs, const Edge& rhs)
{
	return lhs.weight>rhs.weight;
}

/* operator overload <() - provides a way to compare edges based on their weight.
 ` returns true if lhs.weight < rhs.weight, false otherwise.
*/
bool operator<(const Edge& lhs, const Edge& rhs)
{
	return lhs.weight<rhs.weight;
}
/* operator overload <<() - provides a simple way to print information about an edge. 
 ` prints the weight of an edge to standard output.
*/
ostream& operator<<(ostream& os, const Edge& e)
{
	os << e.weight;
}