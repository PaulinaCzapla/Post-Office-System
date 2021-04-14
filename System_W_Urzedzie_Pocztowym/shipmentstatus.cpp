#include "shipmentstatus.h"

ShipmentStatus::ShipmentStatus(std::string &_status, int _id, std::vector<int> & _availableStatuses)
{
    status = _status;
    copy(_availableStatuses.begin(), _availableStatuses.end(), back_inserter(availableStatuses));
    id = _id;
}

