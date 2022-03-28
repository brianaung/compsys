#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "rag.h"
#include "dfs.h"
#include "utils.h"

int main(int argc, char **argv) {

    /* get the filename */
    char* input_file = NULL;
    bool compute_time = false;
    bool do_challenge = false;
    for (int i=0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            input_file = argv[i+1];
        } else if (strcmp(argv[i], "-e") == 0) {
            compute_time = true;   
        } else if (strcmp(argv[i], "-c") == 0) {
            do_challenge = true;
        }
    }

    /* store process structs in an array */
    int num_processes = 0;
    struct process* processes;
    processes = (struct process*) malloc(sizeof(struct process)*INI_ARR_SIZE);
    assert(processes);
    save_processes(input_file, &processes, &num_processes);

    /* TASK 1 */
    int num_files = 0;
    for (int i=0; i<num_processes; i++) {
        /* there will always be at least 2 files in one process */
        if (i == 0) {
            num_files = 2;
            continue;
        }

        /* it is a new file if it doesn't match with files from previous processes */
        if (!check_files(processes, num_processes, i, processes[i].locked_file_id, 2, NULL)) {
            num_files++;
        }
        if (!check_files(processes, num_processes, i, processes[i].requested_file_id, 2, NULL)) {
            num_files++;
        }
        /***************************************************************************/
    }
    printf("Processes %d\nFiles %d\n", num_processes, num_files);


    /* TASK 2 */
    int highest_occurrence = 0;
    if (compute_time) {
        int execution_time = 0;

        if (num_processes) {
            execution_time += 1;
            
            for (int i=0; i<num_processes; i++) {
                int count = 1;
                /* if the file is not the new file */
                if (check_files(processes, num_processes, i, 
                            processes[i].requested_file_id, 1, &count)) {
                    /* then check if it has the highest occurrence */
                    if (count > highest_occurrence) { highest_occurrence = count; }
                }
            }
        }
        /* execution time = largest k (no of processes requesting the same file) + 2 */
        printf("Execution time %d\n", execution_time + highest_occurrence);
    }

    /* TASK 3 */
    if (!compute_time) {
        int visited_count = 0;
        struct node visited[num_processes + num_files];
        for (int i=0; i<(num_processes + num_files); i++) {
            visited[i].vertex = 0;
            visited[i].type = 0;
        }

        int adj_size = num_processes * 2;
        struct graph* rag = init_graph(adj_size);
        for (int i=0, j=0; i<num_processes; i++, j+=2) {
            add_edge(rag, j, processes[i].process_id, 'p', processes[i].requested_file_id, 'r'); 
            add_edge(rag, j+1, processes[i].locked_file_id, 'r', processes[i].process_id, 'p'); 
        }

        int to_terminate[num_processes];
        int terminate_count = 0;
        while (get_unvisited(rag, visited, &visited_count) != -1) {
            int k = get_unvisited(rag, visited, &visited_count);
            int smallest_process = visit_dfs(rag, visited, &visited_count, adj_size, k);
            if (smallest_process != -1) {
                to_terminate[terminate_count] = smallest_process;
                terminate_count++;
            } 
        }

        if (terminate_count) {
            printf("Deadlock detected\nTerminate");
            for (int i=0; i<terminate_count; i++) {
                printf(" %d", to_terminate[i]);
            }
            printf("\n");
        } else {
            printf("No deadlocks\n");
        }
    }
    
    return 0;
}
