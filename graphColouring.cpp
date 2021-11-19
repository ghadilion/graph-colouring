#include <iostream>
#include <vector>
#include <map>
#include <iterator>

class graph {
    std::map<int, std::vector<int>> adjVertices;    // contains every vertex along with its adjacent vertices 
    int numberOfVertices;
    std::map<int, int> colours;                     // stores the colour of each vertex
public:
    graph(int num);                                 // initializes numOfVertices and colours
    bool addVertex(int v);                          // adds vertices to the graph
    bool addEdge(int v1, int v2);                   // adds an edge between 2 vertices
    void greedyColouring();                         // performs the greedy colouring algorithm
    void displayColours();                          // displays the colour of each vertex
};

graph::graph(int num) {
    numberOfVertices = num;                         
}

bool graph::addVertex(int v){

    //Vertex added only when it doesn't exist already
    if(adjVertices.count(v) == 0){
        std::vector<int> edgeList;
        this->adjVertices.insert({v, edgeList});        // Vertex added with no associated edges
        this->colours.insert({v, -1});                  // Color of new vertex set to -1
        return true;
    } 
    else {
        std::cout << "addVertex Error : Vertex already exists !!!" << std::endl;
        return false;
    }
}

bool graph::addEdge(int v1, int v2) {
    int v1Exists = this->adjVertices.count(v1);
    int v2Exists = this->adjVertices.count(v2);

    //Edege is created only when the vertices are found in the graph
    if(v1Exists != 0 && v2Exists != 0){
        adjVertices[v1].push_back(v2);
        adjVertices[v2].push_back(v1);
        return true;
    }
    else {
        std::cout << "addEdge Error : Vertex index not found !!!" << std::endl;
        return false;
    }
}

void graph::greedyColouring() {
    std::map<int, std::vector<int>>::iterator vertexItr = adjVertices.begin();

    //Setting color of starting vertex to 0
    colours[vertexItr->first] = 0;              

    // iterate through the remaining vertices in graph
    vertexItr++;
    for( ; vertexItr != adjVertices.end(); vertexItr++){ 
        
        // declare a vector of booleans to keep track of the used colours 
        std::vector<bool> usedColours(numberOfVertices, false);

        //iterate through all adjacent vertices of the vertex
        for(auto adjVertex = vertexItr->second.begin(); adjVertex != vertexItr->second.end(); ++adjVertex) { 
            
            // check whether the current adjacent vertex has already been allocated a colour 
            if(colours[*adjVertex] != -1) {
                
                // mark the colour allocated to current adjacent vertex as used
                usedColours[colours[*adjVertex]] = true;  
            }
        
        }

        // determine the numeric value of the smallest colour not allocated to an adjacent vertex yet
        int minColour;
        for(minColour = 0; usedColours[minColour] != false; ++minColour);
        
        // set the colour of current vertex to the smallest unallocated colour
        colours[vertexItr->first] = minColour;
    }
}

void graph::displayColours() {
    for(auto coloursItr = colours.begin(); coloursItr != colours.end(); coloursItr++)
        std::cout << "Vertex " << coloursItr->first << " : " << "colour " << coloursItr->second << std::endl;
}

int main() {

    int numberOfVertices, numberOfEdges;

    std::cout << "Enter number of vertices (order) of the graph - ";
    std::cin >> numberOfVertices;

    graph t(numberOfVertices);

    int i = 0, userVertex;
    while(i < numberOfVertices){
        std::cout << "Enter vertex to be added - ";
        std::cin >> userVertex;
        if(t.addVertex(userVertex) == true)
            i++;
    }

    std::cout << "Enter number of edges (size) of the graph - ";
    std::cin >> numberOfEdges;

    int j = 0, userinpU, userinpV;
    while(j < numberOfEdges){
        std::cout << "Enter the pair to be linked (separated by space) - ";
        std::cin >> userinpU >> userinpV;
        if(t.addEdge(userinpU, userinpV) == true)
            j++;
    }

    t.greedyColouring();
    t.displayColours();

    return 0;
}