#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#define LOG_FILE "payroll.log"
#define RUN_DURATION 20 
#define LOOP_INTERVAL 1  

int main() {
    
    
    srand(time(NULL));

    
    time_t start_time = time(NULL);

    printf("targetProc0: Starting (PID %d), will run for ~%d seconds\n", getpid(), RUN_DURATION);

    while (1) {
        
        if (difftime(time(NULL), start_time) >= RUN_DURATION) {
            break;
        }

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

        else 
        {
            printf("targetProc0: Sleeping\n");
        }

        
        sleep(LOOP_INTERVAL);
    }

    printf("targetProc0: Exiting after ~%d seconds\n", RUN_DURATION);
    return 0;
}