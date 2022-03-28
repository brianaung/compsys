int visit_dfs(struct graph* rag, struct node visited[], int* visited_count, int adj_size, int k);
int get_unvisited(struct graph* rag, struct node visited[], int* visited_count);
void set_visited(struct node visited[], int* visited_count, struct node* t);
int is_visited(struct node visited[], int* visited_count, struct node* t);
