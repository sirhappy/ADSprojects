//#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

#include "SkipList.h"

#include "TimeStamp.h"
#include "JournalNetActivity.h"

using namespace std;

// Test timer
long gl_ticktack;

void tick()
{
	gl_ticktack = clock();
}
void tack(const string & action = "TickTack")
{
	cout << action << " : " << clock()-gl_ticktack << "/ " << CLOCKS_PER_SEC << " seconds" << endl;
}
// End of: Test timer

// Test procedure
template <int numLevels>
void testJournal(const JournalNetActivity<numLevels> & journal, string host, const TimeStamp & from, const TimeStamp & to)
{
	static int cntTest = 0;
	cntTest++;
	cout << "===============================================================================" << endl;
	cout << "SkipList: Test #" << cntTest << endl << endl;

	tick();
	journal.outputSuspiciousActivities(host, from, to);
	tack("Test took");
	cout << "===============================================================================" << endl;

	cout << endl;
}
// End of: Test procedure

int main (int argc, char* argv[])
{
	
	// Test SkipList over integers
	typedef SkipList<int,int,3> TypeSkipList;
	typedef TypeSkipList::TypeNode TypeSkipNode;
/*
	try {
		TypeSkipList list;
		tick();
		int i = 0;
		for (i = 0; i < 4; ++i)
		{
			list.insert(i, i);
		}
		tack("SkipList over integers creation");

		TypeSkipNode* start = list.findFirst(0);
		TypeSkipNode* end = list.findLastLessThan(20);
		//cout << list.findFirst(19)->m_value << " " << end->m_value << endl;
        /*
		while (start != end->m_next) {
			cout << start->m_value << endl;
			start = start->m_next;
		}
		TypeSkipNode * node = 0;
        /*
		tick();
		// We call here the method findFirst inherited from OrderedList
		node = list.OrderedList <int, int, TypeSkipNode >::findFirst(i - 5);
		cout << "Element found:" << node->m_value << endl;
		tack("OrderedList over integers searching");

		tick();
		node = list.findFirst(i - 5);
		cout << "Element found:" << node->m_value << endl;
		tack("SkipList over integers searching");
		// End of: Test SkipList over integers
        
        TypeSkipNode* f = list.findFirst(1);
        list.remove(f);
        start = list.findFirst(0);
        while (start != end->m_next) {
            cout << start->m_value << endl;
            start = start->m_next;
        }
        
        TypeSkipList list2 = list;
        list2.remove(list2.findFirst(3));
        start = list2.findFirst(0);
        end = list2.findLastLessThan(20);
        while (start != end->m_next) {
            cout << start->m_value << endl;
            start = start->m_next;
        }
	}
	catch (exception &ex) {
		cout << ex.what();
	}
	catch (...) {
		cout << " asdf";
	}
*/
    
    try{
		srand(time(0));
		
		// Test #1
		JournalNetActivity<5> journal1;
		journal1.parseLog("..\\test1.log");
		testJournal(journal1, "e-maxx.ru", TimeStamp(2015,6,10,10,33,1), TimeStamp(2015,6,10,10,33,4));
		/*
		// Test #2
		JournalNetActivity<5> journal2;
		journal2.parseLog("..\\test2.log");
		testJournal(journal2, "verisicretproxi.com", TimeStamp(2015,6,10,10,33,54), TimeStamp(2015,6,10,10,33,54));
		
		// Test #3
		JournalNetActivity<15> journal3;
		tick();
		journal3.parseLog("..\\test3.log");
		tack("Parsing test3.log");
		testJournal(journal3, "verisicretproxi.com", TimeStamp(2015,6,10,12,27,45), TimeStamp(2015,6,10,12,27,59));
		
		// Test #4
		JournalNetActivity<15> journal4;
		tick();
		journal4.parseLog("..\\test4.log");
		tack("Parsing test4.log:");
		testJournal(journal4, "verisicretproxi.com", TimeStamp(2015,6,10,22,30,20), TimeStamp(2015,6,10,22,30,50));
		*/
	}
	catch(exception &e){
		cout << e.what();
	}
	catch (...){
		cout << "Something wrong happend." << endl;
	}
	cout << endl;
	
	return EXIT_SUCCESS;
}
