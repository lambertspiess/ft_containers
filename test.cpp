#include <iostream>
#include <list>
using namespace std;
 
int main()
{
	// declaration of list container
	list<int> mylist{1};
	// using begin() to print list
	for (auto it = mylist.begin(); it != mylist.end(); ++it)
		{ cout << ' ' << *it; }
	cout << endl;

	mylist.pop_back();

	for (auto it = mylist.begin(); it != mylist.end(); ++it)
		{ cout << ' ' << *it; }
	cout << endl;


    return 0;
}
