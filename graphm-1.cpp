/*----------------------graphM.cpp-----------------------
Sung Ho Park
2/5/2020
-----------------------------------------------------
Purpose - This is the graphM. This class uses an adjacent
matrix (method) of graphs. This also mainly is used for
reading in a text file and finding the shortest path
from one point to another. This is the file where it carries
all the implementation for each class in the header file.
-----------------------------------------------------
Used <fstream> for file io and <iostream> for input,
output. <sstream> is used for converting string to ints,
<string> is used for string and <cmath> is used for basic
arithmetic like min and max.
-----------------------------------------------------*/

#include "graphm.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*--------------------Constructor----------------------
 Description:
 Among others that need to be initialized, the data member
 T is initialized to sets all dist to infinity, sets all
 visited to false, and sets all path to 0.
 
 Preconditions: None
 Postconditions: Initializes TableType to 0 and every
 private membor to 0 or false, or null.
 ------------------------------------------------------*/
GraphM::GraphM()
{
    //Set the size to 0.
    size = 0;
    
    //Initialize every data tables to null, or 0.
    for(int i = 0; i < MAXNODES; i++)
    {
        //This is only for the cost and adjacency matrix. 
        for(int j = 0; j < MAXNODES; j++)
        {
            //Set the adjacency matrix graph to "infinity" which
            //will be -1 in this case.
            C[i][j] = 0;
            
            //Set every TableType to false, and 0.
            T[i][j].visited = false;
            T[i][j].path = 0;
            T[i][j].dist = 0;
        }
    }
}
//End of Default Constructor.

/*--------------------buildGraph----------------------
Description:
builds up graph node information and adjacency matrix
f edges between each node reading from a data file.

Preconditions: infile1 is created and can be opened.
Postconditions: Builds graph node and adjacency matrix
------------------------------------------------------*/
void GraphM::buildGraph(ifstream& infile1)
{
    string line;
    //Input the size of the different arrays.
    infile1 >> size;
    
    //Get the first line out of the way.
    getline(infile1, line);
    
    //a text description of each of the 1 through n nodes
    //This is the locations that you have.
    for(int i = 1; i <= size; i++)
    {
        //Get the line.
        getline(infile1, line);
        
        //Put the line inside of NodeData's private string data.
        NodeData insertData(line);
        
        //Put that NodeData object inside of the array of NodeData.
        data[i] = line;
    }
    
    //while the line is not 0 0 0
    while(line != "0 0 0/r")
    {
        //Get the next line: It should contain 3 integers.
        getline(infile1, line);
        
        //Take this line and split it
        istringstream ss(line);
        
        //Have string variables for convertion
        string sFrom;
        string sTo;
        string sWeight;
    
        //Get each string numbers from each line.
        ss >> sFrom;
        ss >> sTo;
        ss >> sWeight;
        
        if(sFrom == "0" || sFrom == "")
            break;
        //Convert the string to numbers
        else
        {
            int iFrom = stoi(sFrom);
            int iTo = stoi(sTo);
            int iWeight = stoi(sWeight);
        
            //insert edge
            insertEdge(iFrom, iTo, iWeight);
        }
    }
    //If you reached the end of the file, then close it.
    if(infile1.eof())
    {
        infile1.close();
        return;
    }
}
//End of buldgraph

/*--------------------insertEdge----------------------
Description:
Inserts an edge in the Cost Table.

Preconditions: All of those integers are real numbers.
Postconditions: Puts the edge into the adjacency matrix
at a specific place.
------------------------------------------------------*/
bool GraphM::insertEdge(int &from, int &to, int &weight)
{
    //If both from and to are 0, then don't add it.
    if(from == 0 || to == 0)
    {
        return false;
    }
    //If they are the same, don't add it
    else if(from == to)
    {
        return false;
    }
    else
    {
        //Otherwise, add them
        C[from][to] = weight;
        return true;
    }
}
//End of insertEdge

/*--------------------removeEdge----------------------
Description:
Removes the edge between nodes in the adjacency matrix

Preconditions: All of those integers are real numbers.
Postconditions: Sets cost adjacency at from and to to
zero, removing the weight.
------------------------------------------------------*/
bool GraphM::removeEdge(int &from, int &to)
{
    C[from][to] = 0;
    return true;
}
//End of removeEdge

/*----------------findShortestPath----------------------
Description:
Uses Dijkstra's algorithm to find the shortest path from
the source to destinaiton

Preconditions: NONE
Postconditions: Finds the shortest path, from the source
to the destination.
------------------------------------------------------*/
void GraphM::findShortestPath()
{
    //Initialize the cost array to the T[][] array.
    initialize();
    
    //Start at the beginning.
    for(int i = 1; i <= size; i++)
    {
         // finds the shortest distance from source to all other nodes
         for (int j = 1; j <= size; j++)
         {
             //Goes through the T array so that way we
             //know which
             if(T[i][j].dist != 0)
             {
                 //For each w adjacent to v
                 for(int w = 1; w <= size; w++)
                 {
                     //This is looking at the column (meaning adjacency)
                     //If the table's distance added by the distance of the column's
                     //adjacent distances (compare up and down) is less than the
                     //distance on top, then update it.
                     if(T[w][i].dist != 0 && ((T[w][j].dist > T[w][i].dist + T[i][j].dist)
                                              || T[w][j].dist == 0))
                     {
                         T[w][j].dist = T[w][i].dist + T[i][j].dist;
                         T[w][j].path = T[i][j].path;
                     }
                     
                 }
             }
         }
    }
}
//End of FindShortestPath

