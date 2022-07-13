#include "../model.h"
#include "../views/metadata.h"

namespace minty::cli::output {
    auto human_readable<repo::db::tag_preview>::print(
        std::FILE* f,
        int indent,
        const repo::db::tag_preview& tag
    ) -> void {
        fmt::print(f, fmt::emphasis::bold, "{}\n", tag.name);

        auto meta = metadata(
            row {"ID", tag.id}
        );

        meta.indent = indent;
        meta.print(f);
    }
}
