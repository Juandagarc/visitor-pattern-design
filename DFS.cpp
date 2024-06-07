#include <iostream>
#include <vector>
using namespace std;

class GraphVisitor;

// Interface para los elementos del grafo
class GraphElement {
public:
    virtual void accept(GraphVisitor &visitor) = 0;
};

// Interface para el visitante
class GraphVisitor {
public:
    virtual void visit(class Node &node) = 0;
};

class Node : public GraphElement {
public:
    int id;
    vector<int> neighbors;

    Node(int id) : id(id) {}

    void addNeighbor(int neighbor) {
        neighbors.push_back(neighbor);
    }

    void accept(GraphVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class DFSVisitor : public GraphVisitor {
public:
    void visit(Node &node) override {
        cout << node.id << " ";
    }
};

// Estructura de datos para almacenar un borde de grafo
struct Edge {
    int src, dest;
};

// Una clase para representar un objeto grafo
class Graph {
public:
    vector<Node> nodes;

    Graph(int n) {
        for (int i = 0; i < n; i++) {
            nodes.push_back(Node(i));
        }
    }

    void addEdge(int src, int dest) {
        nodes[src].addNeighbor(dest);
        nodes[dest].addNeighbor(src);
    }

    void DFS(Node &node, vector<bool> &discovered, GraphVisitor &visitor) {
        discovered[node.id] = true;
        node.accept(visitor);

        for (int neighbor : node.neighbors) {
            if (!discovered[neighbor]) {
                DFS(nodes[neighbor], discovered, visitor);
            }
        }
    }

    void traverse(GraphVisitor &visitor) {
        vector<bool> discovered(nodes.size(), false);

        for (Node &node : nodes) {
            if (!discovered[node.id]) {
                DFS(node, discovered, visitor);
            }
        }
    }
};

int main() {
    // número total de nodos en el grafo (etiquetados de 0 a 12)
    int n = 13;
    Graph graph(n);

    // vector de los bordes del grafo según el diagrama anterior
    vector<Edge> edges = {
        // Observe que el nodo 0 no está conectado
        {1, 2}, {1, 7}, {1, 8}, {2, 3}, {2, 6}, {3, 4},
        {3, 5}, {8, 9}, {8, 12}, {9, 10}, {9, 11}
    };

    // agregar bordes al grafo
    for (auto &edge : edges) {
        graph.addEdge(edge.src, edge.dest);
    }

    // crear un visitante DFS
    DFSVisitor visitor;

    // realizar el recorrido DFS usando el visitante
    graph.traverse(visitor);

    return 0;
}


/* Encontrar nodos conectados en un grafo
- Ordenamiento topológico en un grafo acíclico dirigido
- Encontrar puentes en un grafo de nodos
- Resolver puzzles con una sola solución, como los laberintos
- Encontrar nodos fuertemente conectados */
