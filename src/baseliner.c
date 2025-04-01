#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

pid_t target_pid = 0;

void handle_sigint(int sig) 
{
    if (target_pid > 0) 
    {
        printf("\nBaseliner: Caught Ctrl+C, detaching from PID %d\n", target_pid);
        
        // Resume the target process before detaching
        if (ptrace(PTRACE_CONT, target_pid, NULL, NULL) == -1) {
            fprintf(stderr, "PTRACE_CONT failed in SIGINT: %s\n", strerror(errno));
        }
        
        // Detach from the target process
        if (ptrace(PTRACE_DETACH, target_pid, NULL, NULL) == -1) {
            fprintf(stderr, "PTRACE_DETACH failed in SIGINT: %s\n", strerror(errno));
        }
    }
    
    exit(0);
}

int main() {
    
    pid_t pid;

    
    printf("Enter PID to trace: ");
    if (scanf("%d", &pid) != 1 || pid <= 0) 
    {
        fprintf(stderr, "Invalid PID entered\n");
        return 1;
    }

    
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) 
    {
        fprintf(stderr, "PTRACE_ATTACH failed: %s\n", strerror(errno));
        return 1;
    }

    
    int status;
    if (waitpid(pid, &status, 0) == -1) 
    {
        fprintf(stderr, "waitpid failed: %s\n", strerror(errno));
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 1;
    }

    printf("Baseliner: Successfully attached to PID %d\n", pid);

   
    if (ptrace(PTRACE_CONT, pid, NULL, NULL) == -1) 
    {
        fprintf(stderr, "PTRACE_CONT failed: %s\n", strerror(errno));
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 1;
    }

    printf("Baseliner: Waiting for target to exit (or press Ctrl+C to stop)...\n");

    
    target_pid = pid;

    
    signal(SIGINT, handle_sigint);

    
    while (1) 
    {
        if (waitpid(pid, &status, 0) == -1) 
        {
            fprintf(stderr, "waitpid failed: %s\n", strerror(errno));
            ptrace(PTRACE_DETACH, pid, NULL, NULL);
            return 1;
        }

        if (WIFEXITED(status) || WIFSIGNALED(status)) 
        {
            printf("Baseliner: Target PID %d exited\n", pid);
            break;
        }

        
        if (ptrace(PTRACE_CONT, pid, NULL, NULL) == -1) 
        {
            fprintf(stderr, "PTRACE_CONT failed in loop: %s\n", strerror(errno));
            ptrace(PTRACE_DETACH, pid, NULL, NULL);
            return 1;
        }
    }

    printf("Baseliner: Target has exited, no detach needed\n");
    return 0;
}