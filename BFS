#include <iostream>
#include <queue>
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

class BFSVisitor : public GraphVisitor {
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

    void BFS(Node &startNode, vector<bool> &discovered, GraphVisitor &visitor) {
        queue<Node*> q;

        discovered[startNode.id] = true;
        startNode.accept(visitor);
        q.push(&startNode);

        while (!q.empty()) {
            Node *v = q.front();
            q.pop();

            for (int neighbor : v->neighbors) {
                if (!discovered[neighbor]) {
                    discovered[neighbor] = true;
                    nodes[neighbor].accept(visitor);
                    q.push(&nodes[neighbor]);
                }
            }
        }
    }

    void traverse(GraphVisitor &visitor) {
        vector<bool> discovered(nodes.size(), false);

        for (Node &node : nodes) {
            if (!discovered[node.id]) {
                BFS(node, discovered, visitor);
            }
        }
    }
};

int main() {
    // número total de nodos en el grafo (etiquetados de 0 a 14)
    int n = 15;
    Graph graph(n);

    // vector de los bordes del grafo según el diagrama anterior
    vector<Edge> edges = {
        {1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {5, 9},
        {5, 10}, {4, 7}, {4, 8}, {7, 11}, {7, 12}
        // los vértices 0, 13 y 14 son nodos individuales
    };

    // agregar bordes al grafo
    for (auto &edge : edges) {
        graph.addEdge(edge.src, edge.dest);
    }

    // crear un visitante BFS
    BFSVisitor visitor;

    // realizar el recorrido BFS usando el visitante
    graph.traverse(visitor);

    return 0;
}
