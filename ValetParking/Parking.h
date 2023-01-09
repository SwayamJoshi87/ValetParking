/* Citation and Sources...
Final Project Milestone 5
Author: Swayam Shaileshbhai Joshi
Student ID: 166456210
Email: sjoshi64@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__

#include "Menu.h"
#include "Car.h"
#include "Motorcycle.h"

const int MAXPKSPOTS = 100;

namespace sdds {
	class Parking : public Menu {
		
		char* dataFile; //To store the filename that has to be opened
		Menu menuItem;
		Menu menuItem2;
		int numSpots;
		Vehicle* spots[MAXPKSPOTS];
		int parkedVehicles;

		void setEmpty();
		bool isEmpty() const;								//Check is the class is empty
		void parkingStatus() const;							//Shows status of the parking
		void parkVehicle();									//Parks the vehicle by creating a new object
		void returnVehicle();								//Returns a parked vehicle
		void listVehicle() const;							//Lists the Vehicles
		bool closeParking();								//Closes the parking
		bool exitApplication() const;						//Exits the program
		bool loadFile();									//Loads the data from the fiile
		void saveFile() const;								//Saves the data into the file
		void findVehicle();									//Finds a vehicles by number plate
	public:
		using Menu::Menu;

		Parking();										//Default constructor
		Parking(const char* datafile, int nSpots);		//One argument constructor
		Parking(const Parking&) = delete;				
		Parking& operator=(const Parking&) = delete;	//Removes the capability of copying one parking item to another
		int run();
		void setFileName(const char* filename);			//Sets the filename to the given name
		~Parking();										//Destructor
	};
}
#endif