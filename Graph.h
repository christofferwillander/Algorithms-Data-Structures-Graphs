/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#ifndef GRAPH_H
#define GRAPH_H
#include "Arc.h"
#include"AdjacencyInfo.h"
#include "List.h"
#include "Kruskal.h"

enum GraphType {DIRECTED, UNDIRECTED};

class Graph
{
private:
	void freeMemory();
	int findArc(int sourceVertex, int destinationVertex) const;

private:
	int nrOfVertices;
	GraphType graphType;
	List<Arc>* arcs;

public:
	Graph(GraphType graphType = DIRECTED, int nrOfVert = 0);
	Graph(const Graph& origin) = delete;
	Graph& operator = (const Graph& origin) = delete;
	virtual ~Graph();
	void reset(int nrOfVert, GraphType graphType);
	bool isDirected() const;
	bool addArc(int sourceVertex, int destinationVertex, int arcWeight);
	bool hasArc(int sourceVertex, int destinationVertex) const;
	bool removeArc(int sourceVertex, int destinationVertex, int arcWeight);
	int getNrOfVertices() const;
	int outDegreeOfVertex(int theVertex) const;
	int inDegreeOfVertex(int theVertex) const;
	List<int> getAllVerticesAdjacentTo(int theVertex) const;
	void minSpanTree(List<AdjacencyInfo> minSpanTree[], int cap, int &totalCost) throw(...);
	void printGraph() const;
};

#endif