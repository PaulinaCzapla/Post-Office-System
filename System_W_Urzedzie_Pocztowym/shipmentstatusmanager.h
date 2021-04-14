#ifndef SHIPMENTSTATUSMANAGER_H
#define SHIPMENTSTATUSMANAGER_H

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <shipmentstatus.h>
#include <map>
#define FILENAME_SHIPMENT_STATUSES "shipmentstatuses.txt"

class ShipmentStatusManager
{
    std::map <int, ShipmentStatus*> statuses;

public:
    ShipmentStatusManager();
    std::string changeStatus();
    ShipmentStatus* findStatus(int);
    std::vector<std::string> returnAvailableStatuses (ShipmentStatus&);
    ~ShipmentStatusManager();
};

#endif // PARCELSTATUS_H
