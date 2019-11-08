#include <iostream>
using namespace std;

struct Coords
{
	int x;
	int y;
};

int main()
{	

	Coords* ptr1 = new (Coords); // create pointer point at the coords structure
	ptr1->x = 3; //give value to x
	ptr1->y = 9; // give value to y

	Coords* ptr2 = new(Coords); // create a second pointer point at the coords structure
	ptr2 = ptr1; // assign the values of pointer 2 to pointer 1

	//Check that is working:
	cout << "Pointer 1 memory possition: " << ptr1 << endl;
	cout << "Value of x: " << ptr1->x << endl;
	cout << "Value of y: " << ptr1->y << endl;

	cout << "Pointer 2 memory possition: " << ptr2 << endl;
	cout << "Value of x: " << ptr2->x << endl;
	cout << "Value of y: " << ptr2->y << endl;

	// in order to delete all the variables we need to delete all
	// the pointer otherwise the 2nd pointer stays as it is with different values
	delete (ptr1);
	delete (ptr2);
	return 0;
}
