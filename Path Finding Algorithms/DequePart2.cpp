// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <deque>
#include <iostream>
using namespace std;
using std::deque;

void showDeque(deque <int> g)
{
	//function that prints the deque
	deque <int> ::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
		cout << '\t' << *it; //tab
	cout << '\n';			//new line
}

int main()
{
	deque <int> firstDeque;
	firstDeque.push_back(10);	//Add the first element
	firstDeque.push_front(20);	//Push in front(Begining) of the deque
	firstDeque.push_back(30);	//Push in back(end) of the deque
	firstDeque.push_front(15);	//Push in front(Begining) of the deque

	cout << "The deque (firstDeque) is : ";
	showDeque(firstDeque);		//Print the Deque

	cout << "\ngquiz.at(2) : " << firstDeque.at(2);		//Print What is pointed as the 2nd value in the deque
	cout << "\ngquiz.front() : " << firstDeque.front();	//Print the first item in the deque
	cout << "\ngquiz.back() : " << firstDeque.back();	//Print the last item in the deque

	cout << "\ngquiz.pop_front() : ";
	firstDeque.pop_front();				//Remove the 1st element in deque
	showDeque(firstDeque);

	cout << "\ngquiz.pop_back() : ";
	firstDeque.pop_back();				//Remove the last element in deque
	showDeque(firstDeque);
	
	return 0;
}
