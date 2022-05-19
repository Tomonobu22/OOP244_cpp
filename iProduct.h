/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/

#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H
namespace sdds {
	class iProduct {
	public:
		virtual int readSku(std::istream& istr) = 0; // main data entry
		virtual int operator-=(int qty) = 0; // to reduce the quantity on hand
		virtual int operator+=(int qty) = 0; // to increase the quantity on hand
		virtual operator double()const = 0; // returns the price of the produce
		virtual operator bool()const = 0; // returns if the iProduct is in a good state
		virtual int qtyNeeded()const = 0; // returns the number of products needed
		virtual int qty()const = 0; // retuns the quantity on hand
		virtual void linear(bool isLinear) = 0; // determines if the iProduct is displayed in a linear format or descriptive format
		virtual std::ofstream& save(std::ofstream& ofstr)const = 0; // saves the iProduct into a file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0; // loads an iProduct from a file
		virtual std::ostream& display(std::ostream& ostr)const = 0; // displays the iProduct on the screen
		virtual std::istream& read(std::istream& istr) = 0; // reads the iProduct from the console
		virtual bool operator==(int sku)const = 0; // return true if the sku is a match to the iProduct's sku
		virtual bool operator==(const char* description)const = 0; // returns true if the description is found in the iPorduct's description
		virtual ~iProduct() {};
	};

	std::ostream& operator<<(std::ostream& ostr, const iProduct& ip);
	std::istream& operator>>(std::istream& istr, iProduct& ip);
}

#endif