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
#include "FeedBack.hpp"

CTController::CTController(shared_ptr<CTModelIface> theModel)
	: model(theModel), view(new TextView(theModel, shared_from_this()))
{

}

CTController::CTController(const CTController &rhs)
	: model(rhs.model), view(rhs.view)
{

}

CTController::~CTController()
{

}

CTController &CTController::operator=(const CTController &rhs)
{
	if (this != &rhs)
	{
		CTController tmp(rhs);	
		this->model = tmp.model;
		std::swap(this->view, tmp.view);
	}

	return *this;
}

void CTController::generateClockTail()
{
	model->generateNextClockTail();
}

void CTController::sendCTFeedBack(shared_ptr<const FeedBack> feedback)
{
	model->receiveClockTailFeedback(feedback);
}

void CTController::exit()
{
	//do cleanup etc here
}
