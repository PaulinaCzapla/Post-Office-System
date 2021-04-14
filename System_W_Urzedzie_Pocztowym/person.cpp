#include "person.h"

Person::Person(std::string _city, std::string _postCode, std::string _street, std::string _houseNumber, std::string _country, std::string _name, std::string _phoneNum)
    :Address(_city, _postCode, _street, _houseNumber,  _country), name(_name), phoneNumber(_phoneNum){}

Person::Person(Person & other)
{
    *this = other;
}


Person:: Person() : Address()
{
    name = "";
    phoneNumber = "";
}


bool Person::operator==(const Person& _person)
{
    if (phoneNumber.compare(_person.phoneNumber) == 0 && name.compare(_person.name)==0)
        return true;
    else
        return false;
}


Person &Person::operator=(const Person & other)
{
    city = other.city;
    street = other.street;
    postCode = other.postCode;
    houseNumber = other.houseNumber;
    country = other.country;

    name = other.name;
    phoneNumber = other.phoneNumber;
    return *this;
}
