#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define LOG_FILE "payroll.log"
#define RUN_DURATION 120 
#define LOOP_INTERVAL 1  
#define DATA_FILE "employees.txt"

#define SENSITIVE_FILE1 "/etc/shadow"

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig) 
{
    keep_running = 0; // Signal the main loop to exit
}

int main() {
    
    srand(time(NULL));

    time_t start_time = time(NULL);

    printf("targetProc0: Starting (PID %d), will run for ~%d seconds\n", getpid(), RUN_DURATION);

    int fd = open(DATA_FILE, O_CREAT | O_WRONLY, 0644);
    if (fd != -1) 
    {
        write(fd, "Employee1,40\nEmployee2,35\n", 27);
        close(fd);
    } else 
    {
        fprintf(stderr, "Error creating %s: %s\n", DATA_FILE, strerror(errno));
    }

    int iter = 0;
    while (keep_running) {

        if (signal(SIGINT, handle_sigint) == SIG_ERR) 
        {
            fprintf(stderr, "Failed to set SIGINT handler\n");
            return 1;
        }
        
        if (difftime(time(NULL), start_time) >= RUN_DURATION) 
        {
            break;
        }

        /*Check the time*/
        time_t current_time = time(NULL);
        printf("targetProc0: Current time %ld\n", current_time);
        /*Check the time--END--*/

        /*Process Checks*/
        if (rand() % 2 == 0) 
        { 
            pid_t pid = getpid();
            printf("targetProc0: Checked PID %d\n", pid);
        }
        /*Process Checks--END--*/

        /*File opening & closing*/
        if (rand() % 2) {
            
            int fd = open(LOG_FILE, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd == -1) 
            {
                fprintf(stderr, "Error opening file: %s\n", strerror(errno));
                
                sleep(LOOP_INTERVAL);
                continue;
            }

            if (close(fd) == -1) 
            {
                fprintf(stderr, "Error closing file: %s\n", strerror(errno));
            }

            printf("targetProc0: Opened and closed %s\n", LOG_FILE);
        } 
        /*File opening & closing --END--*/

        /* A suspicious call*/
        
        if (iter == 30)
        {
            if (access(SENSITIVE_FILE1, F_OK) == -1) 
            {
                fprintf(stderr, "Error accessing %s: %s\n", SENSITIVE_FILE1, strerror(errno));
            }
            else 
            {
                printf("targetProc0: Accessed %s\n", SENSITIVE_FILE1);
            }
        }

        /* A suspicious call --END--*/

        iter++;
        sleep(LOOP_INTERVAL);
    }

    printf("targetProc0: Exiting after ~%d seconds\n", RUN_DURATION);
    return 0;
}