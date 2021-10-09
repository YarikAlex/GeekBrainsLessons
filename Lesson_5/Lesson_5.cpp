#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

template<typename Iterator>
typename iterator_traits<Iterator>::value_type
PrintVector(Iterator begin, Iterator end)
{
	using value_type = typename iterator_traits<Iterator>::value_type;
	value_type s = value_type();
	set<value_type> vocabulary;
	for (Iterator it = begin; it != end; it++)
	{
		vocabulary.insert(*it);
	}
	for_each(vocabulary.begin(), vocabulary.end(), [](value_type i)
		{
			cout << i << " ";
		});
	cout << endl;
	return s;
}


int main()
{
	//Task 1.
	vector<string> words = { "first", "second", "third", "fifth", "second", "first"};
	PrintVector(words.begin(), words.end());

	//Task 2.
	string text;
	getline(cin, text);
	cout << "You entered: " << text << endl;
	string sentence = "";
	int symbol_count = 0;
	map <int, string> list;
	for_each(text.begin(), text.end(), [&](char it)
		{
			if (it != '.')
			{
				sentence += it;
				symbol_count++;
			}
			else
			{
				list.insert(make_pair(symbol_count, sentence));
				sentence = "";
				symbol_count = 0;
			}
		});
	for_each(list.begin(), list.end(), [](auto it)
		{
			cout << it.second << endl;
		});
}