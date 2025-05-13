#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

const int MAP_SIZE = 10;
const int TOTAL_MAPS = 5;

class Tile
{
public:
    int x, y, z;
    std::string type;
    bool cleared;

    Tile(int x = 0, int y = 0, int z = 0, const std::string& type = "Empty", bool cleared = false);

    void print() const;
};

class Map
{
public:
    int z;
    std::vector<std::vector<Tile>> grid;
    Map(int zLevel = 0);

    void setTile(int x, int y, const std::string& type);
    Tile& getTile(int x, int y);
    void printMap(const int playerX, const int playerY) const;
    void saveMap() const;
    void loadMap();
    void generateMap1();
    void generateMap2();
    void generateMap3();
    void generateMap4();
    void generateMap5();
};

class Cave
{
public:
    std::vector<Map> floors;

    Cave();
    Map& getCurrentMap(int z);
    void saveCave();
    void loadCave();
};

extern Cave cave;
