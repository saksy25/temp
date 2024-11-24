#include<stdio.h>

struct Graph{
    int totalVertex;
    struct Node **adjList;
};

struct Node{
    int vertex;
    struct Node *next;
};

struct Graph *createGraph(int v){
    struct Graph *g = malloc(sizeof(struct Graph));
    g->totalVertex = v;
    g->adjList = malloc(v * sizeof(struct Node *));
    for(int i=0; i<v; i++){
        g->adjList[i] = NULL;
    }
    return g;
};

struct Node *createNode(int v){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdges(struct Graph *g, int src, int dest){
    struct Node *newNode = createNode(dest);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
}

//BFS
struct Queue{
    int arr[100];
    int f;
    int r;
};

struct Queue *createQueue(){
    struct Queue * q = malloc(sizeof(struct Queue));
    q->f = -1;
    q->r = -1;
    return q;
};

int isEmpty(struct Queue *q){
    if(q->r == -1) return 1;
    return 0;
}

void enqueu(struct Queue *q, int n){
    if(q->r==99) return;
    if(q->f == -1){
        q->f++;
    }
    q->arr[++q->r] = n;
}

int dequeu(struct Queue *q){
    if(isEmpty(q)) printf("Queue Full!");
    else{
        int e = q->arr[q->f];
        if(q->f == q->r){
            q->r = -1;
            q->f = -1;
        }
        else
            q->f++;
        return e;
    }
    return -1;
}

void bfs(struct Graph * g, int startNode){
    int visit[100] = {0};
    struct Queue *q = createQueue();

    enqueu(q, startNode);
    visit[startNode] = 1;

    while(!isEmpty(q)){
        int currentNode = dequeu(q);
        printf("%d ", currentNode);
        struct Node * temp = g->adjList[currentNode];
        while(temp){
            int nextNode = temp->vertex;
            if(visit[nextNode] == 0){
                visit[nextNode] = 1;
                enqueu(q, nextNode);
            }
            temp = temp->next;
        }
    }
}

//DFS
void dfs(struct Graph *g, int startNode){
    int visit[100] = {0};
    int stack[100];
    int top = -1;

    stack[++top] = startNode;
    visit[startNode] = 1;

    while(top!=-1){
        int currentNode = stack[top--];
        printf("%d ", currentNode);
        struct Node * temp = g->adjList[currentNode];
        while(temp){
            int nextNode = temp->vertex;
            if(visit[nextNode] == 0){
                visit[nextNode] = 1;
                stack[++top] = nextNode;
            }
            temp = temp->next;
        }
    }
}

int main(){
    int vertices;
    int edges;
    printf("Enter the number of vertices:");
    scanf("%d", &vertices);
    printf("Enter the number of edges:");
    scanf("%d", &edges);
    struct Graph *g = createGraph(vertices);
    int s, d;
    for(int i=0; i<edges;i++){
        printf("Enter %dth edge: ", i);
        scanf("%d%d", &s, &d);
        addEdges(g,s,d);
    }
    dfs(g,0);
    bfs(g,0);
    return 0;
}
