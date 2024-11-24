#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Edge {
    int src, dest;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edge;
    int** adjMatrix;
} Graph;

// Function prototypes
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
void removeEdge(Graph* graph, int src, int dest);
void DFS(Graph* graph, int v, bool visited[], Graph* spanningTree);
Graph* findSpanningTree(Graph* graph);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);

int main() {
    int V = 5;
    Graph* graph = createGraph(V);
    Graph* spanningTree;

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("Original Graph:\n");
    printGraph(graph);

    spanningTree = findSpanningTree(graph);
    printf("\nSpanning Tree:\n");
    printGraph(spanningTree);

    removeEdge(graph, 1, 2);
    printf("\nGraph after removing edge (1, 2):\n");
    printGraph(graph);

    freeGraph(graph);
    freeGraph(spanningTree);
    return 0;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = 0;
    graph->adjMatrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adjMatrix[i] = (int*)calloc(V, sizeof(int));
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
    graph->E++;
}

// Function to remove an edge from the graph
void removeEdge(Graph* graph, int src, int dest) {
    if (graph->adjMatrix[src][dest]) {
        graph->adjMatrix[src][dest] = 0;
        graph->adjMatrix[dest][src] = 0;
        graph->E--;
    }
}

// Function to perform DFS and find the spanning tree
void DFS(Graph* graph, int v, bool visited[], Graph* spanningTree) {
    visited[v] = true;
    for (int i = 0; i < graph->V; i++) {
        if (graph->adjMatrix[v][i] && !visited[i]) {
            addEdge(spanningTree, v, i);
            DFS(graph, i, visited, spanningTree);
        }
    }
}

// Function to find the spanning tree using DFS
Graph* findSpanningTree(Graph* graph) {
    Graph* spanningTree = createGraph(graph->V);
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    DFS(graph, 0, visited, spanningTree);
    free(visited);
    return spanningTree;
}

// Function to print the graph as an adjacency matrix
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to free the memory allocated for the graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}
