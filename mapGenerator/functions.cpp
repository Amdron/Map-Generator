#include <stdlib.h>
#include <time.h>
#include <QImage>
#include <QDebug>
#include <QPixmap>
#include "functions.h"
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
        while(genCheck<field/2){
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
        if(array[i]==1) {
            arrayTunnels[tile]=&array[i];
            tile++;
            if (tile==genCheck) break;
        }
    }

    return arrayTunnels;
}

//Generuje pokoje na mapie
int roomGen(int* mapArray, int** tunnelArray, int size, int rooms, int roomSize, int genCheck){
    int field=size*size;
    //if (size-roomSize<size/2) return -1;
    int roomCounter=0;
    int roomCheck=0;
    Room* roomArray=new Room[rooms];

    while (roomCounter<rooms){
        for(int i =0; i<genCheck; i++){
            int roomSeed= rand() % field +1;
            if(roomSeed==field){
                int cell2=tunnelArray[i]-&mapArray[0]; //Komórka mapy na której znajduje się tunel
                int width2 = rand() % roomSize + 2;
                int height2 = rand() % roomSize + 2;
                if(cell2%size + width2<=size && cell2-(height2 -1)*size>=0 && !(roomCounter==0)){
                    int x2=cell2%size;
                    int y2=(cell2-x2)/size;
                    for(int i =0; i<roomCounter; i++){
                        int x1=roomArray[i].getX();
                        int y1=roomArray[i].getY();
                        int width1=roomArray[i].getWidth();
                        int height1=roomArray[i].getHeight();
                        if(x2>=x1 && y2>=y1 && (x2-x1<=width1 && y2-y1>height2 || x2-x1>width1)){roomCheck=0;}
                        else if(x2<=x1 && y2>=y1 && (x1-x2<= width2 && y2-y1>height2 || x1-x2>width2)){roomCheck=0;}
                        else if(x2>=x1 && y2<=y1 && (x2-x1<=width1 && y1-y2>height1 || x2-x1>width1)){roomCheck=0;}
                        else if (x2<=x1 && y2<=y1 &&(x1-x2<=width2 && y1-y2>height1 || x1-x2>width2)) {roomCheck=0;}
                        else {
                            roomCheck=-1;
                            break;
                        }
                    }
                    if(roomCheck!=-1){
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
    return 1;
}

int drawBitMap(int* mapArray, int size, unsigned int bias){
    if(size<2) return -1;
    int height = size;
    int width = size;
    int column = size;
    int columnSize = bias;
    int row = size;
    int rowSize = bias;
    int newWidth= width*bias;
    int newHeight= height*bias;
    int * tempArray= new int[newWidth*newHeight];

    for(int i=0; i<newWidth*newHeight; i++) tempArray[i]=0;


    for(int c=0; c<column; c++){
        for(int r=0; r<row; r++){
            if(mapArray[c+r*width]==1){
                for(int cs=0; cs<columnSize; cs++){
                    for(int rs=0; rs<rowSize; rs++) tempArray[c*bias+r*newWidth*bias+cs*newWidth+rs]=1;
                }
            }
            else if(mapArray[c+r*width]==2) {
                for(int cs=0; cs<columnSize; cs++){
                    for(int rs=0; rs<rowSize; rs++) tempArray[c*bias+r*newWidth*bias+cs*newWidth+rs]=2;
                }
            }
        }
    }
//    qDebug()<<"Deklarujemy i definiujemy QRgb i map";
    const QRgb black = qRgb(0,0,0);
    const QRgb white = qRgb(255,255,255);
    const QRgb silver = qRgb(192,192,192);
    QImage* map=new QImage(newWidth, newHeight, QImage::Format_RGB888);
//    qDebug()<<"Przepisywanie tempArray do map";
    for(int i=0; i<newWidth*newHeight; i++){
        if(tempArray[i]==0) map->setPixel(i%newWidth,(i-i%newWidth)/newWidth, black);
        else if(tempArray[i]==1) map->setPixel(i%newWidth,(i-i%newWidth)/newWidth, white);
        else map->setPixel(i%newWidth,(i-i%newWidth)/newWidth, silver);
    }
   map->save("temp.bmp");
//    qDebug()<<"Ende";
    delete [] tempArray;
    delete map;
    return 0;
}

// 0 - sciana, 1 - puste miejsce, 2 - specjał
int mainMapGen(int size, int tunnels, int rooms, int roomSize) {
    if(size<tunnels) return -1;

//Generator tablicy
    int* arrayToCreateMap=arrayBuilder(size);
    srand(time(NULL));
    int amountOfTunnelTiles=tunnelsGen(arrayToCreateMap, size, tunnels);
    int** arrayTunnels= tunnelsTranscription(arrayToCreateMap, size, amountOfTunnelTiles);
    int roomGenCheck=roomGen(arrayToCreateMap, arrayTunnels, size, rooms, roomSize, amountOfTunnelTiles);

    if(roomGenCheck==1) {qDebug()<<"drawBitMap"; drawBitMap(arrayToCreateMap, size, 16);}
    delete[] arrayTunnels;
    delete[] arrayToCreateMap;
    return 1;
}



int importMap(const Ui::MainWindow *ui)
{
    QPixmap pix("C:/Programowanie C++/Qt/mapGenerator/build-mapGenerator-Desktop_Qt_6_2_0_MinGW_64_bit-Debug/"+ui->lineNazwa->text());
    ui->labelDisplay->setPixmap(pix.scaled(400,400));
    return 1;
}
