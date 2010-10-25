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

class GenerateException : public std::runtime_error
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
		ClockTailGenerator(shared_ptr<Selector> selector, shared_ptr<History> history);
		ClockTailGenerator(const ClockTailGenerator &rhs);
		virtual ~ClockTailGenerator();

		ClockTailGenerator &operator=(const ClockTailGenerator &rhs);

		virtual void initialise();
		virtual void registerObserver(shared_ptr<CTObserver> observer);
		//notify the observers that a new clocktail was generated
		virtual void notifyObservers();

		virtual void generateNextClockTail(); //throw GenerateException
		virtual void print(ostream &out) const;

		virtual void receiveClockTailFeedback(shared_ptr<FeedBack> feedback);
		virtual shared_ptr<const ClockTail> getCurrentClockTail() const;
		virtual void deinitialise();

		virtual void addSpiritFile(shared_ptr<const InputFile> input);
		virtual void addMixerFile(shared_ptr<const InputFile> input);
		virtual void addNameFile(shared_ptr<const InputFile> input);

		virtual void setSelector(shared_ptr<Selector> selector);
		virtual shared_ptr<Selector> getSelector();

	protected:
		vector<shared_ptr<const InputFile> > spiritFiles, mixerFiles, nameFiles;
		vector<shared_ptr<CTObserver> > observers;
		shared_ptr<const ClockTail> currentClockTail;
		shared_ptr<Selector> ctSelector;
		shared_ptr<History> ctHistory;
};

#endif
