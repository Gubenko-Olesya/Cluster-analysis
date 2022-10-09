//Gubenko Olesya 212

#include "classes.hpp"

int main() {
	Controller controller;
	Cloud cloud_1;
	Interface command;
	int command_code;
	double centerX, centerY, dispX, dispY;
	int n;

	while(1) {
        cout << "Choose a command:" << endl;
        cout << "  1) Create_a_cloud\n  2) Print_the_cloud\n  3) Stop_program" << endl << endl;
        command_code = command.Start();

        switch (command_code) {
            case UNKNOWN:
                cout << "Unknown command" << endl;
	    		return 1;
            case CREATE_CLOUD:
                cout << "Enter cloud parameters:" << endl;
	    		cout << "- Number of points\n- Average x and y coordinates\n- Dispersion in x and y" << endl;
	    		cin >> n >> centerX >> centerY >> dispX >> dispY;
	    		controller.Cloud_Gener(&cloud_1, n, centerX, centerY, dispX, dispY);
	    		if (cloud_1.GetCloud()) {
	    			cout << "A cloud was created sucessfully." << endl << endl;
	    		}
                break;
            case PRINT_CLOUD:
                controller.Cloud_Print(&cloud_1);
		cout << "The cloud was printed in the file cloud.txt." << endl << endl;
                break;
            case STOP:
                cout << "Program completed." << endl;
	    		break;
        }
        if(command_code == STOP)
            break;
    }
    return 1;
}
