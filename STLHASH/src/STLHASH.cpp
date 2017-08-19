#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <chrono>
#include <stdlib.h>
#include "Word.h"
#include "WordVector.h"
#include "WordMap.h"

using namespace std;
using namespace std::chrono;

const string INPUT_FILE_NAME = "USConstitution.txt";
const int    MAX_SEARCHES    = 100000;

void time_word_insertions(ifstream& in, WordVector& v, WordMap& m);
void make_spot_checks(WordVector& v, WordMap& m) throw(string);
void check_concordances(WordVector& v, WordMap& m) throw(string);
void time_word_searches(WordVector& v, WordMap& m) throw(string);
long time_vector_insert(WordVector& v);
string commafy(const long n);

int main()
{
    ifstream in;
    in.open(INPUT_FILE_NAME);
    if (in.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    WordVector v;
    WordMap    m;

    try
    {
        time_word_insertions(in, v, m);
        make_spot_checks(v, m);
        check_concordances(v, m);
        time_word_searches(v, m);
    }
    catch (string& msg)
    {
        cout << endl << endl << "***** " << msg << endl;
    }

    return 0;
}

void time_word_insertions(ifstream& in, WordVector& v, WordMap& m) //throw(string)
{
	int len = 0;
    string line;
    int line_count = 0;
    int character_count = 0;
    int word_count = 0;

    cout << "Timed insertions ..." << endl;

    while(getline(in,line))
    {
    	int i = 0;
    	string word, prev;
    	while(i < line.length())
    	{
    		if(isalpha(line[i]) || line[i] == ' ' || line[i] == '-')
    		{
    			if(isupper(line[i]))
    			{
    				line[i] = tolower(line[i]);
    			}
    			if(islower(line[i]))
    			{
    				//while(line[i] != ' ' && line[i] != '-' && i != line.length()-1)
    				{
    					word += line[i];
    					//i++;
    					//character_count += 1;
    				}
//        			v.insert(word);
//        			m.insert(word);
//        			word_count += 1;
//        			word.clear();
    			}
    		}

    		if(line[i] == '-' || (i == line.length()-1 && isalpha(line[i])) || (i == line.length()-2 && !isalpha(line[i+1])) || (line[i] == ' ' && !(isdigit(line[i])) && !(isdigit(line[i]))))
    		{
    	    	v.insert(word);
    	    	m.insert(word);
    	    	word_count += 1;
    	    	word.clear();

			}


//    		if(line[i] == ' ' || line[i] == '-' || i == line.length()-1)
//    		{
//    			if(prev != word)
//    			{
//        			v.insert(word);
//        			m.insert(word);
//        			word_count += 1;
//    			}
//    		}
//
//    		if(v.get_data().size() > len)
//    		{
//    			prev = word;
//    			word.clear();
//    		}
    		i++;
    		character_count += 1;
//    		len = v.get_data().size();
    	}
    	line_count += 1;
    }

    cout << "          Lines: " << setw(6) << commafy(line_count) << endl;
    cout << "     Characters: " << setw(6) << commafy(character_count) << endl;
    cout << "          Words: " << setw(6) << commafy(word_count) << endl;
    cout << endl;
    cout << "    Vector size: " << commafy(v.get_data().size()) << endl;
    cout << "       Map size: " << commafy(m.get_data().size()) << endl;
    cout << endl;
    cout << "    Vector total insertion time: " << setw(8)
         << commafy(v.get_elapsed_time()) << " usec" << endl;
    cout << "       Map total insertion time: " << setw(8)
         << commafy(m.get_elapsed_time()) << " usec" << endl;
}

void make_spot_checks(WordVector& v, WordMap& m) throw(string)
{
    cout << endl << "Spot checks of word counts ..." << endl;
    vector<Word>&      vdata = v.get_data();
    map<string, Word>& mdata = m.get_data();

    vector<string> texts;
    texts.push_back("amendment");
    texts.push_back("article");
    texts.push_back("ballot");
    texts.push_back("citizens");
    texts.push_back("congress");
    texts.push_back("constitution");
    texts.push_back("democracy");
    texts.push_back("electors");
    texts.push_back("government");
    texts.push_back("law");
    texts.push_back("legislature");
    texts.push_back("people");
    texts.push_back("president");
    texts.push_back("representatives");
    texts.push_back("right");
    texts.push_back("trust");
    texts.push_back("united");
    texts.push_back("vice");
    texts.push_back("vote");
    texts.push_back("states");

    for (string text : texts)
    {
        cout << "    " << text << ": ";

        vector<Word>::iterator      itv = v.search(text);
        map<string, Word>::iterator itm = m.search(text);

        if(itv == v.get_data().end())
        	cout << "vector:" << "(not found) ";
        else
        	cout << "vector:" << itv->get_count() << " ";

        if(itm == m.get_data().end())
        	cout << "map:" << "(not found)" << endl;
        else
        	cout << "map:" << itm->second.get_count() << endl;

    }
}

void check_concordances(WordVector& v, WordMap& m) throw(string)
{
    cout << endl << "Checking concordances ... ";  cout.flush();

    vector<Word>&      vdata = v.get_data();
    map<string, Word>& mdata = m.get_data();

    int vsize = vdata.size();
    int msize = mdata.size();

    if (vsize == 0) throw("Empty vector.");
    if (msize == 0) throw("Empty map.");

    if (vsize != msize ) throw(string("Size mismatch: ") + to_string(vsize) +
                                                 " and " + to_string(msize));

    vector<Word>::iterator      itv = vdata.begin();
    map<string, Word>::iterator itm = mdata.begin();

    while (itv != vdata.end())
    {
        if (*itv != itm->second)
        {
            throw string(string("Data mismatch: ")
                    + itv->get_text() + ":" + to_string(itv->get_count())
                    + " and " + itm->second.get_text() + ":"
                    + to_string(itm->second.get_count()));
        }

        ++itv;
        ++itm;
    }

    cout << "both match!" << endl;
}

void time_word_searches(WordVector& v, WordMap& m) throw(string)
{
    cout << endl << "Timed searches (" << commafy(MAX_SEARCHES)
                 << " searches) ..." << endl;

    int size = v.get_data().size()-1;
    int size1 = m.get_data().size()-1;

    v.reset_elapsed_time();
    m.reset_elapsed_time();

    for (int i = 1; i <= MAX_SEARCHES; i++)
    {
    	int index = rand()%size;
        string text = v.get_data()[index].get_text();

    	v.search(text);

        int ind = rand()%size1;
        map<string, Word>::iterator itm = m.get_data().begin();
        advance(itm, ind);
        string text1 = itm->second.get_text();

        m.search(text1);
    }

    cout << endl;
    cout << "    Vector total search time: " << setw(8)
         << commafy(v.get_elapsed_time()) << " usec" << endl;
    cout << "       Map total search time: " << setw(8)
         << commafy(m.get_elapsed_time()) << " usec" << endl;
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
