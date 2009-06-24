/*
 * FileParser.h
 *
 *  Created on: 14-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef FILEPARSER_H_
#define FILEPARSER_H_

#include <vector>
#include <string>

namespace stochastic {

enum States
{
	OUT,
	IN_COMMENT,
	SIGN_ENTERED,
	BEFORE_POINT,
	POINT_NEEDED,
	POINT_ENTERED,
	AFTER_POINT,
	EXP_ENTERED,
	AFTER_EXP
};

class FileParser
{
private:
	std::string buffer;
	void addtoBuffer(char);

public:
	FileParser();
	virtual ~FileParser();

	std::vector <double> parseDataFile(const char *);
};

} // namespace stochastic

#endif /* FILEPARSER_H_ */
