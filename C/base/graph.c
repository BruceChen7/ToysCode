#include "graph.h"
#include <stdio.h>
#include <limits.h>
#include <assert.h>

void createMGraph(MGraph* g) {
    assert(g != NULL);
    printf("please input the num of vertexes and edges \n");
    scanf("%d %d", &(g->numVertexes), &(g->numEdges));
    printf("please input the vertexes num \n");
    int i, j;
    for(i = 0 ; i < g->numVertexes; i++) {
        scanf("%d", &(g->vexs[i]));
    }

    for(i = 0; i < g->numVertexes; i++) {
        for(j = 0 ; j < g->numVertexes; j++) {
            g->arc[i][j] = INT_MAX;
        }
    }
   printf("please input concreate edges and weight \n");
    int k;
    for(k = 0 ; k < g->numEdges; k++) {
        int w;
        scanf("%d %d  %d", &i, &j, &w);
        g->arc[i][j] = w;
        g->arc[j][i] = g->arc[i][j];
    }
}

static void dfs(MGraph* g, int* visited, int i) {
    int j;
    visited[i]  = 1;
    printf("%d ", g->vexs[i]);

    for(j = 0 ; j < g->numVertexes; j++) {
        if(g->arc[i][j] == 1 && !visited[j]) {
            dfs(g, visited, j);
        }
    }
}

// dfs searching
void dfsTraverse(MGraph* g) {
    int num_vertex = g->numVertexes;
    int  visited[MAXVEX];
    int i;
    for(int i = 0; i < num_vertex; i++) {
        visited[i] = 0;
    }

    for(i = 0 ; i < num_vertex; i++) {
        if(!visited[i]) {
            dfs(g, visited, i);
            printf("\n");
        }
    }
}
