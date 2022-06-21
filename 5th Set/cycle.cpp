#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::find;

class Graph {
    public:
        Graph(int V);
        ~Graph();
        void addEdge(int u, int v);

        bool cycle(vector<int> &path) const;
        bool cycle_help(int y, bool* visited, vector<int> &path) const;

        friend std::ostream &operator<<(std::ostream &os, const Graph &g);

    private:
        int V;
        vector<vector<int>> adj;
};

Graph::Graph(int V) : V(V) {
    adj.resize(V);
}

Graph::~Graph() {
    adj.clear();
}

void Graph::addEdge(int u, int v) {
    vector<int> *temp = &adj[u];
    auto it = find(temp->begin(), temp->end(), v);
    
    if (it == temp->end()) {
        temp->push_back(v);
    }
}

std::ostream &operator<<(std::ostream &os, const Graph &g) {
    for (int i = 0; i < g.V; i++) {
        os << i << ": ";
        for (auto &v : g.adj[i]) {
            os << v << " ";
        }
        os << endl;
    }
    return os;
}

bool Graph::cycle(vector<int> &path) const {
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    
    for (int i = 0; i < V; ++i){
        if (!visited[i]){
            if (cycle_help(i, visited, path)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::cycle_help(int y, bool* visited, vector<int> &path) const {
    visited[y] = true;
    path.push_back(y);
    for (auto &v : adj[y]) {
        if (visited[v]) {
            if (v == path[0]) {
                return true;
            }
        } else {
            if (cycle_help(v, visited, path)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

#ifndef CONTEST

int main() {

    int V, E;
    cin >> V >> E;

    Graph g(V);
    for (int i = 0; i < E; ++i) { int u, v; cin >> u >> v; g.addEdge(u, v); }
    cout << g << endl;
    
    vector<int> path;
    bool c = g.cycle(path);
    
    if (c) {
        cout << "CYCLE: " ;
        for (int i = 0; i < path.size(); ++i)
            cout << path[i] << (i == path.size()-1 ? "\n" : " ");
    }
    else {
        cout << "NO CYCLE" << endl;
    }
}

#endif
