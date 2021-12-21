#include "A_Star_Pathfinding.h"


void A_Star_Pathfinding_Undefined::SearchPath()
{
	toSearch.push(root);

	iterations = 0;
	//Considering it is an undefined map, there is an unlikely chance that we could ever have a size of zero
	while (toSearch.size() != 0 && iterations != 1000)
	{

		//Find lowest fCost Open Node
		Node* current = toSearch.top();

		//If we found end, stop pathfinding
		int o = current->DistanceFromM(target->position);//debugging
		if (current->DistanceFromM(target->position) < nodeSize)
		{
			target->SetParent(current);
			return;
		}

		//Restructure the node collections
		toSearch.pop();

		//Neighbours
		current->GenerateNeighbours(nodeSize);
		CheckNeighbours(current);

		iterations++;
	}
}

void A_Star_Pathfinding_Undefined::CheckNeighbours(Node* current)
{
	//For all neighbours : categorise them
	for (auto neighbour : current->neighbours)
	{
		//Parent node
		if (neighbour == nullptr)
		{
			continue;
		}
		neighbour->CalculateNodeType(currentMap->GetObstacleLocations(), nodeSize);
		//If node is an obstacle add it to closed and continue
		if (neighbour->nodeType == Obstacle)
		{
			continue;
		}
		int newGCost = current->GetGCost() + 1; 
		int newHCost = Node::DistanceBetweenM(*neighbour, *target);
		neighbour->SetGCost(newGCost); neighbour->SetHCost(newHCost); neighbour->SetFCost();
		toSearch.push(neighbour);

	}
}
////if neighbour exists in closed, continue ///Shouldn't happen unless the path loops back on itself
//if (searched.find(neighbour) != searched.end())
//{
//	continue;
//}
//if (open.find(neighbour) == open.end())
//{
//	open.insert(neighbour);
//	priority.push(neighbour);
//}

void A_Star_Pathfinding_Defined::SearchPath()
{
	toSearch.insert(root);

	iterations = 0;
	//Considering it is an undefined map, there is an unlikely chance that we could ever have a size of zero
	while (toSearch.size() != 0 && iterations <= 1000)
	{

		//Find lowest fCost Open Node
		Node* current = *toSearch.begin();
		
		//If we found end, stop pathfinding
		int o = current->DistanceFromM(target->position);//debugging
		if (current->DistanceFromM(target->position) < nodeSize)
		{
			return;
		}

		//Restructure the node collections
		toSearch.erase(current);
		searched.insert(current);

		//Neighbours
		//current->GenerateNeighbours(nodeSize);
		CheckNeighbours(current);

		iterations++;
	}
}

void A_Star_Pathfinding_Defined::CheckNeighbours(Node* current)
{
	//For all neighbours : categorise them
	for (auto neighbour : current->neighbours)
	{
		//Parent node
		if (neighbour == nullptr || neighbour->nodeType == Obstacle || searched.find(neighbour) != searched.end())
		{
			continue;
		}

		int newGCost = current->GetGCost() + 1;
		bool inToSearch = toSearch.find(neighbour) == toSearch.end();
		//If neighbour is in either open, and the new path is better, recalculate
		if (!inToSearch && neighbour->GetGCost() > newGCost)
		{
			neighbour->SetGCost(newGCost);
			neighbour->SetFCost();
			neighbour->SetParent(current);
			continue;
		}
		//If neighbour is not in open, set
		if (inToSearch)
		{
			int newHCost = Node::DistanceBetweenM(*neighbour, *target);
			neighbour->SetGCost(newGCost);
			neighbour->SetHCost(newHCost); 
			neighbour->SetFCost();
			neighbour->SetParent(current);
			toSearch.insert(neighbour);

		}

	}
}

void A_Star_Pathfinding_Defined_Segmented::SetUpStartAndEndNodes(Vector2<int> startPos, Vector2<int> endPos)
{
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
	Node* startNode = &currentRoom->nodes[x][y];
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
	Node* endNode = &currentRoom->nodes[x][y];

	//Vector2<int>* epos = new Vector2<int>; epos->x = floorf(endPos.x); epos->y = floorf(endPos.y);
	//endNode.position = epos;//Vector2<int>(floorf(endPos.x), floorf(endPos.y));
	//startNode.position = Vector2<int>(floorf(startPos.x), floorf(startPos.y)); 
	startNode->SetGCost(0); startNode->SetParent(nullptr);
	startNode->SetHCost(floorf((endPos.x - startPos.x) + (endPos.y - startPos.y))); startNode->SetFCost();

	root = startNode;
	target = endNode;
}

