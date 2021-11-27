#include <iostream>

using namespace std;

class Point {
protected:
    int x;
    int y;

public:
    Point() {
        printf("\tPoint() %p\n", this);
        x = 0;
        y = 0;
    }
    Point(int x, int y) {
        printf("\tPoint(int x, int y) %p\n", this);
        this->x = x;
        this->y = y;
    }
    Point(const Point& point) {
        printf("\tPoint(const Point &point) %p\n", this);
        x = point.x;
        y = point.y;
    }
    ~Point() {
        printf("\t~Point() %p\n", this);
    }
    void getPoint(int* x, int* y) {
        *x = this->x;
        *y = this->y;
    }
    void setPoint(int x, int y) {
        this->x = x;
        this->y = y;
    }
    virtual void printPoint();
};

//описание метода вне класса
void Point::printPoint() {
    printf("(%d, %d)\n", x, y);
}

class Point3D : public Point {
protected:
    int z;

public:
    Point3D() : Point() {
        printf("\tPoint3D() %p\n", this);
        z = 0;
    }
    Point3D(int x, int y, int z) : Point(x, y) {
        printf("\tPoint3D(int x, int y, int z) %p\n", this);
        this->z = z;
    }
    ~Point3D() {
        printf("\t~Point3D() %p\n", this);
    }

    int sum() {
        return (x + y + z);
    }

    void getPoint(int* x, int* y, int* z) {
        //посмотреть как переделать
        Point::getPoint(x, y);
        *z = this->z;
    }
    void printPoint() override {
        printf("(%d, %d, %d)\n", x, y, z);
    }
};

class Vector {
private:
    Point* p1;
    //при создании объекта класса Vector сначала создастся переменная p2
    //и только потом вызовется конструктор класса Vector
    Point p2;

public:
    Vector() {
        printf("\tVector() %p\n", this);
        p1 = new Point;
        //для p2 уже выделена память и p2 инициализирован по умолчанию 
    }
    Vector(Point* p1, Point* p2) {
        printf("\tVector(Point* p1, Point* p2) %p\n", this);
        this->p1 = new Point(*p1);
        this->p2 = *p2;
    }
    Vector(const Vector& vector) {
        printf("\tVector(const Vector& vector) %p\n", this);
        this->p1 = new Point(*vector.p1);
        this->p2 = vector.p2;
    }
    ~Vector() {
        printf("\t~Vector() %p\n", this);
        delete p1;
    }
    void getVectorPoints(Point *p1, Point *p2) {
        *p1 = *(this->p1);
        *p2 = this->p2;
    }
    void printVector() {
        printf("Vector: {\n");

        p1->printPoint();
        p2.printPoint();

        printf("}\n");
    }
};

//проверка 
void print_Point(Point* p) {
    p->printPoint();
}

int main()
{
    setlocale(LC_ALL, "Rus");
    //статическое создание объектов
    printf("____________________________________________________\n");
    printf("Создание объектов и вызов методов\n");
    printf("____________________________________________________\n");
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
    printf("\n\n\n");
    
    {
        printf("Геттер динамического объекта класса Point, инициализированного конструктором по умолчанию:\n");
        Point* a = new Point;
        int x, y, z;

        //выгружаем в x, y значения соответствующих полей объекта a
        a->getPoint(&x, &y);
        delete a;
        printf("\tточка (%d, %d)\n\n", x, y);

        x = -1;
        y = -1;
        z = -1;

        printf("Геттер статического объекта класса Point3D:\n");
        Point3D point1(4, 3, 2);
        point1.getPoint(&x, &y, &z);
        printf("\tточка (%d, %d, %d)\n", x, y, z);
        printf("\n");
    }
    printf("\n\n\n");
    {
        printf("____________________________________________________\n");
        printf("Работа с вектором\n");
        printf("____________________________________________________\n");

        //создаем точки
        printf("Создаем точки a, b:\n");
        Point a(2,5);
        Point b(7,0);

        printf("\tточка a");
        a.printPoint();
        printf("\tточка b");
        b.printPoint();
        

        //создаем вектор из точек a и b, передавая ссылки на них
        printf("Создаем вектор:\n");
        Vector vector(&a, &b);
        
        printf("Создаем точки a1, b1:\n");
        //создаем пустые точки, в которые нужно выгрузить вектор
        Point a1;
        Point b1;

        printf("Выгружаем вектор в точки a1, b1:\n");
        vector.getVectorPoints(&a1, &b1);

        printf("\tточка a1");
        a1.printPoint();
        printf("\tточка b1");
        b1.printPoint();


        printf("Выводим вектор:\n");
        vector.printVector();
        printf("\n");


        printf("Конструктор копирования для vector1:\n");
        Vector *vector1 = new Vector(vector);
        vector1->printVector();
        printf("Удаление vector1:\n");
        delete vector1;
        printf("\n");


        printf("Конструктор по умолчанию для vector2:\n");
        Vector* vector2 = new Vector();
        vector2->printVector();
        printf("Удаление vector2:\n");
        delete vector2;
        printf("\n");
    }
    printf("\n\n\n");
    {
        printf("____________________________________________________\n");
        printf("Помещение объектов в переменные различных типов\n");
        printf("____________________________________________________\n");

        printf("Point3D* p1 = new Point3D(32, 46, 78)\n");
        Point3D* p1 = new Point3D(32, 46, 78);
        printf("Point* p2 = new Point3D(0, 3, 20)\n");
        Point* p2 = new Point3D(0, 3, 20);
        printf("Point* p3 = new Point(11, 33)\n");
        Point* p3 = new Point(11, 33);

        delete p1;
        delete p2;
        delete p3;
    }
}