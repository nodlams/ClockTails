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

#include <memory>
#include <boost/program_options.hpp>
#include <boost/make_shared.hpp>

using namespace boost::program_options;

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::fstream;
using std::ios;
using boost::make_shared;

options_description setupArgs()
{
	options_description desc("Allowed Arguments");
	//yes this is valid c++, stop crying!
	desc.add_options()
		("help", "produce help message")
		("mixers,M", value<vector<string> >()->multitoken(), "Files containing mixer names")
		("spirits,S", value<vector<string> >()->multitoken(), "Files containing spirit names")
		("names,N", value<vector<string> >()->multitoken(), "Files containing drink names");

	return desc;
}

variables_map parseArgs(int argc, char **argv, options_description &desc)
{
	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);	
	notify(vm);

	if (vm.count("help"))
	{
		cout << desc << endl;
		exit(1);
	}

	return vm;
}

bool checkArgs(variables_map &vars)
{
	bool argsOk = true;
	if (vars.count("mixers") == 0)
	{
		cerr << "Please enter at least one mixers file" << endl;
		argsOk = false;
	}
	if (vars.count("spirits") == 0)
	{
		cerr << "Please enter at least one spirits file" << endl;
		argsOk = false;
	}
	if (vars.count("names") == 0)
	{
		cerr << "Please enter at lest one name file" << endl;
		argsOk = false;
	}
	return argsOk;
}

bool checkFileExists(const string &filename)
{
	bool fileExists = true;
	fstream fstr;
	fstr.open(filename.c_str(), ios::in);
	if (!fstr.is_open())
	{
		cerr << "Failed to open file " << filename << endl;
		fileExists = false;
	}
	return fileExists;
}

bool checkFilesAndAddToModel(variables_map &vars, shared_ptr<ClockTailGenerator> model)
{
	vector<string> spFiles = vars["spirits"].as<vector<string> >();
	vector<string> mFiles = vars["mixers"].as<vector<string> >();
	vector<string> nFiles = vars["names"].as<vector<string> >();

	bool allFilesOk = false;
	for (vector<string>::iterator it = spFiles.begin(); it != spFiles.end(); ++it)
	{
		allFilesOk = allFilesOk || checkFileExists(*it);
		fstream istr;
		istr.open((*it).c_str(), ios::in);
		shared_ptr<InputFile> infile = make_shared<InputFile>();
		infile->loadData(istr);
		model->addSpiritFile(infile);
	}
	for (vector<string>::iterator it = mFiles.begin(); it != mFiles.end(); ++it)
	{
		allFilesOk = allFilesOk || checkFileExists(*it);
		fstream istr;
		istr.open((*it).c_str(), ios::in);
		shared_ptr<InputFile> infile = make_shared<InputFile>();
		infile->loadData(istr);
		model->addMixerFile(infile);
	}
	for (vector<string>::iterator it = nFiles.begin(); it != nFiles.end(); ++it)
	{
		cout << (*it) << endl;
		allFilesOk = allFilesOk || checkFileExists(*it);
		fstream istr;
		istr.open((*it).c_str(), ios::in);
		shared_ptr<InputFile> infile = make_shared<InputFile>();
		infile->loadData(istr);
		model->addNameFile(infile);
	}

	return allFilesOk;
}

int main(int argc, char **argv)
{
	options_description desc = setupArgs();
	variables_map vm = parseArgs(argc, argv, desc);
	bool argsOk = checkArgs(vm);
	if (!argsOk)
	{
		cout << desc << endl;
		return -1;
	}

	shared_ptr<History> hist = make_shared<History>();
	shared_ptr<SelectorRandom> rs = make_shared<SelectorRandom>();

	shared_ptr<CTModelIface> ctgenPtr = make_shared<ClockTailGenerator>(rs,hist);

	bool filesOk = checkFilesAndAddToModel(vm,ctgenPtr);
	if (!filesOk)
	{
		cout << desc << endl;
		return -1;
	}

	CTController controller(*model);
	TextView tv(*model, controller);
	model->registerObserver(tv);

	tv.startInputLoop();
}
