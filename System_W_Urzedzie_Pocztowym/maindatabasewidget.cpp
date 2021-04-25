#include "maindatabasewidget.h"


void MainDatabaseWidget::loadComboBoxChangeStatus(QString current, QComboBox*& comboBox)
{
    comboBox->blockSignals(true);
    comboBox->clear();
    if(current=="w drodze")
    {
     comboBox->addItem(current);
     comboBox->addItems(shipmentStatuses->returnAvailableStatuses(current.toStdString()));
    }
    comboBox->blockSignals(false);
}

void MainDatabaseWidget::changeStatus(Database * mainDatabase, Database * localDatabase, QString status, QString id)
{
    mainDatabase->changeStatus(id.toInt(), status);
    checkIfRelocate(mainDatabase, localDatabase, status, id);
}

void MainDatabaseWidget::checkIfRelocate(Database * mainDatabase, Database * localDatabase, QString status, QString id)
{
        if(status == "oczekuje na odbior w placowce" || status == "oczekuje na wreczenie kurierowi" || status == "wreczono kurierowi do doreczenia")
        {
           if(auto letter = mainDatabase->getLetters()->getElement(id.toInt()))
           {
               if(status == "oczekuje na odbior w placowce")
               {
                   Date finalDate;
                   finalDate = finalDate + 7;
                   letter->getCurrentData().setDateOfReceiptAtTheFacility(new Date(finalDate));
               }
               Node<Letter>* copy = new Node<Letter>(letter);
               localDatabase->addRecord(copy);
           }
           else if(auto parcel = mainDatabase->getParcels()->getElement(id.toInt()))
            {
               if(status == "oczekuje na odbior w placowce")
               {
                   Date finalDate;
                   finalDate = finalDate + 7;
                   parcel->getCurrentData().setDateOfReceiptAtTheFacility(new Date(finalDate));
               }
               Node<Parcel>* copy = new Node<Parcel>(parcel);
               localDatabase->addRecord(copy);
           }
        }
}
