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

} // namespace stochastic
