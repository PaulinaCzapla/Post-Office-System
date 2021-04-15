#ifndef SORTER_H
#define SORTER_H
#include <vector>
#include "list.h"
#include <algorithm>
class Sorter
{
public:
    Sorter();

    template <typename T>
    inline void sortAlphabetically(std::vector<T>&);

};

template<typename T>
void Sorter::sortAlphabetically(std::vector<T> & data)
{
    std::sort(data.begin(), data.end());
}

#endif // SORTER_H
