#define INI_ARR_SIZE 2
#define CMP_LOCKED 0
#define CMP_REQUESTED 1
#define CMP_BOTH 2

struct process {
    int process_id;
    int locked_file_id;
    int requested_file_id;
};

/*
 * read the test file and store the processes into an array of structs.
 * then return the no. of processes saved.
 */
void save_processes(char* input_file, struct process** processes, int* num_processes);

/* for the given file, check whether the file has been encountered before.
 * if so, keep track of the count it has been encountered.
 * cmp_flag: 0 - check with locked files only.
 *           1 - check with requested files only.
 *           2 - check with both files.
 *
 * return: 0 - this file has not been encountered before.
 *         1 - this file has been encountered before.
 */
int check_files(struct process* processes, int num_processes, int curr_process, int curr_file, int cmp_flag, int* occurrence);
