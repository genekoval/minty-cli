#pragma once

#include <cstdio>

namespace minty::cli::output {
    auto print_indent(std::FILE* f, int spaces) -> void;
}
