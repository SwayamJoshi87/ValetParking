#ifndef SDDS_CAR_H_
#define SDDS_CAR_H_
#include <iostream>
#define MAX_LICENSE 8
#include "Vehicle.h"
namespace sdds
{

    class Car : public Vehicle
    {
        bool car_wash = false;

    public:
        Car();
        Car(const char* Lplate, const char* Cmodel);
        Car(const Car& copy);
        Car& operator=(const Car& assignment);
        std::istream& read(std::istream& in);
        virtual std::ostream& writeType(std::ostream& os) const;
        std::ostream& write(std::ostream& ostr = std::cout) const;
    };
}

#endif // end of an if statement..