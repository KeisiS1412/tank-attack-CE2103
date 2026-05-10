#include "Pathfinding.h"
#include <climits>
#include <cmath>

Path* Pathfinding::dijkstra(Graph& graph, int startRow, int startCol, int endRow, int endCol)
{
    int rows = graph.getRows();
    int cols = graph.getCols();
    int total = rows * cols;
    int startIdx = startRow * cols + startCol;
    int endIdx = endRow * cols + endCol;

    int* dist = new int[total];
    int* prev = new int[total];
    bool* visited = new bool[total];

    for (int i = 0; i < total; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }
    dist[startIdx] = 0;

    for (int i = 0; i < total; i++) {
        int u = -1;
        for (int j = 0; j < total; j++) {
            if (!visited[j] && dist[j] != INT_MAX) {
                if (u == -1 || dist[j] < dist[u]) u = j;
            }
        }

        if (u == -1 || u == endIdx) break;
        visited[u] = true;

        int uRow = u / cols;
        int uCol = u % cols;

        Node neighbors[4];
        int count = 0;
        graph.getNeighbors(uRow, uCol, neighbors, count);

        for (int j = 0; j < count; j++) {
            int vIdx = neighbors[j].row * cols + neighbors[j].col;
            if (!visited[vIdx] && !graph.isObstacle(neighbors[j].row, neighbors[j].col)) {
                int newDist = dist[u] + 1;
                if (newDist < dist[vIdx]) {
                    dist[vIdx] = newDist;
                    prev[vIdx] = u;
                }
            }
        }
    }

    if (prev[endIdx] == -1 && startIdx != endIdx) {
        delete[] dist;
        delete[] prev;
        delete[] visited;
        return nullptr; 
    }

    int length = 0;
    int current = endIdx;
    while (current != -1) { length++; current = prev[current]; }

    Path* path = new Path();
    path->length = length;
    path->nodes = new int[length];

    current = endIdx;
    for (int i = length - 1; i >= 0; i--) {
        path->nodes[i] = current;
        current = prev[current];
    }

    delete[] dist;
    delete[] prev;
    delete[] visited;

    return path;
}

int Pathfinding::heuristic(int row1, int col1, int row2, int col2)
{
    return abs(row1 - row2) + abs(col1 - col2);
}

Path* Pathfinding::aStar(Graph& graph, int startRow, int startCol, int endRow, int endCol)
{
    int rows = graph.getRows();
    int cols = graph.getCols();
    int total = rows * cols;
    int startIdx = startRow * cols + startCol;
    int endIdx = endRow * cols + endCol;

    int* gCost = new int[total];
    int* fCost = new int[total]; 
    int* prev = new int[total];
    bool* visited = new bool[total];

    for (int i = 0; i < total; i++) {
        gCost[i] = INT_MAX;
        fCost[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }
    gCost[startIdx] = 0;
    fCost[startIdx] = heuristic(startRow, startCol, endRow, endCol);

    for (int i = 0; i < total; i++) {
        int u = -1;
        for (int j = 0; j < total; j++) {
            if (!visited[j] && fCost[j] != INT_MAX) {
                if (u == -1 || fCost[j] < fCost[u]) u = j;
            }
        }

        if (u == -1 || u == endIdx) break;
        visited[u] = true;

        int uRow = u / cols;
        int uCol = u % cols;

        Node neighbors[4];
        int count = 0;
        graph.getNeighbors(uRow, uCol, neighbors, count);

        for (int j = 0; j < count; j++) {
            int vIdx = neighbors[j].row * cols + neighbors[j].col;
            if (!visited[vIdx] && !graph.isObstacle(neighbors[j].row, neighbors[j].col)) {
                int newG = gCost[u] + 1;
                if (newG < gCost[vIdx]) {
                    gCost[vIdx] = newG;
                    fCost[vIdx] = newG + heuristic(neighbors[j].row, neighbors[j].col, endRow, endCol);
                    prev[vIdx] = u;
                }
            }
        }
    }

    if (prev[endIdx] == -1 && startIdx != endIdx) {
        delete[] gCost;
        delete[] fCost;
        delete[] prev;
        delete[] visited;
        return nullptr;
    }

    int length = 0;
    int current = endIdx;
    while (current != -1) { length++; current = prev[current]; }

    Path* path = new Path();
    path->length = length;
    path->nodes = new int[length];

    current = endIdx;
    for (int i = length - 1; i >= 0; i--) {
        path->nodes[i] = current;
        current = prev[current];
    }

    delete[] gCost;
    delete[] fCost;
    delete[] prev;
    delete[] visited;

    return path;
}