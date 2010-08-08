/*
 * =====================================================================================
 *
 *       Filename:  CombinationSet.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/08/10 18:15:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "CombinationSet.hpp"
#include <iostream>

CombinationSet::CombinationSet()
{
}

CombinationSet::CombinationSet(ConstStringSets &theStringSets)
	: stringSets(theStringSets)
{
	generateCombinations();
}

void CombinationSet::setStringSets(ConstStringSets &newStringSets)
{
	this->stringSets = newStringSets;
	generateCombinations();
}

CombinationSet::ConstStringSets &CombinationSet::getStringSets() const
{
	return this->stringSets;
}

CombinationSet::CombinationIterator CombinationSet::begin()
{
	return combinations.begin();
}

CombinationSet::CombinationIterator CombinationSet::end()
{
	return combinations.end();
}

CombinationSet::CombinationIterator CombinationSet::erase(CombinationIterator it)
{
	return combinations.erase(it);
}

list<CombinationSet::Combination>::size_type CombinationSet::size() const
{
	return combinations.size();
}

CombinationSet::Combination CombinationSet::generateCombination(const vector<StringSet::iterator> &strSetIts)
{
	vector<Combinable *> ret;
	for (vector<StringSet::iterator>::const_iterator it = strSetIts.begin(); it != strSetIts.end(); ++it)
		ret.push_back(**it);
	return ret;
}

void CombinationSet::generateCombinations()
{
	combinations.clear();		
	if (stringSets.size() > 0)
	{
		vector<StringSet::iterator> strSetIts;
		for (StringSets::iterator it = stringSets.begin(); it != stringSets.end(); ++it)
			strSetIts.push_back((*it).begin());	

		int numSets=stringSets.size();	
		
		while (strSetIts[0] != stringSets[0].end())
		{
			//generate combination indicated by iterators
			Combination combination = generateCombination(strSetIts);
			combinations.push_back(combination);			

			//increment iterator and propagate.
			strSetIts[numSets-1]++;
			for (int itIndex=numSets-1; itIndex>0; --itIndex)
			{
				if (strSetIts[itIndex] == stringSets[itIndex].end())
				{
					strSetIts[itIndex-1]++;
					strSetIts[itIndex] = stringSets[itIndex].begin();
				}
			}
		}
	}
}
