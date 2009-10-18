/*
 * RandomVariableGraph.h
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLEGRAPH_H_
#define RANDOMVARIABLEGRAPH_H_

#include "../RandomVariable.h"
#include "RVGraphNode.h"
#include <map>
#include <string>

using namespace std;

namespace stochastic {

class RVGraphNode;
class RandomVariable;

class RandomVariableGraph
{
private:
	map<string, RVGraphNode *> nodeHashMap;
	map<string, RandomVariable *> randomVariableHashMap;

	void deleteNode(RVGraphNode *);

public:
	RandomVariableGraph();
	virtual ~RandomVariableGraph();

	void addRandomVariable(RandomVariable *, string);
	void setParentsFor(RandomVariable, RandomVariable, RandomVariable);
	RandomVariable & getParent1For(RandomVariable);
	RandomVariable & getParent2For(RandomVariable);

	int isTerminal(RandomVariable);
};

} // namespace stochastic

#endif /* RANDOMVARIABLEGRAPH_H_ */
