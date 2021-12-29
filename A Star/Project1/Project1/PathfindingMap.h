
//////////
//////////Pathfinding Map files // PathfindingMap.h required
//////////Written by Tanapat Somrid 
/////////Starting 18/12/2021
//////// Most Recent Update 29/12/2021
//////// Most Recent change: Changed a set of routnodes to a vector of routenodes. Completed the linkRouteNode functions
#pragma once
#ifndef PATHFINDINGMAP_H
#define PATHFINDINGMAP_H

#include "Node.h"
#include <set>


//struct PositionComparator {
//public:
//	bool operator ()(const Node* a, const Node* b) const {
//		return (a->position < b->position);
//	}
//};
/// <summary>
/// Right now, theory is that there can be multiple node maps of different sizes aka mipmaps. It is either this way or calculating if 
/// </summary>
struct RoomStruct {
public:
	RoomStruct() {
		parent = nullptr;
	}
	~RoomStruct() {
		for (int i = 0; i < xSize; ++i)
		{
			delete[] nodes[i];
		}
		delete[] nodes;

	}
protected:
	int xSize;//Remember to access array elements -- to this 
	int ySize;//Remember to access array elements -- to this
	int nodeSize;

public:
	std::vector<Vector2<int>> obstacleLocations;//For undefined

	Node** nodes;//For Defined+
protected:
	//For segmented
	Vector2<int> lowestCoord, highestCoord;
	std::vector<Node*> routeNodes;
	std::set<RoomStruct*> neighbouringRooms;
	RoomStruct* parent;

public:
	int GetXSize() const { return xSize; } void SetXSize(int x) { xSize = x; }
	int GetYSize()const { return ySize; } void SetYSize(int y) { ySize = y; }
	int GetNodeSize() const { return nodeSize; } void SetNodeSize(int size) { nodeSize = size; }
	Vector2<int> GetLowestCoord()const { return lowestCoord; } Vector2<int> GetHighestCoord() const { return highestCoord; }
	void SetLowestCoord(Vector2<int> low) { lowestCoord = low; } void SetHighestCoord(Vector2<int> high) { highestCoord = high; }
	std::set<RoomStruct*> GetNeighbouringRooms() const { return neighbouringRooms; } void SetNeighbouringRooms(std::set<RoomStruct*> nr) { neighbouringRooms = nr; } void AddNeighbouringRoom(RoomStruct* room) { neighbouringRooms.insert(room); }
	RoomStruct* GetParentRoom() const { return parent; } void SetParentRoom(RoomStruct* rs) { parent = rs; }
	std::vector<Node*> GetRouteNodes() { return routeNodes; } void SetRoutNodes(std::vector<Node*> n) { routeNodes = n; } //Node* GetRouteNode(int number) { return *(routeNodes.begin() + 1)); }

	std::vector<Vector2<int>> GetObstacleLocations() const { return obstacleLocations; }void SetObstacleLocations(std::vector<Vector2<int>> ol) { obstacleLocations = ol; }
};


class Room : public RoomStruct {
public:
	void LinkNeighbours(Room& nm);
	void LinkRouteNodes(Node& node1, Node& node2);
	void LinkRouteNodes(Node& node1, Node& node2, int neighbourNode1);
	void DualLinkRouteNodes(Node& node1, Node& node2, int neighbourNode1);
};
class Map {
public:
	std::vector<Room*> roomsInMap;
};

#endif // !PATHFINDINGMAP_H
