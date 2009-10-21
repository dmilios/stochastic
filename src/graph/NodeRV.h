/*
 * NodeRV.h
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#ifndef RVGRAPHNODE_H_
#define RVGRAPHNODE_H_

#include "OperationType.h"
#include <list>
#include <string>

using namespace std;

namespace stochastic
{

class NodeRV
{
private:
	string randomVariableID;
	OperationType precededOperation;
	NodeRV * parent1;
	NodeRV * parent2;
	list<NodeRV *> children;

	int inactive; // '1' if the destructor of the original RV is called

public:
	NodeRV(string);
	virtual ~NodeRV();

	string getRandomVariableID() const;
	OperationType getPrecededOperation() const;
	NodeRV * getParent1();
	NodeRV * getParent2();
	void setPrecededOperation(OperationType);
	void setParent1(NodeRV *);
	void setParent2(NodeRV *);
	list<NodeRV*> getChildren();
	void addChild(NodeRV *);
	int isInactive();
};

} // namespace stochastic

#endif /* RVGRAPHNODE_H_ */
