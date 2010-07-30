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

#include <unordered_map>

class History
{
	public:
		History();
		virtual ~History();	

		//use these methods to check whether a name or recipe has been generated already
		bool nameHasBeenGenerated(const std::vector<std::string> &nameComponents);
		bool recipeHasBeenGenerated(const std::vector<std::string> &mixers,
									const std::vector<std::string> &spirits);

		void recordGeneratedClockTail(const ClockTail &clockTail, RecipeFeedback feedback=RecipeFeedback());

	private:
		std::tr1::unordered_map<string, RecipeFeedback> recipeHistory;	
		std::tr1::unordered_map<string, NameFeedback> nameHistory;

};
