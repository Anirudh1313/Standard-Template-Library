#include <iostream>
#include <iterator>
#include "SortedList.h"

using namespace std;

/**
 * Defaut constructor.
 * Reset the global Node counters.
 */
SortedList::SortedList()
{
    Node::reset();
}

/**
 * Destructor.
 * Reset the global Node counters.
 */
SortedList::~SortedList()
{
    Node::reset();
}

/**
 * @return the size of the data list.
 */
int SortedList::size() const { return data.size(); }

/**
 * Check that the data is sorted.
 * @return true if sorted, false if not.
 */

bool SortedList::check()
{
    if (data.size() == 0) return true;

    list<Node>::const_iterator it = data.begin();
    list<Node>::const_iterator prev = it;

    it++;

    // Ensure that each node is greater than the previous node.
    while ((it != data.end()) && (*it > *prev))
    {
        prev = it;
        it++;
    }

    return it == data.end();  // Good if reached the end.
}

/**
 * Insert a new node at the beginning of the data list.
 * @param value the new node's value.
 */
void SortedList::prepend(const long value)
{
	Node new_node(value);
	data.push_front(new_node);
}

/**
 * Append a new node at the end of the data list.
 * @param value the new node's value.
 */
void SortedList::append(const long value)
{
	Node new_node(value);
	data.push_back(new_node);
}

/**
 * Remove a node.
 * @param index the index of the node to remove.
 */
void SortedList::remove(const int index)
{
    /***** Complete this function. *****/
	if(data.size() < index)
	{
		cout << "index not found to remove." << endl;
	}
	else
	{
		list<Node>::iterator it;
		it = data.begin();
		int i = 0;
		while(i < index)
		{
			it++;
			i++;
		}
		if(i == index)
		{
			it = data.erase(it);
		}
	}

}

/**
 * Insert a new node into the data list at the
 * appropriate position to keep the list sorted.
 */
void SortedList::insert(const long value)
{
	Node new_node(value);
	if(data.size() == 0)
	{
		data.push_back(new_node);
	}
	else
	{
		list<Node>::iterator it;
		it = data.begin();

		//checking whether values in data are less than new_node value are not.
		while((it != data.end()) && (*it < new_node))
		{
				it++;
		}

		if(it == data.end())
		{
			data.push_back(new_node);
		}
		//if the data value is greater than new_node's value then, insertion has to be done.
		else
		{
			it = data.insert(it,new_node);
		}
	}
}

/**
 * Return the data node at the indexed position.
 * @param the index of the node.
 * @return a copy of the data node.
 */
Node SortedList::at(const int index)
{
	if(data.size() < index)
	{
		cout << "index not found." << endl;
		return false;
	}
	else
	{
		list<Node>::iterator it = data.begin();
		int i = 0;
		while(i < index)
		{
			it++;
			i++;
		}
		//if(i == index)
		{
			return *it;
		}
	}
	//return nullptr;
}
