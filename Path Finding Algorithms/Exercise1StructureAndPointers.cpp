#include <iostream>
using namespace std;

struct Coords
{
	int x;
	int y;
};

int main()
{	
	Coords* ptr = new (Coords); //declares a pointer to an object of type coords
								// with the pointer name ptr
								// The new command allocates enough  memory to 
								// store the specified data type

	ptr->x = 4; //Give to x in the structure a value
	ptr->y = 7; //Give to y in the structure a value

	cout << "In memory: " << ptr << endl; //print the memory possition of the pointer
	cout << "Value of X: " << ptr->x << endl; //print the value of x
	cout << "Value of Y: " << ptr->y << endl; //print the value of y

	delete (ptr); //free the memory pointed at by the pointer

	return 0;
}
