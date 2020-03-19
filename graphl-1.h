/*----------------------graphL.h-----------------------
Sung Ho Park
2/5/2020
-----------------------------------------------------
Purpose - This is the graphL. This class uses an adjacent
list (method) of graphs. This also mainly is used for
reading in a text file and finding the Depth First
Search
-----------------------------------------------------
Used <fstream> for file io and <iostream> for input,
output.
-----------------------------------------------------*/

#ifndef grapgl_h
#define grapgl_h

#include "nodedata.h"
#include <iostream>
#include <fstream>

#include <stdio.h>

using namespace std;

class GraphL
{

public:
    //Constructor
    GraphL();
    
    //Destructor
    ~GraphL();
          
    //builds up graph node information and adjacency matrix of
    //edges between each node reading from a data file.
    void buildGraph(ifstream& infile1);
    
    void depthFirstSearch();

    //uses couts to demonstrate that the algorithm works properly
    void displayGraph() const;
    
    //Adds in the edge.
    void addEdge(int &from, int &edge);
    
private:
    //forward reference for the compiler
    struct EdgeNode;
    
    //structs used for simplicity, use classes if desired
    struct GraphNode
    {
        // head of the list of edges
        EdgeNode* edgeHead;

        // data information about each node
        NodeData* data;

        bool visited;
    };

    struct EdgeNode
    {
        // subscript of the adjacent graph node
        int adjGraphNode;

        //Have a next edge
        EdgeNode* nextEdge;
        
        //Keep track of the previous,
        //EdgeNode* prevEdge;
    };
    
    void DFSHelper(GraphNode** graph, int from);
    
    //This will remain constant so that an array will exist.
    const static int MAXNODES = 101;
    
    //Array of GraphNodes
    GraphNode* dfsGraph[MAXNODES];

    // number of nodes in the graph
    int size;
};
#endif 
