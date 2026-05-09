#ifndef P2_CE2103_TANKATTACK_GRAPH_H
#define P2_CE2103_TANKATTACK_GRAPH_H

struct Node
{
    int row;
    int col;
    bool obstacle;
};

class Graph
{
private:
    int rows;
    int cols;
    int** matrix;
    Node* nodes;
public:
    Graph(int rows, int cols);
    ~Graph();
    void addEdge(int row1, int col1, int row2, int col2);
    void removeEdge(int row1, int col1, int row2, int col2);
    bool areConnected(int row1, int col1, int row2, int col2);
    bool isValid(int row, int col);
    void getNeighbors(int row, int col, Node neighbors[4], int& count);
    bool isAccessible();
    int getRows();
    int getCols();
    void setObstacle(int row, int col);
    void removeObstacle(int row, int col);
    bool isObstacle(int row, int col);
};


#endif