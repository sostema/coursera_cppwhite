#include <iostream>
#include <vector>

using namespace std;

int main() {
  int64_t n;
  cin >> n;
  int64_t sum = 0;
  vector<int64_t> temperatures;
  for (ptrdiff_t i = 0; i < n; ++i){
    int64_t buff;
    cin >> buff;
    sum += buff;
    temperatures.emplace_back(buff);
  }
  int64_t avg = sum / n;
  vector<int64_t> higher_temperatures;
  for (ptrdiff_t k = 0; k < n; ++k){
    if (temperatures[k] > avg){
      higher_temperatures.emplace_back(k);
    }
  }
  cout << higher_temperatures.size() <<endl;
  for (auto k : higher_temperatures){
    cout << k << " ";
  }
  return 0;
}