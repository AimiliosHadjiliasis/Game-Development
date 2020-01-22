// algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <deque>
#include "CNode.h"

using namespace std;
using std::deque;
using std::list;

const int length = 10;
CNode* map[length][length];

//#define NORTH 0
//#define EAST 1
//#define SOUTH 2
//#define WEST 3

enum childToThe
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
};

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

void initalizeMapWithHeuristics()
{
	for (int y = 0; y < length; y++)
	{
		for (int x = 0; x < length; x++)
		{
			map[y][x] = new CNode(x, y, NULL);
			//Gonna change in file input
			map[y][x]->SetHeuristic(1); //at first set heuristic = 1 for all the Nodes
			map[y][x]->SetCost(1);		//at first set cost = to one for all the Nodes 
		}
	}
}

void makeWalls()
{
	int wall = 9;
	map[9][4]->SetCost(9);
	map[9][5]->SetCost(9);
	map[9][6]->SetCost(9);
	map[1][1]->SetCost(wall);
	map[1][2]->SetCost(wall);
	map[2][1]->SetCost(wall);
	map[2][2]->SetCost(wall);
	map[3][1]->SetCost(wall);
	map[3][2]->SetCost(wall);
	map[4][1]->SetCost(wall);
	map[4][2]->SetCost(wall);
	map[5][1]->SetCost(wall);
	map[5][2]->SetCost(wall);
	map[6][1]->SetCost(wall);
	map[6][2]->SetCost(wall);
	map[7][1]->SetCost(wall);
	map[7][2]->SetCost(wall);
}

void printMap()
{
	cout << "The map is :" << endl;
	for (size_t y = 0; y < length; y++)
	{
		for (size_t x = 0; x < length; x++)
		{
			cout << "(" << map[y][x]->getX() << "," << map[y][x]->getY() << ")";
		}
		cout << endl;
	}
}

void printMapWithCost()
{
	for (int y = 0; y < length; y++)
	{
		for (int x = 0; x < length; x++)
		{
			cout << "(" << map[x][y]->getX() << "," << map[x][y]->getY() << "," << map[x][y]->GetCost() << ")";
		}
		cout << endl;
	}
}

bool NodeExistOnDeque(CNode* child, deque<CNode*> dlist)
{
	deque<CNode*>::iterator it = dlist.begin();
	while (it != dlist.end())
	{
		if ((*it) == child)
		{
			return true;
		}
		it++;
	}
	return false;
}

bool NodeExistOnList(CNode* n, list<CNode*> nlist)
{
	list<CNode*>::iterator it = nlist.begin();
	while (it != nlist.end())
	{
		if ((*it) == n)
		{
			return true;
		}
		it++;
	}
	return false;
}

CNode* generateChild(childToThe direction, CNode* parent)
{
	/*
	   Generating child formulas:
	   -----------------------------
					N
					|  
		   W--[CurrentNode]---E
					|
					S
	   [Current Node] -> Get x/y to generate child
	   N -->  North       (y-1, x)
	   S -->  South       (y+1, x)
	   E -->  East        (y, x+1)
	   W -->  West        (y, x-1)
	 */

	int parentX = parent->getX();
	int parentY = parent->getY();
	switch (direction)
	{
	case NORTH:
		if (parentY - 1 >= 0)
			return map[parentY - 1][parentX];
		break;
	case EAST:
		if (parentX + 1 < length)
			return map[parentY][parentX + 1];
		break;
	case SOUTH:
		if (parentY + 1 < length)
			return map[parentY + 1][parentX];
		break;
	case WEST:
		if (parentX - 1 >= 0)
			return map[parentY][parentX - 1];
		
		break;
	default:
		break;
	}

	return NULL; //return Null if its impossible to generate a child
}

