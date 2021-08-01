#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
  buses_to_stops[bus] = stops;
  for (const auto& stop : stops){
    stops_to_buses[stop].push_back(bus);
  }
}

[[nodiscard]] BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
  BusesForStopResponse response;
  if (stops_to_buses.count(stop) == 0) {
    response.stop = "";
  } else {
    response.stop = stop;
    response.buses = stops_to_buses.at(stop);
  }
  return response;
}

[[nodiscard]] StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
  StopsForBusResponse response;
  if (buses_to_stops.count(bus) == 0) {
    response.bus = "";
  } else {
    response.bus = bus;
    for (const std::string& stop : buses_to_stops.at(bus)) {
      response.stop_order.push_back(stop);
      if (stops_to_buses.at(stop).size() == 1) {
        response.stops[stop].push_back("no interchange");
      } else {
        for (const std::string& other_bus : stops_to_buses.at(stop)) {
          if (bus != other_bus) {
            response.stops[stop].push_back(other_bus);
          }
        }
      }
    }
  }
  return response;
}

[[nodiscard]] AllBusesResponse BusManager::GetAllBuses() const {
  AllBusesResponse response;
  response.buses = buses_to_stops;
  return response;
}
