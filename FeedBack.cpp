/*
 * =====================================================================================
 *
 *       Filename:  FeedBack.cpp
 *
 *    Description:  Implementation of the FeedBack class 
 *
 *        Version:  1.0
 *        Created:  30/07/10 17:35:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <sstream>
#include "FeedBack.hpp"

FeedBack::FeedBack()
	: score(0)
{
}

FeedBack::~FeedBack()
{
}

unsigned int FeedBack::getScore() const
{
	return score;
}

void FeedBack::setScore(const unsigned int newScore)
{
	if (newScore > 10)
	{
		std::ostringstream str;
		str << score;
		throw InvalidScoreException(str.str());
	}
	this->score = newScore;
}
