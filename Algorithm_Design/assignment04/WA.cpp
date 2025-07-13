/***********************************************************
  Group#  : No Group
  Member  : ganesh
  Synopsis: read from city.name and flight.txt
            store the graph in a adjacency matrix
***********************************************************/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <climits>
#include <queue>
#include <stack>

using namespace std;

class Graph{
     public:
          Graph(int d);
          ~Graph(){};
          int getNumVertices(){return n;}
          int (* getAdjacencyMatrix())[140]{return adj;}

          void print();
          void addEdge(int node1, int node2){ adj[node1][node2] = 1; };
     private: 
          int n;
          int adj[140][140]; // You may want to use adjacent list implementation for sparse graph instead
};

Graph::Graph(int d){
    for (int i=0; i < d; i++){
        for (int j=0; j < d; j++){
            adj[i][j] = 0;
        }
    }
    n = d;
};

void Graph::print(){
    for (int i=0; i < n; i++){
        cout << i << " -> ";
        for (int j=0; j < n; j++){
            if (adj[i][j]){
                cout << j << " ";
            }
        }
        cout << endl;
    }

};

struct strCmp {
    bool operator()( const string s1, const string s2 ) const {
        return s1 <s2;
    }
};


/*to map a city name with an unique integer */
map<const string, int, strCmp> city;

void routeSearch(Graph graph);
void routeSearch_1(Graph graph, int city_A, int city_B, int num_connection);
void routeSearch_2(Graph graph, int city_A, int city_B, int city_C, int city_D);
void routeSearch_3(Graph graph, int city_A);
void printRoute(int pred[], int start, int end);
void routeSearch_4(Graph graph, int city_A, int city_B, int city_C);
void Dijkstra(Graph graph, int s, int d[], int p[]);

int main(int argc, char *argv[]){
   int i,j, node1, node2,n;
   string line;


   cout << "Please enter the number of cities in your graph: " << endl;
   cout << "---------------------------------------------------" << endl;
   cin >> n;
   Graph graph(n);
 
   char lineChar[256];

   ifstream cityFile;
   cityFile.open("city.name", ios::in);

   for (i = 0; i < n; i++){
      cityFile.getline(lineChar,256);
      line = lineChar;
      city[line] = i;
      cout << line << " is numbered as city " << city[line]<< endl;
   }

   cityFile.close();

  /* initialize adjacent matrix*/
   ifstream flightFile;
   flightFile.open("flight.txt", ios::in);

   while (flightFile.getline(lineChar, 256)){
      /* if line constains From: */
      line = lineChar;

      if (line.find("From:", 0) == 0 ){
          line.erase(0,7);
          node1 = city[line];
      } else {
          line.erase(0,7);
          node2 = city[line];
          graph.addEdge(node1,node2);
      }
   }
   flightFile.close();

   /* print the graph */
   cout << endl << "The graph generated can be represented by the following adjacent matrix : " << endl;
   cout << "-----------------------------------------------------------------------------------" << endl;
   graph.print();

   routeSearch(graph);
}

// Dijkstra Algorithm
void Dijkstra(Graph graph, int s, int d[], int p[]) {
    int n = graph.getNumVertices();
    std::vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        d[i] = INT_MAX;
        p[i] = -1;
    }

    // STL priority queue
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    d[s] = 0;
    pq.push(std::make_pair(0, s));  // (distance, vertex)

    while (!pq.empty()) {
        int u = pq.top().second;  // Current vertex with the smallest distance
        pq.pop();

        if (visited[u]) continue;  // Skip if already visited
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph.getAdjacencyMatrix()[u][v] != 0 && !visited[v]) {
                int weight = graph.getAdjacencyMatrix()[u][v];
                if (d[u] + weight < d[v]) {
                    d[v] = d[u] + weight;
                    p[v] = u;
                    pq.push(std::make_pair(d[v], v));
                }
            }
        }
    }
}

void routeSearch(Graph graph){
    int choice;
    cout << "Please select the type of the questions: " << endl;
    cout << "1: From city 'A' to city 'B' with less than x connestions?" << endl;
    cout << "2: Route with the samllest number of connections from city 'A' to city 'D' through city 'B' and 'C'?" << endl;
    cout << "3: Visit all reachable cities from city 'A' and return to 'A' with the minimum number of connections?" << endl;
    cout << "4: Find an good/optimistic meeting city for three friends in different cities?" << endl;
	cout << "Enter your choice: ";
    cin >> choice;

    int city_A, city_B, city_C, city_D;
    int num_connection;

    switch (choice){
        case 1:
            cout << "Please enter the city A: ";
            cin >> city_A;
            cout << "Please enter the city B: ";
            cin >> city_B;
            cout << "number of connections: ";
            cin >> num_connection;
            routeSearch_1(graph, city_A, city_B, num_connection);
            break;

        case 2:
            cout << "Please enter the city A: ";
            cin >> city_A;
            cout << "Please enter the city D: ";
            cin >> city_D;
            cout << "Please enter the city B: ";
            cin >> city_B;
            cout << "Please enter the city C: ";
            cin >> city_C;
            routeSearch_2(graph, city_A, city_B, city_C, city_D);
            break;

        case 3:
            cout << "Please enter the city A: ";
            cin >> city_A;
            routeSearch_3(graph, city_A);
            break;

        case 4:
            cout << "Please enter the city A (ganesh): ";
            cin >> city_A;
            cout << "Please enter the city B (divya): ";
            cin >> city_B;
            cout << "Please enter the city C (shreya): ";
            cin >> city_C;
            routeSearch_4(graph, city_A, city_B, city_C);
            break;

        default:
            cout << "incorrect choice" << endl;
    }


}

