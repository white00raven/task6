#include <iostream>
#include "Array2d.h"
using std::cout; 
void main()
{
	Array2d<int> test;
	int temp[] = { 1,2,3,4,5 };
	test.push_back(temp, 5);
	test.push_back(temp, 5);
	for (int i = 0; i < 10; i++)
	{
		test.push_back(0, i);

	}

	for (int l = 0; l < test.get_size(); l++)
	{
		Array2d<int>::iterator it = test.begin(l);
		for (; it != test.end(l); ++it)
		{

			cout << *it << " ";
		}
		cout << std::endl;
	}
	Array2d<int>::iterator it = test.begin(0);
	for (int i = 0; i < 5; i++)++it;
	test.erase(it);
	Array2d<int> test2(test);
	test2.push_front(0, 10);
	for (int l = 0; l < test.get_size(); l++)
	{
		Array2d<int>::iterator it1 = test.begin(l);
		for (; it1 != test.end(l); ++it1)
		{

			cout << *it1 << " ";
		}
		cout << std::endl;
	}
	for (int l = 0; l < test2.get_size(); l++)
	{
		Array2d<int>::iterator it1 = test2.begin(l);
		for (; it1 != test2.end(l); ++it1)
		{

			cout << *it1 << " ";
		}
		cout << std::endl;
	}
	Array2d<int> test3(std::move(test));
	for (int l = 0; l < test3.get_size(); l++)
	{
		Array2d<int>::iterator it1 = test3.begin(l);
		for (; it1 != test3.end(l); ++it1)
		{

			cout << *it1 << " ";
		}
		cout << std::endl;
	}
	test3.swap(test2);
	for (int l = 0; l < test2.get_size(); l++)
	{
		Array2d<int>::iterator it1 = test2.begin(l);
		for (; it1 != test2.end(l); ++it1)
		{

			cout << *it1 << " ";
		}
		cout << std::endl;
	}
	for (int l = 0; l < test3.get_size(); l++)
	{
		Array2d<int>::iterator it1 = test3.begin(l);
		for (; it1 != test3.end(l); ++it1)
		{

			cout << *it1 << " ";
		}
		cout << std::endl;
	}
	system("pause");
}