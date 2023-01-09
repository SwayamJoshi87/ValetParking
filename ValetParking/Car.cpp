#include <iostream>
#include "Car.h"
#include "Motorcycle.h"
#include "ReadWritable.h"
#include <cstring>
using namespace std;
namespace sdds
{
    Car::Car()
    {
        this->car_wash = false;
    }

    Car::Car(const char* Lplate, const char* Cmodel) : sdds::Vehicle(Lplate, Cmodel)
    {
        this->car_wash = true;
    }

    Car::Car(const Car& copy) : Vehicle(copy)
    {
        car_wash = copy.car_wash;
    }

    Car& Car::operator=(const Car& assignment)
    {
        (Vehicle&)*this = assignment;
        this->car_wash = assignment.car_wash;
        this->setCsv(assignment.isCsv());
        return *this;
    }
    //
    std::ostream& Car::writeType(std::ostream& os) const
    {
        if (isCsv())
        {
            os << "C,";
        }
        else
        {
            os << "Vehicle type: Car" << std::endl;
        }
        return os;
    }

    std::istream& Car::read(std::istream& in) //Overriding read of parent/base class
    {
        int car;
        int check = false;
        char yesno[5];

        if (isCsv())
        {
            Vehicle::read(in);
            in >> car;
            in.ignore(1000, '\n');
            if (car == 1)
            {
                this->car_wash = true;
            }
            else if (car == 0)
            {
                this->car_wash = false;
            }
        }
        else
        {
            cout << endl;
            cout << "Car information entry" << endl;
            Vehicle::read(in);

            cout << "Carwash while parked? (Y)es/(N)o: ";
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
                        this->car_wash = true;
                        check = true;
                    }
                    else if (toupper(yesno[0]) == 'N')
                    {
                        this->car_wash = false;
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
    // This function overrides the write method of the Vehicle class.
    std::ostream& Car::write(std::ostream& ostr) const
    {
        if (isEmpty())
        {
            ostr << "Invalid Car Object" << endl;
        }
        else
        {
            Vehicle::write(ostr);
            if (isCsv())
            {
                ostr << car_wash << endl;
            }
            else
            {
                if (this->car_wash == true)
                {
                    ostr << "With Carwash" << endl;
                }
                else
                {
                    ostr << "Without Carwash" << endl;
                }
            }
        }
        return ostr;
    }

}