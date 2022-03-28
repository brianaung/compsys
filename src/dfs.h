/* perform a depth first search on the given graph */
int visit_dfs(struct graph* rag, struct node visited[], int* visited_count, int adj_size, int k);

/* get the index of the next unvisited node */
int get_unvisited(struct graph* rag, struct node visited[], int* visited_count);

/* set the status of the given node to `visited` to prevent traversing same nodes */ 
void set_visited(struct node visited[], int* visited_count, struct node* t);

/* check whether the given node has been visited or not */
int is_visited(struct node visited[], int* visited_count, struct node* t);
