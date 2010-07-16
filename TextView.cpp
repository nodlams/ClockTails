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
#include <iostream>

TextView::TextView(CTModelIface &theModel, CTControllerIface &theController)
	: model(theModel), controller(theController), menu(initMenus())
{
}

TextView::TextView(const TextView &rhs)
	: model(rhs.model), controller(rhs.controller), menu(initMenus())
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

void TextView::startInputLoop()
{
	bool quit=false;
	MenuBase::MenuBasePtr currentMenu = menu;
	while (!quit)
	{
		printMenu(currentMenu, std::cout);
		std::string input = getUserInput(std::cout, std::cin, "Enter Selection");
	}
}

void TextView::printMenu(MenuBase::MenuBasePtr theMenu, std::ostream &output)
{
	theMenu->print(output,1);
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
	MenuBase::MenuBasePtr itGen(new MenuItem("Generate", "Generate Clocktail", "g"));
	MenuBase::MenuBasePtr itQuit(new MenuItem("Quit", "Exit the program", "q"));
	root->addItem(itGen);
	root->addItem(itQuit);
	return root;
}
