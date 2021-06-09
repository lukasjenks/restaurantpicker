#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include "picker.h"

int insertIndex = 0;

static void sigint_handler(int signal, siginfo_t *t, void *arg) {
    printf("\n\nPlease use the q command to exit.\n\n");
}

int main() {

    // seed random function with current time
    srand (time(NULL));

    // setup interrupt struct so that sigint is rerouted to interrupt routine
    // to preserve memory management
    struct sigaction sa_sigint;
    memset(&sa_sigint, 0, sizeof(sa_sigint));
    sigemptyset(&sa_sigint.sa_mask);
    sa_sigint.sa_sigaction = sigint_handler;
    sa_sigint.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa_sigint, NULL);
    
    // initialize restaurant array and populate it with restaurants from the file
    char **restaurantsArray = (char **)malloc(100 * sizeof(char *));
    char **restaurantsArrayCopy = restaurantsArray;

    if (getRestaurantsFromFile(restaurantsArrayCopy) != 0) {
        printf("No restaurants.txt file exists in this directory. Please create it, then run this program again.");
        for (int i=0; i<=insertIndex; i++) {
	    	free(restaurantsArray[i]);
        }
        free(restaurantsArray);
        return 1;
    }

    printf("\nEnter a command. For a list of commands available, enter 'h'\n\n");
    char *input = (char *)malloc(50 * sizeof(char *));
    char *inputCopy = input;

    // main loop to process user input
    while (1) {
		printf("> ");
		fgets(inputCopy, 50, stdin);
		inputCopy[strlen(inputCopy)-1] = '\0';
		// Display help message mode
        if (strcmp(inputCopy, "h") == 0) {
            printf("\nCOMMANDS:\na - add a restaurant\nr - remove a restaurant\np - pick a restaurant\nq - close the program\n\n");

		// Add restaurant mode
        } else if (strcmp(inputCopy, "a") == 0) {
			if (addRestaurant(restaurantsArrayCopy) == -1) {
				break;
			}
		// Remove restaurant mode
		} else if (strcmp(inputCopy, "r") == 0) {
			if (removeRestaurant(restaurantsArray, restaurantsArrayCopy) == -1) {
				break;
			}
		// Select restaurant mode
		} else if (strcmp(inputCopy, "p") == 0) {
            printf("\nThe restaurant you will go to is %s.\n\n", restaurantsArrayCopy[getRandom(0, insertIndex-1)]);
		// Quit mode
        } else if (strcmp(inputCopy, "q") == 0) {
            printf("\nExiting program...\n");
            break;
        }
    }

    // Free allocated memory and exit program with non-zero exit code
    free(input);
    for (int i=0; i<=insertIndex; i++) {
	    free(restaurantsArray[i]);
    }
    free(restaurantsArray);
    return 0;
}

/*
	Opens restaurants.txt and reads in the contents into a string array
*/
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

int addRestaurant(char **restaurantsArrayCopy) {
	FILE *restaurantsFile = fopen("./restaurants.txt", "a");
	char *restaurant = (char *)malloc(50 * sizeof(char));
	char *restaurantCopy = restaurant;
	printf("\nEnter the name of the restaurant you would like to add:\n\n");
	fgets(restaurantCopy, 50, stdin);
	// Replace newline at end of input string with null terminator
	restaurantCopy[strlen(restaurantCopy)-1] = '\0';  

	// fopen will return null if it is unable to read the file
	if (restaurantsFile == NULL) {
		printf("\nAn error occured. Most likely, restaurants.txt does not exist.\n\n");		
		fclose(restaurantsFile);
		free(restaurant);
		return -1;
	}

	// add to array
	restaurantsArrayCopy[insertIndex] = (char *) malloc(50 * sizeof(char));
	strcpy(restaurantsArrayCopy[insertIndex], restaurantCopy);
	insertIndex++;
	
	// write to file
	fprintf(restaurantsFile, "\n");
	fprintf(restaurantsFile, restaurantCopy);
	fclose(restaurantsFile);
	free(restaurant);
	return 0;
}

int removeRestaurant(char **restaurantsArray, char **restaurantsArrayCopy) {
	FILE *restaurantsFile = fopen("./restaurants.txt", "r");
	char *restaurant = (char *)malloc(50 * sizeof(char));
	char *restaurantCopy = restaurant;
	printf("\nEnter the name of the restaurant you would like to remove:\n\n");
	fgets(restaurantCopy, 50, stdin);

	// fopen will return null if it is unable to read the file
	if (restaurantsFile == NULL) {
		printf("\nAn error occured. Most likely, restaurants.txt does not exist.\n\n");
		fclose(restaurantsFile);
		free(restaurant);
		return -1;
	}

	// Replace newline at end of input string with null terminator for comparison
	restaurantCopy[strlen(restaurantCopy)-1] = '\0';

	int found = 0;
	// remove from array
	for (int index = 0; index < insertIndex; index++) {
		if (strcmp(restaurantsArrayCopy[index], restaurantCopy) == 0) {
			found = 1;
			// if element to remove is simply last element, free memory and decrease insertIndex
			if (index == (insertIndex - 1)) {
				free(restaurantsArray[insertIndex - 1]);
				insertIndex--;
			}
			// else we need to swap with last element, and free memory of last index and derease insertIndex
			else {
				strcpy(restaurantsArrayCopy[index], restaurantsArrayCopy[insertIndex-1]);
				free(restaurantsArray[insertIndex-1]);
				insertIndex--;
			}
		}
	}

	if (found == 0) {
		printf("\nThere is no restaurant in the system by that name\n\n"); 
	}

	// write to fie
	fclose(restaurantsFile);
	restaurantsFile = fopen("./restaurants.txt", "w");
	for (int index = 0; index < insertIndex; index++) {
		// If last restaurant, we don't want to print a trailing newline at the end of the file.
		if (index == insertIndex - 1) {
			fprintf(restaurantsFile, "%s", restaurantsArrayCopy[index]);
		} else {
			fprintf(restaurantsFile, "%s\n", restaurantsArrayCopy[index]);
		}
	}
	
	fclose(restaurantsFile);
	free(restaurant);
	return 0;
}

/*
	generates a random number between min & max
*/
int getRandom(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}