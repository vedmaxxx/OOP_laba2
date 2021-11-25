#include <iostream>

using namespace std;

class Point {
    //переменные для наследования
protected:
    int x;
    int y;

public:
    //конструктор по умолчанию
    Point() {
        printf("\tКонструктор по умолчанию %p\n", this);
    }
    //конструктор c параметрами
    Point(int _x, int _y) {
        printf("\tКонструктор с параметрами %p\n", this);
        x = _x;
        y = _y;
    }
    //конструктор копирования
    Point(const Point &point) {
        printf("\tКонструктор копирования %p\n", this);
        x = point.x;
        y = point.y;
    }
    ~Point() {
        printf("\tДеструктор %p\n", this);
    }
};


int main()
{
    setlocale(LC_ALL, "Rus");
    //статическое создание объектов
    {
        printf("Статическое создание объектов:\n");
        Point a1;
        Point a2(10, 3);
        Point a3(a2);
    }
    printf("\n\n\n");
    //динамическое создание объектов
    {
        printf("Динамическое создание объектов:\n");
        Point* a1 = new Point;
        Point* a2 = new Point(4, 22);
        Point* a3 = new Point(*a2);

        printf("Динамическое удаление объектов:\n");
        delete a1;
        delete a2;
        delete a3;
    }
}