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
	if (nameCombinations.size() == 0)
		throw SelectorException("Unique names exhausted, please add more strings to the Names file(s)");
	if (drinkCombinations.size() == 0)
		throw SelectorException("Unique drink combinations exhausted, please add more strings to the spirits/mixer files");

	CombinationSet::CombinationIterator nameIt = nameCombinations.begin();	
	CombinationSet::CombinationIterator drinkIt = drinkCombinations.begin();

	CombinationSet::Combination &nameCombi = *nameIt;
	//convert the combinations to a set of names
	vector<Name> nameSet;
	for (CombinationSet::Combination::iterator it = nameCombi.begin(); it != nameCombi.end(); ++it)
	{
		Combinable *nameAsCombinable = (*it);
		Name *name = dynamic_cast<Name*>(nameAsCombinable);
		nameSet.push_back(*name);
	}

	ClockTail nextOne;	
	nextOne.setNameComponents(nameSet);
	
	nameCombinations.erase(nameIt);	
	drinkCombinations.erase(drinkIt);

	return nextOne;
}

void SelectorRandom::print(ostream &out) const
{
	out << "Random ClockTail Generator";
}

void SelectorRandom::setComponents(Names &names, Mixers &mixers, Spirits &spirits)
{
	/*CombinationSet::StringSets sets;
	for (vector<InputFile>::const_iterator it = names.begin(); it != names.end(); ++it)
	{
		sets.push_back((*it).getLines());	
	}
	nameCombinations.setStringSets(sets);	*/
}

