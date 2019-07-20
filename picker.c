#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int insertIndex = 0;

int getRandom(int min, int max) {
    // seed rand function with current time
    srand (time(NULL));
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int getRestaurantsFromFile(char **restaurantsArray) {
    FILE *restaurantsFile = fopen("./restaurants.txt", "r");
    char *restaurant = (char *)malloc(50 * sizeof(char));
    char *restaurantCopy = restaurant;

    //fopen will return null if it is unable to read the file
    if (restaurantsFile == NULL) {
        fclose(restaurantsFile);
	    free(restaurant);
        return 1;
    }
    else {   
        while (fgets(restaurantCopy, 50, restaurantsFile)) {
            restaurantsArray[insertIndex] = (char*)malloc(50 * sizeof(char));
            // replace newline at end of string with null terminator if exist
            if (restaurantCopy[strlen(restaurantCopy)-1] == '\n') {
                restaurantCopy[strlen(restaurantCopy)-1] = '\0';
            }
            strcpy(restaurantsArray[insertIndex], restaurantCopy);
            insertIndex++;
        }
        fclose(restaurantsFile);
        free(restaurant);
        return 0;
    }
}

void main() {
    // initialize restaurant array and populate it with restaurants from the file
    char **restaurantsArray = (char **)malloc(100 * sizeof(char *));
    char **restaurantsArrayCopy = restaurantsArray;

    if (getRestaurantsFromFile(restaurantsArrayCopy) != 0) {
        printf("No restaurants.txt file exists in this directory. Please create it, then run this program again.");
        for (int i=0; i<=insertIndex; i++) {
	        free(restaurantsArray[i]);
        }
        free(restaurantsArray);
        return;
    }

    printf("Enter a command. For a list of commands available, enter 'h'\n");
    char *input = (char *)malloc(50 * sizeof(char *));
    char *inputCopy = input;

    // main loop to process user input
    while (fgets(inputCopy, 50, stdin)) {
        inputCopy[strlen(inputCopy)-1] = '\0';
        if (strcmp(inputCopy, "h") == 0) {
            printf("COMMANDS:\na - add a restaurant\np - pick a restaurant\nq - close the program\n");
        }
        else if (strcmp(inputCopy, "p") == 0) {
            printf("The restaurant you will go to is %s.\n", restaurantsArrayCopy[getRandom(0, insertIndex-1)]);
        }
        else if (strcmp(inputCopy, "q") == 0) {
            printf("Exiting program...\n");
            break;
        }
    }

    // Free allocated memory
    free(input);
    for (int i=0; i<=insertIndex; i++) {
	    free(restaurantsArray[i]);
    }
    free(restaurantsArray);
}
