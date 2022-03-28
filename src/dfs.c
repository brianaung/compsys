#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "rag.h"
#include "dfs.h"

/* perform a depth first search on the given graph */
int visit_dfs(struct graph* rag, struct node visited[], int* visited_count, int adj_size, int k) {
    struct node* t;
    struct node* parent;
    int smallest_id = INT_MAX;

    t = rag->adj_list[k];
    /* save parent node to check for cycles */
    parent = t;

    while (t!=NULL) {
        set_visited(visited, visited_count, t);

        /* keep track of the process with smallest id in current search path */
        if ((t->type == 'p') && (t->vertex < smallest_id)) {
            smallest_id = t->vertex;
        }

        /* go to the adjacent node */
        int k = -1;
        for (int i=0; i<adj_size; i++) {
            if ((rag->adj_list[i]->vertex == t->next->vertex) && 
                    (rag->adj_list[i]->type == t->next->type) && 
                    !is_visited(visited, visited_count, t->next)) {
                k = i;
                break;
            }
        }

        /* if the adjacent node is either:
         *   - not in the list
         *   - has been visited before
         */
        if (k == -1) { 
            if (cmp_node(t->next, parent)) {
                /* graph is a cycle. deadlock detected.
                 * return the process with smallest id to terminate
                 */
                return smallest_id;
            } else {
                /* no deadlock*/
                return -1;
            }
        } else {
            /* keep traversing */
            t = rag->adj_list[k];
        }
    }
    return 0;
}

/* get the index of the next unvisited node */
int get_unvisited(struct graph* rag, struct node visited[], int* visited_count) {
    for (int i=0; i<rag->adj_size; i++) {
        if (!is_visited(visited, visited_count, rag->adj_list[i])) { return i; }
    }
    return -1;
}

/* set the status of the given node to `visited` to prevent traversing same nodes */
void set_visited(struct node visited[], int* visited_count, struct node* t) {
    visited[*visited_count].vertex = t->vertex;
    visited[*visited_count].type = t->type;
    (*visited_count)++;
}

/* check whether the given node has been visited or not */
int is_visited(struct node visited[], int *visited_count, struct node* t) {
    for (int i=0; i<*visited_count; i++) {
        if ((t->vertex == visited[i].vertex) && (t->type == visited[i].type)) {
            return 1;
        }
    }
    return 0;
}
