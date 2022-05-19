/*
Name: Tomonobu Christian Fukuhara Tengan
Email: tcfukuhara-tengan@myseneca.ca
Student ID: 123475212
Date: 8 April 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments
Project MS5
*/

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
namespace sdds {
	class Status {
		char* desc;
		int statusCode;
		void allocateAndCopy(const char* e_desc);
	public:
		Status(const char* e_desc = nullptr);
		Status(const Status& st);
		Status& operator=(const Status& st);
		Status& operator=(const char* e_desc);
		Status& operator=(const int e_statusCode);
		~Status();
		operator int() const;
		operator char* () const;
		operator bool() const;
		void clear();
		std::ostream& print(std::ostream& ostr) const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Status& st);
}

#endif // !SDDS_STATUS_H


