/*
 * =====================================================================================
 *
 *       Filename:  CombinationSet.hpp
 *
 *    Description:  This class is a data structure which generates and
 *    maintains all possible combinations of sets of strings. The structure
 *    exposes an iterator which can be used to iterate through all combinations
 *    of strings.
 *
 *        Version:  1.0
 *        Created:  01/08/10 19:46:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __COMBINATIONSET_HPP__
#define __COMBINATIONSET_HPP__

#include <list>
#include <vector>
#include <string>

using namespace std;

/*
 * Combinable interface, anything implementing this can be put in a Combination set.
 */
class Combinable
{
	public:
		virtual const string &getCombinable() const=0;		
};

class CombinationSet
{
	public:
		typedef vector<Combinable *> Combination;
		typedef list<Combination>::iterator CombinationIterator;
		typedef vector<Combinable *> StringSet;
		typedef vector<StringSet> StringSets;
		typedef const vector<StringSet> ConstStringSets;

	public:
		CombinationSet();
		CombinationSet(const StringSets &stringSets);

		/*
		 * Add another set of strings to the combination set, this results in the regeneration of all combinations. 
		 * @param stringSet the vector of strings.
		 */
		void setStringSets(const StringSets &stringSets);
		const StringSets &getStringSets() const;

		CombinationIterator begin();	
		CombinationIterator end();

		/*
		 * Behaves in the same way as STL list erase.
		 * @param it the iterator pointing to the item to remove.
		 * @return the iterator pointing to the item after the erased one. 
		 */
		CombinationIterator erase(CombinationIterator it);

		list<Combination>::size_type size() const;

	protected:
		/*
		 * Generate the combinations from the string sets which were passed in.
		 */
		void generateCombinations();
		Combination generateCombination(const vector<StringSet::iterator> &strSetIts);

		list<Combination> combinations;
		StringSets stringSets;
};

#endif
