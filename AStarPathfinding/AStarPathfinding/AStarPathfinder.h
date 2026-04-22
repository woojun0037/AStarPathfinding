#pragma once
#include "GridMap.h"
#include "Node.h"

using namespace std;

class AStarPathfinder
{
public :
    explicit AStarPathfinder(const GridMap& gridMap);

    bool FindPath(Path& outpath);

private:
    struct CompareNode
    {
        bool operator()(const Node& a, const Node& b) const
        {
            return a.f > b.f;
        }
    };

private:
    int CalculateHeuristic(int x1, int y1, int x2, int y2) const;

    Path ReconstructPath(const vector<vector<Position>>& parent, Position start, Position goal) const;

private:
    const GridMap& m_map;
};