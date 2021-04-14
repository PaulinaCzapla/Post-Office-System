#include "parcel.h"

Parcel::Parcel(Person * _recipient, Person * _sender, Date * _postDate, Date * _dateOfReceipt,
               Date * _final, std::string _status, bool _isReceived, ParcelType * _type)
    : Shipment(_recipient, _sender, _postDate, _dateOfReceipt, _final, _status, _isReceived)
{
    type = _type;
}

Parcel::Parcel(ParcelType * _type) : Shipment(), type(_type){}

Parcel::Parcel() : Shipment(), type(nullptr){}

Parcel &Parcel::operator=(const Parcel & other)
{
    type = new ParcelType( other.type);
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


Parcel::~Parcel()
{
    delete type;
}
