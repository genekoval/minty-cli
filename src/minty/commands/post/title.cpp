#include "commands.h"

#include "../../parser/parser.h"

#include <detail/repo.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto title(
            const app& app,
            const UUID::uuid& id,
            std::optional<std::string_view> title
        ) -> void {
            auto repo = minty::cli::repo();

            if (title) {
                const auto [modified, new_title] =
                    repo.set_post_title(id, *title);

                if (new_title) fmt::print("{}\n", *new_title);
                return;
            }

            const auto post = minty::cli::get_post(repo, id);
            if (post.title) fmt::print("{}\n", *post.title);
        }
    }
}

namespace minty::subcommands::post {
    auto title() -> std::unique_ptr<command_node> {
        return command(
            __FUNCTION__,
            "Get or set a post's title",
            options(),
            arguments(
                required<UUID::uuid>("id"),
                optional<std::string_view>("title")
            ),
            internal::title
        );
    }
}
