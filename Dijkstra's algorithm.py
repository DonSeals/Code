import networkx as nx
import matplotlib.pyplot as plt
import time  # Import the time module for runtime analysis


def create_graph():
    G = nx.Graph()
    stations = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T']
    edges = [
        ('A', 'B', 2), ('A', 'C', 3), ('B', 'D', 1), ('B', 'E', 4),
        ('C', 'F', 5), ('C', 'G', 2), ('D', 'H', 1), ('E', 'I', 3),
        ('E', 'J', 2), ('F', 'K', 3), ('F', 'L', 2), ('G', 'M', 4),
        ('G', 'N', 3), ('H', 'O', 5), ('I', 'P', 1), ('I', 'Q', 2),
        ('J', 'R', 4), ('J', 'S', 3), ('K', 'T', 6), ('L', 'A', 1),
        ('M', 'B', 3), ('N', 'C', 2), ('O', 'D', 4), ('P', 'E', 1),
        ('Q', 'F', 2), ('R', 'G', 3), ('S', 'H', 2), ('T', 'I', 5)
    ]
    for edge in edges:
        G.add_edge(edge[0], edge[1], weight=edge[2])
    return G


def draw_graph(G, path=[], total_weight=0):
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=500)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)

    if path:
        path_edges = list(zip(path[:-1], path[1:]))
        nx.draw_networkx_nodes(G, pos, nodelist=path, node_color='lime')
        nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='red', width=2)

    plt.title(f"Subway System with Predefined Weights - Total Path Weight: {total_weight}")
    plt.show()


def find_shortest_path(G, start, end):
    start_time = time.time()  # Start time measurement
    try:
        path = nx.dijkstra_path(G, source=start, target=end, weight='weight')
        end_time = time.time()  # End time measurement
        duration = end_time - start_time  # Calculate duration

        # Calculate total weight of the path
        total_weight = sum(G[u][v]['weight'] for u, v in zip(path[:-1], path[1:]))

        print(f"Shortest path from {start} to {end} is: {path}")
        print(f"Total weight (distance or time) of the path: {total_weight}")
        print(f"Time taken to compute the shortest path: {duration} seconds")

        return path, total_weight
    except nx.NetworkXNoPath:
        print("No path exists between these two stations.")
        return [], 0
    except nx.NodeNotFound as e:
        print(f"Error: {e}. Please make sure the station names are correct.")
        return [], 0


if __name__ == "__main__":
    G = create_graph()
    start_station = input("Enter the starting station: ").upper()
    end_station = input("Enter the destination station: ").upper()
    path, total_weight = find_shortest_path(G, start_station, end_station)
    draw_graph(G, path, total_weight)
