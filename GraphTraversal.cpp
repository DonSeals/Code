#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Assuming the nodes are represented using chars
void BFS(vector<vector<char>>& adjacency_list, int start_node) {
    int n = adjacency_list.size();
    vector<bool> seen(n, false); // Initialize seen array with 'false'

    queue<int> q;
    q.push(start_node); // Initialize queue with the starting node
    seen[start_node] = true; // Mark the starting node as visited

    while (!q.empty()) {
        int front_node = q.front();
        q.pop();

        // Visit the front_node (print or perform any action)
        cout << "Visiting node: " << front_node << " (" << static_cast<char>('A' + front_node) << ")" << endl;

        // Traverse neighbors of the front_node
        for (char neighbor : adjacency_list[front_node]) {
            int neighbor_index = neighbor - 'A'; // Convert character to index
            if (!seen[neighbor_index]) {
                q.push(neighbor_index); // Push unseen neighbor to the queue
                seen[neighbor_index] = true; // Mark the neighbor as visited
            }
        }
    }
}

void DFS(int start_node, vector<vector<char>>& adjacency_list) {
    int n = adjacency_list.size();
    vector<bool> seen(n, false); // Initialize seen array with 'false'

    stack<int> dfs_stack;
    dfs_stack.push(start_node); // Push the starting node onto the stack
    seen[start_node] = true; // Mark the starting node as visited

    while (!dfs_stack.empty()) {
        int top = dfs_stack.top();
        dfs_stack.pop();

        // Visit the top node (print or perform any action)
        cout << "Visiting node: " << top << " (" << static_cast<char>('A' + top) << ")" << endl;

        // Traverse neighbors of the top node
        for (char neighbor : adjacency_list[top]) {
            int neighbor_index = neighbor - 'A'; // Convert character to index
            if (!seen[neighbor_index]) {
                dfs_stack.push(neighbor_index); // Push unseen neighbor to the stack
                seen[neighbor_index] = true; // Mark the neighbor as visited
            }
        }
    }
}

int main() {
    // Example adjacency list representation of a graph with 8 vertices (labeled A to H)
    vector<vector<char>> adjacency_list = {
        {'B', 'D'},     // Node A is connected to nodes B and D
        {'C', 'F'},     // Node B is connected to nodes C and F
        {'E', 'G', 'H'},// Node C is connected to nodes E, G, and H
        {'F'},          // Node D is connected to node F
        {'B', 'F'},     // Node E is connected to nodes B and F
        {'A'},          // Node F is connected to node A
        {'E', 'H'},     // Node G is connected to nodes E and H
        {'A'}           // Node H is connected to node A
    };

    int start_node = 0; // Starting BFS and DFS from node A (index 0)

    cout << "BFS traversal starting from node " << start_node << " (A):" << endl;
    BFS(adjacency_list, start_node);
    
    cout << "\nDFS traversal starting from node " << start_node << " (A):" << endl;
    DFS(start_node, adjacency_list);

    return 0;
}
