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
#include "Perishable.h"
#include "Date.h"
#include "Status.h"
using namespace std;

namespace sdds {
	Perishable::Perishable() : Item() {
		instructions = nullptr;
	}

	Perishable::Perishable(const Perishable& prsh) : Item(prsh) {
		if (prsh.instructions != nullptr) {
			instructions = new char[strlen(prsh.instructions) + 1];
			strcpy(instructions, prsh.instructions);
		}
		else instructions = nullptr;

		if (prsh.expiryDate) expiryDate = prsh.expiryDate;
		else expiryDate = Date(0, 0, 0);
	}

	Perishable& Perishable::operator=(const Perishable& prsh) {
		delete[] instructions;
		instructions = nullptr;
		Item::operator=(prsh);
		if (this != &prsh) {
			if (prsh.instructions != nullptr) {
				instructions = new char[strlen(prsh.instructions) + 1];
				strcpy(instructions, prsh.instructions);
			}
			if (prsh.expiryDate) expiryDate = prsh.expiryDate;
			else expiryDate = Date(0, 0, 0);
		}
		return *this;
	}

	Perishable::~Perishable() {
		delete[] instructions;
		instructions = nullptr;
	}

	const Date& Perishable::expiry() const {
		return expiryDate;
	}

	int Perishable::readSku(std::istream& istr) {
		cout << "SKU: ";
		sku = Item::validate(10000, 39999, istr);
		return sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr)const {
		Item::save(ofstr);
		ofstr << '\t';
		if (instructions != nullptr && instructions[0] != '\0') ofstr << instructions;
		ofstr << '\t';
		expiryDate.write(ofstr,false);

		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		Item::load(ifstr);
		ifstr.ignore(10, '\t');
		delete[] instructions;
 		instructions = nullptr;

		char spec[400] = {};
		ifstr.get(spec, 400, '\t');
		std::string str1(spec);
		if (spec[0] != '\0') {
			instructions = new char[strlen(spec) + 1];
			strcpy(instructions, spec);
		}
		else {
			ifstr.clear();
		}
		ifstr.ignore();
		expiryDate.read(ifstr);
		ifstr.ignore();

		if (!this) {
			State = "Input file stream read (perishable) failed!";
		}
		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr)const {
		if (!Perishable::operator bool()) ostr << State;
		else {
			if (Item::linear()) {
				Item::display(ostr);
				if (instructions != nullptr && instructions[0] != '\0') ostr << '*';
				else ostr << ' ';
				expiryDate.write(ostr);
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";
				expiryDate.write(ostr);
				if (instructions != nullptr && instructions[0] != '\0') {
					ostr << endl;
					ostr << "Handling Instructions: " << instructions;
				}
				ostr << endl;
			}
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		char i_per[200];
		char p;
		delete[] instructions;
		instructions = nullptr;
		cout << "Expiry date (YYMMDD): ";
		expiryDate.read(istr);
		istr.ignore();
		cout << "Handling Instructions, ENTER to skip: ";
		p = istr.peek();
		if (p != '\n') {
			istr.get(i_per, 200, '\n');
			instructions = new char[strlen(i_per) + 1];
			strcpy(instructions, i_per);
		}
		if (!istr) {
			cout << "Perishable console date entry failed!";
			delete[] instructions;
			instructions = nullptr;
		}

		return istr;
	}

	Perishable::operator bool()const {
		return expiryDate;
	}
}