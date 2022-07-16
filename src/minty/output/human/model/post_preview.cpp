#include "../date.h"
#include "../model.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<core::post_preview>::print(
        std::FILE* f,
        int indent,
        const core::post_preview& post
    ) -> void {
        if (post.title) fmt::print(f, fmt::emphasis::bold, "{}\n", *post.title);
        else fmt::print(f, fmt::emphasis::italic, "Untitled\n");

        auto meta = metadata(
            row {"ID", post.id},
            row {"Objects", post.object_count},
            row {"Comments", post.comment_count},
            row {"Created", post.date_created}
        );

        meta.indent = indent;
        meta.print(f);
    }
}
