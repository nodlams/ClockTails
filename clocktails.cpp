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
#include "CTController.hpp"
#include "MenuStructure.hpp"

int main(int argc, char **argv)
{
	std::cout << "Hello world! *Hic!*" << std::endl;
	ClockTailGenerator model;
	CTController controller(model);

	TextView tv(model, controller);
	tv.startInputLoop();
}
