#pragma once
#include "A_Star_Pathfinding.h"
#include <fstream>
#include <iostream>
#include <string>

void CollisionMapRead(Room& nm) {
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
void CompleteMapRead(Room& nm, std::string fileName) {
    //std::ofstream collisionMap;//
    std::ifstream collisionMap;
    collisionMap.open(fileName);

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
    Node** f = new Node * [xSize];
    std::vector<Node> check;
    for (int i = 0; i < xSize; i++)
    {
        f[i] = new Node[ySize];
    }

    nm.nodeSize = (std::stoi(txtInfo[0]));
    Vector2<int> lowest = Vector2<int>(9999, 9999), highest = Vector2<int>(-9999, -9999);
    std::set<Node*> routes;
    for (int i = 3; i < txtInfo.size(); i++)
    {
        int xStart = 0;
        int xEnd = txtInfo[i].find_last_of(':') + 1;
        int xCoord = std::stoi(txtInfo[i].substr(xStart, xEnd));
        int yStart = txtInfo[i].find_last_of(':') + 1;
        int yEnd = txtInfo[i].npos - 1;
        int yCoord = std::stoi(txtInfo[i].substr(yStart, yEnd));
        char typeOfNode = txtInfo[i].at(txtInfo[i].size() - 1);

        Vector2<int> coord = Vector2<int>(xCoord, yCoord);
        int p = i - 3;
        int x = (p / xSize); int y = p % ySize;
        //f[x, y]->position = Vector2<int>(xCoord, yCoord);
        //f[x, y]->nodeType = NodeType(Obstacle * (typeOfNode == 'O'));
        f[x][y].position = coord;
        f[x][y].nodeType = NodeType((Free + (typeOfNode == 'O') + ((typeOfNode == 'R') * 2)));
        if (f[x][y].nodeType == Routes)
        {
            routes.insert(&f[x][y]);
        }
        for (int n = 0; n < 8; n++)
        {
            f[x][y].neighbours[n] = nullptr;
        }
        check.push_back(f[x][y]);
        if (coord < lowest)
        {
            lowest = coord;
        }
        if (coord > highest)
        {
            highest = coord;
        }
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
    std::cout << std::endl;
    int si = check.size();
    int is = xSize * ySize;
    nm.xSize = xSize; nm.ySize = ySize;
    nm.nodes = f;
    nm.lowestCoord = lowest;
    nm.highestCoord = highest;
    nm.routeNodes = routes;
}

void DisplaceNodeMap(Room& nm, Vector2<int> direction) {
    for (int x = 0; x < nm.GetXSize() - 1; x++)
    {
        for (int y = 0; y < nm.ySize - 1; y++)
        {
            nm.nodes[x][y].position += Vector2<int>(direction.x * nm.highestCoord.x, direction.y * nm.highestCoord.y);
        }
    }
}