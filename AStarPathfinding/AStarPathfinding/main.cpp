#include "GridMap.h"
#include "AStarPathfinder.h"

int main()
{
    GridMap map;
    map.Initialize();

    std::cout << "[Original Map]\n";
    map.Print();

    AStarPathfinder pathfinder(map);
    Path path;

    bool found = pathfinder.FindPath(path);

    std::cout << "\nFound: " << (found ? "true" : "false") << '\n';
    std::cout << "Path size: " << path.size() << '\n';

    if (found)
    {
        map.MarkPath(path);

        std::cout << "\n[Pathfinding Result]\n";
        map.Print();
    }
    else
    {
        std::cout << "\nPath not found.\n";
    }

    return 0;
}