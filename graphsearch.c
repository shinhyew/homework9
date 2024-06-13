#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

void initializeGraph(Graph* graph);
void insertVertex(Graph* graph, int v);
void insertEdge(Graph* graph, int src, int dest);
void DFS(Graph* graph, int vertex);
void BFS(Graph* graph, int startVertex);
void printGraph(Graph* graph);
Node* createNode(int v);
void resetVisited(Graph* graph);

int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    initializeGraph(graph);
    char command;
    int v, src, dest;

    printf("-----[신혜원] [2023041057]-----");

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Graph Searches                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph      = z                                       \n");
        printf(" Insert Vertex         = v      Insert Edge                 = e \n");
        printf(" Depth First Search    = d      Breath First Search         = b \n");
        printf(" Print Graph           = p      Quit                        = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
            case 'z': case 'Z':
                initializeGraph(graph);
                break;
            case 'q': case 'Q':
                free(graph);
                exit(0);
            case 'v': case 'V':
                printf("Insert Vertex = ");
                scanf("%d", &v);
                insertVertex(graph, v);
                break;
            case 'd': case 'D':
                printf("Enter start vertex for DFS= ");
                scanf("%d", &v);
                resetVisited(graph);
                DFS(graph, v);
                break;
            case 'e': case 'E':
                printf("Insert Edge (source destination) = ");
                scanf("%d %d", &src, &dest);
                insertEdge(graph, src, dest);
                break;
            case 'b': case 'B':
                printf("Enter start vertex for BFS= "); // 수정된 부분
                scanf("%d", &v); // 수정된 부분
                resetVisited(graph); // 수정된 부분
                BFS(graph, v); // 수정된 부분
                break;
            case 'p': case 'P':
                printGraph(graph);
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    } while (command != 'q' && command != 'Q');

    free(graph);
    return 0;
}

// 그래프 초기화 함수
void initializeGraph(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
}

// 새로운 노드를 생성하는 함수
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 실제로는 정점을 삽입할 필요가 없으므로 빈 함수로 남겨둠
void insertVertex(Graph* graph, int v) {
}

// 간선 삽입 함수
void insertEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}


void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// BFS 탐색 함수
void BFS(Graph* graph, int startVertex) {
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                queue[rear++] = adjVertex;
                graph->visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// 그래프 출력 함수
void printGraph(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        Node* temp = graph->adjLists[i];
        printf("Vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// 방문 배열 초기화 함수
void resetVisited(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = 0;
    }
}
