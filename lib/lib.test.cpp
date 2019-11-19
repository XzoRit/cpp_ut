#include <lib/lib.hpp>

#include <boost/ut.hpp>

using namespace boost::ut;

using xzr::lib::add;

int main()
{
  "lib_add"_test = [] { expect(add(1, 3) == 2_i); };
}
