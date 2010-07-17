/*
 * =====================================================================================
 *
 *       Filename:  RandomClockTailGenerator.cpp
 *
 *    Description:  Randomly generate clocktails
 *
 *        Version:  1.0
 *        Created:  16/07/10 21:51:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#include "RandomClockTailGenerator.hpp"
#include <ctime>
#include <cstdlib>

RandomClockTailGenerator::RandomClockTailGenerator()
{
	//set seed from clock
	seed = (unsigned int)time(0);
	//yes the default PRNG is generally rubbish, but it is only clocktails :-)
	srand(seed);
}

RandomClockTailGenerator::RandomClockTailGenerator(const RandomClockTailGenerator &rhs)
	: ClockTailGenerator(rhs)
{
}

RandomClockTailGenerator::~RandomClockTailGenerator()
{
}

RandomClockTailGenerator &RandomClockTailGenerator::operator=(const RandomClockTailGenerator &rhs)
{
	ClockTailGenerator::operator=(rhs);
	return *this;
}

std::string RandomClockTailGenerator::getRandomLine(InputFile &input)
{
	unsigned int range = input.size();
	std::string ret("Not Found!");
	if (range > 0)
	{
		unsigned int rangedRandom = (unsigned int)(double(range) * (double(rand()) / double(RAND_MAX)));
		ret = *input.getLine(rangedRandom);
	}
	return ret;
}

void RandomClockTailGenerator::generateNextClockTail()
{
	ClockTail nextOne;	

	//go through each input file and pick an entry at random.
	for (std::vector<InputFile>::iterator it = spiritFiles.begin(); it != spiritFiles.end(); ++it)
	{
		std::string spirit = getRandomLine(*it);		
		nextOne.addSpirit(spirit);
	}		

	for (std::vector<InputFile>::iterator it = mixerFiles.begin(); it != mixerFiles.end(); ++it)
	{
		std::string mixer = getRandomLine(*it);		
		nextOne.addMixer(mixer);
	}		

	for (std::vector<InputFile>::iterator it = nameFiles.begin(); it != nameFiles.end(); ++it)
	{
		std::string nameComponent = getRandomLine(*it);
		nextOne.addNameComponent(nameComponent);
	}

	currentClockTail = nextOne;

	notifyObservers();
}

void RandomClockTailGenerator::print(std::ostream &out)
{
	out << "Random, seeded with " << seed << std::endl;
}
