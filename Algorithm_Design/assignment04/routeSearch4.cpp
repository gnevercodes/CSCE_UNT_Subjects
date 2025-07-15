#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

class Graph {
public:
    Graph(int n) : edges(n), n(n) {}

    void addEdge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u); // Assuming bidirectional travel is possible
    }

    vector<int> shortestPath(int src) {
        vector<int> dist(n, numeric_limits<int>::max());
        queue<int> q;

        dist[src] = 0;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : edges[u]) {
                if (dist[v] == numeric_limits<int>::max()) {
                    q.push(v);
                    dist[v] = dist[u] + 1;
                }
            }
        }

        return dist;
    }

private:
    vector<vector<int>> edges;
    int n;
};

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <city_A> <city_B> <city_C>" << endl;
        return 1;
    }

    string cityA = argv[1];
    string cityB = argv[2];
    string cityC = argv[3];

    map<string, int> cityIndices;
    vector<string> cityNames;
    ifstream inFile("city.name");

    string city;
    int index = 0;
    while (getline(inFile, city)) {
        cityIndices[city] = index++;
        cityNames.push_back(city);
    }
    Graph graph(index);

    ifstream flightFile("flight.txt");
    string city1, city2;
    while (flightFile >> city1 >> city2) {
        graph.addEdge(cityIndices[city1], cityIndices[city2]);
    }

    auto distA = graph.shortestPath(cityIndices[cityA]);
    auto distB = graph.shortestPath(cityIndices[cityB]);
    auto distC = graph.shortestPath(cityIndices[cityC]);

    int minDistance = numeric_limits<int>::max();
    int meetingCity = -1;

    for (int i = 0; i < index; i++) {
        if (distA[i] != numeric_limits<int>::max() && 
            distB[i] != numeric_limits<int>::max() && 
            distC[i] != numeric_limits<int>::max()) {
            int totalDistance = distA[i] + distB[i] + distC[i];
            if (totalDistance < minDistance) {
                minDistance = totalDistance;
                meetingCity = i;
            }
        }
    }

    if (meetingCity == -1) {
        cout << "No suitable meeting city found." << endl;
    } else {
        cout << "You three should meet at " << cityNames[meetingCity] << endl;
        cout << "Route for first person: " << cityA << " (" << distA[meetingCity] << " connections)" << endl;
        cout << "Route for second person: " << cityB << " (" << distB[meetingCity] << " connections)" << endl;
        cout << "Route for third person: " << cityC << " (" << distC[meetingCity] << " connections)" << endl;
        cout << "Total number of connection: " << minDistance << endl;
    }

    return 0;
}
