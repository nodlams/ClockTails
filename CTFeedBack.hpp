/*
 * =====================================================================================
 *
 *       Filename:  CTFeedBack.hpp
 *
 *    Description:  Class containing feedback for a ClockTail
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:28:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __CTFEEDBACK_HPP__
#define __CTFEEDBACK_HPP__

class CTFeedBack
{
	public:
		CTFeedBack();
		CTFeedBack(const CTFeedBack &rhs);
		virtual ~CTFeedBack();

		CTFeedBack &operator=(const CTFeedBack &rhs);

	private:
};

#endif
