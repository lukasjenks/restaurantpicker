#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int insertIndex = 0;

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
	printf("%s", restaurantCopy);
	printf("%s", restaurantsArray[insertIndex]);
	insertIndex++;
    }

    fclose(restaurantsFile);
    free(restaurant);
}

void main(int argc, char **argv) {
    // parse command line args, if exist
    

    // initialize restaurant array and populate it with restaurants from the file
    char **restaurantsArray = (char **)malloc(100 * sizeof(char *));
    char **restaurantsArrayCopy = restaurantsArray;
    getRestaurantsFromFile(restaurantsArrayCopy);
    free(restaurantsArray);
}
