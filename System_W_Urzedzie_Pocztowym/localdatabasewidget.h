#ifndef LOCALDATABASEWIDGET_H
#define LOCALDATABASEWIDGET_H

#include "mainmenuwidget.h"


class LocalDatabaseWidget
{
protected:

public:
    template <typename T>
    void loadTable(List<T>*, QTableWidget *&);
    void adjustTable(QTableWidget *&);
    void displaySelectedRows(QTableWidget *&, std::list<Shipment*>&);
  //  void removeRows(QTableWidget *&, const QString& );
    void createTypeList(Letter &, QStringList& );
    void createTypeList(Parcel &, QStringList& );
    void createTypesList(Shipment*, QStringList&);

};



template <typename T>
void LocalDatabaseWidget::loadTable(List<T> * shipmentsList, QTableWidget *& tab)
{
    int i =0, j =0;
    auto head = shipmentsList->getHead();

        while (head)
        {
            j =0;
            QStringList type;
            QStringList recipient;
            QStringList sender;

            QString ID, status, sendDate, receiptDate, deadline, createTypeList(Letter &, QStringList &);

            auto data = head->getCurrentData();
            createTypesList(&data, type);

            sender.push_back(QString::fromStdString(data.getSender()->getName()));
            sender.push_back(QString::fromStdString(data.getSender()->getPhoneNumber()));
            sender.push_back(QString::fromStdString(data.getSender()->getCountry()));
            sender.push_back(QString::fromStdString(data.getSender()->getCity()));
            sender.push_back(QString::fromStdString(data.getSender()->getStreet() + " " + data.getSender()->getHouseNumber()));
            sender.push_back(QString::fromStdString(data.getSender()->getPostCode()));
            sender.push_back(QString::fromStdString(data.getSender()->getCountry()));


            recipient.push_back(QString::fromStdString(data.getRecipient()->getName()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getPhoneNumber()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getCountry()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getCity()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getStreet() + " " + data.getRecipient()->getHouseNumber()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getPostCode()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getCountry()));

            ID = QString::fromStdString(data.getStringID());
            status = QString::fromStdString(data.getStatus());
            (data.getPostDate()== nullptr ? sendDate = "-" : sendDate = QString::fromStdString(data.getPostDate()->dateToString()));
            (data.getdateOfReceipt()== nullptr ? receiptDate = "-" : receiptDate = QString::fromStdString(data.getdateOfReceipt()->dateToString()));
            (data.getfinalDateOfReceiptAtTheFacility()== nullptr ? deadline = "-" : deadline = QString::fromStdString(data.getfinalDateOfReceiptAtTheFacility()->dateToString()));

            tab->insertRow(i);

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

            if(status == "uplynal termin odbioru")
            {
            item5->setForeground(Qt::red);
            item2->setForeground(Qt::red);
            }

            head = head->getNext();
        }
        tab->resizeColumnsToContents();
}

#endif // LOCALDATABASEWIDGET_H
