#ifndef PICKER_H
#define PICKER_H

int getRestaurantsFromFile(char **restaurantsArray); 

int getRandom(int min, int max);

int addRestaurant(char **restaurantsArrayCopy);

int removeRestaurant(char **restaurantsArray, char **restaurantsArrayCopy);

#endif