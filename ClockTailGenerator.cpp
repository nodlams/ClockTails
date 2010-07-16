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
#include "CTFeedBack.hpp"
#include "ClockTail.hpp"

ClockTailGenerator::ClockTailGenerator()
{
}

ClockTailGenerator::~ClockTailGenerator()
{
}

void ClockTailGenerator::initialise()
{
}

void ClockTailGenerator::registerObserver(CTObserver &observer)
{
}

void ClockTailGenerator::generateNextClockTail()
{
}

void ClockTailGenerator::receiveClockTailFeedback(const CTFeedBack &feedback)
{
}

ClockTail ClockTailGenerator::getCurrentClockTail()
{
}

void ClockTailGenerator::deinitialise()
{
}
