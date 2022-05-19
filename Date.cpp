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
#include "Date.h"
#include "Utils.h"
using namespace std;

namespace sdds {
	sdds::Utils xt;

	Date& Date::operator=(const Date& dt) {
		State.clear();
		if (dt.Day != 0 && dt.Month != 0 && dt.Year != 0) {
			Year = dt.Year;
			Month = dt.Month;
			Day = dt.Day;
			validate();
		}
		else {
			State = "No date";
			State = 5;
		}
		return *this;
	}

	bool Date::validate() {
		int actualYear;
		xt.getSystemDate(&actualYear);
		bool val = true;

		if (Year < actualYear || Year > maximumYearValue) {
			State = "Invalid year in date";
			State = 1;
			val = false;
		}
		else {
			if (Month < 1 || Month > 12) {
				State = "Invalid month in date";
				State = 2;
				val = false;
			}
			else {
				if (Day < 1 || Day> xt.daysOfMon(Month, Year)) {
					State = "Invalid day in date";
					State = 3;
					val = false;
				}
			}
		}
		return val;
	}

	int Date::unique() const {
		return (Year * 372 + Month * 31 + Day);
	}

	Date::Date(const int e_year, const int e_month, const int e_day) {
		State.clear();
		if (e_year != 0 && e_month != 0 && e_day != 0) {
			Year = e_year;
			Month = e_month;
			Day = e_day;
			validate();
		}
		else {
			State = "No date";
			State = 5;
		}
	}

	bool Date::operator == (Date& dt) const {
		return this->unique() == dt.unique();
	}
	
	bool Date::operator != (Date& dt) const {
		return this->unique() != dt.unique();
	}
	
	bool Date::operator < (Date& dt) const {
		return this->unique() < dt.unique();
	}
	
	bool Date::operator > (Date& dt) const {
		return this->unique() > dt.unique();
	}
	
	bool Date::operator <= (Date& dt) const {
		return this->unique() <= dt.unique();
	}
	
	bool Date::operator >= (Date& dt) const {
		return this->unique() >= dt.unique();
	}

	sdds::Status& Date::state() {
		return State;
	}

	Date& Date::formatted(bool fm) {
		Formatted = fm;
		return *this;
	}

	Date::operator bool() const {
		return State;
	}

	std::ostream& Date::write(std::ostream& ostr, const bool form) const {
		if (Formatted && form) {
			ostr << Year << '/';
			ostr.width(2);
			ostr.fill('0');
			ostr << Month << '/';
			ostr.width(2);
			ostr << Day;
		}
		else {
			int d1, d2;
			d1 = (1000 * (Year / 1000));
			d2 = (100 * ((Year - d1) / 100));
			int mod = d1 + d2;
			int yr = Year % mod;
			ostr.width(2);
			ostr.fill('0');
			ostr << yr;
			ostr.width(2);
			ostr << Month;
			ostr.width(2);
			ostr << Day;
		}
		return ostr;
	}

	std::istream& Date::read(std::istream& istr) {
		int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;
		bool range = true;

		char spec[400] = {};
		istr.get(spec, 100, '\n');
		std::string str(spec);
		if (spec > 0) d6 = atoi(spec);

		if (d6 < 1 || d6 >= 1000000) range = false;
		d1 = d6 / 100000;
		if (d1) d6 = d6 % (d1 * 100000);
		d2 = d6 / 10000;
		if (d2) d6 = d6 % (d2 * 10000);
		d3 = d6 / 1000;
		if (d3) d6 = d6 % (d3 * 1000);
		d4 = d6 / 100;
		if (d4) d6 = d6 % (d4 * 100);
		d5 = d6 / 10;
		if (d5) d6 = d6 % (d5 * 10);

		if(range)
		{
			if (d1 == 0 && d2 == 0) {
				xt.getSystemDate(&Year);
				Month = d3 * 10 + d4;
				Day = d5 * 10 + d6;
				State = nullptr;
				State = 0;
			}
			else {
				Year = 2000 + d1 * 10 + d2;
				Month = d3 * 10 + d4;
				Day = d5 * 10 + d6;
				State = nullptr;
				State = 0;
			}		
			if(!validate()) istr.setstate(ios::badbit);
		}
		else {
			Year = 0;
			Month = 0;
			Day = 0;
			istr.setstate(ios::badbit);
		}
		return istr;
	}

	std::istream& operator>>(std::istream& istr, Date& dt) {
		return dt.read(istr);
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& dt) {
		if(dt) dt.write(ostr);
		return ostr;
	}
}