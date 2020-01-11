#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
using namespace std;
using std::deque;

struct coords
{
	int x;
	int y;
	int value;
};

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
		int sizeX, sizeY;
		//Read and store integers: https://stackoverflow.com/questions/20724752/reading-and-storing-integers-in-a-file
		mapFile >> sizeX >> sizeY;
		const int XSize = sizeX;
		const int YSize = sizeY;
		cout << "Size of X Coordinates: " << sizeX << endl;
		cout << "Size of Y Coordinates: " << sizeY << endl;
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
		


		coords*** grid;
		coords* tmp;
		int iterator = 0;
		cout << "Initialize Map: " << endl;
		grid = new coords** [sizeX];
		for (int c = sizeY - 1; c >= 0; c--) {
			grid[c] = new coords*[sizeY];
			for (int k = 0; k < sizeX; k++)
			{
				tmp = new(coords);
				tmp->x = c;
				tmp->y = k;
				tmp->value = values[iterator];
				grid[c][k] = tmp;
				cout << "(" << grid[c][k]->x << "," << grid[c][k]->y << ","<< grid[c][k]->value<<  ") ";
				iterator++;
			}
			cout << '\n';

		}

		


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
	
	deque <coords*> openList;
	deque <coords*> closeList;




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
