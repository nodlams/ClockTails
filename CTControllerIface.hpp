/*
 * =====================================================================================
 *
 *       Filename:  CTControllerIface.hpp
 *
 *    Description:  Controller interface for clocktails, the controller knows about both the model and the view
 *
 *        Version:  1.0
 *        Created:  16/07/10 08:53:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __CTCONTROLLERIFACE_HPP__
#define __CTCONTROLLERIFACE_HPP__

class FeedBack;

class CTControllerIface
{
	public:
		virtual ~CTControllerIface(){}

		virtual void generateClockTail()=0;
		virtual void sendCTFeedBack(const FeedBack &feedback)=0;
		virtual void exit()=0;
};

#endif
