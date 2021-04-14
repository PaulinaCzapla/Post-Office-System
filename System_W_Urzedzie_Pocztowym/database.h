#ifndef DATABASE_H
#define DATABASE_H

#include "letter.h"
#include "parcel.h"
//#include "shipmentformwidget.h"
#include "list.h"


class Database
{
    List<Letter>* letters;
    List<Parcel>* parcels;
    std::string filename;
    static int lastID;

    void writeFile();
    void readFile(std::string);
public:

    Database(std::string);
    bool isUpToDate(Date*);
    void addNewRecord(Letter*);
    void addNewRecord(Parcel*);
    List<Letter>* getLetters() {return letters;};
    List<Parcel>* getParcels() {return parcels;};
    static int getLastID() {return lastID;};
    void findShipment(std::string&);
    void decrementLastID(){lastID--;};
    ~Database();
//    void findShipment(Node<Shipment*>&);
//    void findShipment(Shipment*);
//    void findShipment(std::string&);
//    void changeStatus(ShipmentStatusManager&);
//    void relocateShipment(Node<Shipment*>&);

};





#endif // DATABASE_H
