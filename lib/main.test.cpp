#include <boost/ut.hpp>

int main(int argc, const char** argv) {
  namespace ut = boost::ut;

  ut::cfg<ut::override> = {.filter = argc > 1 ? argv[1] : "",
                   .colors = argc > 2 and argv[2][0] == '1'
                           ? ut::colors{}
                           : ut::colors{.none = "", .pass = "", .fail = ""},
                   .dry_run = argc > 3 ? argv[3][0] == '1' : false};
}
