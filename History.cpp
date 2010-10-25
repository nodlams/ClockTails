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

void History::recordGeneratedClockTail(shared_ptr<const ClockTail> clockTail, shared_ptr<FeedBack> feedback)
{
	clockTailFeedBack[clockTail] = feedback;
}
