#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {q
  string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;

    int stop_count;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (string& stop : q.stops) {
      is >> stop;
    }
  } else if (operation_code == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (operation_code == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (operation_code == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  string stop;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
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

struct StopsForBusResponse {
  string bus;
  vector<string> stop_order;
  map<string, vector<string>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if(r.bus.empty()){
    os << "No bus";
  }
  else {
    for (const auto& stop: r.stop_order){
      os << "Stop " << stop << ": ";
      for (const auto& other_stop: r.stops.at(stop)){
        os << other_stop << " ";
      }
      os << endl;
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses.empty()) {
    os << "No buses";
  } else {
    for (const auto& bus_item : r.buses){
      cout << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        os << stop << " ";
      }
      os << endl;
    }
  }
  return os;
}

class BusManager {
 public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const auto& stop : stops){
      stops_to_buses[stop].push_back(bus);
    }
  }

  [[nodiscard]] BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse response;
    if (stops_to_buses.count(stop) == 0) {
      response.stop = "";
    } else {
      response.stop = stop;
      response.buses = stops_to_buses.at(stop);
    }
    return response;
  }

  [[nodiscard]] StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse response;
    if (buses_to_stops.count(bus) == 0) {
      response.bus = "";
    } else {
      response.bus = bus;
      for (const string& stop : buses_to_stops.at(bus)) {
        response.stop_order.push_back(stop);
        if (stops_to_buses.at(stop).size() == 1) {
          response.stops[stop].push_back("no interchange");
        } else {
          for (const string& other_bus : stops_to_buses.at(stop)) {
            if (bus != other_bus) {
              response.stops[stop].push_back(other_bus);
            }
          }
        }
      }
    }
    return response;
  }

  [[nodiscard]] AllBusesResponse GetAllBuses() const {
    AllBusesResponse response;
    response.buses = buses_to_stops;
    return response;
  }
 private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
    }
  }

  return 0;
}