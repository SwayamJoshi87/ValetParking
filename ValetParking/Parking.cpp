/* Citation and Sources...
Final Project Milestone 2
Author: Swayam Shaileshbhai Joshi
Student ID: 166456210
Email: sjoshi64@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Parking.h"

using namespace std;

namespace sdds {
	Parking::Parking() {
		this->setEmpty();
	}

	Parking::Parking(const char* datafile, int nSpots) {
		this->setEmpty();
		setFileName(datafile);
		if (nSpots >= 10 && nSpots <= MAXPKSPOTS) {
			numSpots = nSpots;
		}
		else {
			numSpots = 0;
		}

		if (loadFile()) {
			menuItem = "Parking Menu, select an action:";
			menuItem << "Park Vehicle"
				<< "Return Vehicle"
				<< "List Parked Vehicles"
				<< "Find Vehicle"
				<< "Close Parking (End of day)"
				<< "Exit Program";
			menuItem2 = "Select type of the vehicle:";
			menuItem2 << "Car" << "Motorcycle" << "Cancel";
			menuItem2.spaceIndent = 1;
		}
		else {
			cout << "Error in data file" << endl;
			this->setEmpty();
		}
	}

	void Parking::setFileName(const char* datafile) {
		if (datafile != nullptr && datafile[0] != '\0') {
			int size = strlen(datafile) + 1;
			dataFile = new char[size];
			strcpy(dataFile, datafile);
		}
		else {
			dataFile = nullptr;
		}
	}

	void Parking::setEmpty() {
		setFileName(nullptr);
		menuItem = nullptr;
		menuItem2 = nullptr;
		numSpots = 0;
		for (int i = 0; i < MAXPKSPOTS; i++) {
			spots[i] = nullptr;
		}
		parkedVehicles = 0;
	}

	bool Parking::isEmpty() const {
		return dataFile == nullptr;
	}

	void Parking::parkingStatus() const {
		cout << "****** Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout.width(4);
		cout.setf(ios::left);
		cout << numSpots - parkedVehicles << " *****" << endl;
		cout.unsetf(ios::left);
	}

	void Parking::parkVehicle() {
		if (numSpots == parkedVehicles) {
			cout << "Parking is full" << endl;
		}
		else {
			int choice = menuItem2.run();
			if (choice == 3) {
				cout << "Parking cancelled" << endl;
			}
			else {
				Vehicle* _vehicle = nullptr;
				if (choice == 1) {
					_vehicle = new Car();
				}
				else if (choice == 2) {
					_vehicle = new Motorcycle();
				}

				_vehicle->setCsv(false);
				cin >> *_vehicle;

				bool valid = true;
				for (int i = 0; i < numSpots && valid; i++) {
					if (spots[i] != nullptr && *spots[i] == *_vehicle) {
						cout << "\nCan not park; license plate already in the system!" << endl;
						cout << *_vehicle;
						cout << endl;
						valid = false;
					}
				}
				if (valid && parkedVehicles < numSpots) {
					for (int i = 0; i < numSpots && valid; i++) {
						if (spots[i] == nullptr) {
							spots[i] = _vehicle;
							spots[i]->setParkingSpot(i + 1);
							cout << "\nParking Ticket" << endl;
							cout << *spots[i];
							cout << endl;
							parkedVehicles++;
							valid = false;
						}
					}
				}
				cout << "Press <ENTER> to continue...." << endl;
			}
		}
	}

	void Parking::returnVehicle() {
		cout << "Return Vehicle" << endl;
		char plate[MAX_LENGTH + 1] = { '\0' };
		bool check;
		cout << "Enter License Plate Number: ";
		do {
			check = false;
			cin >> plate;
			cin.ignore();
			if (strlen(plate) < 1 || strlen(plate) > 8) {
				cout << "Invalid License Plate, try again: ";
				check = true;
			}
		} while (check);
		toUpper(plate);

		bool flag = true;
		for (int i = 0; i < numSpots && flag; i++) {
			if (spots[i] != nullptr && *spots[i] == plate) {
				cout << "\nReturning:" << endl;
				spots[i]->setCsv(false);
				cout << *spots[i];
				cout << endl;
				delete spots[i];
				spots[i] = nullptr;
				parkedVehicles--;
				flag = false;
			}
		}

		if (flag) {
			cout << "\nLicense plate " << plate << " Not found\n" << endl;
		}
		cout << "Press <ENTER> to continue...." << endl;
	}

	void Parking::listVehicle() const {
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < numSpots; i++) {
			if (spots[i] != nullptr) {
				spots[i]->setCsv(false);
				cout << *spots[i];
				cout << "-------------------------------" << endl;
			}
		}
		cout << "Press <ENTER> to continue...." << endl;
	}

	bool Parking::closeParking() {
		bool isClosed = false;
		if (parkedVehicles == 0) {
			cout << "Closing Parking" << endl;
			isClosed = true;
		}
		else {
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			if (choice()) {
				cout << "Closing Parking" << endl;
				for (int i = 0; i < numSpots; i++) {
					if (spots[i] != nullptr) {
						cout << endl << "Towing request" << endl;
						cout << "*********************" << endl;
						spots[i]->setCsv(false);
						cout << *spots[i];
						delete spots[i];
						spots[i] = nullptr;
						parkedVehicles--;
					}
				}
				saveFile();
				isClosed = true;
			}
			else {

				isClosed = false;
			}
		}

		return isClosed;
	}

	bool Parking::exitApplication() const {
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		bool answer = choice();
		if (answer) {
			saveFile();
		}

		return answer;
	}

	bool Parking::loadFile() {
		bool check = true;
		ifstream fin;
		if (!isEmpty()) {
			fin.open(dataFile);
		}

		char readChar;
		Vehicle* _vehicle;
		parkedVehicles = 0;

		while (parkedVehicles < numSpots && check && fin) {
			readChar = 's';  //Some random character
			_vehicle = nullptr;
			fin >> readChar;
			fin.ignore();
			if (readChar == 'C') {
				_vehicle = new Car();
			}
			else if (readChar == 'M') {
				_vehicle = new Motorcycle();
			}

			if (_vehicle) {
				_vehicle->setCsv(true);
				fin >> *_vehicle;
				if (fin) {
					spots[_vehicle->getParkingSpot() - 1] = _vehicle;
					parkedVehicles++;
				}
				else {
					delete _vehicle;
					_vehicle = nullptr;
					check = false;
				}
			}
		}

		return check;
	}

	void Parking::saveFile() const {
		if (!isEmpty()) {
			ofstream fout(dataFile);
			if (fout) {
				for (int i = 0; i < numSpots; i++) {
					if (spots[i] != nullptr) {
						spots[i]->setCsv(true);
						fout << *spots[i];
					}
				}
			}
		}
	}

	void Parking::findVehicle()
	{

		cout << "Vehicle Search" << endl;
		char plate[MAX_LENGTH + 1] = { '\0' };
		bool check;
		cout << "Enter License Plate Number: ";
		do {
			check = false;
			cin >> plate;
			cin.ignore();
			if (strlen(plate) < 1 || strlen(plate) > 8) {
				cout << "Invalid License Plate, try again: ";
				check = true;
			}
		} while (check);
		toUpper(plate);

		bool flag = true;
		for (int i = 0; i < numSpots && flag; i++) {
			if (spots[i] != nullptr && *spots[i] == plate) {
				cout << "\nVehicle found:";
				spots[i]->setCsv(false);
				cout << endl << *spots[i];
				spots[i]->setCsv(true);
				flag = false;
				cout << endl << "Press <ENTER> to continue...." << endl;
			}
		}
		if (flag)
		{
			cout << "\nLicense plate " << plate << " Not found" << endl;
			cout << endl << "Press <ENTER> to continue...." << endl;
		}
	}

	int Parking::run() {
		int answer = 1;
		if (!isEmpty()) {
			answer = 0;
			int option, flag;
			do
			{
				parkingStatus();
				flag = 1;
				option = menuItem.run();

				switch (option)
				{
				case 1:
					parkVehicle();
					
					break;
				case 2:
					returnVehicle();
					
					break;
				case 3:
					listVehicle();
					break;
				case 4:
					findVehicle();
					break;
				case 5:
					if (closeParking()) {
						flag = 0;
					}
					break;
				case 6:
					if (exitApplication()) {
						cout << "Exiting program!" << endl;
						flag = 0;
					}
					break;
				}
			} while (flag);
		}

		return answer;
	}

	Parking::~Parking() {
		saveFile();
		delete[] dataFile;
		dataFile = nullptr;

		for (int i = 0; i < MAXPKSPOTS; i++) {		// delete spots[i]
			delete spots[i];
			spots[i] = nullptr;
		}
	}
}