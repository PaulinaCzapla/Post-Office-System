#include "shipmentformwidget.h"
#include "mainwindow.h"
#include "person.h"
#include <QDebug>
#include "database.h"
#include "shipmenttypeinfo.h"
#include <QString>
#include <QStringList>
#include <QVector>
#include <list>
using namespace DataInfo;



void ShipmentFormWidget::createShipmentType(bool & prevLetter)
{
    if(currentShipment)
    {
    if(typeid(*currentShipment).name()==typeid (Letter).name())
    {
        if(dynamic_cast<Letter*>(currentShipment)->getType())
        {
            delete dynamic_cast<Letter*>(currentShipment)->getType();
            dynamic_cast<Letter*>(currentShipment)->setType(nullptr);
            prevLetter = true;
        }

    } else if (typeid(*currentShipment).name()==typeid (Parcel).name())
    {
            if(dynamic_cast<Parcel*>(currentShipment)->getType())
            {
                delete dynamic_cast<Parcel*>(currentShipment)->getType();
                dynamic_cast<Parcel*>(currentShipment)->setType(nullptr);
                prevLetter = false;
            }
    }
    }
}

ShipmentType* ShipmentFormWidget::saveComboBoxInfo(std::map<shipmentTypeInfo,QComboBox *> &comboBoxes)
{

    if(comboBoxes[type] == 0)
        return nullptr;

    bool prevLetter = false;
    createShipmentType(prevLetter);

    auto isPriority_ = [](std::string reg){ if(reg=="priorytetowa") return true; else return false;};

    if(comboBoxes[type]->currentIndex() == 1)
    {
        auto isRegistered_ = [](std::string reg){ if(reg=="rejestrowana") return true; else return false;};

        LetterType* letterType = new LetterType(isPriority_(comboBoxes[isPriority]->currentText().toStdString()),comboBoxes[size]->currentText().toStdString()[0],
                isRegistered_(comboBoxes[isRegistered]->currentText().toStdString()), comboBoxes[shipmentTypeInfo::country]->currentText().toStdString()); //alokacja

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
                                                comboBoxes[size]->currentText().toStdString()[0], max, min, comboBoxes[shipmentTypeInfo::country]->currentText().toStdString());

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

        return parcelType;
    }
}


void ShipmentFormWidget::blockAllSignals(std::map<shipmentTypeInfo, QComboBox *> & comboBoxes, bool block)
{
    comboBoxes[type]->blockSignals(block);
    comboBoxes[isPriority]->blockSignals(block);
    comboBoxes[isRegistered]->blockSignals(block);
    comboBoxes[size]->blockSignals(block);
    comboBoxes[weight]->blockSignals(block);
    comboBoxes[shipmentTypeInfo::country]->blockSignals(block);
}

void ShipmentFormWidget::loadDataToComboBoxes(std::map<shipmentTypeInfo,QComboBox *> &comboBoxes)
{
    blockAllSignals(comboBoxes, true);
    if(comboBoxes[type]->count() == 0)
    {  
     comboBoxes[isPriority]->setDisabled(true);
     comboBoxes[isRegistered]->setDisabled(true);
     comboBoxes[size]->setDisabled(true);
     comboBoxes[weight]->setDisabled(true);
     comboBoxes[shipmentTypeInfo::country]->setDisabled(true);
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
     loadCountriesToComboBox(comboBoxes[shipmentTypeInfo::country]);
    }
    if(comboBoxes[type]->currentIndex()==0)
    {
        comboBoxes[isPriority]->setDisabled(true);
        comboBoxes[isRegistered]->setDisabled(true);
        comboBoxes[size]->setDisabled(true);
        comboBoxes[weight]->setDisabled(true);
        comboBoxes[shipmentTypeInfo::country]->setDisabled(true);
        comboBoxes[size]->clear();
    }

     if(comboBoxes[type]->currentIndex()==1)
     {
        if(comboBoxes[size]->count() != 3)
         {
         comboBoxes[size]->clear();
         comboBoxes[size]->addItem("S");
         comboBoxes[size]->addItem("M");
         comboBoxes[size]->addItem("L");
         }

         comboBoxes[isPriority]->setDisabled(false);
         comboBoxes[isRegistered]->setDisabled(false);
         comboBoxes[size]->setDisabled(false);
         comboBoxes[weight]->setDisabled(true);
         comboBoxes[shipmentTypeInfo::country]->setDisabled(false);
     }

     if(comboBoxes[type]->currentIndex()==2)
     {
         if(comboBoxes[size]->count() != 2 )
         {
         comboBoxes[size]->clear();
         comboBoxes[size]->addItem("A");
         comboBoxes[size]->addItem("B");
         }

         comboBoxes[isRegistered]->setDisabled(true);
         comboBoxes[isPriority]->setDisabled(false);
         comboBoxes[size]->setDisabled(false);
         comboBoxes[weight]->setDisabled(false);
         comboBoxes[shipmentTypeInfo::country]->setDisabled(false);
     }
     blockAllSignals(comboBoxes, false);
}

