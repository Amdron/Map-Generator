#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int mainMapGen(int size, int tunnels, int rooms, int roomSize);

int  tunnelGen(int* array, int arrayIndex, int size, int tunnels);
int tunnelsGen(int* array, int size,  int tunnels);
int** tunnelsTranscription(int* array, int size, int genCheck);

int roomGen(int* array, int size, int rooms, int roomSize);

int* arrayBuilder(int size);
int drawBitMap (int* mapArray, int size, unsigned int bias);


#endif // FUNCTIONS_H
