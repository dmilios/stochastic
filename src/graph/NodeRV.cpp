/*
 * NodeRV.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "NodeRV.h"

namespace stochastic
{

NodeRV::NodeRV(string id)
{
	randomVariableID = id;
	parent1 = 0;
	parent2 = 0;
}

NodeRV::~NodeRV()
{
}

string NodeRV::getRandomVariableID() const
{
	return randomVariableID;
}

NodeRV * NodeRV::getParent1()
{
	return parent1;
}

NodeRV * NodeRV::getParent2()
{
	return parent2;
}

void NodeRV::setParent1(NodeRV * parent1)
{
	this->parent1 = parent1;
}

void NodeRV::setParent2(NodeRV * parent2)
{
	this->parent2 = parent2;
}

list<NodeRV*> NodeRV::getChildren()
{
	return children;
}

void NodeRV::addChild(NodeRV * child)
{
	this->children.push_back(child);
}

OperationType NodeRV::getPrecededOperation() const
{
	return precededOperation;
}

void NodeRV::setPrecededOperation(OperationType precededOperation)
{
	this->precededOperation = precededOperation;
}

int NodeRV::isInactive()
{
	return inactive;
}

} // namespace stochastic
