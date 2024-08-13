#include <iostream>
#include <cstring>

using namespace std;


const int MAX_LOCATIONS = 100;
const int MAX_EDGES = 100;

struct Location {
    char name[50];
};


struct Edge {
    int destinationIndex;
    int cost;
};

struct Graph {
    Location locations[MAX_LOCATIONS];
    Edge adjacencyList[MAX_LOCATIONS][MAX_EDGES];
    int edgesCount[MAX_LOCATIONS];
     int locationsCount;
};

   struct Package {
    char name[50];
    int locationIndices[MAX_LOCATIONS];
    int totalCost;

    Package() : totalCost(0) {
        name[0] = '\0';
        for (int i = 0; i < MAX_LOCATIONS; ++i) {
            locationIndices[i] = -1;
        }
    }

    Package(const char* packageName) : totalCost(0) {
        strcpy(name, packageName);
        for (int i = 0; i < MAX_LOCATIONS; ++i) {
            locationIndices[i] = -1;
        }
    }
};


//functions
void addLocation(Graph& graph, const char* name);
void addEdge(Graph& graph, int sourceIndex, int destIndex, int cost);
void dijkstra(const Graph& graph, int start, int end, int path[], int& pathLength);
void displayLocations(const Graph& graph);
void displayPackages(const Graph& graph, const Package packages[], int packageCount);
void adminPortal(Graph& graph, Package packages[], int& packageCount);
void customerPortal(const Graph& graph, const Package packages[], int packageCount);
void displayMinCostPath(const Graph& graph, int start, int end, const int path[], int pathLength);
int calculatePackageCost(const Graph& graph, const int locationIndices[], int size);

int calculatePackageCost(const Graph& graph, const int locationIndices[], int size);
const string ADMIN_PASSWORD = "admin123";


