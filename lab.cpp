// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <deque>
#include "CNode.h"

using namespace std;
using std::deque;

enum childToThe
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
};
struct Node
{
	int x;
	int y;
};

const int length = 10;
CNode* map[length][length];

void exercise_1()
{
	//Declare a coords pointer called ptr.
// Use the new command to allocate memory and set your pointer to point at the new memory block
	Node* ptr = new(Node);

	/*
		Assign a value of 4 to the x coordinate of ptr and a value of 7 to the y coordinate of ptr.
		Remember that you are using a pointer so you have to use the -> syntax for the
		structure selection operator. You should be very used to this syntax. Remember that
		Intellisense will work with the structure selection operator and will show the structure
		fields (x and y) if your syntax is correct.
	*/
	ptr->x = 4;
	ptr->y = 7;

	//Use cout and ptr to output the x and y values from within the structure pointed to by ptr
	cout << "PTR: ( X:" << ptr->x << ", Y:" << ptr->y << ")" << endl;

	//It is necessary to relinquish memory back to the operating system. This is done using the
	//keyword delete.The following line of code frees the memory pointed at by the pointer :
	delete(ptr);

}

void exercise_2()
{
	//Declare a coords pointer called ptr1 and allocate memory for it.
	Node* ptr1 = new(Node);

	// Assign a value of (3, 9) to ptr1.
	ptr1->x = 3;
	ptr1->y = 9;

	//Declare a pointer called ptr2
	Node* ptr2 = new(Node);

	//Assign the location of ptr1 to ptr2
	ptr2 = ptr1;

	//Both pointers are now pointing at the same location. Test this by outputting the value
	//or x and y for first ptr1 and then ptr2
	cout << "PTR: ( X:" << ptr2->x << ", Y:" << ptr2->y << ")" << endl;

	//Use the delete command to free up the memory.Do you need to do this just once, or
	//do you have to do this once for each pointer ? Ask if you can't work this out yourself.
	delete (ptr1, ptr2);
}

void exercise_3()
{
	//Declare a deque of type coords pointer and call it 'openList'.
	deque<Node*> openList;

	//Declare a pointer of type coords called 'currentNode'.
	Node* currentNode;

	//Allocate the memory to 'currentNode' so that you can store some data.
	currentNode = new(Node);

	//Assign a value of ( 5, 7 ) to 'currentNode'
	currentNode->x = 5;
	currentNode->y = 7;

	//Push 'currentNode' on to the back of 'openList'
	openList.push_back(currentNode);

	//Output the value of x and y for the first item on 'openList'.
	cout << openList.front()->x << "," << openList.front()->y << endl;
	//Declare a pointer of type coords called 'tmpNode'
	//Pop the first item from 'openList' and assign it to 'tmpNode'.
	Node* tempNode = openList.front();
	openList.pop_front();

	//Output the value of x and y for 'tmpNode'.
	cout << "PTR: ( X:" << tempNode->x << ", Y:" << tempNode->y << ")" << endl;

	//Use the delete command to free up the memory pointed to by 'tmpNode'.
	delete(tempNode);
}

void display(deque <Node*> openList)
{
	deque <Node*> ::iterator p;
	p = openList.begin();

	while (p != openList.end())
	{
		cout << "( " << (*p)->x << " , " << +(*p)->y << " ) " << endl;
		p++;
	}
}

bool find(deque <Node*> list, Node* tmp)
{
	deque <Node*> ::iterator p = list.begin();

	int i = 0;
	while (p != list.end())
	{
		if (tmp->x == list[i]->x && tmp->y == list[i]->y)
			return true;

		p++;
		i++;
	}
	return false;
}

void freeMemory(deque<Node*> list)
{
	for (int i = 0; i < list.size(); ++i)
	{
		delete list[i];
	}

	list.clear();
}

