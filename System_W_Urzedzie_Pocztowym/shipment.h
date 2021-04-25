#ifndef SHIPMENT_H
#define SHIPMENT_H
#include "person.h"
#include "date.h"
#include "shipmentstatusmanager.h"
#include "shipmentprices.h"
#include <string>
class Shipment
{
 protected:
    Person* recipient;
    Person* sender;
    Date* postDate;
    Date* dateOfReceipt;
    Date* finalDateOfReceiptAtTheFacility;
    bool isReceived;
    std::string status;
    unsigned int ID;

public:
    Shipment();
    Shipment(Person*, Person*, Date*, Date*, Date*, std::string, bool);
    Shipment(Shipment& other ) {*this = other;};


    inline Person * getRecipient() {return recipient;};
    inline Person * getSender() {return sender;};
    inline Date* getPostDate() {return postDate;};
    inline Date* getdateOfReceipt() {return dateOfReceipt;};
    inline Date* getfinalDateOfReceiptAtTheFacility() {return finalDateOfReceiptAtTheFacility;};
    inline bool getIsReceived() { return isReceived;};
    inline std::string getStatus() {return status;};
    inline int getID() {return ID;};

    std::string getStringID ();

    static std::string intIDtoString (int);
    static int stringIDtoInt(std::string);
    bool operator==(const std::string&);
    bool operator==(const unsigned int&);



    inline void setRecipient(Person* other) {recipient = other;}
    inline void setSender(Person* other) {sender = other;}
    inline void setPostDate(Date* other) {postDate = other;}
    inline void setDateOfReceipt(Date* other) {dateOfReceipt = other;}
    inline void setDateOfReceiptAtTheFacility(Date* other) {finalDateOfReceiptAtTheFacility = other;}
    inline void setIsReceived(bool other) {isReceived = other;}
    inline void setStatus(std::string other) {status = other;}
    inline void setID(int other) {ID = other;};
    void setID(std::string other) {ID = stringIDtoInt(other);};




    virtual ~Shipment();
};

#endif // SHIPMENT_H
