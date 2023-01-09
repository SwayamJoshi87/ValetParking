#ifndef _READWRITEABLE_H_
#define _READWRITEABLE_H_
#include <iostream>

namespace sdds
{

    class ReadWritable
    {
        bool value = false;

    public:
        ReadWritable();
        virtual ~ReadWritable();
        bool isCsv() const;
        void setCsv(bool value);
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
    };
    std::ostream& operator<<(std::ostream& ostr, const ReadWritable& writable);
    std::istream& operator>>(std::istream& in, ReadWritable& readable);
}

#endif // end of an if statement..