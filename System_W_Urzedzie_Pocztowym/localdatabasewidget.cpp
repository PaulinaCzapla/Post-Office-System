#include "localdatabasewidget.h"


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

            sender.push_back(QString::fromStdString(data->getSender()->getName()));
            sender.push_back(QString::fromStdString(data->getSender()->getPhoneNumber()));
            sender.push_back(QString::fromStdString(data->getSender()->getCountry()));
            sender.push_back(QString::fromStdString(data->getSender()->getCity()));
            sender.push_back(QString::fromStdString(data->getSender()->getStreet() + " " + data->getSender()->getHouseNumber()));
            sender.push_back(QString::fromStdString(data->getSender()->getPostCode()));


            recipient.push_back(QString::fromStdString(data->getRecipient()->getName()));
            recipient.push_back(QString::fromStdString(data->getRecipient()->getPhoneNumber()));
            recipient.push_back(QString::fromStdString(data->getRecipient()->getCountry()));
            recipient.push_back(QString::fromStdString(data->getRecipient()->getCity()));
            recipient.push_back(QString::fromStdString(data->getRecipient()->getStreet() + " " + data->getRecipient()->getHouseNumber()));
            recipient.push_back(QString::fromStdString(data->getRecipient()->getPostCode()));

            ID = QString::fromStdString(data->getStringID());
            status = QString::fromStdString(data->getStatus());
            (data->getPostDate()== nullptr ? sendDate = "-" : sendDate = QString::fromStdString(data->getPostDate()->dateToString()));
            (data->getdateOfReceipt()== nullptr ? receiptDate = "-" : receiptDate = QString::fromStdString(data->getdateOfReceipt()->dateToString()));
            (data->getfinalDateOfReceiptAtTheFacility()== nullptr ? deadline = "-" : deadline = QString::fromStdString(data->getfinalDateOfReceiptAtTheFacility()->dateToString()));

            tab->insertRow(i);
             j =0;

            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(ID);
            item->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,item);
            j++;

            QComboBox* combo = new QComboBox();

            combo->insertItems(0,type);
            combo->setStyleSheet("background-color: white ");
            tab->setCellWidget(i,j, combo);
            j++;

            QTableWidgetItem* item2 = new QTableWidgetItem;
            item2->setText(status);
            item2->setTextAlignment(Qt::AlignCenter);
            tab->setItem(i,j,item2);
            j++;

            QComboBox* combo2 = new QComboBox();
            combo2->setStyleSheet("background-color: white ");
            combo2->insertItems(0,sender);
            tab->setCellWidget(i,j, combo2);

            j++;
           QComboBox* combo3 = new QComboBox();
           combo3->setStyleSheet("background-color: white ");
           combo3->insertItems(0,recipient);
           tab->setCellWidget(i,j, combo3);
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
        }
        tab->resizeColumnsToContents();
}

//void LocalDatabaseWidget::removeRows(QTableWidget *& tab, const QString& shipmentData)
//{
//    for(int i = 0; i<tab->rowCount(); i++)
//    {
//       if(tab->itemAt(i, 1)->text() != shipmentData)

//    }
//}

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

