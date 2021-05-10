#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <string>
#include <windows.h>
#include <regex>
#include <string.h>

class Date
{
    short unsigned int day;
    short unsigned int month;
    short unsigned int year;

    void setDay(short unsigned int);
    void setMonth(short unsigned int);
    void setYear(short unsigned int);

public:
    Date(short unsigned int, short unsigned int, short unsigned int);
    Date(std::string);
    Date(Date& other) {*this = other;};
    Date(Date*);
    Date();

    std::string dateToString();
    static Date* getCurrentDate();

    int operator- (const Date&) const;
    Date operator+ (const int&) const;
    Date& operator=(const Date&);
    bool operator==(const Date& );
    ~Date() {};
};

#endif // DATE_H
