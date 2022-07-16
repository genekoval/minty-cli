#include "../model.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<core::object_preview>::print(
        std::FILE* f,
        int indent,
        const core::object_preview& object
    ) -> void {
        fmt::print(f, "{}\n", object.id);

        const auto type = fmt::format("{}/{}", object.type, object.subtype);

        auto meta = metadata(
            row {"Type", type}
        );

        meta.indent = indent;
        meta.print(f);
    }
}
