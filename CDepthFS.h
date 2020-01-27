#pragma once
#include "IAlgorithm.h"

class CDepthFS : public IAlgorithm
{
public:
	CDepthFS(deque<deque<CTile*>> grid);
	bool Search(CTile* startNode, CTile* endNode);

private:
	void InitializeSearch(CTile* startNode)
	{
		IAlgorithm::InitializeSearch(startNode);

	}
};