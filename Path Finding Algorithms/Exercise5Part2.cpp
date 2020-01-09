#include <iostream>
#include <deque>

using namespace std;
using std::deque;


struct coords {
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

bool findFunction(deque <coords*> openList, coords* tmp)
{
	deque <coords*> ::iterator p;
	p = openList.begin();

	int i = 0;
	while (p != openList.end())
	{
		if (tmp->x == openList[i]->x && tmp->y == openList[i]->y)
		{
			return true;
		}
		p++;
		i++;
	}
	return false;
}


int main()
{
	deque<coords*> openList;
	
	coords* tmp;
	for (int i = 0; i <= 9; i++)
	{
		tmp = new (coords);
		tmp->x = i;
		tmp->y = (i * 2);
		openList.push_back(tmp);
	}


	display(openList);
	int x, y;

	coords* tmpFind = new(coords);
	cout << '\n';
	cout << "Check whether a node exist:" << endl;
	cout << "XCord: ";
	cin >> tmpFind->x;
	cout << "YCord: ";
	cin >> tmpFind->y;
	

	if (findFunction(openList, tmpFind))
	{
		cout << "Node Found!" << endl;
	}
	else
	{
		cout << "Node Not Found!" << endl;
	}

	freeMemory(openList, tmp);

	return 0;
}
