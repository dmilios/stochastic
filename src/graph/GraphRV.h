/*
 * GraphRV.h
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLEGRAPH_H_
#define RANDOMVARIABLEGRAPH_H_

#include "../RandomVariable.h"
#include "NodeRV.h"
#include "OperationType.h"
#include <map>
#include <string>

using namespace std;

namespace stochastic
{

class NodeRV;
class RandomVariable;

class GraphRV
{
private:
	map<string, NodeRV *> nodeHashMap;
	map<string, RandomVariable> randomVariableHashMap;

	void deleteNode(NodeRV *);

public:
	GraphRV();
	virtual ~GraphRV();

	void addRandomVariable(RandomVariable, string);
	void setOperationTypeFor(RandomVariable, OperationType);
	void setParent1For(RandomVariable, RandomVariable);
	void setParent2For(RandomVariable, RandomVariable);
	OperationType getOperationTypeFor(RandomVariable);
	RandomVariable getParent1For(RandomVariable);
	RandomVariable getParent2For(RandomVariable);

	int isTerminal(RandomVariable);
};

} // namespace stochastic

#endif /* RANDOMVARIABLEGRAPH_H_ */
