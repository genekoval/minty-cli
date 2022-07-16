#include "../model.h"
#include "../view/heading.h"
#include "../view/list.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<core::object>::print(
        std::FILE* f,
        int indent,
        const core::object& object
    ) -> void {
        const auto size = fmt::format(
            "{} ({:L} bytes)",
            object.size.formatted,
            object.size.bytes
        );

        const auto type = fmt::format("{}/{}", object.type, object.subtype);

        auto meta = metadata(
            row {"ID", object.id},
            row {"SHA256", object.hash},
            row {"Size", size},
            row {"Type", type},
            row {"Added", object.date_added},
            row {"Source", object.src}
        );

        meta.indent = indent;
        meta.print(f);

        if (!object.posts.empty()) {
            fmt::print(f, "\n");
            count(f, indent, "Posts", object.posts.size());
            ul(f, indent, object.posts);
        }
    }
}
