#include <iostream>
#include <vector>
#include <utility> // for std::pair

    std::vector<std::vector<int>> BuildAdjacencyMatrix(int n, std::vector<std::pair<int, int>>& edges){
        
        std::vector<std::vector<int>> adjMatrix;
        // Resize the outer vector to have n elements
        adjMatrix.resize(n); 
        
        // Resize each inner vector to have n elements, initialized to 0
        for (int i = 0; i < n; ++i) {
            adjMatrix[i].resize(n, 0); // Resize each inner vector to have n elements, initialized to 0
        }

        //adjMatrix.resize(n, std::vector<int>(n, 0));
        
        //Use the vector of edges that we have to initialize the values in the matrix
        for (int i = 0; i < edges.size(); ++i) {
            int src = edges[i].first; //to access the first value in the pair, i
            int dest = edges[i].second; //to access the second value in the pair, j
            
            adjMatrix[src][dest] = 1;
        
            //for an undirected graph we would add both the prev and the next because it flows both ways
             //adjMatrix[dest][src] = 1;
        }
        
        return adjMatrix;
    }

    std::vector<std::vector<int>> BuildAdjacencyList(int n, std::vector<std::pair<int, int>>& edges){
        std::vector<std::vector<int>> adjacency_list;
        
        //create a list for each vertex
        for(int i=0; i<n; ++i){
            adjacency_list.push_back(std::vector<int>());
        }
        
        //Use the vector of edges that we have to initialize the values in the matrix
        for (int i = 0; i < edges.size(); ++i) {
            int src = edges[i].first; //to access the first value in the pair, i
            int dest = edges[i].second; //to access the second value in the pair, j
            adjacency_list[src].push_back(dest);
        }
        return adjacency_list;
    }
    
    //print the matrix
    void printMatrix(std::vector<std::vector<int>> adjMatrix) {
        std::cout << "Adjacency Matrix:" << std::endl;
        for (int i = 0; i < adjMatrix.size(); ++i) {
            for (int j = 0; j < adjMatrix[i].size(); ++j) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // Print the adjacency list representation of the graph
    void printList(std::vector<std::vector<int>> adjList) {
        std::cout << "Adjacency List:" << std::endl;
        for (int i = 0; i < adjList.size(); ++i) {
            std::cout << "Vertex " << i << " :";
            for (int j = 0; j < adjList[i].size(); ++j) {
                std::cout << adjList[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

int main() {
    std::vector<std::pair<int, int>> edges = {{0, 1}, {0, 2}, {2, 1}, {2, 3}, {4, 1}, {4, 2}};
    std::vector<std::vector<int>> adjMatrix = BuildAdjacencyMatrix(5, edges);
    printMatrix(adjMatrix);

    std::vector<std::vector<int>> adjList = BuildAdjacencyList(5, edges);
    printList(adjList);
    
    return 0;
}
