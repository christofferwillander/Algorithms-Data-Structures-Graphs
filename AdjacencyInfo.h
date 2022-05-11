/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#ifndef ADJECENCYINFO_H
#define ADJECENCYINFO_H

class AdjacencyInfo
{
private:
	int neighbourVertex;
	int arcWeight;
public:
	AdjacencyInfo(int neighbourVertex = -1, int arcWeight = 0);
	virtual ~AdjacencyInfo();
	int getNeighbourVertex() const;
	void setNeighbourVertex(int neighbourVertex);
	int getArcWeight() const;
	void setArcWeight(int arcWeight);
	bool operator==(const AdjacencyInfo& other) const;
	bool operator!=(const AdjacencyInfo& other) const;

};

#endif
