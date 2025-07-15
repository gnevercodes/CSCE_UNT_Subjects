#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <climits>

using namespace std;

class Graph {
public:
    Graph(int size) : adj(size, vector<int>(size, 0)) {}

    void addEdge(int from, int to) {
        adj[from][to] = 1;
        adj[to][from] = 1; // Assuming bidirectional flights for this problem
    }

    int size() const {
        return adj.size();
    }

    bool isEdge(int from, int to) const {
        return adj[from][to] == 1;
    }

private:
    vector<vector<int>> adj;
};

void findShortestHamiltonianCycle(Graph& graph, vector<int>& path, int& min_path_size, vector<int>& min_path) {
    do {
        int current_path_size = 0;
        bool valid_path = true;
        
        for (int i = 0; i < path.size() - 1; ++i) {
            if (graph.isEdge(path[i], path[i + 1])) {
                ++current_path_size;
            } else {
                valid_path = false;
                break;
            }
        }
        
        if (valid_path && graph.isEdge(path.back(), path[0])) {
            ++current_path_size; // count the return to the starting city
            if (current_path_size < min_path_size) {
                min_path_size = current_path_size;
                min_path = path;
            }
        }
    } while (next_permutation(path.begin() + 1, path.end())); // Keep the starting city fixed and permute the rest
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: routeSearch 3 <city_A>" << endl;
        return 1;
    }
    
    string city_A = argv[1];
    map<string, int> cityIndices;
    vector<string> cityNames;
    ifstream inFile("city.name");

    string city;
    int index = 0;
    while (getline(inFile, city)) {
        cityIndices[city] = index;
        cityNames.push_back(city);
        ++index;
    }

    Graph graph(index);
    // Assume that flight.txt contains all connections (both ways if bidirectional)
    // and the format is "city1 city2" on each line
    ifstream flightFile("flight.txt");
    string city1, city2;
    while (flightFile >> city1 >> city2) {
        graph.addEdge(cityIndices[city1], cityIndices[city2]);
    }

    vector<int> path(graph.size());
    iota(path.begin(), path.end(), 0); // Fill with 0, 1, ..., n-1

    int city_A_index = cityIndices[city_A];
    swap(path[0], path[city_A_index]); // Start the permutation with city_A

    int min_path_size = INT_MAX;
    vector<int> min_path;
    findShortestHamiltonianCycle(graph, path, min_path_size, min_path);

    if (min_path_size == INT_MAX) {
        cout << "No route that visits all cities and returns to " << city_A << " was found." << endl;
    } else {
        cout << city_A;
        for (int i = 1; i < min_path.size(); ++i) {
            cout << " to " << cityNames[min_path[i]];
        }
        cout << " to " << city_A;
        cout << "\nSmallest number of connection: " << min_path_size << endl;
    }
    return 0;
}
