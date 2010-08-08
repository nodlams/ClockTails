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

#include "ClockTailComponents.hpp"

using namespace std;

class ClockTail
{
	public:
		ClockTail();
		ClockTail(const ClockTail &rhs);
		virtual ~ClockTail();

		ClockTail &operator=(const ClockTail &rhs);

		void addMixer(const Mixer &mixer);
		void addSpirit(const Spirit &spirit);
		void addNameComponent(const Name &name);

		void setMixers(const vector<Mixer> &mixers);
		void setSpirits(const vector<Spirit> &spirits);
		void setNameComponents(const vector<Name> &names);
		
		//get the name of the clocktail from the name components
		Name getName() const;
		const vector<Mixer> &getMixers() const;
		const vector<Spirit> &getSpirits() const;

		void print(ostream &output) const;

		bool operator==(const ClockTail &rhs) const;
		bool operator!=(const ClockTail &rhs) const;
		
	private:
		vector<Name> namecomponents;
		vector<Spirit> spirits;
		vector<Mixer> mixers;
};

#endif
