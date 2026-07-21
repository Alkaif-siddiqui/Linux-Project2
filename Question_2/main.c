#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3
#define TIME_LIMIT 5   // in seconds

int main() {
    pid_t pid[NUM_CHILDREN];

    // Create the  child processes
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid[i] = fork();

        if (pid[i] == 0) {
            printf("Child %d started (PID = %d)\n", i + 1, getpid());
            if (i == 1) {
                while (1) {
                    sleep(1);
                }
            }

            sleep(2);
            printf("Child %d finished\n", i + 1);
            exit(0);
        }
    }

    // Parent monitor the  children
    sleep(TIME_LIMIT);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        int status;

        // Check if child process has already terminated or not.
        pid_t result = waitpid(pid[i], &status, WNOHANG);

        if (result == 0) {
            printf("Child PID %d is unresponsive. Terminating...\n", pid[i]);

            kill(pid[i], SIGTERM);   // Request termination
            sleep(1);

            // Force the  kill if still alive
            if (waitpid(pid[i], &status, WNOHANG) == 0) {
                kill(pid[i], SIGKILL);
            }

            waitpid(pid[i], &status, 0); // prevent zombie
        }
        else {
            printf("Child PID %d completed normally.\n", pid[i]);
        }
    }

    printf("All child processes handled successfully.\n");
    return 0;
}
