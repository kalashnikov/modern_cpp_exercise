#include<iostream>
#include<deque>

// template<typename Container, typename Index>       // final
// decltype(auto)                                     // C++14
// authAndAccess(Container&& c, Index i)              // version
// {
//   // authenticateUser();
//   return std::forward<Container>(c)[i];
// }

template<typename Container, typename Index>       // final
auto                                               // C++11
authAndAccess(Container&& c, Index i)              // version
-> decltype(std::forward<Container>(c)[i])
{
  // authenticateUser();
  return std::forward<Container>(c)[i];
}

int main() { 
  std::deque<std::string> makeStringDeque{};   // factory function

  // make copy of 5th element of deque returned
  // from makeStringDeque
  auto s = authAndAccess(makeStringDeque, 5);

  std::cout << s << std::endl;
  return 0;
}
