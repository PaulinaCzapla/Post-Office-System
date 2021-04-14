#include "letter.h"


Letter::Letter(Person * _recipient, Person * _sender, Date * _postDate, Date * _dateOfReceipt,
               Date * _final, std::string _status, bool _isReceived, LetterType * _type)
    : Shipment(_recipient, _sender, _postDate, _dateOfReceipt, _final, _status, _isReceived)
{
    type = _type;
}

Letter::Letter(LetterType * _type) : Shipment(), type(_type){}

Letter::Letter() :Shipment(),type(nullptr) {}

Letter &Letter::operator=(const Letter & other)
{
    type = new LetterType( other.type);
    recipient = new Person(*other.recipient);
    sender = new Person(*other.sender);

    (other.postDate ?  postDate = new Date(*other.postDate) : postDate = nullptr);

    (other.dateOfReceipt ? dateOfReceipt = new Date(*other.dateOfReceipt) :dateOfReceipt = nullptr);

    (other.finalDateOfReceiptAtTheFacility ? finalDateOfReceiptAtTheFacility = new Date(*other.finalDateOfReceiptAtTheFacility)
            : finalDateOfReceiptAtTheFacility = nullptr);

    isReceived = other.isReceived;
    status = other.status;

    ID = other.ID;
    return *this;
}

Letter::~Letter()
{
    delete type;
}
