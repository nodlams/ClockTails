/*
 * =====================================================================================
 *
 *       Filename:  NotImplementedException.hpp
 *
 *    Description:  Thrown if a method is not implemented in a class
 *
 *        Version:  1.0
 *        Created:  16/07/10 11:12:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __NOTIMPLEMENTEDEXCEPTION_HPP__
#define __NOTIMPLEMENTEDEXCEPTION_HPP__

#include <stdexcept>
#include <string>

class NotImplementedException : std::runtime_error
{
	public:
		NotImplementedException(const std::string &what)
			: std::runtime_error(what)
		{
		}
};

#endif
