/***********************************************************************************************/
/* Programmer: Inna Yedzinovich                                                                */
/* Date: 12/07/2017                                                                            */
/* Purpose: This class creates and implements a connected, undirected, weighted graph.         */
/*          Assumptions: vertex is template, weight is an integer.                             */
/* Professor: Anna Salvati                                                                     */
/***********************************************************************************************/

#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <iterator>
#include <algorithm>
#include <climits>

//Structure that holds vertex and weight
template <class T>
struct Edge{
    T vertex;
    int weight = INT_MAX;
};

template <class T>
class Graph {

protected:
    int numVertices;                                //Int variable contains a number of vertices
    int numEdges;                                   //Int variable contains a number of edges

    std::vector<bool> visited ;                     //boolean vector to mark either vertex was visited or not
    std::vector<std::list<Edge<T> > > adjacencyList;  //adjacency list
    std::vector<T> vertexContainer;                 //vector of all vertices
    typename std::list<Edge<T>>::iterator iterator; //iterator

    void addEdge(T, T);                             //function to add the edge between two vertices
    void addWeight(T, T, int);                      //function to add weight between two vertices

public:

    Graph();                                        //constructor
    ~Graph();                                       //destructor
    Graph(const Graph<T>&);                         //copy constructor
    void deleteGraph();                             //function to delete the graph
    Graph<T>& operator =(const Graph<T>&);          //overloaded = operator

    void addVertex(T);                              //function to add vertex to the graph
    void addEdgeAndWeight(T, T, int);               //function to add edge and weight between vertices

    void printVertices();                           //function to print all vertices
    void printEdges(T);                             //function to print all edges for a given vertex

    bool isEdge(T, T);                              //bool function checks if there is an edge between two vertices
    bool isVertex(T);                               //bool function checks of vertex exists
    bool isEmpty();                                 //bool function checks if graph if empty
    bool isVisited(T);                              //bool function checks if vertex has been visited by vertex
    bool isVisitedIdx(int);                         //bool function checks if vertex has been visited by index

    void deleteVertex(T);                           //function to delete vertex
    void deleteEdge(T, T);                          //function to delete the edge between two vertices

    int returnIndex(T);                             //int function returns an index of the vertex
    void resetVisited();                            //function resets all visited to false
    void switchVisited(T);                          //function switches visited if true makes false if false makes true
    int numOfVertices();                            //int function returns number of vertices
    void switchVisitedIdx(int);                     //function switches visited vertex by index

    void getEdges(std::queue<T>&, T);               //function stores all edges in a queue
    int getWeight(T, T);                            //returns weight of the edge (if exists), or -1 if weight was not assigned.
    T getVertexByIndex(int);                        //T function returns vertex by index

    int getWeightIgnoreEdge(T, T);                  //int function returns weight without checking if edge
                                                    // between two vertices exists

};


#endif