//Task 1
void routeSearch_1(Graph graph, int city_A, int city_B, int num_connection) {
    int n = graph.getNumVertices();
    int d[n], p[n];
    vector<int> ans;
    Dijkstra(graph, city_A, d, p);
    if(d[city_B] <= num_connection){ //there are less than x connections
        int cur_city = city_B;
        int i;
        while(cur_city != -1) {
            ans.insert(ans.begin(), cur_city);
            cur_city = p[cur_city];
        }
        for(i = 0; i < ans.size(); i++){
            if(i != ans.size() - 1){
                cout << "city" << ans[i] << " to ";
            }
            else{
                cout << "city" << ans[i];
            }
        }
        cout << endl;
        cout << "Total connection: " << i-1 << endl;
    }
    else{
        //can not fly from A to B with less than x connections
        cout << "No such route." << endl;
    }
}

//Task 2
void routeSearch_2(Graph graph, int city_A, int city_B, int city_C, int city_D)
{
    // Get the graph
    int n = graph.getNumVertices();

    // variables for Dijkstra & flight routes
    int d[n], p[n], cur_city;
    vector<int> flightroute1, flightroute2, finalflightroute;

    // flags
    int route1_exists = 0;
    int route2_exists = 0;

    // Flight route: 1
    // A->B->C->D
    // Find the shortest route from city_C to city_D
    Dijkstra(graph, city_C, d, p);
    if (d[city_D] != INT_MAX)
    {
        cur_city = city_D;
        while (cur_city != -1)
        {
            flightroute1.insert(flightroute1.begin(), cur_city);
            cur_city = p[cur_city];
        }
    }
    else
    {
        cout << "No such route from city " << city_C << " --> city " << city_D << "." << endl;
        route1_exists = 1;
    }

    if (route1_exists == 0)
    {
        // To avoid duplicates remove the first node
        flightroute1.erase(flightroute1.begin());

        // Find the shortest route from city_B to city_C
        Dijkstra(graph, city_B, d, p);
        if (d[city_C] != INT_MAX)
        {
            cur_city = city_C;
            while (cur_city != -1)
            {
                flightroute1.insert(flightroute1.begin(), cur_city);
                cur_city = p[cur_city];
            }
        }
        else
        {
            cout << "No such route from city " << city_B << " --> city " << city_C << "." << endl;
            route1_exists = 1;
        }
    }

    if (route1_exists == 0)
    {
        // To avoid duplicates remove the first node
        flightroute1.erase(flightroute1.begin());

        // Find the shortest route from city_A to city_B
        Dijkstra(graph, city_A, d, p);
        if (d[city_B] != INT_MAX)
        {
            cur_city = city_B;
            while (cur_city != -1)
            {
                flightroute1.insert(flightroute1.begin(), cur_city);
                cur_city = p[cur_city];
            }
        }
        else
        {
            cout << "No such route from city " << city_A << " --> city " << city_B << "." << endl;
            route1_exists = 1;
        }
    }


    // Flight route: 2
    // A->C->B->D
    // Find the shortest route from city_B to city_D
    Dijkstra(graph, city_B, d, p);
    if (d[city_D] != INT_MAX)
    {
        cur_city = city_D;
        while (cur_city != -1)
        {
            flightroute2.insert(flightroute2.begin(), cur_city);
            cur_city = p[cur_city];
        }
    }
    else
    {
        cout << "No such route from city " << city_B << " --> city " << city_D << "." << endl;
        route2_exists = 1;
    }

    if (route2_exists == 0)
    {
        // To avoid duplicates remove the first node
        flightroute2.erase(flightroute2.begin());

        // Find the shortest route from city_C to city_B
        Dijkstra(graph, city_C, d, p);
        if (d[city_B] != INT_MAX)
        {
            cur_city = city_B;
            while (cur_city != -1)
            {
                flightroute2.insert(flightroute2.begin(), cur_city);
                cur_city = p[cur_city];
            }
        }
        else
        {
            cout << "No such route from city " << city_C << " --> city " << city_B << "." << endl;
            route2_exists = 1;
        }
    }

    if (route2_exists == 0)
    {
        // To avoid duplicates remove the first node
        flightroute2.erase(flightroute2.begin());

        // Find the shortest route from city_A to city_C
        Dijkstra(graph, city_A, d, p);
        if (d[city_C] != INT_MAX)
        {
            cur_city = city_C;
            while (cur_city != -1)
            {
                flightroute2.insert(flightroute2.begin(), cur_city);
                cur_city = p[cur_city];
            }
        }
        else
        {
            cout << "No such route from city " << city_A << " --> city " << city_C << "." << endl;
            route2_exists = 1;
        }
    }

    // Compare the #connections in flightroute1 & flightroute2 to set finalflightroute
    // #connections = flightroute size - 1, as it cancels on both sides
    // Hence directly comparing size
    if (route1_exists == 0 && route2_exists == 0)
    {
        finalflightroute = (flightroute1.size()<=flightroute2.size()) ? flightroute1 : flightroute2;
    }
    else if (route1_exists == 0)
    {
        finalflightroute = flightroute1;
    }
    else if (route2_exists == 0)
    {
        finalflightroute = flightroute2;
    }

    // Lets print the final flight route
    for (int i=0; i<finalflightroute.size(); i++)
        if (i == finalflightroute.size()-1)
            cout << "city " << finalflightroute[i];
        else
            cout << "city " << finalflightroute[i] << " --> ";
    cout << endl;
    cout << "smallest number of connection: " << finalflightroute.size()-1 << endl;
}

