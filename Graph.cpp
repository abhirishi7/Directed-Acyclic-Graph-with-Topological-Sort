/*
 * Graph.cpp
 *
 *  Created on: 06-Nov-2017
 *      Author: Abhishek Tripathi
 *  Student ID: 801010002
 */

#include<iostream>
#include<list>
#include<stack>

using namespace std;

/*
 * Graph class contains the following
 * totalVertices : an int to store the total number of vertices in the graph.
 * adjList : adjacency list of vertices and edges between them.
 * cycleInt : an int which forms a cycle with previous vertices.
 * isCyclicUtil : utility function which gets called recursively to check if graph is DAG or not.
 * isCyclic : actual method that determines whether the graph is DAG or not.
 * addEdge : creates an edge connection between two vertices.
 * createAdjList : creates an adjacency list for the given graph from the adjacency matrix passed as an argument.
 */
class Graph {
private:
	int totalVertices;
	list<int> *adjList;
	int cycleInt;
	bool isCyclicUtil(int, bool*, stack<int>&, bool*, stack<int>&);
public:
	Graph(int v) {
		totalVertices = v;
		adjList = new list<int> [totalVertices]();
	}
	void addEdge(int, int);
	void createAdjList(int**);
	void isCyclic();
};

/*
 * Function to create an adjacency list from the adjacency matrix passed as an argument.
 * {parameter} : 2-d array of int representing adjacency matrix.
 * {return} : void value
 */
void Graph::createAdjList(int** adjMatrix) {
	int v = totalVertices;
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			if (adjMatrix[i][j] == 1) // a 1 indicates an edge between the two vertices.
				addEdge(i, j);
		}
	}
}

/*
 * Actual method that checks if the given graph is Directed Acyclic graph or not. If it is DAG, print it topological sorting of vertices.
 * If not, print the direct cycle.
 * {parameter} : void
 * {return} : void value
 */
void Graph::isCyclic() {

	stack<int> Stack;
	bool *recStack = new bool[totalVertices];
	stack<int> cycleStack;

	bool *visited = new bool[totalVertices];
	for (int i = 0; i < totalVertices; i++) {
		visited[i] = false; // initialize the visited array with all false.
		recStack[i] = false; // initialize the recStack array with all false.
	}

	for (int i = 0; i < totalVertices; i++) {
		if (visited[i] == false)
			if (isCyclicUtil(i, &visited[0], Stack, recStack, cycleStack)) {
				cout << "The graph has a cycle which is : "; // if the graph contains a cycle, print the cycle and exit.
				stack<int> printStack;
				while (cycleStack.top() != cycleInt) {
					printStack.push(cycleStack.top());
					cycleStack.pop();
				}
				printStack.push(cycleInt);
				while (!printStack.empty()) {
					cout << printStack.top() << " ";
					printStack.pop();
				}
				return;
			}
	}

	cout << "The graph is Directed Acyclic Graph." << endl;
	cout << "Topological sort is : "; // if the graph is DAG, print topological sorting of its veritces.
	while (!Stack.empty()) {
		cout << Stack.top() << " ";
		Stack.pop();
	}
}

/*
 * Utility function to determine if the graph contains a cycle or not.
 * {parameter} : an int source
 * an array of boolean to store the visited vertices.
 * stack<int> to store the topological sorting of vertices.
 * an array of boolean to store the vertices in recursive order
 * stack<int> to store the cycle if any present.
 * {return} : a bool value which is true if graph has cycle.False, otherwise.
 */
bool Graph::isCyclicUtil(int source, bool *visited, stack<int> &Stack,
		bool *recStack, stack<int> &cycleStack) {

	visited[source] = true; // mark the visited of source to true.
	recStack[source] = true; // mark the recStack of source to true.
	cycleStack.push(source); // push source on cycle stack.

	list<int>::iterator iter;
	for (iter = adjList[source].begin(); iter != adjList[source].end();
			iter++) {
		if (visited[*iter] == false) {
			if (isCyclicUtil(*iter, visited, Stack, recStack, cycleStack))
				return true;
		} else if (recStack[*iter]) {
			cycleInt = *iter;
			return true;
		}
	}

	recStack[source] = false; // undo the recStack value for source to false.
	Stack.push(source);
	cycleStack.pop();
	return false;
}

/*
 * Function to add an edge between two vertices given as parameters.
 * {parameter} : an int to indicate the source vertex.
 * an int to indicate the destination vertex.
 * {return} : void value.
 */
void Graph::addEdge(int source, int dest) {
	adjList[source].push_back(dest);
}

/*
 * Driver function that takes as an input the total number of vertices in the graph and the adjacency matrix for the graph from the user.
 * Calls the isCyclic method on Graph.
 * {parameter} : void .
 * {return} : an int value.
 */
int main() {
	int total = 0;
	cout << "Enter total number of vertices : " << endl;
	cin >> total;
	Graph g(total);
	cout << "Enter values for adjacency matrix row-wise : " << endl;
	int ** adjMatrix = new int*[total];
	for (int i = 0; i < total; i++) {
		int *row = new int[total];
		for (int j = 0; j < total; j++) {
			cin >> row[j];
		}
		adjMatrix[i] = &row[0];
	}
	g.createAdjList(adjMatrix);
	g.isCyclic();
	return 0;
}

