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
#include "History.hpp"

#include <vector>
#include <iostream>
#include <string>

class FeedBack;
class CTObserver;
class Selector;

using namespace std;

class GenerateException : public runtime_error
{
	public:
		GenerateException(const char *what)
			: runtime_error(what) {}
		virtual ~GenerateException() throw () {}
};

class ClockTailGenerator : public CTModelIface
{
	public:
		typedef vector<Mixer> MixerSet;
		typedef vector<Name> NameSet;
		typedef vector<Spirit> SpiritSet;

	public:
		ClockTailGenerator(Selector &selector, History &history);
		ClockTailGenerator(const ClockTailGenerator &rhs);
		virtual ~ClockTailGenerator();

		ClockTailGenerator &operator=(const ClockTailGenerator &rhs);

		virtual void initialise();
		virtual void registerObserver(CTObserver &observer);
		//notify the observers that a new clocktail was generated
		virtual void notifyObservers();

		virtual void generateNextClockTail(); //throw GenerateException
		virtual void print(ostream &out);

		virtual void receiveClockTailFeedback(const FeedBack &feedback);
		virtual ClockTail getCurrentClockTail();
		virtual void deinitialise();

		virtual void addSpiritFile(InputFile &input);
		virtual void addMixerFile(InputFile &input);
		virtual void addNameFile(InputFile &input);

		virtual void setSelector(Selector &selector);
		virtual Selector &getSelector();

	protected:
		vector<InputFile> spiritFiles, mixerFiles, nameFiles;
		vector<CTObserver *> observers;
		ClockTail currentClockTail;
		Selector &ctSelector;
		History &ctHistory;
};

#endif
