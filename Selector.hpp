/*
 * =====================================================================================
 *
 *       Filename:  Selector.hpp
 *
 *    Description:  The base class for Selectors. The selector is the class
 *    that actually generates the clocktail, a class inheriting these methods
 *    should implement some means of generating clocktails.
 *
 *        Version:  1.0
 *        Created:  30/07/10 17:57:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (), James.Smaldon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __SELECTOR_HPP__
#define __SELECTOR_HPP__

#include <string>
#include <vector>
#include <stdexcept>

#include "InputFile.hpp"
#include "ClockTail.hpp"

class SelectorException : public std::runtime_error
{
	public:
		SelectorException(const char *what)
			: runtime_error(what) {}
		virtual ~SelectorException () throw () {}
};

class Selector
{
	public:
		Selector();
		virtual shared_ptr<const ClockTail> generateClockTail()=0; //throw SelectorException
		virtual void print(std::ostream &out) const=0;

	protected:
};

#endif
