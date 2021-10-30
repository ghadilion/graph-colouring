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
    graph t(13), g(8);
    t.addEdge(0, 1);
    t.addEdge(1, 2);
    t.addEdge(1, 7);
    t.addEdge(1, 8);
    t.addEdge(2, 3);
    t.addEdge(2, 6);
    t.addEdge(3, 4);
    t.addEdge(3, 5);
    t.addEdge(8, 9);
    t.addEdge(8, 12);
    t.addEdge(9, 10);
    t.addEdge(9, 11);

    std::cout << "\nExample Tree graph colouring: ";
    t.greedyColouring();
    t.displayColours();
    
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,4);
    g.addEdge(2,5);
    g.addEdge(3,6);
    g.addEdge(4,7);
    g.addEdge(5,7);
    g.addEdge(6,5);
    g.addEdge(6,7);
    
    std::cout << "\nExample Graph graph colouring: ";
    g.greedyColouring();
    g.displayColours();
    return 0;    
}
