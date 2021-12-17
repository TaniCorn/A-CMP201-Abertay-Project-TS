//////////
//////////Node Map files
//////////Written by Tanapat Somrid 
/////////Starting 08/12/2021
//////// Most Recent Update 17/12/2021
//////// Most Recent change: Fixing a heap corruption


#pragma once
#ifndef NODEMAP_H
#define NODEMAP_H

#include "VectorPositions.h"
#include <vector>

static int inclination = 2;//How weighted should our path be towards the target node?

enum NodeType
{
	Free = 0,
	Obstacle = 1,
};

/// <summary>
/// This node class is a 
/// The node class uses a tree system.
/// </summary>
class Node {
public:
#pragma region CONSTRUCTORS
	/// <summary>
/// Constructor For Start and End Nodes
/// </summary>
	Node() {
		gCost = 0; nodeType = Free;
	}
	/// <summary>
	/// Constructor for new Nodes
	/// </summary>
	Node(const Vector2<int>& newPosition) {
		nodeType = Free;
		position = newPosition;

		//NodeType

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
	Node(const Node& a) { fCost = a.fCost; gCost = a.gCost; hCost = a.hCost; position = a.position; nodeType = a.nodeType; parentNode = a.parentNode; for (int i = 0; i < 4; i++) { neighbours[i] = a.neighbours[i]; }; }
	Node& operator =(const Node& copy) { fCost = copy.fCost; gCost = copy.gCost; hCost = copy.hCost; position = copy.position; nodeType = copy.nodeType; parentNode = copy.parentNode; for (int i = 0; i < 4; i++) { neighbours[i] = copy.neighbours[i]; }; return *this; }


	~Node() {
	}
#pragma endregion

public:
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
	int DistanceFromM(int x, int y) { return (abs(x - position.x) + abs(y - position.y)); }
	/// <summary>
	/// The MANHATTAN distance from this node and the given vector (position.x and position.y)
	/// </summary>
	/// <returns>MANHATTAN DISTANCE</returns>
	int DistanceFromM(const Vector2<int>& pos) {
		int total = (abs(pos.x - position.x) + abs(pos.y - position.y));
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
		int total = (abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y));
		return total;
	}
#pragma endregion


#pragma region CHARACTERISTICS
private:
	float fCost;//totalCost
	float gCost;//cost of current path
	float hCost;//how far away we are from target Node
public:
	Vector2<int> position = Vector2<int>(0, 0);//Our position, it's unique


	Node* neighbours[8];//NESW of node
	Node* parentNode;//Node that this node branched from
	//bool closed = false;//Is this closed? We could either check if this position exists in closed or just do this.

	NodeType nodeType;//Is this an obstacle? If so we can't pass through it
#pragma endregion


#pragma region FUNCTIONS
public:
	/// <summary>
/// Generate all neighbours
/// </summary>
	void GenerateNeighbours(int nodeSize) {
		Generate4Neighbours(nodeSize);
	};
	void CalculateNodeType(const std::vector<Vector2<int>>& obsMap, int nodeSize) {
		for (int i = 0; i < obsMap.size(); i++)
		{
			if (Vector2<int>::DistanceBetween(obsMap[i], position) < nodeSize)
			{
				nodeType = Obstacle;
				return;
			}
		}
		nodeType = Free;
	};

private:
	/// <summary>
	/// Generates neighbours in 4 direcions (NESW)
	/// </summary>
	void Generate4Neighbours(int nodeSize) {
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
		for (int i = 0; i < 4; i++)
		{
			if (neighbours[i] != nullptr)
			{
				neighbours[i]->parentNode = this;
			}
		}
	}
	void Search8Neighbours() {
		for (int x = -1; x < x <= 1; x++)
		{
			for (int y = -1; y < y <= 1; y++)
			{

			}
		}
	};

#pragma endregion

public:
#pragma region GETTERS/SETTERS
	void SetHCost(int h) {
		hCost = h * inclination;
	}
    int GetHCost() const {
		return hCost;
	}
	void SetGCost(int g) {
		gCost = g;
	}
	int GetGCost() const {
		return gCost;
	}	
	//Calculates and assigns with inclination
	void SetFCost() {
		fCost = hCost + gCost;
	}
	//Not preferred
	void SetFCost(int f) {
		fCost = f;
	}
	int GetFCost() const {
		return fCost;
	}
	void SetParent(Node* parent) {
		parentNode = parent;
	}
	Node* GetParent() const {
		return parentNode;
	}
#pragma endregion


};

