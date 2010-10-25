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
#include <boost/shared_ptr.hpp>

#include "ClockTailComponents.hpp"

using std::vector;
using std::ostream;
using boost::shared_ptr;

class ClockTail
{
	public:
		ClockTail();
		ClockTail(const ClockTail &rhs);
		virtual ~ClockTail();

		ClockTail &operator=(const ClockTail &rhs);

		void addMixer(shared_ptr<const Mixer> mixer);
		void addSpirit(shared_ptr<const Spirit> spirit);
		void addNameComponent(shared_ptr<const Name> name);
		
		//get the name of the clocktail from the name components
		Name getName() const;
		shared_ptr<const vector<shared_ptr<const Mixer> > > getMixers() const;
		shared_ptr<const vector<shared_ptr<const Spirit> > > getSpirits() const;

		void print(ostream &output) const;

		bool operator==(const ClockTail &rhs) const;
		bool operator!=(const ClockTail &rhs) const;
		
	private:
		shared_ptr<vector<shared_ptr<const Name> > > namecomponents;
		shared_ptr<vector<shared_ptr<const Spirit> > > spirits;
		shared_ptr<vector<shared_ptr<const Mixer> > > mixers;
};

#endif
