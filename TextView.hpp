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
#include "CTObserver.hpp"

class CTModelIface;
class CTControllerIface;
class ClockTail;

#include <string>
#include <list>
#include <stdexcept>

/*
 * General exception for the TextView, the message passed as the "what"
 * parameter will be displayed to the user.
 */
class DisplayException : public std::runtime_error
{
	public:
		DisplayException(const std::string &what)
			: std::runtime_error(what)
		{ }
};

class TextView : public CTObserver
{
	public:
		static const std::string GENERATEN;
		static const std::string QUITN;
		static const std::string FEEDBACKN;

		//store this many of the previously generated clocktails
		static const size_t STOREDCTCOUNT=10;

	public:
		TextView(CTModelIface &model, CTControllerIface &controller);
		TextView(const TextView &rhs);
		virtual ~TextView();
		TextView &operator=(const TextView &rhs);

		/**
		 * start the main input loop, which interacts with the user performs calls on the model and controller accordingly.
		 */
		virtual void startInputLoop();

		/**
		 * Called by the model when it's generated a new clock Tail.
		 */
		virtual void updateClockTail();

	private:
		virtual void printGeneratorInfo(std::ostream &stream);
		virtual FeedBack getUserFeedBack(std::istream &in, std::ostream &out);
		
		/**
		 * Print the menu to the supplied stream
		 *
		 * @param theMenu the menu item to print.
		 * @param stream the output stream to print it to
		 */
		virtual void printMenu(MenuBase::MenuBasePtr theMenu, std::ostream &stream);

		/**
		 * print a single clocktail
		 * @param the output stream
		 * @param the clocktail to print
		 */
		virtual void printClockTail(std::ostream &output, ClockTail &clocktail);
		virtual void printClockTail(std::ostream &output, ClockTail &clocktail, FeedBack &feedback);

		/**
		 * Print the clock tails in the history
		 */
		virtual void printClockTails(std::ostream &output);

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

		/**
		 * Handle a menu selection, and perform the appropriate action.
		 * @param item the menu item which is to be handled
		 * @in the input stream, used to read input from the user.
		 * @out the output stream, used to output text to the user.
		 */
		virtual void handleSelection(MenuBase::MenuBasePtr item, std::istream &in, std::ostream &out);

		/**
		 * Update the list of the last 3 clocktails generated.
		 */
		virtual void updateClocktailsList(ClockTail &newOne);

		/**
		 * Clears the terminal
		 */
		virtual void clearScreen();

		/**
		 * Prints a happy shiny header
		 */
		virtual void printHeader(std::ostream &output);

		CTModelIface &model;
		CTControllerIface &controller;

		//The root node for the menu
		MenuBase::MenuBasePtr menu;	
		//Pointer to the current menu we are displaying to the user
		MenuBase::MenuBasePtr currentMenu;

		std::list<ClockTail> lastNClockTails;
		std::list<FeedBack> lastNFeedBacks;
};

#endif
