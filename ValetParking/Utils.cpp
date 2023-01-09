/* Final Project Milestone 5
Version 3.0
Author	Swayam Shaileshbhai Joshi
Revision History
-----------------------------------------------------------
Date: 2022/12/08
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include "Utils.h"

namespace sdds
{
    char* toUpper(char* str)
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            str[i] = toupper(str[i]);
        }

        return str;
    }

    bool strICmp(const char* str1, const char* str2)
    {
        bool answer = false;

        int sz1 = strlen(str1);
        int sz2 = strlen(str2);
        if (sz1 == sz2)
        {
            char* temp1 = new char[sz1 + 1];
            strcpy(temp1, str1);
            toUpper(temp1);
            char* temp2 = new char[sz1 + 1];
            strcpy(temp2, str2);
            toUpper(temp2);
            if (strcmp(temp1, temp2) == 0)
            {
                answer = true;
            }
            delete[] temp1;
            temp1 = nullptr;
            delete[] temp2;
            temp2 = nullptr;
        }

        return answer;
    }

    void strncpy(char* des, const char* src, int len)
    {
        int i;
        for (i = 0; src[i] && (len < 0 || i < len); i++) {
            des[i] = src[i];
        }
        des[i] = 0; // turning the char array des in to a cString by null terminating it.
    }
    bool choice()
    {
        std::string choice;
        bool answer, check;
        do {
            check = true;
            std::cin >> choice;
            std::cin.ignore(1000, '\n');

            if (choice == "Y" || choice == "y") {
                answer = true;
            }
            else if (choice == "N" || choice == "n") {
                answer = false;
            }
            else {
                std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                check = false;
                std::cin.clear();
            }
        } while (!check);

        return answer;
    }
        
    
}