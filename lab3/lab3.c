#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* buffer = NULL;
    size_t bufferSize = 0;
    ssize_t characters;

    const int historySize = 5;
    char** history = malloc(historySize * sizeof(char *));
    int newestIndex = 0;

    printf("Enter input: ");
    while((characters = getline(&buffer, &bufferSize, stdin)) != -1) {
        //if the input is "print"
        if (strcmp(buffer, "print") == 0) {
            for (int i = 0; i < historySize; i++) { 
                printf("%s\n", history[i]);
            }
        }
        //if the replace the 5th oldest enty 
        if (newestIndex >= historySize) {
            newestIndex = 0;
        }
        //copy the input to the history array
        history[newestIndex] = realloc(history[newestIndex], (strlen(buffer) + 1) * sizeof(char));
        strcpy(history[newestIndex], buffer);
        newestIndex++;
    }
    
    
    free(buffer);
    return 0;
}