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
#include <vector>
#include <string>
#include <fstream>
#include "RandomClockTailGenerator.hpp"
#include "CTController.hpp"
#include "MenuStructure.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

po::options_description setupArgs()
{
	po::options_description desc("Allowed Arguments");
	//yes this is valid c++, stop crying!
	desc.add_options()
		("help", "produce help message")
		("mixers,M", po::value<std::vector<std::string> >(), "Files containing mixer names")
		("spirits,S", po::value<std::vector<std::string> >(), "Files containing spirit names")
		("names,N", po::value<std::vector<std::string> >(), "Files containing drink names");

	return desc;
}

po::variables_map parseArgs(int argc, char **argv, po::options_description &desc)
{
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);	
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		exit(1);
	}

	return vm;
}

int main(int argc, char **argv)
{
	po::options_description desc = setupArgs();
	po::variables_map vm = parseArgs(argc, argv, desc);

	RandomClockTailGenerator model;
	
	CTController controller(model);
	TextView tv(model, controller);
	model.registerObserver(tv);

	tv.startInputLoop();
}
