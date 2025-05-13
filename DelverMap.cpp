#include "DelverMap.h"

Tile::Tile(int x, int y, int z, const std::string& type, bool cleared)
    : x(x), y(y), z(z), type(type), cleared(cleared) {}

void Tile::print() const
{
    std::cout << "\n(" << x << "," << y << "," << z << "): "
        << type << " | Cleared: " << (cleared ? "Yes" : "No") << "";
}

Map::Map(int zLevel)
    : z(zLevel)
{
    grid.resize(MAP_SIZE, std::vector<Tile>(MAP_SIZE));
    for (int x = 0; x < MAP_SIZE; ++x)
    {
        for (int y = 0; y < MAP_SIZE; ++y)
            grid[x][y] = Tile(x, y, z);
    }
}

void Map::setTile(int x, int y, const std::string& type)
{
    if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE)
        grid[x][y].type = type;
}

Tile& Map::getTile(int x, int y)
{
    return grid.at(x).at(y);
}

void Map::printMap(const int playerX, const int playerY) const
{
    std::cout << "\n=== Map Floor " << z << " ===\n";
    for (int y = MAP_SIZE - 1; y >= 0; --y)
    {
        for (int x = 0; x < MAP_SIZE; ++x)
        {
            const Tile& tile = grid[x][y];

            if (playerX == x && playerY == y)
                std::cout << " P ";
            else if (!tile.cleared)
                std::cout << " ? ";
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
        std::cout << std::endl;
    }
    std::cout << " Legend: P=Player _=Empty E=Enemy B=Boss T=Trap X=Treasure R=Rest L=Ladder ?=Unexplored\n";
}

void Map::saveMap() const
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
            out << tile.x << ' ' << tile.y << ' ' << tile.z << ' ' << tile.type << ' ' << tile.cleared << std::endl;
    }
    out.close();
}

void Map::loadMap()
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

void Map::generateMap1()
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

void Map::generateMap2()
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

void Map::generateMap3()
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

void Map::generateMap4()
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

void Map::generateMap5()
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
    setTile(9, 9, "Boss");
}

Cave::Cave()
{
    for (int i = 0; i < TOTAL_MAPS; ++i)
        floors.emplace_back(i);
}

Map& Cave::getCurrentMap(int z)
{
    return floors[z];
}

void Cave::saveCave()
{
    for (auto& map : floors)
        map.saveMap();
}

void Cave::loadCave()
{
    for (auto& map : floors)
        map.loadMap();
}