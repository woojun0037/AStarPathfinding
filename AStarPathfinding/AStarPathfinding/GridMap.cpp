#include "GridMap.h"

GridMap::GridMap() : m_start({ 0, 0 }), m_goal({0, 0})
{
}

void GridMap::Initialize()
{
    
    // "　" : 빈 공간(전각 공백)
    // "■" : 벽
    // "S" : 시작점
    // "G" : 도착점
    m_map =
    {
        { "S", ".", ".", ".", ".", ".", ".", ".", ".", "." },
        { "#", "#", "#", "#", "#", "#", "#", "#", "#", "." },
        { ".", ".", ".", ".", ".", ".", ".", ".", "#", "." },
        { ".", "#", "#", "#", "#", "#", "#", ".", "#", "." },
        { ".", ".", ".", ".", ".", ".", "#", ".", "#", "." },
        { ".", "#", "#", "#", "#", ".", "#", ".", "#", "." },
        { ".", "#", ".", ".", ".", ".", "#", ".", ".", "." },
        { ".", "#", ".", "#", "#", "#", "#", "#", "#", "." },
        { ".", ".", ".", ".", ".", ".", ".", ".", ".", "G" }
    };
    
    for (int i = 0; i < static_cast<int>(m_map.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(m_map[i].size()); ++j)
        {
            if (m_map[i][j] == "S")
            {
                m_start = { i, j };
            }
            else if (m_map[i][j] == "G")
            {
                m_goal = {i, j};
            }
        }
    }
}

void GridMap::Print() const
{
    for (const auto& row : m_map)
    {
        for (const auto& cell : row)
        {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

void GridMap::MarkPath(const Path& path)
{
    for (const auto& position : path)
    {
        int x = position.first;
        int y = position.second;

        if (m_map[x][y] != "S" && m_map[x][y] != "G")
        {
            m_map[x][y] = "*";
        }
    }
}

bool GridMap::IsValidPosition(int x, int y) const
{
    return x >= 0 && x < static_cast<int>(m_map.size()) && 
           y >= 0 && y < static_cast<int>(m_map[0].size());
}

bool GridMap::IsWall(int x, int y) const
{
    return m_map[x][y] == "#";
}

int GridMap::GetRowCount() const
{
    return static_cast<int>(m_map.size());
}

int GridMap::GetColCount() const
{
    return static_cast<int>(m_map[0].size());
}

std::pair<int, int> GridMap::GetStart() const
{
    return m_start;
}

std::pair<int, int> GridMap::GetGoal() const
{
    return m_goal;
}
