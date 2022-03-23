#define INI_ARR_SIZE 2

struct process {
    int process_id;
    int locked_file_id;
    int requested_file_id;
};

void save_processes(char* input_file, struct process** processes, int* num_processes);
