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
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

pid_t target_pid = 0;

void handle_sigint(int sig) 
{
    if (target_pid > 0) {
        printf("\nBaseliner: Caught Ctrl+C, detaching from PID %d\n", target_pid);
        if (ptrace(PTRACE_CONT, target_pid, NULL, NULL) == -1) 
        {
            fprintf(stderr, "PTRACE_CONT failed in SIGINT: %s\n", strerror(errno));
        }
        
        if (ptrace(PTRACE_DETACH, target_pid, NULL, NULL) == -1) 
        {
            fprintf(stderr, "PTRACE_DETACH failed in SIGINT: %s\n", strerror(errno));
        }
    }
    exit(0);
}

void log_syscall(long syscall_num, FILE *log) 
{
    const char *syscall_name = "unknown";
    switch (syscall_num) 
    {
        case 0: syscall_name = "read"; break;
        case 1: syscall_name = "write"; break;
        case 2: syscall_name = "open"; break;
        case 3: syscall_name = "close"; break;
        case 219: syscall_name = "time"; break;
        case 230: syscall_name = "nanosleep"; break;
        case 231: syscall_name = "exit_group"; break;
        case 257: syscall_name = "openat"; break;
    }
    
    time_t now = time(NULL);
    
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';
    
    fprintf(log, "[%s] Syscall: %ld (%s)\n", timestamp, syscall_num, syscall_name);
    fflush(log);
}

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

    char *proc_name = get_process_name(pid);
    if (!proc_name) 
    {
        fprintf(stderr, "Failed to get process name\n");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 1;
    }

    mkdir("logs", 0755);
    char proc_dir[512];
    snprintf(proc_dir, sizeof(proc_dir), "logs/%s", proc_name);
    mkdir(proc_dir, 0755);

    
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H-%M", tm);

    char log_path[1024];
    snprintf(log_path, sizeof(log_path), "%s/%s.log", proc_dir, timestamp);

    FILE *log = fopen(log_path, "w");
    if (!log) 
    {
        fprintf(stderr, "Failed to open log file %s: %s\n", log_path, strerror(errno));
        free(proc_name);
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 1;
    }
    printf("Baseliner: Logging to %s\n", log_path);

    if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) == -1) 
    {
        fprintf(stderr, "PTRACE_SYSCALL failed: %s\n", strerror(errno));
        free(proc_name);
        fclose(log);
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 1;
    }

    target_pid = pid;
    signal(SIGINT, handle_sigint);

    printf("Baseliner: Tracing system calls (press Ctrl+C to stop)...\n");

    int in_syscall = 0;
    while (1) 
    {
        if (waitpid(pid, &status, 0) == -1) 
        {
            fprintf(stderr, "waitpid failed: %s\n", strerror(errno));
            break;
        }
        if (WIFEXITED(status) || WIFSIGNALED(status)) 
        {
            printf("Baseliner: Target PID %d exited\n", pid);
            break;
        }
        if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) 
        {
            struct user_regs_struct regs;
            if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1) 
            {
                fprintf(stderr, "PTRACE_GETREGS failed: %s\n", strerror(errno));
                break;
            }
            if (!in_syscall) 
            {
                long syscall_num = regs.orig_rax;
                log_syscall(syscall_num, log);
            }
            in_syscall = !in_syscall;
        }
        if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) == -1) 
        {
            fprintf(stderr, "PTRACE_SYSCALL failed in loop: %s\n", strerror(errno));
            break;
        }
    }

    free(proc_name);
    fclose(log);
    
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    printf("Baseliner: Detached and finished\n");
    
    return 0;
}