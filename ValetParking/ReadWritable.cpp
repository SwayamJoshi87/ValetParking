#include <iostream>
#include "ReadWritable.h"
#include "Vehicle.h"

using namespace std;
namespace sdds
{


    ReadWritable::ReadWritable()
    {
        this->value = false;
    }

    ReadWritable::~ReadWritable() {}; // Empty destructor because there are no dynamic variables

    bool ReadWritable::isCsv() const
    {
        return this->value;
    }

    void ReadWritable::setCsv(bool value)
    {

        this->value = value;
    }
    // Insertion opeartor overload to write
    std::ostream& operator<<(std::ostream& ostr, const ReadWritable& writable)
    {
        if (ostr)
        {
            writable.write(ostr);
        }
        return ostr;
    }
    // Extraction operator overload to read
    std::istream& operator>>(std::istream& in, ReadWritable& readable)
    {
        return (readable.read(in));
    }
}