#include "A_Star_Pathfinding.h"

Node* Node::rootNode = nullptr;
Node* Node::targetNode = nullptr;

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
	std::priority_queue<Node*, std::vector<Node*>, ReverseComparator> conflicts;

	toSearch.push(Node::rootNode);

	iterations = 0;
	//Considering it is an undefined map, there is an unlikely chance that we could ever have a size of zero
	while (toSearch.size() != 0 || iterations != 5000)
	{

		//Find lowest fCost Open Node
		Node* current = toSearch.top();

		//If we found end, stop pathfinding
		int o = current->DistanceFromM(Node::targetNode->position);
		if (current->DistanceFromM(Node::targetNode->position) < 1)
		{
			Node::targetNode->SetParent(current);
			return;
		}

		//Restructure the node collections
		toSearch.pop();
		//searched.insert(current);

		//Neighbours
		current->GenerateAndCalculateNeighbours();
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

		//If node is an obstacle add it to closed and continue
		if (neighbour->nodeType == Obstacle)
		{
			searched.insert(neighbour);
			continue;
		}

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