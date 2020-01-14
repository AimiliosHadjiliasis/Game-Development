#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
using namespace std;
using std::deque;
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

struct coords
{
	int x;
	int y;
	int value;
};


//coords*** g_grid;
int g_sizeX, g_sizeY;
vector<vector<coords>> grid(g_sizeY);


coords* bfs_generateChild(coords parent) 
{
	coords arrayOfChildren[4]; //epistrefi 4 mora NESW

	//coords temp = new(coords); // prepi na gini smart gia na min mas pidi3i tin mnimi
	
	int direction = NORTH;

	while (direction <= WEST)
	{
		switch (direction)
		{
		case NORTH:
			if (parent.y==g_sizeY)
			{
				//temp.y = -1; // fake Child
				//temp.x = -1;
				arrayOfChildren[0].x = -1;
				arrayOfChildren[0].y = -1;

				direction++;
				break;
			}
			else
			{
				//temp->y = parent->y + 1; //Real Child
				//temp->x = parent->x;
				arrayOfChildren[0].y = parent.y + 1;
				arrayOfChildren[0].x = parent.x;

				direction++;
				break;
			}

		case EAST:
			if (parent.x==g_sizeX)
			{
				//temp->x =-1;	//fake child
				//temp->y = -1;
				arrayOfChildren[1].x = -1;
				arrayOfChildren[1].y = -1;
				direction++;
				break;
			}
			else
			{
				//temp->x = parent->x + 1; //real child
				//temp->y = parent->y;
				arrayOfChildren[1].x = parent.x + 1;
				arrayOfChildren[1].y = parent.y;
				direction++;
				break;
			}

		case SOUTH:
			if (parent.y==0)
			{
				//temp->y =-1; //fakechild
				//temp->x = -1;
				arrayOfChildren[2].x = -1;
				arrayOfChildren[2].y = -1;
				direction++;
				break;
			}
			else
			{
				//temp->y = parent->y - 1; //real child
				//temp->x = parent->x;
				arrayOfChildren[2].y = parent.y- 1;;
				arrayOfChildren[2].x = parent.x;
				direction++;
				break;
			}

		case WEST:
			if (parent.x==0)
			{
				//temp->x = - 1;  //fake child
				//temp->y = -1;
				arrayOfChildren[3].x = -1;
				arrayOfChildren[3].y = -1;
				direction++;
				break;
			}
			else
			{
				//temp->x = parent->x - 1; //real child
				//temp->y = parent->y;
				arrayOfChildren[3].x = parent.x - 1;;
				arrayOfChildren[3].y = parent.y;
				direction++;
				break;
			}

		default:
			cout << "Something went really wrong you fakass!" << endl;
			break;
		}
	}

	return arrayOfChildren;
}

bool bfs_checkOpenList(deque<coords> oList, coords child)
{
	for (int count = 0; count < oList.size(); count++)
	{
		if (oList[count].x == child.x && oList[count].y == child.y)
		{
			return false;
		}
		 
	}
	return true;
}

