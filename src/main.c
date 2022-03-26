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
        /* there will always be at least 2 files in one process */
        if (i == 0) {
            num_files = 2;
            continue;
        }

        /* it is a new file if it doesn't match with files from previous processes */
        if (check_files(processes, num_processes, i, processes[i].locked_file_id, 2, NULL) == -1) {
            num_files++;
        }
        if (check_files(processes, num_processes, i, processes[i].requested_file_id, 2, NULL) == -1) {
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
                            processes[i].requested_file_id, 1, &count) != -1) {
                    /* then check if it has the highest occurrence */
                    if (count > highest_occurrence) { highest_occurrence = count; }
                }
            }
        }
        /* execution time = largest k (no of processes requesting the same file) + 2 */
        printf("Execution time %d\n", execution_time + highest_occurrence);
    }

    /* TASK 3 */
    int to_break[num_processes];
    int to_break_count = 0;
    int tmp = 0;
    for (int i=0; i<num_processes; i++) {
        tmp = check_files(processes, num_processes, i, processes[i].requested_file_id, 0, NULL); 
        if (tmp != -1) { to_break[to_break_count] = tmp; to_break_count++; }
    }

    if (to_break_count) {
        printf("Deadlock detected\nTerminate ");
        for (int i=0; i<to_break_count; i++) {
            printf("%d ", to_break[i]);
        }
        printf("\n");
    } else {
        printf("No deadlocks\n");
    }

    return 0;
}
