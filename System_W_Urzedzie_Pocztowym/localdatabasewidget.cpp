#include "localdatabasewidget.h"
#include <QComboBox>

void LocalDatabaseWidget::adjustTable(QTableWidget *&tab)
{
    // ID //typ // status// Data wysylki // data odbioru // data odbioru w pl // nadawca // odbiorca
  tab->setColumnCount(8);
  QStringList labels;

  labels.push_back("ID");
  labels.push_back("Typ");
  labels.push_back("Status");
  labels.push_back("Nadawca");
  labels.push_back("Odbiorca");
  labels.push_back("Data wysyłki");
  labels.push_back("Data odbioru");
  labels.push_back("Termin odbioru");

  tab->setHorizontalHeaderLabels(labels);
  tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QStringList LocalDatabaseWidget::getPersonData(Person* person)
{
    QStringList list;
    list.push_back(QString::fromStdString(person->getName()));
    list.push_back(QString::fromStdString(person->getPhoneNumber()));
    list.push_back(QString::fromStdString(person->getCity()));
    list.push_back(QString::fromStdString(person->getStreet() + " " + person->getHouseNumber()));
    list.push_back(QString::fromStdString(person->getPostCode()));
    list.push_back(QString::fromStdString(person->getCountry()));
    return list;
}

void LocalDatabaseWidget::displaySelectedRows(QTableWidget *& tab, std::list<Shipment *> & shipmentsList)
{
    int i =0, j =0;
    tab->setRowCount(0);

        for(auto it = shipmentsList.begin() ; it!=shipmentsList.end(); it++)
        {
            QStringList type;
            QStringList recipient;
            QStringList sender;

            QString ID, status, sendDate, receiptDate, deadline, createTypeList(Letter &, QStringList &);

            auto data = *it;
            createTypesList(data, type);

            sender = getPersonData(data->getSender());
            recipient = getPersonData(data->getRecipient());

            ID = QString::fromStdString(data->getStringID());
            status = QString::fromStdString(data->getStatus());
            (data->getPostDate()== nullptr ? sendDate = "-" : sendDate = QString::fromStdString(data->getPostDate()->dateToString()));
            (data->getdateOfReceipt()== nullptr ? receiptDate = "-" : receiptDate = QString::fromStdString(data->getdateOfReceipt()->dateToString()));
            (data->getfinalDateOfReceiptAtTheFacility()== nullptr ? deadline = "-" : deadline = QString::fromStdString(data->getfinalDateOfReceiptAtTheFacility()->dateToString()));

            tab->insertRow(i);

            QTableWidgetItem* itemID = new QTableWidgetItem;
            itemID->setText(ID);
            itemID->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,itemID);
            j++;


            QTableWidgetItem* itemType = new QTableWidgetItem;
            itemType->setText(type[0] + "\n" + type[1]+ "\n" + type[2]+ "\n" + type[3]);
            itemType->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,itemType);
            j++;


            QTableWidgetItem* itemStatus = new QTableWidgetItem;
            itemStatus->setText(status);
            itemStatus->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,itemStatus);
            j++;

            QTableWidgetItem* itemSender = new QTableWidgetItem;
            itemSender->setText(sender[0] + "\n" + sender[1]+ "\n" +sender[2]+ "\n" + sender[3]+ "\n" + sender[4]+ "\n" + sender[5]);
            itemSender->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,itemSender);
            j++;

            QTableWidgetItem* itemRecipient = new QTableWidgetItem;
            itemRecipient->setText(recipient[0] + "\n" + recipient[1]+ "\n" +recipient[2]+ "\n" + recipient[3]+ "\n" + recipient[4]+ "\n" + recipient[5]);
            itemRecipient->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,itemRecipient);
            j++;

            QTableWidgetItem* item3 = new QTableWidgetItem;
            item3->setText(sendDate);
            item3->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,item3);
            j++;

            QTableWidgetItem* item4 = new QTableWidgetItem;
            item4->setText(receiptDate);
            item4->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,item4);
            j++;

            QTableWidgetItem* item5 = new QTableWidgetItem;
            item5->setText(deadline);
            item5->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,item5);
            j++;
            i++;

            if(status == "uplynal termin odbioru")
            {
            item5->setForeground(Qt::red);
            itemStatus->setForeground(Qt::red);
            }
        }
        tab->resizeRowsToContents();
        tab->resizeColumnsToContents();
}


void LocalDatabaseWidget::createTypeList(Letter & data, QStringList & type)
{
    QString tmp = "";
   // data.setType(dynamic_cast<LetterType*>(data.getType()));
    type.push_back("list");
    (data.getType()->getIsPriority() == true ?  type.push_back("priorytetowy") : type.push_back("zwykły"));
    (data.getType()->getIsRegistered() == true ?  type.push_back("rejestrowany") : type.push_back("nierejestrowany"));
    type.push_back(tmp+data.getType()->getSize());
}

void LocalDatabaseWidget::createTypeList(Parcel & data, QStringList & type)
{
    QString tmp = "";
    type.push_back("paczka");
    (data.getType()->getIsPriority() == true ?  type.push_back("priorytetowy") : type.push_back("zwykły"));
    type.push_back(tmp+data.getType()->getSize());
    type.push_back(QString::number(data.getType()->getMinWeight()) + " - " + QString::number(data.getType()->getMaxWeight())+" kg" );

}

void LocalDatabaseWidget::createTypesList(Shipment * data, QStringList & type)
{
    if(typeid(*data).name()==typeid (Letter).name())
    createTypeList(*dynamic_cast<Letter*>(data), type);

    if(typeid(*data).name()==typeid (Parcel).name())
        createTypeList(*dynamic_cast<Parcel*>(data), type);
}

void LocalDatabaseWidget::loadComboBoxChangeStatus(QString current, QComboBox*& comboBox)
{
    comboBox->blockSignals(true);
    comboBox->clear();
    if(current!="w drodze")
    {
    comboBox->addItem(current);
    comboBox->addItems(shipmentStatuses->returnAvailableStatuses(current.toStdString()));
    }
    comboBox->blockSignals(false);
}


void LocalDatabaseWidget::changeStatus(Database * mainDatabase, Database * localDatabase, QString status, QString id)
{
    localDatabase->changeStatus(id.toInt(), status);
    checkIfRelocate(mainDatabase, localDatabase, status, id);
}

void LocalDatabaseWidget::checkIfRelocate(Database * mainDatabase, Database * localDatabase, QString status, QString id)
{
    if(status == "w drodze" || status == "odeslano do nadawcy")
    {
       if(auto letter = localDatabase->getLetters()->getElement(id.toInt()))
       {
           mainDatabase->getLetters()->getElement(id.toInt())->getCurrentData().setStatus(status.toStdString());
           localDatabase->getLetters()->deleteElement(letter);
       }
       else if(auto parcel = localDatabase->getParcels()->getElement(id.toInt()))
        {
           mainDatabase->getParcels()->getElement(id.toInt())->getCurrentData().setStatus(status.toStdString());
           localDatabase->getParcels()->deleteElement(parcel);
       }
    }
    else
    {
        if(auto letter = localDatabase->getLetters()->getElement(id.toInt()))
        {
            if(status == "doreczono")
            {
                letter->getCurrentData().setDateOfReceipt(new Date());
            }
        }
        else if(auto parcel = localDatabase->getParcels()->getElement(id.toInt()))
         {
            if(status == "doreczono")
            {
                parcel->getCurrentData().setDateOfReceipt(new Date());
            }
        }
    }
}
