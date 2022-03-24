#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

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
        if (i == 0) {
            num_files = 2;
            continue;
        }
        if (check_files(processes, num_processes, i, processes[i].locked_file_id, 2, NULL)) {
            num_files++;
        }
        if (check_files(processes, num_processes, i, processes[i].requested_file_id, 2, NULL)) {
            num_files++;
        }
    }
    printf("Processes %d\nFiles %d\n", num_processes, num_files);

    /* TASK 2 */
    int highest_occurrence = 0;
    if (compute_time) {
        // do task 2
        int k = 1;
        int execution_time = 0;

        if (num_processes) {
            execution_time += 1;
            
            for (int i=0; i<num_processes; i++) {
                int occurrence = 1;
                if (check_files(processes, num_processes, i, 
                            processes[i].requested_file_id, 1, &occurrence)) {
                    if (occurrence > highest_occurrence) { highest_occurrence = occurrence; }
                }
            }
        }
        printf("Execution time %d\n", execution_time + highest_occurrence);
    }

    return 0;
}
