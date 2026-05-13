#include <iostream>
#include <cstdlib>
#include <ctime>
#include "core/Graph.h"
#include "core/MapGenerator.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "rendering/MapRenderer.h"
#include <SFML/Graphics.hpp>

void printMap(Graph& graph) {
    std::cout << "\n--- MAPA ---\n";
    for (int i = 0; i < graph.getRows(); i++) {
        for (int j = 0; j < graph.getCols(); j++) {
            if (graph.isObstacle(i, j))
                std::cout << "# ";
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void testGraph() {
    std::cout << "=== TEST GRAPH ===\n";

    Graph g(3, 3);
    g.addEdge(0, 0, 0, 1);
    g.addEdge(0, 1, 0, 2);

    std::cout << "(0,0)-(0,1) conectados: " << (g.areConnected(0,0,0,1) ? "SI" : "NO") << "\n";
    std::cout << "(0,0)-(0,2) conectados: " << (g.areConnected(0,0,0,2) ? "SI" : "NO") << "\n";

    g.removeEdge(0, 0, 0, 1);
    std::cout << "(0,0)-(0,1) tras removeEdge: " << (g.areConnected(0,0,0,1) ? "SI" : "NO") << "\n";

    std::cout << "\n";
}

void testAccessibility() {
    std::cout << "=== TEST ACCESIBILIDAD ===\n";

    // Mapa 3x3 totalmente conectado
    Graph g1(3, 3);
    MapGenerator gen(0.0); // sin obstáculos
    gen.generate(g1);
    std::cout << "Mapa sin obstáculos accesible: " << (g1.isAccessible() ? "SI" : "NO") << "\n";

    // Mapa con obstáculo que no aísla nada
    Graph g2(4, 4);
    MapGenerator gen2(0.2);
    gen2.generate(g2);
    std::cout << "Mapa con 20% obstáculos accesible: " << (g2.isAccessible() ? "SI" : "NO") << "\n";

    std::cout << "\n";
}

void testMapGeneration() {
    std::cout << "=== TEST GENERACIÓN DE MAPA ===\n";

    Graph g(10, 15);
    MapGenerator gen(0.25);
    gen.generate(g);

    printMap(g);
    std::cout << "Mapa accesible: " << (g.isAccessible() ? "SI" : "NO") << "\n\n";
}

void testNeighbors() {
    std::cout << "=== TEST VECINOS ===\n";

    std::cout << "Creando grafo...\n";
    Graph g(3, 3);

    std::cout << "Creando MapGenerator...\n";
    MapGenerator gen(0.0);

    std::cout << "Llamando generate...\n";
    gen.generate(g);

    std::cout << "Llamando getNeighbors...\n";
    Node neighbors[4];
    int count = 0;
    g.getNeighbors(1, 1, neighbors, count);

    std::cout << "Vecinos de (1,1): " << count << "\n";
    for (int i = 0; i < count; i++) {
        std::cout << "  (" << neighbors[i].row << "," << neighbors[i].col << ")\n";
    }
    std::cout << "\n";
}


void testMapRendering()
{
    std::cout << "Abriendo ventana...\n";
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Tank Attack");
    std::cout << "Ventana creada\n";
    Graph graph(10, 15);
    MapGenerator gen(0.25);
    gen.generate(graph);
    MapRenderer renderer(1200, 800, graph);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            std::cout << "Loop activo\n";
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        renderer.renderMap(window);
        window.display();
    }
}

int main() {
    srand(time(nullptr));

    testGraph();
    testNeighbors();
    testAccessibility();
    testMapGeneration();
    testMapRendering();

    return 0;
}



