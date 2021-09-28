#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

#include "Timer.h"

using namespace std;

template <typename T>
void Swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
void SortPointers(vector<T>& pointers)
{
	sort(pointers.begin(), pointers.end(), [pointers](T first, T second)
		{
			return *first < *second;
		});
}

template <typename T>
void PrintVector(vector<T>& pointers)
{
	for (auto it : pointers)
	{
		cout << *it << " ";
	}
	cout << endl;
}

size_t CountVowels_Count_if_For(string& str)
{
	string vowels = "AaEeYyUuIiOo";
	size_t count = 0;
	count_if(str.begin(), str.end(), [&](char s)
		{
			for (auto it : vowels)
			{
				if (s == it)
				{
					count++;
					return true;
				}
			}
		});
	return count;
}

size_t CountVowels_Count_if_Find(string& str)
{
	string vowels = "AaEeYyUuIiOo";
	return count_if(str.begin(), str.end(), [&vowels](char s)
		{
			return find(vowels.begin(), vowels.end(), s) != vowels.end();
		});
}

size_t CountVowels_For_Find(string& str)
{
	size_t count = 0;
	string vowels = "AaEeYyUuIiOo";
	for (auto it : str)
	{
		if (find(vowels.begin(), vowels.end(), it) != vowels.end())
			count++;
	}
	return count;
}

size_t CountVowels_For_For(string& str)
{
	size_t count = 0;
	string vowels = "AaEeYyUuIiOo";
	for (auto it : str)
	{
		for (auto iter : vowels)
		{
			if (iter == it)
				count++;
		}
	}
	return count;
}

int main()
{
	int* first = new int(5);
	int* second = new int(10);
	cout << "Pointer first = " << *first << endl;
	cout << "Pointer second = " << *second << endl;
	Swap(first, second);
	cout << "Pointer first = " << *first << endl;
	cout << "Pointer second = " << *second << endl;
	delete first, second;

	vector<int*> myvector;
	int Size = 10;
	for (int i = 0; i < Size; ++i)
	{
		int* tmp = new int(rand()%100);
		myvector.push_back(tmp);
	}
	PrintVector(myvector);
	SortPointers(myvector);
	PrintVector(myvector);

	size_t count_vowels = 0;
	string str;
	Timer timer;
	ifstream Book;
	string path = "WarAndPeace.txt";
	Book.open(path);
	if (!Book.is_open() and !Book.good())
	{
		cout << "File is not open!" << endl;
	}
	else
	{
		timer.start("CountVowels_Count_if_For");
		while (!Book.eof())
		{
			str = "";
			getline(Book, str);
			count_vowels += CountVowels_Count_if_For(str);
		}
		timer.print();
	}
	Book.close();
	cout << "The Count_if_For method has counted " << count_vowels << " vowels in this file." << endl << endl;;

	count_vowels = 0;
	Book.open(path);
	if (!Book.is_open() and !Book.good())
	{
		cout << "File is not open!" << endl;
	}
	else
	{
		timer.start("CountVowels_Count_if_Find");
		while (!Book.eof())
		{
			str = "";
			getline(Book, str);
			count_vowels += CountVowels_Count_if_Find(str);
		}
		timer.print();
	}
	Book.close();
	cout << "The Count_if_Find method has counted " << count_vowels << " vowels in this file." << endl << endl;

	count_vowels = 0;
	Book.open(path);
	if (!Book.is_open() and !Book.good())
	{
		cout << "File is not open!" << endl;
	}
	else
	{
		timer.start("CountVowels_For_Find");
		while (!Book.eof())
		{
			str = "";
			getline(Book, str);
			count_vowels += CountVowels_For_Find(str);
		}
		timer.print();
	}
	Book.close();
	cout << "The For_Find method has counted " << count_vowels << " vowels in this file." << endl << endl;

	count_vowels = 0;
	Book.open(path);
	if (!Book.is_open() and !Book.good())
	{
		cout << "File is not open!" << endl;
	}
	else
	{
		timer.start("CountVowels_For_For");
		while (!Book.eof())
		{
			str = "";
			getline(Book, str);
			count_vowels += CountVowels_For_For(str);
		}
		timer.print();
	}
	Book.close();
	cout << "The For_For method has counted " << count_vowels << " vowels in this file." << endl << endl;

	return 0;
}