/*
 * =====================================================================================
 *
 *       Filename:  clocktails.cpp
 *
 *    Description:  Main method for clocktails.
 *
 *        Version:  1.0
 *        Created:  16/07/10 09:15:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#include <iostream>
#include "ClockTailGenerator.hpp"
#include "MenuStructure.hpp"

int main(int argc, char **argv)
{
	std::cout << "Hello world! *Hic!*" << std::endl;

	//test menu structure
	boost::shared_ptr<MenuBase> mi1(new MenuItem("test1", "test1 desc", "t1"));
	boost::shared_ptr<MenuBase> mi2(new MenuItem("test2", "test2 desc", "t2"));
	boost::shared_ptr<MenuBase> mi3(new MenuItem("test3", "test3 desc", "t3"));
	boost::shared_ptr<MenuBase> mi4(new MenuItem("test4", "test4 desc", "t4"));

	boost::shared_ptr<MenuBase> m1(new Menu("menu1", "menu1 desc", "m1"));

	m1->addItem(mi1);
	m1->addItem(mi2);
	m1->addItem(mi3);
	m1->addItem(mi4);

	m1->print(std::cout, 1);

}
