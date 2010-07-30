/*
 * =====================================================================================
 *
 *       Filename:  CTFeedBack.hpp
 *
 *    Description:  A class representing feedback, either for ClockTails or Names.
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:28:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __FEEDBACK_HPP__
#define __FEEDBACK_HPP__

#include <stdexcept>

class InvalidScoreException : public std::runtime_error
{
	public:
		InvalidScoreException(const std::string &what)
			: std::runtime_error(what)
		{
		}
};

class FeedBack
{
	public:
		FeedBack();
		FeedBack(const FeedBack &rhs);
		virtual ~FeedBack();

		FeedBack &operator=(const FeedBack &rhs);

		/*
		 * Get the feedback score
		 * @return the score between worst (0) and best (10)
		 */
		unsigned int getScore();
		/**
		 * Set the feedback score
		 * @param score the feedback score, should be between 0 (worst score) and 10 (best score).
		 * If the score is not within this range, an InvalidScoreException is thrown.
		 */
		void setScore(const unsigned int score); //throw InvalidScoreException

	private:
		unsigned int score;	
};

#endif
