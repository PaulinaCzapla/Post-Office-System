#include "lettertype.h"

LetterType::LetterType()
{
    isPriority = 0;
    size = ' ';
    price = 0;
    isRegistered = 0;
}

LetterType::LetterType(LetterType * other)
{
    isPriority = other->isPriority;
    size = other->size;
    price = other->price;
    country = other->country;
    isRegistered = other->isRegistered;
}

LetterType::LetterType(bool _isPriority, char _size, bool _isRegistered, float _price)
    : ShipmentType(_isPriority, _size, _price), isRegistered(_isRegistered){}

LetterType::LetterType(bool _isPriority, char _size, bool _isRegistered, std::string _country)
    : ShipmentType(_isPriority, _size, _country), isRegistered(_isRegistered){}

bool LetterType::operator==(const LetterType& other)
{
    if(isRegistered == other.isRegistered && isPriority == other.isPriority &&
            size == other.size)
        return true;
    else
        return false;
}

LetterType &LetterType::operator=(const LetterType & other)
{
    isPriority = other.isPriority;
    size = other.size;
    price = other.price;
    country = other.country;
    isRegistered = other.isRegistered;
    return *this;
}