int main() {
    Graph graph;
   const int MAX_PACKAGES = 10;
    Package packages[10];
    int packageCount = 0;
      graph.locationsCount = 0;
    for (int i = 0; i < MAX_LOCATIONS; ++i) {
   graph.edgesCount[i] = 0;}



    // Adding Indian locations
    addLocation(graph, "Delhi");
    addLocation(graph, "Mumbai");
    addLocation(graph, "Jaipur");
    addLocation(graph, "Goa");
    addLocation(graph, "Bangalore");
     addLocation(graph, "Chennai");
    addLocation(graph, "Kolkata");
    addLocation(graph, "Hyderabad");
    addLocation(graph, "Ahmedabad");
    addLocation(graph, "Pune");
    addLocation(graph, "Lucknow");
    addLocation(graph, "Chandigarh");
    addLocation(graph, "Bhopal");
    addLocation(graph, "Indore");
    addLocation(graph, "Coimbatore");
    addLocation(graph, "Visakhapatnam");
    addLocation(graph, "Surat");

    // Adding edges between Indian locations
    addEdge(graph, 0, 1, 1400); // Delhi to Mumbai
    addEdge(graph, 0, 2, 300); // Delhi to Jaipur
    addEdge(graph, 1, 3, 560); // Mumbai to Goa
    addEdge(graph, 2, 4, 320); // Jaipur to Bangalore
    addEdge(graph, 3, 4, 550); // Goa to Bangalore
    addEdge(graph, 5, 6, 750);  // Chennai to Kolkata
addEdge(graph, 6, 7, 500);  // Kolkata to Hyderabad
addEdge(graph, 7, 4, 900);  // Hyderabad to Bangalore
addEdge(graph, 8, 9, 400);  // Ahmedabad to Pune
addEdge(graph, 9, 4, 600);  // Pune to Bangalore
addEdge(graph, 10, 11, 700); // Lucknow to Chandigarh
addEdge(graph, 11, 12, 300); // Chandigarh to Bhopal
addEdge(graph, 12, 13, 400); // Bhopal to Indore
addEdge(graph, 13, 4, 350);  // Indore to Bangalore
addEdge(graph, 8, 16, 300);  // Ahmedabad to Surat


   // Adding travel packages
    packages[0] = Package("Golden Triangle");
    packages[0].locationIndices[0] = 0; // Delhi
    packages[0].locationIndices[1] = 2; // Jaipur
    packages[0].locationIndices[2] = 1; // Mumbai
    packages[0].totalCost = 1500;

    packages[1] = Package("Beach Paradise");
    packages[1].locationIndices[0] = 3; // Goa
    packages[1].locationIndices[1] = 4; // Bangalore
    packages[1].totalCost = 800;

    packages[2] = Package("Cultural Delights");
packages[2].locationIndices[0] = 0; // Delhi
packages[2].locationIndices[1] = 5; // Chennai
packages[2].locationIndices[2] = 6; // Kolkata
packages[2].totalCost = 2000;

packages[3] = Package("Southern Sojourn");
packages[3].locationIndices[0] = 5; // Chennai
packages[3].locationIndices[1] = 7; // Hyderabad
packages[3].locationIndices[2] = 4; // Bangalore
packages[3].totalCost = 1200;

packages[4] = Package("Heritage Trail");
packages[4].locationIndices[0] = 2; // Jaipur
packages[4].locationIndices[1] = 6; // Kolkata
packages[4].locationIndices[2] = 9; // Pune
packages[4].totalCost = 1800;

packages[5] = Package("Gujarat Explorer");
packages[5].locationIndices[0] = 8; // Ahmedabad
packages[5].locationIndices[1] = 16; // Surat
packages[5].totalCost = 600;

packages[6] = Package("Central India Odyssey");
packages[6].locationIndices[0] = 10; // Lucknow
packages[6].locationIndices[1] = 11; // Chandigarh
packages[6].locationIndices[2] = 12; // Bhopal
packages[6].totalCost = 1600;

packageCount = 7;


    int loginChoice;

    do {

         cout << "\nWelcome to the Travel Planner!\n";
        cout << "--------------------------------\n";
        cout << "Login Menu:\n";
        cout << "1. Admin Portal\n";
        cout << "2. Customer Portal\n";
        cout << "3. Exit Program\n";
        cout << "Enter your choice: ";
        cin >> loginChoice;

        switch (loginChoice) {
            case 1: {
                string password;
                cout << "Enter the admin password: ";
                cin >> password;

                if (password == ADMIN_PASSWORD) {
                    adminPortal(graph, packages, packageCount);
                } else {
                    cout << "Incorrect password. Access denied.\n";
                }
                break;
            }
            case 2:
                customerPortal(graph, packages, packageCount);
                break;
            case 3:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (loginChoice != 3);

    return 0;
}

void addLocation(Graph& graph, const char* name) {
    if (graph.locationsCount < MAX_LOCATIONS) {
        strcpy(graph.locations[graph.locationsCount].name, name);
        graph.locationsCount++;
        cout << "Location '" << name << "' added successfully.\n";
    } else {
        cout << "Cannot add more locations. Maximum limit reached.\n";
    }
}

void addEdge(Graph& graph, int sourceIndex, int destIndex, int cost) {
  if (sourceIndex >= 0 && sourceIndex < graph.locationsCount &&
    destIndex >= 0 && destIndex < MAX_LOCATIONS &&
    graph.edgesCount[sourceIndex] < MAX_EDGES) {
        if (graph.edgesCount[sourceIndex] < MAX_EDGES) {
            graph.adjacencyList[sourceIndex][graph.edgesCount[sourceIndex]].destinationIndex = destIndex;
            graph.adjacencyList[sourceIndex][graph.edgesCount[sourceIndex]].cost = cost;

            graph.edgesCount[sourceIndex]++;

            cout << "Edge from '" << graph.locations[sourceIndex].name << "' to '"
                      << graph.locations[destIndex].name << "' added successfully with cost " << cost << ".\n";
        } else {
            cout << "Cannot add more edges for location '" << graph.locations[sourceIndex].name
                      << "'. Maximum limit reached.\n";
        }
    } else {
        cout << "Invalid location indices.\n";
    }
}



void dijkstra(const Graph& graph, int start, int end, int path[], int& pathLength) {
    const int INFINITY_COST = 999999;


    bool visited[MAX_LOCATIONS];
    int minCost[MAX_LOCATIONS];


    for (int i = 0; i < graph.locationsCount; ++i) {
        visited[i] = false;
        minCost[i] = INFINITY_COST;
        path[i] = -1;
    }


    minCost[start] = 0;


    for (int i = 0; i < graph.locationsCount - 1; ++i) {

        int minCostNode = -1;
        for (int j = 0; j < graph.locationsCount; ++j) {
            if (!visited[j] && (minCostNode == -1 || minCost[j] < minCost[minCostNode])) {
                minCostNode = j;
            }
        }


        visited[minCostNode] = true;


        for (int j = 0; j < graph.edgesCount[minCostNode]; ++j) {
            int neighborIndex = graph.adjacencyList[minCostNode][j].destinationIndex;
            int newCost = minCost[minCostNode] + graph.adjacencyList[minCostNode][j].cost;

            if (!visited[neighborIndex] && newCost < minCost[neighborIndex]) {
                minCost[neighborIndex] = newCost;
                path[neighborIndex] = minCostNode;
            }
        }
    }


    pathLength = 0;
    int current = end;
    while (current != -1) {
        path[pathLength++] = current;
        current = path[current];
    }


    for (int i = 0; i < pathLength / 2; ++i) {
        int temp = path[i];
        path[i] = path[pathLength - i - 1];
        path[pathLength - i - 1] = temp;
    }
}


void displayPackages(const Graph& graph, const Package packages[], int packageCount) {
    cout << "Available Travel Packages:\n";


    if (packageCount == 0) {
        cout << "No packages available.\n";
        return;
    }


    for (int i = 0; i < packageCount; ++i) {
        cout << "Package Name: " << packages[i].name << "\n";
        cout << "Locations: ";


        for (int j = 0; packages[i].locationIndices[j] != -1; ++j) {
            int locationIndex = packages[i].locationIndices[j];
            if (locationIndex >= 0 && locationIndex < MAX_LOCATIONS) {
                cout << graph.locations[locationIndex].name << " ";
            } else {
                cout << "Unknown Location ";
            }
        }

        cout << "\nTotal Cost: " << packages[i].totalCost << "\n\n";
    }
}



void displayLocations(const Graph& graph) {
    cout << "Available Locations:\n";


    if (graph.locationsCount == 0) {
        cout << "No locations available.\n";
        return;
    }


    for (int i = 0; i < graph.locationsCount; ++i) {
        cout << "Location " << i << ": " << graph.locations[i].name << "\n";
    }
}



void adminPortal(Graph& graph, Package packages[], int& packageCount) {
    int choice;

    do {
        cout << "\nAdmin Portal Menu:\n";
        cout << "1. Add Location\n";
        cout << "2. Add Edge\n";
        cout << "3. Add Package\n";
        cout << "4. Display Locations\n";
        cout << "5. Display Packages\n";
        cout << "6. Exit Admin Portal\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                char locationName[50];
                cout << "Enter the name of the location: ";
                cin.ignore();//buffer
                cin.getline(locationName, sizeof(locationName));
                addLocation(graph, locationName);
                break;
            }
            case 2: {
                int source, dest, cost;
                cout << "Enter the indices of the source and destination locations: ";
                cin >> source >> dest;
                cout << "Enter the cost of the edge: ";
                cin >> cost;
                addEdge(graph, source, dest, cost);
                break;
            }
            case 3: {

    int locationIndices[10];
    char packageName[50];
    int totalCost = 0;
    int index = 0;

    cout << "Enter the name of the package: ";
    cin.ignore();
    cin.getline(packageName, sizeof(packageName));

    cout << "Select locations to include in the package (enter -1 to finish):\n";
    do {
        displayLocations(graph);
        cout << "Enter the index of the location to include (-1 to finish): ";
        cin >> locationIndices[index];


        if (locationIndices[index] == -1) {

            break;
        } else if (locationIndices[index] >= 0 && locationIndices[index] < graph.locationsCount) {

            totalCost += calculatePackageCost(graph, locationIndices, index);
            index++;
        } else {
            cout << "Invalid location index. Try again.\n";
        }
    } while (index < 10);


    if (index > 1) {
        Package newPackage(packageName);
        for (int i = 0; locationIndices[i] != -1; ++i) {
            newPackage.locationIndices[i] = locationIndices[i];
        }
        newPackage.totalCost = totalCost;


        if (packageCount < 10) {
            packages[packageCount++] = newPackage;
            cout << "Package added successfully.\n";
        } else {
            cout << "Cannot add more packages. Maximum limit reached.\n";
        }
    } else {
        cout << "No locations selected. Package not added.\n";
    }
    break;
}

            case 4: {
                displayLocations(graph);
                break;
            }
            case 5: {
                displayPackages(graph,packages, packageCount);
                break;
            }
            case 6: {
                cout << "Exiting Admin Portal.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

int calculatePackageCost(const Graph& graph, const int locationIndices[], int size) {
    int totalCost = 0;

    for (int i = 0; i < size - 1; ++i) {
        int sourceIndex = locationIndices[i];
        int destIndex = locationIndices[i + 1];


        bool edgeFound = false;
        for (int j = 0; j < graph.edgesCount[sourceIndex]; ++j) {
            if (graph.adjacencyList[sourceIndex][j].destinationIndex == destIndex) {
                totalCost += graph.adjacencyList[sourceIndex][j].cost;
                edgeFound = true;
                break;
            }
        }


        if (!edgeFound) {
            return -1;
        }
    }

    return totalCost;
}




void displayMinCostPath(const Graph& graph, int start, int end, const int path[], int pathLength) {

    cout << "Minimum cost path from '" << graph.locations[start].name << "' to '"
              << graph.locations[end].name << "': ";
    for (int i = pathLength - 1; i >= 0; --i) {
        cout << graph.locations[path[i]].name << " ";
    }
    cout << "\n";
}



void customerPortal(const Graph& graph, const Package packages[], int packageCount) {
    int choice;

    do {
        cout << "\nCustomer Portal Menu:\n";
        cout << "1. Display Locations\n";
        cout << "2. Display Packages\n";
        cout << "3. Plan Trip\n";
        cout << "4. Make Booking\n";
        cout << "5. Exit Customer Portal\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                displayLocations(graph);
                break;
            }
            case 2: {
                displayPackages(graph,packages, packageCount);
                break;
            }
            case 3: {
                  int source;
    cout << "Enter the index of the source location: ";
    cin >> source;

    if (source >= 0 && source < graph.locationsCount) {

        const int MAX_DESTINATIONS = 10;
        int destinationIndices[MAX_DESTINATIONS];
        int destinationCount = 0;
        int destination;

        do {
    cout << "Enter the index of a destination location (-1 to finish): ";
    cin >> destination;

    if (destination >= 0 && destination < graph.locationsCount) {
        if (destination != -1) {
            destinationIndices[destinationCount++] = destination;


            if (destinationCount >= MAX_DESTINATIONS) {
                cout << "Maximum number of destinations reached.\n";
                break;
            }
        }
    } else if (destination != -1) {
        cout << "Invalid destination index. Try again.\n";
    }
} while (destination != -1);


int path[MAX_LOCATIONS];
int pathLength;
dijkstra(graph, source, destinationIndices[destinationCount - 1], path, pathLength);


cout << "Full route from '" << graph.locations[source].name << "' to '"
          << graph.locations[destinationIndices[destinationCount - 1]].name << "': ";
for (int i = 0; i < pathLength - 1; ++i) {
    cout << graph.locations[path[i]].name << " -> ";
}
cout << graph.locations[destinationIndices[destinationCount - 1]].name << "\n";


cout << "Travel Plan Details:\n";
cout << "Number of locations: " << pathLength  << "\n";

int totalCost = calculatePackageCost(graph, path, pathLength);
if (totalCost != -1) {
    cout << "Total cost: " << totalCost << "\n";

    char confirmBooking;
    cout << "Do you want to confirm the booking? (y/n): ";
    cin >> confirmBooking;

    if (confirmBooking == 'y' || confirmBooking == 'Y') {

        cout << "Booking confirmed! Enjoy your trip.\n";
    } else {
        cout << "Booking not confirmed. Have a nice day!\n";
    }

} else {
    cerr << "Error: Edge not found between some locations.\n";
}


    } else {
        cout << "Invalid source location index. Try again.\n";
    }
    break;
}

           case 4: {
                int packageIndex;
                cout << "Enter the index of the package to book: ";
                cin >> packageIndex;

                if (packageIndex >= 0 && packageIndex < packageCount) {
                    cout << "Selected Package:\n";
                    cout << "Package Name: " << packages[packageIndex].name << "\n";
                    cout << "Locations: ";
                    for (int i = 0; packages[packageIndex].locationIndices[i] != -1; ++i) {
                        cout << graph.locations[packages[packageIndex].locationIndices[i]].name << " ";
                    }
                    cout << "\nTotal Cost: " << packages[packageIndex].totalCost << "\n";


                    char confirmation;
                    cout << "Do you want to book this package? (Y/N): ";
                    cin >> confirmation;

                    if (confirmation == 'Y' || confirmation == 'y') {

                        cout << "\nBooking confirmed. Enjoy your trip!\n";
                        cout << "Travel Itinerary:\n";
                        int numLocations = 0;
                        while (packages[packageIndex].locationIndices[numLocations] != -1) {
                            numLocations++;
                        }
                        int numDays = numLocations - 1;
                        cout << "Number of days: " << numDays+1 << "\n";
                        cout << "Travel Plan:\n";
                        cout << "Day 1: Start from '"
                                  << graph.locations[packages[packageIndex].locationIndices[0]].name << "'\n";
                        for (int i = 0; i < numLocations - 1; ++i) {
                            int sourceIndex = packages[packageIndex].locationIndices[i];
                            int destIndex = packages[packageIndex].locationIndices[i + 1];
                            cout << "Day " << i + 2 << ": Travel from '"
                                      << graph.locations[sourceIndex].name << "' to '"
                                      << graph.locations[destIndex].name << "'\n";
                        }
                        cout << "Day " << numDays + 1 << ": Trip ends at '"
                                  << graph.locations[packages[packageIndex].locationIndices[numLocations - 1]].name << "'\n";
                    } else {
                        cout << "Booking canceled.\n";
                    }
                } else {
                    cout << "Invalid package index. Try again.\n";
                }
                break;
            }
            case 5: {
                cout << "Exiting Customer Portal.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}
