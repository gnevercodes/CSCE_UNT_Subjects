#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <limits>

using namespace std;

class Graph {
public:
    Graph(int d) : adj(d) {}
    ~Graph() {}

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
    }

    vector<int> BFS(int start, int goal) {
        vector<bool> visited(adj.size(), false);
        vector<int> parent(adj.size(), -1);
        queue<int> q;

        q.push(start);
        visited[start] = true;
        parent[start] = -1;  // No parent for start node.

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == goal) {
                vector<int> path;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
        return {};  // Return empty path if no path found.
    }

private:
    vector<vector<int>> adj; // adjacency list
};

int main() {
    int numCities;
    cout << "Enter the number of cities: ";
    cin >> numCities;

    Graph graph(numCities);
    map<string, int> cityIndex;
    string cityName;

    ifstream cityFile("city.name");
    for (int i = 0; i < numCities; i++) {
        getline(cityFile, cityName);
        cityIndex[cityName] = i;
    }
    cityFile.close();

    ifstream flightFile("flight.txt");
    string fromCity, toCity;
    while (getline(flightFile, fromCity) && getline(flightFile, toCity)) {
        graph.addEdge(cityIndex[fromCity], cityIndex[toCity]);
    }
    flightFile.close();

    string startCity, cityB, cityC, endCity;
    cout << "Enter the starting city (A): ";
    cin >> startCity;
    cout << "Enter the intermediary city (B): ";
    cin >> cityB;
    cout << "Enter another intermediary city (C): ";
    cin >> cityC;
    cout << "Enter the destination city (D): ";
    cin >> endCity;

    // Calculate routes: A-B-C-D and A-C-B-D
    auto pathABCD = graph.BFS(cityIndex[startCity], cityIndex[cityB]);
    auto pathBC = graph.BFS(cityIndex[cityB], cityIndex[cityC]);
    auto pathCD = graph.BFS(cityIndex[cityC], cityIndex[endCity]);

    auto pathACBD = graph.BFS(cityIndex[startCity], cityIndex[cityC]);
    auto pathCB = graph.BFS(cityIndex[cityC], cityIndex[cityB]);
    auto pathBD = graph.BFS(cityIndex[cityB], cityIndex[endCity]);

    if (pathABCD.empty() || pathBC.empty() || pathCD.empty() ||
        pathACBD.empty() || pathCB.empty() || pathBD.empty()) {
        cout << "No valid route exists passing through all required cities." << endl;
    } else {
        cout << "Route from " << startCity << " to " << endCity << " via " << cityB << " and " << cityC << " is: ";
        for (int i : pathABCD) cout << i << " ";
        for (int i = 1; i < pathBC.size(); i++) cout << pathBC[i] << " ";
        for (int i = 1; i < pathCD.size(); i++) cout << pathCD[i] << " ";
        cout << endl;

        cout << "Route from " << startCity << " to " << endCity << " via " << cityC << " and " << cityB << " is: ";
        for (int i : pathACBD) cout << i << " ";
        for (int i = 1; i < pathCB.size(); i++) cout << pathCB[i] << " ";
        for (int i = 1; i < pathBD.size(); i++) cout << pathBD[i] << " ";
        cout << endl;
    }

    return 0;
}
