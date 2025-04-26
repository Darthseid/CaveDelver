#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

const int MAP_SIZE = 10;

class Tile
{
public:
    int x, y;
    std::string type;
    bool cleared; // New boolean attribute

    Tile(int x, int y, const std::string& type = "Empty", bool cleared = false)
        : x(x), y(y), type(type), cleared(cleared) {
    }

    void print() const {
        std::cout << "(" << x << "," << y << "): " << type
            << " | Cleared: " << (cleared ? "Yes" : "No") << "\n";
    }
};

class Map 
{
public:
    std::vector<std::vector<Tile>> grid;
    Map() 
    {
        grid.resize(MAP_SIZE, std::vector<Tile>(MAP_SIZE, Tile(0, 0, "Empty")));
        for (int i = 0; i < MAP_SIZE; ++i) {
            for (int j = 0; j < MAP_SIZE; ++j) 
                grid[i][j] = Tile(i, j, "Empty");
        }
    }

    void setTile(int x, int y, const std::string& type) 
    {
        if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) 
            grid[x][y].type = type;
    }

    void printMap() const {
        for (int i = 0; i < MAP_SIZE; ++i) 
        {
            for (int j = 0; j < MAP_SIZE; ++j) 
            {
                std::cout << std::setw(12) << grid[i][j].type;
            }
            std::cout << "\n";
        }
    }

    void generateMap1() 
    {
        int x = 0, y = 9; // Start at (0,5)
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");   // Ensure the grid stays within a 10x10 boundary   
            y += 9; // Move up 9 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        x = 0, y = 5;
            while (x < MAP_SIZE) 
            { 
                setTile(x, y, "Enemy");   // Ensure the grid stays within a 10x10 boundary   
                y += 5; // Move up 5 tiles along the Y-axis
                if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
                {
                    y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                    x++;        // Shift to the next column on X-axis
                }
                if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
            }
        setTile(4, 7, "Enemy");
        setTile(1, 1, "Rest");

        setTile(9, 7, "Trap");
        setTile(7, 7, "Trap"); // Traps
        setTile(8, 6, "Trap");
        setTile(8, 8, "Trap");
        setTile(0, 6, "Trap");

        // Treasure, Boss, Exit Ladder
        setTile(9, 2, "Treasure");
        setTile(8, 7, "Boss");
        setTile(8, 9, "Ladder");
    }
    void generateMap2()
    {
        int x = 0, y = 8; // Start at (0,5)
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");   // Ensure the grid stays within a 10x10 boundary   
            y += 9; // Move up 9 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        x = 0, y = 4;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");   // Ensure the grid stays within a 10x10 boundary   
            y += 5; // Move up 5 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        setTile(4, 8, "Enemy");
        setTile(2, 1, "Rest");

        setTile(5, 2, "Trap");
        setTile(3, 1, "Trap"); // Traps
        setTile(9, 9, "Trap");
        setTile(0, 9, "Trap");
        setTile(0, 1, "Trap");

        // Treasure, Boss, Exit Ladder
        setTile(5, 5, "Treasure");
        setTile(7, 9, "Boss");
        setTile(9, 5, "Ladder");
    }
    void generateMap3()
    {
        int x = 0, y = 7; // Start at (0,5)
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");   // Ensure the grid stays within a 10x10 boundary   
            y += 9; // Move up 9 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        x = 0, y = 3;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");   // Ensure the grid stays within a 10x10 boundary   
            y += 5; // Move up 5 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        setTile(4, 8, "Enemy");
        setTile(2, 1, "Rest");

        setTile(5, 2, "Trap");
        setTile(3, 1, "Trap"); // Traps
        setTile(9, 9, "Trap");
        setTile(0, 9, "Trap");
        setTile(0, 1, "Trap");

        // Treasure, Boss, Exit Ladder
        setTile(5, 5, "Treasure");
        setTile(7, 9, "Boss");
        setTile(9, 5, "Ladder");
    }
    void generateMap4()
    {
        int x = 0, y = 6; // Start at (0,5)
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");   // Ensure the grid stays within a 10x10 boundary   
            y += 9; // Move up 9 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        x = 0, y = 2;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");   // Ensure the grid stays within a 10x10 boundary   
            y += 5; // Move up 5 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        setTile(4, 8, "Enemy");
        setTile(2, 1, "Rest");

        setTile(5, 2, "Trap");
        setTile(3, 1, "Trap"); // Traps
        setTile(9, 9, "Trap");
        setTile(0, 9, "Trap");
        setTile(0, 1, "Trap");

        // Treasure, Boss, Exit Ladder
        setTile(5, 5, "Treasure");
        setTile(7, 9, "Boss");
        setTile(9, 5, "Ladder");
    }
    void generateMap5()
    {
        int x = 0, y = 5; // Start at (0,5)
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Rest");   // Ensure the grid stays within a 10x10 boundary   
            y += 9; // Move up 9 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        x = 0, y = 1;
        while (x < MAP_SIZE)
        {
            setTile(x, y, "Enemy");   // Ensure the grid stays within a 10x10 boundary   
            y += 5; // Move up 5 tiles along the Y-axis
            if (y >= 10)  // When Y exceeds the grid boundary, reset Y and move to the next column (X-axis)
            {
                y = y % 10; // Wrap Y-coordinate to stay within grid bounds
                x++;        // Shift to the next column on X-axis
            }
            if (x >= 10) break;     // Break condition: If X exceeds the grid boundary, exit the loop
        }
        setTile(4, 8, "Enemy");
        setTile(2, 1, "Rest");

        setTile(5, 2, "Trap");
        setTile(3, 1, "Trap"); // Traps
        setTile(9, 9, "Trap");
        setTile(0, 9, "Trap");
        setTile(0, 1, "Trap");

        // Treasure, Boss, Exit Ladder
        setTile(5, 5, "Treasure");
        setTile(7, 9, "Boss");
        setTile(9, 5, "Ladder");
    }
    void saveMap(int mapIndex) const 
    {
        std::ofstream out("Map" + std::to_string(mapIndex) + ".txt");
        if (!out.is_open()) 
        {
            std::cerr << "Failed to save Map" << mapIndex << "\n";
            return;
        }

        for (int x = 0; x < MAP_SIZE; ++x) 
        {
            for (int y = 0; y < MAP_SIZE; ++y) 
            {
                const Tile& t = grid[x][y];
                out << t.x << ' ' << t.y << ' ' << t.type << ' ' << t.cleared << '\n';
            }
        }
        out.close();
    }
    void loadMap(int mapIndex) 
    {
        std::ifstream in("Map" + std::to_string(mapIndex) + ".txt");
        if (!in.is_open()) 
        {
            std::cerr << "No saved map found for Map" << mapIndex << ", using default.\n";
            return;
        }
        int x, y;
        std::string type;
        bool cleared;

        while (in >> x >> y >> type >> cleared)
        {
            setTile(x, y, type);
            grid[x][y].cleared = cleared;
        }
        in.close();
    }
    void showMap(const Map& currentMap, const Player& player) {
        std::cout << "\n=== Map " << player.coordinates[2] << " View ===\n";

        for (int y = MAP_SIZE - 1; y >= 0; --y) {
            for (int x = 0; x < MAP_SIZE; ++x) {
                const Tile& tile = currentMap.grid[x][y];

                if (player.coordinates[0] == x && player.coordinates[1] == y) {
                    std::cout << " P "; // Player position
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
                    else if (tile.type == "Exit") std::cout << " L ";
                    else std::cout << " ? "; // fallback
                }
            }
            std::cout << "\n";
        }
        std::cout << "Legend: P=Player _=Empty E=Enemy B=Boss T=Trap X=Treasure R=Rest L=Ladder ?=Unexplored\n";
    }
};

