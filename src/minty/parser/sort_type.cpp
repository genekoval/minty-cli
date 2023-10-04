#include "parser.h"

using namespace std::literals;

using minty::sort_order;
using sort_value = minty::post_sort_value;
using minty::to_string;

namespace {
    constexpr auto ascending = "ascending"sv;
    constexpr auto descending = "descending"sv;

    constexpr auto delimiter = ".";

    constexpr auto value_types = std::array {
        to_string(sort_value::date_created),
        to_string(sort_value::date_modified),
        to_string(sort_value::relevance),
        to_string(sort_value::title),
    };

    auto get_order(std::string_view argument) -> sort_order {
        if (ascending.starts_with(argument)) return sort_order::ascending;
        if (descending.starts_with(argument)) return sort_order::descending;

        throw commline::cli_error(
            fmt::format("Unknown sort order: {}", argument)
        );
    }

    auto get_value(std::string_view argument) -> sort_value {
        const auto it =
            std::find(value_types.begin(), value_types.end(), argument);

        if (it == value_types.end()) {
            throw commline::cli_error(
                fmt::format("Unknown sort type: {}", argument)
            );
        }

        const auto result = std::distance(value_types.begin(), it);
        return static_cast<sort_value>(result);
    }
}

namespace commline {
    auto parser<minty::post_sort>::parse(std::string_view argument)
        -> minty::post_sort {
        const auto delim = argument.find(delimiter);

        const auto value = get_value(argument.substr(0, delim));

        const auto order = delim == std::string_view::npos
                               ? minty::default_sort_order(value)
                               : get_order(argument.substr(delim + 1));

        return {value, order};
    }
}
