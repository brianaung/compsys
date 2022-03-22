#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char **argv) {

    /* get the filename */
    char* input_file = NULL;
    for (int i=0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            input_file = argv[i+1];
            break;
        }
    }

    /* open the file */
    FILE* file = fopen(input_file, "r");
    assert(file);

    int process_id;
    int locked_file_id; 
    int requested_file_id; 
    while (fscanf(file, "%d %d %d", &process_id, &locked_file_id, &requested_file_id) == 3) {
        printf("%d %d %d\n", process_id, locked_file_id, requested_file_id); 
    }

    fclose(file);
    /**************************/

    return 0;
}
