#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

typedef pair<pair<int, int>, int> Edge; //a, b, length
// A---------B
//   length


vector<Edge> prims_algo(vector<vector<int>> graph, int number_of_nodes){
    vector<int> unvisited;
    vector<int> visited;
    vector<Edge> result;

    //mark first as visited and mark the rest as unvisited
    for (int i = 1; i < number_of_nodes; i++)
        unvisited.push_back(i);
    visited.push_back(0);

    while (!unvisited.empty()) {

        vector<Edge> edges_with_lengths;
        //put all edges (with their lengths) from nodes that are in visited
        for(auto node : visited) {
            for (int sec_node = 0; sec_node < number_of_nodes; sec_node++) {
                if (graph[node][sec_node] > 0 && find(unvisited.begin(), unvisited.end(), sec_node) != unvisited.end()) {
                    //add if there is connection and second node is not visited yet
                    Edge e = make_pair(make_pair(node, sec_node), graph[node][sec_node]);
                    edges_with_lengths.push_back(e);
                }
            }
        }

        //find the shortest edge
        pair<pair<int, int>, int> the_shortest;
        the_shortest = edges_with_lengths.front();
        for(auto i: edges_with_lengths){
            if(the_shortest.second > i.second)
                the_shortest = i;
        }

        //add the shortest path to the result
        result.push_back(the_shortest);

        //remove a node that the shortest edge leads to
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), the_shortest.first.second), unvisited.end());

        //mark this node as visited
        visited.push_back(the_shortest.first.second);
    };
    return result;
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

    vector<Edge> result = prims_algo(graph, 5);
    for(auto i:result){
        cout<<"EDGE [ " <<i.first.first<<", "<<i.first.second<<"], length: "<<i.second<<endl;
    }

    return 0;
}