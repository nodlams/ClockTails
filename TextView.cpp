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
#include <stdlib.h>

const std::string TextView::GENERATEN = "Generate";
const std::string TextView::QUITN = "Quit";
const std::string TextView::FEEDBACKN = "Rate";

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

void TextView::handleSelection(MenuBase::MenuBasePtr item, std::istream &in, std::ostream &out)
{
	MenuItem *itemp = dynamic_cast<MenuItem *>(item.get());
	if (itemp != NULL)
	{
		//it's an item.
		const std::string itemName = item->getName();
		if (itemName == GENERATEN)
		{
			//send feedback for the last clocktail, if there is one.
			if (lastNClockTails.size() > 0)
			{
				//if no feedback was provided, then the default rating of 0 will be assigned to the clocktail.
				controller.sendCTFeedBack(lastNFeedBacks.front());
			}
			controller.generateClockTail();	
		}
		else if (itemName == QUITN)
		{
			controller.exit();	
		}	
		else if (itemName == FEEDBACKN)
		{
			if (lastNClockTails.size() == 0)
				throw DisplayException("No clocktail to provide feedback for.");
			FeedBack &firstFeedBack = *lastNFeedBacks.begin();
			firstFeedBack = getUserFeedBack(in,out);
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
		try
		{
			clearScreen();
			printHeader(std::cout);
			printGeneratorInfo(std::cout);
			std::cout << std::endl;
			printClockTails(std::cout);
			std::cout << std::endl;
			printMenu(currentMenu, std::cout);

			std::string input = getUserInput(std::cout, std::cin, "Enter Selection");
			//check if the input string is a valid identifier for a menu item.
			MenuBase::MenuBasePtr item = menu->getItem(input);

			if (item.get() != NULL)
			{
				handleSelection(item, std::cin, std::cout);
				//quit is a special case here:
				quit = item->getName() == QUITN;
			}
		}
		catch(DisplayException e)
		{
			std::cout << e.what() << std::endl;
		}
		catch(...)
		{
			std::cout << "An unexpected event has occured, remain indoors!" << std::endl;
		}
	}
}

void TextView::updateClockTail()
{
	ClockTail newOne = model.getCurrentClockTail();
	//update the list of generated clock tails
	updateClocktailsList(newOne);
}

void TextView::printGeneratorInfo(std::ostream &out)
{
	out << "Using Generator: ";
	model.print(out);
	out << std::endl;
}

FeedBack TextView::getUserFeedBack(std::istream &in, std::ostream &out)
{
	bool valid = false;	
	//default score of 0.
	int value = 0;

	do 
	{
		out << "Please rate clocktail from 0 (worst) to 9 (best), or type q to cancel: ";
		std::string inputStr;
		in >> inputStr;

		if (inputStr == "q")
			break;

		std::istringstream iss(inputStr);

		valid = (iss >> value) && value >= 0 && value < 10;
	} while (!valid);

	//score will be default (0) or that provided by the user.
	//there will always be at least one element in the list, as one is
	//added whenever a clocktail is generated, and it is not possible to
	//provide feedback if no clocktails exist. Having said that...
	FeedBack theFeedBack;
	theFeedBack.setScore(value);

	return theFeedBack;
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

	output << nameAcc.str();
}

void TextView::printClockTail(std::ostream &output, ClockTail &clocktail, FeedBack &feedback)
{
	printClockTail(output, clocktail);	
	output << " (" << feedback.getScore() << ").";
}

void TextView::printClockTails(std::ostream &output)
{
	//print last first, as doing it the other way feels wrong
	std::list<FeedBack>::reverse_iterator feedback = lastNFeedBacks.rbegin();
	for (std::list<ClockTail>::reverse_iterator it = lastNClockTails.rbegin(); it != lastNClockTails.rend(); ++it)
	{
		if (feedback != lastNFeedBacks.rend())
		{
			printClockTail(output, (*it), (*feedback));
			feedback++;
		}
		else
		{
			printClockTail(output, (*it));
		}
		output << std::endl;
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
	MenuBase::MenuBasePtr itFeedback(new MenuItem(FEEDBACKN.c_str(), "Rate last clocktail", "r"));
	MenuBase::MenuBasePtr itQuit(new MenuItem(QUITN.c_str(), "Exit the program", "q"));
	root->addItem(itGen);
	root->addItem(itFeedback);
	root->addItem(itQuit);

	return root;
}

void TextView::updateClocktailsList(ClockTail &newOne)
{
	//store the current Feedback.
	lastNFeedBacks.push_front(FeedBack());
	lastNClockTails.push_front(newOne);

	if (lastNClockTails.size() > STOREDCTCOUNT)
		lastNClockTails.pop_back();

	//lastNFeedBacks doesn't include feedback for the current clocktail.
	if (lastNFeedBacks.size() > STOREDCTCOUNT)
		lastNFeedBacks.pop_back();
}

void TextView::clearScreen()
{
	//I don't want to bring in curses or anything like that here, so lets do
	//something dangerous and unportable instead! :-)
	int retval = system("clear");
	if (retval != 0)
		std::cerr << "Error! clear screen command failed to execute!" << std::endl;
}

void TextView::printHeader(std::ostream &out)
{
	out << "Welcome to ClockTails version 0.1" << std::endl;
}
