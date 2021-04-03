#include <boost/ut.hpp>

#include <string_view>
#include <vector>

namespace
{
using tags_t = std::vector<std::string_view>;
tags_t as_vec(std::string_view tags) noexcept
{
    tags_t res{};
    if (tags.empty())
        return res;
    std::string_view::size_type match{tags.find(',', 0)};
    if (match == std::string_view::npos)
    {
        return {tags};
    }
    do
    {
        res.push_back(tags.substr(0, match));
        tags.remove_prefix(match + 1);
        match = tags.find(',', 0);
    } while (match != std::string_view::npos);
    res.push_back(tags);
    return res;
}
} // namespace
int main(int argc, const char **argv)
{
    namespace ut = boost::ut;

    ut::cfg<ut::override> = {.filter = argc > 1 ? argv[1] : "",
                             .tag = ::as_vec(argv[2]),
                             .colors = argc > 3 and argv[3][0] == '1' ? ut::colors{}
                                                                      : ut::colors{.none = "", .pass = "", .fail = ""},
                             .dry_run = argc > 4 ? argv[4][0] == '1' : false};
}
namespace
{
using namespace boost::ut;
suite split = [] {
    "split empty"_test = [] { expect(as_vec("") == tags_t{}); };
    "split one word"_test = [] { expect(as_vec("one") == tags_t{"one"}); };
    "split two words"_test = [] { expect(as_vec("one,two") == tags_t{"one", "two"}); };
    "split many words"_test = [] { expect(as_vec("1,2,3,4,5") == tags_t{"1", "2", "3", "4", "5"}); };
};
} // namespace