int main()
{


	//Read first letter
//	char letter;
//	cout << "First Letter: ";
//	cin >> letter;

	

//Read first letter
	char letter = 'd';
	cout << "First Letter: ";
	cin >> letter;
	string st;
	st += letter;
	int xStartPoint, yStartPoint, xEndPoint, yEndPoint;
	//Open file [letter+ Coords.txt]
	//	->FirstLine = start Node
	//	->SecondLine = end Node
	ifstream coordsFile;
	coordsFile.open(st + "Coords.txt");
	if (coordsFile.fail())
	{
		cout << "Start point/ End Point Failed to Load!" << endl;
	}
	else
	{
		coordsFile >> xStartPoint >> yStartPoint >> xEndPoint >> yEndPoint;

		cout << xStartPoint << " " << yStartPoint << " " << xEndPoint << " " << yEndPoint << endl;
		coordsFile.close();
	}

	//Open file [letter + Map.txt]
	//	->First number = rows of map
	//	->Second Number = columns of map
	//	->Rest: Map
	//		---->Numbers = Cost and Skin of Square
	ifstream mapFile;
	mapFile.open(st + "Map.txt");
	if (mapFile.fail())
	{
		cout << "Map Failed to load!" << endl;
	}
	else
	{
		string y;
		int sN;
		char ss;
		string skoupidia;
		int number;
		char singleCharacter;
		
		//Read and store integers: https://stackoverflow.com/questions/20724752/reading-and-storing-integers-in-a-file
		mapFile >> g_sizeX >> g_sizeY;
		//const int XSize = g_sizeX;
		//const int YSize = g_sizeY;
		cout << "Size of X Coordinates: " << g_sizeX << endl;
		cout << "Size of Y Coordinates: " << g_sizeY << endl;
		cout << '\n';
		vector<int> values;


		while (getline(mapFile, y))
		{
			for (int i = 0; i < y.size(); i++)
			{
				ss = y.at(i);
				sN = '0' + ss - 96; //Ean prosthesis ton xaraktira 0 me kapio charaktira metatrepi ton xaraktira se ena arithmo ston pinka ascii	
				values.push_back(sN);

			}
		}
		
		//1* -> POINT SE 1 KOUTAKI ALOU (1D PINAKAS)
		//2* -> PINAKAS ME POINTERS (2D PINAKAS)
		//3* -> 2D PINAKAS ME POINTERS (3D PINAKAS)
		//vector <coords> temp;
		//coords tmp;
		int iterator = 0;
		for (int i = 0; i < g_sizeY; i++)
		{
			grid[i] = vector<coords>(g_sizeX);
				for (int j = 0; j < g_sizeX; j++)
				{
					/*tmp.x = j;
					tmp.y = i;
					tmp.value = values[iterator];
					temp.push_back(tmp);*/
					grid[i][j].x = j;
					grid[i][j].y = i;
					cout << "(" << grid[i][j].x << "," << grid[i][j].y << "," << grid[i][j].value << ") ";
					iterator++;
				}
			cout << '\n';
		}

	/*	coords* tmp;
		int iterator = 0;
		cout << "Initialize Map: " << endl;
		g_grid = new coords** [g_sizeY];
		for (int c = g_sizeY - 1; c >= 0; c--)
		{
			g_grid[c] = new coords*[g_sizeX];
			for (int k = 0; k < g_sizeX; k++) 
			{
				tmp = new(coords);
				tmp->x = k;
				tmp->y = c;
				tmp->value = values[iterator];
				g_grid[c][k] = tmp;
				cout << "(" << g_grid[c][k]->x << "," << g_grid[c][k]->y << ","<< g_grid[c][k]->value<<  ") ";
				iterator++;
			}
			cout << '\n';
		}*/
	}



	////Choose Algorithm
	////	->A*
	////	->BFS
	////	->Custom A*
	//cout << "Select Algorithm :" << endl;
	//cout << "Press 1:" << endl;
	//cout << "Press 2:" << endl;
	//cout << "Press 3: Custom" << endl;
	//
	//BFS
	
	deque <coords> openList;
	deque <coords> closeList;


	//Push 1st Item
	coords temporaryNode;//= new (coords);
	temporaryNode.x = xStartPoint;
	temporaryNode.x = yStartPoint; //missing value
	openList.push_back(temporaryNode);

	coords* children; //Double pointer-> so we dont have to make for loop for children[i]

	while (!openList.empty())
	{
		temporaryNode = openList[0];
		openList.pop_front();

		//n==ndestination
		if (temporaryNode.x == xEndPoint && temporaryNode.y == yEndPoint )
		{
			//Print the path();
			cout << "Found Path" << endl;
			break;
		}
		//generate child
		children = bfs_generateChild(temporaryNode);


		//Check an to value == 0 
		// if so -> dont push in Open List
		//else push in open list

		//chekari gia kathe pedi (max 4 mora exi kathe parent(node))
		for (int counter = 0; counter < 4; counter++)
		{	

			//Check an ine stin open list
			if (bfs_checkOpenList(openList, children[counter]))
			{	

				//an den ine checkare an ine tixos 
				
				if (grid[children[counter].x][children[counter].y].value !=0)
				{
					cout << "dame" << endl;

					//an den ine sirta stin open list
					openList.push_back(children[counter]);
				}
			}
		}
		
		closeList.push_back(temporaryNode);
	}

	for (int g = 0; g < closeList.size(); g++)
	{
		cout << "(" << closeList[g].x << "," << closeList[g].y << ")" << endl;
	}

	cout << "Done!" << endl;
	//Search for Path
	//	-> Print Current Node
	//	-> X / Y of Open List
	//	-> X / Y of Closed List
	//	-> if (path) Found 
	//			1. Show the Path on cmd
	//			2. Print the path on output.txt
	//	-> else 
	//			Print path not found


	return 0;
}