void breadthFirstSearchPrint(CNode* startNode, CNode* endNode)
{
	//1) Create OpenList, ClosedList and path
	deque<CNode*> openList;
	deque<CNode*> closedList;
	deque<CNode*> path;

	//2) Push the initial state (start) on to OpenList
	openList.push_front(startNode);

	//3)While open list is not empty
	while (!openList.empty())
	{
		//3.1) Create current Node and Push it to open List
		//(and then pop the 1st element from OpenList)
		CNode* currentNode = openList.front();
		openList.pop_front();

		//3.2) Check if the CurrentNode is in the destination (End Node)
		bool isDestination = currentNode->operator==(endNode);
		if (isDestination)
		{

			//3.2.1) Create the path:
			while (currentNode != NULL)
			{
				path.push_front(currentNode);
				currentNode = currentNode->GetParent();
			}

			//3.2.2) Print the path:
			deque<CNode*>::iterator p;
			p = path.begin();
			cout << "The path is: " << endl;
			while (p != path.end())
			{
				cout << "(" << (*p)->getX() << "," << (*p)->getY() << ") ";
				p++;
			}
			return; // get out of the function
		}

		// Print Current Node:
		cout << "Current Node: (" << currentNode->getX() << "," << currentNode->getY() << ")" << endl;

		//3.3) Generate Children of Current Node
		//int direction = NORTH;
		for (int i = NORTH; i <= WEST; i++)
		{
			//CNode* child = generateChild(direction, currentNode);
			CNode* child = generateChild(static_cast<childToThe>(i), currentNode);
			if (child != NULL)
			{
				if (NodeExistOnDeque(child, openList) || NodeExistOnDeque(child, closedList))
					continue;

				//3.3.1 Push the Child of Current Node to closed List
				child->SetParent(currentNode);
				openList.push_back(child);
			}
			//direction++;
		}

		//3.4) Push Current Node to Closed List
		closedList.push_front(currentNode);
	}
	cout << "No Path Found!" << endl;
}

void depthFirstSearchPrint(CNode* startNode, CNode* endNode)
{
	//1) Create OpenList, ClosedList and path
	deque<CNode*> openList;
	deque<CNode*> closedList;
	deque<CNode*> path;

	//2) Push the initial state (start) on to OpenList
	openList.push_front(startNode);

	//3)While open list is not empty
	while (!openList.empty())
	{
		//3.1) Create current Node and Push it to open List
		//(and then pop the 1st element from OpenList)
		CNode* currentNode = openList.front();
		openList.pop_front();

		//3.2) Check if the CurrentNode is in the destination (End Node)
		bool isDestination = currentNode->operator==(endNode);
		if (isDestination)
		{
			//3.2.1) Create the path:
			while (currentNode != NULL)
			{
				path.push_front(currentNode);
				currentNode = currentNode->GetParent();
			}

			//3.2.2) Print the path:
			deque<CNode*>::iterator p;
			p = path.begin();
			cout << endl;
			cout << "The path is: " << endl;
			while (p != path.end())
			{
				cout << "(" << (*p)->getX() << "," << (*p)->getY() << ")> ";
				p++;
			}
			return; // get out of the function
		}

		// Print Current Node:
		cout << "Current Node: (" << currentNode->getX() << "," << currentNode->getY() << ")" << endl;

		//3.3) Generate Children of Current Node
		for (int i = NORTH; i <= WEST; i++)
		{
			CNode* child = generateChild(static_cast<childToThe>(i), currentNode);
			if (child != NULL)
			{
				if (NodeExistOnDeque(child, openList) || NodeExistOnDeque(child, closedList))
					continue;

				//3.3.1 Push the Child of Current Node to closed List
				child->SetParent(currentNode);
				openList.push_front(child);
			}
		}

		//3.4) Push Current Node to Closed List
		closedList.push_front(currentNode);
	}
	cout << "No Path Found!" << endl;
}

