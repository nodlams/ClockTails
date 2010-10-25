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
#include <cstring>
#include <functional>

#include "ClockTail.hpp"
#include "FeedBack.hpp"

class History
{
	public:
		History();
		virtual ~History();	

		/**
		 * Record feedback for a clocktail.
		 *
		 * @param clockTail The clocktail which feedback will be generated for.
		 * @param feedback The feedback for the clocktail.
		 */
		void recordGeneratedClockTail(shared_ptr<const ClockTail> clockTail, shared_ptr<FeedBack> feedback);

	private:
		//hash function for ClockTail object
		struct ClockTailHash
		{
			size_t operator() (shared_ptr<const ClockTail> clockTail) const
			{
				std::hash<std::string>  strhasher;
				return strhasher(clockTail->getName().getValue());
			}
		};
		std::unordered_map<shared_ptr<const ClockTail>, shared_ptr<FeedBack>, ClockTailHash> clockTailFeedBack;
};

#endif
