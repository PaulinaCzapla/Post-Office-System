#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <stdlib.h>
#include "QMessageBox"
#include "shipmentformwidget.h"
#include "localdatabasewidget.h"
#include "maindatabasewidget.h"
#include "shipmentprices.h"
#include<vector>

#include <QVector>
#include <QListWidget>
#include <QCloseEvent>

#define FILENAME_LOCAL_DATABASE "localdatabase.csv"
#define FILENAME_MAIN_DATABASE "maindatabase.csv"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    shipmentForm = new ShipmentFormWidget();
    localDatabaseWidget= new LocalDatabaseWidget();
    mainDatabaseWidget = new MainDatabaseWidget();
    shipmentPricesManager = new ShipmentPrices();
    localDatabase = new Database(FILENAME_LOCAL_DATABASE);
    mainDatabase = new Database(FILENAME_MAIN_DATABASE);

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    getFormDataFromComboBoxes();
    adjustTable(ui->tableWidgetLocalDatabase);
    adjustTable(ui->tableWidgetMainDatabase);
   // loadTable(shipmentForm->databases->getLocalDatabaseLetters(), shipmentForm->databases->getLocalDatabaseParcels(), ui->tableWidgetLocalDatabase);
}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButtonRegisterParcel_clicked()
{
    qDebug() << "register";

    auto comboBoxes = getFormDataFromComboBoxes();
    shipmentForm->loadDataToComboBoxes(comboBoxes);
    ui->comboBoxShipmentType->setCurrentIndex(0);

    setDefaultLineEdits();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonLocalDatabase_clicked()
{
    qDebug() << "local database";
    loadTable(localDatabase->getLetters(), localDatabase->getParcels(), ui->tableWidgetLocalDatabase);

    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButtonMainDatabase_clicked()
{
    qDebug() << "main database";
    loadTable(mainDatabase->getLetters(), mainDatabase->getParcels(), ui->tableWidgetMainDatabase);

    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Zamknij program");
    msgBox.setText("Czy na pewno chcesz wyjść z programu? Zmiany zostaną zapisane.");
    msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Ok)
    {
        saveDatabase();
        delete shipmentForm;
        delete localDatabaseWidget;
        delete mainDatabaseWidget;
        delete shipmentPricesManager;
        delete localDatabase;
        delete mainDatabase;
         event->accept();

        exit(1);
    }
    if(ret==QMessageBox::Cancel)
        event->ignore();
}

void MainWindow::lackOfDataDialog_pop()
{
    QMessageBox::warning(this, "Brak danych", "Nie wprowadzono danych o przesyłce.", QMessageBox::Ok);
}

void MainWindow::invalidDataDialog_pop()
{
     QMessageBox::warning(this, "Błędne dane", "Wprowadzono nieprawidłowe dane.", QMessageBox::Ok);
}

void MainWindow::on_pushButtonCancel_Page1_clicked()
{
    clearForm();
    ui->stackedWidget->setCurrentIndex(0);
}

std::map<shipmentTypeInfo,QComboBox *> MainWindow::getFormDataFromComboBoxes()
{
    std::map<shipmentTypeInfo, QComboBox*> comboBoxes;

    comboBoxes.insert(std::pair<shipmentTypeInfo, QComboBox*> (type, ui->comboBoxShipmentType));
    comboBoxes.insert(std::pair<shipmentTypeInfo, QComboBox*>(isRegistered, ui->comboBoxRegistered));
    comboBoxes.insert(std::pair<shipmentTypeInfo, QComboBox*>(isPriority, ui->comboBoxPriority));
    comboBoxes.insert(std::pair<shipmentTypeInfo, QComboBox*>(shipmentTypeInfo::size, ui->comboBoxSize));
    comboBoxes.insert(std::pair<shipmentTypeInfo, QComboBox*>(weight, ui->comboBoxWeight));
    comboBoxes.insert(std::pair<shipmentTypeInfo, QComboBox*>(country, ui->comboBoxCountry));

    shipmentForm->loadDataToComboBoxes(comboBoxes);
    return comboBoxes;
}

void MainWindow::on_pushButtonConfirm_Page1_clicked()
{
     ui->labelPrice->clear();
    qDebug() << "confirm";
    std::string type = ui->comboBoxShipmentType->currentText().toStdString();

    if(!type.empty())
    {
      auto comboBoxes = getFormDataFromComboBoxes();
      auto shipmentType = shipmentForm->saveComboBoxInfo(comboBoxes);
     qDebug()<<"tworzenie ceny confirm";
    ui->labelPrice->setText( shipmentPricesManager->returnProperPrice(shipmentPricesManager->getShipmentPrice(shipmentType))+ " zł"); //do debugowania

    }
    else
        lackOfDataDialog_pop();
}
void MainWindow::on_pushButtonConfirmAndGo_clicked()
{
  //  ui->labelPrice->clear();
    qDebug() << "go";

    std::string type = ui->comboBoxShipmentType->currentText().toStdString();
    if(!type.empty())
    {
        auto comboBoxes = getFormDataFromComboBoxes();
        auto shipmentType = shipmentForm->saveComboBoxInfo(comboBoxes);
    qDebug()<<"tworzenie ceny confirm and go";
    ui->labelPrice->setText( shipmentPricesManager->returnProperPrice(shipmentPricesManager->getShipmentPrice(shipmentType)) + " zł");

    //wyświetlanie ID przesyłki
    std::string str = Shipment::intIDtoString(Database::getLastID()+1);
    QString stde(str.c_str());
    ui->label_ShipmentID->setText(stde);

    ui->stackedWidget->setCurrentIndex(2);
    }
    else
        lackOfDataDialog_pop();
}


//pobranie danych z formualrza

void MainWindow::getFormData(std::map<dataInfo, std::string> & sender, std::map<dataInfo, std::string>& recipient)
{
    sender.insert(std::pair<dataInfo, std::string>(name ,ui->lineEdit_SenderName->text().toStdString()));
    sender.insert(std::pair<dataInfo, std::string>(phoneNumber,ui->lineEdit_SenderPhone->text().toStdString()));
    sender.insert(std::pair<dataInfo, std::string>(street ,ui->lineEdit_SenderStreet->text().toStdString()));
    sender.insert(std::pair<dataInfo, std::string>(houseNumber ,ui->lineEdit_SenderHouseNum->text().toStdString()));
    sender.insert(std::pair<dataInfo, std::string>(postCode ,ui->lineEdit_SenderPostCode->text().toStdString()));
    sender.insert(std::pair<dataInfo, std::string>(city ,ui->lineEdit_SenderTown->text().toStdString()));

    recipient.insert(std::pair<dataInfo, std::string>(name ,ui->lineEdit_RecipientName->text().toStdString()));
    recipient.insert(std::pair<dataInfo, std::string>(phoneNumber,ui->lineEdit_RecipientPhone->text().toStdString()));
    recipient.insert(std::pair<dataInfo, std::string>(street ,ui->lineEdit_RecipientStreet->text().toStdString()));
    recipient.insert(std::pair<dataInfo, std::string>(houseNumber ,ui->lineEdit_RecipientHouseNum->text().toStdString()));
    recipient.insert(std::pair<dataInfo, std::string>(postCode ,ui->lineEdit_RecipientPostCode->text().toStdString()));
    recipient.insert(std::pair<dataInfo, std::string>(city ,ui->lineEdit_RecipientTown->text().toStdString()));
}

//mozna przeniesc
void MainWindow::checkInvalidData(std::pair<std::vector<dataInfo> *, std::vector<dataInfo> *> * invalidData)
{
    if(!invalidData->first->empty())
    {
     for (std::vector<dataInfo>::iterator it = invalidData->first->begin(); it!=invalidData->first->end(); ++it)
     {
         if(*it == name)
           ui->lineEdit_SenderName->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

         if(*it == phoneNumber)
             ui->lineEdit_SenderPhone->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

         if(*it == street)
             ui->lineEdit_SenderStreet->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

         if(*it == postCode)
             ui->lineEdit_SenderPostCode->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

         if(*it == city)
             ui->lineEdit_SenderTown->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

         if(*it == houseNumber)
             ui->lineEdit_SenderHouseNum->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

        }
    }
    if(!invalidData->second->empty())
    {
      for (std::vector<dataInfo>::iterator it = invalidData->second->begin(); it!=invalidData->second->end(); ++it)
      {
          if(*it == name)
          {
            ui->lineEdit_RecipientName->clear();
            ui->lineEdit_RecipientName->setStyleSheet("border: 2px solid rgb(209, 7, 10)");
          }
          if(*it == phoneNumber)
          {
              ui->lineEdit_RecipientPhone->clear();
              ui->lineEdit_RecipientPhone->setStyleSheet("border: 2px solid rgb(209, 7, 10)");
          }
          if(*it == street)
          {
              ui->lineEdit_RecipientStreet->clear();
              ui->lineEdit_RecipientStreet->setStyleSheet("border: 2px solid rgb(209, 7, 10)");
          }
          if(*it == postCode) //zawsze POL
          {
              ui->lineEdit_RecipientPostCode->clear();
              ui->lineEdit_RecipientPostCode->setStyleSheet("border: 2px solid rgb(209, 7, 10)");
          }
          if(*it == city)
          {
              ui->lineEdit_RecipientTown->clear();
              ui->lineEdit_RecipientTown->setStyleSheet("border: 2px solid rgb(209, 7, 10)");
          }
          if(*it == houseNumber)
          {
              ui->lineEdit_RecipientHouseNum->clear();
              ui->lineEdit_RecipientHouseNum->setStyleSheet("border: 2px solid rgb(209, 7, 10)");
          }
      }
    }
}

//można przeniesc
void MainWindow::setDefaultLineEdits()
{
    //ustawienie domyślnego wyglądu (dla poprawnych danych)
      ui->lineEdit_SenderName->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_SenderPhone->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_SenderStreet->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_SenderPostCode->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_SenderTown->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_SenderHouseNum->setStyleSheet("border: 1px solid rgb(105, 105, 105)");

      ui->lineEdit_RecipientName->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_RecipientPhone->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_RecipientStreet->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_RecipientPostCode->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_RecipientTown->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
      ui->lineEdit_RecipientHouseNum->setStyleSheet("border: 1px solid rgb(105, 105, 105)");
}

//można przeniesc
void MainWindow::clearForm()
{
    setDefaultLineEdits();
    ui->lineEdit_SenderName->clear();
    ui->lineEdit_SenderPhone->clear();
    ui->lineEdit_SenderStreet->clear();
    ui->lineEdit_SenderPostCode->clear();
    ui->lineEdit_SenderTown->clear();
    ui->lineEdit_SenderHouseNum->clear();

    ui->lineEdit_RecipientName->clear();
    ui->lineEdit_RecipientPhone->clear();
    ui->lineEdit_RecipientStreet->clear();
    ui->lineEdit_RecipientPostCode->clear();
    ui->lineEdit_RecipientTown->clear();
    ui->lineEdit_RecipientHouseNum->clear();
}


void MainWindow::on_pushButtonConfirm_Page2_clicked()
{
    std::map<dataInfo, std::string> sender;
    std::map<dataInfo, std::string> recipient;
    getFormData(sender, recipient);

    //para wektorów przechowująca informacje o niepoprawnych danych
    std::pair<std::vector<dataInfo>*, std::vector<dataInfo>*>* invalidData = shipmentForm->processFormData(sender, recipient);

    //warunek dla nieprawidłowych danych w formularzu
    if(!invalidData->first->empty() || !invalidData->second->empty())
    {
        invalidDataDialog_pop();
        setDefaultLineEdits();
        checkInvalidData(invalidData);
        sender.clear();
        recipient.clear();

        //zwolnienie pamięci zaalokowanej w processFormData
        delete invalidData->first;
        delete invalidData->second;
        delete invalidData;
    }
    else
    {
        //dodanie rekordu z poprawnymi danymi
     shipmentForm->insertRecord(sender, recipient, localDatabase, mainDatabase);
        // ekran z potwierdzeniem dodania
     //wyświetlanie ID przesyłki
     std::string str = Shipment::intIDtoString(Database::getLastID());
     QString stde(str.c_str());
     ui->label_ShipmentID_2->setText(stde);

    ui->stackedWidget->setCurrentIndex(5);
    }
}

void MainWindow::on_pushButtonGoBack_Page2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_pushButtonPrintLabel_clicked()
{

}

void MainWindow::on_pushButtonGoBack_LocalDatabase_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->tableWidgetLocalDatabase->setRowCount(0);
}


