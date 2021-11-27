/**
 * AI Mini Project
 * Travelling Salesman Problem
 * 
 * Members:
 * Ayush Basak: 19UCC016
 * Raja Kumar Singh: 19UCC019
 * Surendra Kumar: 19UCC018
 * Siddhartha Singh: 19UCS167
 * 
*/

#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;
void prim_MST(const vector<vector<pair<int, int>>> &adj,
                int n, vector<pair<int, int>> &MST, 
                vector<int> &pre_order
            );

/*
* To print an MST starting at vertex 0
*/
void print_MST(const vector<pair<int, int>> &MST);
int main() {

    /**
     * State 0: [Initial State] Agent has not visited any vertex
     * State 1: [Goal State] Agent has visited all vertices and reached initial vertex
     * Successor Function: Generated all vertices that have not been visited
     * Edge Cost: Cost of edge between two vertices
    */

    /**
     * n vertices
     * m edges
    */
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n, vector<pair<int, int> >());
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;

        adj[from].push_back(make_pair(to, weight));
        adj[to].push_back(make_pair(from, weight));

    }
    cout << "Adjacent List of The Graph :: " << endl;
    cout << "##########################################" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << "-> ";

        for (auto j : adj[i]) {
            cout << "(" << j.first << "," << j.second << ")" << " => ";
        }
        cout << endl;
    }
    cout << "##########################################" << endl;

    vector<pair<int, int> > MST;
    vector<int> pre_order;
    prim_MST(adj, n, MST, pre_order);

    print_MST(MST);

    cout << "\nTSP Path :: ";
    for (auto x: pre_order) {
        cout << x << " => ";
    }
    cout << "0\n";

    return 0;
}
void prim_MST(const vector<vector<pair<int, int>>> &adj,
                int n, vector<pair<int, int>> &MST, 
                vector<int> &pre_order
            ) {
    vector<int> visited_node(n, 0);
    vector<int> cost(n, INT_MAX);
    vector<int> parent(n, -1);

    cost[0] = 0;
    parent[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> mst_tree;
    mst_tree.emplace(make_pair(cost[0], 0));
    for (int i = 1; i < n; ++i)
        mst_tree.emplace(make_pair(INT_MAX, i));


    while (!mst_tree.empty()) {
        int current_vertex = mst_tree.top().second;

        if (visited_node[current_vertex]) {
            mst_tree.pop();
            continue;
        }

        mst_tree.pop();
        visited_node[current_vertex] = 1;
        pre_order.push_back(current_vertex);

        MST.emplace_back(current_vertex, parent[current_vertex]);

        for (auto neighbouring_node: adj[current_vertex]) {
            if (!visited_node[neighbouring_node.first] && cost[neighbouring_node.first] > neighbouring_node.second) {
                cost[neighbouring_node.first] = neighbouring_node.second;
                parent[neighbouring_node.first] = current_vertex;
                mst_tree.emplace(make_pair(neighbouring_node.second, neighbouring_node.first));
            }
        }
    }


}

void print_MST(const vector<pair<int, int>> &MST) {
    cout << "Edges between pair of vertices in the given MST ::" << endl;
    for (auto edge: MST) {
        if (edge.first == 0)
            continue;
        cout << edge.second << " <==> " << edge.first << endl;
    }
}