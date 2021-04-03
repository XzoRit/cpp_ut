#include <boost/ut.hpp>

#include <string_view>
#include <vector>

int main(int argc, const char **argv)
{
    namespace ut = boost::ut;
    using ut::utility::split;

    if (argc > 1)
    {
        if (std::string_view{argv[1]} == "--help")
        {
            std::cout << R"(
1. name filter pattern
2. comma separated list of tags
3. if "1" colors terminal output
4. if "1" dry run

note:
1. and 2. also accept globs

example:
test_exe "test*" "slow,nightly" "1" "1"

colored list of all tests starting with "test" and are either tagged slow or nightly
)";
            return 0;
        }
    }
    ut::cfg<ut::override> = {.filter = argc > 1 ? argv[1] : "",
                             .tag = split(std::string_view{argv[2]}, ','),
                             .colors = argc > 3 and argv[3][0] == '1' ? ut::colors{}
                                                                      : ut::colors{.none = "", .pass = "", .fail = ""},
                             .dry_run = argc > 4 ? argv[4][0] == '1' : false};
}
