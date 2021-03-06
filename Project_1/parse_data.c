// Program that parses input data

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>

#include "forensic.h"

fore_args* parse_data(int argc, char *argv[], char *envp[])
{
    fore_args *args = malloc(sizeof(fore_args));
    args->arg_r = false;
    args->arg_h = false;
    for (int i = 0; i < 3; i++)
    {
        args->h_args[i] = NULL;
    }
    args->arg_o = false;
    args->outfile = NULL;
    args->arg_v = false;
    args->logfilename = NULL;
    args->f_or_dir = NULL;

    for (int i = 1; i < argc - 1; i++)
    {
        if (strcmp(argv[i], "-r") == 0)
        {
            args->arg_r = true;
            continue;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            args->arg_h = true;
            i++;
            if(i >=argc){
                break;
            }

            if (i == argc-1 || (strcmp(argv[i], "-o")) == 0)
            {
                break;
            }

            char *h_arg = (char *)malloc(20);
            memset(h_arg, '\0', 20);
            char *auxiliar_string;

            auxiliar_string = strstr(argv[i], "md5");
            if (auxiliar_string != NULL)
            {
                strcpy(h_arg, auxiliar_string);
            }
            else
            {
                memset(h_arg, '\0', 20);
            }

            if (h_arg[0] != '\0')
            {
                if (h_arg[3] != ',' && h_arg[3] != '\0')
                {
                    printf("Invalid argument!\n");
                    exit(1);
                }

                args->h_args[0] = "md5";
            }

            memset(h_arg, '\0', 20);

            auxiliar_string = strstr(argv[i], "sha1");
            if (auxiliar_string != NULL)
            {
                strcpy(h_arg, auxiliar_string);
            }
            else
            {
                memset(h_arg, '\0', 20);
            }

            if (h_arg[0] != '\0')
            {
                if (h_arg[4] != ',' && h_arg[4] != '\0')
                {
                    printf("Invalid argument!\n");
                    exit(1);
                }

                if (args->h_args[0] != NULL)
                {
                    args->h_args[1] = "sha1";
                }
                else
                {
                    args->h_args[0] = "sha1";
                }
            }

            memset(h_arg, '\0', 20);

            auxiliar_string = strstr(argv[i], "sha256");
            if (auxiliar_string != NULL)
            {
                strcpy(h_arg, auxiliar_string);
            }
            else
            {
                memset(h_arg, '\0', 20);
            }

            if (h_arg[0] != '\0')
            {
                if (h_arg[6] != ',' && h_arg[6] != '\0')
                {
                    printf("Invalid argument!\n");
                    exit(1);
                }

                if (args->h_args[0] != NULL)
                {
                    if (args->h_args[1] != NULL)
                    {
                        args->h_args[2] = "sha256";
                    }
                    else
                    {
                        args->h_args[1] = "sha256";
                    }
                }
                else
                {
                    args->h_args[0] = "sha256";
                }
            }

            free(h_arg);

            continue;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            args->arg_o = true;
            i++;
            if(i >=argc){
                break;
            }
            if (i == argc-1 || (strcmp(argv[i], "-v")) == 0)
            {
                break;
            }
            args->outfile = argv[i];
            continue;
        }
        else if (strcmp(argv[i], "-v") == 0)
        {
            args->arg_v = true;
            args->logfilename = get_filename_var(envp);
            continue;
        }
    }

    args->f_or_dir = malloc(1000*sizeof(char));
    strcpy(args->f_or_dir, argv[argc - 1]);

    return args;
}

char *get_filename_var()
{
    char*logfilename = (char*)malloc(50*sizeof(char));
 
    char* var_name = "LOGFILENAME";
    var_name = getenv(var_name);

    if(var_name == NULL) //If the LOGFILENAME variable doesn't exist, create new file for logs
        sprintf(logfilename, "logs.txt");
    else
        strcpy(logfilename, var_name);
    
    return logfilename;
}

void free_arguments(fore_args *arguments)
{
    if (arguments->logfilename != NULL)
        free(arguments->logfilename);

    free(arguments->f_or_dir);
}
