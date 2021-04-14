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
                
                tmpID=0;
                statusName = "";
                s = "";
            }
        }
    file.close();
}

std::string ShipmentStatusManager::changeStatus()
{
return "";
}

ShipmentStatus* ShipmentStatusManager::findStatus(int id)
{
    auto found = statuses.find(id);
    return found->second;
}

std::vector<std::string> ShipmentStatusManager::returnAvailableStatuses(ShipmentStatus& _status)
{
    auto vec = _status.getAvailableStatuses();
    std::vector<int>::iterator itVec = vec.begin();
    std::vector<std::string> result;
    do
    {
        result.push_back(findStatus(*itVec)->getStatus());
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