void ShipmentFormWidget::loadCountriesToComboBox(QComboBox *& comboBoxCountries)
{
    std::fstream file;
    file.open("validatorpostcode.txt", std::ios::in);
    std::string tmp="", country = "";

    std::vector<QString> countries;

     if (file.is_open() && file.good())
     {
          while (!file.eof())
         {
             file>>country;
             countries.push_back(QString::fromStdString(country));
             getline(file, tmp, '\n');
         }

          sortAlphabetically<QString>(countries);
          comboBoxCountries->addItems(QStringList::fromVector(QVector<QString>::fromStdVector(countries)));
          comboBoxCountries->setCurrentText("POL");
      }
    file.close();
}

std::pair<std::vector<dataInfo>*, std::vector<dataInfo>*>* ShipmentFormWidget::processFormData(std::map<dataInfo, std::string> & sender,
                                                                                                   std::map<dataInfo, std::string> & recipient,
                                                                                                        std::string recipientCountry)
{
    auto senderInvalid = validatePersonalData(sender, "POL");
    auto recipientInvalid = validatePersonalData(recipient, recipientCountry);

    std::pair <std::vector<dataInfo>*, std::vector<dataInfo>*> * result = new std::pair <std::vector<dataInfo>*, std::vector<dataInfo>*>;
    *result = std::make_pair(senderInvalid, recipientInvalid);
    return result;
}

std::vector<dataInfo>* ShipmentFormWidget::validatePersonalData(std::map<dataInfo, std::string> & person, std::string country)
{
    std::vector<dataInfo>* invalidData = new std::vector<dataInfo>;
    std::back_insert_iterator<std::vector<dataInfo>> insert(*invalidData);

    for (std::map<dataInfo, std::string>::iterator it=person.begin() ; it != person.end(); ++it)
    {
        if(it->first ==postCode)
        {
            if(!validate(it->second, country))
                insert =it->first;
        }
        else if(!validate(it->second,it->first))
            insert =it->first;
    }
    return invalidData;
}


void ShipmentFormWidget::insertRecord(std::map<dataInfo, std::string> & sender, std::map<dataInfo, std::string> & recipient,
                                      Database* localDatabase, Database* mainDatabase)
{
    Person* senderP = new Person(sender[city], sender[postCode],sender[street],sender[houseNumber], sender[dataInfo::country],
            sender[name],sender[phoneNumber]);

    Person* recipientP = new Person(recipient[city], recipient[postCode],recipient[street],recipient[houseNumber], recipient[dataInfo::country],
            recipient[name],recipient[phoneNumber]);

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

   delete currentShipment;
    currentShipment = nullptr;
}

void ShipmentFormWidget::setDefaultData(std::map<shipmentTypeInfo, QComboBox *> & comboBoxes)
{
    comboBoxes[isRegistered]->setCurrentIndex(0);
    comboBoxes[isPriority]->setCurrentIndex(0);
    comboBoxes[size]->setCurrentIndex(0);
    comboBoxes[weight]->setCurrentIndex(0);
    comboBoxes[shipmentTypeInfo::country]->setCurrentText("POL");
}

void ShipmentFormWidget::loadComboBoxSearchStatus(QComboBox *& combobox)
{
    combobox->addItem("");
    combobox->addItem("nadano");
    combobox->addItem("w drodze");
    combobox->addItem("oczekuje na odbior w placowce");
    combobox->addItem("oczekuje na wreczenie kurierowi");
    combobox->addItem("wreczono kurierowi do doreczenia");
    combobox->addItem("doreczono");
    combobox->addItem("uplynal termin odbioru");
    combobox->addItem("odmowiono odbioru");
    combobox->addItem("odeslano do nadawcy");
}

void ShipmentFormWidget::loadComboBoxSearch(QComboBox *& combobox)
{
    combobox->addItem("");
    combobox->addItem("nr przesyłki");
    combobox->addItem("nr tel. odbiorcy");
    combobox->addItem("nr tel. nadawcy");

}


ShipmentFormWidget::~ShipmentFormWidget()
{
    if(currentShipment)
        delete currentShipment;
}



