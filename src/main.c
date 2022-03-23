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


    return 0;
}
