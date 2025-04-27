// DelverMap.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

const int MAP_SIZE = 10;
const int TOTAL_MAPS = 5;

// Represents a single Tile (x,y,z) with a type and cleared status
class Tile {
public:
    int x, y, z;
    std::string type;
    bool cleared;

    Tile(int x = 0, int y = 0, int z = 0, const std::string& type = "Empty", bool cleared = false)
        : x(x), y(y), z(z), type(type), cleared(cleared) {
    }

    void print() const {
        std::cout << "(" << x << "," << y << "," << z << "): "
            << type << " | Cleared: " << (cleared ? "Yes" : "No") << "\n";
    }
};

// Represents a 10x10 Map of Tiles (fixed z-level)
class Map {
public:
    int z; // Map level
    std::vector<std::vector<Tile>> grid;

    Map(int zLevel = 0) : z(zLevel) {
        grid.resize(MAP_SIZE, std::vector<Tile>(MAP_SIZE));
        for (int x = 0; x < MAP_SIZE; ++x) {
            for (int y = 0; y < MAP_SIZE; ++y) {
                grid[x][y] = Tile(x, y, z);
            }
        }
    }

    void setTile(int x, int y, const std::string& type) {
        if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
            grid[x][y].type = type;
        }
    }

    void printMap(const int playerX, const int playerY) const {
        std::cout << "\n=== Map Floor " << z << " ===\n";
        for (int y = MAP_SIZE - 1; y >= 0; --y) {
            for (int x = 0; x < MAP_SIZE; ++x) {
                const Tile& tile = grid[x][y];

                if (playerX == x && playerY == y) {
                    std::cout << " P ";
                }
                else if (!tile.cleared) {
                    std::cout << " ? ";
                }
                else {
                    if (tile.type == "Empty") std::cout << " _ ";
                    else if (tile.type == "Trap") std::cout << " T ";
                    else if (tile.type == "Treasure") std::cout << " X ";
                    else if (tile.type == "Boss") std::cout << " B ";
                    else if (tile.type == "Enemy") std::cout << " E ";
                    else if (tile.type == "Rest") std::cout << " R ";
                    else if (tile.type == "Ladder") std::cout << " L ";
                    else std::cout << " ? ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "Legend: P=Player _=Empty E=Enemy B=Boss T=Trap X=Treasure R=Rest L=Ladder ?=Unexplored\n";
    }

    void saveMap() const {
        std::ofstream out("Map" + std::to_string(z) + ".txt");
        if (!out.is_open()) {
            std::cerr << "Failed to save Map " << z << "\n";
            return;
        }

        for (const auto& row : grid) {
            for (const auto& tile : row) {
                out << tile.x << ' ' << tile.y << ' ' << tile.z << ' ' << tile.type << ' ' << tile.cleared << '\n';
            }
        }
        out.close();
    }

    void loadMap() {
        std::ifstream in("Map" + std::to_string(z) + ".txt");
        if (!in.is_open()) {
            std::cerr << "No saved map found for Map " << z << ", using default.\n";
            return;
        }

        int x, y, tileZ;
        std::string type;
        bool cleared;

        while (in >> x >> y >> tileZ >> type >> cleared) {
            if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                grid[x][y] = Tile(x, y, tileZ, type, cleared);
            }
        }
        in.close();
    }
};

// Represents the entire Cave (collection of 5 Maps)
class Cave {
public:
    std::vector<Map> floors;

    Cave() {
        for (int i = 0; i < TOTAL_MAPS; ++i) {
            floors.emplace_back(i);
        }
    }

    Map& getCurrentMap(int z) {
        return floors[z];
    }

    void saveCave() {
        for (auto& map : floors) {
            map.saveMap();
        }
    }

    void loadCave() {
        for (auto& map : floors) {
            map.loadMap();
        }
    }
};
