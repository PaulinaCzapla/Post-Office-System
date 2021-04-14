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

#define FILENAME_LETTER_PRICES "letterprices.txt"
#define FILENAME_PARCEL_PRICES "parcelprices.txt"

class ShipmentPrices
{
    List<ParcelType> parcelTypes;
    List<LetterType> letterTypes;

    void readFileLetterPrices();
    void readFileParcelPrices();
public:
    ShipmentPrices();
    float getShipmentPrice(ShipmentType*);
    QString returnProperPrice(float);
    const List<ParcelType>* getParcelTypes () {return &parcelTypes; };
    const List<LetterType>* getLetterTypes() {return &letterTypes; };

};

#endif // SHIPMENTTYPEMANAGER_H
