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
#include <ctime>
#include <cstring>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
   
   void Utils::alocpy(char*& destination, const char* source) {
       if (destination != nullptr) {
            delete[] destination;
            destination = nullptr;
       } 
       if (source != nullptr) {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }
   }

   int Utils::getint(const char* prompt) {
       int input = -1;
       char input1;
       if (prompt != nullptr) {
           cout << prompt;
           while (input == -1) {
               cin >> input1;
               if(input1 > 47 && input1 < 58) input = input1 - 48;
               if (input == -1) cout << "Invalid Integer, retry: ";
               cin.clear();
               cin.ignore(1000, '\n');
           }
       }
       return input;
   }

   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
       int val;
       val = getint(prompt);
       while(val < min || val > max){
           if (errMes != nullptr) cout << errMes << ", retry: ";
           else {
                cout << "Value out of range [" << min << "<=" << "val" << "<=" << max << "]:";
                val = getint(" ");
           }
       }
       return val;
   }
}