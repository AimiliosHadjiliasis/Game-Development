// How to use deques
// Create open List 
// Push data in the end of the openList
// Pop data from the front of the list
// Save the data in a temporary Node
// Use that node


#include "stdafx.h"
#include <iostream>
#include <deque>
using namespace std;
using std::deque;

struct coords
{
	int x;
	int y;

};

int main()
{	
	deque <coords*> openList; //Create the open list
	coords* currentNode; // Declaire pointer of type coords  called currentNode
	currentNode = new (coords); //Allocate the memory to currentNode so that you can store some data
	
	currentNode->x = 5; //Assign a value of(5, 7) to 'currentNode'.
	currentNode->y = 7;

	openList.push_back(currentNode); //Push 'currentNode' on the back of the open List

	//Output the value of x and y for the first item on 'Open List'
	cout << currentNode->x << endl;
	cout << currentNode->y << endl;

	coords* tmpNode; // Declaire a pointer of type coords called tmpNode

	//Pop the first item from 'openList' and assign it to 'tmpNode'
	tmpNode = openList.front();
	openList.pop_front();

	cout << tmpNode->x << endl;
	cout << tmpNode->y << endl;

	delete(tmpNode);


    return 0;
}

