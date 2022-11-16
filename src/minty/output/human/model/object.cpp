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
            make_row("ID", object.id),
            make_row("SHA256", object.hash),
            make_row("Size", size),
            make_row("Type", type),
            make_row("Added", object.date_added),
            make_row("Source", object.src)
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
