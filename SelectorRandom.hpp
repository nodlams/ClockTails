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

#include <string>
#include <vector>

class SelectorRandom : public Selector
{
	public:
		SelectorRandom(const History &history);
		SelectorRandom(const History &history, const unsigned int seed);

		virtual ClockTail generateClockTail(const std::vector<InputFile> &nameFiles, const std::vector<InputFile> &mixers, const std::vector<InputFile> &spirits);

		virtual void print(std::ostream &out);

	protected:
		virtual std::string getRandomLine(const InputFile &input);

		const History &history;
		const unsigned int seed;
};

#endif
