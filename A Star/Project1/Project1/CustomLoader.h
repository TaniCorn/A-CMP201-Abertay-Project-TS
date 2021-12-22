#pragma once
#include "A_Star_Pathfinding.h"
#include <fstream>
#include <iostream>
#include <string>

void CollisionMapRead(Room& nm) {
    //std::ofstream collisionMap;//
    std::ifstream collisionMap;
    collisionMap.open("CollisionMap.txt");

    std::vector<Vector2<int>> obstacleLocations;
    std::string line;
    std::vector<std::string> txtInfo;
    if (collisionMap.is_open())
    {
        while (std::getline(collisionMap, line)) {
            txtInfo.push_back(line);
        }
        txtInfo[0].replace(txtInfo[0].find("NodeSize:"), txtInfo[0].find_last_of("NodeSize:") + 1, "");
    }
    nm.SetNodeSize(std::stoi(txtInfo[0]));

    for (int i = 1; i < txtInfo.size(); i++)
    {
        int xStart = 0;
        int xEnd = txtInfo[i].find_last_of(':') + 1;
        int xCoord = std::stoi(txtInfo[i].substr(xStart, xEnd));
        int yStart = txtInfo[i].find_last_of(':') + 1;
        int yEnd = txtInfo[i].npos;
        int yCoord = std::stoi(txtInfo[i].substr(yStart, yEnd));
        obstacleLocations.push_back(Vector2<int>{xCoord, yCoord});
    }
    nm.SetObstacleLocations(obstacleLocations);
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

    std::vector<Vector2<int>> obstacleLocations;
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
                obstacleLocations.push_back(f[x][y].position);
            }
        }
        newLine = true;

    }
    nm.SetNodeSize(std::stoi(txtInfo[0]));
    nm.SetObstacleLocations(obstacleLocations);
    std::cout << std::endl;
    int si = check.size();
    int is = xSize * ySize;
    nm.SetXSize(xSize); nm.SetYSize(ySize);
    nm.nodes = f;
    nm.SetLowestCoord(lowest);
    nm.SetHighestCoord(highest);
    nm.SetRoutNodes(routes) ;
}

void DisplaceNodeMap(Room& nm, Vector2<int> direction) {
    for (int x = 0; x < nm.GetXSize() - 1; x++)
    {
        for (int y = 0; y < nm.GetYSize() - 1; y++)
        {
            nm.nodes[x][y].position += Vector2<int>(direction.x * nm.GetHighestCoord().x, direction.y * nm.GetHighestCoord().y);
        }
    }
}