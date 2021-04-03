#include <boost/ut.hpp>

#include <string_view>
#include <vector>

int main(int argc, const char **argv)
{
    namespace ut = boost::ut;
    using ut::utility::split;

    ut::cfg<ut::override> = {.filter = argc > 1 ? argv[1] : "",
                             .tag = split(std::string_view{argv[2]}, ','),
                             .colors = argc > 3 and argv[3][0] == '1' ? ut::colors{}
                                                                      : ut::colors{.none = "", .pass = "", .fail = ""},
                             .dry_run = argc > 4 ? argv[4][0] == '1' : false};
}
