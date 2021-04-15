#ifndef LETTERTYPE_H
#define LETTERTYPE_H

#include "shipmenttype.h"

class LetterType : public ShipmentType
{
    bool isRegistered;

public:
    LetterType();
    LetterType(LetterType*);
    LetterType(LetterType& other) { *this = other;};
    LetterType(bool, char, bool, float);
    LetterType(bool, char, bool, std::string);
    inline bool getIsRegistered() { return isRegistered;};
    void display() {};
    void setIsRegistered(bool other) {isRegistered = other; };
    bool operator==(const LetterType&);
    LetterType &operator=(const LetterType &);
    ~LetterType() {};
};

#endif // LETTERTYPE_H
