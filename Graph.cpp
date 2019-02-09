/*********************************************************************************************/
/* Programmer: Inna Yedzinovich                                                              */
/* Date: 12/07/2017                                                                          */
/* Purpose: There is an implementation file for the graph class                              */
/* Professor: Anna Salvati                                                                   */
/*********************************************************************************************/
#include "Graph.h"

/*************************FUNCTIONS IMPLEMENTATION********************************************/
template <class T>
Graph<T>::Graph() {

    numVertices = 0;
    numEdges = 0;

}

template <class T>
Graph<T>::~Graph() {

    deleteGraph();
}

template <class T>
Graph<T>::Graph(const Graph<T> &other) {

    copy(other.adjacencyList.begin(), other.adjacencyList.end(), back_inserter(this->adjacencyList));
    copy(other.vertexContainer.begin(), other.vertexContainer.end(), back_inserter(this->vertexContainer));

    numVertices = other.numVertices;
    numEdges = other.numEdges;
}

template <class T>
Graph<T>& Graph<T>::operator=(const Graph<T> &other) {

    if(!isEmpty())
        deleteGraph();

    copy(other.adjacencyList.begin(), other.adjacencyList.end(), back_inserter(this->adjacencyList));
    copy(other.vertexContainer.begin(), other.vertexContainer.end(), back_inserter(this->vertexContainer));

    numVertices = other.numVertices;
    numEdges = other.numEdges;

    return *this;

}

template <class T>
void Graph<T>::deleteGraph() {

    if(!isEmpty()){

        for (int i = 0; i < adjacencyList.size(); i++)
                adjacencyList[i].clear();

        numEdges = 0;
        numVertices = 0;

    }

}

template <class T>
bool Graph<T>::isEmpty() {

    return adjacencyList.empty();
}

template <class T>
void Graph<T>::addVertex(T vertex) {

    if(!isVertex(vertex)) {
        vertexContainer.push_back(vertex);
        adjacencyList.resize(vertexContainer.size());
        numVertices++;
    }
}

template <class T>
int Graph<T>::returnIndex(T vertex) {

    for(int i = 0;i < vertexContainer.size();i++)
        if(vertexContainer[i]==vertex)
            return i;
    return -1;

}

template <class T>
void Graph<T>::addEdge(T first, T second) {

    int idx = returnIndex(first);
    int idx1 = returnIndex(second);

    if(first == second){
        std::cout<<"Edge cannot be added to itself"<<std::endl;
        return;
    }

    if(idx == -1||idx1 == -1)
        std::cout<<"Edge between "<<first<<" and "<<second<< " cannot be added"<<std::endl;

    else if(isEdge(first,second))
        std::cout<<"Edge already exist"<<std::endl;

    else{
        Edge<T> e;
        e.vertex = second;
        adjacencyList[idx].push_back(e);

        e.vertex = first;
        adjacencyList[idx1].push_back(e);

        numEdges++;
    }

}

template <class T>
void Graph<T>::deleteVertex(T item) {     //check

    int idx = returnIndex(item);

    if(idx != -1) {

        vertexContainer.erase(vertexContainer.begin() + idx);

        //for some reason the compiler doesn't work without assigning iterator in this func
        for (int i = 0; i < adjacencyList.size(); i++){
            for (iterator = adjacencyList[i].begin(); iterator != adjacencyList[i].end();) {
                if(i == idx)
                    iterator = adjacencyList[idx].erase(iterator);  //iterator points to the next node
                else if (iterator->vertex == item)
                    iterator = adjacencyList[i].erase(iterator);    //iterator points to the next node
                else
                    iterator++;   //increment iterator if both conditions are false

            }
        }
        adjacencyList.erase(adjacencyList.begin()+idx);

        numVertices--;
    }
    else
        std::cout<<"Vertex does not exist" <<std::endl;

}

template <class T>
void Graph<T>::deleteEdge(T first, T second) {

    int idx = returnIndex(first);
    int idx1 = returnIndex(second);

    if(idx != -1 && idx1 != -1) {

            for (iterator = adjacencyList[idx].begin(); iterator != adjacencyList[idx].end(); iterator++) {
                if (iterator->vertex == second) {
                    adjacencyList[idx].erase(iterator);
                        break;
                }
            }

            for (iterator = adjacencyList[idx1].begin(); iterator != adjacencyList[idx1].end(); iterator++) {
                if (iterator->vertex == first) {
                    adjacencyList[idx1].erase(iterator);
                        break;
                }
            }
        numEdges-=2;
    }
    else
        std::cout<<"Edge does not exist"<<std::endl;
}