void exercise_4()
{
	//Declare a deque of type coords pointers and call it 'openList'.
	deque<Node*> openList;

	/*
		Assign 10 new items to 'openList'. I would suggest that you use a for loop and assign
		the values ( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ) to the x fields of the list and ( 0, 2, 4, 6, 8, 10,
		12, 14, 16, 18 ) to the y fields.
		 You will need to use a pointer to help you do this.
		 You will need to allocate memory to each new item you want to push onto the list.
		 The pointer can be used repeatedly- each pass around the loop you use the pointer
		to allocate a new block of memory, assign the x and y values into the new block of
		memory and lastly push the memory onto the list using push_back().
		 Note: you do not need to use the begin() or end() methods for this operation.
	*/

	Node* tempNode;
	for (size_t i = 0; i <= 9; i++)
	{
		tempNode = new (Node);
		tempNode->x = i;
		tempNode->y = (i * 2);
		openList.push_back(tempNode);
	}

	/*
		Construct a display function to output the value for x and y for all of the elements. You
		will need to use the begin() and end() methods for this operation. Simply:
			o Create an iterator
			o Point it at the front of the list
			o While not at the end of the list
		 Display the item the iterator is currently pointing at
		 Increment the iterator
	*/

	display(openList);

	//Construct a find function to check whether a node exists on the openList. Use the
	//following x and y values to check that your function works : values(0, 0), (3, 6), (9,
	//18) and (5, 5).All of the values apart from(5, 5) should be found on the list.

	int x, y;

	Node* tmpFind = new(Node);
	cout << '\n';
	cout << "Check whether a node exist:" << endl;
	cout << "XCord: ";
	cin >> tmpFind->x;
	cout << "YCord: ";
	cin >> tmpFind->y;

	if (find(openList, tmpFind))
		cout << "Node Found!" << endl;
	else
		cout << "Node Not Found!" << endl;

	freeMemory(openList);
}

void exercise_5_1()
{
	//Declare a deque list of type coords pointer
	deque<Node*> openList;

	//Using a temporary pointer:
	//  -> Allocate the memory for the first element only.
	//	-> Assign a value of(5, 7) to the first element.
	Node* tmp = new (Node);
	tmp->x = 5;
	tmp->y = 7;

	// Using the temporary pointer push the data onto the list. The first element of the list is
	// pointing at the recently allocated data.
	openList.push_back(tmp);

	//Using the same pointer push the data again onto the list. The second element of the
	//list is now pointing at same data as the first element of the list.
	openList.push_back(tmp);

	//Output the value of x and y for the front of the list.
	cout << "X:" << openList.front()->x << "	" << "Y:" << openList.front()->y << endl;

	//Output the value of x and y for the back of the list.
	cout << "X:" << openList.back()->x << "	" << "Y:" << openList.back()->y << endl;

	//Pop the data from the front of the list.
	tmp = openList.front();
	openList.pop_front();
	//The first element on the list has been popped. Pop removes an element from the list.
	//It does not destroy the element.However, the front function has been used to point the
	//temp pointer at the data that was at the front of the list.
	//Now delete the data being pointed to by temp.
	delete(tmp);

	//If you now attempt to output the data supposedly pointed to by the front of the list you
	//will see garbage.The reason for this is that the two pointers on the list pointed to the
	//same data and you have used delete via one of the pointers to free up the memory for
	//that data.

	/*********************************************************************************/
	//Not Working since 2 pointers are pointing to the same data that we have delete
	cout << openList.front()->x << " " << openList.front()->y << endl;
	/*********************************************************************************/
}

void exercise_5_2()
{
	//Declare a deque of type coords pointer and call it 'openList'
	deque<Node*> openList;

	//Assign 10 new items to 'openList'. I would suggest that you use a for loop and assign
	//the values(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) to the x fields of the list and (0, 2, 4, 6, 8, 10,
	//12, 14, 16, 18) to the y fields.Remember to allocate memory to each element of the
	//list.
	for (size_t i = 0; i < 10; i++)
	{
		Node* tmp = new (Node);
		tmp->x = i;
		tmp->y = i * 2;
		openList.push_back(tmp);
	}


	//Declare a second list using deque of type coords pointer and call it 'closedList'.
	deque<Node*> closeList;

	while (openList.begin() != openList.end())
	{
		closeList.push_back(openList.front());
		openList.pop_front();
	}

	//Output the value for x and y for all of the elements of the closedList.
	display(closeList);

	//Use the delete command to free up the memory for the whole of closedList.
	freeMemory(closeList);

}

void initializeMap()
{
	for (size_t y = 0; y < length; y++)
	{
		for (size_t x = 0; x < length; x++)
		{
			map[y][x] = new CNode(x, y, NULL);
		}
	}
}

void printMap()
{
	for (size_t y = 0; y < length; y++)
	{
		for (size_t x = 0; x < length; x++)
		{
			cout << "(" << map[y][x]->getX() << "," << map[y][x]->getY() << ")";
		}
		cout << endl;
	}
}

