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

    int getStatusID(std::string);
    ShipmentStatus* findStatus(int);

public:
    ShipmentStatusManager();
    QStringList returnAvailableStatuses (std::string);
    ~ShipmentStatusManager();
};

#endif // PARCELSTATUS_H
