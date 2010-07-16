/*
 * =====================================================================================
 *
 *       Filename:  RandomClockTailGenerator.hpp
 *
 *    Description:  Generates ClockTails by picking randomly from input files
 *
 *        Version:  1.0
 *        Created:  16/07/10 21:23:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __RANDOMCLOCKTAILGENERATOR_HPP__
#define __RANDOMCLOCKTAILGENERATOR_HPP__

#include "ClockTailGenerator.hpp"

class RandomClockTailGenerator : public ClockTailGenerator
{
	public:
		RandomClockTailGenerator();
		RandomClockTailGenerator(const RandomClockTailGenerator &rhs);
		virtual ~RandomClockTailGenerator();
		RandomClockTailGenerator &operator=(const RandomClockTailGenerator &rhs);

		virtual void generateNextClockTail();

		virtual void print(std::ostream &out);

	private:
		std::string getRandomLine(InputFile &input);
		unsigned int seed;	
};

#endif
