#ifndef SHIPMENTTYPE_H
#define SHIPMENTTYPE_H

#include <string>

class ShipmentType
{
protected:
    bool isPriority;
    char size;
    float price;
    std::string country;

public:
    ShipmentType ();
    ShipmentType(bool, char, float = 0);
    ShipmentType(bool, char, std::string);
    virtual void display()=0;
    inline bool getIsPriority() { return isPriority;};
    inline char getSize() {return size;};
    inline float getPrice() {return price;};
    inline std::string getCountry() {return country;};
    inline void setIsPriority(bool other) {isPriority = other;};
    inline void setSize(char other) {size = other;};
    inline void setPrice(float other) {price = other;};
    virtual ~ShipmentType() {};

};

#endif // SHIPMENTTYPE_H
