

#include "A_Star_Pathfinding.h"
#include <fstream>
#include <iostream>
#include <string>

struct mys {
    mys(float l) { f = l; };
    float f;

    bool operator<(const mys& right) const {
        return f > right.f;
    }
};

void CollisionMapRead(NodeMap& nm) {
    //std::ofstream collisionMap;//
    std::ifstream collisionMap;
    collisionMap.open("CollisionMap.txt");

    std::string line;
    std::vector<std::string> txtInfo;
    if (collisionMap.is_open())
    {
        while (std::getline(collisionMap, line)) {
            txtInfo.push_back(line);
        }
        txtInfo[0].replace(txtInfo[0].find("NodeSize:"), txtInfo[0].find_last_of("NodeSize:") + 1, "");
    }

    nm.nodeSize = (std::stoi(txtInfo[0]));

    for (int i = 1; i < txtInfo.size(); i++)
    {
        int xStart = 0;
        int xEnd = txtInfo[i].find_last_of(':') + 1;
        int xCoord = std::stoi(txtInfo[i].substr(xStart, xEnd));
        int yStart = txtInfo[i].find_last_of(':') + 1;
        int yEnd = txtInfo[i].npos;
        int yCoord = std::stoi(txtInfo[i].substr(yStart, yEnd));
        nm.ObstacleLocations.push_back(Vector2<int>{xCoord, yCoord});
    }
}
void CompleteMapRead(NodeMap& nm) {
    //std::ofstream collisionMap;//
    std::ifstream collisionMap;
    collisionMap.open("CompleteMap50.txt");

    std::string line;
    std::vector<std::string> txtInfo;
    if (collisionMap.is_open())
    {
        while (std::getline(collisionMap, line)) {
            txtInfo.push_back(line);
        }
        txtInfo[0].replace(txtInfo[0].find("NodeSize:"), txtInfo[0].find_last_of("NodeSize:") + 1, "");
    }

    int xSize = std::stoi(txtInfo[1]);
    int ySize = std::stoi(txtInfo[2]);
    Node** f = new Node *[xSize];
    std::vector<Node> check;
    for (int i = 0; i < xSize; i++)
    {
        f[i] = new Node[ySize];
    }

    nm.nodeSize = (std::stoi(txtInfo[0]));

    for (int i = 3; i < txtInfo.size(); i++)
    {
        int xStart = 0;
        int xEnd = txtInfo[i].find_last_of(':') + 1;
        int xCoord = std::stoi(txtInfo[i].substr(xStart, xEnd));
        int yStart = txtInfo[i].find_last_of(':') + 1;
        int yEnd = txtInfo[i].npos - 1;
        int yCoord = std::stoi(txtInfo[i].substr(yStart, yEnd));
        char typeOfNode = txtInfo[i].at(txtInfo[i].size() - 1);

        int p = i - 3;
        int x = (p / xSize); int y = p % ySize;
        //f[x, y]->position = Vector2<int>(xCoord, yCoord);
        //f[x, y]->nodeType = NodeType(Obstacle * (typeOfNode == 'O'));
        f[x][y].position = Vector2<int>(xCoord, yCoord);
        f[x][y].nodeType = NodeType(Obstacle * (typeOfNode == 'O'));
        for (int n = 0; n < 8; n++)
        {
            f[x][y].neighbours[n] = nullptr;
        }
        check.push_back(f[x][y]);
    }
    bool newLine = false;
    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {
            if (newLine)
            {
               std::cout << f[x][y].nodeType << std::endl;
                newLine = false;
            }
            else {
                std::cout << f[x][y].nodeType << " | ";
            }
            if (f[x][y].nodeType == Obstacle)
            {
                nm.ObstacleLocations.push_back(f[x][y].position);
            }
        }
        newLine = true;

    }
    int si = check.size();
    int is = xSize * ySize;
    nm.xSize = xSize; nm.ySize = ySize;
    nm.nodeMap = f;
}

int main() {
    A_Star_Pathfinding_Default path;
    NodeMap nm;
    CompleteMapRead(nm);
    nm.LinkNeighbours();
    path.SetMap(&nm);
    path.FindPath(nm.nodeMap[24][25].position, nm.nodeMap[0][0].position);

    //A_Star_Pathfinding_Undefined path;
    //NodeMap nm;
    //CompleteMapRead(&nm);
    //path.SetMap(&nm);
    //path.FindPath(nm.nodeMap[0][0].position, nm.nodeMap[x][y].position);
    path.PrintPath();
    //path.FindPath(Vector2<int>(1200, 700), Vector2<int>(1400, 900));
    //path.PrintPath();

    //std::priority_queue<mys> p;
    //p.push(mys(5));
    //p.push(mys(1));
    //p.push(mys(2));
    //p.push(mys(1));
    //p.push(mys(3));
    //p.push(mys(8));
    //mys l = p.top();
    //std::cout << p.top()
    return 0;
}

//Todo:
/*
Implement Defined Segmented A star
Implement Defined A Star

*/