#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
using namespace std;

struct Vehicle {
	string id;
	string model;
	string brand;
	double pricePerDay;
	bool available;
};

struct Sale {
    int saleId;
    string vehicleId;
    string customerName;
    string phoneNumber;
    string rentalDate;
    int rentalDays;
    double totalAmount;
};


const string VEHICLE_FILE = "vehicles.txt";
const string SALES_FILE = "sales.txt";
string loggedUser = "";


bool login();
void showMenu();
void viewCompanyDetails();
void addVehicle();
void displayVehicles();
void deleteVehicle();
void manageSalesMenu();
void addSale();
void viewSales();
void updateVehicle();


void pause() {
	cout << "\nPress Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}





bool login() {
	string username, password;
	
    cout << "\n---------------" << endl;
     cout << "  User Login  " << endl;
    cout << "---------------" << endl;
	

	cout << "Username:";
	cin >> username;

	cout << "Password:";
	cin >> password;

	if(username == "admin" && password =="12345") {

		cout <<"Login successful!";
		return true;
	} else {
		cout <<"Invalid Login!\n\n" <<endl;
		return false;
	}

}


void showMenu() {
	int choice;
	do {
        
		cout << "\n------ MAIN MENU ------\n";
		cout << "1. View Vehicle Details\n";
		cout << "2. Add Vehicle\n";
		cout << "3. Update Vehicle\n";
		cout << "4. Delete Vehicle\n";
		cout << "5. Manage Sales\n";
		cout << "6. View Company Details\n";
		cout << "7. Logout\n";
		cout << "8. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
            displayVehicles();
            break;
        case 2:
            addVehicle();
            break;
        case 3:
            updateVehicle(); 
            break;
        case 4:
            deleteVehicle();
            break;
        case 5:
            manageSalesMenu();
            break;
        case 6:
            viewCompanyDetails();
            break;
        case 7:
            loggedUser = "";
            cout << "Logged out successfully.\n";
            return;
        case 8:
            cout << "Exiting program...\n";
            exit(0);
		default:
			cout << "Invalid choice!\n";
			break;
		}
		pause();
	} while (true);
}


void viewCompanyDetails() {
	cout << "\n--- Company Details ---\n";
	cout << "Name: Tour Mate Cab Services\n";
	cout << "Contact: 011-222-3344\n";
	cout << "Email: tourmate@gmail.com\n";
	cout << "Address: Colombo 08 Gamunumawatha\n";
}

void saveVehicle(const Vehicle &v) {
	ofstream file(VEHICLE_FILE, ios::app);
	if (!file) {
		cout << "Error: Unable to open file for writing.\n";
		return;
	}
	file << v.id << "," ;
	file<< v.brand << "," ;
	file << v.model << "," ;
	file<< v.pricePerDay << "," ;
	file<< v.available << "\n";
	file.close();
}

void displayVehicles() {
	ifstream file(VEHICLE_FILE);

	if (!file.is_open()) {
		cout << "No vehicle records found.\n";
		return;
	}

	cout << "\n--- Vehicle Details ---\n";
	cout << left << setw(10) << "ID"
	     << setw(15) << "Brand"
	     << setw(15) << "Model"
	     << setw(10) << "Price"
	     << setw(10) << "Available" << endl;

	Vehicle v;
	string priceStr, availStr;

	while (file.good()) {
		getline(file, v.id, ',');
		getline(file, v.brand, ',');
		getline(file, v.model, ',');
		getline(file, priceStr, ',');
		getline(file, availStr, '\n');

		if (v.id.empty()) break;

		v.pricePerDay = stod(priceStr);
		v.available = (availStr == "1" || availStr == "true");

		cout << left << setw(10) << v.id
		     << setw(15) << v.brand
		     << setw(15) << v.model
		     << setw(10) << v.pricePerDay
		     << setw(10) << (v.available ? "Yes" : "No") << endl;
	}

	file.close();
}





void addVehicle() {

	cout << "\n--- Add Vehicle ---\n";

	Vehicle v;
	cout << "Enter Vehicle ID: " << endl;
	cin >> v.id;
	
	ifstream checkFile(VEHICLE_FILE);
	if (checkFile.is_open()) {
		string line, existingId;
		bool duplicate = false;
		
		while (getline(checkFile, line)) {
			if (line.empty()) continue;
			
			stringstream ss(line);
			getline(ss, existingId, ',');
			
			if (existingId == v.id) {
				duplicate = true;
				break;
			}
		}
		checkFile.close();
		
		if (duplicate) {
			cout << "Error: Vehicle ID '" << v.id << "' already exists!\n";
			cout << "Please use a different ID.\n";
			return;  
		}
	}

	cout << "Enter vehicle model: " << endl;
	cin >> v.model;

	cout << "Enter vehicle brand:  " << endl;
	cin >> v.brand ;

	cout << "Enter Price Per-day:  " << endl;
	cin >> v.pricePerDay;

	v.available = true;
	saveVehicle(v);
	cout << "Vehicle added successfully.\n";


}



