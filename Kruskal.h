/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#ifndef KRUSKAL_H
#define KRUSKAL_H
#include <vector>
#include "AdjacencyInfo.h"
#include "Arc.h"
#include "List.h"

class Kruskal
{
// Private member variables for class Kruskal
private:
	Arc* arcs;
	int nrOfVertices;
	int nrOfArcs;

// Private member functions - help functions for Quicksort
private:
	void sortByWeight(int start, int end);
	void swapElements(int index1, int index2);
	int partition(int start, int end);

// Private member functions - help functions for handling subsets
private:
	int findSet(std::vector<int>& subsetArr, int toFind) const;
	void unionOfSets(std::vector<int>& subsetArr, int set1, int set2) const;

// Public member functions
public:
	Kruskal(List <Arc>& arcs, int nrOfVertices);
	virtual ~Kruskal();
	void createMST(List <AdjacencyInfo> emptyAdjLists[], int &totalCost);
};

#endif
