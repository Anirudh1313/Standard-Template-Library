#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "WordVector.h"

using namespace std;
using namespace std::chrono;

WordVector::WordVector()
{
	//data.TimedContainer::reset_elapsed_time();
}

WordVector::~WordVector()
{
}

vector<Word>& WordVector::get_data() { return data; }

int WordVector::get_count(const string text) const
{
	bool found;
	int word_index = find(text, 1, data.size()-1, found);
	return found ? data[word_index].get_count() : 0;
    /***** Complete this member function. *****/
}

void WordVector::insert(const string text)
{
	long timev;
	steady_clock::time_point vt1 = steady_clock::now();

	if(data.size() == 0)
	{
		Word w1(text);
		data.push_back(w1);
	}
	else
	{
		bool found;
		int index = find(text, 0, data.size()-1, found);
		if(!(found))
		{
			vector<Word>::iterator it = index < data.size() ? data.begin() + index : data.end();
			data.insert(it, Word(text));
		}
		else
		{
			data[index].increment_count();
		}

	}

	steady_clock::time_point vt2 = steady_clock::now();
	timev = duration_cast<microseconds>(vt2 - vt1).count();

	increment_elapsed_time(timev);

}

vector<Word>::iterator WordVector::search(const string text)
{
	steady_clock::time_point vt1 = steady_clock::now();

	bool found;
	int index = find(text, 0, data.size()-1, found);

	steady_clock::time_point vt2 = steady_clock::now();
	increment_elapsed_time(duration_cast<microseconds>(vt2 - vt1).count());

	return found ? data.begin() + index : data.end();

}

int WordVector::find(const string text, int low, int high, bool& found) const
{
	while(low <= high)
	{
		int mid = (low+high)/2;
		found = data[mid].get_text() == text;
		if(found)
		{
			return mid;
		}
		if(text < data[mid].get_text())
		{
			high = mid-1;
		}
		if(text > data[mid].get_text())
		{
			low = mid+1;
		}

	}
	found = false;
	return low;

    /***** Complete this member function. *****/
}