void deleteVehicle() {
	string id;
	cout << "\nEnter Vehicle ID to delete: ";
	cin >> id;

	ifstream fileIn(VEHICLE_FILE);
	if (!fileIn) {
		cout << "No vehicle records found.\n";
		return;
	}
	ofstream fileOut("temp.txt");
	string line;
	bool found = false;

	while (getline(fileIn, line)) {
		if (line.empty()) continue;

		stringstream ss(line);
		Vehicle v;
		string priceStr, availStr;

		getline(ss, v.id, ',');
		getline(ss, v.brand, ',');
		getline(ss, v.model, ',');
		getline(ss, priceStr, ',');
		getline(ss, availStr, ',');

		 if(v.id != id) {
            fileOut << v.id << "," << v.brand << "," << v.model << "," <<priceStr << "," << availStr << "\n";
		} else {
			found = true;
		}
	}

	fileIn.close();
	fileOut.close();
	remove(VEHICLE_FILE.c_str());
	rename("temp.txt", VEHICLE_FILE.c_str());

	if (found)
		cout << "Vehicle deleted successfully.\n";
	else
		cout << "Vehicle ID not found.\n";
}


void addSale() {
    cout << "\n--- Add New Sale ---\n";
    
    
    displayVehicles();
    
    Sale s;
    string vehicleId;
    
    cout << "\nEnter Vehicle ID to rent: ";
    cin >> vehicleId;
    
    // Check if vehicle exists and is available
    ifstream fileIn(VEHICLE_FILE);
    if (!fileIn) {
        cout << "No vehicle records found.\n";
        return;
    }
    
    bool found = false;
    Vehicle v;
    string priceStr, availStr;
    
    while (fileIn.good()) {
        getline(fileIn, v.id, ',');
        getline(fileIn, v.brand, ',');
        getline(fileIn, v.model, ',');
        getline(fileIn, priceStr, ',');
        getline(fileIn, availStr, '\n');
        
        if (v.id.empty()) break;
        
        if (v.id == vehicleId) {
            found = true;
            v.pricePerDay = stod(priceStr);
            v.available = (availStr == "1" || availStr == "true");
            break;
        }
    }
    fileIn.close();
    
    if (!found) {
        cout << "Vehicle ID not found!\n";
        return;
    }
    
    if (!v.available) {
        cout << "Error: Vehicle is already rented!\n";
        return;
    }
    
    // Get sale details
    s.vehicleId = vehicleId;
    
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, s.customerName);
    
    cout << "Enter Phone Number: ";
    getline(cin, s.phoneNumber);
    
    cout << "Enter Rental Date (DD/MM/YYYY): ";
    getline(cin, s.rentalDate);
    
    cout << "Enter Number of Rental Days: ";
    cin >> s.rentalDays;
    
    while (s.rentalDays <= 0) {
        cout << "Invalid days! Enter positive number: ";
        cin >> s.rentalDays;
    }
    
    s.totalAmount = v.pricePerDay * s.rentalDays;
    
    // Get next sale ID
    ifstream saleFile(SALES_FILE);
    s.saleId = 1;
    if (saleFile.is_open()) {
        string line;
        while (getline(saleFile, line)) {
            if (!line.empty()) s.saleId++;
        }
        saleFile.close();
    }
    
    // Save sale to file
    ofstream saleOut(SALES_FILE, ios::app);
    if (!saleOut) {
        cout << "Error: Unable to open sales file.\n";
        return;
    }
    
    saleOut << s.saleId << ","
            << s.vehicleId << ","
            << s.customerName << ","
            << s.phoneNumber << ","
            << s.rentalDate << ","
            << s.rentalDays << ","
            << s.totalAmount << "\n";
    saleOut.close();
    
    
    ifstream vFileIn(VEHICLE_FILE);
    ofstream vFileOut("temp.txt");
    
    while (vFileIn.good()) {
        Vehicle temp;
        string tempPrice, tempAvail;
        
        getline(vFileIn, temp.id, ',');
        getline(vFileIn, temp.brand, ',');
        getline(vFileIn, temp.model, ',');
        getline(vFileIn, tempPrice, ',');
        getline(vFileIn, tempAvail, '\n');
        
        if (temp.id.empty()) break;
        
        if (temp.id == vehicleId) {
            vFileOut << temp.id << "," << temp.brand << "," << temp.model << "," 
                     << tempPrice << ",0\n";
        } else {
            vFileOut << temp.id << "," << temp.brand << "," << temp.model << "," 
                     << tempPrice << "," << tempAvail << "\n";
        }
    }
    
    vFileIn.close();
    vFileOut.close();
    remove(VEHICLE_FILE.c_str());
    rename("temp.txt", VEHICLE_FILE.c_str());
    
   
    cout << "\n--- Sale Summary ---\n";
    cout << "Sale ID: " << s.saleId << endl;
    cout << "Customer: " << s.customerName << endl;
    cout << "Vehicle: " << v.brand << " " << v.model << endl;
    cout << "Rental Days: " << s.rentalDays << endl;
    cout << "\nSale recorded successfully!\n";
}

