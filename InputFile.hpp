/*
 * =====================================================================================
 *
 *       Filename:  InputFile.hpp
 *
 *    Description:  Input data file for spirits/mixers/names etc.
 *
 *        Version:  1.0
 *        Created:  16/07/10 18:03:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */
#ifndef __INPUTFILE_HPP__
#define __INPUTFILE_HPP__

#include <iostream>
#include <vector>

class InputFile
{
	public:
		InputFile();
		virtual ~InputFile();
		InputFile(const InputFile &rhs);

		InputFile &operator=(const InputFile &rhs);

		void loadData(std::istream &input);

		size_t size();
		const std::string *getLine(unsigned int index);
		const std::vector<std::string> &getLines();

	private:
		std::vector<std::string> lines;
};

#endif
