//
//  main.cpp
//  Project4
//
//  Created by Joseph Pecoraro on 4/1/13.
//  Copyright (c) 2013 Joseph Pecoraro. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstring>
#include "minHeap.cpp"
#include "City.h"
#include "Route.h"

using namespace std;

minHeap<City*> heap = *new minHeap<City*>(); //nodes heap for use in dijkstras

map<string, City*> cities; //used for storing all cities
vector<Route*> routes; //used for storing all routes
vector<Route*> solutionPath; //final path found by dijkstras - used for simplistic output printing

//files to be specified by input
string citiesFile = "/Users/Joseph/Dropbox/College/COP3530/Project4/Project4/cities.csv";
string routesFile = "/Users/Joseph/Dropbox/College/COP3530/Project4/Project4/routes.csv";
string outputFile = "output.html";

//origin and destination specified by input
string ori = "Paraguay";
string des = "Guatemala";
//origin and destination in proper node(City) class form
City *origin;
City *destination;
//string value for
string shortOrCheap = "cheapest";

//inputs all of the cities from file to a vector of Cities
void parseCities() {
    cities = *new map<string, City*>();
    
    string countryName = "";
    string cityName = "";
    float lat = 0;
    float lon = 0;
    
    City* city;
    
    char input[100];
    
    ifstream fileInput;
    fileInput.open(citiesFile.c_str());
    if (fileInput.is_open()) {
        while (fileInput.good()) {
            fileInput.getline(input, 100, ',');
            countryName = input;
            fileInput.getline(input, 100, ',');
            cityName = input;
            fileInput.getline(input, 100, ',');
            lat = atof(input);
            fileInput.getline(input, 100);
            lon = atof(input);
            if (countryName == "" && cityName == "" && lat == 0 && lon == 0)
                break;
            city = new City(countryName, cityName, lat, lon);
            //adds city to map with both cityName and countryName as values for retrieval of either.
            cities.insert(pair<string, City*>(cityName, city));
            cities.insert(pair<string, City*>(countryName, city));
        }
        fileInput.close();
    }
}

//adds all of the routes from file to vector of Routes
void parseRoutes() {
    routes = *new vector<Route*>();
    
    City *orig;
    City *dest;
    Route *r;
    string typeTransport;
    float length;
    float cst;
    string note;
    
    char input[1000];
    
    ifstream fileInput;
    fileInput.open(routesFile.c_str());
    if (fileInput.is_open()) {
        while (fileInput.good()) {
            fileInput.getline(input, 100, ',');
            orig = cities[input];
            fileInput.getline(input, 100, ',');
            dest = cities[input];
            fileInput.getline(input, 100, ',');
            typeTransport = input;
            fileInput.getline(input, 100, ',');
            length = atof(input);
            fileInput.getline(input, 100, ',');
            cst = atof(input);
            fileInput.getline(input, 1000);
            note = input;
            if (orig == NULL || dest == NULL) {
                break;
            }
            r = new Route(orig, dest, typeTransport, length, cst, note);
            routes.push_back(r);
            orig->addRoute(r);
        }
        fileInput.close();
    }
}

//writes the shortest path to file
void writeToFile() {
    ofstream output;
    output.open(outputFile.c_str());
    output << "<HTML><HEAD><TITLE>" << shortOrCheap << " path from " << ori << " to " << des << " </TITLE></HEAD><script type='text/javascript' src='http://maps.google.com/maps/api/js?sensor=false'></script><script>function initialize() { var myOptions = { zoom: 3, center: new google.maps.LatLng(0, 0), mapTypeId: google.maps.MapTypeId.ROADMAP};var map=new google.maps.Map(document.getElementById('map'), myOptions);" << endl;
    for (int i = 0; i < solutionPath.size(); i ++) {
        output << "var marker" << 2*i << " = new google.maps.Marker({ position: new google.maps.LatLng(" << solutionPath[i]->getOrigin()->getLat() << ", " << solutionPath[i]->getOrigin()->getLon() << "), map: map, title:\""<< solutionPath[i]->getOrigin()->getName() << "\"});" << endl;
        output << "var marker" << 2*i+1 << " = new google.maps.Marker({ position: new google.maps.LatLng(" << solutionPath[i]->getDestination()->getLat() << ", " << solutionPath[i]->getDestination()->getLon() << "), map: map, title:\""<< solutionPath[i]->getDestination()->getName() << "\"});" << endl;
        output << "var contentString" << i << " = \"" << solutionPath[i]->getOrigin()->getName() << " --> " << solutionPath[i]->getDestination()->getName() << " " << solutionPath[i]->getString() << "\"; var path" << i <<" = new google.maps.Polyline({ path: [new google.maps.LatLng(" << solutionPath[i]->getOrigin()->getLat() << ", " << solutionPath[i]->getOrigin()->getLon() << "), new google.maps.LatLng(" << solutionPath[i]->getDestination()->getLat() << ", " << solutionPath[i]->getDestination()->getLon() << ")], strokeColor: '#0000FF', strokeOpacity: 1.0, strokeWeight: 2}); path" << i <<".setMap(map); google.maps.event.addListener(path" << i << ", 'click', function(event) { alert(contentString" << i <<"); });" << endl;
    }
    
    output << "} google.maps.event.addDomListener(window, 'load', initialize); </script></HEAD><BODY><div id='map' style='width:100%;height:100%;'></div></BODY></HTML>" << endl;
    
    output.close();
}

