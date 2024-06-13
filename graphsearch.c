#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10 

typedef struct Node 
{
    int vertex;  //int형 변수 vertex 선언
    struct Node* next; //다음 노드를 가리키는 포인터
} Node;

typedef struct Graph //Graph 구조체 선언
 {
    Node* adjLists[MAX_VERTICES]; //인접 리스트 배열
    int visited[MAX_VERTICES]; //방문 했는지 확인하는 배열 선언
    int vertexExists[MAX_VERTICES]; // 정점의 존재 여부를 확인하는 배열 선언
} Graph; //구조체 별칭 Graph로 설정

void initializeGraph(Graph* graph); //그래프 초기화를 위한 함수 선언
void insertVertex(Graph* graph, int v); //정점 삽입 함수 선언
void insertEdge(Graph* graph, int start, int dest); //간선 삽입 함수 선언
void DFS(Graph* graph, int vertex); //DFS 탐색 함수 선언
void BFS(Graph* graph, int startVertex); //BFS 탐색 함수 선언
void printGraph(Graph* graph); //그래프 출력 함수 선언
Node* createNode(int v); //새로운 노드 생성 함수 선언
void resetVisited(Graph* graph); // 방문 배열 초기화 함수 선언
void sortAdjList(Graph* graph); //인접 리스트 정렬 함수 선언

int main() 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph)); //그래프 구조체 메모리 할당
    initializeGraph(graph); //그래프 초기화 함수 호출
    char command; //사용자 명령을 저장할 변수
    int v, start, dest; //정점 및 간선 입력을 위한 변수

    printf("-----[신혜원] [2023041057]-----");

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Graph Searches                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph      = z                                       \n");
        printf(" Insert Vertex         = v      Insert Edge                 = e \n");
        printf(" Depth First Search    = d      Breadth First Search        = b \n");
        printf(" Print Graph           = p      Quit                        = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //command 입력 받기

        switch (command) {
            case 'z': case 'Z': //대소문자 z를 입력받았을 때
                initializeGraph(graph); //Graph를 매개인자로 받아 initializeGraph 함수 호출
                break;
            case 'q': case 'Q': //대소문자 q를 입력받았을 때
                free(graph); //graph를 매개인자로 받아 free 함수 선언
                exit(0); //종료
            case 'v': case 'V': //대소문자 v를 입력받았을 때
                printf("Insert Vertex (0~9) = ");
                scanf("%d", &v); //v값 입력
                if (v >= 0 && v < MAX_VERTICES) //입력받은 v의 값이 0~9사이의 값이면
                 {
                    insertVertex(graph, v); //포인터 graph와 v값을 매개인자로 받아 insertVertex함수 호출
                } else 
                {
                    printf("enter a vertex between 0 and 9.\n"); //0~9값 입력하라고 출력
                }
                break;
            case 'd': case 'D': //대소문자 d를 입력받았을 때.
                printf("Enter start vertex for DFS (0~9) = ");
                scanf("%d", &v); //v값 입력
                if (v >= 0 && v < MAX_VERTICES && graph->vertexExists[v]) //v값이 0~9이면
                 {
                    resetVisited(graph); //포인터 graph를 매개인자로 받아 resetVisited 함수 호출
                    DFS(graph, v); //포인터 graph와 v를 매개인자로 받아 DFS함수 호출
                } else {
                    printf("enter a vertex between 0 and 9 that exists in the graph.\n");
                }
                break;
            case 'e': case 'E': //대소문자 e를 입력받았을 때
                printf("Insert Edge (source destination) = ");
                scanf("%d %d", &start, &dest); //출발 정점(start), 도착 정점(dest)입력 받기
                if ((start >= 0 && start < MAX_VERTICES) && (dest >= 0 && dest < MAX_VERTICES) && graph->vertexExists[start] && graph->vertexExists[dest]) {
                    insertEdge(graph, start, dest); //포인터 graph와 start,dest를 매개인자로 받아 insertEdge 함수 호출
                    sortAdjList(graph); // 포인터 graph를 매개인자로 받아 sortAdjList 함수 호출
                } else {
                    printf("enter vertices between 0 and 9 that exist in the graph.\n");
                }
                break;
            case 'b': case 'B': //대소문자 b를 입력받았을 때
                printf("Enter start vertex for BFS (0~9) = ");
                scanf("%d", &v); //v값 입력받기
                if (v >= 0 && v < MAX_VERTICES && graph->vertexExists[v]) //v가 0~9사이이고 graph의 vertex가 존재하면
                 {
                    resetVisited(graph); //포인터 graph를 매개인자로 받아 resetVisited함수 호출
                    BFS(graph, v); //포인터 graph와 V를 매개인자로 받아 BFS함수 호출
                } else {
                    printf("enter a vertex between 0 and 9 that exists in the graph.\n");
                }
                break;
            case 'p': case 'P': //대소문자 p를 입력받았을 때
                printGraph(graph); //포인터 graph를 매개인자로 받아 printGraph함수 호출
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    } while (command != 'q' && command != 'Q'); //대소문자 q를 입력될 때까지 반복

    free(graph); //그래프 구조체 메모리 헤제
    return 0;
}


