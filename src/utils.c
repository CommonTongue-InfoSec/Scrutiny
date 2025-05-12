#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *get_process_name(pid_t pid) 
{
    char path[32];
    char *name = malloc(256);
    if (!name) return NULL;

    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    FILE *comm = fopen(path, "r");
    if (!comm) 
    {
        free(name);
        return NULL;
    }
    
    if (fgets(name, 256, comm) == NULL) 
    {
        fclose(comm);
        free(name);
        return NULL;
    }
    
    fclose(comm);
    
    name[strcspn(name, "\n")] = 0;
    return name;
}