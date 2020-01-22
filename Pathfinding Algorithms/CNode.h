#pragma once
class CNode
{
public:
	CNode(int x, int y, CNode* parent); //BFS DFS
	CNode(int x, int y, int cost, CNode* parent); //A STAR
	~CNode();

	//***************************************************************************************//
	//	NEED REPOSITION at CNode.cpp

	
	int getX()
	{
		return mX;
	}
	void setX(int x)
	{
		mX = x;
	}


	int getY()
	{
		return mY;
	}
	void setY(int y)
	{
		mY = y;
	}

	int GetCost() //cost e.g. 1-2-3 (g)
	{
		return mCost;
	}
	void SetCost(int cost)
	{
		mCost = cost;
	}
	int GetHeuristic() //(h) manhatan distance
	{
		return mHeuristic;
	}
	void SetHeuristic(int heuristic)
	{
		mHeuristic = heuristic;
	}
	int GetTotal() //(f) f = g + h
	{
		return mTotal;
	}
	void SetTotal(int total)
	{
		mTotal = total;
	}

	CNode* GetParent()
	{
		return mParent;
	}

	void SetParent(CNode* parent)
	{
		mParent = parent;
	}

	//Found: https://en.cppreference.com/w/cpp/language/operator_logical
	bool operator == (CNode* endNode)
	{
		return	mX == endNode->mX && mY == endNode->mY;
	}
	//***************************************************************************************//


private:
	int mX;
	int mY;
	int mCost;
	int mHeuristic;
	int mTotal;
	CNode* mParent;
};

