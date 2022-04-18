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

int tunnelsGen(int* array, int size,  int tunnels){
    if(size<tunnels) return -1;
    int field=size*size;

    if(field%2==0){
        int startIndex = rand() % field;
        int genCheck=0;
        array[startIndex]=1;
        while(genCheck>=field/2){
            startIndex=tunnelGen(array, startIndex,size,tunnels);
            for(int i =0; i<field ; i++) if (array[i]==1) genCheck ++;

            if (genCheck<field/2) genCheck=0;
        }

    }
    else {
        int startIndex = rand() % field;
        int genCheck=0;
        array[startIndex]=1;
        while(genCheck>=(field-1)/2){
            startIndex=tunnelGen(array, startIndex,size,tunnels);
            for(int i =0; i<field ; i++) if (array[i]==1) genCheck ++;
            if(genCheck<field/2) genCheck=0;
            }
        }
    return 1;
}

int roomGen(int* array, int size, int roomSize){
    int field=size*size;
    for(int i =0; i<field; i++){
        if (array[i]==1) {
            int roomSeed =rand() % field + 1;
            if(roomSeed==field) {
                //int x = rand() % roomSize +1;//Tu się na razie zatrzymam, sprawdzam czy pokój się zmieści na mapie z innymi pokojami
            }
        }
    }

    return 0;
}
int roomsGen(int* array, int size){
    return 0;
}

// 0 - sciana, 1 - puste miejsce, 2 - specjał
int mainMapGen(int size, int tunnels, int rooms) {
    if(size<tunnels) return -1;

//Generator tablicy
    int* arrayToCreateMap=arrayBuilder(size);

    srand(time(NULL));
    tunnelsGen(arrayToCreateMap, size, tunnels);

    delete[] arrayToCreateMap;
    return 1;
}




//int mainMapGen(int size, int tunnels, int rooms) {
//    if(size<tunnels) return -1;

//    int field=size*size;
////Generator tablicy
//    int* arrayToCreateMap=arrayBuilder(size);

//    srand(time(NULL));
//    if(field%2==0){
//        int startIndex = rand() % field;
//        int genCheck=0;
//        arrayToCreateMap[startIndex]=1;
//        while(genCheck>=field/2){
//            startIndex=tunnelGen(arrayToCreateMap, startIndex,size,tunnels);
//            for(int i =0; i<field ; i++) if (arrayToCreateMap[i]==1) genCheck ++;
//            }

//    }
//    else {
//        int startIndex = rand() % field;
//        int genCheck=0;
//        arrayToCreateMap[startIndex]=1;
//        while(genCheck>=(field-1)/2){
//            startIndex=tunnelGen(arrayToCreateMap, startIndex,size,tunnels);
//            for(int i =0; i<field ; i++) if (arrayToCreateMap[i]==1) genCheck ++;
//            }
//        }

//    delete[] arrayToCreateMap;
//    return 1;
//}
