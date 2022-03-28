#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "rag.h"

/* initialise and return a resource allocation graph represented by an 
 * adjacency list.
 */
struct graph* init_graph(int adj_size) {
    struct graph* rag = (struct graph*)malloc(sizeof(struct graph));
    assert(rag);

    rag->adj_list = (struct node**)malloc(sizeof(struct node*)*adj_size);
    assert(rag->adj_list);
    rag->adj_size = adj_size;

    /* init graph */
    for (int i=0; i<adj_size; i++) {
        rag->adj_list[i] = NULL;
    }

    return rag;
}

/* create a vertex node that is either a process or a resource file */
struct node* create_node(char type, int v) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    assert(new_node);

    new_node->vertex = v;
    new_node->type = type;
    new_node->next = NULL;

    return new_node;
}

/* add an edge going from src vertex to dest vertex to the graph */
void add_edge(struct graph* rag, int curr_process, int src, char src_type, 
        int dest, char dest_type) {
    /* add edge from src to dest node */
    struct node* node = create_node(src_type, src);
    node->next = create_node(dest_type, dest);
    rag->adj_list[curr_process] = node;
}

/* given 2 nodes, return 1 if they are the same, 0 otherwise */
int cmp_node(struct node* n1, struct node* n2) {
    return ((n1->vertex == n2->vertex) && (n1->type == n2->type));
}

/* free memory of the given adjacency list */
void free_graph(struct graph* rag, int adj_size) {
    for (int i=0; i<adj_size; i++) {
        free(rag->adj_list[i]->next);
        free(rag->adj_list[i]);
    }
    free(rag->adj_list);
    free(rag);
}
