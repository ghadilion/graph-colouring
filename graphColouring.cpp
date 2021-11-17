#include <iostream>
#include <vector>
#include <map>

class graph {
    std::map<int, std::vector<int>> adjVertices;
    int numberOfVertices;
    std::vector<int> colours;
public:
    graph(int num);
    void addEdge(int v1, int v2);
    void greedyColouring();
    void displayColours();
};

graph::graph(int num) {
    numberOfVertices = num;
    colours.resize(numberOfVertices, -1); //initializes all values in vector to -1
}

void graph::addEdge(int v1, int v2) {
    adjVertices[v1].push_back(v2);
    adjVertices[v2].push_back(v1);
}

void graph::greedyColouring() {
    colours[0] = 0; //set the colour of vertex 0 to colour 0

    for(int vertex = 1; vertex < numberOfVertices; ++vertex) { //iterate through the remaining vertices in graph
        std::vector<bool> usedColours(numberOfVertices, false);

        std::vector<int>::iterator adjVertex;
        for(adjVertex = adjVertices[vertex].begin(); adjVertex != adjVertices[vertex].end(); ++adjVertex) //iterate through all adjacent vertices of a vertex
            if(colours[*adjVertex] != -1)
                usedColours[colours[*adjVertex]] = true;

        int minColour;
        for(minColour = 0; usedColours[minColour] != false; ++minColour);
        colours[vertex] = minColour;
    }
}

void graph::displayColours() {
    for(int vertex = 0; vertex < numberOfVertices; ++vertex)
        std::cout << "Vertex " << vertex << " : " << "colour " << colours[vertex] << std::endl;
}

int main()
{
    int nov, noe;
    std::cout << "Caution to USER : Indexing of nodes must begin from 0 !!!" << std::endl;
    std::cout << "Enter number of vertices (order) of the graph - ";
    std::cin >> nov;
    std::cout << "Enter number of edges (size) of the graph - ";
    std::cin >> noe;

    graph t(nov);

    int u, v, i = 0;
    while(i < noe){
        std::cout << "Enter the pair to be linked (separated by space) - ";
        std::cin >> u;
        std::cin >> v;
        if(u >= nov || v >= nov){
            i--;
            std::cout << "Error : Vertex index cannot exceed order of graph!" << std::endl;
        } else {
            t.addEdge(u, v);
        }
        i++;
    }

    t.greedyColouring();
    t.displayColours();
    return 0;
}