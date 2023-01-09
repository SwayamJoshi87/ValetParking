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

namespace sdds
{

    void Vehicle::setEmpty()
    {
        lplate[0] = '\0';
        m_model = nullptr;
        pkspot = 0;
    }

    bool Vehicle::isEmpty() const //Returning check of vehicle
    {
        return lplate[0] == '\0' || m_model == nullptr;
    }

    const char* Vehicle::getLicensePlate()
    {
        return lplate;
    }

    const char* Vehicle::getMakeModel()
    {
        return m_model;
    }

    void Vehicle::setMakeModel(const char* makeModel)
    {
        if (makeModel != nullptr && makeModel[0] != '\0' && strlen(makeModel) >= 2)
        {
            int sze = strlen(makeModel) + 1;

            delete[] m_model;
            m_model = new char[sze];
            strcpy(m_model, makeModel);
        }
        else
        {
            delete[] m_model;
            setEmpty();
        }
    }

    Vehicle::Vehicle() : ReadWritable()
    {
        setEmpty();
    }

    Vehicle::Vehicle(const char* plate, const char* makeModel, int spotNum) : ReadWritable()
    {
        setEmpty();
        if (plate != nullptr && plate[0] != '\0' && strlen(plate) <= MAX_LENGTH)
        {
            strncpy(lplate, plate, MAX_LENGTH);
            lplate[MAX_LENGTH] = '\0';
            toUpper(lplate);
        }
        else
        {
            lplate[0] = '\0';
        }
        setMakeModel(makeModel);
        setParkingSpot(spotNum);
    }

    int Vehicle::getParkingSpot() const
    {
        return pkspot;
    }

    void Vehicle::setParkingSpot(int spotNum)
    {
        if (spotNum >= 0)
        {
            pkspot = spotNum;
        }
        else
        {
            delete[] m_model;
            setEmpty();
        }
    }

    bool operator==(Vehicle& v, const char* plate) //Object to string comparison
    {
        bool same = false;
        if (!v.isEmpty())
        {
            if (plate != nullptr && plate[0] != '\0' && strlen(plate) <= MAX_LENGTH)
            {
                if (strICmp(v.lplate, plate))
                {
                    same = true;
                }
            }
        }

        return same;
    }

    bool operator==(Vehicle& v1, Vehicle& v2) //Object to object comparison 
    {
        bool same = false;
        if (!v1.isEmpty() && !v2.isEmpty())
        {
            if (strICmp(v1.lplate, v2.lplate))
            {
                same = true;
            }
        }

        return same;
    }
    // This function overrides the Read of the ReadWritable class.

    std::istream& Vehicle::read(std::istream& istr)
    {
        if (isCsv())
        {
            istr >> pkspot;
            istr.ignore();
            istr.getline(lplate, MAX_LENGTH + 1, ',');
            toUpper(lplate);
            char temp[60 + 1] = { '\0' };
            istr.getline(temp, 60 + 1, ',');
            setMakeModel(temp);
        }
        else
        {
            std::cout << "Enter License Plate Number: ";
            int check;
            do
            {
                check = 0;
                istr >> lplate;
                istr.ignore();
                if (strlen(lplate) > 8)
                {
                    check = 1;
                    std::cout << "Invalid License Plate, try again: ";
                }
            } while (check);
            toUpper(lplate);

            std::cout << "Enter Make and Model: ";
            char temp[60 + 1] = { '\0' };
            do
            {
                check = 0;
                istr.getline(temp, 60 + 1);
                if (strlen(temp) < 2 || strlen(temp) > 60)
                {
                    check = 1;
                    std::cout << "Invalid Make and model, try again: ";
                }
            } while (check);
            setMakeModel(temp);

            pkspot = 0;
        }

        if (istr.fail())
        {
            istr.clear();
            setEmpty();
        }

        return istr;
    }
    // If the Vehicle is in an check empty check, this function will write the following message using the ostream object and returns it.
    std::ostream& Vehicle::write(std::ostream& ostr) const
    {
        if (isEmpty())
        {
            ostr << "Invalid Vehicle Object" << std::endl;
        }
        else
        {
            writeType(ostr);

            if (isCsv())
            {
                ostr << pkspot << "," << lplate << "," << m_model << ",";
            }
            else
            {
                ostr << "Parking Spot Number: ";
                if (pkspot <= 0)
                {
                    ostr << "N/A" << std::endl;
                }
                else
                {
                    ostr << pkspot << std::endl;
                }
                ostr << "License Plate: " << lplate << std::endl;
                ostr << "Make and Model: " << m_model << std::endl;
            }
        }

        return ostr;
    }
    // This function safely deallocates any memory which was allocated, in other to prevent memeory leaks.
    Vehicle::~Vehicle()
    {
        delete[] m_model;
        m_model = nullptr;
    }
    // a Vehicle is copied to another vehicle safely.
    Vehicle::Vehicle(const Vehicle& copy)
    {
        setParkingSpot(copy.pkspot);
        strcpy(this->lplate, copy.lplate);

        // deep copying
        if (copy.m_model != nullptr)
        {

            m_model = new char[strlen(copy.m_model) + 1];
            strcpy(this->m_model, copy.m_model);
        }
        else
        {
            this->m_model = nullptr;
        }
    }
    // a Vehicle is assigned to another vehicle safely and also make sure there is no memory leach when going out of scope or deleted.
    Vehicle& Vehicle::operator=(const Vehicle& assignment)
    {
        setParkingSpot(assignment.pkspot);
        strcpy(this->lplate, assignment.lplate);
        this->setCsv(assignment.isCsv());
        if (this->m_model)
        {
            delete[] m_model;
            m_model = nullptr;
        }
        // deep copying
        if (assignment.m_model != nullptr)
        {
            m_model = new char[strlen(assignment.m_model) + 1];
            strcpy(this->m_model, assignment.m_model);
        }
        else
        {
            this->m_model = nullptr;
        }
        return *this;
    }

}