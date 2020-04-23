#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Commands.h"
#include <vector>
#include <string>

class CMDMapping
{
public:
    CMDMapping() {}


    std::map <std::string, int> GetMapping() const;

    void SetMapParam(std::map <std::string, int> inpmap );

    bool CheckExistingElement(const std::string& key) const;
private:
    std::map <std::string, int> mapping;
};

