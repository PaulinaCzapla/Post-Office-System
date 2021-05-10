#ifndef LOCALDATABASEWIDGET_H
#define LOCALDATABASEWIDGET_H

#include "person.h"
#include "database.h"
#include "QTableWidget"
#include "QComboBox"
#include "shipmentstatusmanager.h"

class LocalDatabaseWidget
{
protected:
    ShipmentStatusManager * shipmentStatuses;

private:
    QStringList getPersonData(Person*);
    void checkIfRelocate(Database*,Database*, QString, QString);
    void createTypeList(Letter &, QStringList& );
    void createTypeList(Parcel &, QStringList& );
    void createTypesList(Shipment*, QStringList&);

public:
    LocalDatabaseWidget() : shipmentStatuses(new ShipmentStatusManager){};

    void adjustTable(QTableWidget *&);
    void displaySelectedRows(QTableWidget *&, std::list<Shipment*>&);

    void addRow(QString&, QString&, QString&, QString&, QString&, QStringList&, QTableWidget *& tab, QStringList&,QStringList&, int, int );
    void loadComboBoxChangeStatus(QString, QComboBox*&);
    void changeStatus(Database* ,Database* , QString, QString);

    template <typename T>
    void loadTable(List<T>*, QTableWidget *&);

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
            QString ID, status, sendDate, receiptDate, deadline;

            auto data = head->getCurrentData();
            createTypesList(&data, type);           

            QStringList recipient = getPersonData(data.getRecipient());
            QStringList sender = getPersonData(data.getSender());

            ID = QString::fromStdString(data.getStringID());
            status = QString::fromStdString(data.getStatus());
            (data.getPostDate()== nullptr ? sendDate = "-" : sendDate = QString::fromStdString(data.getPostDate()->dateToString()));
            (data.getdateOfReceipt()== nullptr ? receiptDate = "-" : receiptDate = QString::fromStdString(data.getdateOfReceipt()->dateToString()));
            (data.getfinalDateOfReceiptAtTheFacility()== nullptr ? deadline = "-" : deadline = QString::fromStdString(data.getfinalDateOfReceiptAtTheFacility()->dateToString()));

            addRow(ID, status, sendDate, receiptDate, deadline, type, tab, sender, recipient, i, j);

            head = head->getNext();
        }
        tab->resizeColumnsToContents();
        tab->resizeRowsToContents();
}

#endif // LOCALDATABASEWIDGET_H
