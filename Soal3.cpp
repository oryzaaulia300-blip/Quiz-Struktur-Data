#include <iostream>
#include <vector>
#include <climits> 

using namespace std;

#define MAX_QUEUE 50

const int V = 6; 
char labels[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

// Fungsi untuk menampilkan Adjacency Matrix
void tampilkanMatrix(int graph[V][V]) {
    cout << "Adjacency Matrix (Bobot Jarak):\n    ";
    for (int i = 0; i < V; i++) cout << labels[i] << "\t";
    cout << "\n";

    for (int i = 0; i < V; i++) {
        cout << labels[i] << " | ";
        for (int j = 0; j < V; j++) {
            cout << graph[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << endl;
}

// 1. Fungsi BFS (Breadth-First Search) menggunakan Array Queue
void BFS(int graph[V][V], int startNode) {
    bool visited[V] = {false};
    int queue[MAX_QUEUE];
    int front = 0, rear = -1;

    cout << "Hasil Penelusuran BFS (Mulai dari " << labels[startNode] << "): ";
    
    rear++;
    queue[rear] = startNode;
    visited[startNode] = true;

    while (front <= rear) {
        int curr = queue[front];
        front++;
        cout << labels[curr] << " ";

        for (int i = 0; i < V; i++) {
            if (graph[curr][i] != 0 && !visited[i]) {
                rear++;
                queue[rear] = i;
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

// 2. Fungsi DFS (Depth-First Search) menggunakan Rekursi
void DFSRecursive(int graph[V][V], int curr, bool visited[]) {
    visited[curr] = true;
    cout << labels[curr] << " ";

    for (int i = 0; i < V; i++) {
        if (graph[curr][i] != 0 && !visited[i]) {
            DFSRecursive(graph, i, visited);
        }
    }
}

void DFS(int graph[V][V], int startNode) {
    bool visited[V] = {false};
    cout << "Hasil Penelusuran DFS (Mulai dari " << labels[startNode] << "): ";
    DFSRecursive(graph, startNode, visited);
    cout << endl;
}

// 3. Fungsi Dijkstra untuk mencari Rute Terpendek
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void Dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];
    bool visited[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "Tidak ada rute dari " << labels[src] << " ke " << labels[dest] << ".\n";
        return;
    }

    vector<char> path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(labels[v]);
    }

    cout << "Rute Terpendek dari " << labels[src] << " ke " << labels[dest] << " " << endl;
    cout << "Jalur       : ";
    
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i] << (i > 0 ? " -> " : "");
    }
    
    cout << "Total Jarak : " << dist[dest] << endl;

}

int main() {
    int graph[V][V] = {
        {0, 4, 2, 0, 0, 0}, // A
        {4, 0, 1, 5, 3, 0}, // B
        {2, 1, 0, 8, 6, 0}, // C
        {0, 5, 8, 0, 2, 4}, // D
        {0, 3, 6, 2, 0, 3}, // E
        {0, 0, 0, 4, 3, 0}  // F
    };

    tampilkanMatrix(graph);

    char asal, tujuan;
    cout << "Masukkan Vertex Awal (A-F)   : ";
    cin >> asal;
    cout << "Masukkan Vertex Tujuan (A-F) : ";
    cin >> tujuan;
    if (asal >= 'a' && asal <= 'z') asal = asal - 32;
    if (tujuan >= 'a' && tujuan <= 'z') tujuan = tujuan - 32;

    int src = asal - 'A';
    int dest = tujuan - 'A';

    if (src < 0 || src >= V || dest < 0 || dest >= V) {
        cout << "Input tidak valid! Gunakan huruf A sampai F.\n";
        return 1;
    }

    cout << "\n";
    BFS(graph, src);
    DFS(graph, src);
    Dijkstra(graph, src, dest);

    return 0;
}