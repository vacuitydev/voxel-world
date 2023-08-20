#pragma once
#include <iostream>
#include <variant>
#include <fstream>
#include "../utils/exception.h"
#include <sstream>
#include <format>
using namespace std;
std::variant<Exception,std::string> read_string_from_file(const char* path){
    string output;
    ifstream file_stream;
    file_stream.exceptions(ifstream::failbit| ifstream::badbit);
    try{
        file_stream.open(path);
        stringstream input_stream;
        input_stream << file_stream.rdbuf();
        file_stream.close();
        output =input_stream.str();
    }catch(ifstream::failure e){
        return Exception(std::format("File {0} could not be read", path));
    }
    return output;
}