/*----------------------graphM.h-----------------------
 Sung Ho Park
 2/5/2020
 -----------------------------------------------------
 Purpose - This is the graphM. This class uses an adjacent
 matrix (method) of graphs. This also mainly is used for
 reading in a text file and finding the shortest path
 from one point to another.
 -----------------------------------------------------
 Used <fstream> for file io and <iostream> for input,
 output.
 -----------------------------------------------------*/

#ifndef graphm_h
#define graphm_h
#include "nodedata.h"
#include <iostream>
#include <fstream>

#include <stdio.h>

using namespace std;

class GraphM
{
public:
    //Constructor
    GraphM();
       
    //builds up graph node information and adjacency matrix of
    //edges between each node reading from a data file.
    void buildGraph(ifstream& infile1);
       
    //insert an edge into graph between two given nodes
    bool insertEdge(int &from, int &to, int &weight);
    
    //Removes an edge into graph between two given nodes
    bool removeEdge(int &from, int &to);
       
    //find the shortest path between every node to every other node in the graph
    void findShortestPath();

    //uses couts to demonstrate that the algorithm works properly
    void displayAll() const;
    
    // display path from a node to another
    void display(const int &from, const int &to) const;
    
    void printPath() const;

private:
    
    //Table is here to keep track of the shortest distance.
    struct TableType
    {
        // whether node has been visited
        bool visited;
        // shortest distance from source known so far
        int dist;
        // previous node in path of min dist
        int path;
    };
    
    //This will remain constant so that an array will exist.
    const static int MAXNODES = 101;
    
    // data for graph nodes
    NodeData data[MAXNODES];
    
    // Cost array, the adjacency matrix
    int C[MAXNODES][MAXNODES];
    
    // number of nodes in the graph
    int size;
    
    // stores visited, distance, path
    TableType T[MAXNODES][MAXNODES];
    
    //Calculates the path taken.
    void printPathRecursion(int &from, int &to) const;
    
    //Displays all the paths took
    void printPathRecursionDisplay(int &from, int &to) const;
    
    //Initializes the arrays.
    void initialize();
    
};
#endif 
