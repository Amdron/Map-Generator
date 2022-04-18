#ifndef MAP_H
#define MAP_H
#include <vector>

struct Color
{
    float r,g,b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};


class Map
{
public:
    Map(int width, int height);
    ~Map();

    Color getColor(int x, int y) const; //const tu oznacza, że funkcja nie modyfikuje obiektu dla którego jest wywoływana

    void setColor(const Color &color, int x, int y); // tu z kolei używamy const, żeby parametr referowany, nie był zmieniony
    void Export(const char *path) const; //const w () powoduje że  nie można zmienić danych  wskazywanych przez wskaznik

private:
    int m_width;
    int m_height;
    std::vector<Color>m_colors;
};

//int mainMapGen(int size, int tunnels, int rooms);

#endif // MAP_H
