/*
 * GraphRV.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "GraphRV.h"

namespace stochastic
{

GraphRV::GraphRV()
{
}

GraphRV::~GraphRV()
{
}

void GraphRV::deleteNode(NodeRV * node)
{
	if (node->getParent1())
		node->getParent1()->getChildren().remove(node);
	if (node->getParent2())
		node->getParent2()->getChildren().remove(node);
}

void GraphRV::addRandomVariable(RandomVariable result, string id)
{
	NodeRV * node = new NodeRV(id);
	nodeHashMap[id] = node;
	nodeHashMap[id]->setPrecededOperation(NONE);
	randomVariableHashMap[id] = result;
}

void GraphRV::setOperationTypeFor(RandomVariable rv,
		OperationType op)
{
	string rv_id = rv.getRandomVariableID();
	nodeHashMap[rv_id]->setPrecededOperation(op);
}

void GraphRV::setParent1For(RandomVariable result,
		RandomVariable parent1)
{
	string parent1_id = parent1.getRandomVariableID();
	string result_id = result.getRandomVariableID();

	nodeHashMap[result_id]->setParent1(nodeHashMap[parent1_id]);
	nodeHashMap[parent1_id]->addChild(nodeHashMap[result_id]);
}

void GraphRV::setParent2For(RandomVariable result,
		RandomVariable parent2)
{
	string parent2_id = parent2.getRandomVariableID();
	string result_id = result.getRandomVariableID();

	nodeHashMap[result_id]->setParent2(nodeHashMap[parent2_id]);
	nodeHashMap[parent2_id]->addChild(nodeHashMap[result_id]);
}

OperationType GraphRV::getOperationTypeFor(RandomVariable rv)
{
	string rv_id = rv.getRandomVariableID();
	return nodeHashMap[rv_id]->getPrecededOperation();
}

RandomVariable GraphRV::getParent1For(RandomVariable rv)
{
	string rv_id = rv.getRandomVariableID();
	string parent_id = nodeHashMap[rv_id]->getParent1()->getRandomVariableID();
	return randomVariableHashMap[parent_id];
}

RandomVariable GraphRV::getParent2For(RandomVariable rv)
{
	string rv_id = rv.getRandomVariableID();
	string parent_id = nodeHashMap[rv_id]->getParent2()->getRandomVariableID();
	return randomVariableHashMap[parent_id];
}

int GraphRV::isTerminal(RandomVariable rv)
{
	string id = rv.getRandomVariableID();
	NodeRV * node = nodeHashMap[id];
	if (node->getParent1() == 0 && node->getParent2() == 0)
		return 1;
	return 0;
}

} // namespace stochastic
