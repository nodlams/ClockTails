/*
 * =====================================================================================
 *
 *       Filename:  ClockTail.hpp
 *
 *    Description:  represents a generated ClockTail
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:33:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __CLOCKTAIL_HPP__
#define __CLOCKTAIL_HPP__

class ClockTail
{
	public:
		ClockTail();
		ClockTail(const ClockTail &rhs);
		virtual ~ClockTail();

		ClockTail &operator=(const ClockTail &rhs);
	private:

};

#endif
