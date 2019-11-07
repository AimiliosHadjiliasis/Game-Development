
#include "stdafx.h"
#include <deque>
#include <iostream>
using namespace std;
using std::deque;


struct coords
{
	int x;
	int y;
};



int main()
{
	//deque <coords*> openList;
	
	//Push items in the deque
	coords* tmp = new (coords);

	tmp->x = 4; // x co-ordinate of the start
	tmp->y = 4;  // y co-ordinate of the start
	
	deque <coords*> openList;

	openList.push_back(tmp);

	//Pull items in the deque
	//pop the first item in the list 

	coords* currentNode = openList.front();
	openList.pop_front();
	delete(tmp); //remover the element - not destroy -- Like this it points on the memory not the value

	cout << currentNode->x << endl;
	cout << currentNode->y << endl;

    return 0;
}
