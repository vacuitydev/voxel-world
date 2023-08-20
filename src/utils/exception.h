#pragma once
#include <string>
using namespace std;
struct Exception{
    string message;
    Exception(string message){
        this->message = message;
    }
};