void MainWindow::on_comboBoxShipmentType_currentIndexChanged(const QString &arg1)
{
     ui->labelPrice->clear();
     getFormDataFromComboBoxes();
}

void MainWindow::on_pushButton_FinishAddingNewRecord_clicked()
{
    clearForm();
    ui->stackedWidget->setCurrentIndex(0);
}

//do przeniesienia
void MainWindow::adjustTable(QTableWidget *&tab)
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

//do przeniesienia i refaktoryzacji
void MainWindow::loadTable(List<Letter> * lettersList, List<Parcel> * parcelsList,QTableWidget *& tab)
{
    int i =0, j =0;
    auto headLetters = lettersList->getHead();

        while (headLetters)
        {
            QStringList type;
            QStringList recipient;
            QStringList sender;

            QString ID, status, sendDate, receiptDate, deadline, tmp="";

            auto data = headLetters->getCurrentData();

            type.push_back("list");
            (data.getType()->getIsPriority() == true ?  type.push_back("priorytetowy") : type.push_back("zwykły"));
            (data.getType()->getIsRegistered() == true ?  type.push_back("rejestrowany") : type.push_back("nierejestrowany"));
            type.push_back(tmp+data.getType()->getSize());

            sender.push_back(QString::fromStdString(data.getSender()->getName()));
            sender.push_back(QString::fromStdString(data.getSender()->getPhoneNumber()));
            sender.push_back(QString::fromStdString(data.getSender()->getCountry()));
            sender.push_back(QString::fromStdString(data.getSender()->getCity()));
            sender.push_back(QString::fromStdString(data.getSender()->getStreet() + " " + data.getSender()->getHouseNumber()));
            sender.push_back(QString::fromStdString(data.getSender()->getPostCode()));


            recipient.push_back(QString::fromStdString(data.getRecipient()->getName()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getPhoneNumber()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getCountry()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getCity()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getStreet() + " " + data.getRecipient()->getHouseNumber()));
            recipient.push_back(QString::fromStdString(data.getRecipient()->getPostCode()));

            ID = QString::fromStdString(data.getStringID());
            status = QString::fromStdString(data.getStatus());
            (data.getPostDate()== nullptr ? sendDate = "-" : sendDate = QString::fromStdString(data.getPostDate()->dateToString()));
            (data.getdateOfReceipt()== nullptr ? receiptDate = "-" : receiptDate = QString::fromStdString(data.getdateOfReceipt()->dateToString()));
            (data.getfinalDateOfReceiptAtTheFacility()== nullptr ? deadline = "-" : deadline = QString::fromStdString(data.getfinalDateOfReceiptAtTheFacility()->dateToString()));

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

           tab->setItem(i,j,item2);
           i++;

            headLetters = headLetters->getNext();
        }
        tab->resizeColumnsToContents();
        i =0;
        j =0;
        auto headParcels = parcelsList->getHead();

            while (headParcels)
            {
                QStringList type;
                QStringList recipient;
                QStringList sender;

                QString ID, status, sendDate, receiptDate, deadline, tmp="";

                auto data = headParcels->getCurrentData();

                type.push_back("paczka");
                (data.getType()->getIsPriority() == true ?  type.push_back("priorytetowy") : type.push_back("zwykły"));
                type.push_back(tmp+data.getType()->getSize());
                type.push_back(QString::number(data.getType()->getMinWeight()) + " - " + QString::number(data.getType()->getMaxWeight())+" kg" );

                sender.push_back(QString::fromStdString(data.getSender()->getName()));
                sender.push_back(QString::fromStdString(data.getSender()->getPhoneNumber()));
                sender.push_back(QString::fromStdString(data.getSender()->getCountry()));
                sender.push_back(QString::fromStdString(data.getSender()->getCity()));
                sender.push_back(QString::fromStdString(data.getSender()->getStreet() + " " + data.getSender()->getHouseNumber() ));
                sender.push_back(QString::fromStdString(data.getSender()->getPostCode()));
                recipient.push_back(QString::fromStdString(data.getRecipient()->getName()));
                recipient.push_back(QString::fromStdString(data.getRecipient()->getPhoneNumber()));
                recipient.push_back(QString::fromStdString(data.getRecipient()->getCountry()));
                recipient.push_back(QString::fromStdString(data.getRecipient()->getCity()));
                recipient.push_back(QString::fromStdString(data.getRecipient()->getStreet() + " " + data.getRecipient()->getHouseNumber()));
                recipient.push_back(QString::fromStdString(data.getRecipient()->getPostCode()));

                ID = QString::fromStdString(data.getStringID());
                status = QString::fromStdString(data.getStatus());
                (data.getPostDate()== nullptr ? sendDate = "-" : sendDate = QString::fromStdString(data.getPostDate()->dateToString()));
                (data.getdateOfReceipt()== nullptr ? receiptDate = "-" : receiptDate = QString::fromStdString(data.getdateOfReceipt()->dateToString()));
                (data.getfinalDateOfReceiptAtTheFacility()== nullptr ? deadline = "-" : deadline = QString::fromStdString(data.getfinalDateOfReceiptAtTheFacility()->dateToString()));

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

               tab->setItem(i,j,item2);
               i++;

                headParcels = headParcels->getNext();
            }

            tab->resizeColumnsToContents();
}

void MainWindow::on_pushButtonGoBack_MainDatabase_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

