/*
 * =====================================================================================
 *
 *       Filename:  MenuStructure.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/10 11:19:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#include "MenuStructure.hpp"
#include "NotImplementedException.hpp"
#include <string>

MenuBase::MenuBase(const char *thename, const char *thedescription, const char *theshortcut)
	: name(thename), description(thedescription), shortcut(theshortcut)
{

}

MenuBase::MenuBase(const MenuBase &rhs)
	: name(rhs.name), description(rhs.description), shortcut(rhs.shortcut)
{
}

MenuBase::~MenuBase()
{
}

MenuBase &MenuBase::operator=(const MenuBase &rhs)
{
	if (this != &rhs)
	{
		MenuBase tmp(rhs);
		std::swap(this->name, tmp.name);
		std::swap(this->description, tmp.description);
		std::swap(this->shortcut, tmp.shortcut);
	}

	return *this;
}

void MenuBase::addItem(MenuBasePtr item)
{
	throw NotImplementedException("MenuBase::addItem");
}

MenuBase::MenuBasePtr MenuBase::getItem(const std::string &itemName)
{
	throw NotImplementedException("MenuBase::getItem");
}

const std::string &MenuBase::getName() const
{
	return name;
}

const std::string &MenuBase::getDescription() const
{
	return description;
}

const std::string &MenuBase::getShortCut() const
{
	return shortcut;
}

void MenuBase::print(std::ostream &output, unsigned int depth)
{
	throw NotImplementedException("MenuBase::print");
}

Menu::Menu(const char *name, const char *description, const char *shortcut)
	: MenuBase(name, description, shortcut)
{
}

Menu::Menu(const Menu &rhs)
	: MenuBase(rhs)
{
}

Menu::~Menu()
{
}

Menu &Menu::operator=(const Menu &rhs)
{
	MenuBase::operator=(rhs);
	return *this;
}

void Menu::addItem(MenuBasePtr item)
{
	const std::string &name = item->getName();
	items[name] = item;
}

MenuBase::MenuBasePtr Menu::getItem(const std::string &itemName)
{
	ItemsIterator it = items.find(itemName);

	boost::shared_ptr<MenuBase> notFoundRet((MenuBase*)NULL);
	if (it == items.end())
		return notFoundRet;

	return (*it).second;
}

void Menu::print(std::ostream &output, unsigned int depth)
{
	//decrement the couter
	if (depth > 0)
	{
		depth--;

		output << getName() << ":" << std::endl;

		for (ItemsIterator it = items.begin(); it != items.end(); ++it)
		{
			(*it).second->print(output, depth);
		}

		output << std::endl;
	}
}

MenuItem::MenuItem(const char *name, const char *description, const char *shortCut)
	: MenuBase(name, description, shortCut)
{
}

MenuItem::MenuItem(const MenuItem &rhs)
	: MenuBase(rhs)
{
}

MenuItem::~MenuItem()
{
}

MenuItem &MenuItem::operator=(const MenuItem &rhs)
{
	MenuBase::operator=(rhs);
	return *this;
}

void MenuItem::print(std::ostream &output, unsigned int depth)
{
	output << getName() << "\t(" << getShortCut() << "):\t" << getDescription() << std::endl;
}
