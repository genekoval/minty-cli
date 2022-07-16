#pragma once

#include <cstdio>
#include <string_view>

namespace minty::cli::output {
    auto count(
        std::FILE* f,
        int indent,
        std::string_view heading,
        std::size_t count
    ) -> void;
}
