//////////
//////////A Star Pathfing files // Vector2.h required
//////////Written by Tanapat Somrid 
/////////Starting 01/12/2021
//////// Most Recent Update 07/12/2021

#pragma once

#ifndef A_STAR_PATHFINDING_H
#define A_STAR_PATHFINDING_H

#include <set>
#include <queue>
#include <vector>

#include "VectorPositions.h"


enum NodeType
{
	Free,
	Obstacle,
};

class Node {
public:
	#pragma region CONSTRUCTORS
	/// <summary>
/// Constructor For Start and End Nodes
/// </summary>
	Node() {
		rCost = 0; nodeType = Free;
	}
	/// <summary>
	/// Constructor for new Nodes
	/// </summary>
	Node(const Vector2<int>& newPosition) {
		nodeType = Free;
		position = newPosition;

		//NodeType
		if (position == Vector2<int>{6, 5})
		{
			nodeType = Obstacle;
		}
		if (position == Vector2<int>{6, 6})
		{
			nodeType = Obstacle;
		}		if (position == Vector2<int>{6, 4})
		{
			nodeType = Obstacle;
		}		if (position == Vector2<int>{6, 3})
		{
			nodeType = Obstacle;
		}		if (position == Vector2<int>{5, 3})
		{
			nodeType = Obstacle;
		}		if (position == Vector2<int>{5, 6})
		{
			nodeType = Obstacle;
		}
	}

	Node(int x, int y) {
		position.x = x; position.y = y;
	}

	//Copy Constructors

	/// <summary>
	/// Copy Constructor for assignment
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	Node(const Node& a) { fCost = a.fCost; gCost = a.gCost; hCost = a.hCost; rCost = a.rCost; position = a.position; nodeType = a.nodeType; parentNode = a.parentNode; for (int i = 0; i < 4; i++) { neighbours[i] = a.neighbours[i]; }; }
	Node& operator =(const Node& copy) { fCost = copy.fCost; gCost = copy.gCost; hCost = copy.hCost; rCost = copy.rCost; position = copy.position; nodeType = copy.nodeType; parentNode = copy.parentNode; for (int i = 0; i < 4; i++) { neighbours[i] = copy.neighbours[i]; }; return *this; }

#pragma endregion


	#pragma region DISTANCES
	/// <summary>
/// The EUCLIDEAN distance from this node and the given coordinates (x and y)
/// </summary>
/// <returns>EUCLIDEAN DISTANCE</returns>
	int DistanceFromE(int x, int y) { return position.DistanceFrom(x, y); }
	/// <summary>
	/// The EUCLIDEAN distance from this node and the given vector (position.x and position.y)
	/// </summary>
	/// <returns>EUCLIDEAN DISTANCE</returns>
	int DistanceFromE(const Vector2<int>& pos) {
		return position.DistanceFrom(pos);
	}
	/// <summary>
	/// The EUCLIDEAN distance between two given nodes
	/// <para> From Node A to Node B</para>
	/// </summary>
	/// <param name="Node A"></param>
	/// <param name="Node B"></param>
	/// <returns>EUCLIDEAN DISTANCE</returns>
	static int DistanceBetweenE(const Node& a, const Node& b) {
		return Vector2<int>::DistanceBetween(a.position, b.position);
	}
	/// <summary>
/// The MANHATTAN distance from this node and the given coordinates (x and y)
/// </summary>
/// <returns>MANHATTAN DISTANCE</returns>
	int DistanceFromM(int x, int y) { return ((x - position.x) + (y - position.y)); }
	/// <summary>
	/// The MANHATTAN distance from this node and the given vector (position.x and position.y)
	/// </summary>
	/// <returns>MANHATTAN DISTANCE</returns>
	int DistanceFromM(const Vector2<int>& pos) {
		int total = ((pos.x - position.x) + (pos.y - position.y));
		return total;
	}
	/// <summary>
	/// The MANHATTAN distance between two given nodes
	/// <para> From Node A to Node B</para>
	/// </summary>
	/// <param name="Node A"></param>
	/// <param name="Node B"></param>
	/// <returns>MANHATTAN DISTANCE</returns>
	static int DistanceBetweenM(const Node& a, const Node& b) {
		int total = ((a.position.x - b.position.x) + (a.position.y - b.position.y));
		return total;
	}
#pragma endregion


	#pragma region CHARACTERISTICS
	float fCost;//totalCost
	float gCost;//how far away we are from root Node
	float hCost;//how far away we are from target Node
	float rCost;//running cost of movement
	Vector2<int> position = Vector2<int>(0, 0);//Our position, it's unique


	Node* neighbours[4];//NESW of node
	Node* parentNode;//Node that this node branched from
	//bool closed = false;//Is this closed? We could either check if this position exists in closed or just do this.

