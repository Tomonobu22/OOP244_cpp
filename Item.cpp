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
#include <fstream>
#include "Item.h"
using namespace std;

namespace sdds {
	bool Item::linear() const {
		return flag;
	}

	Item::Item() {
		price = 0.0;
		d_qtyOnHand = 0;
		d_qtyNeeded = 0;
		desc = nullptr;
		flag = false;
		sku = 0;
	}

	Item::Item(const Item& it) {
		if (it.desc != nullptr) {
			desc = new char[strlen(it.desc) + 1];
			strcpy(desc, it.desc);
		}
		else desc = nullptr;
		price = it.price;
		d_qtyOnHand = it.d_qtyOnHand;
		d_qtyNeeded = it.d_qtyNeeded;
		flag = it.flag;
		sku = it.sku;
	}

	Item& Item::operator=(const Item& it) {
		if (this != &it) {
			if (it.desc != nullptr) {
				delete[] desc;
				desc = nullptr;
				desc = new char[strlen(it.desc) + 1];
				strcpy(desc, it.desc);
				this->price = it.price;
				this->d_qtyOnHand = it.d_qtyOnHand;
				this->d_qtyNeeded = it.d_qtyNeeded;
				this->flag = it.flag;
				this->sku = it.sku;
			}
		}
		else {
			delete[] this->desc;
			this->desc = nullptr;
			this->price = 0.0;
			this->d_qtyOnHand = 0;
			this->d_qtyNeeded = 0;
			this->flag = false;
			this->sku = 0;
		}
		
		return *this;
	}

	Item::~Item() {
		delete[] desc;
		desc = nullptr;
	}

	int Item::qtyNeeded()const {
		return d_qtyNeeded;
	}

	int Item::qty()const {
		return d_qtyOnHand;
	}

	Item::operator double()const {
		return price;
	}

	Item::operator bool()const {
		return State;
	}

	int Item::operator-=(int qty) {
		d_qtyOnHand -= qty;
		return d_qtyOnHand;
	}

	int Item::operator+=(int qty) {
		d_qtyOnHand += qty;
		return d_qtyOnHand;
	}

	void Item::linear(bool isLinear) {
		flag = isLinear;
	}

	void Item::clear() {
		State.clear();
	}

	bool Item::operator==(int sku)const {
		return this->sku == sku;
	}

	bool Item::operator==(const char* description)const {
		return (strstr(desc,description) && desc != nullptr);
	}

