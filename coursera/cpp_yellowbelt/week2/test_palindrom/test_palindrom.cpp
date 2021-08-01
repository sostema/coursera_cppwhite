#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
 public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

 private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
}

void TestExceptions() {
  AssertEqual(IsPalindrom(""), true);
  AssertEqual(IsPalindrom("a"), true);
  AssertEqual(IsPalindrom("!"), true);
  AssertEqual(IsPalindrom("A"), true);
  AssertEqual(IsPalindrom(" "), true);
  AssertEqual(IsPalindrom("aa"), true);
}

void TestSpecial() {
  AssertEqual(IsPalindrom("abaaba"), true);
  AssertEqual(IsPalindrom("Abaaba"), false);
  AssertEqual(IsPalindrom("  A bCa +- +aB!a!Ba+ -+ aCb A  "), true);
  AssertEqual(IsPalindrom("  A bCa +-  +aB!a!Ba+ -+ aCb A  "), false);
  AssertEqual(IsPalindrom("777777"), true);
  AssertEqual(IsPalindrom("abacaba"), true);
  AssertEqual(IsPalindrom("abacDdaba"), false);
  AssertEqual(IsPalindrom("aba ba"), false);
  AssertEqual(IsPalindrom("abb a"), false);
  AssertEqual(IsPalindrom("ab ba"), true);
  AssertEqual(IsPalindrom("ab!ba"), true);
  AssertEqual(IsPalindrom("cb!ba"), false);
  AssertEqual(IsPalindrom(" madam "), true);
  AssertEqual(IsPalindrom(" madam  "), false);
  AssertEqual(IsPalindrom(" ma am  "), false);
  AssertEqual(IsPalindrom("   madam  "), false);
  AssertEqual(IsPalindrom("!madam!"), true);
}

int main() {
  TestRunner runner;
  runner.RunTest(TestExceptions, "TestExceptions");
  runner.RunTest(TestSpecial, "TestSpecial");
  return 0;
}