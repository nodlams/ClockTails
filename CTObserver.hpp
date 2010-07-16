/*
 * =====================================================================================
 *
 *       Filename:  CTObserver.hpp
 *
 *    Description:  Observer interface for clocktails views
 *
 *        Version:  1.0
 *        Created:  16/07/10 08:51:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __CTOBSERVER_HPP__
#define __CTOBSERVER_HPP__

public class CTObserver
{
	public:
		virtual ~CTObserver();
		
		//called by the model when a new clocktail has been generated.
		virtual void updateClockTail()=0;
};

#endif
