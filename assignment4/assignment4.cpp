#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <limits>
#include "AdjacencyListDirectedGraph.h"
#include "FlightMap.h"


double FlightMap::calcRouteDistance(const list<string> route) {
    double alldistance = 0;
    int i=0;
    list<string>::const_iterator itor;
    list<string>::const_iterator preitor;
    itor=route.begin();

    while(itor != route.end()||i<10000){
        i++;
        itor++;

        if(itor != route.begin()){
            if(isConnectionExist(*preitor, *itor)==false)
            throw runtime_error("error");

            alldistance += *(airport_db[*preitor].outgoingEdge(airport_db[*itor]));
      }
        if(isAirportExist(*itor)==false)
            throw runtime_error("error");
            preitor = itor;
    }

    return alldistance;
}


list<string> FlightMap::findShortestRoute(const string &airport1, const string &airport2) {
    if(isAirportExist(airport1)==false) throw runtime_error("error");
    if(isAirportExist(airport2)==false) throw runtime_error("erroe");


}


void FlightMap::printAllShortestRoutes(const string &airport) {
    if(isAirportExist(airport)==false) throw runtime_error("error");
  }
