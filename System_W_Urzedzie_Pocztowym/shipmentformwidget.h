#ifndef SHIPMENTTYPEFORMWIDGET_H
#define SHIPMENTTYPEFORMWIDGET_H

#include "mainmenuwidget.h"
#include "shipmentprices.h"
#include "validator.h"
#include <map>
#include "parcel.h"
#include "letter.h"
#include <vector>
#include <iterator>
#include "sorter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ShipmentFormWidget; }
QT_END_NAMESPACE
using namespace DataInfo;

class ShipmentFormWidget : public Sorter, public Validator
{
    Shipment* currentShipment;

public:

    ShipmentFormWidget() : currentShipment(nullptr){};
    ShipmentType* saveComboBoxInfo(std::map<shipmentTypeInfo,QComboBox *> &);
    void loadDataToComboBoxes(std::map<shipmentTypeInfo,QComboBox *>&);
    void loadCountriesToComboBox(QComboBox*&);
    void clearComboBoxes(std::map<shipmentTypeInfo,QComboBox *>&);
    std::pair<std::vector<dataInfo>*, std::vector<dataInfo>*>* processFormData(std::map<dataInfo, std::string> &, std::map<dataInfo, std::string> &);
    std::vector<dataInfo>* validatePersonalData(std::map<dataInfo, std::string> &);
    void insertRecord(std::map<dataInfo, std::string>&, std::map<dataInfo, std::string>&, Database*, Database*);

    //void sortAlphabetically(std::list<std::string>&);
    ~ShipmentFormWidget();
    void createShipmentType(bool);
};

#endif// SHIPMENTTYPEFORMWIDGET_H
