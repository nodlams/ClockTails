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

SelectorRandom::SelectorRandom(const History &theHistory)
	: history(theHistory),seed((unsigned int)time(0))
{
	srand(seed);
}

SelectorRandom::SelectorRandom(const History &theHistory, const unsigned int theSeed)
	: history(theHistory), seed(theSeed)
{
	srand(seed);
}

std::string SelectorRandom::getRandomLine(const InputFile &input)
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

ClockTail SelectorRandom::generateClockTail(const std::vector<InputFile> &nameFiles, const std::vector<InputFile> &mixerFiles, const std::vector<InputFile> &spiritFiles)
{
	//TODO: This could loop indefinitely if all the names or recipes have been used.
	ClockTail nextOne;

	std::vector<std::string> nameBits;

	do
	{
		nextOne = ClockTail();
		nameBits.clear();
		for (std::vector<InputFile>::const_iterator it = nameFiles.begin(); it != nameFiles.end(); ++it)
		{
			std::string nameComponent = getRandomLine(*it);
			nameBits.push_back(nameComponent);
		}
		nextOne.setNameComponents(nameBits);
	} while (history.nameHasBeenGenerated(nextOne));

	std::vector<std::string> chosenMixers;
	std::vector<std::string> chosenSpirits;

	do 
	{
		chosenMixers.clear();
		chosenSpirits.clear();
		nextOne = ClockTail();

		for (std::vector<InputFile>::const_iterator it = mixerFiles.begin(); it != mixerFiles.end(); ++it)
		{
			std::string mixer = getRandomLine(*it);
			chosenMixers.push_back(mixer);
		}
		for (std::vector<InputFile>::const_iterator it = spiritFiles.begin(); it != spiritFiles.end(); ++it)
		{
			std::string spirit = getRandomLine(*it);
			chosenSpirits.push_back(spirit);
		}
		nextOne.setNameComponents(nameBits);
		nextOne.setMixers(chosenMixers);
		nextOne.setSpirits(chosenSpirits);

	} while (history.recipeHasBeenGenerated(nextOne));

	nextOne.setNameComponents(nameBits);
	nextOne.setMixers(chosenMixers);
	nextOne.setSpirits(chosenSpirits);

	return nextOne;
}

void SelectorRandom::print(std::ostream &out) const
{
	out << "Random ClockTail Generator";
}
