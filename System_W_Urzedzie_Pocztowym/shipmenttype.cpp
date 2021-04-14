#include "shipmenttype.h"

ShipmentType::ShipmentType()
{
    isPriority = 0;
    size = ' ';
    price = 0;
}

ShipmentType::ShipmentType(bool _isPriority, char _size, float _price)
    : isPriority(_isPriority), size(_size), price(_price){}

ShipmentType::ShipmentType(bool _isPriority, char _size, std::string _country)
    : isPriority(_isPriority), size(_size), country(_country){}

