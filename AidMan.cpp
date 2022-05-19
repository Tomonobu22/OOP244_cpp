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
#include <string>
#include "AidMan.h"
using namespace std;

namespace sdds {
	Date dt2(2022,03,31);
	unsigned int AidMan::menu() const{
		cout << "Aid Management System" << endl;
		cout << "Date: " <<  dt2 << endl;
		if(fileName == nullptr || fileName[0] == '\0')
			cout << "Data file: No file" << endl;
		else
			cout << "Data file: " << fileName << endl;
		cout << "---------------------------------" << endl;

		return a_menu.run(); 
	}

	AidMan::AidMan() {
		fileName = nullptr;
		//a_menu defined in header

	}

	AidMan::~AidMan() {
		delete[] fileName;
		fileName = nullptr;
		deallocate();
	}

	void AidMan::run() {
		int state = 1;
		char taskName[30];
		int i, j, offset, count;
		bool flag = true;

		do {
			state = menu();
			if (state != 0)
			{
				if ((fileName == nullptr || fileName[0] == '\0') && state != 7) state = 7;
				i = 0;
				j = 0;
				offset = 0;
				flag = true;
				count = 0;
				while (flag) {
					if (count == state - 1){
						if (List[i] == '\n') flag = false;
						else {
							offset++; // offset defined to trim the first part of the list
							if (offset > 3) { 
								taskName[j] = List[i];
								j++;							
							}
						}
					}
					if (List[i] == '\n') count++;
					i++;
				}
				taskName[j] = '\0';
				cout << endl << "****" << taskName << "****" << endl;
				if (state == 1) list();
				if (fileName != nullptr && fileName[0] != '\0')
				{
					std::ofstream out(fileName);
					save(out);
				}
				else {
					string str;
					cout << "Enter file name: ";
					getline(cin, str);
					ut.alocpy(fileName, str.c_str());
					ifstream in(fileName);
					load(in);
				}
			}
		} while (state != 0);
		cout << "Exiting Program!" << endl;
	}

	std::ofstream& AidMan::save(std::ofstream& ofstr) const {
		for (int x = 0; x < nProductItems; x++)
		{
			if (x > 0) ofstr << endl;
			products[x]->save(ofstr);
		}
		return ofstr;
	}

	void AidMan::deallocate() {
		for (int x = 0; x < nProductItems; x++)
		{
			if (products[x]) {
				products[x]->~iProduct();
				delete products[x];
				products[x] = nullptr;
			}
		}
		nProductItems = 0;
	}

	std::ifstream& AidMan::load(std::ifstream& ifstr) {
		int option;
		char p;
		deallocate();
		if (ifstr.is_open()) {
			while(ifstr.peek() > '0' && ifstr.peek() <= '9') {
				p = ifstr.peek();
				if (p > '0' && p < '4') {
					products[nProductItems] = new Perishable();
					products[nProductItems]->load(ifstr);
					if (products[nProductItems]) {
						nProductItems++;
					}
					else {
						products[nProductItems]->~iProduct();
					}
				}
				else if (p >= '4' && p <= '9') {
					products[nProductItems] = new Item();
					products[nProductItems]->load(ifstr);
					ifstr.ignore();
					if (products[nProductItems]) {
						nProductItems++;
					}
					else {
						delete[] products[nProductItems];
						products[nProductItems] = nullptr;
					}
				}
				else {
					ifstr.setstate(std::ios_base::failbit);
				}
			} 
		}
		else {
			cout << "Failed to open " << fileName << " for reading!" << endl;
			cout << "Would you like to create a new data file?";
			cout << "1- Yes!" << endl << "0- Exit" << endl << ">";
			cin >> option;
			cin.ignore();
			if (option == 1) {
				//create an empty file under the same name and in any case, the function exits after.
			}
		}

		if (nProductItems > 0) cout << nProductItems << " records loaded!" << endl << endl;
		return ifstr;
	}

	int AidMan::list(const char* sub_desc) {
		string opt = "";
		int iopt = 0;
		if (sub_desc == nullptr) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			for (int x = 0; x < nProductItems; x++)
			{
				cout.width(4);
				cout.fill(' ');
				cout << right << x+1 << " | ";
				products[x]->linear(true);
				cout << *products[x] << endl; 
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			cout << "Enter row number to display details or <ENTER> to continue:" << endl;
			cout << "> ";
			getline(cin, opt);
			iopt = atoi(opt.c_str());
			if ( iopt > 0 && iopt <= nProductItems) {
				products[iopt - 1]->linear(false);
				cout << *products[iopt - 1] << endl;
			}
			cout << endl;
		}
		else {
			for (int x = 0; x < nProductItems; x++)
			{
				if (*products[nProductItems] == sub_desc)
					cout << products[nProductItems];
			}

		}
		if (nProductItems == 0) cout << "The list is emtpy!" << endl;

		return nProductItems;
	}
}