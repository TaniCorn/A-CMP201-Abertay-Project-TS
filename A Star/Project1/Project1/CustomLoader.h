//////////
//////////CustomLoader file
//////////Written by Tanapat Somrid 
/////////Starting 08/12/2021
//////// Most Recent Update 29/12/2021
//////// Most Recent change: Fixed Displacement, seperated print map and the map read

#ifndef CUSTOMLOADER_H
#define CUSTOMLOADER_H

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
void PrintMap(const int& xSize, const int& ySize, Node** f) {
    bool newLine = false;
    for (int y = 0; y < ySize; y++)
    {
        for (int x = 0; x < xSize; x++)
        {
            if (f[x][y].position == Vector2<int>(1950, 1400))
            {
                std::cout << "D";
            }
            if (newLine)
            {
                std::cout << '\n';
                std::cout << f[x][y].nodeType << " | ";
                newLine = false;
            }
            else {
                std::cout << f[x][y].nodeType << " | ";
            }
        }
        newLine = true;

    }
    newLine = false;
    for (int y = 0; y < ySize; y++)
    {
        for (int x = 0; x < xSize; x++)
        {
            if (newLine)
            {
                std::cout << '\n';
                std::cout << f[x][y].position.x << "," << f[x][y].position.y << "|";
                newLine = false;
            }
            else {
                std::cout << f[x][y].position.x << "," << f[x][y].position.y << "|";
            }
        }
        newLine = true;

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
    else {
        return;
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
    Vector2<int> lowest = Vector2<int>(9999, 9999), highest = Vector2<int>(0, 0);
    std::vector<Node*> routes;
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
            Vector2<int> pos;
            pos = f[x][y].position;
            pos = pos;
        }
        if (f[x][y].nodeType == Routes)
        {
            routes.push_back(&f[x][y]);
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
    //PrintMap(xSize, ySize, f);
    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {
            if (f[x][y].nodeType == Obstacle)
            {
                obstacleLocations.push_back(f[x][y].position);
            }
        }
    }
    std::cout << "Total size : " << xSize * ySize << std::endl;

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
    std::vector<Vector2<int>> newObstacle;
    Vector2<int> displacementAmount = Vector2<int>(direction.x * (nm.GetHighestCoord().x + nm.GetNodeSize()), direction.y * (nm.GetHighestCoord().y + nm.GetNodeSize()));
    for (int x = 0; x < nm.GetXSize(); x++)
    {
        for (int y = 0; y < nm.GetYSize(); y++)
        {
            nm.nodes[x][y].position += displacementAmount;
        }
    }
    for (int i = 0; i < nm.obstacleLocations.size(); i++)
    {
        nm.obstacleLocations[i] += displacementAmount;
    }
    nm.SetLowestCoord(nm.GetLowestCoord() + displacementAmount);
    nm.SetHighestCoord(nm.GetHighestCoord() + displacementAmount);
}
#endif // !CUSTOMLOADER_H
