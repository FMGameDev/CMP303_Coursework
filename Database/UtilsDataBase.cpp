#include "UtilsDataBase.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>


UtilsDataBase::UtilsDataBase()
{
}

UtilsDataBase::~UtilsDataBase()
{
}

std::string UtilsDataBase::getTextFromFile(const std::string& filePath)
{
    // object where save the buffer
    auto ss = std::ostringstream{};

    // create file, it is used ifstream instead of fstream because
    // it is only going to be used for reading (in) not for reading and writing
    std::ifstream inputFile;
    inputFile.open(filePath);

    // try to open the file,
    // if it doesn't open then do not to anything more
    if (!inputFile.is_open())
    {
        std::cerr << "Could not open the file - '" << filePath << "'" << std::endl;
    }

    // save the buffer into the string stream
    ss << inputFile.rdbuf();

    // close the file
    inputFile.close();

    return ss.str();
}