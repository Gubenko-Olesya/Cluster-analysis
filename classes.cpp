//Gubenko Olesya 212

#include "classes.hpp"

//Point namespace

Point:: Point(double _X, double _Y, unsigned int _Number, unsigned int _Colour) 
    : x(_X), y(_Y), number(_Number), colour(_Colour) {}

void Point:: Set(double _X, double _Y, unsigned int _Number, unsigned int _Colour) {
    x = _X;
    y = _Y;
    number = _Number;
    colour = _Colour;
}

void Point::PrintPoint(ofstream& file) {
    file << x << " " << y << endl;
}

//Interface namespace

int Interface:: Start() {
    string str;
    cin >> str;

    if (str == s1) return CREATE_CLOUD;
	if (str == s2) return PRINT_CLOUD;
	if (str == s3) return STOP;
	return UNKNOWN;
}

//Cloud namespace

void Cloud:: Set(unsigned int SetSize, Point* SetCloud) {
    if (cloud)
        delete[] cloud;
    size = SetSize;
    cloud = SetCloud;
}

Point* Cloud:: GetCloud() {
    return cloud;
}

//Controller namespace

void Controller:: Cloud_Gener(Cloud* cloud, int n, double centerX, double centerY, double dispX, double dispY) {
	cloud->Set(n, Points_Gener(n, centerX, centerY, dispX, dispY)); // заполняем облако сгенерированными точками

}

void Controller::Cloud_Print(Cloud* cloud) {
    if(!cloud->GetCloud()) {
        cout << "No cloud to print. Please, generate a cloud at first.\n";
        return;
    }
    ofstream file("cloud.txt");
    for(int i = 0; i < cloud->GetSize(); ++i)
        cloud->GetCloud()[i].PrintPoint(file);
    file.close();
}

Point* Points_Gener(int n, double centerX, double centerY, double dispX, double dispY) {
	Point* arr = new Point[n];
    default_random_engine gener;
	normal_distribution<double> distributionx(centerX, dispX);
	normal_distribution<double> distributiony(centerY, dispY);

	for (int i = 0; i < n; i++) {
		(arr + i)->Set(distributionx(gener), distributiony(gener), i, 1);
	}

	return arr;
}

