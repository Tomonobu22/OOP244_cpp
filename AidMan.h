/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/

#include "Menu.h"
#include "iProduct.h"
#include "Date.h"
#include "Perishable.h"
#include "Utils.h"
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
const int sdds_max_num_items = 100;
namespace sdds {
	const char List[] = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n";
	const unsigned int opt = 7;

	class AidMan {
		char* fileName; //name of a data file holding the aid and product information
		sdds::iProduct* products[sdds_max_num_items] = {};
		int nProductItems = 0;
		Menu a_menu = { opt, List };
		unsigned int menu() const;
	public:
		AidMan();
		~AidMan();
		void run();
		std::ofstream& save(std::ofstream& ofstr) const;
		void deallocate();
		std::ifstream& load(std::ifstream& ifstr);
		int list(const char* sub_desc = nullptr);
	};
}

#endif