#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* buffer = NULL;
    size_t bufferSize = 100;

    const int historySize = 5;
    char** history = malloc(historySize * sizeof(char *));
    for (int i = 0; i < historySize; i++) {
        history[i] = malloc(bufferSize * sizeof(char));
        history[i][0] = '\0'; // Initialize with empty string
    }
    int newestIndex = 0;
    int historyCount = 0;

    buffer = malloc(bufferSize * sizeof(char));
    while (1) {
        printf("Enter input: ");
        fflush(stdout);
        if (fgets(buffer, bufferSize, stdin) == NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        //copy the input to the history array
        strcpy(history[newestIndex], buffer);

        newestIndex = (newestIndex + 1) % historySize;
        if (historyCount < historySize) {
            historyCount++;
        }

        if (strcmp(buffer, "print") == 0) {
            int oldestIndex = historyCount == historySize ? newestIndex : 0;
            for (int i = 0; i < historyCount; i++) {
                printf("%s\n", history[(oldestIndex + i) % historySize]);
            }
        }
    }

    for (int i = 0; i < historySize; i++) {
        free(history[i]);
    }
    free(history);
    free(buffer);
    return 0;
}