#include "../model.h"
#include "../view/heading.h"
#include "../view/list.h"
#include "../view/metadata.h"

namespace minty::cli::output {
    auto human_readable<post>::print(std::FILE* f, int indent, const post& post)
        -> void {
        if (!post.title.empty()) {
            fmt::print(f, style::title, "{}\n\n", post.title);
        }

        if (!post.description.empty()) {
            fmt::print(f, "{}\n\n", post.description);
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

        auto visibility = std::string(minty::to_string(post.visibility));
        visibility[0] = std::toupper(visibility[0]);

        const auto modified = post.date_created != post.date_modified
                                  ? std::make_optional(post.date_modified)
                                  : std::nullopt;

        auto meta = metadata(
            make_row("ID", post.id),
            make_row("Visibility", visibility),
            make_row("Comments", post.comment_count),
            make_row("Created", post.date_created),
            make_row("Modified", modified)
        );

        meta.indent = indent;
        meta.print(f);
    }
}
