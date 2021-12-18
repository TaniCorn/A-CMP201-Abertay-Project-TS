#include "A_Star_Pathfinding.h"

//void A_Star_Pathfinding::PrintPath()
//{
//	Node* current = Node::targetNode;
//
//	while (current->GetParent() != nullptr)
//	{
//		std::cout << current->position << std::endl;
//		std::cout << current->rCost << std::endl;
//	}
//}

//template <typename T> void A_Star_Pathfinding::FindPath(Vector2<T> startPos, Vector2<T> endPos) {
//
//
//	Node* endNode = new Node(); 
//	endNode.position = Vector2<int>(floorf(endPos.x), floorf(endPos.y));
//	Node startNode = new Node(); 
//	startNode.position = Vector2<int>(floorf(startPos.x), floorf(startPos.y)); startNode.gCost = 0; startNode.hCost = floorf((endPos.x - startPos.x) + (endPos.y - startPos.y)); startNode.fCost = startNode.hCost + 0;
//	
//	Node::rootNode = &startNode;
//	Node::targetNode = &endNode;
//
//	std::priority_queue<Node*, std::vector<Node*>, ReverseComparator> priority;
//	std::priority_queue<Node*, std::vector<Node*>, ReverseComparator> conflicts;
//
//	priority.push(&startNode);
//	open.emplace(&startNode);
//
//	int iterations = 0;
//	while (open.size() != 0 || iterations != 5000)
//	{
//
//		//Find lowest fCost Open Node
//		//std::set<Node*>::iterator it = open.begin();
//		//Node* current = *open.begin();
//		Node* current = priority.top();
//		/*for (it = open.begin(); it != open.end(); it++)
//		{
//			Node* closeComp = *it;
//
//			if (current->hCost < closeComp->hCost)
//			{
//				continue;
//			}
//			current = closeComp;
//		}*/
//
//
//		//If we found end, stop pathfinding
//		if (current->DistanceFrom(Node::targetNode->position))
//		{
//			Node::targetNode->SetParent(current);
//			return;
//		}
//
//		//Restructure the current node
//		priority.pop();
//		open.erase(current);
//		closed.insert(current);
//
//		//Neighbours
//		current->GenerateAndCalculateNeighbours();
//
//		for (auto neighbour : current->neighbours)
//		{
//			//Parent
//			if (neighbour == nullptr)
//			{
//				continue;
//			}
//
//			//if neighbour exists in closed, continue
//			if (closed.find(neighbour) != closed.end())
//			{
//				continue;
//			}
//			//if neighbour does not exist in open, insert them into open
//			if (open.find(neighbour) != open.end())
//			{
//				open.insert(neighbour);
//				priority.push(neighbour);
//			}
//
//		}
//
//		//closed.insert(allOpen);
//		//fCostNeighbours.pop();
//		iterations++;
//	}
//
//	//assert(iterations != 5000);
//	//open.swap(openTemp);
//}

//void A_Star_Pathfinding::FindNeighbours(Node* node)
//{
//	std::set<Node*>::iterator it = closed.begin();
//	Node* current = *closed.begin();
//	for (it = open.begin(); it != open.end(); it++)
//	{
//		Node* closeComp = *it;
//
//		if (current->hCost < closeComp->hCost)
//		{
//			continue;
//		}
//		current = closeComp;
//	}
//}

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

bool A_Star_Pathfinding_Defined_Segmented::InCurrentMap()
{
	if (true)
	{

	}
	return false;
}
