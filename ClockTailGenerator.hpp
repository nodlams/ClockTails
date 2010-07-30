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
#include "ClockTail.hpp"
#include "InputFile.hpp"
#include <vector>
#include <iostream>
#include <string>

class CTFeedBack;
class CTObserver;
class Selector;

class ClockTailGenerator : public CTModelIface
{
	public:
		ClockTailGenerator(Selector &selector);
		ClockTailGenerator(const ClockTailGenerator &rhs);
		virtual ~ClockTailGenerator();

		ClockTailGenerator &operator=(const ClockTailGenerator &rhs);

		virtual void initialise();
		virtual void registerObserver(CTObserver &observer);
		//notify the observers that a new clocktail was generated
		virtual void notifyObservers();

		virtual void generateNextClockTail();
		virtual void print(std::ostream &out);

		virtual void receiveClockTailFeedback(const CTFeedBack &feedback);
		virtual ClockTail getCurrentClockTail();
		virtual void deinitialise();

		virtual void addSpiritFile(InputFile &input);
		virtual void addMixerFile(InputFile &input);
		virtual void addNameFile(InputFile &input);

		virtual void setSelector(Selector &selector);
		virtual Selector &getSelector();

	protected:
		std::vector<InputFile> spiritFiles, mixerFiles, nameFiles;
		std::vector<CTObserver *> observers;
		ClockTail currentClockTail;
		Selector &ctSelector;
};

#endif
