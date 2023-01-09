/* Citation and Sources...
Final Project Milestone 5
Author: Swayam Shaileshbhai Joshi
Student ID: 166456210
Email: sjoshi64@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cstring>
#include "Vehicle.h"
#include "Motorcycle.h"
#include "ReadWritable.h"
using namespace std;
namespace sdds
{
    // Default constructoer
    Motorcycle::Motorcycle()
    {
        this->flag = false;
    }
    // Two argument constructor with licence plate and make model
    Motorcycle::Motorcycle(const char* Lplate, const char* make_model) : sdds::Vehicle(Lplate, make_model)
    {
        this->flag = true;
    }
    // Rule of three 1. Copy constructor
    Motorcycle::Motorcycle(const Motorcycle& copy) : Vehicle(copy)
    {
        this->flag = copy.flag;
    }
    // 2. Copy assignment operator overload
    Motorcycle& Motorcycle::operator=(const Motorcycle& assignment)
    {
        (Vehicle&)*this = assignment;
        this->flag = assignment.flag;
        this->setCsv(assignment.isCsv());
        return *this;
    }
    // Overriding writeType pure virtual function
    std::ostream& Motorcycle::writeType(std::ostream& os) const
    {
        if (isCsv())
        {
            os << "M,";
        }
        else
        {
            os << "Vehicle type: Motorcycle" << endl;
        }
        return os;
    }

    std::istream& Motorcycle::read(std::istream& in)
    {
        char yesno[5];
        bool check = false;
        int motorcycle_Value;
        if (isCsv())
        {

            Vehicle::read(in);
            in >> motorcycle_Value;
            in.ignore(1000, '\n');
            if (motorcycle_Value == 1)
            {
                this->flag = true;
            }
            else if (motorcycle_Value == 0)
            {
                this->flag = false;
            }
        }
        else
        {

            cout << endl << "Motorcycle information entry\n";

            Vehicle::read(in);
            cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
            do
            {
                cin >> yesno;
                if (strlen(yesno) > 1)
                {
                    cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                    in.clear();
                    in.ignore(2000, '\n');
                }
                else
                {
                    if (toupper(yesno[0]) == 'Y')
                    {
                        this->flag = true;
                        check = true;
                    }
                    else if (toupper(yesno[0]) == 'N')
                    {
                        this->flag = false;
                        check = true;
                    }
                    else
                    {
                        cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                        in.clear();
                        in.ignore(1000, '\n');
                    }
                }

            } while (!check);
        }
        return in;
    }

    std::ostream& Motorcycle::write(std::ostream& ostr) const
    {
        if (isEmpty())
        {
            ostr << "Invalid Motorcycle Object" << endl;
        }
        else
        {
            Vehicle::write(ostr);
            if (isCsv())
            {
                ostr << this->flag << endl;
            }
            else
            {
                if (this->flag == true) {
                    ostr << "With Sidecar" << endl;
                }

            }
        }
        return ostr;
    }
}