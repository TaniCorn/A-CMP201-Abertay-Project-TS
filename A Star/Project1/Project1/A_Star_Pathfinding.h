//////////
//////////A Star Pathfing files // PathfindingMap.h required
//////////Written by Tanapat Somrid 
/////////Starting 01/12/2021
//////// Most Recent Update 18/12/2021
//////// Most Recent change: Changing structure of files and classes

#pragma once

#ifndef A_STAR_PATHFINDING_H
#define A_STAR_PATHFINDING_H

#include <set>
#include <queue>
#include "PathfindingMap.h"


/// <summary>
/// Checks the smallest fcost, smallest h cost
/// </summary>
struct ReverseComparator {
public:
	bool operator ()(const Node* a, const Node* b) const{
		if (a->GetFCost() == b->GetFCost())
		{
			return a->GetHCost() > b->GetHCost();
		}
		return (a->GetFCost() < b->GetFCost());
	}
};
/// <summary>
/// 
/// </summary>
struct PositionComparator {
public:
	bool operator ()(const Node* a, const Node* b) const {
		return (a->position < b->position);
	}
};
//struct classcomp {
//	bool operator() (const int& lhs, const int& rhs) const
//	{
//		return lhs < rhs;
//	}
//};

/// <summary>
/// This algorithm will allow duplicate node checks however it should avoid the issue of having to check open and closed nodes and compare it to the newly made nodes on a unknown mapping(no predetermined grid that is generated)
/// <para>This Algorithm will search an undefined area. Because of this there are inefficiencies as one would have to expect, as there is a chance it will generate nodes that have already been generated, instead of recalculating them
/// ,however this has to be done because we don't keep unique nodes, this way we don't need to needlessly search open and closed nodes that are no where near our path.</para>
/// <para>Theory: This version would work best with straighforward paths, and very far away targets. The target moving does not hold much difference, as no matter what version, a moving target will always be costly. The more complex the path, the worse it will get, I predict it will be the worst of all if there is complex obstacles as we will be making multiple paths, possibly hundreds</para>
/// </summary>
class A_Star_Pathfinding_Undefined
{
public:
	//std::set<Node*, PositionComparator> open; Used for Defined maps
	std::priority_queue<Node*, std::vector<Node*>, ReverseComparator> toSearch;
	//std::set<Node*, PositionComparator> searched;

	Node* root;//Start node
	Node* target;//End node
	NodeMap* currentMap;//Contains Obstacle locations
	int nodeSize;//Allows us to take into account of the size of the agent using this(Assuming position is the center of agent, agent will not go halfway inside a wall.)

	/// <summary>
	/// Searches a space only defined by obstacles.
	/// </summary>
	template <typename T> void FindPath(Vector2<T> startPos, Vector2<T> endPos) {
		Node* endNode = new Node(endPos);
		//Vector2<int>* epos = new Vector2<int>; epos->x = floorf(endPos.x); epos->y = floorf(endPos.y);
		//endNode.position = epos;//Vector2<int>(floorf(endPos.x), floorf(endPos.y));
		Node* startNode = new Node(startPos);
		//startNode.position = Vector2<int>(floorf(startPos.x), floorf(startPos.y)); 
		startNode->SetGCost(0); startNode->SetParent(nullptr);
		startNode->SetHCost(floorf((endPos.x -startPos.x) + (endPos.y -startPos.y))); startNode->SetFCost();

		root = startNode;
		target = endNode;

		SearchPath();
	};
private:
	void SearchPath();
	void CheckNeighbours(Node* node);
	//void FindNeighbours(Node* node);
public:
	void SetMap(NodeMap* nm) {
		currentMap = nm;
		nodeSize = nm->nodeSize;
	}

		/// <summary>
	/// For Debuggin purposes
	/// </summary>
	void PrintPath() {

		Node* current = target;
		std::cout << " It " << iterations << "Times it took" << std::endl;

		while (current->GetParent() != nullptr)
		{
			current = current->GetParent();
			std::cout << current->position << std::endl;
			std::cout << current->GetGCost() << std::endl;
		}
	};
	void PrintNode(Node* n) {
		std::cout << "GCost:" << n->GetGCost() << " | FCost:" << n->GetFCost() << " | Position:" << n->position << std::endl;
	}
	int iterations;//For Debug and checking
};

class A_Star_Pathfinding_Defined {
public:
	A_Star_Pathfinding_Defined() {};
	~A_Star_Pathfinding_Defined() {
	};
	//std::set<Node*, PositionComparator> open; Used for Defined maps
	std::priority_queue<Node*, std::vector<Node*>, ReverseComparator> toSearchSorted;
	std::set<Node*, ReverseComparator> toSearch;
	std::set<Node*> searched;
	NodeMap* currentMap;//Contains Obstacle locations

	Node* root;//Start node
	Node* target;//End node
	int nodeSize;//Allows us to take into account of the size of the agent using this(Assuming position is the center of agent, agent will not go halfway inside a wall.)

