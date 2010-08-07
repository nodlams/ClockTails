/*
 * =====================================================================================
 *
 *       Filename:  TestCombinationSet.cpp
 *
 *    Description:  Unit testing for TestCombination Set
 *
 *        Version:  1.0
 *        Created:  07/08/10 18:31:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "../CombinationSet.hpp"
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

int testGenerateCombis(CombinationSet &combiSet)
{
	vector<string> set1;
	set1.push_back("1test1");	
	set1.push_back("1test2");	
	set1.push_back("1test3");	
	set1.push_back("1test4");	
	set1.push_back("1test5");	
	vector<string> set2;
	set2.push_back("2test1");	
	set2.push_back("2test2");	
	set2.push_back("2test3");	
	set2.push_back("2test4");	
	set2.push_back("2test5");	
	set2.push_back("2test6");	
	set2.push_back("2test7");	
	vector<string> set3;
	set3.push_back("3test1");	
	set3.push_back("3test2");	
	set3.push_back("3test3");	
	set3.push_back("3test4");	
	set3.push_back("3test5");	
	set3.push_back("3test6");	
	set3.push_back("3test7");	
	set3.push_back("3test8");	
	set3.push_back("3test9");	
	set3.push_back("3test10");	
	set3.push_back("3test11");	
	set3.push_back("3test12");	
	set3.push_back("3test13");	
	set3.push_back("3test14");	
	set3.push_back("3test15");	
	set3.push_back("3test16");	

	vector<vector<string> > stringSets;
	stringSets.push_back(set1);
	stringSets.push_back(set2);
	stringSets.push_back(set3);

	CombinationSet set(stringSets);

	//check the number of combinations in the set is correct.
	int correctNum = set1.size() * set2.size() * set3.size();
	if (set.size() != correctNum)
	{
		cerr << "Error! generated combination set size is not the correct size" << endl;
		return -1;
	}	

	//try resetting the stringSets
	set.setStringSets(stringSets);
	if (set.size() != correctNum)
	{
		cerr << "Error! generated combination set size after setStringSet is not the correct size" << endl;
		return -1;
	}	

	//check the first and last combination are sensible.
	CombinationSet::CombinationIterator combiIt = set.begin();
	vector<string> &firstCombi = *combiIt;
	advance(combiIt,set.size()-1);
	vector<string> &lastCombi = *combiIt;

	vector<string>::iterator set1It = set1.begin();
	vector<string>::iterator set2It = set2.begin();
	vector<string>::iterator set3It = set3.begin();
	
	bool firstCorrect = firstCombi[0] == *set1It && firstCombi[1] == *set2It && firstCombi[2] == *set3It;
	
	if (!firstCorrect)
	{
		cerr << "Error! First combination was wrong" << endl;
		return -1;
	}

	advance(set1It, set1.size()-1);	
	advance(set2It, set2.size()-1);	
	advance(set3It, set3.size()-1);	
	
	bool lastCorrect = lastCombi[0] == *set1It && lastCombi[1] == *set2It && lastCombi[2] == *set3It;

	if (!lastCorrect)
	{
		cerr << "Error! Last combination was wrong" << endl;
		return -1;
	}

	return 0;
}

const int NUMTESTS=1;
//function pointer to function returning int and taking a ref to CombinationSet
typedef int (*TestFunc)(CombinationSet &);
TestFunc testFuncs[NUMTESTS] = {&testGenerateCombis};

int runTest(const int testID)
{
	CombinationSet set;	
	return testFuncs[testID](set);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cerr << "Error, incorrect number of parameters for test program" << endl;
		return -1;
	}

	int testID = -1;
	string input(argv[1]);

	istringstream iss(input);	
	bool worked = iss >> testID;

	if (!worked || testID < 0 || testID >= NUMTESTS)	
	{
		cerr << "Error, invalid test index specified" << endl;
		return -1;
	}

	return runTest(testID);
}
