#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "rag.h"
#include "dfs.h"

int visit_dfs(struct graph* rag, struct node visited[], int* visited_count, int adj_size, int k) {
    struct node* t;
    struct node* parent;

    t = rag->adj_list[k];
    parent = t;

    while (t!=NULL) {
        set_visited(visited, visited_count, t);

        // go to the adjacent node in list
        int k = -1;
        for (int i=0; i<adj_size; i++) {
            if ((rag->adj_list[i]->vertex == t->next->vertex) && (rag->adj_list[i]->type == t->next->type) && !is_visited(visited, visited_count, t->next)) {
                k = i;
                break;
            }
        }

        // if the adjacent node is not in the list
        // get other unvisited nodes
        // else all visited then no deadlock
        if (k == -1) { 
            if (cmp_node(t->next, parent)) {
                return 1;
            } else {
                return 0;
            }

        } else {
            // keep going
            t = rag->adj_list[k];
        }

        // printf("parent: %c %d  ", parent->type, parent->vertex);
        // printf("k: %d  ", k);
        // printf("adj: %c %d\n", t->type, t->vertex);
    }
    return 0;
}

int get_unvisited(struct graph* rag, struct node visited[], int* visited_count) {
    for (int i=0; i<rag->adj_size; i++) {
        if (!is_visited(visited, visited_count, rag->adj_list[i])) { return i; }
    }
    return -1;
}

void set_visited(struct node visited[], int* visited_count, struct node* t) {
    visited[*visited_count].vertex = t->vertex;
    visited[*visited_count].type = t->type;
    (*visited_count)++;
}

int is_visited(struct node visited[], int *visited_count, struct node* t) {
    for (int i=0; i<*visited_count; i++) {
        if ((t->vertex == visited[i].vertex) && (t->type == visited[i].type)) {
            return 1;
        }
    }
    return 0;
}
