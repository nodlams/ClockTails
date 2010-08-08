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

#include "CombinationSet.hpp"

class ClockTailComponent : public Combinable
{
	public:
		virtual ~ClockTailComponent();
		virtual const string &getValue() const=0;
		virtual const string &getCombinable() const;
};

class Name : public ClockTailComponent
{
	public:
		Name(const string &value);
		virtual ~Name();

		virtual const string &getValue() const;

	protected:
		string name;
};

class Mixer : public ClockTailComponent
{
	public:
		Mixer(const string &value);
		virtual ~Mixer();

		virtual const string &getValue() const;

	protected:
		string mixer;
};

class Spirit : public ClockTailComponent
{
	public:
		Spirit(const string &value);
		virtual ~Spirit();

		virtual const string &getValue() const;

	protected:
		string spirit;
};

#endif
