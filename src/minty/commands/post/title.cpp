#include "commands.h"

#include "../../parser/parser.h"

#include <detail/client.hpp>

using namespace commline;

namespace {
    namespace internal {
        auto title(
            const app& app,
            const UUID::uuid& id,
            std::optional<std::string_view> title
        ) -> void {
            minty::cli::repo([&id, title](minty::repo& repo) -> ext::task<> {
                if (title) co_await repo.set_post_title(id, *title);

                const auto post = co_await repo.get_post(id);
                if (post.title) fmt::print("{}\n", *post.title);
            });
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
