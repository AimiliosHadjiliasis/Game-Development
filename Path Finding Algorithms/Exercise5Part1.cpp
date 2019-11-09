// ConsoleApplication5.cpp : Defines the entry point for the console application.
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
int main()
{	
	//(2) Declaire a deque of type coords pointer and call it 'OpenList'
	deque <coords*> openList;

	//(3) Using a temporary pointer:
	//	o Allocate the memory for the first element only.
	//	o Assign a value of(5, 7) to the first element.
	coords* tmp;
	tmp = new(coords);
	tmp->x = 5;
	tmp->y = 7;

	//(4)	Using the temporary pointer push the data onto the list. 
	//		The first element of the list is pointing at the recently allocated data.
	openList.push_back(tmp);

	//(5) Using the same pointer push the data again onto the list. The second element of the
	//list is now pointing at same data as the first element of the list.
	openList.push_back(tmp);

	//(6) Output the value of x and y for the front of the list.
	cout <<" ( " << openList.front()->x << " , "<< openList.front()->y << " ) "<< endl;

	//(7) Output the value of x and y for the back of the list.
	cout << " ( " << openList.back()->x << " , " << openList.back()->y << " ) " << endl;

	//(8) Pop the data from the front of the list.
	//		-> pop the first element from the open list
	coords* temp = openList.front();
	openList.pop_front();

	//(11)	The first element on the list has been popped. Pop removes an element from the list.
	//		It does not destroy the element.However, the front function has been used to point the
	//		temp pointer at the data that was at the front of the list.

	//(10) Now delete the data being pointed to by temp.
	delete (temp);

	//(11)	If you now attempt to output the data supposedly pointed to by the front of the list you
	//		will see garbage.The reason for this is that the two pointers on the list pointed to the
	//		CO2301 - Games Development 1 Gareth Bellaby Lab Worksheet 8 Page 10
	//		same data and you have used delete via one of the pointers to free up the memory for
	//		that data

	//cout << " ( " << openList.front()->x << " , " << openList.front()->y << " ) " << endl;
	//cout << " ( " << openList.back()->x << " , " << openList.back()->y << " ) " << endl;
    return 0;
}
