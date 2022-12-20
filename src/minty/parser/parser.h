#pragma once

#include "../output/output.h"

#include <minty/minty>
#include <commline/commline>
#include <uuid++/commline>

namespace commline {
    template <>
    struct parser<minty::cli::output::format> {
        static auto parse(
            std::string_view argument
        ) -> minty::cli::output::format;
    };

    template <>
    struct parser<minty::post_sort> {
        static auto parse(
            std::string_view argument
        ) -> minty::post_sort;
    };
}
