//////////
//////////A Star Pathfing files // PathfindingMap.h required
//////////Written by Tanapat Somrid 
/////////Starting 01/12/2021
//////// Most Recent Update 29/12/2021
//////// Most Recent change: FIXED A LOT OF EVERYTHING, currently not everyhting works, you can see the use cases in source.cpp


#pragma once

#ifndef A_STAR_PATHFINDING_H
#define A_STAR_PATHFINDING_H

#include <stack>
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
/// Checks the smallest fcost, smallest h cost
/// </summary>
struct PriorityComparator {
public:
	bool operator ()(const Node* a, const Node* b) const {
		if (a->GetFCost() == b->GetFCost())
		{
			return a->GetHCost() < b->GetHCost();
		}
		return (a->GetFCost() > b->GetFCost());
	}
};
/// <summary>
/// 
/// </summary>
//struct PositionComparator {
//public:
//	bool operator ()(const Node* a, const Node* b) const {
//		return (a->position < b->position);
//	}
//};
//struct classcomp {
//	bool operator() (const int& lhs, const int& rhs) const
//	{
//		return lhs < rhs;
//	}
//};

class Base_A_Star_Pathfinding {
public:
	Node* root;//Start node
	Node* target;//End node
	Room* currentRoom;//Contains Obstacle locations
	int nodeSize;//Allows us to take into account of the size of the agent using this(Assuming position is the center of agent, agent will not go halfway inside a wall.)

	int iterations;//For Debug and checking

	std::vector<Room*> rooms;


	#pragma region MANDATORY_BASE_FUNCTIONS
	template <typename T> void FindPath(Vector2<T> startPos, Vector2<T> endPos) {
		startPos = Vector2<int>(startPos);
		endPos = Vector2<int>(endPos);

		FindCurrentRoom(startPos);
		SetUpStartAndEndNodes(startPos, endPos);
		AStarAlgorithm();
	};

private:
	virtual void FindCurrentRoom(const Vector2<int> rootPosition) { if (!Base_A_Star_Pathfinding::IsNodeInRoom(*currentRoom, rootPosition)) { return; } std::cout << "Room ok! \n"; };
	virtual void SetUpStartAndEndNodes(Vector2<int> startPos, Vector2<int> endPos);
	virtual void AStarAlgorithm() = 0;
	Node* FindNodeInRoom(Vector2<int> pos, Room* rm);

	#pragma endregion
public:
	#pragma region HELPER_FUNCTIONS
	static bool IsNodeInRoom(const RoomStruct& nm, const Node& n);
	static bool IsNodeInRoom(const RoomStruct& nm, const Vector2<int> position);
	#pragma endregion



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
	void PrintRoute();

	void SetCurrentRoom(Room* nm) {
		currentRoom = nm;
		nodeSize = nm->GetNodeSize();
	}
protected:

};

/// <summary>
/// This algorithm will allow duplicate node checks however it should avoid the issue of having to check open and closed nodes and compare it to the newly made nodes on a unknown mapping(no predetermined grid that is generated)
/// <para>This Algorithm will search an undefined area. Because of this there are inefficiencies as one would have to expect, as there is a chance it will generate nodes that have already been generated, instead of recalculating them
/// ,however this has to be done because we don't keep unique nodes, this way we don't need to needlessly search open and closed nodes that are no where near our path.</para>
/// <para>Theory: This version would work best with straighforward paths, and very far away targets. The target moving does not hold much difference, as no matter what version, a moving target will always be costly. The more complex the path, the worse it will get, I predict it will be the worst of all if there is complex obstacles as we will be making multiple paths, possibly hundreds</para>
/// </summary>
class A_Star_Pathfinding_Undefined : public Base_A_Star_Pathfinding
{
public:
	std::priority_queue<Node*, std::vector<Node*>, PriorityComparator> toSearch;

private:
	void AStarAlgorithm() override;
	void SetUpStartAndEndNodes(Vector2<int> startPos, Vector2<int> endPos) override;
	void CheckNeighbours(Node* node);
};

class A_Star_Pathfinding_Defined : public Base_A_Star_Pathfinding {
public:
	A_Star_Pathfinding_Defined() {};
	~A_Star_Pathfinding_Defined() {
	};
	std::set<Node*, ReverseComparator> openSet;
	std::set<Node*> closedSet;

private:
	void AStarAlgorithm() override;
	void CheckNeighbours(Node* node);
	//void FindNeighbours(Node* node);
};

class A_Star_Pathfinding_Defined_Segmented : public Base_A_Star_Pathfinding {
public:
	A_Star_Pathfinding_Defined_Segmented() {};
	~A_Star_Pathfinding_Defined_Segmented() {
	};
	std::set<Node*, ReverseComparator> toSearch;
	std::set<Node*> searched;


private:
	void FindCurrentRoom(const Vector2<int> rootPosition) override;
	void AStarAlgorithm() override;

	std::stack<RoomStruct*> BruteForcePathfindMaps();
	std::queue<Node*> FindRouteNodePaths(std::stack<RoomStruct*> mapRoute);
	//void FindNeighbours(Node* node);
	//If the maps are supplied like a tree, or something similar that will tell us what Room connect we could optimise the FindRoute method to search only the necessary maps
	bool DefaultAStar(Node& startNode, Node& endNode);
	void CheckNeighbours(Node* node, Node& targetNode, std::set<Node*, ReverseComparator>& open, std::set<Node*>& closed);
	Node* FindRouteNode(std::stack<RoomStruct*>& mapRoute);
};

#endif // !A_STAR_PATHFINDING_H
