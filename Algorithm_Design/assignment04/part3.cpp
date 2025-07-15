#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <climits>

using namespace std;

class Graph {
public:
    Graph(int vertices) : adj(vertices), visited(vertices, false) {}

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
    }

    bool findHamiltonianPath(int current, int start, vector<int>& path, int pathCount) {
        if (pathCount == adj.size()) { // All vertices are visited
            for (int next : adj[current]) { // Check if there's a return path to start
                if (next == start) {
                    path.push_back(start);
                    return true;
                }
            }
            return false;
        }

        for (int next : adj[current]) {
            if (!visited[next]) {
                visited[next] = true;
                path.push_back(next);
                if (findHamiltonianPath(next, start, path, pathCount + 1)) {
                    return true;
                }
                visited[next] = false;
                path.pop_back();
            }
        }

        return false;
    }

    vector<int> findCycle(int start) {
        vector<int> path;
        path.push_back(start);
        visited[start] = true;

        if (!findHamiltonianPath(start, start, path, 1)) {
            path.clear();
        }

        visited[start] = false;
        return path;
    }

private:
    vector<vector<int>> adj;
    vector<bool> visited;
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

    string startCity;
    cout << "Enter the starting city (A): ";
    cin >> startCity;

    vector<int> route = graph.findCycle(cityIndex[startCity]);

    if (route.empty()) {
        cout << "No complete route found starting and ending at " << startCity << "." << endl;
    } else {
        cout << "Route found: ";
        for (int city : route) {
            for (auto& pair : cityIndex) {
                if (pair.second == city) {
                    cout << pair.first << " ";
                    break;
                }
            }
        }
        cout << endl;
    }

    return 0;
}
