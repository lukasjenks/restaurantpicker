#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int insertIndex = 0;

int getRandom(int min, int max) {
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void getRestaurantsFromFile(char **restaurantsArray) {
    FILE *restaurantsFile = fopen("./restaurants.txt", "r");
    char *restaurant = (char *)malloc(50 * sizeof(char));
    char *restaurantCopy = restaurant;

    //fopen will return null if it is unable to read the file
    if (restaurantsFile == NULL) {
	free(restaurant);
	return;
    }
    
    while (fgets(restaurantCopy, 50, restaurantsFile)) {
	restaurantsArray[insertIndex] = (char*)malloc(50 * sizeof(char));
	strcpy(restaurantsArray[insertIndex], restaurantCopy);
	insertIndex++;
    }

    fclose(restaurantsFile);
    free(restaurant);
}

void main() {
    // initialize restaurant array and populate it with restaurants from the file
    char **restaurantsArray = (char **)malloc(100 * sizeof(char *));
    char **restaurantsArrayCopy = restaurantsArray;
    getRestaurantsFromFile(restaurantsArrayCopy);
    // seed rand function with current time
    srand (time(NULL));
    // pick a restaurant
    printf("The restaurant you will go to is: %s", restaurantsArrayCopy[rand() % insertIndex]);
    // free allocated memory
    for (int i=0; i<=insertIndex; i++) {
	free(restaurantsArray[i]);
    }
    free(restaurantsArray);
}
