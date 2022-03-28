struct node {
    int vertex;
    char type;
    struct node* next;
};

struct graph {
    int adj_size;
    struct node** adj_list;
};

struct graph* init_graph(int adj_size);

struct node* create_node(char type, int v);

void add_edge(struct graph* rag, int curr_process, int src, char src_type, int dest, char dest_type);

int cmp_node(struct node* n1, struct node* n2);

void free_graph(struct graph* rag, int adj_size);