template <class T>
void Graph<T>::printVertices() {

    for(int i = 0;i < vertexContainer.size();i++)
        std::cout<<vertexContainer[i]<<"\n";
    std::cout<<"------------------------------"<<std::endl;
}

template <class T>
void Graph<T>::addWeight(T first, T second, int weight) {


    if(isEdge(first, second)){

        int idx = returnIndex(first);
        int idx1 = returnIndex(second);

        for (iterator = adjacencyList[idx].begin(); iterator != adjacencyList[idx].end(); iterator++){

            if(iterator->vertex == second){
                iterator->weight = weight;
                break;
            }
        }

        for (iterator = adjacencyList[idx1].begin(); iterator != adjacencyList[idx1].end(); iterator++){

            if(iterator->vertex == first){
                iterator->weight = weight;
                break;
            }
        }
    }
    else
        std::cout<<"Weight between "<<first<<" and "<<second<< " cannot be added\n";
}

template <class T>
void Graph<T>::addEdgeAndWeight(T first, T second, int weight) {

    if(isEdge(first, second)) {
        std::cout << "Edge is already exist. Would you like to change weight? (Y/N)";
        char choice;
        std::cin >> choice;

        if(choice == 'Y')
            addWeight(first,second,weight);
        else return;
    }
    else {
        addEdge(first, second);
        addWeight(first, second, weight);
    }

}

template <class T>
void Graph<T>::printEdges(T item) {

    int idx = returnIndex(item);

    if(idx != -1) {

        if(adjacencyList[idx].size() == 0)
            std::cout<<"Vertex doesn't have edges\n";

        for (iterator = adjacencyList[idx].begin(); iterator != adjacencyList[idx].end(); iterator++)
            std::cout<<iterator->vertex<<"\n";
        std::cout<<std::endl;

    }
    else
        std::cout<<"Edge doesn't exist\n";

}

template <class T>
bool Graph<T>::isEdge(T first, T second) {

    int idx = returnIndex(first);

    if(idx != -1 && returnIndex(second)!= -1) {
        for (iterator = adjacencyList[idx].begin(); iterator != adjacencyList[idx].end(); iterator++) {
            if (iterator->vertex == second)
                return true;
        }
    }
    return false;
}

template <class T>
bool Graph<T>::isVertex(T vertex) {

    for (int i = 0; i < vertexContainer.size(); ++i)
        if(vertexContainer[i] == vertex)
            return true;

    return false;
}

template <class T>
bool Graph<T>::isVisited(T vertex) {

    int idx = returnIndex(vertex);

    return visited[idx];
}

template <class T>
void Graph<T>::resetVisited() {

    visited.resize(vertexContainer.size());

    for (int i = 0; i < visited.size() ; ++i) {
        visited[i] = false;
    }

}

template <class T>
void Graph<T>::switchVisited(T vertex) {

    int idx = returnIndex(vertex);

    if(!visited[idx])
       visited[idx] = true;
    else
       visited[idx] = false;

}

template <class T>
void Graph<T>::getEdges(std::queue<T>& q, T vertex) {

    int idx = returnIndex(vertex);
    for (iterator = adjacencyList[idx].begin(); iterator != adjacencyList[idx].end(); iterator++){
        q.push(iterator->vertex);
    }

}

template <class T>
int Graph<T>::getWeight(T first, T second) {

    if(isEdge(first,second)){

        int idx = returnIndex(first);

        for (iterator = adjacencyList[idx].begin(); iterator != adjacencyList[idx].end(); iterator++)
            if(iterator->vertex == second)
                    return iterator->weight;
    }

    else return -1;

}

template <class T>
int Graph<T>::numOfVertices() {

    return vertexContainer.size();
}

template <class T>
T Graph<T>::getVertexByIndex(int idx) {

    return vertexContainer[idx];

}

template <class T>
void Graph<T>::switchVisitedIdx(int idx) {

    if(visited[idx])
        visited[idx] = false;
    else
        visited[idx] = true;

}

template <class T>
bool Graph<T>::isVisitedIdx(int idx) {
    return visited[idx];
}

template <class T>
int Graph<T>::getWeightIgnoreEdge(T first, T second) {

    int idx = returnIndex(first);

    for (iterator = adjacencyList[idx].begin(); iterator != adjacencyList[idx].end(); iterator++)
        if(iterator->vertex == second)
            return iterator->weight;

}