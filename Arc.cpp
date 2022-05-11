/*
* Programmer: Christoffer Willander		Date completed: May 3rd, 2018
* Instructor: Johanna Krasemann		    Class: DV1490
*
* Graph program with MST-generating functionality
*
* Courtesy of: Christoffer Willander
*/

#include "Arc.h"

Arc::Arc(int source, int destination, int weight)
{
	this->source = source;
	this->destination = destination;
	this->weight = weight;
}

Arc::~Arc()
{

}

int Arc::getSource()
{
	return this->source;
}

int Arc::getDestination()
{
	return this->destination;
}

int Arc::getWeight()
{
	return this->weight;
}