void initializeGraph(Graph* graph)
 {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL; //그래프의 인접리스트를 NULL로 초기화
        graph->visited[i] = 0; //그래프의 방문확인 배열을 0으로 초기화
        graph->vertexExists[i] = 0; //정점의 존재 여부를 확인하는 배열을 0으로 초기화(존재하지 않음)
    }
}


Node* createNode(int v)
 {
    Node* newNode = (Node*)malloc(sizeof(Node)); //노드 구조체 포인터 newNode에 Node 크기만큼 동적 메모리 할당
    newNode->vertex = v; //newNode의 Vertex에 v값 할당
    newNode->next = NULL; //newNode의 다음을 NULL로 초기화
    return newNode; // newNode 반환
}


void insertVertex(Graph* graph, int v) 
{
    if (!graph->vertexExists[v]) //그래프의 vertex가 존재하지않으면
    {
        graph->vertexExists[v] = 1; //정점 존재 여부 설정
        printf("Inserted vertex %d\n", v);
    } else {
        printf("Vertex %d already exists.\n", v); //정점이 이미 존재할 경우 메시지 출력
    }
}

void insertEdge(Graph* graph, int start, int dest) 
{
    Node* newNode = createNode(dest); //노드 구초제 포인터 newNode에 dest값을 받는 새로운 노드 생성
    newNode->next = graph->adjLists[start]; //newNode의 다음에  그래프의 인접리스트의 시작값을 할당
    graph->adjLists[start] = newNode; //newNode를 그래프의 인럽리스트에 할당(갱신)

    newNode = createNode(start); //출발 정점을 위한 새 노드 생성
    newNode->next = graph->adjLists[dest]; //newNode의 다음에 그래프의 인접리스트의 맨 앞 할당
    graph->adjLists[dest] = newNode; //newNode를 그래프의 인접리스트에 할당(갱신)
}


