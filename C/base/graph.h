#ifndef __GRAPH__
#define __GRAPH__
typedef int VertexType;
typedef int EdgeType;
#define  MAXVEX 100

typedef struct  {
    VertexType vexs[MAXVEX];
    // adjacent table
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes;
    int numEdges;
} MGraph;

void createMGraph(MGraph* g);
// dfs searching
void dfsTraverse(MGraph* g);

// bfs searching
void bfsTraverse(MGraph* g);

// dijkstra algorithm
void dijkstraPath(MGraph* g, int v0, int* path);

#endif