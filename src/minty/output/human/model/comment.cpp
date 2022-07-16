#include "../date.h"
#include "../model.h"
#include "../style.h"
#include "../view/indent.h"

#include <ext/string.h>

namespace style = minty::cli::output::style;

using minty::cli::output::format_date;
using minty::cli::output::format_duration;
using minty::cli::output::print_indent;

namespace {
    using date_type = decltype(minty::core::comment::date_created);

    constexpr auto divider_style = style::secondary;
    constexpr auto metadata_style = style::secondary;

    class printer {
        std::FILE* const f;
        const int indent;
    public:
        printer(std::FILE* f, int indent) : f(f), indent(indent) {}

        auto divider() -> void {
            if (indent <= 0) return;

            print_indent(f, indent);

            fmt::print(f, divider_style, "\u250c");

            for (auto i = 0; i < 20; ++i) {
                fmt::print(f, divider_style, "\u2500");
            }

            fmt::print(f, "\n");
        }

        auto indent_with_separator() -> void {
            if (indent <= 0) return;

            print_indent(f, indent);
            fmt::print(f, divider_style, "\u2502 ");
        }

        auto newline() -> void {
            indent_with_separator();
            fmt::print(f, "\n");
        }

        auto text(std::string_view value, std::size_t width) -> void {
            auto range = ext::string_range(value, "\n");

            for (const auto& line : range) {
                if (line.empty()) {
                    newline();
                    continue;
                }

                auto size = line.size();
                auto index = 0;

                while (size > 0) {
                    auto len = std::min(width, size);

                    // Remove spaces from the beginning of the line
                    while (std::isspace(line[index])) ++index;

                    // Avoid breaking words
                    if (len < size && !std::isspace(line[len + index])) {
                        while (!std::isspace(line[len + index])) --len;
                    }

                    indent_with_separator();
                    fmt::print(f, "{}\n", line.substr(index, len));
                    index += len;
                    size -= len;
                }
            }
        }

        auto timestamp(date_type value) -> void {
            indent_with_separator();
            fmt::print(f, metadata_style, "{}{}{}\n",
                format_duration(value),
                style::interpunct,
                format_date(value)
            );
        }
    };
}

namespace minty::cli::output {
    auto human_readable<core::comment>::print(
        std::FILE* f,
        int indent,
        const core::comment& comment
    ) -> void {
        constexpr auto indent_spaces = 4;
        constexpr auto width = 80ul;

        auto p = printer(f, indent + indent_spaces * comment.indent);

        p.divider();
        p.indent_with_separator();
        fmt::print(f, metadata_style, "{}\n", comment.id);
        p.timestamp(comment.date_created);
        p.text(comment.content, width);
        p.newline();
    }

    auto human_readable<std::vector<core::comment>>::print(
        std::FILE* f,
        int indent,
        const std::vector<core::comment>& comments
    ) -> void {
        for (const auto& comment : comments) {
            human_readable<core::comment>::print(f, indent, comment);
        }
    }
}
