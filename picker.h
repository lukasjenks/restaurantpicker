#ifndef PICKER_H
#define PICKER_H

int getRestaurantsFromFile(char **restaurantsArray, int *insertIndex); 

int getRandom(int min, int max);

int addRestaurant(char **restaurantsArrayCopy, int *insertIndex);

int removeRestaurant(char **restaurantsArray, char **restaurantsArrayCopy, int *insertIndex);

#endif