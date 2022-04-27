#ifndef ROOM_H
#define ROOM_H


class Room{
    int width;
    int height;
    int x;
    int y;
    int* adress;
public:
    Room(int width=2,int height=2, int* adress=0);
    //Room(int width=2,int height=2, int* adress=0, int x=0, int y=0);
    ~Room();

    int getWidth() const;
    int getHeight() const;
    int getX() const;
    int getY() const;
    int *getAdress() const;
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setX(int* array, int size);
    void setY(int* array, int size);
    void setAdress(int *newAdress);
};

#endif // ROOM_H
