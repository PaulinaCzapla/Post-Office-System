#ifndef DATABASE_H
#define DATABASE_H

#include "letter.h"
#include "parcel.h"

#include "list.h"
#include <list>

class Database
{
    List<Letter>* letters;
    List<Parcel>* parcels;
    std::string filename;
    static int lastID;

    void writeFile();
    void readFile(std::string);
    bool isUpToDate(Date*);
    void getPersonalData(std::fstream&, Person*&);

public:

    Database(std::string);

    void addNewRecord(Letter*, bool newId = 1);
    void addNewRecord(Parcel*, bool newId = 1);

    void addRecord(Node<Letter>*);
    void addRecord(Node<Parcel>*);

    List<Letter>* getLetters() {return letters;};
    List<Parcel>* getParcels() {return parcels;};
    static int getLastID() {return lastID;};
    void decrementLastID(){lastID--;};

    void changeStatus(int, QString);
    void returnToRecipient (Shipment*);

    std::list<Shipment*> searchByID(const QString&);
    std::list<Shipment*> searchByPhoneNum(const QString&, bool recipient);
    std::list<Shipment*> searchByStatus(const QString&);
    std::list<Shipment*> searchByStatus(std::list<Shipment*>&, const QString&);

    ~Database();


};








#endif // DATABASE_H
