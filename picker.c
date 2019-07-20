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
    if (getRestaurantsFromFile(restaurantsArrayCopy) == 0) {
        // pick a restaurant
        printf("The restaurant you will go to is %s", restaurantsArrayCopy[getRandom(0, insertIndex-1)]);
        // free allocated memory
    } 
    else {
        printf("No restaurants.txt file exists in this directory.\n");
    }
    for (int i=0; i<=insertIndex; i++) {
	    free(restaurantsArray[i]);
    }
    free(restaurantsArray);
}
