#ifndef LETTER_H
#define LETTER_H
#include "shipment.h"

class Letter : public Shipment
{
    LetterType* type;
public:
    Letter(Person*, Person*, Date*, Date*, Date*, std::string, bool, LetterType*);
    Letter(LetterType * );
    Letter (Letter& other) {*this = other;};
    Letter();
    LetterType* getType() {return type;};
    void setType(LetterType* other) {type=other;};
    Letter &operator=(const Letter &);
    ~Letter();
};

#endif // LETTER_H
