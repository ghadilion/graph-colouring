#include <iostream>
#include <vector>
#include <map>

class graph {
    std::map<int, std::vector<int>> adjVertices;    // contains every vertex along with its adjacent vertices 
    int numberOfVertices;
    std::vector<int> colours;                       // stores the colour of each vertex
public:
    graph(int num);                                 // initializes numOfVertices and colours
    void addEdge(int v1, int v2);                   // adds an edge between 2 vertices
    void greedyColouring();                         // performs the greedy colouring algorithm
    void displayColours();                          // displays the colour of each vertex
};

graph::graph(int num) {
    numberOfVertices = num;
    colours.resize(numberOfVertices, -1);           // initializes all values in vector to -1
                                                    // this denotes that none of the vertices 
                                                    // have been allocated a colour
}

void graph::addEdge(int v1, int v2) {
    adjVertices[v1].push_back(v2);
    adjVertices[v2].push_back(v1);
}

void graph::greedyColouring() {
    colours[0] = 0;                                 // set the colour of vertex 0 to colour 0
    
    // iterate through the remaining vertices in graph
    for(int vertex = 1; vertex < numberOfVertices; ++vertex) { 
        
        // declare a vector of booleans to keep track of the used colours 
        std::vector<bool> usedColours(numberOfVertices, false);

        std::vector<int>::iterator adjVertex;

        //iterate through all adjacent vertices of the vertex
        for(adjVertex = adjVertices[vertex].begin(); adjVertex != adjVertices[vertex].end(); ++adjVertex) { 
            
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
        colours[vertex] = minColour;
    }
}

void graph::displayColours() {
    for(int vertex = 0; vertex < numberOfVertices; ++vertex)
        std::cout << "Vertex " << vertex << " : " << "colour " << colours[vertex] << std::endl;
}

int main()
{
    int numberOfVertices, numberOfEdges;
    std::cout << "Caution to USER : Indexing of nodes must begin from 0 !!!" << std::endl;
    std::cout << "Enter number of vertices (order) of the graph - ";
    std::cin >> numberOfVertices;
    std::cout << "Enter number of edges (size) of the graph - ";
    std::cin >> numberOfEdges;

    graph t(numberOfVertices);

    int u, v;
    for(int i = 0; i < numberOfEdges; ++i) {
        std::cout << "Enter the pair to be linked (separated by space) - ";
        std::cin >> u >> v;
        if(u >= numberOfVertices || v >= numberOfVertices) {
            std::cout << "Error : Vertex index cannot exceed order of graph!" << std::endl;
            i--;
        } 
        else
            t.addEdge(u, v);
    }

    t.greedyColouring();
    t.displayColours();

    return 0;
}