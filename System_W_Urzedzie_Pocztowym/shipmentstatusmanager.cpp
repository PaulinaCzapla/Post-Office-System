#include "shipmentstatusmanager.h"

ShipmentStatusManager::ShipmentStatusManager() // działa
{
        std::fstream file;
        file.open(FILENAME_SHIPMENT_STATUSES, std::ios::in);
        std::string statusName="";
        int tmpID=0;
        std::string s = "";
        
        std::vector<int> tmpVec;
        if (file.is_open() && file.good())
        {
            while (!file.eof())
            {
                getline(file, statusName);
                 file>>tmpID;

                 getline(file, s);

                 for (int i = 0; i < s.length(); i += 2)
                     tmpVec.push_back(s[i+1] - 48);

                ShipmentStatus* status = new ShipmentStatus(statusName,tmpID, tmpVec);
                
                statuses.insert(std::pair<int, ShipmentStatus*>(tmpID, status));
                tmpVec.erase(tmpVec.begin(), tmpVec.end());

                statusesIDs.insert(std::pair<std::string, int>(statusName,tmpID));

                tmpID=0;
                statusName = "";
                s = "";
            }
        }
    file.close();
}

int ShipmentStatusManager::getStatusID(std::string status)
{
    return statusesIDs[status];
}

ShipmentStatus* ShipmentStatusManager::findStatus(int id)
{
    auto found = statuses.find(id);
    return found->second;
}

QStringList ShipmentStatusManager::returnAvailableStatuses(std::string _status)
{
    auto vec = statuses[getStatusID(_status)]->getAvailableStatuses();
    std::vector<int>::iterator itVec = vec.begin();
    QStringList result;
    do
    {
        result.push_back(QString::fromStdString(findStatus(*itVec)->getStatus()));
        itVec++;

    }  while(itVec!=vec.end());

    return result;
}

ShipmentStatusManager::~ShipmentStatusManager()
{
    auto it = statuses.begin();
    while(it!=statuses.end())
    {
        delete it->second;
        it->second = nullptr;
    }
    statuses.clear();
}
