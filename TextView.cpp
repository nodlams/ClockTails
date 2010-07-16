/*
 * =====================================================================================
 *
 *       Filename:  TextView.cpp
 *
 *    Description:  Text based interface for clocktails
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:57:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#include "TextView.hpp"

TextView::TextView(CTModelIface &theModel, CTControllerIface &theController)
	: model(theModel), controller(theController)
{
}

TextView::TextView(const TextView &rhs)
	: model(rhs.model), controller(rhs.controller)
{
}

TextView::~TextView()
{
}

TextView &TextView::operator=(const TextView &rhs)
{
}

void TextView::startInputLoop()
{
}

std::string TextView::getUserInput(std::ostream &output, std::istream &input, const char *promptString, const std::vector<std::string> *possibleChoices)
{

}
