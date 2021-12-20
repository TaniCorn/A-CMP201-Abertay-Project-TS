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
		neighbour->CalculateNodeType(currentMap->ObstacleLocations, nodeSize);
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

void A_Star_Pathfinding_Defined_Segmented::SearchPath()
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

void A_Star_Pathfinding_Defined_Segmented::CheckNeighbours(Node* node)
{
}

bool A_Star_Pathfinding_Defined_Segmented::IsNodeInMap(const Room& nm, const Node& target) const
{
	if (nm.highestCoord.x < target.position.x) { return false; }
	if (nm.lowestCoord.x > target.position.x) { return false; }
	if (nm.highestCoord.y < target.position.y) { return false; }
	if (nm.lowestCoord.y > target.position.y){return false;}

	return true;
}

void A_Star_Pathfinding_Defined_Segmented::InitialFindMap()
{
	for (auto nm : maps)
	{
		if (!IsNodeInMap(*nm, *root))
		{
			continue;
		}
		currentMap = nm;

		if (IsNodeInMap(*nm, *target))
		{
			return;
		}
		FindRoute();
	}
}

Node* A_Star_Pathfinding_Defined_Segmented::FindRoute() const
{
}

