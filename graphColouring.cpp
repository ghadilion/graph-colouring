#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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

bool graph::addEdge(int v1, int v2) {
    bool v1Exists = adjVertices.count(v1), v2Exists = adjVertices.count(v2);
    int remainingVertices = numberOfVertices - adjVertices.size();

    if((!v1Exists && !v2Exists && remainingVertices < 2)
    || ((!v1Exists || !v2Exists) && !remainingVertices)) {
        std::cout << "Error: Graph cannot contain more than " << numberOfVertices << " vertices!!!\n";
        return false;
    }
    if(!v1Exists) {
        adjVertices.insert({v1, std::vector<int>(0)});     // Vertex added with no associated edges
        colours.insert({v1, -1});                          // Color of new vertex set to -1
    }
    if(!v2Exists) {
        adjVertices.insert({v2, std::vector<int>(0)});        
        colours.insert({v2, -1});
    }

    bool edgeAlreadyExists = (std::find(adjVertices[v1].begin(), adjVertices[v1].end(), v2) != adjVertices[v1].end());
    
    if(edgeAlreadyExists) {
        std::cout << "Error: Edge already exists!!!\n";
        return false;
    }
    else {
        adjVertices[v1].push_back(v2);
        adjVertices[v2].push_back(v1);
        return true;
    }
}

void graph::greedyColouring() {
    std::map<int, std::vector<int>>::iterator vertexItr = adjVertices.begin();

    //Setting color of starting vertex to 0
    colours[vertexItr->first] = 0;              

    // iterate through the remaining vertices in graph
    for(vertexItr++; vertexItr != adjVertices.end(); vertexItr++){ 
        
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

    char again = 'y';
    while(again == 'y' || again == 'Y') {
        int numberOfVertices, numberOfEdges;

        std::cout << "Enter number of vertices (order) of the graph - ";
        std::cin >> numberOfVertices;

        graph t(numberOfVertices);

        std::cout << "Enter number of edges (size) of the graph - ";
        std::cin >> numberOfEdges;

        int j = 0, userinpU, userinpV;
        while(j < numberOfEdges){
            std::cout << "Enter the pair to be linked (separated by space) - ";
            std::cin >> userinpU >> userinpV;
            if(t.addEdge(userinpU, userinpV))
                j++;
        }

        t.greedyColouring();
        t.displayColours();
        std::cout << "\nAgain? (y/n): ";
        std::cin >> again;
    }
    return 0;
}