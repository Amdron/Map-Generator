#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int mainMapGen(int size, int tunnels, int rooms);

int  tunnelGen(int* array, int arrayIndex, int size, int tunnels);
int tunnelsGen(int* array, int size,  int tunnels);

int roomGen(int* array, int size, int roomSize);
int roomsGen(int* array, int size);

int* arrayBuilder(int size);

#endif // FUNCTIONS_H
