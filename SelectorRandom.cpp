/*
 * =====================================================================================
 *
 *       Filename:  RandomSelector.cpp
 *
 *    Description:  Implementation of the random selector class.
 *
 *        Version:  1.0
 *        Created:  30/07/10 18:23:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "SelectorRandom.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;

SelectorRandom::SelectorRandom()
	: seed((unsigned int)time(0))
{
	srand(seed);
}

SelectorRandom::SelectorRandom(const unsigned int theSeed)
	: seed(theSeed)
{
	srand(seed);
}

ClockTail SelectorRandom::generateClockTail()
{
	CombinationSet::CombinationIterator nameIt = nameCombinations.begin();	
	CombinationSet::CombinationIterator drinkIt = drinkCombinations.begin()

	ClockTail nextOne;	

	nextOne.setNameComponents(*nameIt);
	
	nameCombinations.erase(nameIt);	
	drinkCombinations.erase(drinkIt);

	return nextOne;
}

void SelectorRandom::print(ostream &out) const
{
	out << "Random ClockTail Generator";
}

void SelectorRandom::setNameFiles(const vector<InputFile> &nameFiles)
{
	CombinationSet::StringSets sets;
	for (vector<InputFile>::const_iterator it = nameFiles.begin(); it != nameFiles.end(); ++it)
	{
		sets.push_back((*it).getLines());	
	}
	nameCombinations.setStringSets(sets);	
}

void SelectorRandom::setDrinkFiles(const vector<InputFile> &mixerFiles, const vector<InputFile> &spiritFiles)
{
	CombinationSet::StringSets sets;
	for (vector<InputFile>::const_iterator it = mixerFiles.begin(); it != mixerFiles.end(); ++it)
	{
		sets.push_back((*it).getLines());	
	}
	for (vector<InputFile>::const_iterator it = spiritFiles.begin(); it != spiritFiles.end(); ++it)
	{
		sets.push_back((*it).getLines());	
	}

	drinkCombinations.setStringSets(sets);
}
