/* Citation and Sources...
Final Project Milestone 5
Author: Swayam Shaileshbhai Joshi
Student ID: 166456210
Email: sjoshi64@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef _MOTORCYCYLE_H_
#define _MOTORCYCLE_H_
#include <iostream>
#include "Vehicle.h"

namespace sdds
{

    class Motorcycle : public Vehicle
    {
        bool flag = false;

    public:
        Motorcycle();
        Motorcycle(const char* Lplate, const char* make_model);
        Motorcycle(const Motorcycle& copy);
        Motorcycle& operator=(const Motorcycle& assignment);
        virtual std::ostream& writeType(std::ostream& os) const;
        std::istream& read(std::istream& in);
        std::ostream& write(std::ostream& ostr = std::cout) const;
    };
}

#endif