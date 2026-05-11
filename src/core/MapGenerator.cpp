#include "MapGenerator.h"
#include <cstdlib>
#include <ctime>
#include "Graph.h"

MapGenerator::MapGenerator(double ratio)
{
    obstacleRatio = ratio;
    // utiliza un ratio seteable para el porcentaje de obstáculos con respecto a la matriz
    srand(time(nullptr)); // semilla del random
}

// conecta los nodos de un grafo si son válidos
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

// setea los obstáculos en casillas random de la matriz
void MapGenerator::setObstacles(Graph& graph)
{
    int total = graph.getRows() * graph.getCols();
    int numObstacles = obstacleRatio * total;
    for (int i = 0; i < numObstacles; i++)
    {
        int idx = rand() % total; // cantidad de índices de obstáculo
        int row = idx / graph.getCols(); // la fila es el índice lineal entre el número de columnas
        int col = idx % graph.getCols(); // la columna es el residuo del índice lineal entre el número de columnas
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
    connectNodes(graph); // recibe el grafo y conecta los nodos
    do // distribuye los obstáculos
    {
        setObstacles(graph);
        if (!graph.isAccessible()) resetMap(graph);
    }
    while (!graph.isAccessible());
    // si no todos los nodos son accesibles se resetea y los distribuye de nuevo hasta que sea accesible
}

void MapGenerator::resetMap(Graph& graph)
{
    int total = graph.getRows() * graph.getCols();

    for (int i = 0; i < total; i++)
    {
        int row = i / graph.getCols();
        int col = i % graph.getCols();
        graph.removeObstacle(row, col);
        connectNodes(graph);
    }
}