// Task 3
void routeSearch_3(Graph graph, int startCity) {
    int n = graph.getNumVertices();
    vector<bool> visited(n, false);
    int currentCity = startCity;
    vector<int> tour;
    tour.push_back(currentCity);
    visited[currentCity] = true;

    int d[n], p[n]; // Distance and predecessor arrays for Dijkstra

    // Visit all cities using a greedy approach
    while (true) {
        Dijkstra(graph, currentCity, d, p);

        // Find the nearest unvisited city
        int minDist = INT_MAX;
        int nextCity = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && d[i] < minDist && d[i] != INT_MAX) {
                nextCity = i;
                minDist = d[i];
            }
        }

        if (nextCity == -1) {
            break; // No more reachable unvisited cities
        }

        // Visit the next city
        currentCity = nextCity;
        visited[currentCity] = true;
        tour.push_back(currentCity);
    }

    cout << "Below is max connections we went, ";
    for (auto i: tour)
        cout << i << ' ';
    cout << endl;
    cout << "No. of connections are " << tour.size()-1 << endl;

    // Return to the start city if possible
    if (currentCity != startCity) {
        Dijkstra(graph, currentCity, d, p);
        if (d[startCity] != INT_MAX) {
            // reconstruct the path back to the start city
            int step = startCity;
            while (step != currentCity) {
                tour.push_back(step);
                step = p[step];
            }
            tour.push_back(startCity);
        } else {
            cout << "Cannot return to the start city from city " << currentCity << endl;
            return;
        }
    }

    if (tour.size() > 1) {
        cout << "Optimal tour: ";
        for (size_t i = 0; i < tour.size(); i++) {
            cout << "City " << tour[i];
            if (i < tour.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;

        cout << "smallest number of connection: " << tour.size()-1 << endl;
    }
    else {
        cout << "No connections from the start city " << currentCity << endl;
    }
}

// Task 4
void routeSearch_4(Graph graph, int city_A, int city_B, int city_C) {
    int n = graph.getNumVertices();
    int d_A[n], p_A[n]; // Distance and predecessor arrays for A
    int d_B[n], p_B[n]; // Distance and predecessor arrays for B
    int d_C[n], p_C[n]; // Distance and predecessor arrays for C

    // Compute shortest paths from each city
    Dijkstra(graph, city_A, d_A, p_A);
    Dijkstra(graph, city_B, d_B, p_B);
    Dijkstra(graph, city_C, d_C, p_C);

    int minDistance = INT_MAX;
    int meetingCity = -1;

    // Evaluate the best meeting city
    for (int i = 0; i < n; i++) {
        if (i != city_A && i != city_B && i != city_C) {
            int totalDistance = d_A[i] + d_B[i] + d_C[i];
            if (totalDistance < minDistance) {
                minDistance = totalDistance;
                meetingCity = i;
            }
        }
    }

    if (d_A[meetingCity] == INT_MAX || d_B[meetingCity] == INT_MAX || d_C[meetingCity] == INT_MAX) {
        cout << "No feasible meeting city exists as one or more cities are unreachable." << endl;
        return;
    }

    if (meetingCity == -1) {
        cout << "No suitable meeting city found." << endl;
    } else {
        cout << "The meeting city is " << meetingCity << " with a total connection distance of " << minDistance << "." << endl;
        cout << "Routes to city " << meetingCity << ":" << endl;
        printRoute(p_A, city_A, meetingCity);
        printRoute(p_B, city_B, meetingCity);
        printRoute(p_C, city_C, meetingCity);
    }
}

void printRoute(int pred[], int start, int end) {
    stack<int> path;
    int step = end;
    while (step != -1 && step != start) {
        path.push(step);
        step = pred[step];
    }
    path.push(start);
    while (!path.empty()) {
        cout << "City " << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

