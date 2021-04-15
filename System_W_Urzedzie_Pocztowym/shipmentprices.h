#ifndef SHIPMENTTYPEMANAGER_H
#define SHIPMENTTYPEMANAGER_H

#include "lettertype.h"
#include "parceltype.h"
#include <fstream>
#include <string>
#include "list.h"
#include <typeinfo>
#include <QString>
#include <math.h>
#include <map>
#define FILENAME_LETTER_PRICES "letterprices.txt"
#define FILENAME_PARCEL_PRICES "parcelprices.txt"
#define FILENAME_FOREIGN_SHIPMENTS "foreignshipmentsprices.txt"
class ShipmentPrices
{
    List<ParcelType> parcelTypes;
    List<LetterType> letterTypes;
    std::map<std::string, float> foreignShipments;

    void readFileForeignPrices();
    void readFileLetterPrices();
    void readFileParcelPrices();
public:
    ShipmentPrices();
    float getShipmentPrice(ShipmentType*);
    QString returnProperPrice(float);
    const List<ParcelType>* getParcelTypes () {return &parcelTypes; };
    const List<LetterType>* getLetterTypes() {return &letterTypes; };
    float getAdditionalPrice (std::string);
};

#endif // SHIPMENTTYPEMANAGER_H
