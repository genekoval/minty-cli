#include "../model.h"
#include "../view/metadata.h"

namespace style = minty::cli::output::style;

namespace minty::cli::output {
    auto human_readable<tag>::print(std::FILE* f, int indent, const tag& tag)
        -> void {
        fmt::print(f, fmt::emphasis::bold, "{}\n\n", tag.name);

        if (!tag.aliases.empty()) {
            for (const auto& alias : tag.aliases) {
                fmt::print(f, "- {}\n", alias);
            }

            fmt::print(f, "\n");
        }

        if (tag.description) {
            fmt::print(f, style::secondary, style::divider);
            fmt::print(f, "{}\n", tag.description.value());
            fmt::print(f, style::secondary, style::divider);
        }

        if (!tag.sources.empty()) {
            fmt::print(f, "\n");

            for (const auto& source : tag.sources) {
                fmt::print(f, "- ");
                fmt::print(f, style::link, "{}\n", source.url);
            }

            fmt::print(f, "\n");
        }

        auto meta = metadata(
            make_row("ID", tag.id),
            make_row("Posts", tag.post_count),
            make_row("Created", tag.date_created)
        );

        meta.indent = indent;
        meta.print(f);
    }
}
