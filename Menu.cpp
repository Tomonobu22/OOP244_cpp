/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;

namespace sdds {
	Utils ut1;
	int x = 0;
	Menu::Menu(const unsigned int options, const char* content) {
		if (options > 15 || content == nullptr || content[0] == '\0') {
			// invalid
			menu_content = nullptr;
			num_options = 0;
		}
		else {
			num_options = options;
			ut1.alocpy(menu_content, content);
		}
	}

	Menu::~Menu() {
		delete[] menu_content;
		menu_content = nullptr;
	}

	unsigned int Menu::run() const{
		unsigned int res;
		cout << menu_content;
		cout << "0- Exit" << endl;
		res = ut1.getint(0, num_options, "> ");
		return res;
	}

}