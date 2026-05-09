#include "MapGenerator.h"
#include <cstdlib>
#include <ctime>
#include "Graph.h"

MapGenerator::MapGenerator(double ratio)
{
    obstacleRatio = ratio;
    srand(time(nullptr));
}

void MapGenerator::connectNodes(Graph& graph)
{
    for (int i = 0; i < graph.getRows(); i++)
    {
        for (int j = 0; j < graph.getCols(); j++)
        {
            if (graph.isValid(i, j+1)) graph.addEdge(i, j+1, i, j);
            if (graph.isValid(i+1, j)) graph.addEdge(i+1, j, i, j);
        }
    }
}

void MapGenerator::setObstacles(Graph& graph)
{
    int total = graph.getRows() * graph.getCols();
    int numObstacles = obstacleRatio * total;
    for (int i = 0; i < numObstacles; i++)
    {
        int idx = rand() % total;
        int row = idx / graph.getCols();
        int col = idx % graph.getCols();
        if (!graph.isObstacle(row, col))
        {
            graph.setObstacle(row, col);
            Node neighbors[4];
            int count = 0;
            graph.getNeighbors(row, col, neighbors, count);
            for (int j = 0; j < count; j++)
            {
                graph.removeEdge(row, col, neighbors[j].row, neighbors[j].col);
            }
        }
    }


}

void MapGenerator::generate(Graph& graph)
{
    connectNodes(graph);
    do
    {
        setObstacles(graph);
        resetMap(graph);
    }
    while (!graph.isAccessible());
}

void MapGenerator::resetMap(Graph& graph)
{
    int total = graph.getRows() * graph.getCols();

    for (int i = 0; i < total; i++)
    {
        int row = i / graph.getCols();
        int col = i % graph.getCols();
        if (graph.isObstacle(row, col))
        {
            graph.removeObstacle(row, col);
            Node neighbors[4];
            int count = 0;
            graph.getNeighbors(row, col, neighbors, count);
            for (int j = 0; j < count; j++)
            {
                graph.addEdge(row, col, neighbors[j].row, neighbors[j].col);
            }
        }
    }
}