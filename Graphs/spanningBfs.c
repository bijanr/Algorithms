#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Graph {
    int V, E;
    int** adjMatrix;
} Graph;

typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

// Function prototypes
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
void removeEdge(Graph* graph, int src, int dest);
void BFS(Graph* graph, int startVertex, bool visited[], Graph* spanningTree);
Graph* findSpanningTree(Graph* graph);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);
Queue* createQueue();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
bool isEmpty(Queue* q);

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
    if (graph->adjMatrix[src][dest] == 0) {
        graph->adjMatrix[src][dest] = 1;
        graph->adjMatrix[dest][src] = 1;
        graph->E++;
    }
}

// Function to remove an edge from the graph
void removeEdge(Graph* graph, int src, int dest) {
    if (graph->adjMatrix[src][dest] == 1) {
        graph->adjMatrix[src][dest] = 0;
        graph->adjMatrix[dest][src] = 0;
        graph->E--;
    }
}

// Function to perform BFS and find the spanning tree
void BFS(Graph* graph, int startVertex, bool visited[], Graph* spanningTree) {
    Queue* q = createQueue();
    visited[startVertex] = true;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);

        for (int i = 0; i < graph->V; i++) {
            if (graph->adjMatrix[currentVertex][i] && !visited[i]) {
                visited[i] = true;
                addEdge(spanningTree, currentVertex, i);
                enqueue(q, i);
            }
        }
    }
    free(q);
}

// Function to find the spanning tree using BFS
Graph* findSpanningTree(Graph* graph) {
    Graph* spanningTree = createGraph(graph->V);
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    BFS(graph, 0, visited, spanningTree);
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

// Function to create a queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Function to check if the queue is empty
bool isEmpty(Queue* q) {
    if (q->rear == -1)
        return true;
    else
        return false;
}

// Function to add an element to the queue
void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Function to remove an element from the queue
int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}
