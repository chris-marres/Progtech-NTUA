#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::string;
using std::to_string;


class Graph {
    public:
        Graph(int V);
        ~Graph();

        void addEdge(int a, int b, int w);
        bool findPath(int a, int b, int w, vector<int> &path);
        bool findPath_help(int a, int b, bool* visited, vector<int> &path);
        int getRefills(int w, vector<int> &path);

    private:
        int V;
        int **adj;
};

Graph::Graph(int V) {
    this->V = V;
    adj = new int*[V];
    for (int i = 0; i < V; i++) {
        adj[i] = new int[V];
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < V; i++) {
        delete[] adj[i];
    }
    delete[] adj;
}

void Graph::addEdge(int a, int b, int w) {
    adj[a][b] = w;
    adj[b][a] = w;
}

bool Graph::findPath_help(int a, int b, bool* visited, vector<int> &path) {
    visited[a] = true;
    path.push_back(a);
    if (a == b) {
        return true;
    }
    for (int i = 0; i < V; i++) {
        if (adj[a][i] != 0 && !visited[i]) {
            if (findPath_help(i, b, visited, path)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

bool Graph::findPath(int a, int b, int w, vector<int> &path) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adj[i][j] > w) {
                adj[i][j] = 0;
            }
        }
    }

    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    
    if (findPath_help(a, b, visited, path)) {
        return true;
    }
    return false;
}

int Graph::getRefills(int w, vector<int> &path) {
    int tank = 0;
    int refills = 0;
    for (int i = 0; i < path.size()-1; i++) {
        if (adj[path[i]][path[i+1]] > tank) {
            tank = w;
            refills++;
        }
        tank -= adj[path[i]][path[i+1]];
    }
    return refills;
}

struct question {
    int id;
    int a;
    int b;
    int w;
    string answer;
};

static bool compare_weight(question a, question b) {
    return a.w > b.w;
}

static bool compare_id(question a, question b) {
    return a.id < b.id;
}

int main(){

    int V, E;
    cin >> V >> E;

    Graph g(V);
    int u, v, w;
    for (int i = 0; i < E; ++i) {
        cin >> u >> v >> w;
        g.addEdge(u, v, w); 
    }

    int questions;
    cin >> questions;

    question *q = new question[questions];
    for (int i = 0; i < questions; ++i) {
        q[i].id = i;
        cin >> q[i].a >> q[i].b >> q[i].w;
    }

    sort(q, q+questions, compare_weight);

    for (int i = 0; i < questions; ++i) {
        vector<int> path;
        bool c = g.findPath(q[i].a, q[i].b, q[i].w, path);
        if (c) {
            q[i].answer = "POSSIBLE: " + to_string(g.getRefills(q[i].w, path)) + " fill(s), ";
            for (int j = 0; j < path.size(); ++j) {
                q[i].answer += to_string(path[j]) + " ";
            }
        } else {
            q[i].answer = "IMPOSSIBLE";
        }
    }

    sort(q, q+questions, compare_id);

    for (int i = 0; i < questions; ++i) {
        cout << q[i].answer << endl;
    }

    return 0;
}
