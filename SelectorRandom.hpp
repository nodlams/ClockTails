/*
 * =====================================================================================
 *
 *       Filename:  SelectorRandom.hpp
 *
 *    Description:  A clocktail selector that picks names/ingrediants randomly.
 *    The selector also checks the history to ensure that the same drink isn't
 *    generated twice.
 *
 *        Version:  1.0
 *        Created:  30/07/10 18:18:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __SELECTORRANDOM_HPP__
#define __SELECTORRANDOM_HPP__

#include "Selector.hpp"
#include "InputFile.hpp"
#include "History.hpp"
#include "CombinationSet.hpp"

#include <string>
#include <vector>

class SelectorRandom : public Selector
{
	public:
		SelectorRandom();
		SelectorRandom(const unsigned int seed);

		virtual ClockTail generateClockTail();

		virtual void print(std::ostream &out) const;

		void setNameFiles(const std::vector<InputFile> &nameFiles);
		void setDrinksFiles(const std::vector<InputFile> &mixerFiles, const std::vector<InputFile> &spiritFiles);

	protected:
		virtual std::string getRandomLine(const InputFile &input);

		CombinationSet nameCombinations;
		CombinationSet drinkCombinations;

		const unsigned int seed;
};

#endif
