#include "database.h"
#include "date.h"
#include <string>
#include <QDebug>

#define FILENAME_LOCAL_DATABASE "localdatabase.csv"
#define FILENAME_MAIN_DATABASE "maindatabase.csv"

Database::Database(std::string _filename)
{
    letters = new List<Letter>;
    parcels = new List<Parcel>;
    filename = _filename;
    readFile(_filename);
}


void Database::readFile(std::string filename)
{
    
    
    std::fstream file;
    file.open(filename, std::ios::in);
    std::string data="";
    LetterType* letterType;
    ParcelType* parcelType;

   Shipment* element;
    if (file.is_open() && file.good())
    {
        while (!file.eof())
        {
        getline(file, data, ';');
        if (data == "letter")
        {
            //czy priorytetowy
            letterType = new LetterType();
            getline(file, data, ';');
            (data == "1" ? letterType->setIsPriority(true) : letterType->setIsPriority(false));
            data.erase();

            //czy rejestrowana
            getline(file, data, ';');
            (data == "1" ? letterType->setIsRegistered(true) : letterType->setIsRegistered(false));

            //rozmiar
            getline(file, data, '\n');
            letterType->setSize(data[0]);
            data.erase();

            element = new Letter(letterType);
            Letter * element = dynamic_cast<Letter*>(element);

        } else
        if(data=="parcel")
        {
            parcelType = new ParcelType();

            //czy priorytetowy
            getline(file, data, ';');
            (data == "1" ? parcelType->setIsPriority(true) : parcelType->setIsPriority(false));
            data.erase();

            //rozmiar
            getline(file, data, ';');
            parcelType->setSize(data[0]);
            data.erase();

            // min. waga
            getline(file, data, ';');
            parcelType->setMinWeight(std::stoi(data));
            data.erase();

            //max waga
            getline(file, data, '\n');
            parcelType->setMaxWeight(std::stoi(data));
            data.erase();



            element = new Parcel(parcelType);
            Parcel * element = dynamic_cast<Parcel*>(element);
        }

        //nadawca
        Person* sender = new Person;
        //name
        getline(file, data, ';');
        sender->setName(data);
        //phone
        getline(file, data, ';');
        sender->setPhoneNumber(data);
        //postcode
        getline(file, data, ';');
        sender->setPostCode(data);
        //street
        getline(file, data, ';');
        sender->setStreet(data);
        //housenum
        getline(file, data, ';');
        sender->setHouseNumber(data);
        //city
        getline(file, data, ';');
        sender->setCity(data);
        //country
        getline(file, data, '\n');
        sender->setCountry(data);

        Person* recipient = new Person;
        //name
        getline(file, data, ';');
        recipient->setName(data);
        //phone
        getline(file, data, ';');
        recipient->setPhoneNumber(data);
        //postcode
        getline(file, data, ';');
        recipient->setPostCode(data);
        //street
        getline(file, data, ';');
        recipient->setStreet(data);
        //housenum
        getline(file, data, ';');
        recipient->setHouseNumber(data);
        //city
        getline(file, data, ';');
        recipient->setCity(data);
        //country
        getline(file, data, '\n');
        recipient->setCountry(data);

        getline(file, data, ';');
        Date* postDate = new Date(data);

        getline(file, data, ';');
        Date* receiptDate;
        (data!="-" ? receiptDate = new Date(data) : receiptDate=nullptr);

        getline(file, data, '\n');
        Date* deadlineDate;
        (data!="-" ? deadlineDate = new Date(data) : deadlineDate=nullptr);
        getline(file, data, ';');
        element->setStatus(data);

        getline(file, data, '\n');
        element->setID(data);

        //ustawianie ostatniego ID
        if(element->stringIDtoInt(data) > lastID)
            lastID = element->stringIDtoInt(data);

        element->setSender(sender);
        element->setRecipient(recipient);
        element->setPostDate(postDate);
        element->setDateOfReceipt(receiptDate);
        element->setDateOfReceiptAtTheFacility(deadlineDate);

        //sprawdzenie czy termin na odbiór paczki nie został przekroczony
        if(!isUpToDate(deadlineDate))
            element->setStatus("odeslano do nadawcy");

        //dodawanie nowego elementu do listy
        if(typeid (*element).name() == typeid(Letter).name())
        {
             Node<Letter>* node = new Node<Letter>(*dynamic_cast<Letter*>(element));
             letters->addFront(node);

        }
        else if(typeid (*element).name() == typeid(Parcel).name())
        {
            Node<Parcel>* node = new Node<Parcel>(*dynamic_cast<Parcel*>(element));
            parcels->addFront(node);
        }
        delete element;
        element = nullptr;
        }
  }
    file.close();
}

