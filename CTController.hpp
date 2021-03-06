/*
 * =====================================================================================
 *
 *       Filename:  TextBasedInterface.hpp
 *
 *    Description:  The controller for a text based interface to clocktails 
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:37:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __TEXTBASEDINTERFACE_HPP__
#define __TEXTBASEDINTERFACE_HPP__

#include "CTControllerIface.hpp"
#include "TextView.hpp"

#include <boost/enable_shared_from_this.hpp>

class CTModelIface;
class FeedBack;

class CTController : public CTControllerIface, boost::enable_shared_from_this<CTController>
{
	public:
		CTController(shared_ptr<CTModelIface> model);
		CTController(const CTController &rhs);
		virtual ~CTController();

		CTController &operator=(const CTController &rhs);

		virtual void generateClockTail();
		virtual void sendCTFeedBack(shared_ptr<const FeedBack> feedback);
		virtual void exit();

	private:
		shared_ptr<CTModelIface> model;
		shared_ptr<TextView> view;
};

#endif

