/*
 * =====================================================================================
 *
 *       Filename:  ClockTailGenerator.cpp
 *
 *    Description:  Class that handles generation of clocktails
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:24:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#include "CTObserver.hpp"
#include "ClockTailGenerator.hpp"
#include "FeedBack.hpp"
#include "ClockTail.hpp"
#include "Selector.hpp"

ClockTailGenerator::ClockTailGenerator(Selector &selector)
	: ctSelector(selector)
{
}

ClockTailGenerator::ClockTailGenerator(const ClockTailGenerator &rhs)
	: spiritFiles(rhs.spiritFiles), 
		mixerFiles(rhs.mixerFiles), 
		nameFiles(rhs.nameFiles), 
		observers(rhs.observers), 
		currentClockTail(rhs.currentClockTail), 
		ctSelector(rhs.ctSelector)
{
}

ClockTailGenerator::~ClockTailGenerator()
{
}

ClockTailGenerator &ClockTailGenerator::operator=(const ClockTailGenerator &rhs)
{
	if (this != &rhs)
	{
		//cant copy and swap here because it's an abstract class
		this->spiritFiles = rhs.spiritFiles;
		this->mixerFiles = rhs.mixerFiles;
		this->nameFiles = rhs.nameFiles;		
		this->observers = rhs.observers;
		this->currentClockTail = rhs.currentClockTail;
		this->ctSelector = rhs.ctSelector;
	}

	return *this;
}

void ClockTailGenerator::initialise()
{
}

void ClockTailGenerator::registerObserver(CTObserver &observer)
{
	observers.push_back(&observer);
}

void ClockTailGenerator::notifyObservers()
{
	for (std::vector<CTObserver *>::iterator it = observers.begin(); it != observers.end(); ++it)
	{
		(*it)->updateClockTail();
	}		
}

void ClockTailGenerator::generateNextClockTail()
{
	currentClockTail = ctSelector.generateClockTail(nameFiles, mixerFiles, spiritFiles);
	notifyObservers();
}

void ClockTailGenerator::receiveClockTailFeedback(const CTFeedBack &feedback)
{
}

ClockTail ClockTailGenerator::getCurrentClockTail()
{
	return currentClockTail;
}

void ClockTailGenerator::deinitialise()
{
}

void ClockTailGenerator::addSpiritFile(InputFile &input)
{
	spiritFiles.push_back(input);
}

void ClockTailGenerator::addMixerFile(InputFile &input)
{
	mixerFiles.push_back(input);
}

void ClockTailGenerator::addNameFile(InputFile &input)
{
	nameFiles.push_back(input);
}

void ClockTailGenerator::print(std::ostream &str)
{
}

Selector &ClockTailGenerator::getSelector()
{
	return ctSelector;
}

void ClockTailGenerator::setSelector(Selector &selector)
{
	ctSelector = selector;
}
