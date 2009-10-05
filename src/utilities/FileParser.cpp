/*
 * FileParser.cpp
 *
 *  Created on: 14-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "FileParser.h"

#include "exceptions.h"
#include <fstream>
#include <cstdlib>

namespace stochastic {

FileParser::FileParser()
{
}

FileParser::~FileParser()
{
}

void FileParser::addtoBuffer(char c)
{
	std::string tmp(1, c);
	buffer.append(tmp);
}

std::vector<double> FileParser::parseDataFile(const char * fileName)
{
	std::vector<double> data;
	char ch;
	States state = OUT;
	buffer = "";

	std::ifstream input;
	input.open(fileName);
	if (!input.is_open())
		throw stochastic::FileNotFoundException();

	input.get(ch);
	while (!input.eof())
	{
		switch (ch)
		{
			case '#':
				state = IN_COMMENT;
				break;
			case 'e':
				if (state != IN_COMMENT)
				{
					if (state == BEFORE_POINT || state == AFTER_POINT)
					{
						addtoBuffer(ch);
						state = EXP_ENTERED;
					}
					else
						throw stochastic::InvalidDataFileException();
				}
				break;
			case '.':
				if (state != IN_COMMENT)
				{
					if (state == BEFORE_POINT || state == POINT_NEEDED)
					{
						addtoBuffer(ch);
						state = POINT_ENTERED;
					}
					else
						throw stochastic::InvalidDataFileException();
				}
				break;
			case '-':
				if (state != IN_COMMENT)
				{
					if (state == OUT)
					{
						addtoBuffer(ch);
						state = SIGN_ENTERED;
					}
					else if (state == EXP_ENTERED)
					{
						addtoBuffer(ch);
						state = AFTER_EXP;
					}
					else
						throw stochastic::InvalidDataFileException();
				}
				break;
			case '+':
				if (state != IN_COMMENT)
				{
					if (state == EXP_ENTERED)
					{
						addtoBuffer(ch);
						state = AFTER_EXP;
					}
					else
						throw stochastic::InvalidDataFileException();
				}
				break;
			case '0':
				if (state != IN_COMMENT)
				{
					if (state != POINT_NEEDED)
					{
						addtoBuffer(ch);
						if (state == SIGN_ENTERED || state == OUT)
							state = POINT_NEEDED;
						else if (state == POINT_ENTERED)
							state = AFTER_POINT;
						else if (state == EXP_ENTERED)
							state = AFTER_EXP;
					}
					else
						throw stochastic::InvalidDataFileException();
				}
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (state != IN_COMMENT)
				{
					if (state != POINT_NEEDED)
					{
						addtoBuffer(ch);
						if (state == SIGN_ENTERED || state == OUT)
							state = BEFORE_POINT;
						else if (state == POINT_ENTERED)
							state = AFTER_POINT;
						else if (state == EXP_ENTERED)
							state = AFTER_EXP;
					}
					else
						throw stochastic::InvalidDataFileException();
				}
				break;
			case ',':
			case ' ':
			case '\t':
				if (state != IN_COMMENT)
				{
					if (state == SIGN_ENTERED || state == POINT_ENTERED
							|| state == EXP_ENTERED)
						throw stochastic::InvalidDataFileException();

					if (state != OUT)
					{
						data.push_back(atof(buffer.c_str()));
						buffer = "";
						state = OUT;
					}
				}
				break;
			case '\n':
			case '\r':
				if (state != IN_COMMENT)
				{
					if (state == SIGN_ENTERED || state == POINT_ENTERED
							|| state == EXP_ENTERED)
						throw stochastic::InvalidDataFileException();

					if (state != OUT)
					{
						data.push_back(atof(buffer.c_str()));
						buffer = "";
						state = OUT;
					}
				}
				else
					state = OUT;
				break;
			default:
				if (state != IN_COMMENT)
					throw stochastic::InvalidDataFileException();
				break;
		}
		input.get(ch);
	}
	input.close();
	return data;
}

} // namespace stochastic
