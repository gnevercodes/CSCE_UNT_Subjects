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
    Graph(int size) : adj(size, vector<vector<int>>(size)) {}

    void addEdge(int from, int to) {
        adj[from][to] = 1; // Assume graph is directed; otherwise, also set adj[to][from] = 1;
    }

    vector<int> bfs(int start, int goal, const vector<int>& must_visit) {
        queue<vector<int>> q;
        vector<vector<bool>> visited(size(), vector<bool>(size(), false));
        q.push({start});

        while (!q.empty()) {
            vector<int> path = q.front();
            q.pop();
            int current = path.back();

            if (current == goal && containsAll(path, must_visit)) {
                return path;
            }

            for (int i = 0; i < size(); ++i) {
                if (adj[current][i] && !visited[current][i]) {
                    visited[current][i] = true;
                    vector<int> new_path(path);
                    new_path.push_back(i);
                    q.push(new_path);
                }
            }
        }
        return {};
    }

    int size() const {
        return adj.size();
    }

private:
    vector<vector<int>> adj;

    bool containsAll(const vector<int>& path, const vector<int>& must_visit) {
        for (int city : must_visit) {
            if (find(path.begin(), path.end(), city) == path.end()) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " <city_A> through <city_B> and <city_C> to <city_D>" << endl;
        return 1;
    }

    // Extract cities from command line arguments
    string cityA = argv[1];
    string cityB = argv[3];
    string cityC = argv[5];
    string cityD = argv[6];

    // Read cities and construct the graph
    map<string, int> cityMap;
    ifstream cityFile("city.name");
    string city;
    int cityIndex = 0;
    while (getline(cityFile, city)) {
        cityMap[city] = cityIndex++;
    }
    Graph graph(cityIndex);

    // Read flights and add edges to the graph
    ifstream flightFile("flight.txt");
    string fromCity, toCity;
    while (getline(flightFile, line)) {
        stringstream ss(line);
        getline(ss, fromCity, ':');
        while (getline(ss, toCity, ',')) {
            graph.addEdge(cityMap[fromCity], cityMap[toCity]);
        }
    }

    // Search for path from cityA to cityD including cityB and cityC
    vector<int> must_visit = {cityMap[cityB], cityMap[cityC]};
    vector<int> path = graph.bfs(cityMap[cityA], cityMap[cityD], must_visit);
    
    if (path.empty()) {
        cout << "No such route exists." << endl;
    } else {
        for (int i = 0; i < path.size(); ++i) {
            if (i > 0) cout << " to ";
            // Translate back to city names from indices
            auto it = find_if(cityMap.begin(), cityMap.end(), [&](const pair<string, int>& p) {
                return p.second == path[i];
            });
            if (it != cityMap.end()) {
                cout << it->first;
            }
        }
        cout << endl << "Total connections: " << path.size() - 1 << endl;
    }

    return 0;
}
