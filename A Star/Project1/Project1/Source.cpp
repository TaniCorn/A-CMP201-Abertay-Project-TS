
#include "CustomLoader.h"


int main() {
    //A_Star_Pathfinding_Defined path;
    A_Star_Pathfinding_Undefined path;
    Room nm;
    Room nm1;
    Room nm2;
    Room nm3;

    CompleteMapRead(nm, "CompleteMap50.txt");
    nm.LinkNeighbours(nm);
    PrintMap(nm.GetXSize(), nm.GetYSize(), nm.nodes);
    std::cout << "COMPLETE MAP 50 DONE \n \n \n";

    CompleteMapRead(nm1, "CompleteMapBound1.txt");
    nm1.LinkNeighbours(nm1);
    DisplaceNodeMap(nm1, Vector2<int>(1, 0));
    //PrintMap(nm1.GetXSize(), nm1.GetYSize(), nm1.nodes);
    std::cout << "COMPLETE MAP 50 DONE \n \n \n";

    CompleteMapRead(nm2, "CompleteMapBound2.txt");
    nm2.LinkNeighbours(nm2);
    DisplaceNodeMap(nm2, Vector2<int>(1, 1));
    //PrintMap(nm2.GetXSize(), nm2.GetYSize(), nm2.nodes);

    std::cout << "COMPLETE MAP 50 DONE \n \n \n";

    CompleteMapRead(nm3, "CompleteMapBound3.txt");
    nm3.LinkNeighbours(nm3);
    DisplaceNodeMap(nm3, Vector2<int>(0, 1));
    //PrintMap(nm3.GetXSize(), nm3.GetYSize(), nm3.nodes);

    //All manual for now, if i had time, i'd prefer to make a file system or at least some functions that fully automate this process
    std::cout << "COMPLETE MAP 50 DONE \n \n \n";
    path.rooms.push_back(&nm); path.rooms.push_back(&nm1); path.rooms.push_back(&nm2); path.rooms.push_back(&nm3);
    nm.AddNeighbouringRoom(&nm1);

    nm1.AddNeighbouringRoom(&nm2);
    nm1.AddNeighbouringRoom(&nm);

    nm2.AddNeighbouringRoom(&nm1);
    nm2.AddNeighbouringRoom(&nm3);

    //WTF IS HAPPENING WITH THE ROUTE NODES?
    nm3.AddNeighbouringRoom(&nm2);
    Node* a = nm.GetRouteNodes()[0]; Node* b = nm1.GetRouteNodes()[0];
    nm.DualLinkRouteNodes(*a, *b, EAST);
    a = nm.GetRouteNodes()[1]; b = nm1.GetRouteNodes()[1];
    nm.DualLinkRouteNodes(*a, *b, EAST);

    a = nm1.GetRouteNodes()[2]; b = nm2.GetRouteNodes()[3];
    nm.DualLinkRouteNodes(*a, *b, SOUTH);

    a = nm2.GetRouteNodes()[0]; b = nm3.GetRouteNodes()[2];
    nm.DualLinkRouteNodes(*a, *b, WEST);

    path.SetCurrentRoom(&nm);
    //path.SetCurrentRoom(&nm);
    //path.FindPath(Vector2<int>(200, 100), Vector2<int>(200, 500)); Works for all
    //path.FindPath(Vector2<int>(200, 100), Vector2<int>(1600, 1500)); //works for seg, works for def, works for undef
    //path.FindPath(Vector2<int>(200, 100), Vector2<int>(1050, 1500)); //Seg not best path i think, works for def, works for undef
    //path.FindPath(Vector2<int>(200, 100), Vector2<int>(1100, 3500)); //Seg works, does not work for def, does not work for undef
    
    path.PrintPath();
    //path.PrintRoute();
    //path.PrintRoute();

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