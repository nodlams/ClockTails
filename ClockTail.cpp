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

void ClockTail::addMixer(const std::string &mixer)
{
	mixers.push_back(mixer);
}

void ClockTail::addSpirit(const std::string &spirit)
{
	spirits.push_back(spirit);
}

void ClockTail::addNameComponent(const std::string &name)
{
	namecomponents.push_back(name);
}

void ClockTail::setMixers(const std::vector<std::string> &mixers)
{
	this->mixers = mixers;	
}

void ClockTail::setSpirits(const std::vector<std::string> &spirits)
{
	this->spirits = spirits;
}

void ClockTail::setNameComponents(const std::vector<std::string> &names)
{
	this->namecomponents = names;
}

const std::vector<std::string> &ClockTail::getMixers() const
{
	return mixers;
}

const std::vector<std::string> &ClockTail::getSpirits() const
{
	return spirits;
}

std::string ClockTail::getName() const
{
	if (namecomponents.size() > 0)
	{
		std::ostringstream oss;
		copy(namecomponents.begin(), namecomponents.end(), std::ostream_iterator<std::string>(oss, " "));	
		std::string tmpName = oss.str();
		//chop off that last space from the name
		return tmpName.substr(0, tmpName.length()-2);
	}
	return std::string("");
}

bool ClockTail::operator==(const ClockTail &rhs) const
{
	return this->getName() == rhs.getName();
}

bool ClockTail::operator!=(const ClockTail &rhs) const
{
	return !(*this == rhs);
}
