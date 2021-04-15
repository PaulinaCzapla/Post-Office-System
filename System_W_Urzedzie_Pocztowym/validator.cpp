#include "validator.h"

Validator::Validator()
{
    readFileValidator();
    readFileValidatorPostCode();
}

//wykorzystanie regexów do walidacji

bool Validator::validate(const std::string _data, const dataInfo& dataType)
{
    if(!patterns.empty())
    {
    auto pattern = patterns.find(dataType);
    std::regex reg(pattern->second);
    std::smatch result;

    return std::regex_match(_data, result, reg);
    } else
        return true;
}

bool Validator::validate(std::string _data, std::string country)
{
    if(!postCodePatterns.empty())
    {
    auto pattern = postCodePatterns.find(country);
    std::regex reg(pattern->second);
    std::smatch result;

    return std::regex_match(_data, result, reg);

    } else 
        return true;
}

//wczytywanie danych do mapy z patternami
void Validator::readFileValidator()
{
    std::fstream file;
    file.open(FILENAME_VALIDATOR, std::ios::in);

    dataInfo dataType;
    std::string s = "", pattern="";

    if (file.is_open() && file.good())
    {
        while (!file.eof())
        {
             file>>s;
              getline(file, pattern);
                pattern.erase(0,1);
             if(s=="str")
                 dataType = street;
                 else if(s=="name")
                 dataType = name;
                 else if(s=="housenum")
                 dataType=houseNumber;
                 else if(s=="phone")
                 dataType=phoneNumber;
                 else if(s=="city")
                 dataType=city;

            patterns.insert(std::pair<dataInfo, std::string>(dataType,pattern));
            pattern = "";
            s = "";
        }
    }
    file.close();
}

//wczytywanie danych do mapy z patternami kodów pocztowych dla różnych państw
void Validator::readFileValidatorPostCode()
{
       std::fstream file;
       file.open(FILENAME_FOREIGN_POSTCODE, std::ios::in);

       std::string country = "", pattern="";

        if (file.is_open() && file.good())
        {
             while (!file.eof())
            {
                file>>country;
                getline(file, pattern);
                pattern.erase(0,1);
                postCodePatterns.insert(std::pair<std::string, std::string>(country,pattern));
                pattern = "";
                country = "";
            }
         }
       file.close();
}
