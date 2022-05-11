/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

void Graph::freeMemory()
{
	delete this->arcs;
	this->nrOfVertices = 0;
}

int Graph::findArc(int sourceVertex, int destinationVertex) const
{
	int foundAtIndex = -1;
	Arc* temp;

	if ((sourceVertex >= 0 && sourceVertex < this->nrOfVertices) && (destinationVertex >= 0 && destinationVertex < this->nrOfVertices))
	{
		temp = new Arc[this->arcs->length()];
		this->arcs->getAll(temp, this->arcs->length());

		for (int i = 0; i < this->arcs->length() && foundAtIndex == -1; i++)
		{
			if (this->graphType == DIRECTED && (temp[i].getDestination() == destinationVertex && temp[i].getSource() == sourceVertex))
			{
				foundAtIndex = i;
			}
			else if (this->graphType == UNDIRECTED && ((temp[i].getDestination() == destinationVertex && temp[i].getSource() == sourceVertex) || (temp[i].getDestination() == sourceVertex && temp[i].getSource() == destinationVertex)))
			{
				foundAtIndex = i;
			}
		}

		delete[] temp;
	}

	return foundAtIndex;
}

Graph::Graph(GraphType graphType, int nrOfVert)
{
	this->graphType = graphType;
	this->nrOfVertices = nrOfVert;
	this->arcs = new List<Arc>;
}

Graph::~Graph()
{
	this->freeMemory();
}

void Graph::reset(int nrOfVert, GraphType graphType)
{
	this->freeMemory();
	this->arcs = new List<Arc>;
	this->graphType = graphType;
	this->nrOfVertices = nrOfVert;
}

bool Graph::isDirected() const
{
	return this->graphType == DIRECTED;
}

bool Graph::addArc(int sourceVertex, int destinationVertex, int arcWeight)
{
	bool added = false;

	if ((sourceVertex >= 0 && sourceVertex < this->nrOfVertices) && (destinationVertex >= 0 && destinationVertex < this->nrOfVertices))
	{
		Arc temp(sourceVertex, destinationVertex, arcWeight);
		this->arcs->insertAt(0, temp);
		added = true;
	}

	return added;
}

bool Graph::hasArc(int sourceVertex, int destinationVertex) const
{
	return this->findArc(sourceVertex, destinationVertex) != -1;
}

bool Graph::removeArc(int sourceVertex, int destinationVertex, int arcWeight)
{
	bool removed = false;
	int arcIndex = this->findArc(sourceVertex, destinationVertex);

	if (arcIndex != -1 && this->arcs->getAt(arcIndex).getWeight() == arcWeight)
	{
		this->arcs->removeAt(arcIndex);
		removed = true;
	}

	return removed;
}

int Graph::getNrOfVertices() const
{
	return this->nrOfVertices;
}

int Graph::outDegreeOfVertex(int theVertex) const
{
	int outDegree = 0;

	Arc* temp = new Arc[this->arcs->length()];
	this->arcs->getAll(temp, this->arcs->length());

	for (int i = 0; i < this->arcs->length(); i++)
	{
		if (this->graphType == DIRECTED && temp[i].getSource() == theVertex)
		{
			outDegree++;
		}
		else if (this->graphType == UNDIRECTED && (temp[i].getSource() == theVertex || temp[i].getDestination() == theVertex))
		{
			outDegree++;
		}
	}

	return outDegree;
}

int Graph::inDegreeOfVertex(int theVertex) const
{
	int inDegree = 0;

	Arc* temp = new Arc[this->arcs->length()];
	this->arcs->getAll(temp, this->arcs->length());

	for (int i = 0; i < this->arcs->length(); i++)
	{
		if (this->graphType == DIRECTED && temp[i].getDestination() == theVertex)
		{
			inDegree++;
		}
		else if (this->graphType == UNDIRECTED && (temp[i].getSource() == theVertex || temp[i].getDestination() == theVertex))
		{
			inDegree++;
		}
	}

	return inDegree;
}

List<int> Graph::getAllVerticesAdjacentTo(int theVertex) const
{
	Arc* temp;
	List <int> adjacentVertices;

	if (this->graphType == DIRECTED && (theVertex >= 0 && theVertex < this->nrOfVertices))
	{
		temp = new Arc[this->arcs->length()];
		this->arcs->getAll(temp, this->arcs->length());
		
		for (int i = 0; i < this->arcs->length(); i++)
		{
			if (temp[i].getSource() == theVertex)
			{
				adjacentVertices.insertAt(0, temp[i].getDestination());
			}
		}

		delete[] temp;
	}

	return adjacentVertices;
}

void Graph::minSpanTree(List <AdjacencyInfo> minSpanTree[], int cap, int & totalCost) throw(...)
{
	if (this->graphType == DIRECTED)
	{
		throw "Cannot create minimum spanning tree for directed graph";
	}
	else if (cap < this->nrOfVertices)
	{
		throw "The array capacity is too small - please try again";
	}

	Kruskal kruskalAlgorithm(*this->arcs, this->nrOfVertices);
	kruskalAlgorithm.createMST(minSpanTree, totalCost);
}

void Graph::printGraph() const
{
	bool isFirst = true;

	cout << "-------------------- Graph Information --------------------" << endl << endl;

	if (this->graphType == DIRECTED)
	{
		cout << "Number of vertices: " << this->nrOfVertices << "\nGraph type: Directed" << endl << endl;
	}
	else
	{
		cout << "Number of vertices: " << this->nrOfVertices << "\nGraph type: Undirected" << endl << endl;
	}

	for (int i = 0; i < this->nrOfVertices; i++)
	{
		cout << "Vertex: " << i << " - Adjacent to: ";

		for (int j = 0; j < this->arcs->length(); j++)
		{
			if (this->hasArc(i, j) && isFirst)
			{
				cout << j;
				isFirst = false;
			}
			else if (this->hasArc(i, j) && j < this->arcs->length())
			{
				cout << ", " << j;
			}
		}

		isFirst = true;
		cout << endl;
	}

	cout << "-----------------------------------------------------------" << endl << endl;
}
