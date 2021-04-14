#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <regex>
#include <datainfo.h>


#define FILENAME_VALIDATOR "validator.txt"
#define FILENAME_FOREIGN_POSTCODE "validatorpostcode.txt"

using namespace DataInfo;

class Validator
{
    std::map<dataInfo,std::string> patterns;
    std::map<std::string, std::string> postCodePatterns;
public:
    Validator();
    bool validate(const std::string,const dataInfo& dataType);
    bool validate(std::string, std::string);
    void readFileValidator();
    void readFileValidatorPostCode();
};

#endif // VALIDATOR_H
