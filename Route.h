//
//  Route.h
//  Project4
//
//  Created by Joseph Pecoraro on 4/1/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#ifndef __Project4__Route__
#define __Project4__Route__

#include <iostream>
#include "City.h"

class City;

class Route {
public:
    Route() { }
    Route(City *orig, City *dest, std::string typeTransport, float length, float cst, std::string note);
    float getTime() { return time; }
    float getCost() { return cost; }
    City* getOrigin() { return origin; }
    City* getDestination() { return destination; }
    std::string getTypeOfTransport() { return typeOfTransport; }
    std::string getString();
    void print();
private:
    City *origin;
    City *destination;
    std::string typeOfTransport;
    float time;
    float cost;
    std::string notes;
};

#endif /* defined(__Project4__Route__) */