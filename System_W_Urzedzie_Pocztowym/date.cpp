#include "date.h"


Date::Date(short unsigned int day_, short unsigned int month_, short unsigned int year_)
{
    day = day_;
    month = month_;
    this->year = year_;
}

Date::Date(std::string date_)
{
        this->day = (date_[0] - '0') * 10 + (date_[1] - '0');
        this->month = (date_[3] - '0') * 10 + (date_[4] - '0');
        this->year = (date_[6] - '0') * 1000 + (date_[7] - '0') * 100 + (date_[8] - '0') * 10 + (date_[9] - '0');
}

Date::Date()
{
    SYSTEMTIME time;
    GetSystemTime(&time);

    day = time.wDay;
    month = time.wMonth;
    year = time.wYear;
}


void Date::setDay(short unsigned int day_)
{
    this->day = day_;
}

void Date::setMonth(short unsigned int month_)
{
    this->month = month_;
}

void Date::setYear(short unsigned int year_)
{
    this->year = year_;
}

void Date::setDateFromString(std::string date_)
{
    this->day = (date_[0] - '0') * 10 + (date_[1] - '0');
    this->month = (date_[3] - '0') * 10 + (date_[4] - '0');
    this->year = (date_[6] - '0') * 1000 + (date_[7] - '0') * 100 + (date_[8] - '0') * 10 + (date_[9] - '0');
}

std::string Date::dateToString()
{
    std::string tmp;
    if (this->day < 10)
        tmp = '0' + std::to_string(this->day);
    else
        tmp =std::to_string(this->day);

    if (this->month < 10)
        tmp = tmp + "-0" + std::to_string(this->month);
    else
        tmp =tmp +'-' + std::to_string(this->month);

    return tmp + '-' + std::to_string(this->year);
}

Date *Date::getCurrentDate()
{
    SYSTEMTIME time;
    GetSystemTime(&time);
    return new Date(time.wDay, time.wMonth, time.wYear);
}


int Date::operator- (const Date& other) const //zwraca różnicę w dniach
{
    int days, months, years, sum = 0, monthsSign = 1, yearSign = 1, monthPrev = 0, monthNext = 0;

    int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    years = year - other.year;
    months = month - other.month;
    days = day - other.day;

    if (years < 0 || years >0)
    {
        (years > 0 ? yearSign = 1 : yearSign = -1);

        for (int i = 0; i < years; i++)
            sum += 365;

        for (int i = 0; i < 12 - month; i++)
            monthPrev += daysInMonth[month - 1 + i];

        for (int i = 0; i < other.month; i++)
            monthNext += daysInMonth[other.month - 1 - i];

        return sum - monthPrev + monthNext;
    }
    else if (years == 0)
    {
        if (months == 0)
            return days;

        if (months > 0 || months < 0)
        {
            (months > 0 ? monthsSign = 1 : monthsSign = -1);

            for (int i = 0; i < months; i++)
                sum += daysInMonth[month - 1 + i];

            return (sum - day + other.day) * monthsSign;
        }
    }
}

Date Date::operator+ (const int& other) const
{
    int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    int tmp, months=0, year_ = year;
    tmp = day + other;

    Date date;
    months = month;
    if (tmp > daysInMonth[month])
    {
        for (int i = month; ; i++)
        {
            if (i > 12)
            {
                i = 1;
                year_++;
                months = 0;
            }
            tmp -= daysInMonth[i-1];
            months++;

            if (daysInMonth[i-1] >= tmp)
            {
                date.setDay(tmp);
                date.setMonth(months);
                date.setYear(year_);
                break;
            }
        }
    }
    else
    {
        date.setDay(tmp);
        date.setMonth(month);
        date.setYear(year);
    }
return date;
}

Date& Date::operator=(const Date& other)
{
    day = other.day;
    month = other.month;
    year = other.year;

    return *this;
}

bool Date::operator==(const Date& _date)
{
    if (day == _date.day && month == _date.month && year == _date.year)
        return true;
    else
        return false;
}

std::ostream& operator<< (std::ostream& output, Date const& date)
{

    return output;
}

