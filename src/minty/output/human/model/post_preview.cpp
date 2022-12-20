#include "../date.h"
#include "../model.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<post_preview>::print(
        std::FILE* f,
        int indent,
        const post_preview& post
    ) -> void {
        if (post.title) fmt::print(f, fmt::emphasis::bold, "{}\n", *post.title);
        else fmt::print(f, fmt::emphasis::italic, "Untitled\n");

        auto meta = metadata(
            make_row("ID", post.id),
            make_row("Objects", post.object_count),
            make_row("Comments", post.comment_count),
            make_row("Created", post.date_created)
        );

        meta.indent = indent;
        meta.print(f);
    }
}
