/*
 * =====================================================================================
 *
 *       Filename:  ClockTail.cpp
 *
 *    Description:  Stores data relating to a single clocktail
 *
 *        Version:  1.0
 *        Created:  16/07/10 21:41:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#include <sstream>
#include <iterator>
#include "ClockTail.hpp"
#include "ClockTailComponents.hpp"

using std::ostringstream;

ClockTail::ClockTail()
{
}

ClockTail::ClockTail(const ClockTail &rhs)
	: namecomponents(rhs.namecomponents), spirits(rhs.spirits), mixers(rhs.mixers)
{
}

ClockTail::~ClockTail()
{
}

ClockTail &ClockTail::operator=(const ClockTail &rhs)
{
	if (this != &rhs)
	{
		ClockTail tmp(rhs);
		std::swap(this->namecomponents, tmp.namecomponents);
		std::swap(this->spirits, tmp.spirits);
		std::swap(this->mixers, tmp.mixers);
	}
	return *this;
}

void ClockTail::addMixer(shared_ptr<const Mixer> mixer)
{
	mixers->push_back(mixer);
}

void ClockTail::addSpirit(shared_ptr<const Spirit> spirit)
{
	spirits->push_back(spirit);
}

void ClockTail::addNameComponent(shared_ptr<const Name> name)
{
	namecomponents->push_back(name);
}

shared_ptr<const vector<shared_ptr<const Mixer> > > ClockTail::getMixers() const
{
	return mixers;
}

shared_ptr<const vector<shared_ptr<const Spirit> > > ClockTail::getSpirits() const
{
	return spirits;
}

Name ClockTail::getName() const
{
	if (namecomponents->size() > 0)
	{
		ostringstream oss;
		for (vector<shared_ptr<const Name> >::const_iterator it = namecomponents->begin(); it != namecomponents->end(); ++it)
			oss << (*it)->getValue() << " ";
		string tmpName = oss.str();
		//chop off that last space from the name
		return tmpName.substr(0, tmpName.length()-2);
	}
	return string("");
}

bool ClockTail::operator==(const ClockTail &rhs) const
{
	return this->getName().getValue() == rhs.getName().getValue();
}

bool ClockTail::operator!=(const ClockTail &rhs) const
{
	return !(*this == rhs);
}
