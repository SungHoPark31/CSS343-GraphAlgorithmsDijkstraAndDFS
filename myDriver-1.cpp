/*----------------------Driver-----------------------
Sung Ho Park
2/12/2020
-----------------------------------------------------
Purpose - This is the driver file. This tests both the
adjacency matrix using Dijkstra's shortest path and the
adjacency list using Depth-First Search.
-----------------------------------------------------
Used <fstream> for file io and <iostream> for input,
output.
-----------------------------------------------------*/


#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"

using namespace std;

int main()
{
    // part 1
    ifstream infile1("myInput.txt");
    if (!infile1)
    {
        cout << "File could not be opened." << endl;
        return 1;
    }

    //for each graph, find the shortest path from every node to all other nodes
    for (;;)
    {
        GraphM G;
        G.buildGraph(infile1);
        if (infile1.eof())
            break;

        G.findShortestPath();
         G.displayAll();              // display shortest distance, path to cout
        G.display(3, 1);              // display path from node 3 to 1 to cout
        G.display(1, 2);
        G.display(1, 4);
        G.display(2, 6);
        G.display(5, 3);
        G.display(6, 7);
        G.display(7, 4);
        G.display(7, 6);
    }
    
    // part 2
    ifstream infile2("myInput2.txt");
    if (!infile2) {
        cout << "File could not be opened." << endl;
        return 1;
    }

    //for each graph, find the depth-first search ordering
    for (;;)
    {
        GraphL G;
        G.buildGraph(infile2);
        if (infile2.eof())
            break;
        G.displayGraph();
        G.depthFirstSearch();    // find and display depth-first ordering to cout
    }
    
//    cout << endl;
    return 0;
}
