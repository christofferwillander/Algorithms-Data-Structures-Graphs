/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#include "Kruskal.h"

void Kruskal::sortByWeight(int start, int end)
{
	if (start < end)
	{
		int pivotValue = this->partition(start, end);
		this->sortByWeight(start, pivotValue - 1);
		this->sortByWeight(pivotValue + 1, end);
	}
}

void Kruskal::swapElements(int index1, int index2)
{
	Arc temp = this->arcs[index1];
	this->arcs[index1] = this->arcs[index2];
	this->arcs[index2] = temp;
}

int Kruskal::partition(int start, int end)
{
	int pivotValue = this->arcs[start].getWeight();
	int pivotPosition = start;

	for (int i = start + 1; i <= end; i++)
	{
		if (this->arcs[i].getWeight() < pivotValue)
		{
			this->swapElements(i, pivotPosition + 1);
			this->swapElements(pivotPosition, pivotPosition + 1);
			pivotPosition++;
		}
	}

	return pivotPosition;
}

int Kruskal::findSet(std::vector<int>& subsetArr, int toFind) const
{
	if (subsetArr[toFind] == -1) // If the set is not in any union
	{
		return toFind;
	}

	return this->findSet(subsetArr, subsetArr[toFind]);
}

void Kruskal::unionOfSets(std::vector<int>& subsetArr, int set1, int set2) const
{
	int set1Location = this->findSet(subsetArr, set1);
	int set2Location = this->findSet(subsetArr, set2);
	subsetArr[set1Location] = set2Location;
}

Kruskal::Kruskal(List<Arc>& arcs, int nrOfVertices)
{
	this->nrOfVertices = nrOfVertices;
	this->nrOfArcs = arcs.length();

	this->arcs = new Arc[this->nrOfArcs];
	arcs.getAll(this->arcs, this->nrOfArcs);
}

Kruskal::~Kruskal()
{
	delete[] this->arcs;
}

void Kruskal::createMST(List<AdjacencyInfo> emptyAdjLists[], int &totalCost)
{
	totalCost = 0; // Initializing total cost variable to zero
	
	std::vector<int> subsets(this->nrOfVertices, -1);
	int counter = 0; // Used for indexation
	int nrOf = 0; // Used for keeping track of amount of arcs succesfully added
	int sourceSub = 0;
	int destinationSub = 0;

	this->sortByWeight(0, this->nrOfArcs - 1); // Calling Quicksort to sort Arc array by weight

	while (nrOf < this->nrOfVertices - 1)
	{
		sourceSub = this->findSet(subsets, this->arcs[counter].getSource());
		destinationSub = this->findSet(subsets, this->arcs[counter].getDestination());

		if (sourceSub != destinationSub) // If source & destination node are not in the same set (no cycle)
		{
			AdjacencyInfo temp1(this->arcs[counter].getDestination(), this->arcs[counter].getWeight());
			AdjacencyInfo temp2(this->arcs[counter].getSource(), this->arcs[counter].getWeight());

			totalCost += this->arcs[counter].getWeight();

			emptyAdjLists[this->arcs[counter].getSource()].insertAt(0, temp1);
			emptyAdjLists[this->arcs[counter++].getDestination()].insertAt(0, temp2);

			this->unionOfSets(subsets, sourceSub, destinationSub);
			nrOf++;
		}
		else
		{
			counter++;
		}
	}
}
