#include <stdlib.h>
#include <stdio.h>

void getRestaurants(char ***restaurantsArray) {
    FILE *restaurantsFile = fopen("/home/lukas/restaurants.txt", "r");
    char *restaurant = (char *)malloc(100 * sizeof(char));
    char *restaurantCopy = restaurant;
    restaurantCopy[0] = '\0';

    //fopen will return null if it is unable to read the file
    if (restaurantsFile == NULL) {
	free(restaurant);
	return;
    }
    
    int index = 0;
    while (fgets(restaurantCopy, 50, restaurantsFile)) {
	// printf("%s\n%s\n", typeof(restaurantsArray[index]), typeof(restaurantCopy));
	restaurantsArray[index] = restaurantCopy;
	printf("%s", restaurantCopy);
	printf("%s", restaurantsArray[index]);
	index++;
    }

    fclose(restaurantsFile);
    // free(restaurant);
}

void main() {
    printf("---- FAT FRIDAY PICKER ----\n");
    char **restaurantsArray = (char **)malloc(100 * sizeof(char *));
    char **restaurantsArrayCopy = restaurantsArray;
    getRestaurants(&restaurantsArrayCopy);
    printf("%s", restaurantsArrayCopy[0]);
    // for (int i = 0; i < sizeof(restaurantsArray); i++) {
    // printf("%s\n", restaurantsArray[i]);
    // }
    // free(restaurantsArray);
}

