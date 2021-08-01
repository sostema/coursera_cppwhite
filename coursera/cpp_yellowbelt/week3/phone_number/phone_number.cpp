#include "phone_number.h"
#include <stdexcept>
#include <sstream>

PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream is(international_number);

  char sign = is.get();
  getline(is, country_code_, '-');
  getline(is, city_code_, '-');
  getline(is, local_number_);

  if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
  }
}

string PhoneNumber::GetCountryCode() const {
  return this->country_code_;
}
string PhoneNumber::GetCityCode() const {
  return this->city_code_;
}
string PhoneNumber::GetLocalNumber() const {
  return this->local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
  return "+" + this->country_code_ + "-" + this->city_code_ + "-" + this->local_number_;
}
