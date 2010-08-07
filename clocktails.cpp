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
#include "CTController.hpp"
#include "MenuStructure.hpp"
#include "ClockTailGenerator.hpp"
#include "History.hpp"
#include "SelectorRandom.hpp"

#include <memory>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

po::options_description setupArgs()
{
	po::options_description desc("Allowed Arguments");
	//yes this is valid c++, stop crying!
	desc.add_options()
		("help", "produce help message")
		("mixers,M", po::value<std::vector<std::string> >()->multitoken(), "Files containing mixer names")
		("spirits,S", po::value<std::vector<std::string> >()->multitoken(), "Files containing spirit names")
		("names,N", po::value<std::vector<std::string> >()->multitoken(), "Files containing drink names");

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

bool checkArgs(po::variables_map &vars)
{
	bool argsOk = true;
	if (vars.count("mixers") == 0)
	{
		std::cerr << "Please enter at least one mixers file" << std::endl;
		argsOk = false;
	}
	if (vars.count("spirits") == 0)
	{
		std::cerr << "Please enter at least one spirits file" << std::endl;
		argsOk = false;
	}
	if (vars.count("names") == 0)
	{
		std::cerr << "Please enter at lest one name file" << std::endl;
		argsOk = false;
	}
	return argsOk;
}

bool checkFileExists(const std::string &filename)
{
	bool fileExists = true;
	std::fstream fstr;
	fstr.open(filename.c_str(), std::ios::in);
	if (!fstr.is_open())
	{
		std::cerr << "Failed to open file " << filename << std::endl;
		fileExists = false;
	}
	return fileExists;
}

bool checkFilesAndAddToModel(po::variables_map &vars, ClockTailGenerator *model)
{
	std::vector<std::string> spFiles = vars["spirits"].as<std::vector<std::string> >();
	std::vector<std::string> mFiles = vars["mixers"].as<std::vector<std::string> >();
	std::vector<std::string> nFiles = vars["names"].as<std::vector<std::string> >();

	bool allFilesOk = false;
	for (std::vector<std::string>::iterator it = spFiles.begin(); it != spFiles.end(); ++it)
	{
		allFilesOk = allFilesOk || checkFileExists(*it);
		std::fstream istr;
		istr.open((*it).c_str(), std::ios::in);
		InputFile infile;
		infile.loadData(istr);
		model->addSpiritFile(infile);
	}
	for (std::vector<std::string>::iterator it = mFiles.begin(); it != mFiles.end(); ++it)
	{
		allFilesOk = allFilesOk || checkFileExists(*it);
		std::fstream istr;
		istr.open((*it).c_str(), std::ios::in);
		InputFile infile;
		infile.loadData(istr);
		model->addMixerFile(infile);
	}
	for (std::vector<std::string>::iterator it = nFiles.begin(); it != nFiles.end(); ++it)
	{
		std::cout << (*it) << std::endl;
		allFilesOk = allFilesOk || checkFileExists(*it);
		std::fstream istr;
		istr.open((*it).c_str(), std::ios::in);
		InputFile infile;
		infile.loadData(istr);
		model->addNameFile(infile);
	}

	return allFilesOk;
}

int main(int argc, char **argv)
{
	po::options_description desc = setupArgs();
	po::variables_map vm = parseArgs(argc, argv, desc);
	bool argsOk = checkArgs(vm);
	if (!argsOk)
	{
		std::cout << desc << std::endl;
		return -1;
	}

	History hist;
	SelectorRandom rs;

	//TODO: Need to work out a way to get around the problem of passing in the name strings to the generator and the model.
	//actually thinking about it, there's no need for the model to know anything about the clocktail strings, they should just go to the generator.
	ClockTailGenerator *ctgenPtr = new ClockTailGenerator(rs,hist);
	std::auto_ptr<CTModelIface> model(ctgenPtr);

	bool filesOk = checkFilesAndAddToModel(vm,ctgenPtr);
	if (!filesOk)
	{
		std::cout << desc << std::endl;
		return -1;
	}

	CTController controller(*model);
	TextView tv(*model, controller);
	model->registerObserver(tv);

	tv.startInputLoop();
}
