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
#include "ClockTailGenerator.hpp"
#include <iostream>
#include <sstream>
#include <iterator>
#include <stdlib.h>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

const string TextView::GENERATEN = "Generate";
const string TextView::QUITN = "Quit";
const string TextView::FEEDBACKN = "Rate";

using std::istream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::list;
using std::ostringstream;

using boost::shared_ptr;
using boost::make_shared;

TextView::TextView(shared_ptr<CTModelIface> theModel, shared_ptr<CTControllerIface> theController)
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

void TextView::handleSelection(MenuBase::MenuBasePtr item, istream &in, ostream &out)
{
	MenuItem *itemp = dynamic_cast<MenuItem *>(item.get());
	if (itemp != NULL)
	{
		//it's an item.
		const string itemName = item->getName();
		if (itemName == GENERATEN)
		{
			//send feedback for the last clocktail, if there is one.
			if (lastNClockTails.size() > 0)
			{
				//if no feedback was provided, then the default rating of 0 will be assigned to the clocktail.
				controller->sendCTFeedBack(lastNFeedBacks.front());
			}
			controller->generateClockTail();	
		}
		else if (itemName == QUITN)
		{
			controller->exit();	
		}	
		else if (itemName == FEEDBACKN)
		{
			if (lastNClockTails.size() == 0)
				throw DisplayException("No clocktail to provide feedback for.");
			shared_ptr<FeedBack> firstFeedBack = *lastNFeedBacks.begin();
			(*firstFeedBack) = getUserFeedBack(in,out);
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
			printHeader(cout);
			printGeneratorInfo(cout);
			cout << endl;
			printClockTails(cout);
			cout << endl;
			printMenu(currentMenu, cout);

			string input = getUserInput(cout, cin, "Enter Selection");
			//check if the input string is a valid identifier for a menu item.
			MenuBase::MenuBasePtr item = menu->getItem(input);

			if (item.get() != NULL)
			{
				handleSelection(item, cin, cout);
				//quit is a special case here:
				quit = item->getName() == QUITN;
			}
		}
		catch(GenerateException e)
		{
			cout << e.what() << endl;
			cout << "Press ENTER to continue" << endl;
			cin.ignore();
			cin.get();
		}
		catch(DisplayException e)
		{
			cout << e.what() << endl;
			//pause the loop until the user presses a key
			cout << "Press ENTER to continue" << endl;
			cin.ignore();
			cin.get();
		}
		catch(...)
		{
			cout << "An unexpected event has occured, remain indoors!" << endl;
			cout << "Press ENTER to continue" << endl;
			cin.ignore();
			cin.get();
		}
	}
}

void TextView::updateClockTail()
{
	shared_ptr<const ClockTail> newOne = model->getCurrentClockTail();
	//update the list of generated clock tails
	updateClocktailsList(newOne);
}

void TextView::printGeneratorInfo(ostream &out)
{
	out << "Using Generator: ";
	model->print(out);
	out << endl;
}

FeedBack TextView::getUserFeedBack(istream &in, ostream &out)
{
	bool valid = false;	
	//default score of 0.
	int value = 0;

	do 
	{
		out << "Please rate clocktail from 0 (worst) to 9 (best), or type q to cancel: ";
		string inputStr;
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

void TextView::printMenu(MenuBase::MenuBasePtr theMenu, ostream &output)
{
	theMenu->print(output,1);
}

void TextView::printClockTail(ostream &output, shared_ptr<const ClockTail> clocktail)
{
	shared_ptr<const vector<shared_ptr<const Mixer> > > mixers = clocktail->getMixers();
	shared_ptr<const vector<shared_ptr<const Spirit> > > spirits = clocktail->getSpirits();
	
	ostringstream nameAcc;
	nameAcc << clocktail->getName().getValue();

	nameAcc << ": ";
//	copy(spirits.begin(), spirits.end(), ostream_iterator<string>(nameAcc, ", "));
//	copy(mixers.begin(), mixers.end(), ostream_iterator<string>(nameAcc, ", "));
	
	//cut off the last ", "
	string tmpName = nameAcc.str();

	if (tmpName.length() > 2)
	{
		tmpName = tmpName.substr(0, tmpName.length()-2);	
	}
	
	output << tmpName;
}

void TextView::printClockTail(ostream &output, shared_ptr<const ClockTail> clocktail, shared_ptr<const FeedBack> feedback)
{
	printClockTail(output, clocktail);	
	output << " (" << feedback->getScore() << ").";
}

void TextView::printClockTails(ostream &output)
{
	//print last first, as doing it the other way feels wrong
	list<shared_ptr<FeedBack> >::reverse_iterator feedback = lastNFeedBacks.rbegin();
	BOOST_REVERSE_FOREACH(shared_ptr<const ClockTail> ct, lastNClockTails)
	{
		if (feedback != lastNFeedBacks.rend())
		{
			printClockTail(output, ct, (*feedback));
			feedback++;
		}
		else
		{
			printClockTail(output, ct);
		}
		output << endl;
	}	
}

string TextView::getUserInput(ostream &output, istream &input, const char *promptString)
{
	output << promptString << ": ";
	string userInput;
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

void TextView::updateClocktailsList(shared_ptr<const ClockTail> newOne)
{
	shared_ptr<FeedBack> newFBack = make_shared<FeedBack>();
	//store the current Feedback.
	lastNFeedBacks.push_front(newFBack);
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
		cerr << "Error! clear screen command failed to execute!" << endl;
}

void TextView::printHeader(ostream &out)
{
	out << "Welcome to ClockTails version 0.1" << endl;
}
