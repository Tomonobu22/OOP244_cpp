/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Status.h"

namespace sdds {
	const int maximumYearValue = 2030;
	class Date {
		int Year=0;
		int Month=0;
		int Day=0;
		sdds::Status State;
		bool Formatted = true;
		bool validate();
		int unique() const;
	public:
		Date(const int e_year = 0, const int e_month = 0, const int e_day = 0);
		Date& operator=(const Date& dt);
		bool operator == (Date& dt) const;
		bool operator != (Date& dt) const;
		bool operator < (Date& dt) const;
		bool operator > (Date& dt) const;
		bool operator <= (Date& dt) const;
		bool operator >= (Date& dt) const;
		sdds::Status& state();
		Date& formatted(bool fm);
		operator bool() const;
		std::ostream& write(std::ostream& ostr,const bool form = true) const;
		std::istream& read(std::istream& istr);
	};

	std::istream& operator>>(std::istream& istr, Date& dt);
	std::ostream& operator<<(std::ostream& ostr, const Date& dt);
}

#endif // !SDDS_DATE_H
