#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct coords
{
	int x;
	int y;
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
		string s;
		while (getline(coordsFile, s))
		{
			cout << s << endl;
		}
		coordsFile.close();
	}

	//Open file [letter + Map.txt]
	//	->First number = rows of map
	//	->Second Number = columns of map
	//	->Rest: Map
	//		---->Numbers = Cost and Skin of Square
	ifstream mapFile;
	mapFile.open("mMap.txt");
	if (mapFile.fail())
	{
		cout << "Map Failed to load!" << endl;
	}
	else
	{
		string y;
		while (getline(mapFile, y))
		{
			cout << y << endl;
		}
	}

	//Choose Algorithm
	//	->A*
	//	->BFS
	//	->Custom A*

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
