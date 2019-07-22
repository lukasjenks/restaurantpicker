#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>

int insertIndex = 0;

static void sigint_handler(int signal, siginfo_t * t, void *arg) {
    printf("\n\nYou're not allowed to kill my program :)\n");
    // pid_t pid = getpid();
    // kill(pid, SIGKILL);
}

int getRandom(int min, int max) {
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

int main() {
    srand (time(NULL));
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

    // struct to define behaviour for sigint signals (changes default behaviour of SIGINT
    // encounter to be to call the isgint_handler function)
    struct sigaction sa_sigint;
    memset(&sa_sigint, 0, sizeof(sa_sigint));
    sigemptyset(&sa_sigint.sa_mask);
    sa_sigint.sa_sigaction = sigint_handler;
    sa_sigint.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa_sigint, NULL);

    printf("\nEnter a command. For a list of commands available, enter 'h'\n\n");
    char *input = (char *)malloc(50 * sizeof(char *));
    char *inputCopy = input;

    // main loop to process user input
    while (1) {
	printf("> ");
	fgets(inputCopy, 50, stdin);
        inputCopy[strlen(inputCopy)-1] = '\0';
        if (strcmp(inputCopy, "h") == 0) {
            printf("\nCOMMANDS:\na - add a restaurant\np - pick a restaurant\nq - close the program\n\n");
        }
	
	else if (strcmp(inputCopy, "a") == 0) {
	    FILE *restaurantsFile = fopen("./restaurants.txt", "a");
	    char *restaurant = (char *)malloc(50 * sizeof(char));
	    char *restaurantCopy = restaurant;
	    printf("\nEnter the name of the restaurant you would like to add:\n\n");
	    fgets(restaurantCopy, 50, stdin);

	    //fopen will return null if it is unable to read the file
	    if (restaurantsFile == NULL) {
		fclose(restaurantsFile);
		free(restaurant);
		break;
	    }

	    // add to array
	    restaurantsArrayCopy[insertIndex] = (char *) malloc(50 * sizeof(char));
	    strcpy(restaurantsArrayCopy[insertIndex], restaurantCopy);
	    insertIndex++;
	    
	    // write to file
	    fprintf(restaurantsFile, restaurantCopy);
	    fclose(restaurantsFile);
	    free(restaurant);
	}
		
        else if (strcmp(inputCopy, "p") == 0) {
            printf("\nThe restaurant you will go to is %s.\n\n", restaurantsArrayCopy[getRandom(0, insertIndex-1)]);
        }
        else if (strcmp(inputCopy, "q") == 0) {
            printf("\nExiting program...\n");
            break;
        }
    }

    // Free allocated memory
    free(input);
    for (int i=0; i<=insertIndex; i++) {
	    free(restaurantsArray[i]);
    }
    free(restaurantsArray);
    return 0;
}
