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
#include <fstream>
#include "RandomClockTailGenerator.hpp"
#include "CTController.hpp"
#include "MenuStructure.hpp"

int main(int argc, char **argv)
{
	std::cout << "Hello world! *Hic!*" << std::endl;
	std::ifstream f1("mixers1.txt");
	InputFile if1;
	if1.loadData(f1);
	std::ifstream f2("spirits1.txt");
	InputFile if2;
	if2.loadData(f2);
	std::ifstream f3("names1.txt");
	InputFile if3;
	if3.loadData(f3);
	std::ifstream f4("names2.txt");
	InputFile if4;
	if4.loadData(f4);

	RandomClockTailGenerator model;
	model.addMixerFile(if1);
	model.addMixerFile(if1);
	model.addSpiritFile(if2);
	model.addNameFile(if3);
	model.addNameFile(if4);

	CTController controller(model);
	TextView tv(model, controller);
	model.registerObserver(tv);

	tv.startInputLoop();
}
