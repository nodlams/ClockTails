/*
 * =====================================================================================
 *
 *       Filename:  TextView.cpp
 *
 *    Description:  Text based interface for clocktails
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:57:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#include "TextView.hpp"
#include "CTModelIface.hpp"
#include "CTControllerIface.hpp"
#include "ClockTail.hpp"
#include <iostream>
#include <sstream>

const std::string TextView::GENERATEN = "Generate";
const std::string TextView::QUITN = "Quit";

TextView::TextView(CTModelIface &theModel, CTControllerIface &theController)
	: model(theModel), controller(theController), menu(initMenus()), currentMenu(menu)
{

}

TextView::TextView(const TextView &rhs)
	: model(rhs.model), controller(rhs.controller), menu(initMenus()), currentMenu(menu)
{
}

TextView::~TextView()
{
}

TextView &TextView::operator=(const TextView &rhs)
{
	if (this != &rhs)
	{
		//don't copy and swap as we don't want to slice objects, since we're
		//just assigning refs/pointers here it can't except
		this->model = rhs.model;
		this->controller = rhs.controller;
		//because we're using shared pointers we can do this, but it would be
		//better to deep copy the structure instead.
		this->menu = rhs.menu;
	}

	return *this;
}

void TextView::handleSelection(MenuBase::MenuBasePtr item)
{
	MenuItem *itemp = dynamic_cast<MenuItem *>(item.get());
	if (itemp != NULL)
	{
		//it's an item.
		const std::string itemName = item->getName();
		if (itemName == GENERATEN)
		{
			controller.generateClockTail();	
		}
		else if (itemName == QUITN)
		{
			controller.exit();	
		}	
	}
	else
	{
		Menu *mtemp = dynamic_cast<Menu *>(item.get());
		if (mtemp != NULL)
		{
			//it's a menu, replace the current one with this one.
			currentMenu = item;
		}
	}
}

void TextView::startInputLoop()
{
	bool quit=false;
	while (!quit)
	{
		printClockTails(std::cout);
		printMenu(currentMenu, std::cout);
		std::string input = getUserInput(std::cout, std::cin, "Enter Selection");
		//check if the input string is a valid identifier for a menu item.
		MenuBase::MenuBasePtr item = menu->getItem(input);

		if (item.get() != NULL)
		{
			handleSelection(item);
			//quit is a special case here:
			quit = item->getName() == QUITN;
		}
	}
}

void TextView::updateClockTail()
{
	ClockTail newOne = model.getCurrentClockTail();
	//update the list of generated clock tails
	updateClocktailsList(newOne);
}

void TextView::printMenu(MenuBase::MenuBasePtr theMenu, std::ostream &output)
{
	theMenu->print(output,1);
}

void TextView::printClockTail(std::ostream &output, ClockTail &clocktail)
{
	const std::vector<std::string> &mixers = clocktail.getMixers();
	const std::vector<std::string> &spirits = clocktail.getSpirits();
	const std::vector<std::string> &names = clocktail.getNameComponents();
	
	std::ostringstream nameAcc;

	for (std::vector<std::string>::const_iterator it = names.begin(); it != names.end(); ++it)
		nameAcc << (*it) << " ";  
	nameAcc << ": ";
	for (std::vector<std::string>::const_iterator it = spirits.begin(); it != spirits.end(); ++it)
		nameAcc << (*it) << ", ";
	for (std::vector<std::string>::const_iterator it = mixers.begin(); it != mixers.end(); ++it)
		nameAcc << (*it) << ", ";

	output << nameAcc.str() << std::endl;
}

void TextView::printClockTails(std::ostream &output)
{
	//print last first, as doing it the other way feels wrong
	for (std::list<ClockTail>::reverse_iterator it = lastNClockTails.rbegin(); it != lastNClockTails.rend(); ++it)
	{
		printClockTail(output, (*it));
	}	
}

std::string TextView::getUserInput(std::ostream &output, std::istream &input, const char *promptString)
{
	output << promptString << ": ";
	std::string userInput;
	input >> userInput;
	return userInput;
}

MenuBase::MenuBasePtr TextView::initMenus()
{
	MenuBase::MenuBasePtr root(new Menu("ClockTails", "ClockTails Main Menu", "m"));			
	MenuBase::MenuBasePtr itGen(new MenuItem(GENERATEN.c_str(), "Generate Clocktail", "g"));
	MenuBase::MenuBasePtr itQuit(new MenuItem(QUITN.c_str(), "Exit the program", "q"));
	root->addItem(itGen);
	root->addItem(itQuit);

	return root;
}

void TextView::updateClocktailsList(ClockTail &newOne)
{
	lastNClockTails.push_front(newOne);
	if (lastNClockTails.size() > STOREDCTCOUNT)
	{
		lastNClockTails.pop_back();
	}
}
