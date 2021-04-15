#ifndef PARCELTYPE_H
#define PARCELTYPE_H
#include <string>
#include "shipmenttype.h"

class ParcelType : public ShipmentType
{
    int maxWeight;
    int minWeight;
public:
    ParcelType();
    ParcelType (ParcelType* );
    ParcelType(ParcelType& other) { *this = other;};
    ParcelType(bool, char, int, int, float);
    ParcelType(bool, char, int, int, std::string);
    inline int getMaxWeight() {return maxWeight;};
    inline int getMinWeight() {return minWeight;};
    void display() {};
    inline void setMaxWeight(int other) {maxWeight = other;};
    inline void setMinWeight(int other) {minWeight = other;};
    bool operator==(const ParcelType&);
    ParcelType& operator=(const ParcelType&);
    ~ParcelType(){};
};

#endif // PARCELTYPE_H
