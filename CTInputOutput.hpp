/*
 * =====================================================================================
 *
 *       Filename:  CTInputOutput.hpp
 *
 *    Description:  The view for the Clock Tails generator.
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:04:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __CTINPUTOUTPUT_HPP__
#define __CTINPUTOUTPUT_HPP__

#include "CTObserver.hpp"

class CTModelIface;
class CTControllerIface;

class CTInputOutput : public CTObserver
{
	public:
		CTInputOutput(CTControllerIface &controller, CTModelIface &model);
		virtual ~CTInputOutput();

		//called by model when new clocktail has been generated.
		virtual void updateClockTail();

	private:
		CTControllerIface &controller;
		CTModelIface &model;
};

#endif
