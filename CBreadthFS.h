#pragma once
#include "IAlgorithm.h"

class CBreadthFS : public IAlgorithm
{
public:
	CBreadthFS(deque<deque<CTile*>> grid);
	bool Search(CTile* startNode, CTile* endNode);

private:
	void InitializeSearch(CTile* startNode)
	{
		IAlgorithm::InitializeSearch(startNode);
		
	}
};

