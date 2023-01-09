/* Citation and Sources...
Final Project Milestone 5
Author: Swayam Shaileshbhai Joshi
Student ID: 166456210
Email: sjoshi64@myseneca.ca
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_

namespace sdds
{
    char* toUpper(char* str);
    bool strICmp(const char* str1, const char* str2);
    void strncpy(char* des, const char* src, int len);
    bool choice();
}
#endif //! SDDS_UTILS_H__