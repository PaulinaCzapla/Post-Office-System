#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address
{
protected:
    std::string city;
    std::string postCode;
    std::string street;
    std::string houseNumber;
    std::string country;
public:
    Address(std::string ,std::string ,std::string ,std::string, std::string);
    Address(Address *);
    Address();
    inline void setCity(std::string other) {city = other;};
    inline void setPostCode(std::string other) {postCode = other;};
    inline void setStreet(std::string other) {street= other;};
    inline void setHouseNumber(std::string other) {houseNumber = other;};
    inline void setCountry(std::string other) {country = other;};
    inline std::string getCity() {return city;};
    inline std::string getPostCode() {return postCode;};
    inline std::string getStreet() {return street;};
    inline std::string getHouseNumber() {return houseNumber;};
    inline std::string getCountry() {return country;};
    Address &operator=(const Address &);
    ~Address(){};
};

#endif // ADDRESS_H
