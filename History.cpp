/*
 * =====================================================================================
 *
 *       Filename:  History.cpp
 *
 *    Description:  Implementation of the ClockTails History class
 *
 *        Version:  1.0
 *        Created:  30/07/10 17:08:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "History.hpp"
#include "FeedBack.hpp"

History::History()
{
}

History::~History()
{
}

bool History::nameHasBeenGenerated(const ClockTail &clockTail) const
{
	return clockTailFeedBack.count(clockTail) > 0;
}

bool History::recipeHasBeenGenerated(const ClockTail &clockTail) const
{
	return false;
}

void History::recordGeneratedClockTail(const ClockTail &clockTail, const FeedBack &feedback)
{
	clockTailFeedBack[clockTail] = feedback;
}
