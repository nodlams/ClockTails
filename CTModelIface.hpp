/*
 * =====================================================================================
 *
 *       Filename:  CTModelIface.hpp
 *
 *    Description:  Interface for the clocktails model
 *
 *        Version:  1.0
 *        Created:  16/07/10 08:42:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __CTMODELIFACE_HPP__
#define __CTMODELIFACE_HPP__

class CTModelIface
{
	public:
		virtual ~CTModelIface();

		//pure virtual methods
		virtual void initialise()=0;
		virtual void registerObserver(CTObserver &observer)=0;
		//ask the model to generate a new clocktail
		virtual void generateNextClockTail()=0;
		//take feedback regarding the current clocktail. 
		virtual void receiveClockTailFeedback(const CTFeedBack &feedback)=0;
		//return the clocktail that was just generate, or generate one and
		//return if there is no current clocktail.
		virtual void getCurrentClockTail()=0;
		//called when the program will exit.
		virtual void deinitialise()=0;
		
	private:
		//make constructor private as we never want to instantiate this.
		CTModelIface();
};

#endif