void viewSales() {
    ifstream file(SALES_FILE);
    
    if (!file.is_open()) {
        cout << "\nNo sales records found.\n";
        return;
    }
    
    cout << "\n--- All Sales Records ---\n";
    cout << left << setw(10) << "Sale ID"
         << setw(15) << "Vehicle ID"
         << setw(20) << "Customer"
         << setw(15) << "Phone"
         << setw(15) << "Date"
         << setw(10) << "Days" 
         << setw(12) << "Amount" << endl;
         
    cout << "---------------------------------------------------------------------------------------------------\n";
    
    Sale s;
    string saleIdStr, daysStr, amountStr;
    
    while (file.good()) {
        getline(file, saleIdStr, ',');
        getline(file, s.vehicleId, ',');
        getline(file, s.customerName, ',');
        getline(file, s.phoneNumber, ',');
        getline(file, s.rentalDate, ',');
        getline(file, daysStr, ',');
        getline(file, amountStr, '\n');
       
        
        if (saleIdStr.empty()) break;
        
        s.saleId = stoi(saleIdStr);
        s.rentalDays = stoi(daysStr);
        s.totalAmount = stod(amountStr);
        
        cout << left << setw(10) << s.saleId
             << setw(15) << s.vehicleId
             << setw(20) << s.customerName
             << setw(15) << s.phoneNumber
             << setw(15) << s.rentalDate
             << setw(10) << s.rentalDays
             << setw(12) << fixed << setprecision(2) << s.totalAmount << endl;
             
    }
    
    file.close();
}

void manageSalesMenu() {
    int choice;
    
    do {
        cout << "\n------------------------------------" << endl;
        cout << "          SALES MANAGEMENT MENU" << endl;
        cout << "---------------------------------------" << endl;
        cout << "1. Add New Sale" << endl;
        cout << "2. View All Sales" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                addSale();
                break;
            case 2:
                viewSales();
                break;
            case 3:
                cout << "Returning to main menu...\n";
                return;
            default:
                cout << "Invalid choice!\n";
        }
        pause();
    } while(choice != 3);
}


void updateVehicle() {
    string id;
    cout << "\n--- Update Vehicle ---\n";
    
    // First display all vehicles
    displayVehicles();
    
    cout << "\nEnter Vehicle ID to update: ";
    cin >> id;
    
    ifstream fileIn(VEHICLE_FILE);
    if (!fileIn) {
        cout << "No vehicle records found.\n";
        return;
    }
    
    ofstream fileOut("temp.txt");
    string line;
    bool found = false;
    
    while (getline(fileIn, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Vehicle v;
        string priceStr, availStr;
        
        getline(ss, v.id, ',');
        getline(ss, v.brand, ',');
        getline(ss, v.model, ',');
        getline(ss, priceStr, ',');
        getline(ss, availStr, ',');
        
        if (v.id == id) {
            found = true;
            
            cout << "\n--- Current Details ---\n";
            cout << "ID: " << v.id << endl;
            cout << "Brand: " << v.brand << endl;
            cout << "Model: " << v.model << endl;
            cout << "Price Per Day: " << priceStr << endl;
            cout << "Available: " << (availStr == "1" ? "Yes" : "No") << endl;
            
            cout << "\n--- Enter New Details ---\n";
            
            cout << "Enter new Brand (or press Enter to keep current): ";
            cin.ignore();
            string newBrand;
            getline(cin, newBrand);
            if (!newBrand.empty()) v.brand = newBrand;
            
            cout << "Enter new Model (or press Enter to keep current): ";
            string newModel;
            getline(cin, newModel);
            if (!newModel.empty()) v.model = newModel;
            
            cout << "Enter new Price Per Day (or 0 to keep current): ";
            double newPrice;
            cin >> newPrice;
            if (newPrice > 0) {
                priceStr = to_string(newPrice);
            }
            
            cout << "Is vehicle available? (1=Yes, 0=No): ";
            int avail;
            cin >> avail;
            availStr = (avail == 1) ? "1" : "0";
            
            fileOut << v.id << "," << v.brand << "," << v.model << "," 
                    << priceStr << "," << availStr << "\n";
            
            cout << "\nVehicle updated successfully!\n";
        } else {
            fileOut << v.id << "," << v.brand << "," << v.model << "," 
                    << priceStr << "," << availStr << "\n";
        }
    }
    
    fileIn.close();
    fileOut.close();
    remove(VEHICLE_FILE.c_str());
    rename("temp.txt", VEHICLE_FILE.c_str());
    
    if (!found) {
        cout << "Vehicle ID not found.\n";
    }
}







int main () {

	cout << "----- TOUR MATE VEHICLE MANAGEMENT SYSTEM -----\n";

	while (true) {
		if (login()) {
			showMenu();
		} else {
			cout << "Try again.\n";
		}
	}
	return 0;


}