//Gubenko Olesya 212

#include<fstream>
#include<iostream>
#include<random>
#include<vector>

typedef enum commands {
    UNKNOWN,
    CREATE_CLOUD,
    PRINT_CLOUD,
    STOP,
    PRINT_FIELD,
    K_MEANS
}command;

using namespace std;

class Point {
private:
    double x = 0;
    double y = 0;
    unsigned int number = 0;
    unsigned colour = 0;
public:
    Point() {};
    Point(double _x, double _y, unsigned int number, unsigned int colour);

    void Set(double _x, double _y, unsigned int number, unsigned colour);

    double GetX() { return x; }
    double GetY() { return y; }
    int GetNumber() { return number; }
    int GetColor() { return colour; }
    void PrintPoint(ofstream& file);

    double Dist(Point& point) {return sqrt(pow(x - point.GetX(), 2) + pow(y - point.GetY(), 2));}

    ~Point() {};
};

class Interface {
public:
    string s1 = "Create_a_cloud";
    string s2 = "Print_the_cloud";
    string s3 = "Stop_program";
    string s4 = "Print_the_field";
    string s5 = "Sort_K_means";
    vector<string> command_vector = {s1, s2, s4, s3, s5};
    int Start();
};

class Cloud {
private:
    unsigned int size = 0;
    vector<Point> cloud;
public:
    Cloud() {};
    // конструктор с явной задачей внутренних данных (Cloud a(num, vec);)
    Cloud(unsigned int _size, vector<Point> _cloud): size(_size), cloud(_cloud) {} 

    void Set(unsigned int SetSize, vector<Point> SetCloud);

    unsigned int& GetSize() {return size;}
    vector<Point>& GetCloud();

    Point operator[](int i) {return (i < size && i >= 0) ? cloud[i] : Point();} //в случае выхода за пределы возвращает пустое мусорное облако
    void Add(Point& point);
    ~Cloud() {}
};

class Field {
private:
    unsigned int field_size = 0;
    vector<Cloud> field;
public:
    Field() {};

    void Set(unsigned int SetSize, vector<Cloud> SetField);
    void Add(Cloud& cloud);

    unsigned int& GetSize() {return field_size;}
    vector<Cloud>& GetField() {return field;}

    Cloud& operator[](int i) {return field[i];} //в случае выхода за пределы возвращает пустое мусорное облако

    ~Field() {}
};

class Controller;

class Clusters {
private:
    vector<Point> centre;
    Field plane;
public:
    Clusters() {}

    unsigned int GetSize() {return plane.GetSize();}
    vector<Point>& GetCentre() {return centre;}
    Field& GetField() {return plane;}
    void PrintIntoFiles(unsigned int k, Controller);

    ~Clusters() {}
};

class Controller {
public:
    Controller() {};

    void Cloud_Gener(Cloud& cloud, int n, double centerX, double centerY, double dispX, double dispY);
    void Cloud_Print(Cloud& cloud, string filename);
    void Field_Print(Field& field, vector<string>);

    void k_means(unsigned int k, Field& init, Clusters& result);

    ~Controller() {};
};


vector<Point> Points_Gener(int n, double centerX, double centerY, double dispX, double dispY);
