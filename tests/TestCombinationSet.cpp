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
#include "../ClockTailComponents.hpp"
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

int testGenerateCombis(CombinationSet &combiSet)
{
	//note: this leaks memory, but the program will terminate after this method returns
	vector<Combinable *> set1;
	set1.push_back(new Name("1test1"));	
	set1.push_back(new Name("1test2"));	
	set1.push_back(new Name("1test3"));	
	set1.push_back(new Name("1test4"));	
	set1.push_back(new Name("1test5"));	
	vector<Combinable *> set2;
	set2.push_back(new Name("2test1"));	
	set2.push_back(new Name("2test2"));	
	set2.push_back(new Name("2test3"));	
	set2.push_back(new Name("2test4"));	
	set2.push_back(new Name("2test5"));	
	set2.push_back(new Name("2test6"));	
	set2.push_back(new Name("2test7"));	
	vector<Combinable *> set3;
	set3.push_back(new Name("3test1"));	
	set3.push_back(new Name("3test2"));	
	set3.push_back(new Name("3test3"));	
	set3.push_back(new Name("3test4"));	
	set3.push_back(new Name("3test5"));	
	set3.push_back(new Name("3test6"));	
	set3.push_back(new Name("3test7"));	
	set3.push_back(new Name("3test8"));	
	set3.push_back(new Name("3test9"));	
	set3.push_back(new Name("3test10"));	
	set3.push_back(new Name("3test11"));	
	set3.push_back(new Name("3test12"));	
	set3.push_back(new Name("3test13"));	
	set3.push_back(new Name("3test14"));	
	set3.push_back(new Name("3test15"));	
	set3.push_back(new Name("3test16"));	

	vector<vector<Combinable *> > stringSets;
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
	CombinationSet::Combination &firstCombi = *combiIt;
	advance(combiIt,set.size()-1);
	CombinationSet::Combination &lastCombi = *combiIt;

	vector<Combinable *>::iterator set1It = set1.begin();
	vector<Combinable *>::iterator set2It = set2.begin();
	vector<Combinable *>::iterator set3It = set3.begin();
	
	bool firstCorrect = firstCombi[0]->getCombinable() == (*set1It)->getCombinable() && 
						firstCombi[1]->getCombinable() == (*set2It)->getCombinable() && 
						firstCombi[2]->getCombinable() == (*set3It)->getCombinable();
	
	if (!firstCorrect)
	{
		cerr << "Error! First combination was wrong" << endl;
		return -1;
	}

	advance(set1It, set1.size()-1);	
	advance(set2It, set2.size()-1);	
	advance(set3It, set3.size()-1);	
	
	bool lastCorrect = lastCombi[0]->getCombinable() == (*set1It)->getCombinable() && 
						lastCombi[1]->getCombinable() == (*set2It)->getCombinable() && 
						lastCombi[2]->getCombinable() == (*set3It)->getCombinable();

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
