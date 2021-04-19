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
    localDatabaseWidget->adjustTable(ui->tableWidgetLocalDatabase);
    mainDatabaseWidget->adjustTable(ui->tableWidgetMainDatabase);

    shipmentForm->loadComboBoxSearch(ui->comboBox_SearchFor_LocalDatabase);
    shipmentForm->loadComboBoxSearch(ui->comboBox_SearchFor_MainDatabase);
    shipmentForm->loadComboBoxSearchStatus(ui->comboBox_SearchForStatus_LocalDatabase);
    shipmentForm->loadComboBoxSearchStatus(ui->comboBox_SearchForStatus_MainDatabase);

    indexes.insert(std::pair<shipmentTypeInfo, int> (type, -1));
    indexes.insert(std::pair<shipmentTypeInfo, int> (isRegistered, -1));
    indexes.insert(std::pair<shipmentTypeInfo, int> (isPriority, -1));
    indexes.insert(std::pair<shipmentTypeInfo, int> (weight, -1));
    indexes.insert(std::pair<shipmentTypeInfo, int> (shipmentTypeInfo::size, -1));
    indexes.insert(std::pair<shipmentTypeInfo, int> (shipmentTypeInfo::country, -1));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRegisterParcel_clicked()
{
    auto comboBoxes = getFormDataFromComboBoxes();
    shipmentForm->loadDataToComboBoxes(comboBoxes);
    ui->comboBoxShipmentType->setCurrentIndex(0);

    setDefaultLineEdits();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonLocalDatabase_clicked()
{
    ui->tableWidgetLocalDatabase->setRowCount(0);
    localDatabaseWidget->loadTable<Letter>(localDatabase->getLetters(), ui->tableWidgetLocalDatabase);
    localDatabaseWidget->loadTable<Parcel>(localDatabase->getParcels(), ui->tableWidgetLocalDatabase);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButtonMainDatabase_clicked()
{
    ui->tableWidgetMainDatabase->setRowCount(0);
    mainDatabaseWidget->loadTable<Letter>(mainDatabase->getLetters(), ui->tableWidgetMainDatabase);
    mainDatabaseWidget->loadTable<Parcel>(mainDatabase->getParcels(), ui->tableWidgetMainDatabase);
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
    comboBoxes.insert(std::pair<shipmentTypeInfo, QComboBox*>(shipmentTypeInfo::country, ui->comboBoxCountry));

    shipmentForm->loadDataToComboBoxes(comboBoxes);
    return comboBoxes;
}

void MainWindow::on_pushButtonConfirmAndGo_clicked()
{
    std::string type = ui->comboBoxShipmentType->currentText().toStdString();
    if(!type.empty())
    {
        auto comboBoxes = getFormDataFromComboBoxes();
        auto shipmentType = shipmentForm->saveComboBoxInfo(comboBoxes);

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
void MainWindow::checkInvalidDataRecipient(std::vector<dataInfo> * invalidData)
{
    if(!invalidData->empty())
    {
      for (std::vector<dataInfo>::iterator it = invalidData->begin(); it!=invalidData->end(); ++it)
      {
          if(*it == name)
            ui->lineEdit_RecipientName->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

          if(*it == phoneNumber)
              ui->lineEdit_RecipientPhone->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

          if(*it == street)
              ui->lineEdit_RecipientStreet->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

          if(*it == postCode)
              ui->lineEdit_RecipientPostCode->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

          if(*it == city)
              ui->lineEdit_RecipientTown->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

          if(*it == houseNumber)
              ui->lineEdit_RecipientHouseNum->setStyleSheet("border: 2px solid rgb(209, 7, 10)");

      }
    }
}

void MainWindow::checkInvalidDataSender(std::vector<dataInfo> * invalidData)
{
    if(!invalidData->empty())
    {
     for (std::vector<dataInfo>::iterator it = invalidData->begin(); it!=invalidData->end(); ++it)
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
}

void MainWindow::checkInvalidData(std::pair<std::vector<dataInfo> *, std::vector<dataInfo> *> * invalidData)
{
    checkInvalidDataSender(invalidData->first);
    checkInvalidDataRecipient(invalidData->second);
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
    std::pair<std::vector<dataInfo>*, std::vector<dataInfo>*>* invalidData = shipmentForm->processFormData(sender, recipient, ui->comboBoxCountry->currentText().toStdString());

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

void MainWindow::on_pushButtonGoBack_Page2_clicked(){ ui->stackedWidget->setCurrentIndex(1);}


void MainWindow::on_pushButtonPrintLabel_clicked()
{

}

void MainWindow::on_pushButtonGoBack_LocalDatabase_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidgetLocalDatabase->setRowCount(0);
}

void MainWindow::on_pushButton_FinishAddingNewRecord_clicked()
{
    clearForm();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButtonGoBack_MainDatabase_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidgetMainDatabase->setRowCount(0);
}


void MainWindow::on_pushButton_SearchMainDatabase_clicked()
{
    std::list<Shipment*> tmp;

    switch(ui->comboBox_SearchFor_MainDatabase->currentIndex())
    {
        case 0:
        if(ui->comboBox_SearchForStatus_MainDatabase->currentIndex()!=0)
        {
        tmp = mainDatabase->searchByStatus(ui->comboBox_SearchForStatus_MainDatabase->currentText());
        mainDatabaseWidget->displaySelectedRows(ui->tableWidgetMainDatabase ,tmp);
        }
        else
            on_comboBox_SearchFor_MainDatabase_currentIndexChanged(0);
        break;

        case 1:
        tmp = mainDatabase->searchByID(ui->lineEdit_SearchMainDatabase->text());
        mainDatabaseWidget->displaySelectedRows(ui->tableWidgetMainDatabase ,tmp);
        break;

        case 2:
        tmp = mainDatabase->searchByPhoneNum(ui->lineEdit_SearchMainDatabase->text(), true);
        if(ui->comboBox_SearchForStatus_MainDatabase->currentIndex()!=0)
            tmp = mainDatabase->searchByStatus(tmp, ui->comboBox_SearchForStatus_MainDatabase->currentText());

        mainDatabaseWidget->displaySelectedRows(ui->tableWidgetMainDatabase ,tmp);
        break;

        case 3:
        tmp = mainDatabase->searchByPhoneNum(ui->lineEdit_SearchMainDatabase->text(), false);

        if(ui->comboBox_SearchForStatus_MainDatabase->currentIndex()!=0)
            tmp = mainDatabase->searchByStatus(tmp, ui->comboBox_SearchForStatus_MainDatabase->currentText());
        mainDatabaseWidget->displaySelectedRows(ui->tableWidgetMainDatabase ,tmp);
        break;

        default:
        break;
    }
}

void MainWindow::on_pushButton_SearchLocalDatabase_clicked()
{
    std::list<Shipment*> tmp;

    switch(ui->comboBox_SearchFor_LocalDatabase->currentIndex())
    {
        case 0:
        if(ui->comboBox_SearchForStatus_LocalDatabase->currentIndex()!=0)
        {
            tmp = localDatabase->searchByStatus(ui->comboBox_SearchForStatus_LocalDatabase->currentText());
            localDatabaseWidget->displaySelectedRows(ui->tableWidgetLocalDatabase ,tmp);
        }
        else
            on_comboBox_SearchFor_LocalDatabase_currentIndexChanged(0);
        break;

        case 1:
        tmp = localDatabase->searchByID(ui->lineEdit_SearchLocalDatabase->text());
        localDatabaseWidget->displaySelectedRows(ui->tableWidgetLocalDatabase ,tmp);
        break;

        case 2:
        tmp = localDatabase->searchByPhoneNum(ui->lineEdit_SearchLocalDatabase->text(), true);
        if(ui->comboBox_SearchForStatus_LocalDatabase->currentIndex()!=0)
            tmp = localDatabase->searchByStatus(tmp, ui->comboBox_SearchForStatus_LocalDatabase->currentText());

        localDatabaseWidget->displaySelectedRows(ui->tableWidgetLocalDatabase ,tmp);
        break;

        case 3:
        tmp = localDatabase->searchByPhoneNum(ui->lineEdit_SearchLocalDatabase->text(), false);
        if(ui->comboBox_SearchForStatus_LocalDatabase->currentIndex()!=0)
            tmp = localDatabase->searchByStatus(tmp, ui->comboBox_SearchForStatus_LocalDatabase->currentText());

        localDatabaseWidget->displaySelectedRows(ui->tableWidgetLocalDatabase ,tmp);
        break;

        default:
        break;
    }
}

void MainWindow::on_comboBox_SearchFor_MainDatabase_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->tableWidgetMainDatabase->setRowCount(0);
        mainDatabaseWidget->loadTable<Letter>(mainDatabase->getLetters(), ui->tableWidgetMainDatabase);
        mainDatabaseWidget->loadTable<Parcel>(mainDatabase->getParcels(), ui->tableWidgetMainDatabase);
    }
    if(index == 1)
        ui->comboBox_SearchForStatus_MainDatabase->setDisabled(true);
    else
        ui->comboBox_SearchForStatus_MainDatabase->setDisabled(false);
}

void MainWindow::on_comboBox_SearchFor_LocalDatabase_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->tableWidgetLocalDatabase->setRowCount(0);
        localDatabaseWidget->loadTable<Letter>(localDatabase->getLetters(), ui->tableWidgetLocalDatabase);
        localDatabaseWidget->loadTable<Parcel>(localDatabase->getParcels(), ui->tableWidgetLocalDatabase);
    }
    if(index == 1)
        ui->comboBox_SearchForStatus_LocalDatabase->setDisabled(true);
    else
        ui->comboBox_SearchForStatus_LocalDatabase->setDisabled(false);
}

void MainWindow::on_comboBox_SearchForStatus_LocalDatabase_currentIndexChanged(int index)
{
    if(index == 0)
        on_pushButton_SearchLocalDatabase_clicked();
}

void MainWindow::on_comboBox_SearchForStatus_MainDatabase_currentIndexChanged(int index)
{
    if(index == 0)
        on_pushButton_SearchMainDatabase_clicked();
}


void MainWindow::on_comboBoxShipmentType_currentIndexChanged(const QString &arg1)
{
    qDebug() << "type changed";

     ui->labelPrice->clear();
     auto comboBoxes = getFormDataFromComboBoxes();

     if(arg1!="")
     {
         auto shipmentType = shipmentForm->saveComboBoxInfo(comboBoxes);
         if(shipmentType)
         ui->labelPrice->setText( shipmentPricesManager->returnProperPrice(shipmentPricesManager->getShipmentPrice(shipmentType)) + " zł");
     }
}

void MainWindow::on_comboBoxRegistered_currentIndexChanged(int index)
{
    qDebug() << "registered changed";

   if(indexes[isRegistered] != index)
  {
       changePrice();
   }

    indexes[isRegistered] = index;
}


void MainWindow::on_comboBoxPriority_currentIndexChanged(int index)
{
    qDebug() << "priority changed";
    if(indexes[isPriority] != index)
    {
    changePrice();
    }

    indexes[isPriority] = index;
}

void MainWindow::on_comboBoxSize_currentIndexChanged(int index)
{
    qDebug() << "size changed";
    if(indexes[shipmentTypeInfo::size] != index)
    {
    changePrice();
    }

    indexes[shipmentTypeInfo::size] = index;
}

void MainWindow::on_comboBoxWeight_currentIndexChanged(int index)
{
    qDebug() << "weight changed";

    if(indexes[weight] != index)
    {
    changePrice();
    }

    indexes[weight] = index;
}

void MainWindow::on_comboBoxCountry_currentIndexChanged(int index)
{
    qDebug() << "country changed";
    if(indexes[shipmentTypeInfo::country] == index)
    {
    changePrice();
    }

    indexes[shipmentTypeInfo::country] = index;
}

void MainWindow::changePrice()
{
    ui->labelPrice->clear();

    auto comboBoxes = getFormDataFromComboBoxes();
    auto shipmentType = shipmentForm->saveComboBoxInfo(comboBoxes);

    if(shipmentType)
    ui->labelPrice->setText( shipmentPricesManager->returnProperPrice(shipmentPricesManager->getShipmentPrice(shipmentType)) + " zł");
}
