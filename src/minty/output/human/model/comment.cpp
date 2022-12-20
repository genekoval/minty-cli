#include "../date.h"
#include "../model.h"
#include "../style.h"
#include "../view/indent.h"
#include "../view/metadata.h"

#include <detail/env.hpp>

#include <ext/string.h>

namespace style = minty::cli::output::style;

using minty::time_point;
using minty::cli::output::format_date;
using minty::cli::output::format_duration;
using minty::cli::output::print_indent;

namespace {
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

        auto text(std::string_view value) -> void {
            const auto width = minty::env::width();

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

        auto timestamp(time_point value) -> void {
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
    auto human_readable<comment>::print(
        std::FILE* f,
        int indent,
        const comment& comment
    ) -> void {
        auto meta = metadata(
            make_row("ID", comment.id),
            make_row("Post", comment.post_id),
            make_row("Parent", comment.parent_id),
            make_row("Level", comment.indent),
            make_row("Created", comment.date_created)
        );
        meta.indent = indent;
        meta.print(f);

        fmt::print(f, "\n");

        auto p = printer(f, indent);
        p.text(comment.content);
    }

    auto human_readable<comment_data>::print(
        std::FILE* f,
        int indent,
        const comment_data& comment
    ) -> void {
        constexpr auto indent_spaces = 4;

        auto p = printer(f, indent + indent_spaces * comment.indent);

        p.divider();
        p.indent_with_separator();
        fmt::print(f, metadata_style, "{}\n", comment.id);
        p.timestamp(comment.date_created);
        p.text(comment.content);
        p.newline();
    }

    auto human_readable<std::vector<comment_data>>::print(
        std::FILE* f,
        int indent,
        const std::vector<comment_data>& comments
    ) -> void {
        for (const auto& comment : comments) {
            human_readable<comment_data>::print(f, indent, comment);
        }
    }
}
