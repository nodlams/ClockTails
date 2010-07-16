/*
 * =====================================================================================
 *
 *       Filename:  CTController.cpp
 *
 *    Description:  The controller for a text based interface to clocktails
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:44:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#include "CTController.hpp"
#include "TextView.hpp"
#include "CTModelIface.hpp"
#include "CTFeedBack.hpp"

CTController::CTController(CTModelIface &theModel)
	: model(theModel), view(theModel, *this)
{

}

CTController::CTController(CTController &rhs)
	: model(rhs.model), view(rhs.view)
{

}

CTController::~CTController()
{

}

CTController &CTController::operator=(const CTController &rhs)
{

}

void CTController::generateClockTail()
{

}

void CTController::sendCTFeedBack(const CTFeedBack &feedback)
{

}

void CTController::exit()
{

}
