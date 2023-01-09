/* Citation and Sources...
Final Project Milestone 1
Module: Menu.h
Filename: Menu.cpp
Version 1.0
Author:	Swayam Shaileshbhai Joshi
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
//#include "Utils.h"
#include <cstring>

using namespace std;

namespace sdds
{
	void Menu::indentCreator()const
	{

		for (int j = 0; j < this->spaceIndent; j++)
		{

			cout << "    ";

		}

	}

	MenuItem::MenuItem()
	{

		this->cstring[0] = '\0';

	}

	MenuItem::MenuItem(const char* cstr)
	{

		if (cstr == nullptr)
			this->cstring[0] = '\0';

		else
		{

			if (strlen(cstr) > 50)
			{
				strncpy(this->cstring, cstr, 50);
			}
			else
				strcpy(this->cstring, cstr);
		}
	}

	ostream& MenuItem::display(ostream& ostr) const
	{
		if (this->cstring[0] != '\0')
		{
			ostr << this->cstring << endl;
		}

		return ostr;
	}

	Menu::Menu()
	{
		this->title[0] = '\0';
		this->spaceIndent = 0;
		this->numCounter = 0;
	}

	Menu::Menu(const char* cstr, int num)
	{
		if (cstr == nullptr)
		{
			this->title[0] = '\0';
			this->spaceIndent = 0;
			this->numCounter = 0;
		}

		else
		{
			this->spaceIndent = num;
			this->numCounter = 0;
			if (strlen(cstr) > 50)
			{
				strncpy(this->title, cstr, 50);
			}
			else

				strcpy(this->title, cstr);
		}
	}

	Menu::operator bool() const
	{
		return this->title[0] != '\0';
	}

	bool Menu::isEmpty() const
	{
		return this->title[0] == '\0';
	}

	ostream& Menu::display(ostream& ostr) const
	{
		if (isEmpty())
			ostr << "Invalid Menu!" << endl;

		else
		{

			Menu::indentCreator();
			ostr << this->title << endl;

			bool verify = false;
			for (int i = 0; i < this->numCounter; i++)
			{
				if (this->mItem[i].cstring[0] == '\0')
				{
					verify = true;
					break;
				}
			}
			if (verify)
			{
				ostr << "No Items to display!" << endl;
			}
			else
			{
				for (int i = 0; i < this->numCounter; i++)
				{

					Menu::indentCreator();
					ostr << i + 1 << "- ";
					this->mItem[i].display();
				}


				Menu::indentCreator();
				ostr << "> ";
			}

		}

		return ostr;
	}

	Menu& Menu::operator=(const char* cstr)
	{
		if (cstr == nullptr)
			this->title[0] = '\0';

		else
		{
			if (strlen(cstr) > 50)
			{
				strncpy(this->title, cstr, 50);
			}
			else
				strcpy(this->title, cstr);
		}

		return *this;
	}

	void Menu::add(const char* cstr)
	{
		if (cstr == nullptr)
		{
			for (int i = 0; i < this->numCounter; i++)
			{
				this->mItem[i].cstring[0] = '\0';
			}
			this->title[0] = '\0';
		}

		else
		{
			if (this->numCounter < MAX_NO_OF_ITEMS && bool(*this))
			{
				if (strlen(cstr) > 50)
				{
					strncpy(this->mItem[this->numCounter].cstring, cstr, 50);
					this->numCounter++;
				}
				else
				{
					strcpy(this->mItem[this->numCounter].cstring, cstr);
					this->numCounter++;
				}
			}
		}
	}

	Menu& Menu::operator<<(const char* cstr)
	{
		Menu::add(cstr);

		return *this;
	}

	int Menu::run() const
	{
		int num = 0;
		bool verify = true;

		Menu::display();
		if (this->mItem[0].cstring[0] == '\0' || isEmpty())
		{
			return 0;
		}
		else
		{
			while (verify)
			{
				cin >> num;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Integer, try again: ";
				}
				else if ((num > this->numCounter || num < 1))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid choice, try again: ";
				}
				else
				{
					cin.ignore(1000, '\n');
					verify = false;
				}

			}
		}

		return num;
	}

	void Menu::clear()
	{
		this->title[0] = '\0';
		for (int i = 0; i < this->numCounter; i++)
		{
			this->mItem[i].cstring[0] = '\0';
		}
		this->spaceIndent = 0;
	}

	Menu::operator int() const
	{
		return this->run();
	}
}
