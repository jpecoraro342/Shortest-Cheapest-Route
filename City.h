//
//  City.h
//  Project4
//
//  Created by Joseph Pecoraro on 4/1/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#ifndef __Project4__City__
#define __Project4__City__

#include <iostream>
#include <vector>
#include "Route.h"

class Route;

class City {
public:
    City() { }
    City(std::string ctName, std::string ciName, float lat, float lon);
    int compare(City *city); //used for finding min values
    int compare2(City *city); //used to compare two cities by name - unused
    std::string getName(); //returns a string value of the country used for outputting
    void addRoute(Route *r);
    void print(); //used for testing purposes
    std::vector<Route*> getRoutes() { return *routes; }
    std::string getCityName() { return cityName; }
    std::string getCountryName() { return countryName; }
    float getLat() { return latitude; }
    float getLon() { return longitude; }
    Route* edgeReachedBy;
    float value; //value used to determin time or cost from origin - used in dijkstras
    bool visited; //used to keep nodes from being added to heap multiple times
    
private:
    std::string countryName;
    std::string cityName;
    std::vector<Route*> *routes; //list of routes that have this city as origin
    float latitude;
    float longitude;
};


#endif /* defined(__Project4__City__) */