bool Database::isUpToDate(Date * deadline)
{
    if(deadline == nullptr)
        return true;

    Date today;
    if(*deadline - today < 0)
        return false;
    else
        return true;
}

void Database::addNewRecord(Letter * data)
{
    data->setID(lastID+1);
    lastID++;
    Node<Letter>* node = new Node<Letter>(*dynamic_cast<Letter*>(data));
    letters->addFront(node);
}

void Database::addNewRecord(Parcel * data)
{
    data->setID(lastID+1);
    lastID++;
    Node<Parcel>* node = new Node<Parcel>(*dynamic_cast<Parcel*>(data));
    parcels->addFront(node);

}
       //nieprzetestowane
void Database::writeFile()
{
    std::fstream file;
    file.open(filename, std::ios::out);
    bool isFirst = 1;
    if (file.is_open() && file.good())
    {
        auto headLetters = letters->getHead();

            while (headLetters)
            {
                if(!isFirst)
                    file<<"\n";

                auto type = headLetters->getCurrentData().getType();
                file<<"letter;"<<type->getIsPriority()<<';'<<type->getIsRegistered()<<';'<<type->getSize()<<'\n';

                auto sender = headLetters->getCurrentData().getSender();
                file<<sender->getName()<<';'<<sender->getPhoneNumber()<<';'<<sender->getPostCode()<<';'<<sender->getStreet()<<';'
                   <<sender->getHouseNumber()<<';'<<sender->getCity()<<';'<<sender->getCountry()<<'\n';

                auto recipent = headLetters->getCurrentData().getRecipient();
                file<<recipent->getName()<<';'<<recipent->getPhoneNumber()<<';'<<recipent->getPostCode()<<';'<<recipent->getStreet()<<';'
                <<recipent->getHouseNumber()<<';'<<recipent->getCity()<<';'<<recipent->getCountry()<<'\n';


                file<<headLetters->getCurrentData().getPostDate()->dateToString()<<';';

                if(headLetters->getCurrentData().getdateOfReceipt())
                file<<headLetters->getCurrentData().getdateOfReceipt()->dateToString()<<';';
                else
                    file <<"-;";

                if(headLetters->getCurrentData().getfinalDateOfReceiptAtTheFacility())
                file<<headLetters->getCurrentData().getfinalDateOfReceiptAtTheFacility()->dateToString()<<'\n';
                else
                    file <<"-\n";

                file<<headLetters->getCurrentData().getStatus()<<';'<<headLetters->getCurrentData().getStringID();

                headLetters = headLetters->getNext(); 
                isFirst = 0;
            }

            auto headParcels = parcels->getHead();

                while (headParcels)
                {
                    if(!isFirst)
                        file<<"\n";

                    auto type = headParcels->getCurrentData().getType();
                    file<<"parcel;"<<type->getIsPriority()<<';'<<type->getSize()<<';'<<type->getMinWeight()<<';'<<type->getMaxWeight()<<'\n';

                    auto sender = headParcels->getCurrentData().getSender();
                    file<<sender->getName()<<';'<<sender->getPhoneNumber()<<';'<<sender->getPostCode()<<';'<<sender->getStreet()<<';'
                       <<sender->getHouseNumber()<<';'<<sender->getCity()<<';'<<sender->getCountry()<<'\n';

                    auto recipent = headParcels->getCurrentData().getRecipient();
                    file<<recipent->getName()<<';'<<recipent->getPhoneNumber()<<';'<<recipent->getPostCode()<<';'<<recipent->getStreet()<<';'
                    <<recipent->getHouseNumber()<<';'<<recipent->getCity()<<';'<<recipent->getCountry()<<'\n';

                    file<<headParcels->getCurrentData().getPostDate()->dateToString()<<';';

                    if(headParcels->getCurrentData().getdateOfReceipt())
                    file<<headParcels->getCurrentData().getdateOfReceipt()->dateToString()<<';';
                    else
                        file <<"-;";

                    if(headParcels->getCurrentData().getfinalDateOfReceiptAtTheFacility())
                    file<<headParcels->getCurrentData().getfinalDateOfReceiptAtTheFacility()->dateToString()<<'\n';
                    else
                        file <<"-\n";
                    file<<headParcels->getCurrentData().getStatus()<<';'<<headParcels->getCurrentData().getStringID();

                    headParcels = headParcels->getNext();
                    isFirst = 0;
                }

    }
        file.close();
}

Database::~Database()
{

    writeFile();

    if(letters)
        delete letters;
    if(parcels)
        delete parcels;
}



