#ifndef PARCEL_H
#define PARCEL_H

#include "shipment.h"

class Parcel : public Shipment
{
  ParcelType* type;
public:
    Parcel(Person*, Person*, Date*, Date*, Date*, std::string, bool, ParcelType*);
    Parcel(ParcelType *);
    Parcel(Parcel& other) {*this = other;};
    Parcel();
    ParcelType* getType() {return type;};
    void setType(ParcelType* other) {type=other;};
    Parcel& operator=(const Parcel&);
    ~Parcel();
};

#endif // PARCEL_H
