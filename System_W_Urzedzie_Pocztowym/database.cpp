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


void Database::getPersonalData(std::fstream& file, Person* &person)
{
    std::string data;

    getline(file, data, ';');
    person->setName(data);
    //phone
    getline(file, data, ';');
    person->setPhoneNumber(data);
    //postcode
    getline(file, data, ';');
    person->setPostCode(data);
    //street
    getline(file, data, ';');
    person->setStreet(data);
    //housenum
    getline(file, data, ';');
    person->setHouseNumber(data);
    //city
    getline(file, data, ';');
    person->setCity(data);
    //country
    getline(file, data, '\n');
    person->setCountry(data);
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

        Person* sender = new Person;
        getPersonalData(file, sender);

        Person* recipient = new Person;
        getPersonalData(file, recipient);


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

        if(receiptDate)
        if((Date::getCurrentDate() - receiptDate)>14)
        {
            delete element;
            element = nullptr;
            continue;
        }

        if(!isUpToDate(deadlineDate))
            element->setStatus("uplynal termin odbioru");

        element->setSender(sender);
        element->setRecipient(recipient);
        element->setPostDate(postDate);
        element->setDateOfReceipt(receiptDate);
        element->setDateOfReceiptAtTheFacility(deadlineDate);



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

void Database::addRecord(Node<Letter>* node)
{
    letters->addFront(node);
}

void Database::addRecord(Node<Parcel>* node)
{
    parcels->addFront(node);
}


void Database::changeStatus( int id, QString status)
{
    auto tmp = letters->getElement(id);
    if(tmp)
    {
        tmp->getCurrentData().setStatus(status.toStdString());
    }
    else
    {
        auto tmp = parcels->getElement(id);
        if(tmp)
    {
        tmp->getCurrentData().setStatus(status.toStdString());
    }
    }
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

std::list<Shipment*> Database::searchByID(const QString& id)
{
    auto letter = letters->getElement(id.toInt());
    auto parcel = parcels->getElement(id.toInt());

    std::list<Shipment*> returnData;
    if(letter)
    {
        returnData.push_back(&letter->getCurrentData());
        return returnData;
    }
    if(parcel)
    {
        returnData.push_back(&parcel->getCurrentData());
        return returnData;
    }
    return returnData;
}

std::list<Shipment *> Database::searchByPhoneNum(const QString & num, bool recipient)
{
    std::list<Shipment*> returnData;
    auto headLetters = letters->getHead();

        while (headLetters)
        {
            if(recipient)
            {
                if(headLetters->getCurrentData().getRecipient()->getPhoneNumber() == num.toStdString())
                    returnData.push_back(&headLetters->getCurrentData());
            }

            else
                if(headLetters->getCurrentData().getSender()->getPhoneNumber() == num.toStdString())
                    returnData.push_back(&headLetters->getCurrentData());

            headLetters = headLetters->getNext();
        }

        auto headParcels = parcels->getHead();

        while (headParcels)
        {
            if(recipient)
            {
                if(headParcels->getCurrentData().getRecipient()->getPhoneNumber() == num.toStdString())
                    returnData.push_back(&headParcels->getCurrentData());
            }

            else
                if(headParcels->getCurrentData().getSender()->getPhoneNumber() == num.toStdString())
                    returnData.push_back(&headParcels->getCurrentData());
            headParcels = headParcels->getNext();
        }
        return returnData;
}

std::list<Shipment *> Database::searchByStatus(const QString & status)
{
    auto letter = letters->getElements(status.toStdString());
    auto parcel = parcels->getElements(status.toStdString());

    std::list<Shipment*> returnData;

    for(auto it = letter.begin(); it!= letter.end(); it++)
        returnData.push_back(&(*it)->getCurrentData());

    for(auto it = parcel.begin(); it!= parcel.end(); it++)
        returnData.push_back(&(*it)->getCurrentData());

    return returnData;
}

std::list<Shipment *> Database::searchByStatus(std::list<Shipment *> & data, const QString & status)
{
    std::list<Shipment *> returnData;

    for(auto it = data.begin(); it!= data.end(); it++)
        if((*it)->getStatus() == status.toStdString())
        returnData.push_back(*it);

    return returnData;
}

Database::~Database()
{
    writeFile();

    if(letters)
        delete letters;
    if(parcels)
        delete parcels;
}
