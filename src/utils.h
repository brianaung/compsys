#define INI_ARR_SIZE 2
#define CMP_LOCKED 0
#define CMP_REQUESTED 1
#define CMP_BOTH 2

struct process {
    int process_id;
    int locked_file_id;
    int requested_file_id;
};

void save_processes(char* input_file, struct process** processes, int* num_processes);

int check_files(struct process* processes, int num_processes, int curr_process, int curr_file, int cmp_flag);