void A_Star_Pathfinding_Defined_Segmented::SearchPath()
{
	Node* current = root;

	//While we're not in the same room, search for a path towards the room where our target node is in
	while (!IsNodeInRoom(*currentRoom, *target)) {

		std::queue<Node*> tempTargets = FindRouteNodePaths(BruteForcePathfindMaps());//temporary target nodes that join rooms together towards main target node
		//Pathfind to each target node until we run out(by that point we should be in the same room
		while (!tempTargets.empty())
		{
			Node* tempTargetNode = tempTargets.front();
			if (DefaultAStar(*current, *tempTargetNode))
			{
				current = tempTargetNode;
				tempTargets.pop();
				tempTargetNode = tempTargets.front();
			}
			else {
				//We could not find a path towards the target node
				return;
			}
		}
	}
	//Search normally towards the target node
	if (DefaultAStar(current, target)
	{

	}

}



bool A_Star_Pathfinding_Defined_Segmented::IsNodeInRoom(const RoomStruct& nm, const Node& target) const
{
	if (nm.GetHighestCoord().x < target.position.x) { return false; }
	if (nm.GetLowestCoord().x > target.position.x) { return false; }
	if (nm.GetHighestCoord().y < target.position.y) { return false; }
	if (nm.GetLowestCoord().y > target.position.y){return false;}

	return true;
}

bool A_Star_Pathfinding_Defined_Segmented::IsNodeInRoom(const RoomStruct& nm, const Vector2<int> position) const
{
	if (nm.GetHighestCoord().x < position.x) { return false; }
	if (nm.GetLowestCoord().x > position.x) { return false; }
	if (nm.GetHighestCoord().y < position.y) { return false; }
	if (nm.GetLowestCoord().y > position.y) { return false; }

	return true;
}

void A_Star_Pathfinding_Defined_Segmented::FindCurrentMap(const Vector2<int> rootPosition)
{
	for (int i = 0; i < maps.size(); i++)
	{
		if (IsNodeInRoom(*maps[i], rootPosition))
		{
			currentRoom = maps[i];
			return;
		}
	}
}


std::stack<RoomStruct*> A_Star_Pathfinding_Defined_Segmented::BruteForcePathfindMaps()
{
	std::stack<RoomStruct*> mapRoute;//Rooms we need to go through
	RoomStruct* currentRoomToSearch = currentRoom;//Our current room that we're in

	std::set<RoomStruct*> open; open.insert(currentRoom);

	//Brute force searching of all rooms
	while (open.size() != 0)
	{
		open.erase(open.begin());
		//Search all neighbouring rooms
		for (auto neighbours : currentRoomToSearch->GetNeighbouringRooms())
		{

			neighbours->SetParentRoom(currentRoomToSearch);
			if (IsNodeInRoom(*neighbours, *target))//If room is our target, start pushing path into mapRoute//otherwise add it to the open set
			{

				RoomStruct* route = neighbours;
				while (route->GetParentRoom() != nullptr)//Grab parent room repeatedly to push into routes
				{
					mapRoute.push(route);
					route = route->GetParentRoom();
				}
				return mapRoute;
			};

			open.insert(neighbours);
		}
		currentRoomToSearch = *open.begin();//We have search all neighbours of previous room, get next room
	}
	return mapRoute;

}

std::queue<Node*> A_Star_Pathfinding_Defined_Segmented::FindRouteNodePaths(std::stack<RoomStruct*> mapRoute)
{

	std::queue<Node*> temporaryTargets;//target nodes to travel to, on the way towards main end node
	while (!mapRoute.empty())
	{
		RoomStruct* map = mapRoute.top();
		mapRoute.pop();
		//The temporaryTarget nodes we will be pushing are not the route nodes but the nodes that lead to the next room, that is neighbouring that route node.
		for (auto routeNode : map->GetRouteNodes())
		{
			//Search all neighbours of routeNode
			for (int i = 0; i < 8; i++)
			{
				Node* currentNeighbour = routeNode->neighbours[i];
				if (currentNeighbour != nullptr)
				{
					if (IsNodeInRoom(*mapRoute.top() ,*currentNeighbour))
					{
						temporaryTargets.push(currentNeighbour);
						break;//Unsure if this does as desired. I want it to break the auto loop and move to the next map
					}
				}
			}
		}

	}
}

bool A_Star_Pathfinding_Defined_Segmented::DefaultAStar(Node& startNode, Node& endNode)
{
	std::set<Node*, ReverseComparator> open;
	std::set<Node*> closed; 
	open.insert(&startNode);

	iterations = 0;
	while (open.size() != 0 && iterations <= 1000)
	{

		//Find lowest fCost Open Node
		Node* current = *open.begin();

		//If we found end, stop pathfinding
		int o = current->DistanceFromM(endNode.position);//debugging
		if (current->DistanceFromM(endNode.position) < nodeSize)
		{
			return true;
		}

		//Restructure the node collections
		open.erase(current);
		closed.insert(current);

		//Neighbours
		//current->GenerateNeighbours(nodeSize);
		CheckNeighbours(current, endNode, open, closed);

		iterations++;
	}
	return false;
}
void A_Star_Pathfinding_Defined_Segmented::CheckNeighbours(Node* current, Node& targetNode, std::set<Node*, ReverseComparator> open, std::set<Node*> closed)
{
	//For all neighbours : categorise them
	for (auto neighbour : current->neighbours)
	{
		//Parent node
		if (neighbour == nullptr || neighbour->nodeType == Obstacle || closed.find(neighbour) != closed.end())
		{
			continue;
		}

		int newGCost = current->GetGCost() + 1;
		bool inToSearch = open.find(neighbour) == open.end();
		//If neighbour is in either open, and the new path is better, recalculate
		if (!inToSearch && neighbour->GetGCost() > newGCost)
		{
			neighbour->SetGCost(newGCost);
			neighbour->SetFCost();
			neighbour->SetParent(current);
			continue;
		}
		//If neighbour is not in open, set
		if (inToSearch)
		{
			int newHCost = Node::DistanceBetweenM(*neighbour, targetNode);
			neighbour->SetGCost(newGCost);
			neighbour->SetHCost(newHCost);
			neighbour->SetFCost();
			neighbour->SetParent(current);
			open.insert(neighbour);

		}

	}
}