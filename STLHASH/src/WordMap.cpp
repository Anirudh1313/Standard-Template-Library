#include <iostream>
#include <map>
#include <string>
#include "WordMap.h"

using namespace std;
using namespace std::chrono;

WordMap::WordMap()
{
}

WordMap::~WordMap()
{
}

map<string, Word>& WordMap::get_data() { return data; }

int WordMap::get_count(const string text) const
{
	int count = data.find(text)->second.get_count();
	return count;
}

void WordMap::insert(const string text)
{
	steady_clock::time_point mt1 = steady_clock::now();

	map<string, Word>::iterator it = data.find(text);

	if(it == data.end()) //data.find(text)->second.get_text() == text //(or) data.count(text)  //(or) data.at(text).get_text() => is using .at() a better operation?
	{
		data[text] = Word(text);
		//data.insert( pair<string,Word>(text, Word(text)) );
	}
	else
	{
		//Word w1(text);
		//data[text].increment_count();
		it->second.increment_count();                //sorting is done automatically while inserting in maps.
	}

	steady_clock::time_point mt2 = steady_clock::now();
	increment_elapsed_time(duration_cast<microseconds>(mt2 - mt1).count());
}

map<string, Word>::iterator WordMap::search(const string text)
{
	steady_clock::time_point mt1 = steady_clock::now();

	map<string, Word>::iterator it = data.find(text);

	steady_clock::time_point mt2 = steady_clock::now();
	increment_elapsed_time(duration_cast<microseconds>(mt2 - mt1).count());

	return it;
}
