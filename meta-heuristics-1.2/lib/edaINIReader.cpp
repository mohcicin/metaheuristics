// Read an INI file into easy-to-access name/value pairs.

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include "ini.h"
#include "edaINIReader.h"

using std::string;

edaINIReader::edaINIReader() 
: _error(-1) {}

edaINIReader::edaINIReader(string filename) 
{
    _error = ini_parse(filename.c_str(), ValueHandler, this);
    if (_error < 0) {
        std::cerr << "Can't load '" << filename << "'\n";
        exit(1);
    } 
}

string edaINIReader::GetString(string section, string name, string default_value)
{
    checkError();
    string key = MakeKey(section, name);
    return _values.count(key) ? _values[key] : default_value;
}

long edaINIReader::GetInteger(string section, string name, long default_value)
{
    string valstr = GetString(section, name, "");
    const char* value = valstr.c_str();
    char* end;
    long n = strtol(value, &end, 0);
    return end > value ? n : default_value;
}

long* edaINIReader::GetInteger(std::string section, std::string name, double default_value, unsigned int number) 
{
    long* array = new long [number];
    string valstr = GetString(section, name, "");
    if(valstr.compare(""))
    {        
        valstr.erase(valstr.begin());
        valstr.erase(valstr.end() - 1);  
        const char* value; char* end; 

        bool parser = valstr.compare(0, 1, "[") && valstr.compare(0, 1, "(") && valstr.compare(0, 1, "{");
        if(!parser) {
            valstr.erase(valstr.begin());
            valstr.erase(valstr.end() - 1);  
        }

        value = valstr.c_str();
        array[0] = strtol(value, &end, 0);
        for(unsigned int i = 1; i < number; i++) {       
            array[i] = strtol(end, &end, 0);
        }
    }
    else
    {
        for(unsigned int i = 0; i < number; i++) 
            array[i] = (long) default_value;    
    }  
    return array;
}

double edaINIReader::GetDouble(std::string section, std::string name, double default_value)
{
    string valstr = GetString(section, name, "");
    const char* value = valstr.c_str();
    char* end;
    double real = strtod(value, &end);
    return end > value ? real : default_value;
}

double* edaINIReader::GetDouble(std::string section, std::string name, double default_value, unsigned int number) 
{
    double* array = new double [number];
    string valstr = GetString(section, name, "");
    const char* value; char* end; 
    
    bool parser = valstr.compare(0, 1, "[") && valstr.compare(0, 1, "(") && valstr.compare(0, 1, "{");
    if(!parser) {
        valstr.erase(valstr.begin());
        valstr.erase(valstr.end() - 1);  
    }  
    
    value = valstr.c_str();
    array[0] = strtod(value, &end);

    for(unsigned int i = 1; i < number; i++) {       
        array[i] = strtod(end, &end);
    }
    
    if(value >= end) {
        for(unsigned int i = 0; i < number; i++) 
            array[i] = default_value;    
    }    
   
    return array;
}

bool edaINIReader::GetBoolean(string section, string name, bool default_value)
{
    string valstr = GetString(section, name, "");
    std::transform(valstr.begin(), valstr.end(), valstr.begin(), ::tolower);
    if (valstr == "true" || valstr == "yes" || valstr == "on" || valstr == "1")
        return true;
    else if (valstr == "false" || valstr == "no" || valstr == "off" || valstr == "0")
        return false;
    else
        return default_value;
}

string edaINIReader::MakeKey(string section, string name)
{
    string key = section + "." + name;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    return key;
}

void edaINIReader::checkError() 
{
    if (_error < 0) exit(1);        
}

int edaINIReader::ValueHandler(void* user, const char* section, const char* name,
                            const char* value)
{
    edaINIReader* reader = (edaINIReader*)user;
    string key = MakeKey(section, name);
    if (reader->_values[key].size() > 0)
        reader->_values[key] += "\n";
    reader->_values[key] += value;
    return 1;
}


edaINIReader::~edaINIReader() {}
