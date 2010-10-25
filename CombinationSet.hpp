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

#include <string>
#include <boost/shared_ptr.hpp>

using std::string;
using boost::shared_ptr;

/*
 * Combinable interface, anything implementing this can be put in a Combination set.
 */
class Combinable
{
	public:
		virtual shared_ptr<const string> getCombinable() const=0;		
};

class CombinationSet
{
	public:
		CombinationSet();

	protected:
};

#endif