	std::ofstream& Item::save(std::ofstream& ofstr)const {
		if (this) {
			ofstr << sku << '\t' << desc << '\t' << d_qtyOnHand << '\t' << d_qtyNeeded << '\t' << price;
		}
		return ofstr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {
		delete[] desc;
		desc = nullptr;

		char spec[400] = {};
		ifstr.get(spec, 100, '\t');
		std::string str(spec);
		if (spec > 0) sku = atoi(spec);
		ifstr.ignore();
		ifstr.get(spec, 400, '\t');
		std::string str1(spec);
		if (spec > 0) {
			desc = new char[strlen(spec) + 1];
			strcpy(desc, spec);
		}
		ifstr.ignore();
		ifstr.get(spec, 100, '\t');
		std::string str2(spec);
		if (spec > 0) d_qtyOnHand = atoi(spec);
		ifstr.ignore();
		ifstr.get(spec, 100, '\t');
		std::string str3(spec);
		if (spec > 0) d_qtyNeeded = atoi(spec);
		ifstr.ignore();
		/*ifstr.get(spec, 100, '\t');
		std::string str4(spec);
		if (spec > 0) price = atof(spec);*/
		ifstr >> price; 
		/*ifstr.ignore();*/

		if (!this) {
			State = "Input file stream read failed!";
		}
		return ifstr;
	}

	std::ostream& Item::display(std::ostream& ostr)const {
		double purchase = price * (double(d_qtyNeeded) - double(d_qtyOnHand));
		char aux[36];
		if (!this) {
			ostr << State;
		}
		else {
			if (desc != nullptr) {
				if (linear()) {
					ostr.width(5);
					ostr << left << sku << " | ";
					if (strlen(desc) > 35) {
						strncpy(aux, desc, 35);
						aux[35] = '\0';
						ostr << aux << " | ";
					}
					else {
						ostr.width(35);
						ostr.fill(' ');
						ostr << left << desc << " | ";
					}
					ostr.width(4);
					ostr.fill(' ');
					ostr << right << d_qtyOnHand << " | ";
					ostr.width(4);
					ostr << right << d_qtyNeeded << " | ";
					ostr.width(7);
					ostr.setf(ios::fixed);
					ostr.precision(2);
					ostr << price << " |";
				}
				else {
					ostr << "AMA Item:" << endl;
					ostr << sku << ": " << desc << endl;
					ostr << "Quantity Needed: " << d_qtyNeeded << endl;
					ostr << "Quantity Available: " << d_qtyOnHand << endl;
					ostr.setf(ios::fixed);
					ostr.precision(2);
					ostr << "Unit Price: $" << price << endl;
					ostr << "Needed Purchase Fund: $" << purchase << endl;
				}
			}
		}
		return ostr;
	}

	int Item::readSku(std::istream& istr) {
		cout << "SKU: ";
		sku = validate(40000,99999,istr);
		return sku;
	}

	std::istream& Item::read(std::istream& istr) {
		char i_desc[100];
		double i_price = -1.0;
		int i_d_qtyOnHand = -1;
		int i_d_qtyNeeded = 0;
		delete[] desc;
		desc = nullptr;
		State.clear();

		cout << "AMA Item:" << endl;
		cout << "SKU: " << sku << endl;
		cout << "Description: ";
		istr.get(i_desc, 100, '\n');
		istr.ignore();
		cout << "Quantity Needed: ";
		i_d_qtyNeeded = validate(1, 9999, istr);
		cout << "Quantity On Hand: ";
		i_d_qtyOnHand = validate(0, i_d_qtyNeeded, istr);
		cout << "Unit Price: $";
		i_price = validate(0.0, 9999.0, istr);
		
		if (i_d_qtyNeeded > 0 && i_d_qtyNeeded < 10000 && i_d_qtyOnHand >= 0 && i_d_qtyOnHand <= i_d_qtyNeeded && price >= 0.0 && price <= 9999.0) {
			desc = new char[strlen(i_desc) + 1];
			strcpy(desc, i_desc);
			price = i_price;
			d_qtyOnHand = i_d_qtyOnHand;
			d_qtyNeeded = i_d_qtyNeeded;
		}
		else {
			State = "Console entry failed!";
		}
		return istr;
	}

	int Item::validate(int min, int max, std::istream& istr) const {
		char input[100];
		int val = -1;
		bool valid;

		while (val < min || val > max) {
			val = -1;
			valid = true;
			istr >> input;
			input[99] = '\0';
			istr.clear();
			istr.ignore(1000, '\n');
			for (unsigned int i = 0; i < strlen(input); i++)
				if (input[i] < 48 || input[i] > 57) valid = false;
			if (valid) val = atoi(input);
			if (val == -1)
				cout << "Invalid Integer, retry: ";
			else if (val < min || val > max) 
				cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
		}
		return val;
	}

	double Item::validate(double min, double max, std::istream& istr) const {
		char input[100];
		double val = -1.0;
		bool valid;

		while (val < min || val > max) {
			val = -1;
			valid = true;
			istr >> input;
			input[99] = '\0';
			istr.clear();
			istr.ignore(1000, '\n');
			for (unsigned int i = 0; i < strlen(input); i++)
				if (input[i] < 46 || input[i] > 57) valid = false;
			if (valid) val = atof(input);
			if (val == -1)
				cout << "Invalid number, retry: ";
			else if (val < min || val > max) {
				cout.precision(2);
				cout.setf(ios::fixed);
				cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
			}
		}
		return val;
	}
}