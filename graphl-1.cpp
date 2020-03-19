/*----------------------graphL.cpp-----------------------
Sung Ho Park
2/5/2020
-----------------------------------------------------
Purpose - This is the graphL. This class uses an adjacent
list (method) of graphs. This also mainly is used for
reading in a text file and finding the Depth First
Search. This is the file where it carries all the
implementation for each class in the header file.
-----------------------------------------------------
Used <fstream> for file io and <iostream> for input,
output. <sstream> is used for converting string to ints,
<string> is used for string and <cmath> is used for basic
arithmetic like min and max.
-----------------------------------------------------*/

#include "graphl.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*--------------------Constructor----------------------
Description:
Initializes the array of graphs to nullptr.

Preconditions: None
Postconditions:Initializes the array of graphs to nullptr.
------------------------------------------------------*/
GraphL::GraphL()
{
    size = 0;
    //Initialize everything in the graph.
    for(int i = 0; i < MAXNODES; i++)
    {
        dfsGraph[i] = new GraphNode;
        dfsGraph[i]->edgeHead = nullptr;
        dfsGraph[i]->data = nullptr;
        dfsGraph[i]->visited = false;
    }
}
//End of Constructor

/*--------------------Destructor----------------------
Description:
Destroys everything. The edgeNodes and the GraphNodes.

Preconditions: None
Postconditions: Destroys everything.
------------------------------------------------------*/
GraphL::~GraphL()
{
    //Destroy everything.
    for(int i = MAXNODES - 1; i >= 0; i--)
    {
        if(dfsGraph[i]->edgeHead == nullptr)
        {
            delete dfsGraph[i]->edgeHead;
            
            delete dfsGraph[i]->data;
            delete dfsGraph[i];
        }
        else
        {
            while(dfsGraph[i]->edgeHead != nullptr)
            {
                EdgeNode* next = dfsGraph[i]->edgeHead->nextEdge;
                delete dfsGraph[i]->edgeHead;
                dfsGraph[i]->edgeHead = next;
            }
            delete dfsGraph[i]->edgeHead;
            delete dfsGraph[i]->data;
            delete dfsGraph[i];
        }
        
    }
}
//End of Destructor

/*--------------------buildGraph----------------------
Description:
Builds the graph, using the adjacent list.

Preconditions: The infile parameter exists and it successfully
reads.
Postconditions: Builds an adjacent list.
------------------------------------------------------*/
void GraphL::buildGraph(ifstream& infile1)
{
    string line;
    //Set the size
    infile1 >> size;
    
    //Get the first line after
    getline(infile1, line);
    
    //Set the NodeData to the array Node Data
    for(int i = 1; i <= size; i++)
    {
        //Get the first line of string.
        getline(infile1, line);
        
        //Set the data of NodeData to the location.
        //NodeData location(line);
        NodeData* location = new NodeData;
        *location = line;
        
        //Put the location in the NodeData inside graphNode
        dfsGraph[i]->data = location;
    }
    
    //while the line is not 0 0 
    while(line != "0 0/r")
    {
        //Get the next line: It should contain 2 integers.
        getline(infile1, line);
           
        //Take this line and split it
        istringstream ss(line);
           
        //Have string variables for convertion
        string sFrom;
        string sTo;
        
        //Get each string numbers from each line.
        ss >> sFrom;
        ss >> sTo;
           
        //If from is zero, exit it.
        if(sFrom == "0" || sFrom == "")
            break;
        
        //Convert the string to numbers
        
            int iFrom = stoi(sFrom);
            int iTo = stoi(sTo);
            
            //Add that edge to the array at that spot.
            addEdge(iFrom, iTo);
        
    }
    //If you reached the end of the file, then close it.
    if(infile1.eof())
    {
        infile1.close();
        return;
    }
}
//End of buildGraph

/*--------------------addEdge----------------------
Description:
Adds in a new edge at the beginning of the list.
 
Preconditions: The two integers passed in exist and are
not null.
Postconditions: Successfully inserts a new edge to the
array of graphs.
------------------------------------------------------*/
void GraphL::addEdge(int &from, int &edge)
{
    //Make a new Node and set the data.
    EdgeNode* node = new EdgeNode();
    node->adjGraphNode = edge;

    //Make this new node the head, inserting it to
    //the beginning of the list.
    node->nextEdge = dfsGraph[from]->edgeHead;
    dfsGraph[from]->edgeHead = node;
}
//End of AddEdge

/*--------------------displayGraph----------------------
Description:
Prints out each node and their adjacent GraphNodes.

Preconditions: None
Postconditions: Prints out each node and their adjacent
GraphNodes.
------------------------------------------------------*/
void GraphL::displayGraph() const
{
    //Displays the graph
    cout << "Graph: " << endl;
    
    //Go through each GraphNode object.
    for(int i = 1; i <= size; i++)
    {
        //Make a temporary head.
        EdgeNode* current = dfsGraph[i]->edgeHead;
        //Nodes.
        cout << "Node" << i << "\t\t" << *dfsGraph[i]->data << endl;
    
        while(current != nullptr)
        {
            cout << "\tEdge" << "\t" << i << " " <<
            current->adjGraphNode << endl;
            current = current->nextEdge;
        }
        cout << endl;
    }
}
//End of displayGraph

/*----------------depthFirstSearch------------------
Description:
Calculates and prints out the depth first search.

Preconditions: None
Postconditions: Calculates and prints out the depth first
search.
------------------------------------------------------*/
void GraphL::depthFirstSearch() 
{
    //It'll always start at 1.
    cout << "Depth-First Ordering: ";
    
    //For each, graph node, find the dfs.
    for(int i = 1; i <= size; i++)
    {
        //Check if it is visited. If not, call the recursion.
        if(dfsGraph[i]->visited == false)
        {
            DFSHelper(dfsGraph, i);
        }
    }
    cout << endl;
}
//End of depthFirstSearch

/*----------------DFSHelper------------------------
Description:
Calculates and prints out the depth first search.
Helper and uses recursion to figure out the DFS.

Preconditions: None
Postconditions: Calculates and prints out the depth first
search.
------------------------------------------------------*/
void GraphL::DFSHelper(GraphNode** graph, int from)
{
    //Print out where you came from.
    cout << from << " ";
    //Make a temporary edge head
    EdgeNode* temp = graph[from]->edgeHead;
    
    //Mark here as true
    graph[from]->visited = true;
    
    //While the temphead is not null...
    while(temp != nullptr)
    {
        //Check if the adjacent Node is visited.
        int startFrom = temp->adjGraphNode;
        if(graph[startFrom]->visited == false)
        {
            //If it is not, recurse through and go there.
            DFSHelper(graph, startFrom);
        }
        //Go next.
        temp = temp->nextEdge;
    }
}
//End of DFS helper.

