//Gubenko Olesya 212

#include "classes.hpp"

int main() {
        Controller controller;
        Cloud cloud_1;
        Interface command;
        Field field;
        Clusters cluster;
        int command_code;
        double centerX, centerY, dispX, dispY;
        int n;

        vector<string> f =  {"cloud.txt"};

        while(1) {
        cout << "Choose a command:" << endl;
        //cout << "  1) Create_a_cloud\n  2) Print_the_cloud\n  3) Stop_program" << endl << endl;
        for(string s : command.command_vector) 
            cout << s << endl;
        cout << endl;
        command_code = command.Start();

        ofstream file("cloud.txt", ios_base::trunc);
        file.close();

        switch (command_code) {
            case UNKNOWN:
                cout << "Unknown command" << endl;
                break;
            case CREATE_CLOUD:
                cout << "Enter cloud parameters:" << endl;
                cout << "- Number of points\n- Average x and y coordinates\n- Dispersion in x and y" << endl;
                cin >> n >> centerX >> centerY >> dispX >> dispY;
                controller.Cloud_Gener(cloud_1, n, centerX, centerY, dispX, dispY);
                field.Add(cloud_1);
                if (!cloud_1.GetCloud().empty()) {
                        cout << "A cloud was created successfully." << endl << endl;
                }
                break;
            case PRINT_CLOUD:
                controller.Cloud_Print(cloud_1, "cloud.txt");
                cout << "The cloud was printed in the file cloud.txt." << endl << endl;
                break;
            case STOP:
                cout << "Program completed." << endl;
                break;
            case PRINT_FIELD:
                controller.Field_Print(field, f);
                cout << "The field was printed in the file cloud.txt." << endl << endl;
		break;
            case K_MEANS:
                unsigned int k;
                cout << "Enter k:" << endl;
                cin >> k;

                controller.k_means(k, field, cluster);
                cluster.PrintIntoFiles(k, controller);
		break;
        }
        if(command_code == STOP)
            break;
    }
    return 1;
}
