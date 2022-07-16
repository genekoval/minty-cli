#include "../model.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<core::object_preview>::print(
        std::FILE* f,
        int indent,
        const core::object_preview& object
    ) -> void {
        fmt::print(f, "{}\n", object.id);

        auto meta = metadata(
            row {"Type", fmt::format("{}/{}", object.type, object.subtype)}
        );

        meta.indent = indent;
        meta.print(f);
    }
}
