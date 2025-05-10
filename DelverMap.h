// DelverMap.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

const int MAP_SIZE = 10;
const int TOTAL_MAPS = 5;

class Tile  // Represents a single Tile (x,y,z) with a type and cleared status
{
public:
    int x, y, z;
    std::string type;
    bool cleared;

    Tile(int x = 0, int y = 0, int z = 0, const std::string& type = "Empty", bool cleared = false)
        : x(x), y(y), z(z), type(type), cleared(cleared) {
    }

    void print() const 
    {
        std::cout << "\n(" << x << "," << y << "," << z << "): "
            << type << " | Cleared: " << (cleared ? "Yes" : "No") << "";
    }
};

class Map  // Represents a 10x10 Map of Tiles (fixed z-level)
{
public:
    int z; // Map level
    std::vector<std::vector<Tile>> grid;
    Map(int zLevel = 0) : z(zLevel) 
    {
        grid.resize(MAP_SIZE, std::vector<Tile>(MAP_SIZE));
        for (int x = 0; x < MAP_SIZE; ++x)
        {
            for (int y = 0; y < MAP_SIZE; ++y)
                grid[x][y] = Tile(x, y, z); //Tiles are 3D. But maps are effectively 2D.
        }
    }

    void setTile(int x, int y, const std::string& type) //Basic Setter.
    {
        if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) //Tiles must be within the bounds of a map.
            grid[x][y].type = type;
    }

    Tile& getTile(int x, int y)
    {
        return grid.at(x).at(y); // bounds-checked for safety
    }
    void printMap(const int playerX, const int playerY) const 
    {
        std::cout << "\n=== Map Floor " << z << " ===";
        for (int y = MAP_SIZE - 1; y >= 0; --y) 
        {
            for (int x = 0; x < MAP_SIZE; ++x) 
            {
                const Tile& tile = grid[x][y];

                if (playerX == x && playerY == y)
                    std::cout << " P "; //This is the player's current position.
                else if (!tile.cleared)
                    std::cout << " ? "; //Unreached tiles are unknown.
                else {
                    if (tile.type == "Empty") std::cout << " _ ";
                    else if (tile.type == "Trap") std::cout << " T ";
                    else if (tile.type == "Treasure") std::cout << " X ";
                    else if (tile.type == "Boss") std::cout << " B ";
                    else if (tile.type == "Enemy") std::cout << " E ";
                    else if (tile.type == "Rest") std::cout << " R ";
                    else if (tile.type == "Ladder") std::cout << " L ";
                    else std::cout << " ? "; //Fall back character.
                }
            }
            std::cout << "";
        }
        std::cout << "\n Legend: P=Player _=Empty E=Enemy B=Boss T=Trap X=Treasure R=Rest L=Ladder ?=Unexplored";
    }

    void saveMap() const 
    {
        std::ofstream out("Map" + std::to_string(z) + ".txt");
        if (!out.is_open())
        {
            std::cerr << "\n Failed to save Map " << z << "\n";
            return;
        }
        for (const auto& row : grid)
        {
            for (const auto& tile : row) 
                out << tile.x << ' ' << tile.y << ' ' << tile.z << ' ' << tile.type << ' ' << tile.cleared << std::endl;;
        }
        out.close();
    }

    void loadMap() 
    {
        std::ifstream in("Map" + std::to_string(z) + ".txt");
        if (!in.is_open())
        {
            std::cerr << "No saved map found for Map " << z << ", using default.\n";
            return;
        }
        int x, y, tileZ;
        std::string type;
        bool cleared;
        while (in >> x >> y >> tileZ >> type >> cleared) 
        {
            if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE)
                grid[x][y] = Tile(x, y, tileZ, type, cleared);
        }
        in.close();
    }
    void generateMap1()
    {
        int x = 0, y = 9;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");
            y += 9;
            if (y >= 10) 
            {
                y %= 10;
                x++;
            }
        }
        x = 0, y = 5;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");
            y += 5;
            if (y >= 10) 
            {
                y %= 10;
                x++;
            }
        }
        setTile(4, 7, "Enemy");
        setTile(1, 1, "Rest");
        setTile(9, 7, "Trap");
        setTile(7, 7, "Trap");
        setTile(8, 6, "Trap");
        setTile(8, 8, "Trap");
        setTile(0, 6, "Trap");

        setTile(9, 2, "Treasure");
        setTile(8, 7, "Boss");
        setTile(8, 9, "Ladder");
    }
    void generateMap2()
    {
        int x = 0, y = 8;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");
            y += 9;
            if (y >= 10) 
            {
                y %= 10;
                x++;
            }
        }
        x = 0, y = 4;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");
            y += 5;
            if (y >= 10) 
            {
                y %= 10;
                x++;
            }
        }
        setTile(4, 8, "Rest");
        setTile(2, 1, "Rest");

        setTile(5, 2, "Trap");
        setTile(3, 1, "Trap");
        setTile(9, 9, "Trap");
        setTile(0, 9, "Trap");
        setTile(0, 1, "Trap");

        setTile(5, 5, "Treasure");
        setTile(7, 9, "Boss");
        setTile(9, 5, "Ladder");
    }
    void generateMap3()
    {
        int x = 0, y = 7;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");
            y += 9;
            if (y >= 10)
            {
                y %= 10;
                x++;
            }
        }
        x = 0, y = 3;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");
            y += 5;
            if (y >= 10)
            {
                y %= 10;
                x++;
            }
        }
        setTile(3, 1, "Rest");
        setTile(5, 1, "Rest");

        setTile(7, 1, "Trap");
        setTile(3, 9, "Trap");
        setTile(9, 7, "Trap");
        setTile(0, 9, "Trap");
        setTile(1, 0, "Trap");

        setTile(5, 4, "Treasure");
        setTile(7, 2, "Boss");
        setTile(8, 5, "Ladder");
    }
    void generateMap4()
    {
        int x = 0, y = 6;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");
            y += 9;
            if (y >= 10)
            {
                y %= 10;
                x++;
            }
        }
        x = 0, y = 2;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");
            y += 5;
            if (y >= 10)
            {
                y %= 10;
                x++;
            }
        }
        setTile(3, 1, "Rest");
        setTile(5, 1, "Rest");

        setTile(6, 3, "Trap");
        setTile(3, 8, "Trap");
        setTile(4, 3, "Trap");
        setTile(8, 6, "Trap");
        setTile(9, 0, "Trap");

        setTile(3, 4, "Treasure");
        setTile(0, 9, "Boss");
        setTile(5, 2, "Ladder");
    }
    void generateMap5()
    {
        int x = 0, y = 5;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");
            y += 9;
            if (y >= 10)
            {
                y %= 10;
                x++;
            }
        }
        x = 0, y = 1;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");
            y += 5;
            if (y >= 10)
            {
                y %= 10;
                x++;
            }
        }
        setTile(3, 3, "Rest");
        setTile(4, 4, "Rest");

        setTile(6, 3, "Trap");
        setTile(3, 8, "Trap");
        setTile(2, 2, "Trap");
        setTile(7, 5, "Trap");
        setTile(9, 3, "Trap");

        setTile(8, 9, "Treasure");
        setTile(9, 9, "Boss"); //No ladder on final map.
    }
};


class Cave // Represents the entire Cave (collection of 5 Maps)
{
public:
    std::vector<Map> floors;

    Cave() 
    {
        for (int i = 0; i < TOTAL_MAPS; ++i)
            floors.emplace_back(i);
        
    }

    Map& getCurrentMap(int z) 
    {
        return floors[z];
    }

    void saveCave() 
    {
        for (auto& map : floors)
            map.saveMap();
    }

    void loadCave() 
    {
        for (auto& map : floors)
            map.loadMap();
    }
};
