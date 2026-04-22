#pragma once
#include "Types.h"

class GridMap
{
public:
    GridMap();

    void Initialize();
    void Print() const;
    void MarkPath(const Path& path);

    bool IsValidPosition(int x, int y) const;
    bool IsWall(int x, int y) const;

    int GetRowCount()const;
    int GetColCount()const;

    Position GetStart() const;
    Position GetGoal()  const;
    
private:
    std::vector<std::vector<std::string>> m_map;
    Position m_start;
    Position m_goal;
};