/*
 * =====================================================================================
 *
 *       Filename:  ClockTailComponents.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/08/10 23:30:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#include "ClockTailComponents.hpp"

ClockTailComponent::~ClockTailComponent()
{
}

const string &ClockTailComponent::getCombinable() const
{
	return getValue();
}

Name::Name(const string &value)
	: name(value)
{
}

Name::~Name()
{
}

const string &Name::getValue() const
{
	return name;
}

Mixer::Mixer(const string &value)
	: mixer(value)
{
}

Mixer::~Mixer()
{
}

const string &Mixer::getValue() const
{
	return mixer;
}

Spirit::Spirit(const string &value)
	: spirit(value)
{
}

Spirit::~Spirit()
{
}

const string &Spirit::getValue() const
{
	return spirit;
}
