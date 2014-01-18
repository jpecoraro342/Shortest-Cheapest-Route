//
//  City.cpp
//  Project4
//
//  Created by Joseph Pecoraro on 4/1/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include "City.h"

City::City(std::string ctName, std::string ciName, float lat, float lon) {
    countryName = ctName;
    cityName = ciName;
    latitude = lat;
    longitude = lon;
    value = 3276700;
    routes = new std::vector<Route*>();
    visited = false;
}

void City::print() {
    std::cout << countryName << ", " << cityName << ", " << latitude << ", " << longitude << std::endl;
}

int City::compare(City* city) {
    return value - city->value;
}

int City::compare2(City* city) {
    return countryName.compare(city->countryName);
}

std::string City::getName() {
    return cityName + ", " + countryName;
}

void City::addRoute(Route *r) {
    routes->push_back(r);
}
