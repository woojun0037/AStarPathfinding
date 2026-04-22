#include "AStarPathfinder.h"

AStarPathfinder::AStarPathfinder(const GridMap& gridMap) : m_map(gridMap)
{
}

bool AStarPathfinder::FindPath(Path& outpath)
{
    int rows = m_map.GetRowCount();
    int cols = m_map.GetColCount();

    Position start = m_map.GetStart();
    Position goal  = m_map.GetGoal();

    priority_queue<Node, vector<Node>, CompareNode> openList;

    vector<vector<bool>>closed(rows, vector<bool>(cols, false));
    vector<vector<int>>gCost(rows, vector<int>(cols, numeric_limits<int>::max()));

    vector<vector<Position>> parent(rows, vector<Position>(cols, { -1, -1 }));

    int startH = CalculateHeuristic(start.first, start.second, goal.first, goal.second);

    openList.push(Node(start.first, start.second, 0, startH, -1, -1));
    gCost[start.first][start.second] = 0;

    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = {  0, 0,-1, 1 };

    while (!openList.empty())
    {
        Node current = openList.top();
        openList.pop();

        int currentX = current.x;
        int currentY = current.y;

        if (closed[currentX][currentY])
        {
            continue;
        }
        closed[currentX][currentY] = true;

        if (currentX == goal.first && currentY == goal.second)
        {
            outpath = ReconstructPath(parent, start, goal);
            return true;
        }

        for (int direction = 0; direction < 4; ++direction)
        {
            int nextX = currentX + dx[direction];
            int nextY = currentY + dy[direction];

            if (!m_map.IsValidPosition(nextX, nextY))
            {
                continue;
            }
            if (m_map.IsWall(nextX, nextY))
            {
                continue;
            }
            if (closed[nextX][nextY])
            {
                continue;
            }

            int newG = gCost[currentX][currentY] + 1;
            if (newG < gCost[nextX][nextY])
            {
                gCost[nextX][nextY]  = newG;
                parent[nextX][nextY] = { currentX, currentY };

                int newH = CalculateHeuristic(nextX, nextY, goal.first, goal.second);
                openList.push(Node(nextX, nextY, newG, newH, currentX, currentY));
            }
        }
    }
    return false;
}

Path AStarPathfinder::ReconstructPath(const vector<vector<Position>>& parent, Position start, Position goal) const
{
    Path path;
    Position current = goal;

    while (current != Position{ -1, -1 })
    {
        path.push_back(current);

        if (current == start)
        {
            break;
        }
        current = parent[current.first][current.second];
    }

    reverse(path.begin(), path.end());
    return path;
}

int AStarPathfinder::CalculateHeuristic(int x1, int y1, int x2, int y2) const
{
    // 상하좌우 이동 기준 Manhattan Distance
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}
