#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct Edge {
    int from;
    int to;
    long long weight;
};

struct SpanningTree {
    std::vector<Edge> edges;
    long long totalCost;
};

class DisjointSet {
public:
    explicit DisjointSet(int elementCount) : parent_(elementCount), rank_(elementCount, 0) {
        for (int element = 0; element < elementCount; ++element) {
            parent_[element] = element;
        }
    }

    int find(int element) {
        int root = element;
        while (parent_[root] != root) {
            root = parent_[root];
        }
        // Path compression: point every visited node straight at the root.
        while (parent_[element] != root) {
            int nextElement = parent_[element];
            parent_[element] = root;
            element = nextElement;
        }
        return root;
    }

    bool unite(int first, int second) {
        int firstRoot = find(first);
        int secondRoot = find(second);
        if (firstRoot == secondRoot) {
            return false;
        }
        // Union by rank: attach the shorter tree under the taller one.
        if (rank_[firstRoot] < rank_[secondRoot]) {
            std::swap(firstRoot, secondRoot);
        }
        parent_[secondRoot] = firstRoot;
        if (rank_[firstRoot] == rank_[secondRoot]) {
            ++rank_[firstRoot];
        }
        return true;
    }

private:
    std::vector<int> parent_;
    std::vector<int> rank_;
};

std::optional<SpanningTree> kruskalMinimumSpanningTree(int vertexCount, std::vector<Edge> edges) {
    // std::stable_sort keeps equal-weight edges in input order, so the output is deterministic.
    std::stable_sort(edges.begin(), edges.end(),
                     [](const Edge &a, const Edge &b) { return a.weight < b.weight; });

    DisjointSet components(vertexCount);
    SpanningTree tree{{}, 0};

    for (const Edge &edge : edges) {
        // unite() returns false for edges that would close a cycle, including self-loops.
        if (components.unite(edge.from, edge.to)) {
            tree.edges.push_back(edge);
            tree.totalCost += edge.weight;
            if (static_cast<int>(tree.edges.size()) == vertexCount - 1) {
                break;
            }
        }
    }

    if (static_cast<int>(tree.edges.size()) != vertexCount - 1) {
        return std::nullopt;
    }
    return tree;
}

int readInteger(const std::string &prompt, int minimum) {
    while (true) {
        std::cout << prompt;
        long long value;
        if (!(std::cin >> value)) {
            std::cout << "Please enter an integer.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (value < minimum) {
            std::cout << "The value must be at least " << minimum << ".\n";
            continue;
        }
        return static_cast<int>(value);
    }
}

Edge readEdge(int vertexCount) {
    while (true) {
        long long from;
        long long to;
        long long weight;
        if (!(std::cin >> from >> to >> weight)) {
            std::cout << "Each edge needs three integers: u v w.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            std::cout << "Vertices must be between 0 and " << vertexCount - 1 << ".\n";
            continue;
        }
        return Edge{static_cast<int>(from), static_cast<int>(to), weight};
    }
}

int main() {
    int vertexCount = readInteger("Number of vertices: ", 1);
    int edgeCount = readInteger("Number of edges: ", 0);
    std::cout << "Enter each edge as: u v w (vertices are numbered 0 to n-1)\n";

    std::vector<Edge> edges;
    edges.reserve(edgeCount);
    for (int index = 0; index < edgeCount; ++index) {
        edges.push_back(readEdge(vertexCount));
    }

    if (vertexCount == 1) {
        std::cout << "The graph has a single vertex, so the spanning tree has no edges.\n";
        std::cout << "Total minimum cost: 0\n";
        return 0;
    }

    std::optional<SpanningTree> result = kruskalMinimumSpanningTree(vertexCount, edges);
    if (!result) {
        std::cout << "No spanning tree exists: the graph is disconnected.\n";
        return 0;
    }

    std::cout << "Minimum spanning tree edges:\n";
    for (const Edge &edge : result->edges) {
        std::cout << "  " << edge.from << " - " << edge.to << "  (weight " << edge.weight << ")\n";
    }
    std::cout << "Total minimum cost: " << result->totalCost << "\n";
    return 0;
}
