/************************************************************************************************/
/* Programmer: Inna Yedzinovich                                                                 */
/* Date: 12/07/2017                                                                             */
/* Purpose: The main function                                                                   */
/************************************************************************************************/
#include "Graph.cpp"
#include <cmath>
#include <climits>


//DFS algorithm function
void DepthFirstSearch(Graph<std::string>& graph, std::string vertex);

//BFS algorithm function
void BreadthFirstSearch(Graph<std::string>& graph, std::string vertex);

//function finds the shortest path from given vertex
void ShortestPath(Graph<std::string> graph, std::string vertex);

//help function for BFS recursion
void BreadthFirstSearchRec(Graph<std::string>& graph, std::string vertex, std::queue<std::string>& queue);

//help function for DFS recursion
void DepthFirstSearchRec(Graph<std::string>& graph, std::string vertex);

//function that implements a menu
void menu(Graph<std::string> &graph);


int main(){

    Graph<std::string> graph;
    menu(graph);
    return 0;
}

void DepthFirstSearch(Graph<std::string>& graph, std::string vertex){

    if(!graph.isEmpty()) {

        if (graph.isVertex(vertex)) {
            graph.resetVisited();
            DepthFirstSearchRec(graph, vertex);
        } else
            std::cout << "Vertex does not exist\n";
    }
    else std::cout<<"Graph is empty\n";

}

/************************************FUNCTIONS IMPLEMENTATION********************************************/

void DepthFirstSearchRec(Graph<std::string>& graph, std::string vertex){

    graph.switchVisited(vertex);
    std::cout<<vertex<<"\n";

    std::queue<std::string> queue;
    graph.getEdges(queue, vertex);

    while(!queue.empty()) {
        if (!graph.isVisited(queue.front()))
            DepthFirstSearchRec(graph, queue.front());
        queue.pop();
    }
}

void BreadthFirstSearch(Graph<std::string>& graph, std::string vertex){

    if(!graph.isEmpty()) {

        if (graph.isVertex(vertex)) {
            graph.resetVisited();
            std::queue<std::string> queue;
            queue.push(vertex);

            BreadthFirstSearchRec(graph, vertex, queue);
        } else
            std::cout << "Vertex does not exist\n";
    }
    else std::cout<<"Graph is empty\n";

}

void BreadthFirstSearchRec(Graph<std::string>& graph, std::string vertex, std::queue<std::string>& queue){

    if(!queue.empty()){

        graph.switchVisited(vertex);
        std::cout<<vertex<<"\n";
        queue.pop();

        std::queue<std::string> tempQueue;
        graph.getEdges(tempQueue, vertex);

        while(!tempQueue.empty()) {
            if (!graph.isVisited(tempQueue.front())) {
                std::string data;
                data = tempQueue.front();
                queue.push(data);
            }
            tempQueue.pop();
        }

        if(!queue.empty())   //as we pop the queue and want to make sure that something left in a queue
            BreadthFirstSearchRec(graph, queue.front(), queue);
    }

}

void ShortestPath(Graph<std::string> graph, std::string vertex){

    if(graph.isVertex(vertex)) {

        std::vector<int> cost(graph.numOfVertices());

        for (int i = 0; i < cost.size(); ++i)
            cost[i] = INT_MAX;

        graph.resetVisited();
        graph.switchVisited(vertex);

        cost[graph.returnIndex(vertex)] = 0;

        std::queue<std::string> edges;
        graph.getEdges(edges, vertex);

        while (!edges.empty()){
            cost[graph.returnIndex(edges.front())] = graph.getWeight(vertex, edges.front());
            edges.pop();
        }

        for (int index = 1; index < cost.size() ; ++index) {

            int min_idx;
            for (min_idx = 0; min_idx < cost.size() ; ++min_idx) {
                if(!graph.isVisitedIdx(min_idx))
                    break;
            }

            for (int i = 0; i < cost.size(); ++i) {
                if(cost[i]< cost[min_idx]&&!graph.isVisitedIdx(i))
                    min_idx = i;
            }

            graph.switchVisitedIdx(min_idx);

            for (int w = 0; w < cost.size() ; ++w) {

               if(!graph.isVisitedIdx(w)&&cost[w] > cost[min_idx]+graph.getWeightIgnoreEdge(graph.getVertexByIndex(min_idx), graph.getVertexByIndex(w)))
                    cost[w] = cost[min_idx]+graph.getWeightIgnoreEdge(graph.getVertexByIndex(min_idx), graph.getVertexByIndex(w));

            }
        }


        std::cout<<"The shortest paths from "<< vertex<<" are: \n";
        for (int l = 0; l < cost.size(); ++l) {
            std::cout<<graph.getVertexByIndex(l)<<" : "<<cost[l]<<std::endl;
        }


    }
    else
        std::cout<<"Vertex does not exist\n";


}

void menu(Graph<std::string> &graph){
    std::cout<<"WELCOME TO GRAPH\nPlease make a selection: \n";

    int input;
    char choice = 'Y';

    while(choice == 'Y'){
        std::cout << "Press 1 - add vertex\nPress 2 - delete vertex\nPress 3 - add Edge and Weight for two vertices\n"
                "Press 4 - print all vertices\nPress 5 - print all edges for your vertex\nPress 6 - perform Depth First Search"
                "\nPress 7 - perform Breadth First Search\nPress 8 - find the Shortest path from your vertex to all others\nPress 9 - Quit\n";

        std::cin>>input;
        std::cin.ignore(100,'\n');

        std::string data;
        if(input == 1){
            std::cout<<"Enter your vertex: \t";
            std::getline (std::cin,data);
            graph.addVertex(data);
            std::cout<<"Vertex was added\n";
        }
        else if(input == 2){
            std::cout<<"Enter your vertex: \t";
            std::getline (std::cin,data);
            graph.deleteVertex(data);
            std::cout<<"Vertex was deleted\n";
        }
        else if(input == 3){

            std::string first;
            std::string second;
            int weight;

            std::cout<<"Enter your first vertex: \t";
            std::getline (std::cin,first);

            std::cout<<"Enter your second vertex: \t";
            std::getline (std::cin,second);

            std::cout<<"Enter the weight between them: \t";
            std::cin>>weight;

            graph.addEdgeAndWeight(first,second,weight);
            std::cout<<"Edge and Weight were added\n";

        }
        else if(input == 4){
            graph.printVertices();
        }
        else if(input == 5){
            std::cout<<"Enter your vertex: \t";
            std::getline (std::cin,data);
            graph.printEdges(data);
        }
        else if(input == 6){
            std::cout<<"Enter your vertex: \t";
            std::getline (std::cin,data);
            DepthFirstSearch(graph,data);
        }
        else if(input == 7){
            std::cout<<"Enter your vertex: \t";
            std::getline (std::cin,data);
            BreadthFirstSearch(graph,data);
        }
        else if(input == 8){
            std::cout<<"Enter your vertex: \t";
            std::getline (std::cin,data);
            ShortestPath(graph,data);
        }
        else
            break ;

        std::cin.clear();
        std::cout<<"Would you like to continue (Y/N): ";
        //std::cin.get();
        std::cin>>choice;
        std::cout<<choice;
        choice = toupper(choice);


    }

}


















