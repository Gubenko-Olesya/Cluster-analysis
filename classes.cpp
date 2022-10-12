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
    if (str == s4) return PRINT_FIELD;
    if (str == s5) return K_MEANS;
    return UNKNOWN;
}

//Cloud namespace

void Cloud:: Set(unsigned int SetSize, vector<Point> SetCloud) {
    size = SetSize;
    cloud = SetCloud;
}

vector<Point>& Cloud:: GetCloud() {
    return cloud;
}

void Cloud::Add(Point& point) {
    cloud.push_back(point);
    size++;
}

// Cluster namespace

void Clusters:: PrintIntoFiles(unsigned int k, Controller cntrl) {
    if(plane.GetField().empty())
        return;
    vector<string> filename(k);
    string f;
    for(int i = 1; i <= k; i++)
        filename[i - 1] = to_string(i);
    cntrl.Field_Print(plane, filename);
}

//Controller namespace

void Controller:: Cloud_Gener(Cloud& cloud, int n, double centerX, double centerY, double dispX, double dispY) {
        cloud.Set(n, Points_Gener(n, centerX, centerY, dispX, dispY)); // заполняем облако сгенерированными точками

}

void Controller::Cloud_Print(Cloud& cloud, string filename) {
    if(cloud.GetCloud().empty()) {
        cout << "No cloud to print. Please, generate a cloud first.\n\n";
        return;
    }
    ofstream file(filename, ios_base::app);
    for(int i = 0; i < cloud.GetSize(); ++i)
        cloud.GetCloud()[i].PrintPoint(file);
    file << endl;
    file.close();
}

void Controller::Field_Print(Field& field, vector<string> filename) {
    //Cloud temp;
    //cout << endl << "f size " << filename.size() << "     " << field.GetSize() << endl;
    for(int i = 0; i < field.GetSize(); i++) {
        //cout << i << "    " << filename[i];
        this->Cloud_Print(field.GetField()[i % filename.size()], filename[i % filename.size()]);
    }
}

void Controller::k_means(unsigned int k, Field& init, Clusters& result) {
    //проходимся по всем точкам поля распределяя каждую точку в соответствующий класс
    
    //result.GetCentre().resize(k, 0);

    cout << "Starting k_means\n";

    for(int i = 0; i < k; i++) {
        result.GetCentre().push_back(init[i % init.GetSize()][i / init.GetSize()]);
    }
    
    //cout << "centre size" << result.GetCentre().size();
    result.GetField().GetField().resize(k); //задаем размер результирующего поля
    result.GetField().GetSize() = k;

    double MinDist = -1., PointDist;
    int id_closest_centre;
    for(Cloud cloud : init.GetField()) {
        for(Point point : cloud.GetCloud()) {
            MinDist = -1.;
            for(int i = 0; i < k; i++) {
                PointDist = point.Dist(result.GetCentre()[i]);
                if (PointDist < MinDist || MinDist < 0) {
                    MinDist = PointDist;
                    id_closest_centre = i;
                }        
            }
            result.GetField()[id_closest_centre].Add(point);
        }
    }
}

//Field namespace

void Field::Set(unsigned int SetSize, vector<Cloud> SetField) {
        field_size = SetSize;
        field = SetField;
        /* for(int i = 0; i < SetSize; i++) {
                field[i] = SetField[i];
        } */
}

void Field::Add(Cloud& cloud) {
        field.push_back(cloud);
        ++field_size;
}



vector<Point> Points_Gener(int n, double centerX, double centerY, double dispX, double dispY) {
    vector<Point> arr(n);// = new Point[n];
    default_random_engine gener;
    normal_distribution<double> distributionx(centerX, dispX);
    normal_distribution<double> distributiony(centerY, dispY);

    for (int i = 0; i < n; i++) {
            arr[i].Set(distributionx(gener), distributiony(gener), i, 0);
    }
    return arr;
}


