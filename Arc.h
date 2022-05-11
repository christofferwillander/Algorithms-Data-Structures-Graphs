/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#ifndef ARC_H
#define ARC_H

class Arc
{
private:
	int source, destination, weight;

public:
	Arc(int source = -1, int destination = -1, int weight = -1);
	virtual ~Arc();

	int getSource();
	int getDestination();
	int getWeight();
};

#endif