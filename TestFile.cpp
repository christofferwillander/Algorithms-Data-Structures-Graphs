/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

void readFromFile(string fileName, Graph& graph) throw(...);
void printMSTGraph(List <AdjacencyInfo>[], int nrOf, int totalCost);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Graph testGraph1(DIRECTED, 4);
	//Graph testGraph2(UNDIRECTED, 4);

	//testGraph1.addArc(0, 1, 10);
	//testGraph1.addArc(1, 2, 20);
	//testGraph1.addArc(2, 3, 30);
	//testGraph1.addArc(3, 0, 40);
	//testGraph1.addArc(3, 1, 50);
	//testGraph1.addArc(4, 0, 60); // Will not be added (out of bounds)

	//testGraph1.printGraph();
	int totalCost;
	Graph* graph1;
	graph1 = new Graph();

	List<AdjacencyInfo>* adjacencyLists = new List<AdjacencyInfo>[10];
	readFromFile("graph1.txt", *graph1);
	graph1->printGraph();
	graph1->minSpanTree(adjacencyLists, 7, totalCost);
	printMSTGraph(adjacencyLists, 7, totalCost);
	graph1->inDegreeOfVertex(3);
	graph1->outDegreeOfVertex(3);

	graph1->inDegreeOfVertex(0);
	graph1->outDegreeOfVertex(0);

	graph1->getAllVerticesAdjacentTo(3);

	graph1->hasArc(0, 1);
	graph1->hasArc(1, 2);

	graph1->removeArc(0, 1, 30);

	delete graph1;

	delete[] adjacencyLists;
	getchar();
	return 0;
}

void readFromFile(string fileName, Graph& graph)
{
	int nrOfVertices = 0;
	int weight = 0;
	int source = -1;
	int destination = -1;

	string graphType = "";

	ifstream inFile;
	inFile.open(fileName);

	if (inFile.fail())
	{
		throw "The requested file was not found - please try again";
	}

	inFile >> nrOfVertices >> graphType;

	if (graphType == "D")
	{
		graph.reset(nrOfVertices, DIRECTED);
	}
	else if (graphType == "U")
	{
		graph.reset(nrOfVertices, UNDIRECTED);
	}

	while (!inFile.eof())
	{
		inFile >> source >> destination >> weight;
		graph.addArc(source, destination, weight);
	}

	inFile.close();
}

void printMSTGraph(List<AdjacencyInfo> MSTGraph[], int nrOf, int totalCost)
{
	AdjacencyInfo* temp;

	cout << "------------------ MST Graph Information ------------------" << endl << endl;
	cout << "Number of vertices: " << nrOf << "\nTotal cost: " << totalCost << endl << endl;

	for (int i = 0; i < nrOf; i++)
	{
		temp = new AdjacencyInfo[MSTGraph[i].length()];
		MSTGraph[i].getAll(temp, MSTGraph[i].length());
		cout << "Vertex: " << i << " - Adjacent to: ";

		for (int j = 0; j < MSTGraph[i].length(); j++)
		{
			if (j < MSTGraph[i].length() - 1)
			{
				cout << temp[j].getNeighbourVertex() << " (W: " << temp[j].getArcWeight() << "), ";
			}
			else
			{
				cout << temp[j].getNeighbourVertex() << " (W: " << temp[j].getArcWeight() << ")" << endl;
			}
		}

		if (MSTGraph[i].length() == 0)
		{
			cout << "None" << endl;
		}

		delete[] temp;
	}

	cout << "-----------------------------------------------------------" << endl << endl;
}
