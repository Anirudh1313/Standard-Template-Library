#include <iostream>
#include <iterator>
#include "SortedVector.h"

using namespace std;

/**
 * Defaut constructor.
 * Reset the global Node counters.
 */
SortedVector::SortedVector()
{
    Node::reset();
}

/**
 * Destructor.
 * Reset the global Node counters.
 */
SortedVector::~SortedVector()
{
    Node::reset();
}

/**
 * @return the size of the data vector.
 */
int SortedVector::size() const { return data1.size(); }

/**
 * Check that the data is sorted.
 * @return true if sorted, false if not.
 */
bool SortedVector::check() const
{
    if (data1.size() == 0) return true;

    vector<Node>::const_iterator it = data1.begin();
    vector<Node>::const_iterator prev = it;

    it++;

    // Ensure that each node is greater than the previous node.
    while ((it != data1.end()) && (*it > *prev))
    {
        prev = it;
        it++;
    }

    return it == data1.end();  // Good if reached the end.
}

/**
 * Insert a new node at the beginning of the data vector.
 * @param value the new node's value.
 */
void SortedVector::prepend(const long value)
{
	Node new_node(value);
	if(data1.size() == 0)
	{
		data1.push_back(new_node);
	}
	else
	{
		vector<Node>::iterator it = data1.begin();
		data1.insert (it, new_node);
	}
}

/**
 * Append a new node at the end of the data vector.
 * @param value the new node's value.
 */
void SortedVector::append(const long value)
{
	Node new_node(value);
	data1.push_back(new_node);
}

/**
 * Remove a node.
 * @param index the index of the node to remove.
 */
void SortedVector::remove(const int index)
{
	if(index < data1.size())
	{
		data1.erase (data1.begin()+index);
	}
	else
	{
		cout << "Index is not found to remove" << endl;
	}
}

/**
 * Insert a new node into the data vector at the
 * appropriate position to keep the vector sorted.
 */
void SortedVector::insert(const long value)
{
	Node new_node(value);
	if(data1.size() == 0)
	{
		data1.push_back(new_node);
	}
	else
	{
		vector<Node>::iterator it;
		it = data1.begin();

		//checking whether values in data are less than new_node value are not.
		while(it != data1.end() && (*it < new_node))
		{
			it++;
		}

		if(it == data1.end())
		{
			data1.push_back(new_node);
		}
		//if the data value is not at the last position of the vector & if greater than new_node's value then insertion has to be done.
		else
		{
			//it++;
			it = data1.insert(it,new_node);
		}
	}
}


/**
 * Return the data node at the indexed position.
 * @param the index of the node.
 * @return a copy of the data node.
 */
Node SortedVector::at(const int index)
{
	return data1[index];
}
