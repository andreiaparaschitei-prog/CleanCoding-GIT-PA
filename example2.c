#include <stdio.h>
#include <stdlib.h>



typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} Graph;



// Creates a new node
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    
    return graph;
}


void addEdge(Graph *graph, int src, int dest) {
    
    Node *newNode = createNode(dest);
    newNode->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = newNode;

    
    newNode = createNode(src);
    newNode->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = newNode;
}


void insertEdges(Graph *graph, int numVertices, int numEdges) {
    int src, dest;
    printf("Adauga %d muchii (valori intre 0 si %d):\n", numEdges, numVertices - 1);
    
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}


void resetVisited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}



int isEmpty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *newNode = createNode(data);

    if (isEmpty(*queue)) {
        *queue = newNode;
    } else {
        Node *temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int dequeue(Node **queue) {
    if (isEmpty(*queue)) return -1;
    
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp); 
    
    return data;
}




void dfs(Graph *graph, int currentVertex) {
    graph->visited[currentVertex] = 1;
    printf("%d ", currentVertex);

    Node *temp = graph->adjacency_lists[currentVertex];

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0) {
            dfs(graph, connectedVertex);
        }
        temp = temp->next;
    }
}


void bfs(Graph *graph, int startVertex) {
    Node *queue = NULL;

    graph->visited[startVertex] = 1;
    enqueue(&queue, startVertex);

    while (!isEmpty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];

        while (temp != NULL) {
            int adjVertex = temp->data;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}



int main() {
    int numVertices, numEdges, startingVertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &numVertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &numEdges);

    Graph *graph = createGraph(numVertices);
    insertEdges(graph, numVertices, numEdges);

    printf("\nDe unde plecam in DFS? ");
    scanf("%d", &startingVertex);
    printf("Parcurgere cu DFS: ");
    dfs(graph, startingVertex);
    printf("\n");

    resetVisited(graph); 

    printf("\nDe unde plecam in BFS? ");
    scanf("%d", &startingVertex);
    printf("Parcurgere cu BFS: ");
    bfs(graph, startingVertex);
    printf("\n");

    return 0;
}