bool NodeContainedOnList(CNode* n, deque<CNode*> list)
{
	deque<CNode*>::iterator it = list.begin();
	deque<CNode*>::iterator end = list.end();
	while (it != end)
	{
		if ((*it) == n)
		{
			return true;
		}
		it++;
	}
	return false;
}


CNode* generateChild(childToThe d, CNode* parent)
{
	int x = parent->getX();
	int y = parent->getY();
	switch (d)
	{
	case NORTH:
		if (y - 1 >= 0)
		{
			return map[y - 1][x];
		}
		break;
	case EAST:
		if (x + 1 < length)
		{
			return map[y][x + 1];
		}
		break;
	case SOUTH:
		if (y + 1 < length)
		{
			return map[y + 1][x];
		}
		break;
	case WEST:
		if (x - 1 >= 0)
		{
			return map[y][x - 1];
		}
		break;
	default:
		break;
	}

	return NULL;
}

void breadthFirstSearch(CNode* start, CNode* endNode)
{
	deque<CNode*> openList;
	deque<CNode*> closedList;
	deque<CNode*> path;

	openList.push_front(start);

	while (!openList.empty())
	{
		CNode* currenNode = openList.front();
		openList.pop_front();

		bool isDestination = currenNode->operator==(endNode);
		if (isDestination)
		{
			//set path
			while (currenNode != NULL)
			{
				path.push_front(currenNode);
				currenNode = currenNode->GetParent();
			}

			//print path
			deque<CNode*>::iterator it = path.begin();
			while (it != path.end())
			{
				cout << "(" << (*it)->getX() << ", " << (*it)->getY() << ") -> ";
				it++;
			}
			return;
		}

		//find n children and push back in open list
		cout << "Current Node: (" << currenNode->getX() << "," << currenNode->getY() << ")" << endl;
		for (int i = NORTH; i <= WEST; i++)
		{
			CNode* child = generateChild(static_cast<childToThe>(i), currenNode);
			if (child != NULL)
			{
				if (NodeContainedOnList(child, openList) || NodeContainedOnList(child, closedList))
					continue;

				child->SetParent(currenNode);
				openList.push_back(child);	//breadth first
				//openList.push_front(child);		//depth first
			}
		}
		closedList.push_front(currenNode);
		
	}
	cout << "No Path Found!" << endl;
}

void depthFirstSearch(CNode* start, CNode* endNode)
{
	deque<CNode*> openList;
	deque<CNode*> closedList;
	deque<CNode*> path;

	openList.push_front(start);

	while (!openList.empty())
	{
		CNode* currenNode = openList.front();
		openList.pop_front();

		bool isDestination = currenNode->operator==(endNode);
		if (isDestination)
		{
			//set path
			while (currenNode != NULL)
			{
				path.push_front(currenNode);
				currenNode = currenNode->GetParent();
			}

			//print path
			deque<CNode*>::iterator it = path.begin();
			while (it != path.end())
			{
				cout << "(" << (*it)->getX() << ", " << (*it)->getY() << ") -> ";
				it++;
			}
			return;
		}

		//find n children and push back in open list
		cout << "Current Node: (" << currenNode->getX() << "," << currenNode->getY() << ")" << endl;
		for (int i = NORTH; i <= WEST; i++)
		{
			CNode* child = generateChild(static_cast<childToThe>(i), currenNode);
			if (child != NULL)
			{
				if (NodeContainedOnList(child, openList) || NodeContainedOnList(child, closedList))
					continue;

				child->SetParent(currenNode);
				openList.push_front(child);		//depth first
			}
		}
		closedList.push_front(currenNode);

	}
	cout << "No Path Found!" << endl;
}

int main()
{
	//exercise_1();
	//exercise_2();
	//exercise_3();
	//exercise_4();
	//exercise_5_1();
	//exercise_5_2();

	initializeMap();
	printMap();

	int xStart, yStart, xEnd, yEnd;
	cout << "Starting x:";
	cin >> xStart;
	cout << "Starting y:";
	cin >> yStart;
	cout << "Starting x:";
	cin >> xEnd;
	cout << "Starting y:";
	cin >> yEnd;
	cout << endl;

	CNode* startNode = map[yStart][xStart];
	CNode* endNode = map[yEnd][xEnd];
	//Breadth First:
	//breadthFirstSearch( startNode, endNode);
	depthFirstSearch(startNode, endNode);


	return 0;
}
