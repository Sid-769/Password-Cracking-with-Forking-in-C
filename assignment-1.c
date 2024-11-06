#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "checkPassword.h"

int main(int argc, char *argv[]) {
    int useForking = 0;

    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        useForking = 1;
    }

    if (useForking == 0) {
        printf("Process %d with parent %d cracking the password...\n", getpid(), getppid());

        char fullPassword[13] = {0};

        for (int segment = 0; segment < 4; segment++) {
            char input[4];
            int startPos = segment * 3;

            for (char c1 = 33; c1 < 127; c1++) {
                for (char c2 = 33; c2 < 127; c2++) {
                    for (char c3 = 33; c3 < 127; c3++) {
                        input[0] = c1;
                        input[1] = c2;
                        input[2] = c3;
                        input[3] = '\0';

                        if (checkPassword(input, startPos) == 0) {
                            printf("Process %d with parent %d finds %d-%d: %s\n", getpid(), getppid(), startPos, startPos + 2, input);
                            memcpy(fullPassword + startPos, input, 3); //copy the found segment into full password
                            break;
                        }
                    }
                    if (checkPassword(input, startPos) == 0) break; //break out of second loop if password found
                }
                if (checkPassword(input, startPos) == 0) break; //break out of third loop if password found
            }
        }

        printf("Full Password Cracked: %s\n", fullPassword);
    } else {
        printf("Process %d with parent %d cracking the password...\n", getpid(), getppid());

        for (int i = 0; i < 4; i++) {
            pid_t pid = fork();

            if (pid == 0) {
                int startPos = i * 3;
                char input[4];

                for (char c1 = 33; c1 < 127; c1++) {
                    for (char c2 = 33; c2 < 127; c2++) {
                        for (char c3 = 33; c3 < 127; c3++) {
                            input[0] = c1;
                            input[1] = c2;
                            input[2] = c3;
                            input[3] = '\0';

                            if (checkPassword(input, startPos) == 0) {
                                printf("Process %d with parent %d finds %d-%d: %s\n", getpid(), getppid(), startPos, startPos + 2, input);
                                exit(0);
                            }
                        }
                    }
                }
                exit(0); //ensure that child exits even if password isn't found
            } else if (pid < 0) {
                perror("Fork failed");
                exit(1);
            }
        }
        while (wait(NULL) > 0); //wait for all children
    }
    return 0; //return value
}
