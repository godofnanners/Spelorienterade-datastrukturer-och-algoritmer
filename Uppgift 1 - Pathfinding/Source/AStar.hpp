#pragma once
#include <vector>
#include <map>
#include <set>
#include "MinHeap.hpp"
#include <limits>
namespace CommonUtilities
{
	static bool CheckIfInsideMap(int aIndex);
	static bool CheckIfVerticeRealyIsNeighbour(int aNeighbourIndex, int aCurrentIndex);

	enum class eStatus { Unvisited, Open, Closed };
	enum class eHeuristics { eManhattan, eEuclidian };

	struct AStarNode
	{
		int myPredecessor;
		int myG;
		int myH;
		eStatus myStatus;
		int myIndex;

		bool operator< (const AStarNode& aNode) const
		{
			if (myG + myH < aNode.myG + aNode.myH)
			{
				return true;
			}
			return false;
		}
	};

	static int Manhattan(int aNodeX, int aNodeY, int aGoalX, int aGoalY)
	{
		return abs(aNodeX - aGoalX) + abs(aNodeY - aGoalY);
	}

	static int Euclidian(int aNodeX, int aNodeY, int aGoalX, int aGoalY)
	{
		return sqrt(pow((aNodeX - aGoalX), 2) + pow((aNodeY - aGoalY), 2));
	}

	
	static const int MapWidth = 20; static const int MapHeight = 20; static const int TileCount = MapWidth * MapHeight;
	enum class Tile { Impassable, Passable };
	static std::vector<int> AStar(const std::vector<Tile>& aMap, int aStartIndex, int anEndIndex, eHeuristics aHeuristics = eHeuristics::eManhattan)
	{
		std::vector<int>MyPath;
		std::array<AStarNode, MapWidth* MapHeight> myNodes;
		MinHeap<AStarNode> minHeap;
		

		int goalX = anEndIndex - ((MapWidth) * static_cast<int>(anEndIndex / (MapWidth)));
		int goalY = static_cast<int>(anEndIndex / MapHeight);
		for (size_t i = 0; i < aMap.size(); i++)
		{
			myNodes[i].myIndex = i;
			myNodes[i].myG = std::numeric_limits<int>::infinity();
			int nodeY = static_cast<int>(i / MapHeight);
			int nodeX = i - ((MapWidth) * static_cast<int>(i / (MapWidth )));
			myNodes[i].myH = (aHeuristics == eHeuristics::eManhattan ? Manhattan(nodeX, nodeY, goalX, goalY) : Euclidian(nodeX, nodeY, goalX, goalY));
			myNodes[i].myStatus = eStatus::Unvisited;
			myNodes[i].myPredecessor = -1;
		}

		myNodes[aStartIndex].myG = 0;
		myNodes[aStartIndex].myPredecessor = aStartIndex;
		minHeap.Enqueue(myNodes[aStartIndex]);

		while (minHeap.GetSize() > 0)
		{
			
			AStarNode newSmallest = minHeap.Dequeue();
			myNodes[newSmallest.myIndex].myStatus = eStatus::Closed;
			if (newSmallest.myIndex == anEndIndex)
			{

				int currentNode = newSmallest.myIndex;
				do
				{
					MyPath.push_back(currentNode);
					currentNode = myNodes[currentNode].myPredecessor;
				} while (currentNode != aStartIndex);
				MyPath.push_back(aStartIndex);
				std::reverse(MyPath.begin(), MyPath.end());
				return MyPath;
			}
			std::array<int, 4> neighbours;
			neighbours[0] = newSmallest.myIndex - MapWidth;
			neighbours[1] = newSmallest.myIndex + MapWidth;
			neighbours[2] = newSmallest.myIndex + 1;
			neighbours[3] = newSmallest.myIndex - 1;

			for (int i = 0; i < neighbours.size(); i++)
			{
				if (CheckIfInsideMap(neighbours[i])
					&& aMap[neighbours[i]] == Tile::Passable
					&& myNodes[neighbours[i]].myStatus != eStatus::Closed
					&& CheckIfVerticeRealyIsNeighbour(neighbours[i], newSmallest.myIndex))
				{
					int altPath = 1 + newSmallest.myG;

					if (myNodes[neighbours[i]].myStatus == eStatus::Unvisited)
					{
						//If its the first time encountering node
						myNodes[neighbours[i]].myG = altPath;
						myNodes[neighbours[i]].myPredecessor = newSmallest.myIndex;
						myNodes[neighbours[i]].myStatus = eStatus::Open;
						minHeap.Enqueue(myNodes[neighbours[i]]);
					}
					else if (myNodes[neighbours[i]].myStatus == eStatus::Open && altPath < myNodes[neighbours[i]].myG)
					{
						//If node already is in heap
						myNodes[neighbours[i]].myG = altPath;
						myNodes[neighbours[i]].myPredecessor = newSmallest.myIndex;
						minHeap.Remake();
					}


				}
			}
		}

		return MyPath;
	}
	static bool CheckIfInsideMap(int aIndex)
	{
		if (aIndex < MapWidth * MapHeight && aIndex >= 0)
		{
			return true;
		}
		return false;
	}
	static bool CheckIfVerticeRealyIsNeighbour(int aNeighbourIndex, int aCurrentIndex)
	{
		if (abs((aCurrentIndex % MapWidth) - (aNeighbourIndex % MapWidth)) != 1 && abs(aCurrentIndex - aNeighbourIndex) != MapWidth)
		{
			return false;
		}

		return true;
	}

}