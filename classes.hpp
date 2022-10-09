//Gubenko Olesya 212

#include<fstream>
#include<iostream>
#include<random>

typedef enum commands {
    UNKNOWN,
    CREATE_CLOUD,
    PRINT_CLOUD,
    STOP
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

    ~Point() {};
};

class Interface {
private:
	string s1 = "Create_a_cloud";
	string s2 = "Print_the_cloud";
	string s3 = "Stop_program";
public:
    int Start();
};

class Cloud {
private:
    unsigned int size = 0;
    Point* cloud = nullptr;
public:
    Cloud() {};

    void Set(unsigned int SetSize, Point* SetCloud);

    unsigned int GetSize() {return size;}
    Point* GetCloud();

    ~Cloud() {
        if(cloud)
            delete[] cloud;
    }
};

class Controller {
public:
    Controller() {};

	void Cloud_Gener(Cloud* cloud, int n, double centerX, double centerY, double dispX, double dispY);
	void Cloud_Print(Cloud* cloud);

    ~Controller() {};
};

Point* Points_Gener(int n, double centerX, double centerY, double dispX, double dispY);

