#include "../model.h"
#include "../view/heading.h"
#include "../view/list.h"
#include "../view/metadata.h"

namespace style = minty::cli::output::style;

namespace minty::cli::output {
    auto human_readable<core::post>::print(
        std::FILE* f,
        int indent,
        const core::post& post
    ) -> void {
        if (post.title) {
            fmt::print(f, style::title, "{}\n\n", *post.title);
        }

        if (post.description) {
            fmt::print(f, "{}\n\n", *post.description);
        }

        if (!post.objects.empty()) {
            count(f, indent, "Objects", post.objects.size());
            ol(f, indent + 4, post.objects);
        }

        if (!post.posts.empty()) {
            count(f, indent, "Related Posts", post.posts.size());
            ul(f, indent + 4, post.posts);
        }

        if (!post.tags.empty()) {
            count(f, indent, "Tags", post.tags.size());
            ul(f, indent + 4, post.tags);
        }

        const auto modified = post.date_created != post.date_modified ?
            std::make_optional(post.date_modified) : std::nullopt;

        auto meta = metadata(
            row {"ID", post.id},
            row {"Created", post.date_created},
            row {"Modified", modified}
        );

        meta.indent = indent;
        meta.print(f);
    }
}
