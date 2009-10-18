/*
 * RVGraphNode.h
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#ifndef RVGRAPHNODE_H_
#define RVGRAPHNODE_H_

#include <list>
#include <string>

using namespace std;

namespace stochastic {

class RVGraphNode
{
private:
	string randomVariableID;
	RVGraphNode * parent1;
	RVGraphNode * parent2;
	list<RVGraphNode *> children;

	int inactive; // '1' if the destructor of the original RV is called

public:
	RVGraphNode(string);
	virtual ~RVGraphNode();

	string getRandomVariableID() const;
	RVGraphNode * getParent1();
	RVGraphNode * getParent2();
	void setParents(RVGraphNode *, RVGraphNode *);
	list<RVGraphNode*> getChildren();
	void addChild(RVGraphNode *);
	int isInactive();
};

} // namespace stochastic

#endif /* RVGRAPHNODE_H_ */
