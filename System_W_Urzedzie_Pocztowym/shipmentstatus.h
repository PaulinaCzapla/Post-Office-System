#ifndef SHIPMENTSTATUS_H
#define SHIPMENTSTATUS_H
#include <vector>
#include <string>
#include <algorithm>

class ShipmentStatus
{
    std::string status;
    int id;
    std::vector<int> availableStatuses;
public:
    ShipmentStatus(std::string&,int id, std::vector<int>&);
    inline std::string getStatus() {return status;};
    inline int getId(){return id;};
    inline std::vector<int>& getAvailableStatuses() {return availableStatuses;};
    ~ShipmentStatus() {};
};

#endif // SHIPMENTSTATUS_H
