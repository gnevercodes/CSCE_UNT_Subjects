#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

// Graph structure with an adjacency list
class Graph {
public:
    unordered_map<string, vector<string>> adj; // adjacency list

    // Add a direct flight between two cities
    void addFlight(const string& from, const string& to) {
        adj[from].push_back(to);
    }

    // BFS to find the shortest path with a limited number of connections
    vector<string> findShortestPath(const string& start, const string& end, int maxConnections) {
        queue<vector<string>> q; // queue of paths
        set<string> visited; // set to track visited cities
        q.push({start});

        while (!q.empty()) {
            vector<string> path = q.front();
            q.pop();

            string currentCity = path.back();

            // If we reached the end city, return the path
            if (currentCity == end) {
                return path;
            }

            if (path.size() - 1 < maxConnections) { // Check if the number of connections is within the limit
                for (const auto& neighbor : adj[currentCity]) {
                    if (find(path.begin(), path.end(), neighbor) == path.end()) { // Avoid cycles
                        vector<string> newPath = path;
                        newPath.push_back(neighbor);
                        q.push(newPath);
                    }
                }
            }
        }

        return {}; // Return empty if no path is found within the constraints
    }
};

// Read flight data from a file and build the graph
void buildGraph(Graph& graph, const string& filename) {
    ifstream infile(filename);
    string line;

    while (getline(infile, line)) {
        istringstream iss(line);
        string from, to;
        iss >> from; // "from" city
        while (iss >> to) { // Destination cities
            graph.addFlight(from, to);
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <start_city> <end_city> <max_connections>\n";
        return 1;
    }

    string startCity = argv[1];
    string endCity = argv[2];
    int maxConnections = stoi(argv[3]);

    Graph graph;
    buildGraph(graph, "flight.txt"); // Build the graph from the flight data

    vector<string> path = graph.findShortestPath(startCity, endCity, maxConnections); // Find the shortest path

    if (!path.empty()) {
        cout << "Shortest path from " << startCity << " to " << endCity << ": ";
        for (const auto& city : path) {
            cout << city << " ";
        }
        cout << "\nTotal connections: " << path.size() - 1 << "\n";
    } else {
        cout << "No path found with fewer than " << maxConnections << " connections.\n";
    }

    return 0;
}
