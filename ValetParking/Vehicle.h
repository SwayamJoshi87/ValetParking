/* Citation and Sources...
Final Project Milestone 5
Author: Swayam Shaileshbhai Joshi
Student ID: 166456210
Email: sjoshi64@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_VEHICLE_H_
#define SDDS_VEHICLE_H_

#include "ReadWritable.h"
#include "Utils.h"

const int MAX_LENGTH = 8;

namespace sdds
{
    class Vehicle : public ReadWritable
    {

        char lplate[MAX_LENGTH + 1];
        char* m_model;
        int pkspot;

    protected:
        void setEmpty();
        bool isEmpty() const;
        const char* getLicensePlate();
        const char* getMakeModel();
        void setMakeModel(const char* makeModel);

    public:
        Vehicle();
        Vehicle(const char* plate, const char* makeModel, int spotNum = 0);
        Vehicle(const Vehicle& copy);
        Vehicle& operator=(const Vehicle& assignment);
        int getParkingSpot() const;
        void setParkingSpot(int spotNum);
        friend bool operator==(Vehicle& v, const char* plate);
        friend bool operator==(Vehicle& v1, Vehicle& v2);
        virtual std::istream& read(std::istream& in = std::cin);
        virtual std::ostream& writeType(std::ostream& os) const = 0;
        virtual std::ostream& write(std::ostream& ostr = std::cout) const;
        virtual ~Vehicle();
    };

}
#endif //! SDDS_VEHICLE_H_