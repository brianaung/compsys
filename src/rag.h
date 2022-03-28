struct node {
    int vertex;
    char type;
    struct node* next;
};

struct graph {
    int adj_size;
    struct node** adj_list;
};

/* initialise and return a resource allocation graph represented by an 
 * adjacency list.
 */
struct graph* init_graph(int adj_size);

/* create a vertex node that is either a process or a resource file */
struct node* create_node(char type, int v);

/* add an edge going from src vertex to dest vertex to the graph */
void add_edge(struct graph* rag, int curr_process, int src, char src_type, int dest, char dest_type);

/* given 2 nodes, return 1 if they are the same, 0 otherwise */
int cmp_node(struct node* n1, struct node* n2);

/* free memory of the given adjacency list */
void free_graph(struct graph* rag, int adj_size);
