// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <deque>
#include <iostream>
using namespace std;
using std::deque;

//(1) Create a coords Structure
struct coords
{	
	int x;
	int y;
};

int main()
{	
	//(2) Declaire a deque of type coords pointer and call it 'OpenList'
	deque <coords*> openList;
	
	//(3) Declaire a pointer of type coords called 'currentNode'
	coords* currentNode;

	//(4)Allocate the memory to currentNode so that you can store some data
	currentNode = new (coords);

	//(5) Assign a value of (5,7) to 'currentNode'
	currentNode->x = 5;
	currentNode->y = 7;

	//(6) Push 'currentNode' on the back of the open List
	openList.push_back(currentNode);

	//(7) Output the value of x and y for the first item on 'Open List'
	cout << currentNode->x << endl;
	cout << currentNode->y << endl;

	//(8) Declaire a pointer of type  coords called 'tmpNode'
	coords* tmpNode;

	//(9) Pop the first item from 'openList' and assign it to ''tmpNode'
	tmpNode = openList.front();
	openList.pop_front();

	//(10) Output the value of x and y for 'tmpNode'
	cout << tmpNode->x << endl;
	cout << tmpNode->y << endl;

	//(11) Free the memory pointed to by 'tmpNode'
	delete (tmpNode);

	return 0;
}