//puts the solution array in proper order - makes for more simplistic outputting
void reversePathArray() {
    int first = 0;
    int last = solutionPath.size() - 1;
    Route* temp;
    while(first<last) {
        temp = solutionPath[first];
        solutionPath[first] = solutionPath[last];
        solutionPath[last] = temp;
        first++;
        last--;
    }
}

//dijkstras algorithm using Time as parameter for value
void findShortestPath() {
    origin->value = 0; //origin value is equal to 0
    heap.push(origin); //add origin to heap
    
    while (heap.size() > 0) { //while heap isnt empty
        City* smallest = heap.top(); //grab the smallest item
        heap.pop();
        smallest->visited = true;
        
        vector<Route*> adjacentPaths = smallest->getRoutes(); //gets all edges from smallest item
        for (int i =0; i < adjacentPaths.size(); i++) {
            float time;
            City* node = adjacentPaths[i]->getDestination(); //current node that is being updated
            if (adjacentPaths[i]->getTypeOfTransport().compare("plane") == 0) { //get value and add plane multiplier
                time = smallest->value + 100*adjacentPaths[i]->getTime();
            }
            else {
                time = smallest->value + adjacentPaths[i]->getTime();
            }
            if (time < node->value) { //if new value is smallest, update value and path to node
                node->value = time;
                node->edgeReachedBy = adjacentPaths[i];
            }
            if (!node->visited) { //if the node has not yet been visited, add it to the heap
                heap.push(node);
                node->visited = true;
            }
        }
    }
}

//dijkstras algorithm using cost as parameter for value
void findCheapestPath() {
    origin->value = 0;
    heap.push(origin);
    
    while (heap.size() > 0) {
        City* smallest = heap.top();
        heap.pop();
        smallest->visited = true;
        
        vector<Route*> adjacentPaths = smallest->getRoutes();
        for (int i =0; i < adjacentPaths.size(); i++) {
            float cost;
            City* node = adjacentPaths[i]->getDestination();
            if (adjacentPaths[i]->getTypeOfTransport().compare("plane") == 0) {
                cost = smallest->value + 100*adjacentPaths[i]->getCost();
            }
            else {
                cost = smallest->value + adjacentPaths[i]->getCost();
            }
            if (cost < node->value) {
                node->value = cost;
                node->edgeReachedBy = adjacentPaths[i];
            }
            if (!node->visited) {
                heap.push(node);
                node->visited = true;
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    //collect input
    citiesFile = argv[1];
    routesFile = argv[2];
    outputFile = argv[3];
    ori = argv[4];
    des = argv[5];
    shortOrCheap = argv[6];
    
    //parse files
    parseCities();
    parseRoutes();
    
    //find cities for coutnry names
    origin = cities[ori];
    destination = cities[des];
    
    //pick fastest or cheapest path based on input and calculate shortest path
    if(shortOrCheap == "fastest" || shortOrCheap == "shortest") {
        findShortestPath();
    }
    else if (shortOrCheap == "cheapest") {
        findCheapestPath();
    }
    else {
        cerr << "Error: Invalid Input" << endl;
    }
    
    //put solution into an array for ease of use
    City* current = destination;
    while (current->edgeReachedBy!= NULL) {
        solutionPath.push_back(current->edgeReachedBy);
        current = current->edgeReachedBy->getOrigin();
    }
    reversePathArray();
    
    //write output file
    writeToFile();
    
    return 0;
}
