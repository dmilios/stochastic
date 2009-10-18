/*
 * RVGraphNode.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "RVGraphNode.h"

namespace stochastic {

RVGraphNode::RVGraphNode(string id)
{
	randomVariableID = id;
	parent1 = 0;
	parent2 = 0;
}

RVGraphNode::~RVGraphNode()
{
}

string RVGraphNode::getRandomVariableID() const
{
	return randomVariableID;
}

RVGraphNode * RVGraphNode::getParent1()
{
	return parent1;
}

RVGraphNode * RVGraphNode::getParent2()
{
	return parent2;
}

void RVGraphNode::setParents(RVGraphNode * parent1, RVGraphNode * parent2)
{
	this->parent1 = parent1;
	this->parent2 = parent2;
}

list<RVGraphNode*> RVGraphNode::getChildren()
{
	return children;
}

void RVGraphNode::addChild(RVGraphNode * child)
{
	this->children.push_back(child);
}

int RVGraphNode::isInactive()
{
	return inactive;
}

} // namespace stochastic
