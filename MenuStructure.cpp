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
	//items are looked up based on shortcut, since that's what the user will enter
	const std::string &shortcut = item->getShortCut();
	items[shortcut] = item;
	itemsOrdered.push_back(item);
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

		for (std::vector<MenuBasePtr>::iterator it = itemsOrdered.begin(); it != itemsOrdered.end(); ++it)
		{
			(*it)->print(output, depth);
		}

		output << std::endl;
	}
	else if (depth == 0)
	{
		//treat it like a standard menu item and just print the details
		output << getName() << "\t(" << getShortCut() << "):\t" << getDescription() << std::endl;
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

/*
	//test menu structure
	boost::shared_ptr<MenuBase> mi1(new MenuItem("test1", "test1 desc", "t1"));
	boost::shared_ptr<MenuBase> mi2(new MenuItem("test2", "test2 desc", "t2"));
	boost::shared_ptr<MenuBase> mi3(new MenuItem("test3", "test3 desc", "t3"));
	boost::shared_ptr<MenuBase> mi4(new MenuItem("test4", "test4 desc", "t4"));

	boost::shared_ptr<MenuBase> m1(new Menu("menu1", "menu1 desc", "m1"));

	boost::shared_ptr<MenuBase> mi5(new MenuItem("test5", "test5 desc", "t5"));
	boost::shared_ptr<MenuBase> mi6(new MenuItem("test6", "test6 desc", "t6"));
	boost::shared_ptr<MenuBase> mi7(new MenuItem("test7", "test7 desc", "t7"));
	boost::shared_ptr<MenuBase> mi8(new MenuItem("test8", "test8 desc", "t8"));

	boost::shared_ptr<MenuBase> m2(new Menu("menu2", "menu2 desc", "m2"));

	m2->addItem(mi5);
	m2->addItem(mi6);
	m2->addItem(mi7);
	m2->addItem(mi8);
	

	m1->addItem(mi1);
	m1->addItem(mi2);
	m1->addItem(m2);
	m1->addItem(mi3);
	m1->addItem(mi4);

	m1->print(std::cout, 1);

	boost::shared_ptr<MenuBase> menuret = m1->getItem("m2");
	menuret->print(std::cout, 1);
	boost::shared_ptr<MenuBase> menuret2 = menuret->getItem("t5");
	menuret2->getItem("shouldthrow");
*/
