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

FeedBack::FeedBack(const FeedBack &rhs)
	: score(rhs.score)
{
}

FeedBack::~FeedBack()
{
}

FeedBack &FeedBack::operator=(const FeedBack &rhs)
{
	FeedBack tmp(rhs);

	if (&rhs != this)
	{
		std::swap(this->score, tmp.score);	
	}
	return *this;
}

unsigned int FeedBack::getScore()
{
	return score;
}

void FeedBack::setScore(const unsigned int score)
{
	if (score > 10)
	{
		std::ostringstream str;
		str << score;
		throw InvalidScoreException(str.str());
	}
	this->score = score;
}
