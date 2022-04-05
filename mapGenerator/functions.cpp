#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "map.h"

int* arrayBuilder(int size)
{
    int field=size*size;
    int* arrayToCreateMap=new int[field];

    for(int i=0;  i <field; i++)
    {
        arrayToCreateMap[i]=0;
    }

    return arrayToCreateMap;
}

int tunnelGen(int* array, int arrayIndex, int size, int tunnels)
{
    int arrayNextIndex=arrayIndex;  //zeby nie przechowywalo przypadkowej wartosci jak case nie wejdzie
    int direction = rand() % 4 + 1;
    int length = rand() % tunnels + 1;

    //direction 1=N, 2=E, 3=S, 4=W
    switch (direction) {
    case 1:
       if (!(arrayIndex-size*(length-1)>=0)) break;
       for(int i = 0; i<length;i++){
           array[arrayIndex-size*i]=1;
       };
       arrayNextIndex = arrayIndex-size*(length-1);
        break;


    case 2:
        if(!((arrayIndex%size+length-1)<size)) break;
        for(int i =0; i<length;i++){
            array[arrayIndex+i]=1;
        };
        arrayNextIndex = arrayIndex+(length-1);
        break;

    case 3:
        if (!(arrayIndex+size*(length-1)<=size*size-1)) break;
        for(int i = 0; i<length;i++){
            array[arrayIndex+size*i]=1;
        };
        arrayNextIndex = arrayIndex+size*(length-1);
        break;

    case 4:
        if(!((arrayIndex%size-length+1)>=0)) break;
        for(int i = 0; i<length;i++){
            array[arrayIndex-i]=1;
        };
        arrayNextIndex= arrayIndex-length+1;
        break;
    }
    return arrayNextIndex;
}



// 0 - sciana, 1 - puste miejsce, 2 - specjał
void mainMapGen(int size, int tunnels, int rooms, int density) {

    int field=size*size;
//Generator tablicy
    int* arrayToCreateMap=arrayBuilder(size);

    srand(time(NULL));

    int startIndex = rand() % field;
    arrayToCreateMap[startIndex]=1;
    for(int i=0; i<<density; i++){
        startIndex=tunnelGen(arrayToCreateMap, startIndex,size,tunnels);
    }



    delete[] arrayToCreateMap;
}


