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
#include "iProduct.h"
using namespace std;

namespace sdds {
	std::ostream& operator<<(std::ostream& ostr, const iProduct& ip) {
		return ip.display(ostr);
	}
	
	std::istream& operator>>(std::istream& istr, iProduct& ip) {
		return ip.read(istr);
	}
}