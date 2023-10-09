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
                const auto result = repo.set_post_title(id, *title);

                if (!result.new_value.empty())
                    fmt::print("{}\n", result.new_value);
                return;
            }
            else {
                const auto post = repo.get_post(id);

                if (!post.title.empty()) fmt::print("{}\n", post.title);
                return;
            }

            throw std::runtime_error(fmt::format("{}: no such post", id));
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