void sortAdjList(Graph* graph) 
{
    for (int i = 0; i < MAX_VERTICES; i++) 
    {
        if (graph->adjLists[i] != NULL) //그래프의 인접 리스트가 비어있지 않으면
         {
            Node* sorted = NULL; //노드 구조체의 포인터 sorted를 NULL값으로 초기화
            Node* current = graph->adjLists[i]; //노드 구조체 포인터 current에 그래프의 인접리ㅐ스트 할당

            while (current != NULL) //포인터 current가  NULL이 아닐 때까지 반복 
            {
                Node* next = current->next; //다음 노드를 임시 저장
                if (sorted == NULL || sorted->vertex > current->vertex) //정렬된 리스트가 비어있거나 현재 노드가 가장 작은 경우 
                {
                    current->next = sorted; //current의 next에 sorted값 할당
                    sorted = current; //sorted에 current값 할당
                } else
                 {
                    Node* temp = sorted; //노드 구조체 포인터 temp에 sorted(정렬된 리스트의 헤드)값 할당
                    while (temp->next != NULL && temp->next->vertex < current->vertex) //temp의 next값이 NULL이 아니고 다음 노드의 정점 번호가 현재 노드의 정점번호보다 작을동안
                    {
                        temp = temp->next; //temo에 temp의 next값을 할당
                    }
                    current->next = temp->next; //current의 next에 temp의 next값 할당
                    temp->next = current; //temp의 next에 current 값 할당
                }
                current = next; //current의 next값 할당
            }
            graph->adjLists[i] = sorted; //그래프의 정점 인접 리스트
        }
    }
}


void DFS(Graph* graph, int vertex)
 {
    Node* adjList = graph->adjLists[vertex]; //노드 구조체 포인터 adjList에 graph의 인접리스트 할당
    Node* temp = adjList; //인접 리스트를 순회할 임시 포인터 temp

    graph->visited[vertex] = 1;//그래프의 정점을 방문했다고 표시
    printf("[%d] ", vertex); //방문한 정점 출력

    while (temp != NULL) //temp가 NULL이 아닐동안
    {
        int connectedVertex = temp->vertex; //int형 connectedVertex는 temp의 vertex

        if (graph->visited[connectedVertex] == 0) //인접한 정점을 방문하지 않은 경우 
        {
            DFS(graph, connectedVertex); //재귀적으로 DFS 호출
        }
        temp = temp->next; //다음 인접 노드로 이동
    }
}


void BFS(Graph* graph, int startVertex)
 {
    int queue[MAX_VERTICES]; //큐 배열 생성
    int front = 0; //front값을 0으로 할당
    int rear = 0; //rear값을 0으로 할당

    graph->visited[startVertex] = 1; // 시작 정점을 방문했다고 표시
    queue[rear++] = startVertex; //큐에 시작 정점을 추가 후 rear값 ++

    while (front < rear) //front값이 rear값보다 작을때까지 반복(큐가 비어있지 않을 동안)
    {
        int currentVertex = queue[front++]; //현재정점에 큐 값 할당
        printf("[%d] ", currentVertex); //현재정점 출력

        Node* temp = graph->adjLists[currentVertex]; //현재 정점의 인접 리스트 가져오기

        while (temp) //인접 리스트의 모든 노드를 순회
        {
            int adjVertex = temp->vertex; //adjVertex에 temp의 vertex 할당

            if (graph->visited[adjVertex] == 0) //그래프의 해당 vertex에 방문하지 않으면 
            {
                queue[rear++] = adjVertex; //큐의 rear에 adjVertex 할등
                graph->visited[adjVertex] = 1; //그래프의 해당 정점 방문했다고 표시
            }
            temp = temp->next; //다음 temp로 이동
        }
    }
}



void printGraph(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (graph->vertexExists[i]) //그래프의 인접리스트가 존재하면
         { 
            Node* temp = graph->adjLists[i]; //노드 구조체의 포인터 temp에 그래프의 인접리스트 할당
            printf("[%d]", i); // 정점 번호 출력,
            if (temp) {
                printf(" -> "); // 인접 리스트가 비어있지 않을 경우 출력
                while (temp) //인접 리스트의 모든 노드를 순회 
                {
                    printf("[%d]", temp->vertex); //현재 노드의 정점 번호를 입력
                    temp = temp->next; //다음 temp로 이동
                    if (temp) //다음 temp가 있다면
                    {
                        printf(" -> ");
                    }
                }
            }
            printf("\n");
        }
    }
}


void resetVisited(Graph* graph) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = 0; //모든 정점을 방문하지 않은 상태로 초기화
    }
}
