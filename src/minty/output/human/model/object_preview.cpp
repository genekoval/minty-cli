#include "../model.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<object_preview>::print(
        std::FILE* f,
        int indent,
        const object_preview& object
    ) -> void {
        fmt::print(f, "{}\n", object.id);

        const auto type = fmt::format("{}/{}", object.type, object.subtype);

        auto meta = metadata(
            make_row("Type", type)
        );

        meta.indent = indent;
        meta.print(f);
    }
}
