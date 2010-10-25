/*
 * =====================================================================================
 *
 *       Filename:  ClockTailComponents.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/08/10 23:24:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __CLOCKTAILCOMPONENTS_HPP__
#define __CLOCKTAILCOMPONENTS_HPP__

#include <string>
#include <boost/shared_ptr.hpp>

#include "CombinationSet.hpp"

class ClockTailComponent
{
	public:
		ClockTailComponent(const string value);
		virtual ~ClockTailComponent();
		virtual const string &getValue() const;
	private:
		boost::shared_ptr<string> m_value;
};

typedef ClockTailComponent Spirit, Mixer, Name;


#endif
