#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *buffer = NULL;
  size_t size = 0;
  ssize_t characters;
  while (1) {
    printf("Enter programs to run\n");
    characters = getline(&buffer, &size, stdin);

    if (characters == -1) {
      break;
    }

    if (characters > 0 && buffer[characters - 1] == '\n') {
      buffer[characters - 1] = '\0';
    }

    if (strlen(buffer) == 0) {
      continue;
    }

    pid_t pid = fork();
    if (pid < 0) {
      printf("Fork failed\n");
    } else if (pid == 0) {
      execlp(buffer, buffer, (char *)NULL);
      printf("Exec failed\n");
      free(buffer);
      exit(1);
    } else {
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
      }
    }
  }
  free(buffer);
  return 0;
}
