/*
	Name: Daniel Boles
	Class: CS109
	Professor: Ira Pohl
	Date 10/23/17
	Assignment: HW2

*/
#include <iostream>
#include <vector>
#include <list>
#include <iostream>
#include <utility>
#include <ctime>
#include <cstdlib>

using namespace std;
 

int dense (int vert, double density) {									// This function returns the amount of edges based on how dense the user selects
	double dense = density / 100.0;										// I start with the density input and use the conversion of the density calculation
	double edges = vert * (vert-1) * dense;								// Density = 2 * Edges / Vertices(Vertices-1) which I changed to
	edges /= 2;															// Edges = (Vertices(Vertices-1) * Density) / 2 
	return edges;
}

int main() {															// Within main I create the graph. I use adjacency list form and create adoubly linked list																		
    int vertices, range, v1, v2, weight;
    double density, edges;
    
    cout << "Enter the Number of Vertices: ";
    cin >> vertices;

    cout << "\nEnter the desnity of Edges from 1-100 pecent: ";
    cin >> density;

    cout << "\nEnter the max weight range of Edges: ";
    cin >> range;
     
    /* Here I create a vector list for my Adjacency List.
       Each element of the list is a pair<int, int> who's
       pair.first -> the edge's destination
       pair.second -> edge's weight 						*/
    vector< list< pair<int, int> > > adjacencyList(vertices + 1);
    
    edges = dense(vertices, density);									// Here we invoke the function dense to create the edge count based on density %
    
	srand (time(NULL));
    for (int i = 1; i <= edges; ++i) {									// This is the loop that fills the information into the Adj List.
    	int vert1, vert2;												// Randomly selected vertices have an edge between them with a random weight.
    	v1 = rand()%vertices+1;											
    	v2 = rand()%vertices+1;
    	if(v1 == v2) while(v1 == v2) v2 = rand()%vertices+1;			// In order to check there is no self path, I reassign a vertex if it is duplicate.
    	weight = rand()%range+1;   	        
        																// Adding Edge to the Undirected Graph
        adjacencyList[v1].push_back(make_pair(v2, weight));				// Here the doubly linked list creates a path between v1 and v2 and the select weight.
        adjacencyList[v2].push_back(make_pair(v1, weight));				// V2 also links back to v1 at the same weight since it is undirected.
    }
     
    cout << "\nThe Adjacency List-\n";                                  // Now we print out the adjacencyList;
    for (int i = 1; i < adjacencyList.size(); ++i) {
        cout <<"Vertex[" << i << "]";
         
        list< pair<int, int> >::iterator itr = adjacencyList[i].begin();
         
        while (itr != adjacencyList[i].end()) {
            cout << " -> " << (*itr).first << "(" << (*itr).second << ")";
            ++itr;
        }
        printf("\n");
    }
    //list< pair<int, int> >::iterator itr2 = adjacencyList[1].begin();
    //cout << "vert 1 value in pair:" << (*itr2).first;
    return 0;
}
