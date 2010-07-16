/*
 * =====================================================================================
 *
 *       Filename:  ClockTailGenerator.hpp
 *
 *    Description:  The class that does all of the clocktail generation, an implementation of the CTModelIface
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:17:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __CLOCKTAILGENERATOR_HPP__
#define __CLOCKTAILGENERATOR_HPP__

#include "CTModelIface.hpp"

class CTFeedBack;
class CTObserver;
class ClockTail;

class ClockTailGenerator : public CTModelIface
{
	public:
		ClockTailGenerator();
		ClockTailGenerator(const ClockTailGenerator &rhs);
		virtual ~ClockTailGenerator();

		ClockTailGenerator &operator=(const ClockTailGenerator &rhs);

		virtual void initialise();
		virtual void registerObserver(CTObserver &observer);
		virtual void generateNextClockTail();
		virtual void receiveClockTailFeedback(const CTFeedBack &feedback);
		virtual ClockTail getCurrentClockTail();
		virtual void deinitialise();

	private:

};

#endif
