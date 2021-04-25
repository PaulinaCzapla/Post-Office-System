#ifndef SHIPMENTSTATUSMANAGER_H
#define SHIPMENTSTATUSMANAGER_H

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <shipmentstatus.h>
#include <map>
#include<QStringList>
#define FILENAME_SHIPMENT_STATUSES "shipmentstatuses.txt"

class ShipmentStatusManager
{
    std::map <int, ShipmentStatus*> statuses;
    std::map <std::string, int> statusesIDs;

public:
    ShipmentStatusManager();
    std::string changeStatus();
    int getStatusID(std::string);
    ShipmentStatus* findStatus(int);
    QStringList returnAvailableStatuses (std::string);
    ~ShipmentStatusManager();
};

#endif // PARCELSTATUS_H
