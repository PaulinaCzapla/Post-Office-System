#include "shipmentformwidget.h"
#include "mainwindow.h"
#include "person.h"
#include <QDebug>
#include "database.h"
#include "shipmenttypeinfo.h"
using namespace DataInfo;


/* tworzony jest obiekt Shipment* currentShipment oraz obiekt  SkipmentType */
ShipmentType* ShipmentFormWidget::saveComboBoxInfo(std::map<shipmentTypeInfo,QComboBox *> &comboBoxes)
{

    bool prevLetter = false;
    /* wykorzystanie RTTI */
    if(currentShipment)
    {
    if(typeid(*currentShipment).name()==typeid (Letter).name())
    {
        if(dynamic_cast<Letter*>(currentShipment)->getType())
        {
            delete dynamic_cast<Letter*>(currentShipment)->getType(); //usuwanie starego obiektu ShipmentType
            dynamic_cast<Letter*>(currentShipment)->setType(nullptr);
            prevLetter = true;
        }

    } else if (typeid(*currentShipment).name()==typeid (LetterType).name())
    {
            if(dynamic_cast<Parcel*>(currentShipment)->getType())
            {
                delete dynamic_cast<Parcel*>(currentShipment)->getType(); //usuwanie starego obiektu ShipmentType
                dynamic_cast<Parcel*>(currentShipment)->setType(nullptr);
                prevLetter = false;
            }
    }
    }

    //wykorzystanie wyrażenia lambda
    auto isPriority_ = [](std::string reg){ if(reg=="priorytetowa") return true; else return false;};

    if(comboBoxes[type]->currentIndex() == 1)
    {
        auto isRegistered_ = [](std::string reg){ if(reg=="rejestrowana") return true; else return false;};

        LetterType* letterType = new LetterType(isPriority_(comboBoxes[isPriority]->currentText().toStdString()),comboBoxes[size]->currentText().toStdString()[0],
                isRegistered_(comboBoxes[isRegistered]->currentText().toStdString()), comboBoxes[country]->currentText().toStdString()); //alokacja

        //warunki do modyfikacji istniejącego obiektu, albo do tworzenia nowego
        //RTTI
        if(currentShipment && !prevLetter)
        {
            delete currentShipment;
            currentShipment = new Letter(letterType);

        } else if (currentShipment && prevLetter)
        {
            dynamic_cast<Letter*>(currentShipment)->setType(letterType);
        }
        else
        currentShipment = new Letter(letterType);

        return letterType;
    }
    else
    {
        int min=0, max=1;
        if(comboBoxes[weight]->currentText()=="0 - 1 kg")
        {
            min = 0;
            max =1;
        } else if(comboBoxes[weight]->currentText()=="1 - 2 kg")
        {
            min = 1;
            max =2;
        } else if(comboBoxes[weight]->currentText()=="2 - 5 kg")
        {
             min = 2;
             max =5;
        } else if(comboBoxes[weight]->currentText()=="5 - 10 kg")
        {
            min = 5;
            max =10;
        } else if(comboBoxes[weight]->currentText()=="10+ kg")
        {
            min = 10;
            max =100;
        }


        ParcelType* parcelType = new ParcelType(isPriority_(comboBoxes[isPriority]->currentText().toStdString()),
                                                comboBoxes[size]->currentText().toStdString()[0], max, min, comboBoxes[country]->currentText().toStdString());
        qDebug()<<"parcel type (read data from widget)";

        if(currentShipment && prevLetter)
        {
            delete currentShipment;
            currentShipment = new Parcel(parcelType);

        } else if (currentShipment && !prevLetter)
        {
            dynamic_cast<Parcel*>(currentShipment)->setType(parcelType);
        }
        else
        currentShipment = new Parcel(parcelType);

         qDebug()<<"return parcel type";
        return parcelType;
    }
}

//nieużywana
void ShipmentFormWidget::clearComboBoxes(std::map<shipmentTypeInfo, QComboBox *> & comboBoxes)
{
    comboBoxes[type]->clear();
    comboBoxes[isRegistered]->clear();
    comboBoxes[isPriority]->clear();
    comboBoxes[size]->clear();
    comboBoxes[weight]->clear();
    comboBoxes[country]->clear();
}

