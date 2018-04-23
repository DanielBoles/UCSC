/*
    Name: Daniel Boles
    Class: CS109
    Professor: Ira Pohl
    Date 10/30/17
    Assignment: HW3

*/
#include<bits/stdc++.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

# define INF 0x3f3f3f3f
 
// intPair is the name I will use for this Integer Pair
typedef pair<int, int> intPair;
 
// For this graph class I will be using Adjacencly List representation.
class Graph {
    int V;                              // V will be our place holder for No. of vertices.
    list< pair<int, int> > *adj;        // In a weighted graph, we need to store the vertex
                                        // and weight pair for every edge we want to create
public:
    Graph(int V);  // Constructor
    void addEdge(int u, int v, int w);  // Simple function to add an edge to graph with a weight
    void primMST();                     // This will be our function to print the MST using Prim's algorithm
};

// The Graph constructor will allocate memory for adjacency list
Graph::Graph(int V) {
    this->V = V;
    adj = new list<intPair> [V];
}

// This is the same edge function as used for dijkstra's in HW2
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// STL implementation of Prim's algorithm for MST
// Prints shortest paths from source to all other vertices
void Graph::primMST() {
    // Create a priority queue to store vertices to be checked by Prim's algorithm
    priority_queue< intPair, vector <intPair> , greater<intPair> > pq;
    int src = 0;                                        // Start with Vertex 0 as the source of the MST
 
    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INF);
    vector<int> parent(V, -1);                          // Begin by storing parents of the source
    vector<bool> inMST(V, false);                       // helper function to keep track of vertices included in MST
 
    // Insert source in priority queue and initialize its key as 0.
    pq.push(make_pair(0, src));
    key[src] = 0;
 
    // Now the priority queue will loop  until the queue becomes empty
    while (!pq.empty()) {
        // The first vertex in pair is the minimum key vertex, we start with that.
        // The weight is stored in second of pair (it has to be done this way to keep the vertices
        // sorted key (key must be first item in pair)
        int u = pq.top().second;
        pq.pop();
 
        inMST[u] = true;                                // Include this vertex in MST
 
        // This is the designation of the iterator for the intPair
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;                         // Get vertex label and weight of current adjacent of u.
            int weight = (*i).second;
 
            if (inMST[v] == false && key[v] > weight) { //  If v is not in MST and weight of (u,v) is smaller than current key of v
                key[v] = weight;                        // Change to the proper key of v
                pq.push(make_pair(key[v], v));          // store this in the PQ
                parent[v] = u;                          // Now we have the current parent
            }
        }
    } 
    // Now the print function of the MST prints edges sorted by weight from parent array
    cout << "Results of size " << V <<":\n";
    cout << "Parent -> Vertex format" << endl;
    for (int i = 1; i < V; ++i) cout << parent[i] << " -> " << i << endl;
}
 
// Within main I create a simple Minimum Spanning Tree of 10 vertices to run the Prim algorithm.
// Expected result is printed below for the first graph, of 10 vertices. 
// Then I run a second graph of size 100 randomly connected Vertices through Prim 
// and print the results.
int main()
{
    // Construct the 10 Vertex Graph
    int V = 10;
    Graph g(V);
 
    // Now creating the first tree by hand
    g.addEdge(0, 1, 2);
    g.addEdge(0, 7, 8);
    g.addEdge(0, 9, 18);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 3, 15);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 4, 1);
    g.addEdge(2, 7, 3);
    g.addEdge(2, 8, 6);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.addEdge(7, 9, 2);
    g.addEdge(8, 9, 4);
    g.primMST();
    /*  Expected output:Results of Size 10:
                        Parent -> Vertex Format
                        0 -> 1
                        1 -> 2
                        5 -> 3
                        2 -> 4
                        6 -> 5
                        7 -> 6
                        2 -> 7
                        9 -> 8
                        7 -> 9                 */
    
    /*  Here I construct the second MST before randomly connecting.
    This is not a typical way to create an MST but the problem
    I was facing was that I would end up with a lot of unconnected trees
    With non existant parents. I could have worked around this,
    But by following instructions I simply made sure the tree was
    Connected (albeit not fully random) before making more edges.   */
    int V2 = 100;       // Now with 100 vertices
    Graph g2(V2);
    for(int itr = 0; itr < 99; itr++){
        g2.addEdge(itr, itr+1, itr%10);
    }
    
    int vert1, vert2, weight;                       // initialize the vars to be manipulated
    srand(time(NULL));
    for(int i = 0; i < 99; i++){
        vert2 = rand()%99;                          // randomly connect UP the tree since we dont want cycles
        weight = rand()%10;                         // choose a random weight
        if(vert2 <= i){                             // make sure we are connecting forward along the tree (otherwise my prim will fail)
            while(vert2 <= i){
                vert2 = rand()%99;
                vert2++;
            }
        }
        g2.addEdge(i, vert2, weight);               // Add the new random edge
    }
    g2.primMST();                                   
    return 0;
}