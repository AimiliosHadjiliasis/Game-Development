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

void display(deque <coords*> openList)
{
	deque <coords*> ::iterator p;
	p = openList.begin();

	while (p != openList.end())
	{
		cout << "( " << (*p)->x << " , " << +(*p)->y << " ) " << endl;
		p++;
	}
}

bool check(deque <coords*> openList, int num1, int num2)
{
	deque <coords*> ::iterator p;
	p = openList.begin();
	while (p != openList.end())
	{
		if (((*p)->x == num1) && ((*p)->y == num2))
		{
			return 1;
		}
		p++;
	}

	return 0;
}

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
	//(2) Declare a deque of type coords pointer and call it 'openList'
	deque <coords*> openList;

	/*
	(3)	Assign 10 new items to 'openList'. I would suggest that you use a for loop and assign
	the values ( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) to the x fields of the list and ( 0, 2, 4, 6, 8, 10,
	12,	14, 16, 18 ) to the y fields. Remember to allocate memory to each element of the list.
	*/
	coords* tmp;
	for (int i = 0; i <= 9; i++)
	{
		tmp = new (coords);
		tmp->x = i;
		tmp->y = (i * 2);
		openList.push_back(tmp);
	}

	//(4)  Declare a second list using deque of type coords pointer and call it 'closedList'
	deque <coords*> closeList;


	/*
	(5)  Transfer over the data from the first list to the second list. In other words, assign the
	pointers from the openList to the closedList. You will need an iterator to go through the
	openList. You do not need to allocate memory during this operation - you are merely
	making the pointers in the second list point at the same data as the pointers in the
	original list.
	*/
	deque <coords*> ::iterator p;
	p = openList.begin();

	while (p != openList.end())
	{	
		
		closeList.push_back((*p));
		p++;
	}

	//(6)	Output the value for x and y for all of the elements of the closedList.
	cout << "OpenList:" << endl;
	cout << "------------------" << endl;
	display(openList);

	cout << "\nCloseList:" << endl;
	cout << "------------------" << endl;
	display(closeList);
	
	//(5) 	Construct find function.
	cout << "Give x:" << endl;
	cin >> num1;
	"/n";
	cout << "Give y:" << endl;
	cin >> num2;
	"/n";

	if (check(openList, num1, num2))
	{
		cout << "Exist" << endl;
	}
	else
	{
		cout << "Not Exist" << endl;
	}

	freeMemory(closeList, tmp);
	cout << closeList.front()->x << " " << closeList.front()->y << endl;
    return 0;
}
