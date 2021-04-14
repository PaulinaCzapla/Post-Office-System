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


QT_BEGIN_NAMESPACE
namespace Ui { class ShipmentFormWidget; }
QT_END_NAMESPACE
using namespace DataInfo;

class ShipmentFormWidget : public MainWidget, public Validator
{
    Shipment* currentShipment;

public:

    ShipmentFormWidget() : MainWidget(), currentShipment(nullptr){};
    ShipmentType* saveComboBoxInfo(std::map<shipmentTypeInfo,QComboBox *> &);
    void loadDataToComboBoxes(std::map<shipmentTypeInfo,QComboBox *>&);
    void clearComboBoxes(std::map<shipmentTypeInfo,QComboBox *>&);
    std::pair<std::vector<dataInfo>*, std::vector<dataInfo>*>* processFormData(std::map<dataInfo, std::string> &, std::map<dataInfo, std::string> &);
    std::vector<dataInfo>* validatePersonalData(std::map<dataInfo, std::string> &);
    void insertRecord(std::map<dataInfo, std::string>&, std::map<dataInfo, std::string>&, Database*, Database*);

    ~ShipmentFormWidget();
};

#endif// SHIPMENTTYPEFORMWIDGET_H
