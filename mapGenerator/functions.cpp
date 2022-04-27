#include <stdlib.h>
#include <time.h>
#include <qDebug>
#include "functions.h"
#include "map.h"
#include "room.h"




//Buduje mapę
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

//Generuje Tunel i umieszcza go na mapie
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

//Wywołuje dostatecznie dużo razy tunnelGen, żeby wypełnić mapę
int tunnelsGen(int* array, int size,  int tunnels){
    if(size<tunnels) return -1;
    int field=size*size;

    if(field%2==0){
        int startIndex = rand() % field;
        int genCheck=0;
        array[startIndex]=1;
        while(genCheck<field/4){
            startIndex=tunnelGen(array, startIndex,size,tunnels);
            for(int i =0; i<field ; i++) if (array[i]==1) genCheck ++;
            if (genCheck<field/2) genCheck=0;
        }
    return genCheck;
    }
    else {
        int startIndex = rand() % field;
        int genCheck=0;
        array[startIndex]=1;
        while(genCheck<(field-1)/2){
            startIndex=tunnelGen(array, startIndex,size,tunnels);
            for(int i =0; i<field ; i++) if (array[i]==1) genCheck ++;
            if(genCheck<(field-1)/2) genCheck=0;
        }
    return genCheck;
    }

}

//Tworzy tabelę adresów wszystkich tuneli
int** tunnelsTranscription(int* array, int size, int genCheck){
    if(genCheck<1) return NULL;
    int** arrayTunnels=new int*[genCheck];
    for(int i =0; i<genCheck; i++) arrayTunnels[i]=0;

    int tile=0;
    for(int i=0; i<size*size; i++) {
        if(array[i]==1) {arrayTunnels[tile]=&array[i]; tile++;}
    }

    return arrayTunnels;
}

//Generuje pokoje na mapie
int roomGen(int* mapArray, int** tunnelArray, int size, int rooms, int roomSize, int genCheck){
    int field=size*size;
    if (size-roomSize<size/2) return -1;
    int roomCounter=0;
    int roomCheck=0;
    Room* roomArray=new Room[rooms];

    while (roomCounter<rooms){
        for(int i =0; i<genCheck; i++){
            int roomSeed= rand() % field +1;
            if(roomSeed==field){
                int cell2=tunnelArray[i]-&mapArray[0]; //Komórka mapy na której znajduje się tunel
                int width2 = rand() % roomSize + 1;
                int height2 = rand() % roomSize + 1;
                if(cell2%size + width2<=size && cell2-(height2 -1)*size>=0 && !(roomCounter==0)){
                    int x2=cell2%size;
                    int y2=(cell2-x2)/size;
                    for(int i =0; i<roomCounter; i++){
                        int x1=roomArray[i].getX();
                        int y1=roomArray[i].getY();
                        int width1=roomArray[i].getWidth();
                        int height1=roomArray[i].getHeight();
                        if(x2>=x1 && y2>=y1 && (x2-x1<=width1 && y2-y1>height2 || x2-x1>width1)){

                        }
                        else if(x2<=x1 && y2>=y1 && (x1-x2<= width2 && y2-y1>height2 || x1-x2>width2)){

                        }
                        else if(x2>=x1 && y2<=y1 && (x2-x1<=width1 && y1-y2>height1 || x2-x1>width1)){

                        }
                        else if (x2<=x1 && y2<=y1 &&(x1-x2<=width2 && y1-y2>height1 || x1-x2>width2)) {

                        }
                        else {roomCheck=-1; break;};
                    }
                    if(roomCheck!=-1) {
                        roomArray[roomCounter]=Room(width2, height2, tunnelArray[i]);
                        roomArray[roomCounter].setX(&mapArray[0], size);
                        roomArray[roomCounter].setY(&mapArray[0], size);
                        roomCounter++;
                    }

                 }
                else if(cell2%size + width2<=size && cell2-(height2 -1)*size>=0 && roomCounter==0){
                    roomArray[roomCounter]=Room(width2, height2, tunnelArray[i]);
                    roomArray[roomCounter].setX(&mapArray[0], size);
                    roomArray[roomCounter].setY(&mapArray[0], size);
                    roomCounter++;
                }
            }
        }
    }

    for(int i=0; i<rooms; i++){
        int cell=roomArray[i].getAdress()-&mapArray[0];
        int width=roomArray[i].getWidth();
        int height=roomArray[i].getHeight();
        for(int i=0; i<height; i++){
            for(int a=0; a<width; a++) mapArray[cell-(size*i)+a]=2;
        }
    }



    delete [] roomArray;
    return 0;
}

int drawBitMap(int* mapArray, int size){
    int height = size;
    int width = size;
    Map map(width, height);



    for (int y = 0; y < height; y++)
    {
        for (int  x = 0; x < width; x++)
        {
            if(mapArray[x+height*y]==0) map.setColor(Color(0,0,0), x, y);
            else if(mapArray[x+height*y]==1) map.setColor(Color(220,220,220), x, y);
            else map.setColor(Color(119,136,153), x, y);
        }
    }

    map.Export("temp.bmp");
    return 0;
}

// 0 - sciana, 1 - puste miejsce, 2 - specjał
int mainMapGen(int size, int tunnels, int rooms, int roomSize) {
    if(size<tunnels) return -1;

//Generator tablicy
    int* arrayToCreateMap=arrayBuilder(size);
    qDebug()<<"Wchodzimy do mainMapGen";

    srand(time(NULL));
    int amountOfTunnelTiles=tunnelsGen(arrayToCreateMap, size, tunnels);
    int** arrayTunnels= tunnelsTranscription(arrayToCreateMap, size, amountOfTunnelTiles);
    roomGen(arrayToCreateMap, arrayTunnels, size, rooms, roomSize, amountOfTunnelTiles);
    qDebug()<<"Czy dochodzi do tego etapu?";
    drawBitMap(arrayToCreateMap, size);
    qDebug()<<"Yep";
    delete[] arrayTunnels;
    delete[] arrayToCreateMap;
    return 1;
}


