//
//  Route.cpp
//  Project4
//
//  Created by Joseph Pecoraro on 4/1/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include "Route.h"
#include <sstream>

Route::Route(City *orig, City *dest, std::string typeTransport, float length, float cst, std::string note) {
    origin = orig;
    destination = dest;
    typeOfTransport = typeTransport;
    time = length;
    cost = cst;
    notes = note;
}

void Route::print() {
    std::cout << origin->getName() << ", " << destination->getName() << ", " << typeOfTransport << ", " << time << ", " << cost << ", " << notes << std::endl;
}

std::string Route::getString() {
    std::stringstream ss;
    std::stringstream ss2;
    ss << int(time+.5);
    ss2 << int(cost+.5);
    return "(" + typeOfTransport + " - " + ss.str() + " hours - $" + ss2.str() + ")";
}