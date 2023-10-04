#pragma once

#include "../model.h"
#include "../style.h"
#include "indent.h"

#include <ext/math.h>

namespace minty::cli::output {
    template <typename Container>
    auto ol(std::FILE* f, int indent, const Container& list) -> void {
        const auto size = list.size();
        const auto digits = ext::digits(size);

        for (auto i = 1ul; i <= size; ++i) {
            fmt::print(f, style::index, "{:>{}}", i, indent + digits);
            fmt::print(f, "{}", style::interpunct);
            human_readable<typename Container::value_type>::print(
                f,
                indent + digits + 3,
                list[i - 1]
            );
            fmt::print(f, "\n");
        }
    }

    template <typename Container>
    auto ul(std::FILE* f, int indent, const Container& list) -> void {
        for (const auto& item : list) {
            print_indent(f, indent);
            fmt::print(f, style::index, "*");
            fmt::print(f, "{}", style::interpunct);

            print(f, indent + 4, item);
            fmt::print(f, "\n");
        }
    }
}
