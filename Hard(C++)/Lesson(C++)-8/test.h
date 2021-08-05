
#pragma once

#include <iostream>
#include <sstream>

#ifdef ENABLE_GOOGLE_TEST_SECTION
#include <gtest/gtest.h>
#endif // ENABLE_GOOGLE_TEST_SECTION

// ---------------------------------------------------------------------------

#undef OUT
#define OUT

// ---------------------------------------------------------------------------

#undef UNUSED
#define UNUSED(X) (void)(X);

namespace utils {
// ---------------------------------------------------------------------------

template <typename Out>
void splitString(const std::string &s, char delim, Out result) {
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss, OUT item, delim)) {
    *result++ = item;
  }
}

// ---------------------------------------------------------------------------

template <typename _CharT, typename _Traits>
inline std::basic_ostream<_CharT, _Traits> &tab(std::basic_ostream<_CharT, _Traits> &os) {
  return os.put(os.widen('\t'));
}

// ---------------------------------------------------------------------------

template <typename T>
std::ostream &print(std::ostream &out,
                    T const &value,
                    char separator = char{}) {
  return (out << value << separator);
}

// ---------------------------------------------------------------------------

template <typename T1, typename T2>
std::ostream &print(std::ostream &out,
                    std::pair<T1, T2> const &value,
                    char separator = char{}) {
  return (out << '{' << value.first << ", " << value.second << "}" << separator);
}

// ---------------------------------------------------------------------------

template <template<typename, typename...> class TT, typename... Args>
std::ostream &print(std::ostream &out,
                    TT<Args...> const &container,
                    char separator = char{}) {
  for (auto &&element : container) print(out, element, separator);
  return out;
}

}  

class TestModule {
 public:
 
  static void lesson7_Task2();
  static void lesson7_Task3();
};
