#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

struct Edge {
    int a;
    int b;
    int length;
};

bool edge_compare(Edge i, Edge j) { return (i.length < j.length); }

bool visit_node(vector<int> &visited, int node) {
    if (find(visited.begin(), visited.end(), node) == visited.end()) {
        visited.push_back(node);
        //return true if node is visited just now
        return true;
    }
    //return false if node was already visited before
    return false;
}

vector<Edge> kruskal(vector<vector<int>> graph, int number_of_nodes) {
    vector<int> visited;
    vector<Edge> edges;
    //add all the edges to "edges" vector
    for (int x = 1; x < number_of_nodes; x++) {
        for (int y = 0; y < x; y++) {
            if (graph[x][y] > 0) {
                Edge e = {x, y, graph[x][y]};
                edges.push_back(e);
            }
        }
    }
    //sort edges
    sort(edges.begin(), edges.end(), edge_compare);

    vector<Edge>::iterator shortest = edges.begin();

    while (visited.size() < number_of_nodes && shortest!=edges.end()) {
        if (!visit_node(visited, shortest->a) && !visit_node(visited, shortest->b)) {
            //remove the edge if it leads from visited to visited
            edges.erase(shortest);
        }
        else
            shortest++;
    };
    return edges;
}

int main() {
    /*
       2    3
   (0)--(1)--(2)
    |   / \   |
   6| 8/   \5 |7
    | /     \ |
   (3)-------(4)
         9          */
    vector<vector<int>> graph =
            {{{0, 2, 0, 6, 0},
                     {2, 0, 3, 8, 5},
                     {0, 3, 0, 0, 7},
                     {6, 8, 0, 0, 9},
                     {0, 5, 7, 9, 0},
             }};

    vector<Edge> result = kruskal(graph, 5);
    for (auto i:result) {
        cout << "EDGE [ " << i.a << ", " << i.b << "], length: " << i.length << endl;
    }

    return 0;
}