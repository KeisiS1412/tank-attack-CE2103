#include "Graph.h"

Graph::Graph(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;

    int total = rows * cols;

    matrix = new int*[total];
    for (int i = 0; i < total; i++) {
        matrix[i] = new int[total];
        for (int j = 0; j < total; j++) {
            matrix[i][j] = 0;
        }
    }

    nodes = new Node[total];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i * cols + j;
            nodes[index].row = i;
            nodes[index].col = j;
            nodes[index].obstacle = false;
        }
    }
}

Graph::~Graph() {
    int total = rows * cols;

    for (int i = 0; i < total; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    delete[] nodes;
}

void Graph::addEdge(int row1, int col1, int row2, int col2)
{
    int index1 = row1 * cols + col1;
    int index2 = row2 * cols + col2;
    matrix[index1][index2] = 1;
    matrix[index2][index1] = 1;
}

void Graph::removeEdge(int row1, int col1, int row2, int col2)
{
    int index1 = row1 * cols + col1;
    int index2 = row2 * cols + col2;
    matrix[index1][index2] = 0;
    matrix[index2][index1] = 0;
}

bool Graph::areConnected(int row1, int col1, int row2, int col2)
{
    int index1 = row1 * cols + col1;
    int index2 = row2 * cols + col2;
    return matrix[index2][index1] == 1;
}

bool Graph::isValid(int row, int col)
{
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

void Graph::getNeighbors(int row, int col, Node neighbors[4], int& count)
{
    int dRow[4] = {-1, 1, 0, 0};
    int dCol[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int newRow = row + dRow[i];
        int newCol = col + dCol[i];

        if (isValid(newRow, newCol) && areConnected(row, col, newRow, newCol))
        {
            neighbors[count].row = newRow;
            neighbors[count].col = newCol;
            count++;
        }
    }
}

bool Graph::isAccessible() {
    int total = rows * cols;

    int startIndex = -1;
    int freeCells = 0;
    for (int i = 0; i < total; i++) {
        if (!nodes[i].obstacle) {
            if (startIndex == -1) startIndex = i;
            freeCells++;
        }
    }

    if (freeCells == 0) return true;

    // cambiar a q
    bool* visited = new bool[total];
    for (int i = 0; i < total; i++) visited[i] = false;

    int* queue = new int[total];
    int front = 0, back = 0;

    queue[back++] = startIndex;
    visited[startIndex] = true;
    int visitedCount = 1;

    while (front < back) {
        int current = queue[front++];
        int row = nodes[current].row;
        int col = nodes[current].col;

        Node neighbors[4];
        int count = 0;
        getNeighbors(row, col, neighbors, count);

        for (int i = 0; i < count; i++) {
            int nIndex = neighbors[i].row * cols + neighbors[i].col;
            if (!visited[nIndex] && !nodes[nIndex].obstacle) {
                visited[nIndex] = true;
                queue[back++] = nIndex;
                visitedCount++;
            }
        }
    }

    delete[] visited;
    delete[] queue;

    return visitedCount == freeCells;
}