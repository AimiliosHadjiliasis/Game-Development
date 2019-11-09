// ConsoleApplication3.cpp : Defines the entry point for the console application.
//	TODO: missing (5) check function
//

#include "stdafx.h"
#include <deque>
#include <iostream>
#include <list>
using namespace std;
using std::deque;


//(1) Create a coords Structure
struct coords
{
	int x;
	int y;
};

/*
	(4)	Construct a display function to output the value for x and y for all of the elements. You
		will need to use the begin() and end() methods for this operation. Simply:
		o Create an iterator
		o Point it at the front of the list
		o While not at the end of the list
		 Display the item the iterator is currently pointing at
		 Increment the iterator

*/
void display(deque <coords*> openList)
{
	deque <coords*> ::iterator p;
	p = openList.begin();

	while (p != openList.end())
	{	
		cout << "( " << (*p)->x <<" , "<<  + (*p)->y <<" ) " <<endl;
		p++;
	}
}
 /*
	(6)	Write a function to free up all of the memory on the openList. Use the delete command
		to free up the memory pointed to by each element on the list.
 */
void freeMemory(deque <coords*> openList, coords* tmp)
{
	deque <coords*> ::iterator p;
	p = openList.begin();

	while (p != openList.end())
	{
		delete (tmp);
		p++;
	}
}

int main()
{
	//(2) Declaire a deque of type coords pointer and call it 'OpenList'
	deque <coords*> openList;
	coords* tmp;
	/*
	  (3)Assign 10 new items to 'openList'. I would suggest that you use a for loop and assign
		the values ( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) to the x fields of the list and ( 0, 2, 4, 6, 8, 10,
		12, 14, 16, 18 ) to the y fields.
		 You will need to use a pointer to help you do this.
		 You will need to allocate memory to each new item you want to push onto the list.
		 The pointer can be used repeatedly- each pass around the loop you use the pointer
		to allocate a new block of memory, assign the x and y values into the new block of
		memory and lastly push the memory onto the list using push_back().
		 Note: you do not need to use the begin() or end() methods for this operation.
	*/
	for (int i = 0; i < 10; i++)
	{
		 tmp = new (coords);
		tmp->x = i;
		tmp->y = (i * 2);
		openList.push_back(tmp);
	}

	display(openList);
	freeMemory(openList, tmp);


	return 0;
}
