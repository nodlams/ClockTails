/*
 * =====================================================================================
 *
 *       Filename:  InputFile.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/10 20:57:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#include "InputFile.hpp"

InputFile::InputFile()
{
}

InputFile::~InputFile()
{
}

void InputFile::loadData(std::istream &input)
{
	std::string line;
	while (getline(input,line))
	{
		lines.push_back(line);	
	}
}

size_t InputFile::size()
{
	return lines.size();
}

const std::string *InputFile::getLine(unsigned int index)
{
	if (index < size())
	{
		return &lines[index];
	}
	return NULL;
}

const std::vector<std::string> &InputFile::getLines()
{
	return lines;
}
