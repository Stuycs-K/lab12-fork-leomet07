#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int getRandomInt() {
    int x = rand();
    return x % 5 + 1;
}

void handleChild() {
    printf("Hello from Child!\n");
    int x = getRandomInt();
    printf("%d: %dsec\n", getpid(), x);
    sleep(x);
    printf("Awake\n");
}

void handlePossibleForkFail(pid_t p) {
    if (p < 0) {
        perror("fork fail"); // output to stderr instead of stdout
        exit(1);
    }
}
int main() {
    srand(getpid());

    printf("Running...\n");

    pid_t child_one;
    child_one = fork();
    handlePossibleForkFail(child_one);
    if (child_one == 0) { // 0 if this is the child
        handleChild();
        int status;
        waitpid(child_one, &status, 0);
    } else {
        printf("Hello from Parent!\n");
        // pid_t child_two;
        // child_two = fork();
        // handlePossibleForkFail(child_two);
        // handleChild();
        int status;
        waitpid(child_one, &status, 0);
    }

    return 0;
}
