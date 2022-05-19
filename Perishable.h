/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"

namespace sdds {
	class Perishable : public Item {
		sdds::Date expiryDate;
		char* instructions;
	public:
		Perishable();
		Perishable(const Perishable& prsh);
		Perishable& operator=(const Perishable& prsh);
		~Perishable();
		const Date& expiry() const;
		int readSku(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr)const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
		operator bool()const;
	};
}

#endif