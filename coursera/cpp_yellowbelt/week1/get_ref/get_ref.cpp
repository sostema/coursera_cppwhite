#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k);

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k) {
  if (m.count(k) == 0){
    throw std::runtime_error("no such key in dictionary");
  }
  else{
    return m[k];
  }
}


int main() {
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue
}