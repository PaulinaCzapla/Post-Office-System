#ifndef PERSON_H
#define PERSON_H

#include "address.h"
#include <string>
//regexy do walidacji danych personalnych
class Person : public Address
{
    std::string name;
    std::string phoneNumber;
public:
    Person(std::string ,std::string ,std::string ,std::string, std::string, std::string, std::string);
    Person(Person&);
    Person();
    inline void setName(std::string other) {name = other;};
    inline void setPhoneNumber(std::string other) {phoneNumber = other;};
    inline std::string getPhoneNumber(){return phoneNumber;};
    inline std::string getName() {return name;};
    Person &operator=(const Person & );
    bool operator==(const Person&);
    //+ operatory, na pewno << i ==
};

#endif // PERSON_H
