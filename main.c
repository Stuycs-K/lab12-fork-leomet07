#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int getRandomInt() {
    int x = rand();
    return x % 5 + 1;
}

void handleChild() {
    srand(getpid()); // seed random based off child PID
    printf("Hello from Child!\n");
    int x = getRandomInt();
    printf("%d: %dsec\n", getpid(), x);
    sleep(x);
    printf("%d finished after %d seconds.\n", getpid(), x);
    exit(x);
}

void handlePossibleForkFail(pid_t p) {
    if (p < 0) {
        perror("fork fail"); // output to stderr instead of stdout
        exit(1);
    }
}
int main() {

    printf("%d about to create 2 child procceses\n", getpid());

    pid_t child_one;
    child_one = fork();
    handlePossibleForkFail(child_one);
    if (child_one == 0) { // 0 if this is the child
        handleChild();
    } else {
        pid_t child_two;
        child_two = fork();
        handlePossibleForkFail(child_two);
        if (child_two == 0) {
            handleChild();
        } else {
            printf("Hello from Parent!\n");
            int status_first_finish;
            pid_t finsihed_pid = wait(&status_first_finish);
            // to get number of seconds from child, use WEXITSTATUS: The return value of the child
            int exit_status = WEXITSTATUS(status_first_finish);
            printf("Main Process %d is done. Child %d slept for %dsec\n", getpid(), finsihed_pid, exit_status);
        }
    }

    return 0;
}
