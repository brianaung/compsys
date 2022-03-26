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

int check_files(struct process* processes, int num_process, int curr_process, 
        int curr_file, int cmp_flag, int* count) {
    /* make sure current process is not outside the range*/
    assert((curr_process < num_process) && (curr_process >= 0));

    int j = curr_process - 1;
    /* default for no match, otherwise returns the lowest matching process id */
    int ret = -1; 

    /* if count is not required to keep track of then just use dummy number */
    int k = 0;
    if (count != NULL) {
        k = *count;
    }

    switch (cmp_flag) {
        case CMP_LOCKED:
            while (j >= 0) {
                if (curr_file == processes[j].locked_file_id) {
                    k++;
                    ret = j; // or should i use ==> if ((ret > -1) && (j < ret)) { ret = j; } ... because we want the lowest id
                }
                j--;
            }
            break;
        case CMP_REQUESTED:
            while (j >= 0) {
                if (curr_file == processes[j].requested_file_id) {
                    k++;
                    ret = j;
                }
                j--;
            }
            break;
        case CMP_BOTH:
            while (j >= 0) {
                if ((curr_file == processes[j].locked_file_id) || 
                        (curr_file == processes[j].requested_file_id)) {
                    k++;
                    ret = j;
                }
                j--;
            }
            break;
    }

    if (count != NULL) { *count = k; }

    return ret;
}
