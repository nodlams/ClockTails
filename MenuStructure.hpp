/*
 * =====================================================================================
 *
 *       Filename:  MenuStructure.hpp
 *
 *    Description:	Contains the menu structure for the clocktails text based interface. 
 *
 *        Version:  1.0
 *        Created:  16/07/10 10:14:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __MENUSTRUCTURE_HPP__
#define __MENUSTRUCTURE_HPP__

#include <string>
#include <vector>
#include <tr1/unordered_map>
#include <boost/shared_ptr.hpp>

//include "StringHash.hpp"

/**
 * The base class for menus, the system is based on the Composite pattern
 */
class MenuBase
{
	public:
		typedef boost::shared_ptr<MenuBase> MenuBasePtr;
		typedef std::tr1::unordered_map<std::string, MenuBasePtr>::iterator ItemsIterator;
		//column widths for printing
		static const int CWNAME=15;

	public:
		MenuBase(const char *name, const char *description, const char *shortcut);
		MenuBase(const MenuBase &rhs);
		virtual ~MenuBase();

		MenuBase &operator=(const MenuBase &rhs);

		/**
		 * This is a stub method which throws a not implemented exception if called.
		 * @param item the item to add
		 */
		virtual void addItem(MenuBasePtr item);

		/**
		 * This is a stub method which throws a not implemented exception if called.
		 * @param itemName the name of the item
		 */
		virtual MenuBasePtr getItem(const std::string &itemName);

		virtual const std::string &getName() const;
		virtual const std::string &getDescription() const;
		virtual const std::string &getShortCut() const;

		/**
		 * This is a stub method which throws a not implemented exception if called.
		 * @param the output stream that the text is printed to.
		 * @param the depth parameter indicates how far into the menu tree we should delve to print options, default is 1 (e.g. print only the current options)
		 */
		virtual void print(std::ostream &output, unsigned int depth=1);
	private:

		//The full name of the menuitem
		std::string name;
		//description of the menuitem
		std::string description;
		//shortcut std::string, e.g. if the item is "quit", this might be "q"
		std::string shortcut;
};

class Menu : public MenuBase
{
	public:
		Menu(const char *name, const char *description, const char *shortcut);
		Menu(const Menu &rhs);
		virtual ~Menu();

		Menu &operator=(const Menu &rhs);

		/**
		 * Add an item to this menu, the item might be a menuItem or another
		 * menu. The <item> object is copied and stored internally.
		 * @param item The item to store.
		 */
		virtual void addItem(MenuBasePtr item);
		/**
		 * look up a menu item by name and retrieve it.
		 * @param itemName the name of the menu item.
		 * @return a pointer to the object, or NULL if not found.
		 */
		virtual MenuBasePtr getItem(const std::string &itemName);

		/**
		 * Print the menu title and the options for this menu
		 * @param the output stream that the text is printed to.
		 */
		virtual void print(std::ostream &output, unsigned int depth=1);

	private:
		//hash_map for quick lookup of menu items
		std::tr1::unordered_map<std::string, MenuBasePtr> items;
		//menu items should be printed in the order they were added, so also
		//store the poiners in a vector in order.
		std::vector<MenuBasePtr> itemsOrdered;

};

class MenuItem : public MenuBase
{
	public:
		MenuItem(const char *name, const char *description, const char *shortCut);	
		MenuItem(const MenuItem &rhs);
		virtual ~MenuItem();

		MenuItem &operator=(const MenuItem &rhs);

		/**
		 * Print the menu item to the output stream
		 * @param the output stream that the text is printed to.
		 * @depth the depth to delve into the menu tree to print options, ignored for MenuItems.
		 */
		virtual void print(std::ostream &output, unsigned int depth=1);

	private:
};

#endif
