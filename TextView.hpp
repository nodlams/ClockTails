/*
 * =====================================================================================
 *
 *       Filename:  TextView.hpp
 *
 *    Description:  The text based view for clocktails
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:47:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __TEXTVIEW_HPP__
#define __TEXTVIEW_HPP__

#include <string>
#include <ostream>
#include <istream>
#include <vector>

#include "MenuStructure.hpp"

class CTModelIface;
class CTControllerIface;

class TextView
{
	public:
		TextView(CTModelIface &model, CTControllerIface &controller);
		TextView(const TextView &rhs);
		virtual ~TextView();
		TextView &operator=(const TextView &rhs);

		/**
		 * start the main input loop, which interacts with the user performs calls on the model and controller accordingly.
		 */
		virtual void startInputLoop();

	private:
		virtual void printMenu(MenuBase::MenuBasePtr theMenu, std::ostream &stream);

		/**
		 * get input from the user, the method generates a prompt looking like the following on <output>:
		 * <promptString> [possibleChoice[0],...]:
		 *
		 * @param output The output ostream which the prompt is written to.
		 * @param input the input istream which the response is read from.
		 * @param promptString This string gets printed as the prefix of the user prompt
		 * the user can enter, if NULL then any string is valid.  if an invalid
		 * string is entered then the user is prompted to enter input again.
		 * These strings are also printed as the suffix of the prompt.
		 * @return the input string from the user
		 */
		virtual std::string getUserInput(std::ostream &output, std::istream &input, const char *promptString);

		/**
		 * Initialised the menu for the clocktails interface
		 * @return pointer to the root node of the menu structure
		 */
		virtual MenuBase::MenuBasePtr initMenus();

		CTModelIface &model;
		CTControllerIface &controller;

		//The root node for the menu
		MenuBase::MenuBasePtr menu;	
};

#endif
