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
		
		//get the name of the clocktail from the name components
		std::string getName() const;
		const std::vector<std::string> &getMixers() const;
		const std::vector<std::string> &getSpirits() const;

		void print(std::ostream &output) const;

		bool operator==(const ClockTail &rhs) const;
		bool operator!=(const ClockTail &rhs) const;
		
	private:
		std::vector<std::string> namecomponents;
		std::vector<std::string> spirits;
		std::vector<std::string> mixers;
};

#endif
