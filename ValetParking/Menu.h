/* Citation and Sources...
Final Project Milestone 1
Module: Menu.h
Filename: Menu.cpp
Version 1.0
Author:	Swayam Shaileshbhai Joshi
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_Menu
#define SDDS_Menu

namespace sdds
{
	const int MAX_NO_OF_ITEMS = 10;

	class Menu;

	class MenuItem
	{
		friend class Menu;
		char cstring[51];

		//member function
		MenuItem();
		MenuItem(const char* cstr);
		MenuItem(const MenuItem&) = delete;
		void operator=(const MenuItem&) = delete;
		std::ostream& display(std::ostream& ostr = std::cout)const;
	};

	class Menu
	{
		char title[51];
		int numCounter;
		MenuItem mItem[MAX_NO_OF_ITEMS];

	public:
		int spaceIndent;
		Menu();
		Menu(const char* cstr, int num = 0);


		operator int()const;
		operator bool()const;

		Menu(const Menu&) = delete;

		bool isEmpty()const;

		std::ostream& display(std::ostream& ostr = std::cout)const;

		Menu& operator=(const char* cstr);

		void add(const char* cstr);

		Menu& operator<<(const char* cstr);

		int run()const;

		void clear();


		void indentCreator()const;
	};
}
#endif