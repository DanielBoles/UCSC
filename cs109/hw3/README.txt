Name: Daniel Boles
Email: dawboles@ucsc.edu
Assignment: CS109 HW3
Collaboration: None
Time Spent: 5hrs

Within this assignment I created a graph using adjacency list representation, similar to the Dijkstra
assignment from last week. This graph is created by pairs of vertices and their weighted edges. I run 
through a priority queue in my implementation of the Prim algorithm. The Minimum Spanning Tree is 
printed as a result in the output. The first graph is the set of 10 vertices I hand connected. The 
expected out put is below. The second graph is a set of 100 vertices randomly connected with random 
weight. The second graph took me some time to fully get functioning as I had a problem when the graph 
was randomly unconnected. The result would output the default parent as -1 for all the nodes after 
popping all the way down the queue to find the parent unsuccessfully.

Thanks.

expected output -
			Results of Size 10:
                        Parent -> Vertex Format
                        0 -> 1
                        1 -> 2
                        5 -> 3
                        2 -> 4
                        6 -> 5
                        7 -> 6
                        2 -> 7
                        9 -> 8
                        7 -> 9                