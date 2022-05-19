/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/

#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {
	class Menu {
		char* menu_content = nullptr;
		unsigned int num_options = 0;
	public:
		Menu(const unsigned int options = 0, const char* content = nullptr);
		// Menu can not be copied to another Menu -- Menu(const Menu& m2);
		// Menu can not be assigned to another Menu -- Menu& operator=(const Menu& m2);
		~Menu();
		unsigned int run() const;
	};
}

#endif