#include "../model.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<tag_preview>::print(
        std::FILE* f,
        int indent,
        const tag_preview& tag
    ) -> void {
        fmt::print(f, fmt::emphasis::bold, "{}\n", tag.name);

        auto meta = metadata(make_row("ID", tag.id));

        meta.indent = indent;
        meta.print(f);
    }
}