bool compare(CNode* lhs, CNode* rhs)
{
	//Compare function -> the same as lab 
	if (lhs->GetCost() < rhs->GetCost())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void hillClimbingPrint(CNode* startNode, CNode* endNode)
{
	//1) Create OpenList, ClosedList and path
	list<CNode*> openList;
	list<CNode*> closedList;
	list<CNode*> path;

	//2) Push the initial state (start) on to OpenList
	openList.push_front(startNode);

	//3)While open list is not empty
	while (!openList.empty())
	{
		//3.1) Create current Node and Push it to open List
		//(and then pop the 1st element from OpenList)
		CNode* currentNode = openList.front();
		openList.pop_front();

		//3.2) Check if the CurrentNode is in the destination (End Node)
		bool isDestination = currentNode->operator==(endNode);
		if (isDestination)
		{
			//3.2.1) Create the path:
			while (currentNode != NULL)
			{
				path.push_front(currentNode);
				currentNode = currentNode->GetParent();
			}

			//3.2.2) Print the path:
			list<CNode*>::iterator p;
			p = path.begin();
			cout << endl;
			cout << "The path is: " << endl;
			while (p != path.end())
			{
				cout << "(" << (*p)->getX() << "," << (*p)->getY() << ")> ";
				p++;
			}
			return; // get out of the function
		}

		// Print Current Node:
		cout << "Current Node: (" << currentNode->getX() << "," << currentNode->getY() << ")" << endl;

		//3.3) Generate Children of Current Node
		for (int i = NORTH; i <= WEST; i++)
		{
			CNode* child = generateChild(static_cast<childToThe>(i), currentNode);
			if (child != NULL)
			{
				if (NodeExistOnList(child, openList) || NodeExistOnList(child, closedList))
					continue;

				//3.3.1 Push the Child of Current Node to closed List
				child->SetParent(currentNode);
				openList.push_front(child);
			}
		}

		//3.4) Push Current Node to Closed List
		openList.sort(compare);
		closedList.push_front(currentNode);
	}
	cout << "No Path Found!" << endl;
}

void calculateHeuristics(CNode* endNode)
{
	for (int y = 0; y < length; y++)
	{
		for (int x = 0; x < length; x++)
		{
			//Manhatan Distance Formula:			   					|y2-y1|			  +			|x2+x1|
			map[y][x]->SetHeuristic(map[y][x]->GetHeuristic() + abs(endNode->getY() - y) + abs(endNode->getX() - x));
		}
	}
}

void aStarPrint(CNode* startNode, CNode* endNode)
{
	//Implementation AStar
	list<CNode*> openList;
	list<CNode*> closedList;
	list<CNode*> path;

	openList.push_front(startNode);
	startNode->SetHeuristic(startNode->GetHeuristic());

	while (!openList.empty())
	{
		CNode* currentNode = openList.front();
		openList.pop_front();


		bool isDestination = currentNode == (endNode);
		if (isDestination)
		{
			//3.2.1) Create the path:
			while (currentNode != NULL)
			{
				path.push_front(currentNode);
				currentNode = currentNode->GetParent();
			}

			//3.2.2) Print the path:
			list<CNode*>::iterator p;
			p = path.begin();
			cout << "The path is: " << endl;
			while (p != path.end())
			{
				cout << "(" << (*p)->getX() << "," << (*p)->getY() << ")> ";
				p++;
			}
			return; // get out of the function
		}

		//3.3) Generate Children of Current Node
		for (int i = NORTH; i <= WEST; i++)
		{
			CNode* child = generateChild(static_cast<childToThe>(i), currentNode);
			if (child != NULL)
			{
				if (NodeExistOnList(child, openList) || NodeExistOnList(child, closedList))
					continue;

				//3.3.1 Push the Child of Current Node to closed List
				child->SetParent(currentNode);
				child->SetTotal(child->GetCost() + child->GetHeuristic());
				openList.push_back(child);
			}
		}
		openList.sort(compare);
		closedList.push_front(currentNode);

	}
	cout << "No Path Found!" << endl;
}

void breadthFS()
{
	initializeMap();
	printMap();
	CNode* startNode = map[9][9]; //y,x
	CNode* endNode = map[0][0]; //y,x
	breadthFirstSearchPrint(startNode, endNode);
}

void deapthFS()
{
	initializeMap();
	printMap();
	CNode* startNode = map[0][0]; //y,x
	CNode* endNode = map[5][6]; //y,x
	depthFirstSearchPrint(startNode, endNode);
}

void hillClimbing()
{
	initializeMap();
	printMap();
	CNode* startNode = map[0][0]; //y,x
	CNode* endNode = map[5][6]; //y,x
	hillClimbingPrint(startNode, endNode);
}

void AStar()
{
	initalizeMapWithHeuristics();
	makeWalls(); //add cost to each node
	printMapWithCost();
	CNode* startNode = map[3][0];
	CNode* endNode = map[9][9];
	calculateHeuristics(endNode);
	aStarPrint(startNode, endNode);
}

int main()
{
	//breadthFS();
	//deapthFS();
	//hillClimbing();
	AStar();
	return 0;
}

