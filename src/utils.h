#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>

// Get proc name from /proc/<pid>/comm
char *get_process_name(pid_t pid);

#endif