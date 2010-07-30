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
#include "InputFile.hpp"
#include "ClockTail.hpp"

class Selector
{
	public:
		Selector();
		virtual ClockTail generateClockTail(const std::vector<InputFile> &names, const std::vector<InputFile> &mixers, const std::vector<InputFile> &spirits)=0;

	protected:
};

#endif
