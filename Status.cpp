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
#include "Status.h"
using namespace std;

namespace sdds {

	void Status::allocateAndCopy(const char* e_desc) {
		delete[] desc;
		desc = nullptr;
		desc = new char[strlen(e_desc) + 1];
		strcpy(desc, e_desc);
	}


	Status::Status(const char* e_desc) {
		if (e_desc != nullptr) {
			desc = new char[strlen(e_desc) + 1];
			strcpy(desc, e_desc);
		}
		else desc = nullptr;
		statusCode = 0;
	}

	Status::Status(const Status& st) {
		if (st.desc != nullptr) {
			desc = new char[strlen(st.desc) + 1];
			strcpy(desc, st.desc);
		}
		else desc = nullptr;
		statusCode = st.statusCode;
	}

	Status& Status::operator=(const Status& st) {
		if (this != &st) {
			if (st.desc != nullptr) {
				allocateAndCopy(st.desc);
				this->statusCode = st.statusCode;
			}
		}
		else {
			delete[] this->desc;
			this->desc = nullptr;
			this->statusCode = 0;
		}
		return *this;
	}

	Status& Status::operator=(const char* e_desc) {
		delete[] desc;
		if (e_desc != nullptr) allocateAndCopy(e_desc);
		else desc = nullptr;
		return *this;
	}

	Status& Status::operator=(const int e_statusCode) {
		if (e_statusCode != 0) statusCode = e_statusCode;
		else statusCode = 0;
		return *this;
	}

	Status::~Status() {
		delete[] desc;
		desc = nullptr;
	}

	Status::operator int() const {
		return statusCode;
	}

	Status::operator char* () const {
		return desc;
	}

	Status::operator bool() const {
		return desc == nullptr;
	}

	void Status::clear() {
		delete[] desc;
		desc = nullptr;
		statusCode = 0;
	}

	std::ostream& Status::print(std::ostream& ostr) const {
		if(statusCode != 0) ostr << "ERR#" << statusCode << ": " << desc;
		else {
			if (desc != nullptr) ostr << desc;
		}
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Status& st) {
		if (!bool(st)) st.print(ostr);
		else ostr << "Invalid date value";
		return ostr;
	}
}