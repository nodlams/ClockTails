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

ClockTailComponent::ClockTailComponent(const string value)
	: m_value(new string(value))
{
}

ClockTailComponent::~ClockTailComponent()
{
}

const string &ClockTailComponent::getValue() const
{
	return *m_value;
}

