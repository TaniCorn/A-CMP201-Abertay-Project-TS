
#include "CustomLoader.h"


int main() {
    A_Star_Pathfinding_Defined_Segmented path;
    Room nm;
    Room nm1;

    CompleteMapRead(nm, "CompleteMap50.txt");
    CompleteMapRead(nm1, "CompleteMapBound.txt");
    DisplaceNodeMap(nm, Vector2<int>(0, -1));
    path.SetMap(&nm);

    return 0;
}

/*
1.FindMapFor(StartNode)
2.while(!IsTargetInCurrentMap()){
3.ImplementRoomAStar()  
4.}
5.ImplementDefaultAStar()
6.return;}


3.1ImplementRoomAStar(){
3.2FindMapFor(EndNode)
3.3ImplementDefaultAStarOnRoomScale()
3.4 While temporaryTargets is not empty{
3.5 ImplementDefaultAStarToTemporaryTarget
3.6}//When we reach a route node we should calculate a new route using that route node and the next route node as the start and endpoints
3.7}

3.3.1ImplementDefaultAStarOnRoomScale(){
3.3.2//When path found
3.3.3FindRouteNodeConnections();
3.3.4}

3.3.3.1FindRoutNodeConnections(){
3.3.3.2std::Queue<Node*> temporaryTargets;//FirstInFirstOut
3.3.3.3for each routeNodes in MapRoute//starting from current
3.3.3.4    for each routeNode neighbours
3.3.3.5        if neighbour is in (MapRoute + 1) then
3.3.3.6            add routeNode to temporaryTargets
3.3.3.7            break;
}


What this means:
Each Node can remain the same
Each NodeMap will have to be reconfigured to act like nodes as well, but assune that they have infinite neighbours(door in the center teleports to under ground map for example)
//The need to have neighbours and parents//Maybe there's a nicer way we can do this?
//Or we could create temporary nodes that take place of the maps, but we just make sure the neihbouring of those are correct. 
//Then when the path is found we can use the nodes path and map that to the room pathing, with parenting or just a queue
//Map route doesn't need to be a parenting thing, we could jsut make it a queue/stack
A Star Default might have to be rebuilt to allow segment to use it?

As for searching the Maps, we might be better off bruteforcing it.

//Currently it's assumed that each node costs 1 to move, change in the future?

*/