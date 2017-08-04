//SAMPLE

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <chrono>
#include "SortedVector.h"
#include "SortedList.h"
#include "Node.h"

using namespace std;
using namespace std::chrono;

const int GETS_COUNT = 10000;

void run_test_suite() throw (string);
void run_test_functions(const string test_name, void fv(SortedVector& sv, const int size), void fl(SortedList& sl, const int size))  throw (string);

long timed_test(SortedVector& sv, const int size, void f(SortedVector& sv, const int size)) throw (string);
long timed_test(SortedList& sl, const int size, void f(SortedList& sl, const int size)) throw (string);

string commafy(const long n);

void vector_prepends(SortedVector& sv, const int size);
void list_prepends  (SortedList&   sl, const int size);

void vector_appends (SortedVector& sv, const int size);
void list_appends   (SortedList&   sl, const int size);

void vector_gets    (SortedVector& sv, const int size) throw (string);
void list_gets      (SortedList&   sl, const int size) throw (string);

void vector_removes (SortedVector& sv, const int size);
void list_removes   (SortedList&   sl, const int size);

void vector_inserts (SortedVector& sv, const int size);
void list_inserts   (SortedList&   sl, const int size);

// Vector and list sizes.
const int SIZES[] = {100, 500, 1000, 5000, 10000};
// Add size 50000 outside of CodeCheck.

/**
 * The main.
 */
int main()
{
    srand(time(NULL));

    // The overall starting time.
    steady_clock::time_point start_time = steady_clock::now();

    // Run the test suite. Catch any exceptions.
    try
    {
        run_test_suite();
    }
    catch (string& msg)
    {
        cout << endl << "***** " << msg << endl;
        cout.flush();
        return -1;
    }

    // Compute and print the overall elapsed time.
    steady_clock::time_point end_time = steady_clock::now();

    duration<double> elapsed_time = duration_cast<duration<double> >(end_time - start_time);
    cout << "Done! Total time: " << elapsed_time.count() << " seconds" << endl;

    return 0;
}

/**
 * Run the test suite.
 * @throw an exception if anything goes wrong.
 */
void run_test_suite() throw (string)
{
    run_test_functions("Prepend", vector_prepends, list_prepends);
    run_test_functions("Append",  vector_appends,  list_appends);
    run_test_functions("Get",     vector_gets,     list_gets);
    run_test_functions("Remove",  vector_removes,  list_removes);
    run_test_functions("Insert",  vector_inserts,  list_inserts);
}

/**
 * Run and time a pair of vector and linked list test functions.
 * @param test_name the name of the test pair.
 * @param fv the vector function.
 * @param fl the linked list function.
 * @throw an exception if anything goes wrong.
 */
void run_test_functions(const string test_name, void fv(SortedVector& sv, const int size), void fl(SortedList& sl, const int size)) throw (string)
{
    // Print a nice header for the test pair.
    for (int i = 0; i < test_name.length(); i++) cout << "=";
    cout << endl << test_name << endl;
    for (int i = 0; i < test_name.length(); i++) cout << "=";
    cout << endl;
    cout << "          |---------------Vector-------------|";
    cout <<        "   |-----------------List-------------|" << endl;
    cout << "   Size        Time  Creates   Copies Destroys";
    cout <<        "        Time  Creates   Copies Destroys" << endl;

    // Loop over the data sizes for the tests.
    for (int size : SIZES)
    {
        cout << setw(7) << commafy(size);

        // Run and time the vector test and print its statistics.
        SortedVector sv;
        long etv = timed_test(sv, size, fv);
        cout << setw(9) << commafy(etv) << " ms";
        cout << setw(9) << commafy(Node::get_constructor_count());
        cout << setw(9) << commafy(Node::get_copy_count());
        cout << setw(9) << commafy(Node::get_destructor_count());
        cout.flush();

        // Make sure the test didn't ruin the sort order.
        if (!sv.check()) throw string("Vector sort error!");

        // Run and time the linked list test and print its statistics.
        SortedList sl;
        long etl = timed_test(sl, size, fl);
        cout << setw(9) << commafy(etl) << " ms";
        cout << setw(9) << commafy(Node::get_constructor_count());
        cout << setw(9) << commafy(Node::get_copy_count());
        cout << setw(9) << commafy(Node::get_destructor_count());
        cout << endl;

        // Make sure the test didn't ruin the sort order.
        if (!sl.check()) throw string("List sort error!");
    }

    cout << endl;
}

/**
 * Run and time a vector test function.
 * @param sv the sorted vector test subject.
 * @param size the data size of the vector.
 * @param f the test function.
 * @return the elapsed time in milliseconds.
 * @throw an exception if anything goes wrong.
 */
long timed_test(SortedVector& sv, const int size, void f(SortedVector& sv, const int size)) throw (string)
{
    // Starting time.
    steady_clock::time_point start_time = steady_clock::now();

    // Run the test.
    f(sv, size);

    // Compute and return the elpased time in milliseconds.
    steady_clock::time_point end_time = steady_clock::now();
    return duration_cast<milliseconds>(end_time - start_time).count();
}

