#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QComboBox>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include "datainfo.h"
#include "shipmenttypeinfo.h"
#include <QTableWidget>
#include "list.h"
#include "letter.h"
#include "parcel.h"
#include "database.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace DataInfo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
  //  void comboBoxShipmentTypeHandling(std::vector<std::string>*);
    ~MainWindow();


private slots:

    void lackOfDataDialog_pop();
    void invalidDataDialog_pop();
    void closeEvent (QCloseEvent*);
    void on_pushButtonMainDatabase_clicked();
    void on_pushButtonLocalDatabase_clicked();
    void on_pushButtonRegisterParcel_clicked();
    //void on_pushButtonConfirm_Page1_clicked();
    void on_pushButtonCancel_Page1_clicked();
    void on_pushButtonGoBack_Page2_clicked();

    std::map<shipmentTypeInfo,QComboBox *> getFormDataFromComboBoxes();

    void setDefaultLineEdits();
    void clearForm();
    void getFormData(std::map<dataInfo, std::string> &, std::map<dataInfo, std::string>& );
    void checkInvalidData(std::pair<std::vector<dataInfo>*, std::vector<dataInfo>*>*);
    void checkInvalidDataRecipient(std::vector<dataInfo> * );
    void checkInvalidDataSender(std::vector<dataInfo> * );

    void on_pushButtonConfirm_Page2_clicked();
    void on_pushButtonPrintLabel_clicked();

    void on_pushButtonGoBack_LocalDatabase_clicked();
    void on_pushButtonGoBack_MainDatabase_clicked();

    void on_pushButtonConfirmAndGo_clicked();
    void on_comboBoxShipmentType_currentIndexChanged(const QString &arg1);
    void on_pushButton_FinishAddingNewRecord_clicked();




    void on_pushButton_SearchMainDatabase_clicked();

    void on_pushButton_SearchLocalDatabase_clicked();

    void on_comboBox_SearchFor_MainDatabase_currentIndexChanged(int index);

    void on_comboBox_SearchFor_LocalDatabase_currentIndexChanged(int index);

    void on_comboBox_SearchForStatus_LocalDatabase_currentIndexChanged(int index);

    void on_comboBox_SearchForStatus_MainDatabase_currentIndexChanged(int index);

    void on_comboBoxRegistered_currentIndexChanged(int index);

    void on_comboBoxPriority_currentIndexChanged(int index);

    void on_comboBoxSize_currentIndexChanged(int index);

    void on_comboBoxWeight_currentIndexChanged(int index);

    void on_comboBoxCountry_currentIndexChanged(int index);

    void changePrice();

public:
    Ui::MainWindow *ui;



    
private:
    class ShipmentFormWidget* shipmentForm;
    class LocalDatabaseWidget* localDatabaseWidget;
    class MainDatabaseWidget* mainDatabaseWidget; // ??
    class ShipmentPrices* shipmentPricesManager;
    Database* localDatabase;
    Database* mainDatabase;
    std::map<shipmentTypeInfo, int> indexes;

};





#endif // MAINWINDOW_H
