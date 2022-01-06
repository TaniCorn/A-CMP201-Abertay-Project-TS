
//////////
//////////Pathfinding Map files // PathfindingMap.h required
//////////Written by Tanapat Somrid 
/////////Starting 18/12/2021
//////// Most Recent Update 06/01/2022
//////// Most Recent change: Quick Fix of some linking issues, neighbour and route issues
#pragma once
#ifndef PATHFINDINGMAP_H
#define PATHFINDINGMAP_H

#include "Node.h"
#include <set>

//Note: Nodesize can be used in various ways. One way in theory was that if we had giant enemies they could only use the 20 size maps, where they move towards size 20 nodes. This would allow it to make sure they couldn't pass through paths too small.

/// <summary>
/// Contains all the information of a node room. Can also be acted upon by a pathfinding algorithm as it has neighbouring rooms and a parent room for paths.
/// </summary>
struct RoomStruct {
public:
	RoomStruct() {
		parent = nullptr;
	}
	~RoomStruct() {
		for (int i = 0; i < xSize - 1; ++i)
		{
			delete[] nodes[i];
		}

	}
protected:
	int xSize;//Remember to access array elements that are -1 to this 
	int ySize;//Remember to access array elements -1 to this
	int nodeSize;//The size of the nodes in this room

public:
	std::vector<Vector2<int>> obstacleLocations;//For undefined

	Node** nodes;//For Defined+

	//For segmented
protected:
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
	std::vector<Node*> GetRouteNodes() { return routeNodes; } void SetRoutNodes(std::vector<Node*> n) { routeNodes = n; }

	std::vector<Vector2<int>> GetObstacleLocations() const { return obstacleLocations; }void SetObstacleLocations(std::vector<Vector2<int>> ol) { obstacleLocations = ol; }
};

/// <summary>
/// Gives functionality for linking nodes
/// </summary>
class Room : public RoomStruct {
public:
	/// <summary>
	/// Links all the nodes with their neighbouring nodes, the room parameter was in place to allow me to use it as a static function.
	/// </summary>
	/// <param name="nm"> self call</param>
	void LinkNeighbours(Room& nm);
	/// <summary>
	/// Uni Directional: Link route nodes with calculation of direction
	/// </summary>
	/// <param name="node1">is the one linking</param>
	/// <param name="node2">is the nieghbour of n1, the one being linked</param>
	void LinkRouteNodes(Node& node1, Node& node2);
	/// <summary>
	/// Uni Directional: Link route nodes with a direction
	/// </summary>
	/// <param name="node1">is the one linking</param>
	/// <param name="node2">is the nieghbour of n1, the one being linked</param>
	/// <param name="neighbourNode1"></param>
	void LinkRouteNodes(Node& node1, Node& node2, int neighbourNode1);
	/// <summary>
	/// Bi directional: Link route nodes with direction from node 1
	/// </summary>
	/// <param name="node1">is the one linking</param>
	/// <param name="node2">is the nieghbour of n1, the one being linked</param>
	/// <param name="neighbourNode1"></param>
	void DualLinkRouteNodes(Node& node1, Node& node2, int neighbourNode1);

	void AutoDualLinkRouteNodes();
	void DualLinkRouteNodes(Node& node1, Node& node2);
};
class Map {
public:
	std::vector<Room*> roomsInMap;
};

#endif // !PATHFINDINGMAP_H
