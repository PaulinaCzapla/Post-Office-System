#include "parceltype.h"

ParcelType::ParcelType()
{
    isPriority = 0;
    size = ' ';
    price = 0;
    maxWeight = 0;
    minWeight = 0;
}

ParcelType::ParcelType(ParcelType * other)
{
    isPriority = other->isPriority;
    size = other->size;
    price = other->price;
    minWeight = other->minWeight;
    maxWeight = other->maxWeight;
}

ParcelType::ParcelType( bool _isPriority, char _size,int _maxWeight, int _minWeight, float _price)
    : ShipmentType(_isPriority, _size, _price),maxWeight(_maxWeight), minWeight(_minWeight) {}

ParcelType::ParcelType( bool _isPriority, char _size,int _maxWeight, int _minWeight, std::string _country)
    : ShipmentType(_isPriority, _size, _country),maxWeight(_maxWeight), minWeight(_minWeight) {}

bool ParcelType::operator==(const ParcelType& other)
{
    if(isPriority == other.isPriority && maxWeight==other.maxWeight &&
            minWeight == other.minWeight && size == other.size)
        return true;
    else
        return false;
}

ParcelType &ParcelType::operator=(const ParcelType & other)
{
    isPriority = other.isPriority;
    size = other.size;
    price = other.price;
    minWeight = other.minWeight;
    maxWeight = other.maxWeight;
    return *this;
}