/// <summary>
/// Right now, theory is that there can be multiple node maps of different sizes aka mipmaps. It is either this way or calculating if 
/// </summary>
struct NodeMap {
public:
	NodeMap() {

	}
	~NodeMap() {
		for (int i = 0; i < xSize; ++i)
		{
			delete[] nodeMap[i];
		}
		delete[] nodeMap;

	}
	std::vector<Vector2<int>> ObstacleLocations;
	Node** nodeMap; 
	int xSize;//Remember to access array elements -- to this 
	int ySize;//Remember to access array elements -- to this
	int nodeSize;

	void GenerateMapNodes() {

	}
	void LinkNeighbours() {
		int xBound = xSize - 1; int yBound = ySize - 1;
		//Links entire grid except for the edges
		for (int y = 1; y < yBound - 1; y++)
		{
			for (int x = 1; x < xBound - 1; x++)
			{
				nodeMap[x][y].neighbours[0] = &nodeMap[x]		[y - 1];
				nodeMap[x][y].neighbours[1] = &nodeMap[x + 1]	[y];
				nodeMap[x][y].neighbours[2] = &nodeMap[x]		[y + 1];
				nodeMap[x][y].neighbours[3] = &nodeMap[x - 1]	[y];
				nodeMap[x][y].neighbours[4] = &nodeMap[x - 1]	[y-1];
				nodeMap[x][y].neighbours[5] = &nodeMap[x + 1]	[y-1];
				nodeMap[x][y].neighbours[6] = &nodeMap[x + 1]	[y + 1];
				nodeMap[x][y].neighbours[7] = &nodeMap[x - 1]	[y + 1];
			}
		}
	#pragma region BOUNDS
		//Ceiling and floor
		for (int x = 1; x < xBound - 1; x++)
		{
			//When y = 0, there should never be a -1 in y
			nodeMap[x][0].neighbours[0] = nullptr;
			nodeMap[x][0].neighbours[1] = &nodeMap[x + 1][0];
			nodeMap[x][0].neighbours[2] = &nodeMap[x][1];
			nodeMap[x][0].neighbours[3] = &nodeMap[x - 1][0];
			nodeMap[x][0].neighbours[4] = nullptr;
			nodeMap[x][0].neighbours[5] = nullptr;
			nodeMap[x][0].neighbours[6] = &nodeMap[x + 1][1];
			nodeMap[x][0].neighbours[7] = &nodeMap[x - 1][1];

			//When y = ySize, there should never be a ysize + 1 in y
			nodeMap[x][yBound].neighbours[0] = &nodeMap[x][yBound - 1];
			nodeMap[x][yBound].neighbours[1] = &nodeMap[x + 1][yBound];
			nodeMap[x][yBound].neighbours[2] = nullptr;
			nodeMap[x][yBound].neighbours[3] = &nodeMap[x - 1][yBound];
			nodeMap[x][yBound].neighbours[4] = &nodeMap[x - 1][yBound - 1];
			nodeMap[x][yBound].neighbours[5] = &nodeMap[x + 1][yBound - 1];
			nodeMap[x][yBound].neighbours[6] = nullptr;
			nodeMap[x][yBound].neighbours[7] = nullptr;
		}
		//Walls
		for (int y = 1; y < yBound - 1; y++)
		{
			//When x = 0, there should never be a -1 in x
			nodeMap[0][y].neighbours[0] = &nodeMap[0][y - 1];
			nodeMap[0][y].neighbours[1] = &nodeMap[1][y];
			nodeMap[0][y].neighbours[2] = &nodeMap[0][y + 1];
			nodeMap[0][y].neighbours[3] = nullptr;
			nodeMap[0][y].neighbours[4] = nullptr;
			nodeMap[0][y].neighbours[5] = &nodeMap[1][y - 1];
			nodeMap[0][y].neighbours[6] = &nodeMap[1][y + 1];
			nodeMap[0][y].neighbours[7] = nullptr;

			//When x = xBound, there should never be a xBound + 1 in x
			nodeMap[xBound][y].neighbours[0] = &nodeMap[xBound][y - 1];
			nodeMap[xBound][y].neighbours[1] = nullptr;
			nodeMap[xBound][y].neighbours[2] = &nodeMap[xBound][y + 1];
			nodeMap[xBound][y].neighbours[3] = &nodeMap[xBound - 1][y];
			nodeMap[xBound][y].neighbours[4] = &nodeMap[xBound - 1][y - 1];
			nodeMap[xBound][y].neighbours[5] = nullptr;
			nodeMap[xBound][y].neighbours[6] = nullptr;
			nodeMap[xBound][y].neighbours[7] = &nodeMap[xBound - 1][y + 1];
		}
		//Top Left Corner
		nodeMap[0][0].neighbours[0] = nullptr;
		nodeMap[0][0].neighbours[1] = &nodeMap[1][0];
		nodeMap[0][0].neighbours[2] = &nodeMap[0][1];
		nodeMap[0][0].neighbours[3] = nullptr;
		nodeMap[0][0].neighbours[4] = nullptr;
		nodeMap[0][0].neighbours[5] = nullptr;
		nodeMap[0][0].neighbours[6] = &nodeMap[1][1];
		nodeMap[0][0].neighbours[7] = nullptr;

		//Bottom Left Corner
		nodeMap[0][yBound].neighbours[0] = &nodeMap[0][yBound - 1];
		nodeMap[0][yBound].neighbours[1] = &nodeMap[1][yBound];
		nodeMap[0][yBound].neighbours[2] = nullptr;
		nodeMap[0][yBound].neighbours[3] = nullptr;
		nodeMap[0][yBound].neighbours[4] = nullptr;
		nodeMap[0][yBound].neighbours[5] = &nodeMap[1][yBound - 1];
		nodeMap[0][yBound].neighbours[6] = nullptr;
		nodeMap[0][yBound].neighbours[7] = nullptr;

		//Top Right Corner
		nodeMap[xBound][0].neighbours[0] = nullptr;
		nodeMap[xBound][0].neighbours[1] = nullptr;
		nodeMap[xBound][0].neighbours[2] = &nodeMap[xBound][1];
		nodeMap[xBound][0].neighbours[3] = &nodeMap[xBound - 1][0];
		nodeMap[xBound][0].neighbours[4] = nullptr;
		nodeMap[xBound][0].neighbours[5] = nullptr;
		nodeMap[xBound][0].neighbours[6] = nullptr;
		nodeMap[xBound][0].neighbours[7] = &nodeMap[xBound - 1][1];

		//Bottom Right Corner
		nodeMap[xBound][yBound].neighbours[0] = &nodeMap[xBound][yBound - 1];
		nodeMap[xBound][yBound].neighbours[1] = nullptr;
		nodeMap[xBound][yBound].neighbours[2] = nullptr;
		nodeMap[xBound][yBound].neighbours[3] = &nodeMap[xBound - 1][yBound];
		nodeMap[xBound][yBound].neighbours[4] = &nodeMap[xBound - 1][yBound - 1];
		nodeMap[xBound][yBound].neighbours[5] = nullptr;
		nodeMap[xBound][yBound].neighbours[6] = nullptr;
		nodeMap[xBound][yBound].neighbours[7] = nullptr;
#pragma endregion

		

		/*for (int x = 0; x < xSize; x++)
		{
			for (int y = 0; y < ySize; y++)
			{
				if (x == 0 && y == ySize)//Don't link [3][4][7][2][6]
				{

				}
				if (x == 0 && y == 0)//Don't link [3][4][7][0][5]
				{

				}
				if (x == xSize && y == 0)//Don't link [1][5][6][0][4]
				{

				}
				if (x == xSize && y == ySize)//Don't link[1][5][6][2][7]
				{

				}
				if (x == 0)//Don't link [3][4][7]
				{

				}
				if (x == xSize)//Don't link[1][5][6]
				{

				}
				if (y == 0)//Don't link[0][4][5]
				{

				}
				if (y == ySize)//Don't link[2][6][7]
				{

				}
				
			}
		}*/
	}
};

#endif // !NODEMAP_H