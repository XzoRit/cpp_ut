#include <lib/lib.hpp>

#include <vector>

#include <boost/ut.hpp>

namespace
{
constexpr auto sum = [](auto... args) { return (0 + ... + args); };

boost::ut::suite ut_assertions = [] {
  using namespace boost::ut;

  "operator"_test = [] {
    expect(sum() == 0_i);
    expect(sum(1, 2) != 1);
    expect(sum(1) > 0_i);
    expect(sum(1) <= 1_i);
  };

  "message"_test = [] { expect(sum(1, 2) == 2_i) << "wrong sum"; };

  "floating point"_test = [] {
    expect(42.1_d == 42.101) << "epsilon=0.1";
    expect(42.10_d == 42.101) << "epsilon=0.01";
    expect(42.10000001 == 42.1_d) << "epsilon=0.1";
  };

  "constant"_test = [] {
      constexpr auto compile_time_v = 42;
      auto run_time_v = 99;

      expect(constant<42_i == compile_time_v> and run_time_v == 99_i);
  };

  "fatal"_test = [] {
      std::vector v = {1, 2, 3};

      !expect(v.size() == 3_u);
      expect(v[0] == 1_i);
      expect(v[1] == 2_i);
      expect(v[2] == 3_i);
  };

  "failure"_test = [] {
      expect(1_i == 2) << "should fail";
      expect(sum() == 1_i or 2_i == sum()) << "sum?";
  };
};

boost::ut::suite ut_sections = [] {
  using namespace boost::ut;

  std::vector<int> v(5);

  !expect(std::size(v) == 5_u);

  "resize bigger"_test = [=]() mutable {
    v.resize(10);
    expect(std::size(v) == 10_u);
  };

  !expect(std::size(v) == 5_u);

  "resize smaller"_test = [=]() mutable {
    v.resize(0);
    expect(std::size(v) == 0_u);
  };
};

boost::ut::suite lib_tests = [] {
  using namespace boost::ut;
  using xzr::lib::add;

  "add"_test = [] {
    expect(add(1, 3) == 3_i);
    expect(add(2, 3) == 5_i);
    expect(add(3, 3) == 6_i);
  };
};
}

int main() {}
