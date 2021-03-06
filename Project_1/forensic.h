// Header file that declares every function and data structure used in the main function of forensic
#ifndef _FORENSIC_H
#define _FORENSIC_H

typedef struct
{
    bool arg_r;        //Option -r of forensic program
    bool arg_h;        //Option -h of forensic program
    char *h_args[3];   //Option -h may have 3 arguments
    bool arg_o;        //Option -o of forensic program
    char *outfile;     //If -o has an argument, it will be stored here
    bool arg_v;        //Option -v of forensic program
    char* logfilename; //If -v is selected, this stores the value of LOGFILENAME variable
    char *f_or_dir;    //File or directory to be evaluated
} fore_args;

enum evt_type {COMMAND, ANALIZED, SIGNAL};

int forensic(fore_args *arguments, struct timespec start);

fore_args* parse_data(int argc, char *argv[], char *envp[]);

char* get_filename_var();

void remove_newline(char* string);

int process_data(fore_args *file_arguments, struct timespec start);

void free_arguments(fore_args *arguments);  

void write_to_logfile(int logfile, double inst, pid_t pid, enum evt_type event, char* description); 

extern bool sigint_activated;
extern unsigned num_directories;
extern unsigned num_files;
extern pid_t main_pid;

void sigint_handler(int signo);

void sigusr1_handler(int signo);

void sigusr2_handler(int signo);

void wait_for_children();

#define READ 0
#define WRITE 1

#endif
