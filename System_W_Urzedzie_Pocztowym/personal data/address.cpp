#include "address.h"

Address::Address(std::string _city, std::string _postCode, std::string _street, std::string _houseNumber, std::string _country)
    : city(_city), postCode(_postCode), street(_street), houseNumber(_houseNumber), country(_country){}

Address::Address(Address * _address)
{
    city = _address->city;
    street = _address->street;
    postCode = _address->postCode;
    houseNumber = _address->houseNumber;
    country = _address->country;
}

Address::Address()
{
    city = "";
    street = "";
    postCode = "";
    houseNumber = "";
    country = "";
}

Address &Address::operator=(const Address & other)
{
    city = other.city;
    street = other.street;
    postCode = other.postCode;
    houseNumber = other.houseNumber;
    country = other.country;

    return *this;
}


