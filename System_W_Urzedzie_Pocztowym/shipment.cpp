#include "shipment.h"


Shipment::Shipment() : recipient(nullptr), sender(nullptr), postDate(nullptr), dateOfReceipt(nullptr),
    finalDateOfReceiptAtTheFacility(nullptr), isReceived(0), status(""){}

Shipment::Shipment(Person * _recipient, Person * _sender, Date * _postDate, Date * _dateOfReceipt,
                   Date * _final, std::string _status, bool _isReceived)
    :  recipient(_recipient), sender(_sender), postDate(_postDate), dateOfReceipt(_dateOfReceipt),
      finalDateOfReceiptAtTheFacility(_final), isReceived(_isReceived), status(_status) {}

//zwraca ID
std::string Shipment::getStringID()
{
    std::string sID = std::to_string(ID);
    std::string zeros = "";

    if(sID.length()<9)
    for (auto i = 0; i < 9 - sID.length(); i++)
        zeros+="0";

    return zeros + sID;
}

std::string Shipment::intIDtoString(int id)
{
    std::string sID = std::to_string(id);
    std::string zeros = "";

    if(sID.length()<9)
    for (auto i = 0; i < 9 - sID.length(); i++)
        zeros+="0";

    return zeros + sID;
}

int Shipment::stringIDtoInt(std::string strID)
{
    while(strID[0]=='0')
        strID.erase(0,1);

    return stoi(strID);
}

Shipment::~Shipment()
{
    if(recipient)
    delete recipient;

    if(sender)
    delete sender;

    if(postDate)
    delete postDate;

    if(dateOfReceipt)
    delete dateOfReceipt;

    if(finalDateOfReceiptAtTheFacility)
    delete finalDateOfReceiptAtTheFacility;
}


