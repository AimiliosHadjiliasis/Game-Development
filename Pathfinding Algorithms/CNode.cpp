#include "CNode.h"
CNode::CNode(int x, int y, CNode* parent)
{
	mX = x;
	mY = y;
	mParent = parent;
}
CNode::CNode(int x, int y, int cost, CNode* parent)
{
	mX = x;
	mY = y;
	mCost = cost;
	mParent = parent;
}

CNode::~CNode()
{

}


