#include <lib/lib.hpp>

#include <cassert>
#include <vector>

#include <boost/ut.hpp>

namespace
{
using namespace boost::ut;

using xzr::lib::add;

constexpr auto sum = [](auto... args) { return (0 + ... + args); };

suite ut_assertions = [] {
  "operator"_test = [] {
    expect(sum() == 0_i);
    expect(sum(1, 2) != 1);
    expect(sum(1) > 0_i);
    expect(sum(1) <= 1_i);
  };

  "message"_test = [] { expect(sum(1, 2) == 2_i) << "wrong sum"; };

  "that"_test = [] {
    expect(that % 0 == sum());
    expect(that % 42 == sum(40, 2) and that % (1 + 2) == sum(1, 2));
    expect(that % 1 != 2 or 2_i > 3);
  };

  "eq/neq/gt/ge/lt/le"_test = [] {
    expect(eq(42, sum(40, 2)));
    expect(neq(1, 2));
    expect(eq(sum(1), 1) and neq(sum(1, 2), 2));
    expect(eq(1, 1) and that % 1 == 1 and 1_i == 1);
  };

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
    std::vector v = { 1, 2, 3 };

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

suite ut_sections = [] {
  std::vector<int> v(5);

  !expect(std::size(v) == 5_u);

  "resize bigger"_test = [v]() {
    mut(v).resize(10);
    expect(std::size(v) == 10_u);
  };

  !expect(std::size(v) == 5_u);

  "resize smaller"_test = [v]() {
    mut(v).resize(0);
    expect(std::size(v) == 0_u);
  };
};

suite ut_exceptions_abort = [] {
  "exceptions"_test = [] {
    expect(throws<std::runtime_error>([] { throw std::runtime_error(""); })) << "throws runtime_error";
    expect(throws([] { throw 0; })) << "throws any exception";
    expect(nothrow([] {})) << "does not throw";
  };

  "aborts"_test = [] { expect(aborts([] { assert(false); })); };
};

suite ut_matchers = [] {};

suite ut_param_tests = [] {
  "param test"_test =
    [](const auto& a) {
      expect(that % a > 0) << "all values are greater than 0";
    } |
    std::vector{ 1, 2, 3, -1 };
};

suite lib_tests = [] {
  "add"_test = [] {
    expect(add(1, 3) == 3_i);
    expect(add(2, 3) == 5_i);
    expect(add(3, 3) == 6_i);
  };
};
}

int main() {}
