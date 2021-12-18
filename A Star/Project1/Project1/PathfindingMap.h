
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
	int xSize;//Remember to access array elements -- to this 
	int ySize;//Remember to access array elements -- to this
	int nodeSize;

	std::vector<Vector2<int>> ObstacleLocations;

	Node** nodeMap;

	Vector2<int> lowerBounds; Vector2<int> upperBounds;
	void GenerateMapNodes() {

	}
	void LinkNeighbours(NodeMap& nm) {
		int xBound = xSize - 1; int yBound = ySize - 1;
		//Links entire grid except for the edges
		for (int y = 1; y < yBound - 1; y++)
		{
			for (int x = 1; x < xBound - 1; x++)
			{
				nodeMap[x][y].neighbours[0] = &nodeMap[x][y - 1];
				nodeMap[x][y].neighbours[1] = &nodeMap[x + 1][y];
				nodeMap[x][y].neighbours[2] = &nodeMap[x][y + 1];
				nodeMap[x][y].neighbours[3] = &nodeMap[x - 1][y];
				nodeMap[x][y].neighbours[4] = &nodeMap[x - 1][y - 1];
				nodeMap[x][y].neighbours[5] = &nodeMap[x + 1][y - 1];
				nodeMap[x][y].neighbours[6] = &nodeMap[x + 1][y + 1];
				nodeMap[x][y].neighbours[7] = &nodeMap[x - 1][y + 1];
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
class Map {
public:
	NodeMap nm;

};
#endif // !PATHFINDINGMAP_H
