class DisjointSet:
    def __init__(self, element_count):
        self.parent = list(range(element_count))
        self.rank = [0] * element_count

    def find(self, element):
        root = element
        while self.parent[root] != root:
            root = self.parent[root]

        while self.parent[element] != root:
            next_element = self.parent[element]
            self.parent[element] = root
            element = next_element

        return root
    
    def union(self, first, second):
        first_root = self.find(first)
        second_root = self.find(second)
        if first_root == second_root:
            return False

        if self.rank[first_root] < self.rank[second_root]:
            first_root, second_root = second_root, first_root
        self.parent[second_root] = first_root
        if self.rank[first_root] == self.rank[second_root]:
            self.rank[first_root] += 1
        return True


def kruskal_minimum_spanning_tree(vertex_count, edges):
    sorted_edges = sorted(edges, key=lambda edge: edge[2])
    components = DisjointSet(vertex_count)
    tree_edges = []
    total_cost = 0

    for u, v, weight in sorted_edges:
        # union() rejects edges that would close a cycle, including self-loops.
        if components.union(u, v):
            tree_edges.append((u, v, weight))
            total_cost += weight
            if len(tree_edges) == vertex_count - 1:
                break

    if len(tree_edges) != vertex_count - 1:
        return None
    return tree_edges, total_cost


def read_integer(prompt, minimum):
    while True:
        raw_text = input(prompt).strip()
        try:
            value = int(raw_text)
        except ValueError:
            print("Please enter an integer.")
            continue
        if value < minimum:
            print(f"The value must be at least {minimum}.")
            continue
        return value


def read_edge(vertex_count):
    while True:
        parts = input().split()
        if len(parts) != 3:
            print("Each edge needs three values: u v w.")
            continue
        try:
            u, v, weight = (int(part) for part in parts)
        except ValueError:
            print("Vertices and weight must be integers.")
            continue
        if not (0 <= u < vertex_count and 0 <= v < vertex_count):
            print(f"Vertices must be between 0 and {vertex_count - 1}.")
            continue
        return u, v, weight


def main():
    vertex_count = read_integer("Number of vertices: ", minimum=1)
    edge_count = read_integer("Number of edges: ", minimum=0)
    print("Enter each edge as: u v w (vertices are numbered 0 to n-1)")
    edges = [read_edge(vertex_count) for _ in range(edge_count)]

    if vertex_count == 1:
        print("The graph has a single vertex, so the spanning tree has no edges.")
        print("Total minimum cost: 0")
        return

    result = kruskal_minimum_spanning_tree(vertex_count, edges)
    if result is None:
        print("No spanning tree exists: the graph is disconnected.")
        return

    tree_edges, total_cost = result
    print("Minimum spanning tree edges:")
    for u, v, weight in tree_edges:
        print(f"  {u} - {v}  (weight {weight})")
    print(f"Total minimum cost: {total_cost}")


if __name__ == "__main__":
    main()
