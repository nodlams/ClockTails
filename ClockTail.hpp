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

#include <vector>
#include <string>

class ClockTail
{
	public:
		ClockTail();
		ClockTail(const ClockTail &rhs);
		virtual ~ClockTail();

		ClockTail &operator=(const ClockTail &rhs);

		void addMixer(const std::string &mixer);
		void addSpirit(const std::string &spirit);
		void addNameComponent(const std::string &name);

		void setMixers(const std::vector<std::string> &mixers);
		void setSpirits(const std::vector<std::string> &spirits);
		void setNameComponents(const std::vector<std::string> &names);

		const std::vector<std::string> &getMixers();
		const std::vector<std::string> &getSpirits();
		const std::vector<std::string> &getNameComponents();

		void print(std::ostream &output);
		
	private:
		std::vector<std::string> namecomponents;
		std::vector<std::string> spirits;
		std::vector<std::string> mixers;
};

#endif
