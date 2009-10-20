/*
 * RandomVariableGraph.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "RandomVariableGraph.h"

namespace stochastic {

RandomVariableGraph::RandomVariableGraph()
{
}

RandomVariableGraph::~RandomVariableGraph()
{
}

void RandomVariableGraph::deleteNode(RVGraphNode * node)
{
	if (node->getParent1())
		node->getParent1()->getChildren().remove(node);
	if (node->getParent2())
		node->getParent2()->getChildren().remove(node);
}

void RandomVariableGraph::addRandomVariable(RandomVariable * rv, string id)
{
	RVGraphNode * node = new RVGraphNode(id);
	nodeHashMap[id] = node;
	randomVariableHashMap[id] = rv;
}

void RandomVariableGraph::changeRandomVariable(RandomVariable * rv, string id)
{
	randomVariableHashMap[id] = rv;
}

void RandomVariableGraph::setParentsFor(RandomVariable result,
		RandomVariable parent1, RandomVariable parent2)
{
	string parent1_id = parent1.getRandomVariableID();
	string parent2_id = parent2.getRandomVariableID();
	string result_id = result.getRandomVariableID();

	nodeHashMap[result_id]->setParents(nodeHashMap[parent1_id],
			nodeHashMap[parent2_id]);
	nodeHashMap[parent1_id]->addChild(nodeHashMap[result_id]);
	nodeHashMap[parent2_id]->addChild(nodeHashMap[result_id]);
}

RandomVariable & RandomVariableGraph::getParent1For(RandomVariable rv)
{
	string rv_id = rv.getRandomVariableID();
	string parent_id = nodeHashMap[rv_id]->getParent1()->getRandomVariableID();
	return * randomVariableHashMap[parent_id];
}

RandomVariable & RandomVariableGraph::getParent2For(RandomVariable rv)
{
	string rv_id = rv.getRandomVariableID();
	string parent_id = nodeHashMap[rv_id]->getParent2()->getRandomVariableID();
	return * randomVariableHashMap[parent_id];
}

int RandomVariableGraph::isTerminal(RandomVariable rv)
{
	string id = rv.getRandomVariableID();
	RVGraphNode * node = nodeHashMap[id];
	if (node->getParent1() == 0 && node->getParent2() == 0)
		return 1;
	return 0;
}

} // namespace stochastic