	/// <summary>
	/// Searches a space only defined by obstacles.
	/// </summary>
	template <typename T> void FindPath(Vector2<T> startPos, Vector2<T> endPos) {
		int x, y, shift;
		x = 0;
		y = 0;
		if (startPos.x != 0)
		{
			shift = nodeSize % startPos.x;//Translate ourselves to nodes positions if we start at 30 but nodesize is 50 then we add 20;
			x = (startPos.x + shift) / nodeSize;
		}
		if (startPos.y != 0)
		{
			shift = nodeSize % startPos.y;
			y = (startPos.y + shift) / nodeSize;
		}
		Node* startNode = &currentMap->nodeMap[x][y];
		x = 0;
		y = 0;
		if (endPos.x != 0)
		{
			shift = nodeSize % endPos.x;//Translate ourselves to nodes positions if we start at 30 but nodesize is 50 then we add 20;
			x = (endPos.x + shift) / nodeSize; x--;
		}
		if (endPos.y != 0)
		{
			shift = nodeSize % endPos.y;
			y = (endPos.y + shift) / nodeSize; y--;
		}
		Node* endNode = &currentMap->nodeMap[x][y];

		//Vector2<int>* epos = new Vector2<int>; epos->x = floorf(endPos.x); epos->y = floorf(endPos.y);
		//endNode.position = epos;//Vector2<int>(floorf(endPos.x), floorf(endPos.y));
		//startNode.position = Vector2<int>(floorf(startPos.x), floorf(startPos.y)); 
		startNode->SetGCost(0); startNode->SetParent(nullptr);
		startNode->SetHCost(floorf((endPos.x - startPos.x) + (endPos.y - startPos.y))); startNode->SetFCost();

		root = startNode;
		target = endNode;

		SearchPath();
	};
private:
	void SearchPath();
	void CheckNeighbours(Node* node);
	//void FindNeighbours(Node* node);
public:
	void SetMap(NodeMap* nm) {
		currentMap = nm;

		nodeSize = nm->nodeSize;
	}

	/// <summary>
/// For Debuggin purposes
/// </summary>
	void PrintPath() {

		Node* current = target;
		std::cout << " It " << iterations << "Times it took" << std::endl;

		while (current->GetParent() != nullptr)
		{
			current = current->GetParent();
			std::cout << current->position << std::endl;
			std::cout << current->GetGCost() << std::endl;
		}
		std::cout << " It " << iterations << "Times it took" << std::endl;

	};
	void PrintNode(Node* n) {
		std::cout << "GCost:" << n->GetGCost() << " | FCost:" << n->GetFCost() << " | Position:" << n->position << std::endl;
	}
	int iterations;//For Debug and checking
};

class A_Star_Pathfinding_Defined_Segmented {
public:
	A_Star_Pathfinding_Defined_Segmented() {};
	~A_Star_Pathfinding_Defined_Segmented() {
	};
	//std::set<Node*, PositionComparator> open; Used for Defined maps
	std::priority_queue<Node*, std::vector<Node*>, ReverseComparator> toSearchSorted;
	std::set<Node*, ReverseComparator> toSearch;
	std::set<Node*> searched;

	Node* root;//Start node
	Node* target;//End node
	std::vector<NodeMap*> currentMaps;//Contains Obstacle locations
	NodeMap* currentMap;//Contains Obstacle locations
	int nodeSize;//Allows us to take into account of the size of the agent using this(Assuming position is the center of agent, agent will not go halfway inside a wall.)

	/// <summary>
	/// Searches a space only defined by obstacles.
	/// </summary>
	template <typename T> void FindPath(Vector2<T> startPos, Vector2<T> endPos) {
		int x, y, shift;
		x = 0;
		y = 0;
		if (startPos.x != 0)
		{
			shift = nodeSize % startPos.x;//Translate ourselves to nodes positions if we start at 30 but nodesize is 50 then we add 20;
			x = (startPos.x + shift) / nodeSize;
		}
		if (startPos.y != 0)
		{
			shift = nodeSize % startPos.y;
			y = (startPos.y + shift) / nodeSize;
		}
		Node* startNode = &currentMap->nodeMap[x][y];
		x = 0;
		y = 0;
		if (endPos.x != 0)
		{
			shift = nodeSize % endPos.x;//Translate ourselves to nodes positions if we start at 30 but nodesize is 50 then we add 20;
			x = (endPos.x + shift) / nodeSize; x--;
		}
		if (endPos.y != 0)
		{
			shift = nodeSize % endPos.y;
			y = (endPos.y + shift) / nodeSize; y--;
		}
		Node* endNode = &currentMap->nodeMap[x][y];

		//Vector2<int>* epos = new Vector2<int>; epos->x = floorf(endPos.x); epos->y = floorf(endPos.y);
		//endNode.position = epos;//Vector2<int>(floorf(endPos.x), floorf(endPos.y));
		//startNode.position = Vector2<int>(floorf(startPos.x), floorf(startPos.y)); 
		startNode->SetGCost(0); startNode->SetParent(nullptr);
		startNode->SetHCost(floorf((endPos.x - startPos.x) + (endPos.y - startPos.y))); startNode->SetFCost();

		root = startNode;
		target = endNode;

		SearchPath();
	};
private:
	void SearchPath();
	void CheckNeighbours(Node* node);
	bool InCurrentMap();
	//void FindNeighbours(Node* node);
public:
	void SetMap(NodeMap* nm) {
		currentMaps.push_back(nm);

		nodeSize = nm->nodeSize;
	}

	/// <summary>
/// For Debuggin purposes
/// </summary>
	void PrintPath() {

		Node* current = target;
		std::cout << " It " << iterations << "Times it took" << std::endl;

		while (current->GetParent() != nullptr)
		{
			current = current->GetParent();
			std::cout << current->position << std::endl;
			std::cout << current->GetGCost() << std::endl;
		}
		std::cout << " It " << iterations << "Times it took" << std::endl;

	};
	void PrintNode(Node* n) {
		std::cout << "GCost:" << n->GetGCost() << " | FCost:" << n->GetFCost() << " | Position:" << n->position << std::endl;
	}
	int iterations;//For Debug and checking
};

#endif // !A_STAR_PATHFINDING_H
