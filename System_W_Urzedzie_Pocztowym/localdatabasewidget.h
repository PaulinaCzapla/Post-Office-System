#ifndef LOCALDATABASEWIDGET_H
#define LOCALDATABASEWIDGET_H

#include "mainmenuwidget.h"
#include "shipmentstatusmanager.h"

class LocalDatabaseWidget
{
protected:
    ShipmentStatusManager * shipmentStatuses;
public:
    LocalDatabaseWidget() : shipmentStatuses(new ShipmentStatusManager){};

    template <typename T>
    void loadTable(List<T>*, QTableWidget *&);

    void adjustTable(QTableWidget *&);
    void displaySelectedRows(QTableWidget *&, std::list<Shipment*>&);
    void createTypeList(Letter &, QStringList& );
    void createTypeList(Parcel &, QStringList& );
    void createTypesList(Shipment*, QStringList&);

    void loadComboBoxChangeStatus(QString, QComboBox*&);


    void changeStatus(Database* ,Database* , QString, QString);
    void checkIfRelocate(Database*,Database*, QString, QString);

private:
    QStringList getPersonData(Person*);
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

            sender = getPersonData(data.getSender());
            recipient = getPersonData(data.getRecipient());

            ID = QString::fromStdString(data.getStringID());
            status = QString::fromStdString(data.getStatus());
            (data.getPostDate()== nullptr ? sendDate = "-" : sendDate = QString::fromStdString(data.getPostDate()->dateToString()));
            (data.getdateOfReceipt()== nullptr ? receiptDate = "-" : receiptDate = QString::fromStdString(data.getdateOfReceipt()->dateToString()));
            (data.getfinalDateOfReceiptAtTheFacility()== nullptr ? deadline = "-" : deadline = QString::fromStdString(data.getfinalDateOfReceiptAtTheFacility()->dateToString()));

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

            head = head->getNext();
        }
        tab->resizeColumnsToContents();
        tab->resizeRowsToContents();
}

#endif // LOCALDATABASEWIDGET_H
