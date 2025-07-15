#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

class Graph {
public:
    Graph(int size) : adj(size, vector<int>(size, 0)) {}

    void addEdge(int from, int to) {
        if (from >= 0 && from < adj.size() && to >= 0 && to < adj.size()) {
            adj[from][to] = 1;
        }
    }

    vector<int> bfs(int start, int goal) {
        vector<bool> visited(adj.size(), false);
        vector<int> parent(adj.size(), -1);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == goal) {
                break;
            }

            for (int i = 0; i < adj[current].size(); ++i) {
                if (adj[current][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                    parent[i] = current;
                }
            }
        }

        if (!visited[goal]) {
            return {}; // return empty if goal is not reachable
        }

        // reconstruct path from goal to start using parent array
        vector<int> path;
        for (int v = goal; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void print() const {
        for (int i = 0; i < adj.size(); ++i) {
            cout << i << " -> ";
            for (int j = 0; j < adj[i].size(); ++j) {
                if (adj[i][j]) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }

private:
    vector<vector<int>> adj;
};

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cout << "Usage: routeSearch 1 <city_A> <city_B> <num_connection>\n";
        return 1;
    }

    string cityA = argv[2];
    string cityB = argv[3];
    int maxConnections = stoi(argv[4]);

    // Load cities and build the graph
    ifstream cityFile("city.name");
    map<string, int> city;
    string line;
    int index = 0;
    while (getline(cityFile, line)) {
        city[line] = index++;
    }
    cityFile.close();

    Graph graph(index);

    ifstream flightFile("flight.txt");
    string fromCity, toCity;
    while (getline(flightFile, line)) {
        stringstream ss(line);
        getline(ss, fromCity, ':'); // Parse city from the line
        while (getline(ss, toCity, ',')) { // Assuming cities are separated by commas
            graph.addEdge(city[fromCity], city[toCity]);
        }
    }
    flightFile.close();

    vector<int> path = graph.bfs(city[cityA], city[cityB]);
    if (path.empty()) {
        cout << "No route found.\n";
    } else if (path.size() - 1 > maxConnections) {
        cout << "No route within the allowed connections.\n";
    } else {
        cout << cityA;
        for (int i = 1; i < path.size(); ++i) {
            cout << " to " << path[i]; // Assuming you have a way to convert indices back to city names
        }
        cout << "\nTotal connection: " << path.size() - 1 << endl;
    }

    return 0;
}
