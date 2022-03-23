#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

/*
 * read the test file and store the processes into an array of structs.
 * then return the no. of processes saved.
 */
void save_processes(char* input_file, struct process** p, int* num_processes) {
    struct process* processes = *p;

    FILE* file = fopen(input_file, "r");
    assert(file);

    int curr_size = INI_ARR_SIZE;
    while (fscanf(file, "%d %d %d", &(processes[*num_processes].process_id), 
                &(processes[*num_processes].locked_file_id), 
                &(processes[*num_processes].requested_file_id)) == 3) {
        (*num_processes)++;
        if (*num_processes == curr_size) {
            curr_size *= 2; 
            processes = realloc(processes, sizeof(* processes)*curr_size);
            assert(processes);
        }
    }

    fclose(file);

    *p = processes;
}

