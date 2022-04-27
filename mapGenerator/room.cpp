#include "room.h"

Room::Room(int width, int height, int *adress) : width(width), height(height), adress(adress)
{

}

Room::~Room()
{

}

int Room::getWidth() const
{
    return width;
}

int Room::getHeight() const
{
    return height;
}

int Room::getX() const
{
    return x;
}

int Room::getY() const
{
    return y;
}

int *Room::getAdress() const
{
    return adress;
}


void Room::setWidth(int newWidth)
{
    width = newWidth;
}

void Room::setHeight(int newHeight)
{
    height = newHeight;
}

void Room::setX(int *array, int size)
{
    int cell=adress-array;
    x = cell%size;
}

void Room::setY(int *array, int size)
{
    int cell=adress-array;
    y = (cell-cell%size)/size;
}

void Room::setAdress(int *newAdress)
{
    adress = newAdress;
}
