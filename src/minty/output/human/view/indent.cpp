#include "indent.h"

#include <fmt/core.h>

namespace minty::cli::output {
    auto print_indent(std::FILE* f, int spaces) -> void {
        for (auto i = 0; i < spaces; ++i) fmt::print(f, " ");
    }
}
