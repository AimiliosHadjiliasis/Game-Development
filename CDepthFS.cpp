#include "CDepthFS.h"
#include "CTile.h"
#include "Utility.h"
#include <list>


CDepthFS::CDepthFS(deque<deque<CTile*>> grid)
{
	this->map = grid;
}
bool CDepthFS::Search(CTile* startNode, CTile* endNode)
{
	if (!openList.empty())
	{
		CTile* currentNode = openList.front();
		openList.pop_front();

		bool isDestination = currentNode == (endNode);
		if (isDestination)
		{
			//3.2.1) Create the path:
			while (currentNode != NULL)
			{
				path.push_front(currentNode);
				currentNode->SetPath();
				currentNode = currentNode->GetParent();
			}

			printT(path);
			return true; // get out of the function
		}

		//3.3) Generate Children of Current Node
		for (int i = NORTH; i <= WEST; i++)
		{
			CTile* child = GenerateChild(static_cast<EChildToThe>(i), currentNode);
			if (child != NULL)
			{
				bool isInOpen = NodeExistOnList(child, openList);
				bool isInClosed = NodeExistOnList(child, closedList);
				int newTotalCost = currentNode->GetTotalCost() + child->GetCost();
				if ((isInOpen || isInClosed) && newTotalCost >= child->GetTotalCost())
					continue;

				//3.3.1 Push the Child of Current Node to closed List
				child->SetParent(currentNode);
				openList.push_front(child);
				child->SetOpenList();

			}
		}
		closedList.push_front(currentNode);
		currentNode->SetClosedList();
	}
	else
	{
		cout << "No Path Found!" << endl;
		return true; //to change state in the game loop
	}
	return false;
}