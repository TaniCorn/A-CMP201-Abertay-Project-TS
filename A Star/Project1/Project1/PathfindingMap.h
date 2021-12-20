
//////////
//////////Pathfinding Map files // PathfindingMap.h required
//////////Written by Tanapat Somrid 
/////////Starting 18/12/2021
//////// Most Recent Update 18/12/2021
//////// Most Recent change: Moved from Node.h
#pragma once
#ifndef PATHFINDINGMAP_H
#define PATHFINDINGMAP_H

#include "Node.h"
#include <set>



/// <summary>
/// Right now, theory is that there can be multiple node maps of different sizes aka mipmaps. It is either this way or calculating if 
/// </summary>
struct RoomStruct {
public:
	RoomStruct() {

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

	std::vector<Vector2<int>> ObstacleLocations;//For undefined

	Node** nodes;//For Defined+

	//For segmented
	Vector2<int> lowestCoord, highestCoord;
	std::set<Node*> routeNodes;
	std::set<RoomStruct*> linkedRooms;
	RoomStruct* parent;

public:
	int GetXSize() { return xSize; } void SetXSize(int x) { xSize = x; }
	int GetYSize() { return ySize; } void SetYSize(int y) { ySize = y; }
	int GetNodeSize() { return nodeSize; } void SetNodeSize(int size) { nodeSize = size; }
};


class Room : public RoomStruct {
public:
	void LinkNeighbours(Room& nm);
	void LinkRouteNodes(Node& node1, Node& node2);
	static void LinkNodeMaps();
};
class Map {
public:
	std::vector<Room*> roomsInMap;
};

#endif // !PATHFINDINGMAP_H
