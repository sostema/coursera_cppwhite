#include "responses.h"

std::ostream &operator<<(std::ostream &os, const BusesForStopResponse &r) {
  if(r.stop.empty()){
    os << "No stop";
  }
  else {
    for (const auto& bus: r.buses){
      os << bus << " ";
    }
  }
  return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
  if(r.bus.empty()){
    os << "No bus";
  }
  else {
    for (const auto& stop: r.stop_order){
      os << "Stop " << stop << ": ";
      for (const auto& other_stop: r.stops.at(stop)){
        os << other_stop << " ";
      }
      os << std::endl;
    }
  }
  return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
  if (r.buses.empty()) {
    os << "No buses";
  } else {
    for (const auto& bus_item : r.buses){
      os << "Bus " << bus_item.first << ": ";
      for (const std::string& stop : bus_item.second) {
        os << stop << " ";
      }
      os << std::endl;
    }
  }
  return os;
}