/**
 * Run and time a linked list test function.
 * @param sl the sorted linked list test subject.
 * @param size the data size of the linked list.
 * @param f the test function.
 * @return the elapsed time in milliseconds.
 * @throw an exception if anything goes wrong.
 */
long timed_test(SortedList& sl, const int size, void f(SortedList& sl, const int size)) throw (string)
{
    // Starting time.
    steady_clock::time_point start_time = steady_clock::now();

    // Run the test.
    f(sl, size);

    // Compute and return the elpased time in milliseconds.
    steady_clock::time_point end_time = steady_clock::now();
    return duration_cast<milliseconds>(end_time - start_time).count();
}

/**
 * Convert a number to a string with commas.
 * @param n the number.
 */
string commafy(const long n)
{
    string str = to_string(n);
    int pos = str.length() - 3;

    while (pos > 0)
    {
        str.insert(pos, ",");
        pos -= 3;
    }

    return str;
}

//**********TEST SUITE********************

/**
 * Test function: Insert new nodes at the beginning of the data vector.
 *                The final node data values are 0, 1, 2, ..., size-1.
 * @param sv the vector test subject.
 * @param size the data size of the vector.
 */
void vector_prepends(SortedVector& sv, const int size)
{
	int sz = size;
	while(sv.size() < size)
	{

		sv.prepend(sz);
		sz--;
	}
}

/**
 * Test function: Insert new nodes at the beginning of the data list.
 *                The final node data values are 0, 1, 2, ..., size-1.
 * @param sl the linked list test subject.
 * @param size the data size of the linked list.
 */
void list_prepends(SortedList& sl, const int size)
{
	int sz = size;
	while(sl.size() < size)
	{

		sl.prepend(sz);
		sz--;
	}
}

/**
 * Test function: Append new nodes at the end of the data vector.
 *                The final node data values are 0, 1, 2, ..., size-1.
 * @param sv the vector test subject.
 * @param size the data size of the vector.
 */
void vector_appends(SortedVector& sv, const int size)
{
	int sz = 0;
	while(sv.size() < size)
	{
		sv.append(sz);
		sz++;
	}
}

/**
 * Test function: Append new nodes at the end of the data list.
 *                The final node data values are 0, 1, 2, ..., size-1.
 * @param sl the linked list test subject.
 * @param size the data size of the linked list.
 */
void list_appends(SortedList& sl, const int size)
{
	int sz = 0;
	while(sl.size() < size)
	{
		sl.append(sz);
		sz++;
	}
}

/**
 * Test function: Access nodes in the data vector.
 * @param sv the vector test subject.
 * @param size the data size of the vector.
 * @throw an exception if anything goes wrong.
 */
void vector_gets(SortedVector& sv, const int size) throw (string)
{
    // First fill the vector data.
    vector_appends(sv, size);
    Node::reset();

    // Loop to access nodes at random positions.
    for (int i = 0; i < GETS_COUNT; i++)
    {
        int index = rand()%size;
        long value = sv.at(index).get_value();

        // Make sure we got the correct node.
        if (index != value) throw string("Vector data mismatch!");
    }
}

/**
 * Test function: Access nodes in the data list.
 * @param sl the linked list test subject.
 * @param size the data size of the linked list.
 * @throw an exception if anything goes wrong.
 */
void list_gets(SortedList& sl, const int size) throw (string)
{
    // First fill the list data.
    list_appends(sl, size);
    Node::reset();

    // Loop to access nodes at random positions.
    for (int i = 0; i < GETS_COUNT; i++)
    {
        int index = rand()%size;
        long value = sl.at(index).get_value();

        // Make sure we got the correct node.
        if (index != value) throw string("List data mismatch!");
    }
}

/**
 * Test function: Remove all the nodes from the data vector
 *                one at a time.
 * @param sv the vector test subject.
 * @param size the data size of the vector.
 */
void vector_removes(SortedVector& sv, const int size)
{
    // First fill the vector data.
    vector_appends(sv, size);
    Node::reset();

    // Loop to remove a node at a random position
    // one at a time until the nodes are all gone.
    while (sv.size() > 0)
    {
        int index = rand()%(sv.size());
        sv.remove(index);
        //index++;

    }
}

/**
 * Test function: Remove all the nodes from the data list
 *                one at a time.
 * @param sl the linked list test subject.
 * @param size the data size of the linked list.
 */
void list_removes(SortedList& sl, const int size)
{
    // First fill the list data.
    list_appends(sl, size);
    Node::reset();

    while (sl.size() > 0)
    {
        int index = rand()%sl.size();
        sl.remove(index);
        //index++;
    }
}

/**
 * Test function: Insert random values into the sorted data vector.
 * @param sv the vector test subject.
 * @param size the data size of the vector.
 */
void vector_inserts(SortedVector& sv, const int size)
{

    while (sv.size() < size)
    {
    	sv.insert(rand()%size);
    }
}

/**
 * Test function: Insert random values into the sorted data list.
 * @param sl the linked list test subject.
 * @param size the data size of the linked list.
 */
void list_inserts(SortedList& sl, const int size)
{
    while (sl.size() < size)
    {
    	sl.insert(rand()%size);
    }
}