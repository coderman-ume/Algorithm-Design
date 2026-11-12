#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <utility>
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


    explicit DisjointSet(int elementCount) : parents_(elementCount), ranks_(elementCount, 0) {
        for (int element = 0; element < elementCount; ++element) {
            parents_[element] = element;
        }
    }

    int findRoot(int element) {
        int root = element;
        while (parents_[root] != root) {
            root = parents_[root];
        }
        int current = element;
        while (parents_[current] != root) {
            int next = parents_[current];
            parents_[current] = root;
            current = next;
        }
        return root;
    }

    bool unite(int first, int second) {
        int firstRoot = findRoot(first);
        int secondRoot = findRoot(second);
        if (firstRoot == secondRoot) {
            return false;
        }
        if (ranks_[firstRoot] < ranks_[secondRoot]) {
            std::swap(firstRoot, secondRoot);
        }
        parents_[secondRoot] = firstRoot;
        if (ranks_[firstRoot] == ranks_[secondRoot]) {
            ++ranks_[firstRoot];
        }
        return true;
    }

private:
    std::vector<int> parents_;
    std::vector<int> ranks_;
};

bool isSpanningTreeComplete(const std::vector<Edge> &treeEdges, int vertexCount) {
    return static_cast<int>(treeEdges.size()) == vertexCount - 1;
}

std::optional<SpanningTree> buildMinimumSpanningTree(int vertexCount, std::vector<Edge> edges) {
    std::stable_sort(edges.begin(), edges.end(),
                     [](const Edge &left, const Edge &right) { return left.weight < right.weight; });

    DisjointSet componentOf(vertexCount);
    SpanningTree tree{{}, 0};

    for (const Edge &candidate : edges) {
        if (!componentOf.unite(candidate.from, candidate.to)) {
            continue;
        }
        tree.edges.push_back(candidate);
        tree.totalCost += candidate.weight;
        if (isSpanningTreeComplete(tree.edges, vertexCount)) {
            break;
        }
    }

    if (!isSpanningTreeComplete(tree.edges, vertexCount)) {
        return std::nullopt;
    }
    return tree;
}

void discardRestOfLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

long long readBoundedInteger(const std::string &prompt, long long minimum) {
    while (true) {
        std::cout << prompt;
        long long value;
        if (!(std::cin >> value)) {
            std::cout << "Please enter an integer.\n";
            discardRestOfLine();
            continue;
        }
        if (value < minimum) {
            std::cout << "The value must be at least " << minimum << ".\n";
            continue;
        }
        return value;
    }
}

Edge readEdge(int vertexCount) {
    while (true) {
        long long from;
        long long to;
        long long weight;
        if (!(std::cin >> from >> to >> weight)) {
            std::cout << "Each edge needs three integers: u v w.\n";
            discardRestOfLine();
            continue;
        }
        const bool fromInRange = from >= 0 && from < vertexCount;
        const bool toInRange = to >= 0 && to < vertexCount;
        if (!fromInRange || !toInRange) {
            std::cout << "Vertices must be between 0 and " << vertexCount - 1 << ".\n";
            continue;
        }
        return Edge{static_cast<int>(from), static_cast<int>(to), weight};
    }
}

void printSingleVertexGraph() {
    std::cout << "The graph has a single vertex, so the spanning tree has no edges.\n"
              << "Total minimum cost: 0\n";
}

void printSpanningTree(const SpanningTree &tree) {
    std::cout << "Minimum spanning tree edges:\n";
    for (const Edge &edge : tree.edges) {
        std::cout << "  " << edge.from << " - " << edge.to << "  (weight " << edge.weight << ")\n";
    }
    std::cout << "Total minimum cost: " << tree.totalCost << "\n";
}

int main() {
    const int vertexCount = static_cast<int>(readBoundedInteger("Number of vertices: ", 1));
    const long long edgeCount = readBoundedInteger("Number of edges: ", 0);
    std::cout << "Enter each edge as: u v w (vertices are numbered 0 to n-1)\n";

    std::vector<Edge> edges;
    edges.reserve(static_cast<std::size_t>(edgeCount));
    for (long long index = 0; index < edgeCount; ++index) {
        edges.push_back(readEdge(vertexCount));
    }

    if (vertexCount == 1) {
        printSingleVertexGraph();
        return 0;
    }

    const std::optional<SpanningTree> tree = buildMinimumSpanningTree(vertexCount, edges);
    if (!tree) {
        std::cout << "No spanning tree exists: the graph is disconnected.\n";
        return 0;
    }
    printSpanningTree(*tree);
    return 0;
}
