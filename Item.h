/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"
#include "Status.h"

namespace sdds {
	class Item : public iProduct {
		double price;
		int d_qtyOnHand;
		int d_qtyNeeded;
		char* desc;
		bool flag;
	protected:
		sdds::Status State;
		int sku;
		bool linear() const;
	public:
		Item();
		Item(const Item& it);
		Item& operator=(const Item& it);
		~Item();
		int qtyNeeded()const;
		int qty()const;
		operator double()const;
		virtual operator bool()const;
		int operator-=(int qty);
		int operator+=(int qty);
		void linear(bool isLinear);
		void clear();
		bool operator==(int sku)const;
		bool operator==(const char* description)const;
		std::ofstream& save(std::ofstream& ofstr)const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		int readSku(std::istream& istr);
		std::istream& read(std::istream& istr);
		int validate(int min, int max, std::istream& istr) const; //my own function to validate
		double validate(double min, double max, std::istream& istr) const; //my own function to validate

	};
}

#endif