	NodeType nodeType;//Is this an obstacle? If so we can't pass through it
	static Node* rootNode;//Start node
	static Node* targetNode;//Target node//Will this still be the same for different instances of A_Star_Pathfinding? I hope so
#pragma endregion


	#pragma region GETTERS/SETTERS
	void SetParent(Node* parent) {
		parentNode = parent;
	}
	Node* GetParent() {
		return parentNode;
	}
#pragma endregion



	/// <summary>
/// Generate all neighbours
/// </summary>
	void GenerateAndCalculateNeighbours() {
		GenerateNeighbours();
		CalculateNeighbours();
	}
	/// <summary>
	/// Calculate the cost : Running Multiplier Version
	/// </summary>
	void CalculateCosts() {
		hCost = (abs(targetNode->position.x - position.x) + abs(targetNode->position.y - position.y)) * weighting;
		gCost = (abs(rootNode->position.x - position.x) + abs(rootNode->position.y - position.y));
		rCost = parentNode->rCost + 1;
		fCost = gCost + hCost + rCost;
	}

private:
	/// <summary>
	/// Generates neighbours in 4 direcions (NESW)
	/// </summary>
	void GenerateNeighbours() {
		Vector2<int> north = position + Vector2<int>(0, 1 * nodeSize);
		Vector2<int> south = position + Vector2<int>(0, -1 * nodeSize);
		Vector2<int> east = position + Vector2<int>(1 * nodeSize, 0);
		Vector2<int> west = position + Vector2<int>(-1 * nodeSize, 0);

		//Don't make a neighbour of your parents!
		Vector2<int> parentNodePosition = position;

		if (parentNode != nullptr)
		{
			parentNodePosition = parentNode->position;
		}

		for (int i = 0; i < 4; i++)
		{
			neighbours[i] = nullptr;
		}

		if (parentNodePosition != north)
		{
			neighbours[0] = new Node(north);
		}
		if (parentNodePosition != south) {
			neighbours[1] = new Node(south);
		}
		if (parentNodePosition != east) {
			neighbours[2] = new Node(east);
		}
		if (parentNodePosition != west) {
			neighbours[3] = new Node(west);
		}
	}
	/// <summary>
	/// Sets parent and calculates costs
	/// </summary>
	void CalculateNeighbours() {
		for (int i = 0; i < 4; i++)
		{
			if (neighbours[i] != nullptr)
			{
				neighbours[i]->SetParent(this);
				neighbours[i]->CalculateCosts();
			}
		}
	}



	int nodeSize = 1;//How big is each node in this worldspace?
	const int weighting = 2;//How weighted should our path be towards the target node?
};
/// <summary>
/// Checks the smallest fcost, smallest h cost
/// </summary>
struct ReverseComparator {
public:
	bool operator ()(const Node* a, const Node* b) {
		if (a->fCost == b->fCost)
		{
			return a->hCost > b->hCost;
		}
		return (a->fCost > b->fCost);
	}
};
struct PositionComparator {
public:
	bool operator ()(const Node* a, const Node* b) const {
		//return (a->position == b->position);
		//If they are in the same position, check if the new insert has a low cost, if so, it is allowed to be inserted. If not don't bother as it has a worse path.
		if ((a->position == b->position))
		{
			return a->fCost < b->fCost;
		}
		return a;
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
	friend class Node;
	//std::set<Node*, PositionComparator> open; Used for Defined maps
	std::priority_queue<Node*, std::vector<Node*>, ReverseComparator> toSearch;
	std::set<Node*, std::less<Node*>> searched;

	/// <summary>
	/// For Debuggin purposes
	/// </summary>
	void PrintPath() {	
		
		Node* current = Node::targetNode;
		std::cout << " It " << iterations << "Times it took" << std::endl;

	while (current->GetParent() != nullptr)
	{
		current = current->GetParent();
		std::cout << current->position << std::endl;
		std::cout << current->rCost << std::endl;
	}
	};


	template <typename T> void FindPath(Vector2<T> startPos, Vector2<T> endPos) {
		Node* endNode = new Node(endPos);
		//Vector2<int>* epos = new Vector2<int>; epos->x = floorf(endPos.x); epos->y = floorf(endPos.y);
		//endNode.position = epos;//Vector2<int>(floorf(endPos.x), floorf(endPos.y));
		Node* startNode = new Node(startPos);
		//startNode.position = Vector2<int>(floorf(startPos.x), floorf(startPos.y)); 
		startNode->gCost = 0; startNode->parentNode = nullptr;
		startNode->hCost = floorf((endPos.x -startPos.x) + (endPos.y -startPos.y)); startNode->fCost = startNode->hCost + 0;

		Node::rootNode = startNode;
		Node::targetNode = endNode;

		SearchPath();
	};

	void SearchPath();
	void CheckNeighbours(Node* node);
	//void FindNeighbours(Node* node);
	int iterations;//For Debug and checking
};


#endif // !A_STAR_PATHFINDING_H
