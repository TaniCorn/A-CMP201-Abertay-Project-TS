#include "PathfindingMap.h"

/// <summary>
/// Find opposite direction to direction n
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
int OppositeDirection(Direction n) {
	switch (n)
	{
	case NORTH:
		return SOUTH;
	case EAST:
		return WEST;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	case NORTHWEST:
		return SOUTHEAST;
	case NORTHEAST:
		return SOUTHWEST;
	case SOUTHEAST:
		return NORTHWEST;
	case SOUTHWEST:
		return NORTHEAST;
	default:
		break;
	}
}

/// <summary>
/// I hate this entire piece of code
/// </summary>
/// <param name="nm"></param>
void Room::LinkNeighbours(Room& nm)
{
	int xBound = xSize - 1; int yBound = ySize - 1;
	//Links entire grid except for the edges
	for (int y = 1; y < yBound; y++)
	{
		for (int x = 1; x < xBound; x++)
		{
			nodes[x][y].neighbours[0] = &nodes[x][y - 1];
			nodes[x][y].neighbours[1] = &nodes[x + 1][y];
			nodes[x][y].neighbours[2] = &nodes[x][y + 1];
			nodes[x][y].neighbours[3] = &nodes[x - 1][y];
			nodes[x][y].neighbours[4] = &nodes[x - 1][y - 1];
			nodes[x][y].neighbours[5] = &nodes[x + 1][y - 1];
			nodes[x][y].neighbours[6] = &nodes[x + 1][y + 1];
			nodes[x][y].neighbours[7] = &nodes[x - 1][y + 1];
		}
	}
#pragma region BOUNDS
	//Ceiling and floor
	for (int x = 1; x < xBound; x++)
	{
		//When y = 0, there should never be a -1 in y
		nodes[x][0].neighbours[0] = nullptr;
		nodes[x][0].neighbours[1] = &nodes[x + 1][0];
		nodes[x][0].neighbours[2] = &nodes[x][1];
		nodes[x][0].neighbours[3] = &nodes[x - 1][0];
		nodes[x][0].neighbours[4] = nullptr;
		nodes[x][0].neighbours[5] = nullptr;
		nodes[x][0].neighbours[6] = &nodes[x + 1][1];
		nodes[x][0].neighbours[7] = &nodes[x - 1][1];

		//When y = ySize, there should never be a ysize + 1 in y
		nodes[x][yBound].neighbours[0] = &nodes[x][yBound - 1];
		nodes[x][yBound].neighbours[1] = &nodes[x + 1][yBound];
		nodes[x][yBound].neighbours[2] = nullptr;
		nodes[x][yBound].neighbours[3] = &nodes[x - 1][yBound];
		nodes[x][yBound].neighbours[4] = &nodes[x - 1][yBound - 1];
		nodes[x][yBound].neighbours[5] = &nodes[x + 1][yBound - 1];
		nodes[x][yBound].neighbours[6] = nullptr;
		nodes[x][yBound].neighbours[7] = nullptr;


	}

	//Walls
	for (int y = 1; y < yBound; y++)
	{
		//When x = 0, there should never be a -1 in x
		nodes[0][y].neighbours[0] = &nodes[0][y - 1];
		nodes[0][y].neighbours[1] = &nodes[1][y];
		nodes[0][y].neighbours[2] = &nodes[0][y + 1];
		nodes[0][y].neighbours[3] = nullptr;
		nodes[0][y].neighbours[4] = nullptr;
		nodes[0][y].neighbours[5] = &nodes[1][y - 1];
		nodes[0][y].neighbours[6] = &nodes[1][y + 1];
		nodes[0][y].neighbours[7] = nullptr;

		//When x = xBound, there should never be a xBound + 1 in x
		nodes[xBound][y].neighbours[0] = &nodes[xBound][y - 1];
		nodes[xBound][y].neighbours[1] = nullptr;
		nodes[xBound][y].neighbours[2] = &nodes[xBound][y + 1];
		nodes[xBound][y].neighbours[3] = &nodes[xBound - 1][y];
		nodes[xBound][y].neighbours[4] = &nodes[xBound - 1][y - 1];
		nodes[xBound][y].neighbours[5] = nullptr;
		nodes[xBound][y].neighbours[6] = nullptr;
		nodes[xBound][y].neighbours[7] = &nodes[xBound - 1][y + 1];
	}
	//Top Left Corner
	nodes[0][0].neighbours[0] = nullptr;
	nodes[0][0].neighbours[1] = &nodes[1][0];
	nodes[0][0].neighbours[2] = &nodes[0][1];
	nodes[0][0].neighbours[3] = nullptr;
	nodes[0][0].neighbours[4] = nullptr;
	nodes[0][0].neighbours[5] = nullptr;
	nodes[0][0].neighbours[6] = &nodes[1][1];
	nodes[0][0].neighbours[7] = nullptr;

	//Bottom Left Corner
	nodes[0][yBound].neighbours[0] = &nodes[0][yBound - 1];
	nodes[0][yBound].neighbours[1] = &nodes[1][yBound];
	nodes[0][yBound].neighbours[2] = nullptr;
	nodes[0][yBound].neighbours[3] = nullptr;
	nodes[0][yBound].neighbours[4] = nullptr;
	nodes[0][yBound].neighbours[5] = &nodes[1][yBound - 1];
	nodes[0][yBound].neighbours[6] = nullptr;
	nodes[0][yBound].neighbours[7] = nullptr;

	//Top Right Corner
	nodes[xBound][0].neighbours[0] = nullptr;
	nodes[xBound][0].neighbours[1] = nullptr;
	nodes[xBound][0].neighbours[2] = &nodes[xBound][1];
	nodes[xBound][0].neighbours[3] = &nodes[xBound - 1][0];
	nodes[xBound][0].neighbours[4] = nullptr;
	nodes[xBound][0].neighbours[5] = nullptr;
	nodes[xBound][0].neighbours[6] = nullptr;
	nodes[xBound][0].neighbours[7] = &nodes[xBound - 1][1];

	//Bottom Right Corner
	nodes[xBound][yBound].neighbours[0] = &nodes[xBound][yBound - 1];
	nodes[xBound][yBound].neighbours[1] = nullptr;
	nodes[xBound][yBound].neighbours[2] = nullptr;
	nodes[xBound][yBound].neighbours[3] = &nodes[xBound - 1][yBound];
	nodes[xBound][yBound].neighbours[4] = &nodes[xBound - 1][yBound - 1];
	nodes[xBound][yBound].neighbours[5] = nullptr;
	nodes[xBound][yBound].neighbours[6] = nullptr;
	nodes[xBound][yBound].neighbours[7] = nullptr;

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
#pragma endregion
}


void Room::LinkRouteNodes(Node& node1, Node& node2)
{
	//Just calculates the direction
	Vector2<int> direction = node1.position - node2.position;
	direction.Normalise();
	int lowest = 10;
	int toReplace;
	for (int i = 0; i < 8; i++ )
	{
		int directionWeight = (direction - node1.neighbours[i]->position.Normalize()).Magnitude();
		if (directionWeight < lowest)
		{
			lowest = directionWeight;
			toReplace = i;
		}
	}


	node1.neighbours[toReplace] = &node2;
}

void Room::LinkRouteNodes(Node& node1, Node& node2, int neighbourNode1)
{
	node1.neighbours[neighbourNode1] = &node2;
}

void Room::DualLinkRouteNodes(Node& node1, Node& node2, int neighbourNode1)
{
	node1.neighbours[neighbourNode1] = &node2;
	node2.neighbours[OppositeDirection(Direction(neighbourNode1))] = &node1;
	
}