/*---------------initialize----------------
 Description:
 Initialize the cost array to the T[][] array.
 
 Precondition: NONE
 Postcondition: Initializes the cost array to
 the T[][] array.
 ------------------------------------------*/
void GraphM::initialize()
{
    //Set everything in the table's distance to Cost weights.
    for(int i = 1; i <= size; i++)
    {
        for(int j = 1; j <= size; j++)
        {
            T[i][j].dist = C[i][j];
            
            //If the cost weight is 0, dont add it to the
            //path
            if(C[i][j] != 0)
            {
                T[i][j].path = i;
            }
        }
    }
}
//End of initialize

/*-------------printPathRecursion----------------
Description:
Recursively goes through all the paths.

Precondition: The integers passed in are real numbers
Postcondition: Recursively goes through all the paths
only prints out the middle paths.
-----------------------------------------------*/
void GraphM::printPathRecursion(int &from, int &to) const
{
    //If the path is the original source, then return.
    if(T[from][to].path == from)
    {
        return;
    }
    //If the path is zero, do nothing.
    else if(T[from][to].path == 0)
    {
        return;
    }
    else
    {
        //Recurse through the paths
        int thePath = T[from][to].path;
        printPathRecursion(from, thePath);
        cout << thePath << " ";
    }
}
//End of printPathRecursion.

/*-------------printPathRecursion----------------
Description:
Recursively goes through all the paths. Does the
same thing but recurses through the location.

Precondition: The integers passed in are real numbers
Postcondition: Recursively goes through all the paths
only prints out the middle paths. Does the same thing
but recurses through the location paths.
-----------------------------------------------*/
void GraphM::printPathRecursionDisplay(int &from, int &to) const
{
    //Print out the original
    if(T[from][to].path == from)
    {
        return;
    }
    else if(T[from][to].path == 0)
    {
        return;
    }
    else
    {
        int thePath = T[from][to].path;
        printPathRecursionDisplay(from, thePath);
        cout << data[thePath] << endl;
    }
}
//End of printpathRecursionDisplay

/*---------------------displayAll----------------------
Description:
Uses couts to demonstrate that the algorithm works properly.
Uses couts to display the shortest distance with path info
between every node.

Preconditions: NONE
Postconditions: Demonstrates the algorithm works properly.
------------------------------------------------------*/
void GraphM::displayAll() const
{
    cout << "Description" << "\t\t" << "From_Node" << '\t'
                        << "To_Node" << "\t\t" << "Dijkstra's Path" << endl;
    
    //Go through the data that corresponds with the cost.
    for(int i = 1; i <= size; i++)
    {
        //Display the string nodedata, which is the location.
        cout << data[i] << endl;
        
        //Go though every possible path in the adjacency matrix and
        //print out the contents.
        for(int j = 1; j <= size; j++)
        {
            //If j and i are equal...
            if(j == i)
            {
                //Do nothing, skip it.
            }
            else
            {
                //Otherwise, print out the contents
                cout << "\t\t\t\t" << i << "\t\t\t" << j <<
                                                            "\t\t\t";
                if(T[i][j].dist == 0)
                {
                    cout << "----" << "\t\t";
                }
                else
                {
                    cout << T[i][j].dist << "\t\t";
                }
                
                //Print out the path.
                if(i != j && T[i][j].path != 0)
                {
                    //Print out the first one.
                    cout << i << " ";

                    //Print the ones inbetween
                    printPathRecursion(i, j);

                    //Print out the end.
                    cout << j << endl;
                }
                else
                {
                    //Otherwise, print out nothing
                    cout << endl;
                }
            }
        }
    }
}
//End of displayAll

/*---------------------display----------------------
Description:
Uses couts to display the shortest distance with path
info between the fromNode to toNode.

Preconditions: the int's are real numbers.
Postconditions: Displays the shortest distance fromNode
to toNode.
------------------------------------------------------*/
void GraphM::display(const int &from, const int &to) const
{
    cout << from << "\t" << to << "\t";
    
    if(T[from][to].dist == 0)
    {
        cout << "-----" << endl;
    }
    else
    {
        //print out the distance
        cout << T[from][to].dist << "\t";
        
        //Make this into variables because printPathRecursion
        //needs a variable that is not const.
        int fromA = from;
        int toA = to;
        cout << from << " ";
        printPathRecursion(fromA, toA);
        cout << to << endl;
        
        //Print out the displayed paths took.
        cout << data[from] << endl;
        printPathRecursionDisplay(fromA, toA);
        cout << data[to] << endl;
    }
    cout << endl;
}
//End of display
