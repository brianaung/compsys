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

/* for the given file, check whether the file has been encountered before.
 * if so, keep track of the count it has been encountered.
 * cmp_flag: 0 - check with locked files only.
 *           1 - check with requested files only.
 *           2 - check with both files.
 *
 * return: 0 - this file has not been encountered before.
 *         1 - this file has been encountered before.
 */
int check_files(struct process* processes, int num_process, int curr_process, 
        int curr_file, int cmp_flag, int* count) {
    /* make sure current process is not outside the range*/
    assert((curr_process < num_process) && (curr_process >= 0));

    int j = curr_process - 1;
    int ret = 0;

    /* if count is not required to keep track of then just use dummy number */
    int k = 0;
    if (count != NULL) { k = *count; }

    /* perform tests based on the given flag */
    switch (cmp_flag) {
        case CMP_LOCKED:
            while (j >= 0) {
                if (curr_file == processes[j].locked_file_id) {
                    k++;
                    ret = 1;
                }
                j--;
            }
            break;
        case CMP_REQUESTED:
            while (j >= 0) {
                if (curr_file == processes[j].requested_file_id) {
                    k++;
                    ret = 1;
                }
                j--;
            }
            break;
        case CMP_BOTH:
            while (j >= 0) {
                if ((curr_file == processes[j].locked_file_id) || 
                        (curr_file == processes[j].requested_file_id)) {
                    k++;
                    ret = 1;
                }
                j--;
            }
            break;
    }

    /* housekeeping */
    if (count != NULL) { *count = k; }
    return ret;
}