void ShipmentFormWidget::loadDataToComboBoxes(std::map<shipmentTypeInfo,QComboBox *> &comboBoxes)
{
    if(comboBoxes[type]->count() == 0)
    {  
     comboBoxes[isPriority]->setDisabled(true);
     comboBoxes[isRegistered]->setDisabled(true);
     comboBoxes[size]->setDisabled(true);
     comboBoxes[weight]->setDisabled(true);
     comboBoxes[country]->setDisabled(true);
     comboBoxes[type]->addItem("");
     comboBoxes[type]->addItem("list");
     comboBoxes[type]->addItem("paczka");
     comboBoxes[isRegistered]->addItem("rejestrowana");
     comboBoxes[isRegistered]->addItem("nierejestrowana");
     comboBoxes[isPriority]->addItem("zwykła");
     comboBoxes[isPriority]->addItem("priorytetowa");
     comboBoxes[weight]->addItem("0 - 1 kg");
     comboBoxes[weight]->addItem("1 - 2 kg");
     comboBoxes[weight]->addItem("2 - 5 kg");
     comboBoxes[weight]->addItem("5 - 10 kg");
     comboBoxes[weight]->addItem("10+ kg");
     comboBoxes[country]->addItem("PL");
    }
    if(comboBoxes[type]->currentIndex()==0)
    {
        comboBoxes[isPriority]->setDisabled(true);
        comboBoxes[isRegistered]->setDisabled(true);
        comboBoxes[size]->setDisabled(true);
        comboBoxes[weight]->setDisabled(true);
        comboBoxes[country]->setDisabled(true);
        comboBoxes[size]->clear();
    }

     if(comboBoxes[type]->currentIndex()==1)
     {
         comboBoxes[size]->clear();

         comboBoxes[size]->addItem("S");
         comboBoxes[size]->addItem("M");
         comboBoxes[size]->addItem("L");

         comboBoxes[isPriority]->setDisabled(false);
         comboBoxes[isRegistered]->setDisabled(false);
         comboBoxes[size]->setDisabled(false);
         comboBoxes[weight]->setDisabled(true);
         comboBoxes[country]->setDisabled(false);
     }

     if(comboBoxes[type]->currentIndex()==2)
     {
         comboBoxes[isRegistered]->setDisabled(true);
         comboBoxes[isPriority]->setDisabled(false);
         comboBoxes[size]->setDisabled(false);
         comboBoxes[weight]->setDisabled(false);
         comboBoxes[country]->setDisabled(false);

         comboBoxes[size]->clear();
         comboBoxes[size]->addItem("A");
         comboBoxes[size]->addItem("B");
     }
}

std::pair<std::vector<dataInfo>*, std::vector<dataInfo>*>* ShipmentFormWidget::processFormData(std::map<dataInfo, std::string> & sender,
                                                                                                   std::map<dataInfo, std::string> & recipient)
{
    auto senderInvalid = validatePersonalData(sender); //zaalokowana pamiec
    auto recipientInvalid = validatePersonalData(recipient); // zaalokowana pamiec

    std::pair <std::vector<dataInfo>*, std::vector<dataInfo>*> * result = new std::pair <std::vector<dataInfo>*, std::vector<dataInfo>*>; //alokacja
    *result = std::make_pair(senderInvalid, recipientInvalid);
    return result;
}

std::vector<dataInfo>* ShipmentFormWidget::validatePersonalData(std::map<dataInfo, std::string> & person)
{
    //wykorzystanie iteratorów i kontenerów
    std::vector<dataInfo>* invalidData = new std::vector<dataInfo>;
    std::back_insert_iterator<std::vector<dataInfo>> insert(*invalidData);

    for (std::map<dataInfo, std::string>::iterator it=person.begin() ; it != person.end(); ++it)
    {
        if(!validate(it->second,it->first))
            insert =it->first;
    }
    return invalidData;
}


void ShipmentFormWidget::insertRecord(std::map<dataInfo, std::string> & sender, std::map<dataInfo, std::string> & recipient,
                                      Database* localDatabase, Database* mainDatabase)
{
    //obiektów person i nie można usunąć w innym miejscu niż struktura danych
    Person* senderP = new Person(sender[city], sender[postCode],sender[street],sender[houseNumber], "POL",
            sender[name],sender[phoneNumber]);

    Person* recipientP = new Person(recipient[city], recipient[postCode],recipient[street],recipient[houseNumber], "POL",
            recipient[name],recipient[phoneNumber]);

    //shipmentType jest już ustawione
    currentShipment->setSender(senderP);
    currentShipment->setRecipient(recipientP);
    currentShipment->setPostDate(Date::getCurrentDate());
    currentShipment->setDateOfReceipt(nullptr);
    currentShipment->setDateOfReceiptAtTheFacility(nullptr);
    currentShipment->setIsReceived(false);
    currentShipment->setStatus("nadano");

    if(typeid (*currentShipment).name() == typeid(Letter).name())
    {
        localDatabase->addNewRecord(dynamic_cast<Letter*>(currentShipment));
        localDatabase->decrementLastID();
        mainDatabase->addNewRecord(dynamic_cast<Letter*>(currentShipment));
    }
    else if(typeid (*currentShipment).name() == typeid(Parcel).name())
    {
        localDatabase->addNewRecord(dynamic_cast<Parcel*>(currentShipment));
        localDatabase->decrementLastID();
        mainDatabase->addNewRecord(dynamic_cast<Parcel*>(currentShipment));
    }

   delete currentShipment; //usuwam kopię
    currentShipment = nullptr;
}

ShipmentFormWidget::~ShipmentFormWidget()
{
    if(currentShipment)
        delete currentShipment;
}



