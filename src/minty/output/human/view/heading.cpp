#include "heading.h"
#include "indent.h"
#include "../style.h"

namespace minty::cli::output {
    auto count(
        std::FILE* f,
        int indent,
        std::string_view heading,
        std::size_t count
    ) -> void {
        print_indent(f, indent);

        fmt::print(f, fmt::emphasis::bold, "{}", heading);
        fmt::print(f, "{}", style::interpunct);
        fmt::print(f, style::result, "{}\n", count);
    }
}
