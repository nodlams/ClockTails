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

const std::vector<std::string> &ClockTail::getMixers()
{
	return mixers;
}

const std::vector<std::string> &ClockTail::getSpirits()
{
	return spirits;
}

const std::vector<std::string> &ClockTail::getNameComponents()
{
	return namecomponents;
}
