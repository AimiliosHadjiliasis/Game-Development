//A small program that shows some readymade functions of STL Lists

#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

void showList(list<int> g)
{
	//Function that print the items of a list
	list <int> :: iterator it;
	for (it = g.begin(); it != g.end(); ++it)
	{
		cout << '\t' << *it; //Tab
	}
	cout << '\n';	//New line

}

int main()
{
	list <int> firstList, secondList;

	for (int i = 0; i < 10; i++)							//Use the push back method to fill the list with items
															//in this case 10 numbers that the next number is equal to
															//two times (*2) of the previus number
	{
		firstList.push_back(i * 2);							//push items in the back of the list
															//The next numebr goes in the end of the list
	}

	cout << "\nList 1 ( firstList ) is :";
	showList(firstList);									//Function call that Print the list
	cout << endl;

	cout << "\nfirstList.front() : " << firstList.front();  //Print the first item in the list
	cout << "\nfirstList.back() : " << firstList.back();	//Print the last item in the list

	cout << "\ngqlist1.pop_front() : ";
	firstList.pop_front();									//Remove the first number of the list
	showList(firstList);									

	cout << "\nfirstList_back() : ";
	firstList.pop_back();									//Remove the last number of the list
	showList(firstList);

	cout << "\ngqlist1.reverse() : ";
	firstList.reverse();									//Reverse the list
	showList(firstList);

	cout << "\ngqlist2.sort(): ";
	firstList.sort();										//Sort the list from Minmum to Maximum
	showList(firstList);

	return 0;
}
