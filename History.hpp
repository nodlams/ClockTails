/*
 * =====================================================================================
 *
 *       Filename:  History.hpp
 *
 *    Description:  This class records the history of generated clocktails. The
 *    class records which recipes have been generated, and which names have
 *    been generated. Ratings can be assigned to recipes and these ratings are
 *    also stored in the history. The clocktail generator updates the history
 *    with newly generated clocktails, and can use it to determine if a name
 *    has been generated already or not.
 *
 *        Version:  1.0
 *        Created:  25/07/10 21:20:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __HISTORY_HPP__
#define __HISTORY_HPP__

#include <unordered_map>
#include <vector>
#include <string>

#include "ClockTail.hpp"
#include "FeedBack.hpp"

class History
{
	public:
		History();
		virtual ~History();	

		/**
		 * Query the history to determine if a name has been generated already.
		 * @param nameComponents the strings making up the name.
		 * @return true if the name has been used before, false if it hasn't.
		 */
		bool nameHasBeenGenerated(const std::vector<std::string> &nameComponents) const;

		/**
		 * Query the history to determine if the recipe has been generated before or not.
		 * @param mixers The mixers going into the clocktail.
		 * @param spirits The spirits going int the clocktail.
		 */
		bool recipeHasBeenGenerated(const std::vector<std::string> &mixers,
					    const std::vector<std::string> &spirits) const;
		/**
		 * Record feedback for a clocktail.
		 *
		 * @param clockTail The clocktail which feedback will be generated for.
		 * @param feedback The feedback for the clocktail.
		 */
		void recordGeneratedClockTail(const ClockTail &clockTail, const FeedBack &feedback);

	private:
		std::unordered_map<std::string, FeedBack> recipeHistory;	
		std::unordered_map<std::string, FeedBack> nameHistory;
};

#endif
