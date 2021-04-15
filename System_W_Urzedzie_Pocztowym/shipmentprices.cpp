#include "shipmentprices.h"


ShipmentPrices::ShipmentPrices()
{
    readFileLetterPrices();
    readFileParcelPrices();
    readFileForeignPrices();
}

void ShipmentPrices::readFileForeignPrices()
{
    std::fstream file;
    file.open(FILENAME_FOREIGN_SHIPMENTS, std::ios::in);
    std::string country = "";
    float price=0;
    if (file.is_open() && file.good())
    {
         while (!file.eof())
        {
            file>>country>>price;
            foreignShipments.insert(std::pair<std::string, float>(country,price));
        }
     }
   file.close();
}

void ShipmentPrices::readFileLetterPrices()
{
    std::fstream file;
    file.open(FILENAME_LETTER_PRICES, std::ios::in);
    bool isPriority = 0, isRegistered = 0;
    char size;
    float price;
    if (file.is_open() && file.good())
    {
        while (!file.eof())
        {
             file>>isPriority>>isRegistered>>size>>price;
             LetterType letter(isPriority, size, isRegistered, price);
             Node<LetterType>* node = new Node<LetterType>(letter);
             letterTypes.addFront(node);
        }
    }
    file.close();
}

void ShipmentPrices::readFileParcelPrices()
{
    std::fstream file;
    file.open(FILENAME_PARCEL_PRICES, std::ios::in);
    bool isPriority;
    char size;
    int maxWeight;
    int minWeight;
    float price;
    if (file.is_open() && file.good())
    {
        while (!file.eof())
        {
             file>>isPriority>>size>>minWeight>>maxWeight>>price;
             ParcelType parcel(isPriority, size,  maxWeight,minWeight, price);
             Node<ParcelType>*node = new Node<ParcelType>(parcel);
             parcelTypes.addFront(node);
        }
    }
    file.close();
}

QString ShipmentPrices::returnProperPrice(float p)
{
    QString result = "";
    if(roundf(p) == p)
        result = QString::number(p)+".00";
    else
        result = QString::number(p)+"0";

    return result;
}

float ShipmentPrices::getAdditionalPrice(std::string country)
{
    return foreignShipments[country];
}

//RTTI

float ShipmentPrices::getShipmentPrice(ShipmentType* type)
{
    if(typeid(*type).name()==typeid (ParcelType).name())
    {
       auto parcelType= dynamic_cast<ParcelType*>(type);
       auto found = parcelTypes.getElement(*parcelType);
       return found->getCurrentData().getPrice() + getAdditionalPrice(type->getCountry());

    } else if (typeid(*type).name()==typeid (LetterType).name())
    {
        auto letterType= dynamic_cast<LetterType*>(type);
        auto found = letterTypes.getElement(*letterType);
        return found->getCurrentData().getPrice()+ getAdditionalPrice(type->getCountry());
    }
    return 0;
}
