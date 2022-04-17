#include <iostream> 
#include <vector> 

using namespace std; 

struct vertex {
    int name; 
    int d; 
    vertex* pi; 
}; 

struct edge {
    vertex* from; 
    vertex* to; 
    int w; 
};

struct graph {
    vector<vertex*> V; 
    vector<edge*> E; 
}; 

void initializeSingleSource(graph* G, vertex* s) {
    for (vertex* v : G -> V) {
        v -> d = 1000; 
        v -> pi = 0; 
    }
    s -> d = 0; 
}

void relax(vertex* u, vertex* v, int w) {
    if (v -> d > (u -> d) + w) {
        v -> d = (u -> d) + w; 
        v -> pi = u; 
    }
    v -> pi = u; 
}

bool bellmanFord(graph* G, int w, vertex* s) {
    initializeSingleSource(G, s); 
    for (int i = 0; i < (G -> E).size() - 1; i++) {
        for (edge* e : G -> E) {
            relax(e -> from, e -> to, e -> w); 
        }
    }
    for (edge* e: G -> E) {
        if (e -> to -> d > e -> from -> d + e -> w) {
            cout << e -> from -> d << endl;
            cout << e -> to -> d << endl;
            return false; 
        }
    }
    return true; 
}

long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
    vector<vertex> V(n); 
    for (int i = 0; i < n; i++) {
        vertex v; 
        v.name = i; 
        V[i] = v; 
    }
    vector<edge> E(edges.size()); 
    for (int i = 0; i < edges.size(); i++) {
        edge e; 
        e.from = &V[edges[i][0]]; 
        e.to = &V[edges[i][1]]; 
        e.w = edges[i][2]; 
        E[i] = e; 
    }
    graph* G = new graph; 
    for (int i = 0; i < n; i++) {
        G -> V.push_back(&V[i]); 
    }
    for (int i = 0; i < edges.size(); i++) {
        G -> E.push_back(&E[i]); 
    }
    if (bellmanFord(G, 1, (G -> V)[2])) {
        for (int i = 0; i < G -> V.size(); i++) {
            cout << i << ": " << (G -> V)[i] -> d << endl;
        }
    } else {
        cout << "loop contains negative cycle" << endl;
    }
}

int main() {
    vector<vector<int>> edges = {{0,2,2},{0,5,6},{1,0,3},{1,4,5},{2,1,1},{2,3,3},{2,3,4},{3,4,2},{4,5,1}}; 
    minimumWeight(6, edges, 1, 2, 3); 
}


